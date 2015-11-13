/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <dlog.h>

#include <runtime_info.h>
#include <runtime_info_private.h>

#include <E_DBus.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "CAPI_RUNTIME_INFO_USAGE"

#define _E(fmt, arg...) LOGE("[%s,%d] "fmt, __FUNCTION__, __LINE__, ##arg)
#define _D(fmt, arg...) LOGD("[%s,%d] "fmt, __FUNCTION__, __LINE__, ##arg)
#define _I(fmt, arg...) LOGI("[%s,%d] "fmt, __FUNCTION__, __LINE__, ##arg)

#define RESOURCED_BUS_NAME "org.tizen.resourced"
#define RESOURCED_USAGE_OBJECT_NAME "/Org/Tizen/ResourceD/Process"
#define RESOURCED_USAGE_INTERFACE_NAME "org.tizen.resourced.process"
#define RESOURCED_MEMORY_USAGE_METHOD "ProcMemoryUsage"
#define RESOURCED_CPU_USAGE_METHOD "ProcCpuUsage"
#define DBUS_REPLY_TIMEOUT (120 * 1000)
#define MEMORY_USAGE 1
#define CPU_USAGE 2

#define kBtoKiB(val) (int)(((long long)val * 1024)/1000)

static int runtime_info_get_dbus_error(const char *err_name)
{
	int size;

	if (!err_name)
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;

	size = strlen(err_name);
	if (!strncmp(err_name, DBUS_ERROR_IO_ERROR, size))
		return RUNTIME_INFO_ERROR_IO_ERROR;
	else if (!strncmp(err_name, DBUS_ERROR_NO_MEMORY, size))
		return RUNTIME_INFO_ERROR_OUT_OF_MEMORY;
	else if (!strncmp(err_name, DBUS_ERROR_ACCESS_DENIED, size))
		return RUNTIME_INFO_ERROR_PERMISSION_DENIED;
	else
		return RUNTIME_INFO_ERROR_REMOTE_IO;
}

/* Handler function which handles dbus related instructions
 * for both per process memory and cpu requests.
 * Creates the method call to resourced and receives the reply (if successful)
 * Return the received reply (if received) else NULL to signify failed call to resourced
 */
