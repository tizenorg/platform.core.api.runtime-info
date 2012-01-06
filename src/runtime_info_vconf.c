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

#define LOG_TAG "TIZEN_N_RUNTIME_INFO"

int runtime_info_vconf_get_value_int(const char *vconf_key, int *value)
{
	return vconf_get_int(vconf_key, value);
}

int runtime_info_vconf_get_value_bool(const char *vconf_key, bool *value)
{
	return vconf_get_bool(vconf_key, (int*)value);
}

int runtime_info_vconf_get_value_double(const char *vconf_key, double *value)
{
	return vconf_get_dbl(vconf_key, value);
}

int runtime_info_vconf_get_value_string(const char *vconf_key, char **value)
{
	char *str_value = NULL;

	str_value = vconf_get_str(vconf_key);
		
	if (str_value != NULL)
	{
		*value = str_value;
		return 0;
	}
	else
	{
		return -1;
	}
}

static void runtime_info_vconf_event_broker(keynode_t *node, void *event_data)
{
	if (node != NULL)
	{
		runtime_info_updated((runtime_info_key_e)event_data);
	}		
}

int runtime_info_vconf_set_event_cb (const char *vconf_key, runtime_info_key_e runtime_info_key)
{
	if (vconf_notify_key_changed(vconf_key, runtime_info_vconf_event_broker, (void*)runtime_info_key))
	{
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

void runtime_info_vconf_unset_event_cb (const char *vconf_key)
{
	vconf_ignore_key_changed(vconf_key, runtime_info_vconf_event_broker);
}

