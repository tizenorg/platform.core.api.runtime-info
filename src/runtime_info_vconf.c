/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
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
#include <stdlib.h>
#include <string.h>

#include <vconf.h>
#include <dlog.h>

#include <runtime_info.h>
#include <runtime_info_private.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "CAPI_SYSTEM_RUNTIME_INFO"

#define CHECK_VCONF_RESULT(ret) \
	do { \
		if (ret < 0) { \
			ret = vconf_get_ext_errno(); \
			if (ret == VCONF_ERROR_FILE_NO_ENT) \
				ret = RUNTIME_INFO_ERROR_NOT_SUPPORTED; \
			else \
				ret = RUNTIME_INFO_ERROR_IO_ERROR; \
		} else { \
			ret = RUNTIME_INFO_ERROR_NONE; \
		} \
	} while (0);

int runtime_info_vconf_get_value_int(const char *vconf_key, int *value)
{
	int ret = vconf_get_int(vconf_key, value);
	CHECK_VCONF_RESULT(ret);
	return ret;
}

int runtime_info_vconf_get_value_bool(const char *vconf_key, int *value)
{
	int ret = vconf_get_bool(vconf_key, value);
	CHECK_VCONF_RESULT(ret);
	return ret;
}

int runtime_info_vconf_get_value_double(const char *vconf_key, double *value)
{
	int ret = vconf_get_dbl(vconf_key, value);
	CHECK_VCONF_RESULT(ret);
	return ret;
}

int runtime_info_vconf_get_value_string(const char *vconf_key, char **value)
{
	char *str_value = NULL;
	int ret;

	str_value = vconf_get_str(vconf_key);
	if (!str_value) {
		ret = -1;
		CHECK_VCONF_RESULT(ret);
		return ret;
	}

	*value = str_value;
	return RUNTIME_INFO_ERROR_NONE;
}

typedef void (*runtime_info_vconf_event_cb)(keynode_t *node, void *event_data);

static void runtime_info_vconf_event_cb0(keynode_t *node, void *event_data)
{
	if (node != NULL)
		runtime_info_updated((runtime_info_key_e)event_data);
}

static void runtime_info_vconf_event_cb1(keynode_t *node, void *event_data)
{
	if (node != NULL)
		runtime_info_updated((runtime_info_key_e)event_data);
}

static void runtime_info_vconf_event_cb2(keynode_t *node, void *event_data)
{
	if (node != NULL)
		runtime_info_updated((runtime_info_key_e)event_data);
}

static void runtime_info_vconf_event_cb3(keynode_t *node, void *event_data)
{
	if (node != NULL)
		runtime_info_updated((runtime_info_key_e)event_data);
}

static void runtime_info_vconf_event_cb4(keynode_t *node, void *event_data)
{
	if (node != NULL)
		runtime_info_updated((runtime_info_key_e)event_data);
}

static runtime_info_vconf_event_cb runtime_info_vconf_get_event_cb_slot(int slot)
{
	switch (slot) {
	case 0:
		return runtime_info_vconf_event_cb0;

	case 1:
		return runtime_info_vconf_event_cb1;

	case 2:
		return runtime_info_vconf_event_cb2;

	case 3:
		return runtime_info_vconf_event_cb3;

	case 4:
		return runtime_info_vconf_event_cb4;

	default:
		return NULL;
	}
}

int runtime_info_vconf_set_event_cb(const char *vconf_key, runtime_info_key_e runtime_info_key, int slot)
{
	runtime_info_vconf_event_cb vconf_event_cb;
	int ret;

	vconf_event_cb = runtime_info_vconf_get_event_cb_slot(slot);

	if (vconf_event_cb == NULL)
		return RUNTIME_INFO_ERROR_IO_ERROR;

	ret = vconf_notify_key_changed(vconf_key, vconf_event_cb, (void *)runtime_info_key);
	CHECK_VCONF_RESULT(ret);
	return ret;
}

void runtime_info_vconf_unset_event_cb(const char *vconf_key, int slot)
{
	runtime_info_vconf_event_cb vconf_event_cb;

	vconf_event_cb = runtime_info_vconf_get_event_cb_slot(slot);

	if (vconf_event_cb != NULL)
		vconf_ignore_key_changed(vconf_key, vconf_event_cb);
}