static DBusMessage *runtime_info_dbus_process_usage_info(int *pid, int size, int info, int *error)
{
	DBusConnection *conn;
	DBusMessage *msg;
	DBusMessage *reply;
	DBusError err;
	int ret;

	if (!pid || !error) {
		_E("INVALID_PARAMETER(0x%08x): pid list and error params cannot be null");

		if (error)
			*error = RUNTIME_INFO_ERROR_INVALID_PARAMETER;
		return NULL;
	}

	conn = dbus_bus_get(DBUS_BUS_SYSTEM, NULL);
	if (!conn) {
		_E("DBUS_CONNECTION_ERROR");
		*error = RUNTIME_INFO_ERROR_REMOTE_IO;
		return NULL;
	}

	if (info == MEMORY_USAGE) {
		_D("Process %d: received query to get process memory info of %d processes",
				getpid(), size);
		msg = dbus_message_new_method_call(RESOURCED_BUS_NAME,
				RESOURCED_USAGE_OBJECT_NAME,
				RESOURCED_USAGE_INTERFACE_NAME,
				RESOURCED_MEMORY_USAGE_METHOD);
	} else if (info == CPU_USAGE) {
		_D("Process %d: received query to get process cpu usage of %d processes",
				getpid(), size);
		msg = dbus_message_new_method_call(RESOURCED_BUS_NAME,
				RESOURCED_USAGE_OBJECT_NAME,
				RESOURCED_USAGE_INTERFACE_NAME,
				RESOURCED_CPU_USAGE_METHOD);
	} else {
		_E("INVALID_PARAMETER(0x%08x): info parameter should be %d or %d",
				MEMORY_USAGE, CPU_USAGE, RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		*error = RUNTIME_INFO_ERROR_INVALID_PARAMETER;
		return NULL;
	}

	if (!msg) {
		_E("DBUS_METHOD_CALL: not able to create method call (%s:%s-%s)",
				RESOURCED_USAGE_OBJECT_NAME, RESOURCED_USAGE_INTERFACE_NAME,
				RESOURCED_MEMORY_USAGE_METHOD);
		*error = RUNTIME_INFO_ERROR_OUT_OF_MEMORY;
		return NULL;
	}

	ret = dbus_message_append_args(msg, DBUS_TYPE_ARRAY, DBUS_TYPE_INT32, &pid,
			size, DBUS_TYPE_INVALID);
	if (!ret) {
		_E("DBUS_METHOD_CALL: not able to append pid array to message");
		*error = RUNTIME_INFO_ERROR_IO_ERROR;
		dbus_message_unref(msg);
		return NULL;
	}

	dbus_error_init(&err);
	*error = 0;

	if (info == MEMORY_USAGE)
		_D("Process %d: Sending dbus message to resourced for process memory usage info",
				getpid());
	else
		_D("Process %d: Sending dbus message to resourced for process cpu usage info",
				getpid());
	reply = dbus_connection_send_with_reply_and_block(conn, msg,
			DBUS_REPLY_TIMEOUT, &err);
	if (!reply)
		_E("DBUS_METHOD_CALL: not able to send message");

	if (dbus_error_is_set(&err)) {
		_E("DBUS_METHOD_CALL: dbus_connection_send error(%s:%s)", err.name, err.message);
		*error = runtime_info_get_dbus_error(err.name);
		dbus_error_free(&err);
		reply = NULL;
	}

	dbus_message_unref(msg);
	return reply;
}

API int runtime_info_get_system_memory_info(runtime_memory_info_s *info)
{
	FILE *meminfo_fp;
	char buf[256];
	unsigned long swap_total, swap_free, value;

	if (info == NULL) {
		_E("INVALID_PARAMETER(0x%08x) : invalid output param",
				RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	swap_total = swap_free = 0;

	meminfo_fp = fopen("/proc/meminfo", "r");
	if (meminfo_fp == NULL) {
		_E("IO_ERROR(0x%08x) : failed to open file to read memory usage",
				RUNTIME_INFO_ERROR_IO_ERROR);
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	while (fgets(buf, sizeof(buf), meminfo_fp) != NULL) {
		if (sscanf(buf, "MemTotal: %lu", &value) == 1)
			info->total = kBtoKiB(value);
		else if (sscanf(buf, "MemFree: %lu", &value) == 1)
			info->free = kBtoKiB(value);
		else if (sscanf(buf, "Cached: %lu", &value) == 1)
			info->cache = kBtoKiB(value);
		else if (sscanf(buf, "SwapTotal: %lu", &value) == 1)
			swap_total = value;
		else if (sscanf(buf, "SwapFree: %lu", &value) == 1)
			swap_free = value;
	}
	fclose(meminfo_fp);

	info->used = (info->total > info->free) ? (info->total - info->free) : 0;
	info->swap = kBtoKiB(((swap_total > swap_free) ? (int)(swap_total - swap_free) : 0));

	return RUNTIME_INFO_ERROR_NONE;
}

API int runtime_info_get_process_memory_info(int *pid, int size, process_memory_info_s **info)
{
	DBusMessageIter iter, iter_array, iter_struct;
	int index, value;
	int error;
	process_memory_info_s *proc_info;
	DBusMessage *replymsg;

	if (!pid || size <= 0) {
		_E("INVALID_PARAMETER(0x%08x) : invalid input param",
				RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	if (!info) {
		_E("INVALID_PARAMETER(0x%08x) : invalid output param",
				RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	*info = NULL;

	/* Get the needed information from resourced daemon using dbus */
	replymsg = runtime_info_dbus_process_usage_info(pid, size, MEMORY_USAGE, &error);
	if (!replymsg) {
		_E("DBUS_METHOD_CALL: call to resourced not successful");
		return error;
	}

	/* Check if the message is an error message or not in expected
	 * format and return error value */
	dbus_message_iter_init(replymsg, &iter);
	if (dbus_message_iter_get_arg_type(&iter) == DBUS_TYPE_INT32) {
		dbus_message_iter_get_basic(&iter, &error);
		_E("DBUS_METHOD_CALL: call to resourced returned error message");
		dbus_message_unref(replymsg);
		return error;
	} else if (dbus_message_iter_get_arg_type(&iter) != DBUS_TYPE_ARRAY) {
		_E("DBUS_METHOD_CALL: received dbus message is not in expected format");
		dbus_message_unref(replymsg);
		return RUNTIME_INFO_ERROR_REMOTE_IO;
	}

	/* Populate the entries of info array using the data received from resourced */
	*info = (process_memory_info_s *)malloc(size * sizeof(process_memory_info_s));
	if (!info) {
		_E("OUT_OF_MEMORY(0x%08x)", RUNTIME_INFO_ERROR_OUT_OF_MEMORY);
		dbus_message_unref(replymsg);
		return RUNTIME_INFO_ERROR_OUT_OF_MEMORY;
	}

	dbus_message_iter_recurse(&iter, &iter_array);
	for (index = 0; index < size; ++index) {
		proc_info = &(*info)[index];

		dbus_message_iter_recurse(&iter_array, &iter_struct);

		dbus_message_iter_get_basic(&iter_struct, &value);
		proc_info->vsz = value;
		dbus_message_iter_next(&iter_struct);
		dbus_message_iter_get_basic(&iter_struct, &value);
		proc_info->rss = value;
		dbus_message_iter_next(&iter_struct);
		dbus_message_iter_get_basic(&iter_struct, &value);
		proc_info->pss = value;
		dbus_message_iter_next(&iter_struct);
		dbus_message_iter_get_basic(&iter_struct, &value);
		proc_info->shared_clean = value;
		dbus_message_iter_next(&iter_struct);
		dbus_message_iter_get_basic(&iter_struct, &value);
		proc_info->shared_dirty = value;
		dbus_message_iter_next(&iter_struct);
		dbus_message_iter_get_basic(&iter_struct, &value);
		proc_info->private_clean = value;
		dbus_message_iter_next(&iter_struct);
		dbus_message_iter_get_basic(&iter_struct, &value);
		proc_info->private_dirty = value;

		dbus_message_iter_next(&iter_array);
	}

	dbus_message_unref(replymsg);
	return RUNTIME_INFO_ERROR_NONE;
}

API int runtime_info_get_cpu_usage(runtime_cpu_usage_s *usage)
{
	FILE *cpuinfo_fp;
	char buf[256];
	unsigned long long user, nice, system, idle, iowait, irq, softirq, total_uptime;

	if (usage == NULL) {
		_E("INVALID_PARAMETER(0x%08x) : invalid output param",
				RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	cpuinfo_fp = fopen("/proc/stat", "r");
	if (cpuinfo_fp == NULL) {
		_E("IO_ERROR(0x%08x) : failed to open file to read cpu usage",
				RUNTIME_INFO_ERROR_IO_ERROR);
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	while (fgets(buf, sizeof(buf), cpuinfo_fp) != NULL) {
		if (!strncmp(buf, "cpu ", 4) &&
		    sscanf(buf+4, "%llu %llu %llu %llu %llu %llu %llu",
				&user, &nice, &system, &idle,
				&iowait, &irq, &softirq) == 7)
			break;
	}
	fclose(cpuinfo_fp);

	total_uptime = user+nice+system+idle+iowait+irq+softirq;

	usage->user = (double)user*100/total_uptime;
	usage->nice = (double)nice*100/total_uptime;
	usage->system = (double)system*100/total_uptime;
	usage->iowait = (double)iowait*100/total_uptime;

	return RUNTIME_INFO_ERROR_NONE;
}

API int runtime_info_get_process_cpu_usage(int *pid, int size, process_cpu_usage_s **usage)
{
	DBusMessageIter iter, iter_array, iter_struct;
	int index, value;
	int error;
	process_cpu_usage_s *proc_usage;
	DBusMessage *replymsg;

	if (!pid || size <= 0) {
		_E("INVALID_PARAMETER(0x%08x) : invalid input param",
				RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	if (!usage) {
		_E("INVALID_PARAMETER(0x%08x) : invalid output param",
				RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	*usage = NULL;

	/* Get the needed information from resourced daemon using dbus */
	replymsg = runtime_info_dbus_process_usage_info(pid, size, CPU_USAGE, &error);
	if (!replymsg) {
		_E("DBUS_METHOD_CALL: call to resourced not successful");
		return error;
	}

	/* Check if the message is an error message or not in expected format
	 * and return error value */
	dbus_message_iter_init(replymsg, &iter);
	if (dbus_message_iter_get_arg_type(&iter) == DBUS_TYPE_INT32) {
		dbus_message_iter_get_basic(&iter, &error);
		_E("DBUS_METHOD_CALL: call to resourced returned error message");
		dbus_message_unref(replymsg);
		return error;
	} else if (dbus_message_iter_get_arg_type(&iter) != DBUS_TYPE_ARRAY) {
		_E("DBUS_METHOD_CALL: received dbus message is not in expected format");
		dbus_message_unref(replymsg);
		return RUNTIME_INFO_ERROR_REMOTE_IO;
	}

	/* Populate the entries of info array using the data received from resourced */
	*usage = (process_cpu_usage_s *)malloc(size * sizeof(process_cpu_usage_s));
	if (!(*usage)) {
		_E("OUT_OF_MEMORY(0x%08x)", RUNTIME_INFO_ERROR_OUT_OF_MEMORY);
		dbus_message_unref(replymsg);
		return RUNTIME_INFO_ERROR_OUT_OF_MEMORY;
	}

	dbus_message_iter_recurse(&iter, &iter_array);
	for (index = 0; index < size; ++index) {
		proc_usage = &(*usage)[index];

		dbus_message_iter_recurse(&iter_array, &iter_struct);

		dbus_message_iter_get_basic(&iter_struct, &value);
		proc_usage->utime = value;
		dbus_message_iter_next(&iter_struct);
		dbus_message_iter_get_basic(&iter_struct, &value);
		proc_usage->stime = value;

		dbus_message_iter_next(&iter_array);
	}

	dbus_message_unref(replymsg);
	return RUNTIME_INFO_ERROR_NONE;
}
