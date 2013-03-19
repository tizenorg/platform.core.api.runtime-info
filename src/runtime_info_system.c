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

static const char *VCONF_FLIGHT_MODE = VCONFKEY_TELEPHONY_FLIGHT_MODE;
static const char *VCONF_AUDIO_JACK = VCONFKEY_SYSMAN_EARJACK;
static const char *VCONF_SILENT_MODE = "db/setting/sound/sound_on";
static const char *VCONF_VIBRATION_ENABLED = "db/setting/sound/vibration_on";
static const char *VCONF_ROTATION_LOCK_ENABLED = VCONFKEY_SETAPPL_AUTO_ROTATE_SCREEN_BOOL;
static const char *VCONF_BATTERY_CHARGING = VCONFKEY_SYSMAN_BATTERY_CHARGE_NOW;
static const char *VCONF_TVOUT_CONNECTED = VCONFKEY_SYSMAN_EARJACK;
static const char *VCONF_AUDIO_JACK_STATUS = VCONFKEY_SYSMAN_EARJACK;
static const char *VCONF_SLIDING_KEYBOARD_STATUS = VCONFKEY_SYSMAN_SLIDING_KEYBOARD;
static const char *VCONF_USB_CONNECTED = VCONFKEY_SYSMAN_USB_STATUS;
static const char *VCONF_CHARGER_CONNECTED = VCONFKEY_SYSMAN_CHARGER_STATUS;


int runtime_info_flightmode_get_value(runtime_info_value_h value)
{
	bool vconf_value;

	if (runtime_info_vconf_get_value_bool(VCONF_FLIGHT_MODE, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_flightmode_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONF_FLIGHT_MODE, RUNTIME_INFO_KEY_FLIGHT_MODE_ENABLED, 0);
}

void runtime_info_flightmode_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONF_FLIGHT_MODE, 0);
}

int runtime_info_audiojack_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_AUDIO_JACK, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	switch (vconf_value) {
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

int runtime_info_audiojack_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONF_AUDIO_JACK, RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED, 0);
}

void runtime_info_audiojack_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONF_AUDIO_JACK, 0);
}

int runtime_info_silent_mode_get_value(runtime_info_value_h value)
{
	bool vconf_value;

	if (runtime_info_vconf_get_value_bool(VCONF_SILENT_MODE, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_silent_mode_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONF_SILENT_MODE, RUNTIME_INFO_KEY_SILENT_MODE_ENABLED, 0);
}

void runtime_info_silent_mode_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONF_SILENT_MODE, 0);
}

int runtime_info_vibration_enabled_get_value(runtime_info_value_h value)
{
	bool vconf_value;

	if (runtime_info_vconf_get_value_bool(VCONF_VIBRATION_ENABLED, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_vibration_enabled_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONF_VIBRATION_ENABLED, RUNTIME_INFO_KEY_VIBRATION_ENABLED, 0);
}

void runtime_info_vibration_enabled_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONF_VIBRATION_ENABLED, 0);
}

int runtime_info_auto_rotation_enabled_get_value(runtime_info_value_h value)
{
	bool vconf_value;

	if (runtime_info_vconf_get_value_bool(VCONF_ROTATION_LOCK_ENABLED, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_auto_rotation_enabled_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONF_ROTATION_LOCK_ENABLED, RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED, 0);
}

void runtime_info_auto_rotation_enabled_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONF_ROTATION_LOCK_ENABLED, 0);
}

int runtime_info_battery_charging_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_BATTERY_CHARGING, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_battery_charging_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONF_BATTERY_CHARGING, RUNTIME_INFO_KEY_BATTERY_IS_CHARGING, 0);
}

void runtime_info_battery_charging_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONF_BATTERY_CHARGING, 0);
}


int runtime_info_tvout_connected_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_TVOUT_CONNECTED, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	switch (vconf_value) {
	case VCONFKEY_SYSMAN_EARJACK_TVOUT:
		value->b = true;
		break;

	default:
		value->b = false;
		break;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_tvout_connected_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONF_TVOUT_CONNECTED, RUNTIME_INFO_KEY_TV_OUT_CONNECTED, 1);
}

