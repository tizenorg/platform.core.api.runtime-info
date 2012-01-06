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

static const char *VCONF_FLIGHT_MODE = VCONFKEY_SETAPPL_FLIGHT_MODE_BOOL;
static const char *VCONF_AUDIO_JACK = VCONFKEY_SYSMAN_EARJACK;
static const char *VCONF_SILENT_MODE = "db/setting/sound/sound_on";
static const char *VCONF_VIBRATION_ENABLED = "db/setting/sound/vibration_on";
static const char *VCONF_ROTATION_LOCK_ENABLED = VCONFKEY_SETAPPL_ROTATE_LOCK_BOOL;
static const char *VCONF_BATTERY_CHARGING = VCONFKEY_SYSMAN_BATTERY_CHARGE_NOW;


int runtime_info_flightmode_get_value(runtime_info_value_h value)
{
	bool vconf_value;
	
	if (runtime_info_vconf_get_value_bool(VCONF_FLIGHT_MODE, &vconf_value))
	{
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_flightmode_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_FLIGHT_MODE, RUNTIME_INFO_KEY_FLIGHT_MODE_ENABLED);
}

void runtime_info_flightmode_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_FLIGHT_MODE);
}

int runtime_info_audiojack_get_value (runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_AUDIO_JACK, &vconf_value))
	{
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	switch (vconf_value)
	{
	case VCONFKEY_SYSMAN_EARJACK_3WIRE:
	case VCONFKEY_SYSMAN_EARJACK_4WIRE:
		value->b = true;
		break;

	default:
		value->b = false;
		break;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_audiojack_set_event_cb ()
{
	return runtime_info_vconf_set_event_cb(VCONF_AUDIO_JACK, RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED);
}

void runtime_info_audiojack_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_AUDIO_JACK);
}

int runtime_info_silent_mode_get_value(runtime_info_value_h value)
{
	bool vconf_value;
	
	if (runtime_info_vconf_get_value_bool(VCONF_SILENT_MODE, &vconf_value))
	{
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_silent_mode_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_SILENT_MODE, RUNTIME_INFO_KEY_SILENT_MODE_ENABLED);
}

void runtime_info_silent_mode_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_SILENT_MODE);
}

int runtime_info_vibration_enabled_get_value(runtime_info_value_h value)
{
	bool vconf_value;
	
	if (runtime_info_vconf_get_value_bool(VCONF_VIBRATION_ENABLED, &vconf_value))
	{
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_vibration_enabled_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_VIBRATION_ENABLED, RUNTIME_INFO_KEY_VIBRATION_ENABLED);
}

void runtime_info_vibration_enabled_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_VIBRATION_ENABLED);
}

int runtime_info_rotation_lock_enabled_get_value(runtime_info_value_h value)
{
	bool vconf_value;
	
	if (runtime_info_vconf_get_value_bool(VCONF_ROTATION_LOCK_ENABLED, &vconf_value))
	{
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_rotation_lock_enabled_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_ROTATION_LOCK_ENABLED, RUNTIME_INFO_KEY_ROTATION_LOCK_ENABLED);
}

void runtime_info_rotation_lock_enabled_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_ROTATION_LOCK_ENABLED);
}

int runtime_info_battery_charging_get_value (runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_BATTERY_CHARGING, &vconf_value))
	{
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_battery_charging_set_event_cb ()
{
	return runtime_info_vconf_set_event_cb(VCONF_BATTERY_CHARGING, RUNTIME_INFO_KEY_BATTERY_IS_CHARGING);
}

void runtime_info_battery_charging_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_BATTERY_CHARGING);
}

