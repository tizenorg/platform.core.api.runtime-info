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

static const char *VCONF_LOCATION_SERVICE_ENABLED = VCONFKEY_LOCATION_ENABLED;
static const char *VCONF_LOCATION_AGPS_ENABLED = VCONFKEY_LOCATION_AGPS_ENABLED;
static const char *VCONF_LOCATION_NETWORK_ENABLED = VCONFKEY_LOCATION_NETWORK_ENABLED;

int runtime_info_location_service_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_LOCATION_SERVICE_ENABLED, &vconf_value))
		vconf_value = 0;

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_location_service_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_LOCATION_SERVICE_ENABLED, RUNTIME_INFO_KEY_LOCATION_SERVICE_ENABLED, 0);
}

void runtime_info_location_service_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_LOCATION_SERVICE_ENABLED, 0);
}

int runtime_info_location_agps_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_LOCATION_AGPS_ENABLED, &vconf_value))
		vconf_value = 0;

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_location_agps_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_LOCATION_AGPS_ENABLED, RUNTIME_INFO_KEY_LOCATION_ADVANCED_GPS_ENABLED, 0);
}

void runtime_info_location_agps_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_LOCATION_AGPS_ENABLED, 0);
}

int runtime_info_location_network_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_LOCATION_NETWORK_ENABLED, &vconf_value))
		vconf_value = 0;

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_location_network_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_LOCATION_NETWORK_ENABLED, RUNTIME_INFO_KEY_LOCATION_NETWORK_POSITION_ENABLED, 0);
}

void runtime_info_location_network_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_LOCATION_NETWORK_ENABLED, 0);
}
