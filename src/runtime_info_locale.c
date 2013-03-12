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

static const char *VCONF_24HOUR_FORMAT = "db/menu_widget/regionformat_time1224";
static const char *VCONF_FIRST_DAY_OF_WEEK = "db/setting/weekofday_format";
static const char *VCONF_LANGUAGE = VCONFKEY_LANGSET;
static const char *VCONF_REGION = VCONFKEY_REGIONFORMAT;

int runtime_info_24hour_format_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_24HOUR_FORMAT, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	switch (vconf_value) {
	case VCONFKEY_TIME_FORMAT_12:
		value->b = false;
		break;

	case VCONFKEY_TIME_FORMAT_24:
		value->b = true;
		break;

	default:
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_24hour_format_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_24HOUR_FORMAT, RUNTIME_INFO_KEY_24HOUR_CLOCK_FORMAT_ENABLED, 0);
}

void runtime_info_24hour_format_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_24HOUR_FORMAT, 0);
}

int runtime_info_first_day_of_week_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_FIRST_DAY_OF_WEEK, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	switch (vconf_value) {
	case SETTING_WEEKOFDAY_FORMAT_SUNDAY:
		value->i = RUNTIME_INFO_FIRST_DAY_OF_WEEK_SUNDAY;
		break;

	case SETTING_WEEKOFDAY_FORMAT_MONDAY:
		value->i = RUNTIME_INFO_FIRST_DAY_OF_WEEK_MONDAY;
		break;

	case SETTING_WEEKOFDAY_FORMAT_TUESDAY:
		value->i = RUNTIME_INFO_FIRST_DAY_OF_WEEK_TUESDAY;
		break;

	case SETTING_WEEKOFDAY_FORMAT_WEDNESDAY:
		value->i = RUNTIME_INFO_FIRST_DAY_OF_WEEK_WEDNESDAY;
		break;

	case SETTING_WEEKOFDAY_FORMAT_THURSDAY:
		value->i = RUNTIME_INFO_FIRST_DAY_OF_WEEK_THURSDAY;
		break;

	case SETTING_WEEKOFDAY_FORMAT_FRIDAY:
		value->i = RUNTIME_INFO_FIRST_DAY_OF_WEEK_FRIDAY;
		break;

	case SETTING_WEEKOFDAY_FORMAT_SATURDAY:
		value->i = RUNTIME_INFO_FIRST_DAY_OF_WEEK_SATURDAY;
		break;

	default:
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_first_day_of_week_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_FIRST_DAY_OF_WEEK, RUNTIME_INFO_KEY_FIRST_DAY_OF_WEEK, 0);
}

void runtime_info_first_day_of_week_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_FIRST_DAY_OF_WEEK, 0);
}

int runtime_info_language_get_value(runtime_info_value_h value)
{
	char *vconf_value;
	char *token = NULL;

	if (runtime_info_vconf_get_value_string(VCONF_LANGUAGE, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	token = strchr(vconf_value, '.');

	if(token)
		*token = '\0';

	value->s = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_language_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_LANGUAGE, RUNTIME_INFO_KEY_LANGUAGE, 0);
}

void runtime_info_language_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_LANGUAGE, 0);
}

int runtime_info_region_get_value(runtime_info_value_h value)
{
	char *vconf_value;

	if (runtime_info_vconf_get_value_string(VCONF_REGION, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	value->s = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_region_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_REGION, RUNTIME_INFO_KEY_REGION, 0);
}

void runtime_info_region_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_REGION, 0);
}