void runtime_info_tvout_connected_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONF_TVOUT_CONNECTED, 1);
}


int runtime_info_audio_jack_status_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_AUDIO_JACK_STATUS, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	switch (vconf_value) {
	case VCONFKEY_SYSMAN_EARJACK_3WIRE:
		value->i = RUNTIME_INFO_AUDIO_JACK_STATUS_CONNECTED_3WIRE;
		break;

	case VCONFKEY_SYSMAN_EARJACK_4WIRE:
		value->i = RUNTIME_INFO_AUDIO_JACK_STATUS_CONNECTED_4WIRE;
		break;

	default:
		value->i = RUNTIME_INFO_AUDIO_JACK_STATUS_UNCONNECTED;
		break;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_audio_jack_status_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONF_AUDIO_JACK_STATUS, RUNTIME_INFO_KEY_AUDIO_JACK_STATUS, 2);
}

void runtime_info_audio_jack_status_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONF_AUDIO_JACK_STATUS, 2);
}


int runtime_info_sliding_keyboard_opened_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_SLIDING_KEYBOARD_STATUS, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	switch (vconf_value) {
	case VCONFKEY_SYSMAN_SLIDING_KEYBOARD_NOT_AVAILABE:
		value->b = false;
		break;

	case VCONFKEY_SYSMAN_SLIDING_KEYBOAED_AVAILABLE:
		value->b = true;
		break;

	case VCONFKEY_SYSMAN_SLIDING_KEYBOARD_NOT_SUPPORTED:
		value->b = false;
		break;

	default:
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_sliding_keyboard_opened_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONF_SLIDING_KEYBOARD_STATUS, RUNTIME_INFO_KEY_SLIDING_KEYBOARD_OPENED, 0);
}

void runtime_info_sliding_keyboard_opened_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONF_SLIDING_KEYBOARD_STATUS, 0);
}


int runtime_info_usb_connected_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_USB_CONNECTED, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	switch (vconf_value) {
	case VCONFKEY_SYSMAN_USB_DISCONNECTED:
		value->b = false;
		break;

	case VCONFKEY_SYSMAN_USB_CONNECTED:
		value->b = false;
		break;

	case VCONFKEY_SYSMAN_USB_AVAILABLE:
		value->b = true;
		break;

	default:
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_usb_connected_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONF_USB_CONNECTED, RUNTIME_INFO_KEY_USB_CONNECTED, 0);
}

void runtime_info_usb_connected_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONF_USB_CONNECTED, 0);
}

int runtime_info_charger_connected_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_CHARGER_CONNECTED, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	switch (vconf_value) {
	case VCONFKEY_SYSMAN_CHARGER_DISCONNECTED:
		value->b = false;
		break;

	case VCONFKEY_SYSMAN_CHARGER_CONNECTED:
		value->b = true;
		break;

	default:
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_charger_connected_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONF_CHARGER_CONNECTED, RUNTIME_INFO_KEY_CHARGER_CONNECTED, 0);
}

void runtime_info_charger_connected_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONF_CHARGER_CONNECTED, 0);
}


int runtime_info_vibration_level_haptic_feedback_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONFKEY_SETAPPL_TOUCH_FEEDBACK_VIBRATION_LEVEL_INT, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

		value->i = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_vibration_level_haptic_feedback_set_event_cb(void)
{
	return runtime_info_vconf_set_event_cb(VCONFKEY_SETAPPL_TOUCH_FEEDBACK_VIBRATION_LEVEL_INT, RUNTIME_INFO_KEY_VIBRATION_LEVEL_HAPTIC_FEEDBACK, 0);
}

void runtime_info_vibration_level_haptic_feedback_unset_event_cb(void)
{
	runtime_info_vconf_unset_event_cb(VCONFKEY_SETAPPL_TOUCH_FEEDBACK_VIBRATION_LEVEL_INT, 0);
}


