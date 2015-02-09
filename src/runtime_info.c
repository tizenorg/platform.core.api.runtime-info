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

#define RUNTIME_INFO_MAX -1

typedef struct {
	runtime_info_changed_cb changed_cb;
	void *user_data;
	runtime_info_value_h most_recent_value;
} runtime_info_event_subscription_s;

typedef runtime_info_event_subscription_s * runtime_info_event_subscription_h;

typedef struct {
	runtime_info_key_e key;
	runtime_info_data_type_e data_type;
	runtime_info_func_get_value get_value;
	runtime_info_func_set_event_cb set_event_cb;
	runtime_info_func_unset_event_cb unset_event_cb;
	runtime_info_event_subscription_h event_subscription;
} runtime_info_item_s;

typedef runtime_info_item_s * runtime_info_item_h;

runtime_info_item_s runtime_info_item_table[] = {

{
	RUNTIME_INFO_KEY_FLIGHT_MODE_ENABLED, /**<Indicates whether the device is in flight mode. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_flightmode_get_value,
	runtime_info_flightmode_set_event_cb,
	runtime_info_flightmode_unset_event_cb,
	NULL
},


{
	RUNTIME_INFO_KEY_WIFI_STATUS, /**<Indicates the current status of Wi-Fi. */
	RUNTIME_INFO_DATA_TYPE_INT,
	runtime_info_wifi_status_get_value,
	runtime_info_wifi_status_set_event_cb,
	runtime_info_wifi_status_unset_event_cb,
	NULL
},


{
	RUNTIME_INFO_KEY_BLUETOOTH_ENABLED, /**<Indicates whether Bluetooth is enabled. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_bt_enabled_get_value,
	runtime_info_bt_enabled_set_event_cb,
	runtime_info_bt_enabled_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED, /**<Indicates whether Wi-Fi hotspot is enabled. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_wifi_hotspot_get_value,
	runtime_info_wifi_hotspot_set_event_cb,
	runtime_info_wifi_hotspot_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED, /**<Indicates whether Bluetooth tethering is enabled. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_bt_hotspot_get_value,
	runtime_info_bt_hotspot_set_event_cb,
	runtime_info_bt_hotspot_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_USB_TETHERING_ENABLED, /**<Indicates whether USB tethering is enabled. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_usb_hotspot_get_value,
	runtime_info_usb_hotspot_set_event_cb,
	runtime_info_usb_hotspot_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_LOCATION_SERVICE_ENABLED, /**<Indicates whether the location service is allowed to use location data from GPS satellites. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_location_service_get_value,
	runtime_info_location_service_set_event_cb,
	runtime_info_location_service_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_LOCATION_ADVANCED_GPS_ENABLED, /**<Indicates whether the location service is allowed to download location data for GPS operation. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_location_agps_get_value,
	runtime_info_location_agps_set_event_cb,
	runtime_info_location_agps_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_LOCATION_NETWORK_POSITION_ENABLED, /**<Indicates whether the location service is allowed to use location data from cellular and Wi-Fi. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_location_network_get_value,
	runtime_info_location_network_set_event_cb,
	runtime_info_location_network_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_PACKET_DATA_ENABLED, /**<Indicates Whether the packet data through 3G network is enabled. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_packet_data_get_value,
	runtime_info_packet_data_set_event_cb,
	runtime_info_packet_data_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED, /**<Indicates whether data roaming is enabled. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_data_roaming_get_value,
	runtime_info_data_roaming_set_event_cb,
	runtime_info_data_roaming_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_SILENT_MODE_ENABLED, /**<Indicates whether the device is in silent mode. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_silent_mode_get_value,
	runtime_info_silent_mode_set_event_cb,
	runtime_info_silent_mode_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_VIBRATION_ENABLED, /**<Indicates whether vibration is enabled. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_vibration_enabled_get_value,
	runtime_info_vibration_enabled_set_event_cb,
	runtime_info_vibration_enabled_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_24HOUR_CLOCK_FORMAT_ENABLED, /**<Indicates the current time format. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_24hour_format_get_value,
	runtime_info_24hour_format_set_event_cb,
	runtime_info_24hour_format_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_FIRST_DAY_OF_WEEK, /**<Indicates the first day of week. */
	RUNTIME_INFO_DATA_TYPE_INT,
	runtime_info_first_day_of_week_get_value,
	runtime_info_first_day_of_week_set_event_cb,
	runtime_info_first_day_of_week_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_LANGUAGE, /**<Indicates the current language setting. */
	RUNTIME_INFO_DATA_TYPE_STRING,
	runtime_info_language_get_value,
	runtime_info_language_set_event_cb,
	runtime_info_language_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_REGION, /**<Indicates the current region setting. */
	RUNTIME_INFO_DATA_TYPE_STRING,
	runtime_info_region_get_value,
	runtime_info_region_set_event_cb,
	runtime_info_region_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED, /**<Indicates whether audio jack is connected. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_audiojack_get_value,
	runtime_info_audiojack_set_event_cb,
	runtime_info_audiojack_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_GPS_STATUS, /**<Indicates the current status of GPS. */
	RUNTIME_INFO_DATA_TYPE_INT,
	runtime_info_gps_status_get_value,
	runtime_info_gps_status_set_event_cb,
	runtime_info_gps_status_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_BATTERY_IS_CHARGING, /**<Indicates the battery is currently charging. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_battery_charging_get_value,
	runtime_info_battery_charging_set_event_cb,
	runtime_info_battery_charging_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_TV_OUT_CONNECTED, /**<Indicates whether TV out is connected. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_tvout_connected_get_value,
	runtime_info_tvout_connected_set_event_cb,
	runtime_info_tvout_connected_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_AUDIO_JACK_STATUS, /**<Indicates the current status of audio jack. */
	RUNTIME_INFO_DATA_TYPE_INT,
	runtime_info_audio_jack_status_get_value,
	runtime_info_audio_jack_status_set_event_cb,
	runtime_info_audio_jack_status_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_SLIDING_KEYBOARD_OPENED, /**<Indicates whether sliding keyboard is opened. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_sliding_keyboard_opened_get_value,
	runtime_info_sliding_keyboard_opened_set_event_cb,
	runtime_info_sliding_keyboard_opened_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_USB_CONNECTED, /**<Indicates whether usb is connected. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_usb_connected_get_value,
	runtime_info_usb_connected_set_event_cb,
	runtime_info_usb_connected_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_CHARGER_CONNECTED, /**<Indicates whether charger is connected. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_charger_connected_get_value,
	runtime_info_charger_connected_set_event_cb,
	runtime_info_charger_connected_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_VIBRATION_LEVEL_HAPTIC_FEEDBACK, /**<Indicates the current vibration level of haptic feedback. */
	RUNTIME_INFO_DATA_TYPE_INT,
	runtime_info_vibration_level_haptic_feedback_get_value,
	runtime_info_vibration_level_haptic_feedback_set_event_cb,
	runtime_info_vibration_level_haptic_feedback_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED, /**<Indicates whether auto rotation is enabled. */
	RUNTIME_INFO_DATA_TYPE_BOOL,
	runtime_info_auto_rotation_enabled_get_value,
	runtime_info_auto_rotation_enabled_set_event_cb,
	runtime_info_auto_rotation_enabled_unset_event_cb,
	NULL
},

{
	RUNTIME_INFO_MAX, RUNTIME_INFO_DATA_TYPE_INT, NULL, NULL, NULL, NULL
}

};

