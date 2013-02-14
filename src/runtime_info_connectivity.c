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

static const char *VCONF_WIFI_STATUS = VCONFKEY_WIFI_STATE;
static const char *VCONF_BT_ENABLED = VCONFKEY_BT_STATUS;
static const char *VCONF_WIFI_HOTSPOT_ENABLED = VCONFKEY_MOBILE_HOTSPOT_MODE;
static const char *VCONF_BT_HOTSPOT_ENABLED = VCONFKEY_MOBILE_HOTSPOT_MODE;
static const char *VCONF_USB_HOTSPOT_ENABLED = VCONFKEY_MOBILE_HOTSPOT_MODE;
static const char *VCONF_PACKET_DATA_ENABLED = VCONFKEY_3G_ENABLE;
static const char *VCONF_DATA_ROAMING_ENABLED = "db/setting/data_roaming";
static const char *VCONF_GPS_STATUS = VCONFKEY_LOCATION_GPS_STATE;

int runtime_info_wifi_status_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_WIFI_STATUS, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	switch (vconf_value) {
	case VCONFKEY_WIFI_OFF:
		value->i = RUNTIME_INFO_WIFI_STATUS_DISABLED;
		break;

	case VCONFKEY_WIFI_UNCONNECTED:
		value->i = RUNTIME_INFO_WIFI_STATUS_UNCONNECTED;
		break;

	case VCONFKEY_WIFI_CONNECTED:
	case VCONFKEY_WIFI_TRANSFER:
		value->i = RUNTIME_INFO_WIFI_STATUS_CONNECTED;
		break;

	default:
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_wifi_status_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_WIFI_STATUS, RUNTIME_INFO_KEY_WIFI_STATUS, 0);
}

void runtime_info_wifi_status_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_WIFI_STATUS, 0);
}

int runtime_info_bt_enabled_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_BT_ENABLED, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	switch (vconf_value) {
	case VCONFKEY_BT_STATUS_OFF:
		value->b = false;
		break;

	case VCONFKEY_BT_STATUS_ON:
	case VCONFKEY_BT_STATUS_BT_VISIBLE:
	case VCONFKEY_BT_STATUS_TRANSFER:
		value->b = true;
		break;

	default:
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_bt_enabled_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_BT_ENABLED, RUNTIME_INFO_KEY_BLUETOOTH_ENABLED, 0);
}

void runtime_info_bt_enabled_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_BT_ENABLED, 0);
}


int runtime_info_wifi_hotspot_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_WIFI_HOTSPOT_ENABLED, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	value->b = (vconf_value&VCONFKEY_MOBILE_HOTSPOT_MODE_WIFI) ? true : false;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_wifi_hotspot_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_WIFI_HOTSPOT_ENABLED, RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED, 0);
}

void runtime_info_wifi_hotspot_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_WIFI_HOTSPOT_ENABLED, 0);
}

int runtime_info_bt_hotspot_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_BT_HOTSPOT_ENABLED, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	value->b = (vconf_value&VCONFKEY_MOBILE_HOTSPOT_MODE_BT) ? true : false;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_bt_hotspot_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_BT_HOTSPOT_ENABLED, RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED, 0);
}

void runtime_info_bt_hotspot_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_BT_HOTSPOT_ENABLED, 0);
}

int runtime_info_usb_hotspot_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_USB_HOTSPOT_ENABLED, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	value->b = (vconf_value&VCONFKEY_MOBILE_HOTSPOT_MODE_USB) ? true : false;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_usb_hotspot_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_USB_HOTSPOT_ENABLED, RUNTIME_INFO_KEY_USB_TETHERING_ENABLED, 0);
}

void runtime_info_usb_hotspot_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_USB_HOTSPOT_ENABLED, 0);
}

int runtime_info_packet_data_get_value(runtime_info_value_h value)
{
	bool vconf_value;

	if (runtime_info_vconf_get_value_bool(VCONF_PACKET_DATA_ENABLED, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_packet_data_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_PACKET_DATA_ENABLED, RUNTIME_INFO_KEY_PACKET_DATA_ENABLED, 0);
}

void runtime_info_packet_data_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_PACKET_DATA_ENABLED, 0);
}

int runtime_info_data_roaming_get_value(runtime_info_value_h value)
{
	bool vconf_value;

	if (runtime_info_vconf_get_value_bool(VCONF_DATA_ROAMING_ENABLED, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	value->b = vconf_value;

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_data_roaming_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_DATA_ROAMING_ENABLED, RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED, 0);
}

void runtime_info_data_roaming_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_DATA_ROAMING_ENABLED, 0);
}

int runtime_info_gps_status_get_value(runtime_info_value_h value)
{
	int vconf_value;

	if (runtime_info_vconf_get_value_int(VCONF_GPS_STATUS, &vconf_value))
		return RUNTIME_INFO_ERROR_IO_ERROR;

	switch (vconf_value) {
	case VCONFKEY_LOCATION_GPS_OFF:
		value->i = RUNTIME_INFO_GPS_STATUS_DISABLED;
		break;

	case VCONFKEY_LOCATION_GPS_SEARCHING:
		value->i = RUNTIME_INFO_GPS_STATUS_SEARCHING;
		break;

	case VCONFKEY_LOCATION_GPS_CONNECTED:
		value->i = RUNTIME_INFO_GPS_STATUS_CONNECTED;
		break;

	default:
		return RUNTIME_INFO_ERROR_IO_ERROR;
	}

	return RUNTIME_INFO_ERROR_NONE;
}

int runtime_info_gps_status_set_event_cb()
{
	return runtime_info_vconf_set_event_cb(VCONF_GPS_STATUS, RUNTIME_INFO_KEY_GPS_STATUS, 0);
}

void runtime_info_gps_status_unset_event_cb()
{
	runtime_info_vconf_unset_event_cb(VCONF_GPS_STATUS, 0);
}

