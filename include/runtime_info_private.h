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


#ifndef __TIZEN_SYSTEM_RUNTIME_INFO_PRIVATE_H__
#define __TIZEN_SYSTEM_RUNTIME_INFO_PRIVATE_H__

#include <vconf.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef API
#define API __attribute__ ((visibility("default")))
#endif

typedef enum {
	RUNTIME_INFO_DATA_TYPE_STRING,
	RUNTIME_INFO_DATA_TYPE_INT,
	RUNTIME_INFO_DATA_TYPE_DOUBLE,
	RUNTIME_INFO_DATA_TYPE_BOOL
} runtime_info_data_type_e;

typedef union {
	int i;
	bool b;
	double d;
	char *s;
} runtime_info_value_u;

typedef runtime_info_value_u * runtime_info_value_h;

typedef int (*runtime_info_func_get_value) (runtime_info_value_h value);
typedef int (*runtime_info_func_set_event_cb) (void);
typedef void (*runtime_info_func_unset_event_cb) (void);

void runtime_info_updated(runtime_info_key_e key);

int runtime_info_vconf_get_value_int(const char *vconf_key, int *value);
int runtime_info_vconf_get_value_bool(const char *vconf_key, int *value);
int runtime_info_vconf_get_value_double(const char *vconf_key, double *value);
int runtime_info_vconf_get_value_string(const char *vconf_key, char **value);

int runtime_info_vconf_set_event_cb(const char *vconf_key, runtime_info_key_e runtime_info_key, int slot);
void runtime_info_vconf_unset_event_cb(const char *vconf_key, int slot);

int runtime_info_flightmode_get_value(runtime_info_value_h);
int runtime_info_flightmode_set_event_cb(void);
void runtime_info_flightmode_unset_event_cb(void);

int runtime_info_audiojack_get_value(runtime_info_value_h);
int runtime_info_audiojack_set_event_cb(void);
void runtime_info_audiojack_unset_event_cb(void);

int runtime_info_wifi_status_get_value(runtime_info_value_h);
int runtime_info_wifi_status_set_event_cb(void);
void runtime_info_wifi_status_unset_event_cb(void);

int runtime_info_bt_enabled_get_value(runtime_info_value_h);
int runtime_info_bt_enabled_set_event_cb(void);
void runtime_info_bt_enabled_unset_event_cb(void);

int runtime_info_wifi_hotspot_get_value(runtime_info_value_h);
int runtime_info_wifi_hotspot_set_event_cb(void);
void runtime_info_wifi_hotspot_unset_event_cb (void);

int runtime_info_bt_hotspot_get_value(runtime_info_value_h);
int runtime_info_bt_hotspot_set_event_cb(void);
void runtime_info_bt_hotspot_unset_event_cb(void);

int runtime_info_usb_hotspot_get_value(runtime_info_value_h);
int runtime_info_usb_hotspot_set_event_cb(void);
void runtime_info_usb_hotspot_unset_event_cb(void);

int runtime_info_location_service_get_value(runtime_info_value_h);
int runtime_info_location_service_set_event_cb(void);
void runtime_info_location_service_unset_event_cb(void);

int runtime_info_location_agps_get_value(runtime_info_value_h);
int runtime_info_location_agps_set_event_cb(void);
void runtime_info_location_agps_unset_event_cb(void);

int runtime_info_location_network_get_value(runtime_info_value_h);
int runtime_info_location_network_set_event_cb(void);
void runtime_info_location_network_unset_event_cb(void);

int runtime_info_packet_data_get_value(runtime_info_value_h);
int runtime_info_packet_data_set_event_cb(void);
void runtime_info_packet_data_unset_event_cb(void);

int runtime_info_data_roaming_get_value(runtime_info_value_h);
int runtime_info_data_roaming_set_event_cb(void);
void runtime_info_data_roaming_unset_event_cb(void);

int runtime_info_silent_mode_get_value(runtime_info_value_h);
int runtime_info_silent_mode_set_event_cb(void);
void runtime_info_silent_mode_unset_event_cb(void);

int runtime_info_vibration_enabled_get_value(runtime_info_value_h);
int runtime_info_vibration_enabled_set_event_cb(void);
void runtime_info_vibration_enabled_unset_event_cb(void);

int runtime_info_24hour_format_get_value(runtime_info_value_h);
int runtime_info_24hour_format_set_event_cb(void);
void runtime_info_24hour_format_unset_event_cb(void);

int runtime_info_first_day_of_week_get_value(runtime_info_value_h);
int runtime_info_first_day_of_week_set_event_cb(void);
void runtime_info_first_day_of_week_unset_event_cb(void);

int runtime_info_language_get_value(runtime_info_value_h);
int runtime_info_language_set_event_cb(void);
void runtime_info_language_unset_event_cb(void);

int runtime_info_region_get_value(runtime_info_value_h);
int runtime_info_region_set_event_cb(void);
void runtime_info_region_unset_event_cb(void);

int runtime_info_gps_status_get_value(runtime_info_value_h);
int runtime_info_gps_status_set_event_cb(void);
void runtime_info_gps_status_unset_event_cb(void);

int runtime_info_battery_charging_get_value(runtime_info_value_h);
int runtime_info_battery_charging_set_event_cb(void);
void runtime_info_battery_charging_unset_event_cb(void);

int runtime_info_tvout_connected_get_value(runtime_info_value_h value);
int runtime_info_tvout_connected_set_event_cb(void);
void runtime_info_tvout_connected_unset_event_cb(void);

int runtime_info_audio_jack_status_get_value (runtime_info_value_h value);
int runtime_info_audio_jack_status_set_event_cb(void);
void runtime_info_audio_jack_status_unset_event_cb(void);

int runtime_info_sliding_keyboard_opened_get_value(runtime_info_value_h value);
int runtime_info_sliding_keyboard_opened_set_event_cb(void);
void runtime_info_sliding_keyboard_opened_unset_event_cb(void);

int runtime_info_usb_connected_get_value(runtime_info_value_h value);
int runtime_info_usb_connected_set_event_cb(void);
void runtime_info_usb_connected_unset_event_cb(void);

int runtime_info_charger_connected_get_value(runtime_info_value_h value);
int runtime_info_charger_connected_set_event_cb(void);
void runtime_info_charger_connected_unset_event_cb(void);

int runtime_info_vibration_level_haptic_feedback_get_value(runtime_info_value_h value);
int runtime_info_vibration_level_haptic_feedback_set_event_cb(void);
void runtime_info_vibration_level_haptic_feedback_unset_event_cb(void);

int runtime_info_auto_rotation_enabled_get_value(runtime_info_value_h);
int runtime_info_auto_rotation_enabled_set_event_cb(void);
void runtime_info_auto_rotation_enabled_unset_event_cb(void);

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_SYSTEM_RUNTIME_INFO_PRIVATE_H__ */
