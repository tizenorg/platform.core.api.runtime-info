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

#include <dlog.h>

#include <runtime_info.h>
#include <runtime_info_private.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "CAPI_SYSTEM_RUNTIME_INFO"

#define kBtoKiB(val) (int)(((long long)val*1024)/1000)

API int runtime_info_get_system_memory_info(runtime_memory_info_s *info)
{
	FILE *meminfo_fp;
	char buf[256];
	unsigned long swap_total, swap_free, value;

	if (info == NULL) {
		LOGE("INVALID_PARAMETER(0x%08x) : invalid output param", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	swap_total = swap_free = 0;

	meminfo_fp = fopen("/proc/meminfo", "r");
	if (meminfo_fp == NULL) {
		LOGE("IO_ERROR(0x%08x) : failed to open file to read memory usage", RUNTIME_INFO_ERROR_IO_ERROR);
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
	return RUNTIME_INFO_ERROR_NONE;
}

API int runtime_info_get_cpu_usage(runtime_cpu_usage_s *usage)
{
	FILE *cpuinfo_fp;
	char buf[256];
	unsigned long long user, nice, system, idle, iowait, irq, softirq, total_uptime;

	if (usage == NULL) {
		LOGE("INVALID_PARAMETER(0x%08x) : invalid output param", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	cpuinfo_fp = fopen("/proc/stat", "r");
	if (cpuinfo_fp == NULL) {
		LOGE("IO_ERROR(0x%08x) : failed to open file to read cpu usage", RUNTIME_INFO_ERROR_IO_ERROR);
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
	return RUNTIME_INFO_ERROR_NONE;
}