static int runtime_info_get_item(runtime_info_key_e key, runtime_info_item_h *runtime_info_item)
{
	int index = 0;

	while (runtime_info_item_table[index].key != RUNTIME_INFO_MAX) {
		if (runtime_info_item_table[index].key == key) {
			*runtime_info_item = &runtime_info_item_table[index];
			return 0;
		}

		index++;
	}

	return -1;
}

int runtime_info_get_value(runtime_info_key_e key, runtime_info_data_type_e data_type, runtime_info_value_h value)
{
	runtime_info_item_h runtime_info_item;
	runtime_info_func_get_value get_value;

	if (runtime_info_get_item(key, &runtime_info_item))	{
		LOGE("INVALID_PARAMETER(0x%08x) : invalid key", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	if (runtime_info_item->data_type != data_type) {
		LOGE("INVALID_PARAMETER(0x%08x) : invalid data type", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	get_value = runtime_info_item->get_value;

	if (get_value == NULL) {
		LOGE("IO_ERROR(0x%08x) : failed to call getter for the runtime information", RUNTIME_INFO_ERROR_IO_ERROR);
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	if (get_value(value) != RUNTIME_INFO_ERROR_NONE) {
		LOGE("IO_ERROR(0x%08x) : failed to get the runtime informaion / key(%d)", RUNTIME_INFO_ERROR_IO_ERROR, key);
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

API int runtime_info_get_value_int(runtime_info_key_e key, int *value)
{
	int retcode;
	runtime_info_value_u runtime_info_value;

	if (value == NULL) {
		LOGE("INVALID_PARAMETER(0x%08x) : invalid output param", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	retcode = runtime_info_get_value(key, RUNTIME_INFO_DATA_TYPE_INT, &runtime_info_value);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
		*value = runtime_info_value.i;

	return retcode;
}

API int runtime_info_get_value_bool(runtime_info_key_e key, bool *value)
{
	int retcode;
	runtime_info_value_u runtime_info_value;

	if (value == NULL) {
		LOGE("INVALID_PARAMETER(0x%08x) : invalid output param", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	retcode = runtime_info_get_value(key, RUNTIME_INFO_DATA_TYPE_BOOL, &runtime_info_value);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
		*value = runtime_info_value.b;

	return retcode;
}

API int runtime_info_get_value_double(runtime_info_key_e key, double *value)
{
	int retcode;
	runtime_info_value_u runtime_info_value;

	if (value == NULL) {
		LOGE("INVALID_PARAMETER(0x%08x) : invalid output param", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	retcode = runtime_info_get_value(key, RUNTIME_INFO_DATA_TYPE_DOUBLE, &runtime_info_value);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
		*value = runtime_info_value.d;

	return retcode;
}

API int runtime_info_get_value_string(runtime_info_key_e key, char **value)
{
	int retcode;
	runtime_info_value_u runtime_info_value;

	if (value == NULL) {
		LOGE("INVALID_PARAMETER(0x%08x) : invalid output param", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	retcode = runtime_info_get_value(key, RUNTIME_INFO_DATA_TYPE_STRING, &runtime_info_value);

	if (retcode == RUNTIME_INFO_ERROR_NONE)
		*value = runtime_info_value.s;

	return retcode;
}

API int runtime_info_set_changed_cb(runtime_info_key_e key, runtime_info_changed_cb callback, void *user_data)
{
	runtime_info_item_h runtime_info_item;
	runtime_info_func_set_event_cb set_event_cb;
	bool subscribe_event = false;

	if (callback == NULL) {
		LOGE("INVALID_PARAMETER(0x%08x)", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	if (runtime_info_get_item(key, &runtime_info_item))	{
		LOGE("INVALID_PARAMETER(0x%08x) : invalid key", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	set_event_cb = runtime_info_item->set_event_cb;

	if (set_event_cb == NULL) {
		LOGE("IO_ERROR(0x%08x) : failed to set callback for the runtime information", RUNTIME_INFO_ERROR_IO_ERROR);
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	if (runtime_info_item->event_subscription == NULL) {
		subscribe_event = true;

		runtime_info_event_subscription_h event_subscription;
		event_subscription = malloc(sizeof(runtime_info_event_subscription_s));

		if (event_subscription == NULL)	{
			LOGE("OUT_OF_MEMORY(0x%08x)", RUNTIME_INFO_ERROR_OUT_OF_MEMORY);
			return RUNTIME_INFO_ERROR_OUT_OF_MEMORY;
		}

		runtime_info_item->event_subscription = event_subscription;
		runtime_info_item->event_subscription->most_recent_value = NULL;
	}

	runtime_info_item->event_subscription->changed_cb = callback;
	runtime_info_item->event_subscription->user_data = user_data;

	if (runtime_info_item->event_subscription->most_recent_value != NULL)
		free(runtime_info_item->event_subscription->most_recent_value);

	runtime_info_item->event_subscription->most_recent_value = NULL;

	if (subscribe_event == true)
		return set_event_cb();
	else
		return RUNTIME_INFO_ERROR_NONE;
}

API int runtime_info_unset_changed_cb(runtime_info_key_e key)
{
	runtime_info_item_h runtime_info_item;
	runtime_info_func_unset_event_cb unset_event_cb;

	if (runtime_info_get_item(key, &runtime_info_item))	{
		LOGE("INVALID_PARAMETER(0x%08x) : invalid key", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return RUNTIME_INFO_ERROR_INVALID_PARAMETER;
	}

	if (runtime_info_item->event_subscription != NULL) {
		if (runtime_info_item->event_subscription->most_recent_value != NULL) {
			free(runtime_info_item->event_subscription->most_recent_value);
			runtime_info_item->event_subscription->most_recent_value = NULL;
		}

		free(runtime_info_item->event_subscription);
		runtime_info_item->event_subscription = NULL;
	}

	unset_event_cb = runtime_info_item->unset_event_cb;

	if (unset_event_cb == NULL)	{
		LOGE("IO_ERROR(0x%08x) : failed to unset callback for the runtime information", RUNTIME_INFO_ERROR_IO_ERROR);
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	unset_event_cb();

	return RUNTIME_INFO_ERROR_NONE;
}

void runtime_info_updated(runtime_info_key_e key)
{
	runtime_info_item_h runtime_info_item;
	runtime_info_value_u current_value;
	bool dispatch_event = true;
	int retcode;

	if (runtime_info_get_item(key, &runtime_info_item))	{
		LOGE("INVALID_PARAMETER(0x%08x) : invalid key", RUNTIME_INFO_ERROR_INVALID_PARAMETER);
		return;
	}

	if (runtime_info_item->event_subscription == NULL) {
		LOGE("IO_ERROR(0x%08x) : invalid event subscription", RUNTIME_INFO_ERROR_IO_ERROR);
		return;
	}

	memset(&current_value, 0, sizeof(runtime_info_value_u));

	retcode = runtime_info_get_value(key, runtime_info_item->data_type, &current_value);

	if (retcode != RUNTIME_INFO_ERROR_NONE)	{
		LOGE("IO_ERROR(0x%08x) : failed to get the runtime information", RUNTIME_INFO_ERROR_IO_ERROR);
		return;
	}

	if (runtime_info_item->event_subscription->most_recent_value != NULL) {
		if (!memcmp(runtime_info_item->event_subscription->most_recent_value, &current_value, sizeof(runtime_info_value_u)))
			dispatch_event = false;
	} else {
		runtime_info_item->event_subscription->most_recent_value = calloc(1, sizeof(runtime_info_value_u));

		if (runtime_info_item->event_subscription->most_recent_value == NULL) {
			LOGE("OUT_OF_MEMORY(0x%08x)", RUNTIME_INFO_ERROR_OUT_OF_MEMORY);
			return;
		}
	}

	if (dispatch_event == true && runtime_info_item->event_subscription->changed_cb != NULL) {
		memcpy(runtime_info_item->event_subscription->most_recent_value, &current_value, sizeof(runtime_info_value_u));
		runtime_info_item->event_subscription->changed_cb(key, runtime_info_item->event_subscription->user_data);
	}
}
