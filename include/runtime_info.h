/*
 * Copyright (c) 2011 - 2015 Samsung Electronics Co., Ltd All Rights Reserved
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

#ifndef __TIZEN_SYSTEM_RUNTIME_INFO_H__
#define __TIZEN_SYSTEM_RUNTIME_INFO_H__

#include <tizen.h>

#ifdef __cplusplus
extern "C"
{
#endif

 /**
 * @addtogroup CAPI_SYSTEM_RUNTIME_INFO_MODULE
 * @{
 */

/**
 * @brief Enumeration for error codes for runtime information.
 */
typedef enum {
	RUNTIME_INFO_ERROR_NONE = TIZEN_ERROR_NONE,				/**< Successful */
	RUNTIME_INFO_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER,	/**< Invalid parameter */
	RUNTIME_INFO_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY,		/**< Out of memory */
	RUNTIME_INFO_ERROR_IO_ERROR = TIZEN_ERROR_IO_ERROR,			/**< An input/output error occurred when read value from system */
	RUNTIME_INFO_ERROR_REMOTE_IO = TIZEN_ERROR_REMOTE_IO,			/**< Remote I/O error occured */
	RUNTIME_INFO_ERROR_PERMISSION_DENIED = TIZEN_ERROR_PERMISSION_DENIED,	/**< No permission to use the api */
	RUNTIME_INFO_ERROR_NOT_SUPPORTED = TIZEN_ERROR_NOT_SUPPORTED,			/**< Not supported parameter @if MOBILE (Since 2.3.1) @endif */
} runtime_info_error_e;

/**
 * @brief Enumeration for keys for runtime information..
 */
typedef enum {
	RUNTIME_INFO_KEY_FLIGHT_MODE_ENABLED,					/**<@internal Indicates whether the device is in flight mode. */
	RUNTIME_INFO_KEY_WIFI_STATUS,							/**<@internal Indicates the current status of Wi-Fi. */
	RUNTIME_INFO_KEY_BLUETOOTH_ENABLED,						/**<Indicates whether Bluetooth is enabled. */
	RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED,					/**<Indicates whether Wi-Fi hotspot is enabled. */
	RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED,			/**<Indicates whether Bluetooth tethering is enabled. */
	RUNTIME_INFO_KEY_USB_TETHERING_ENABLED,					/**<Indicates whether USB tethering is enabled. */
	RUNTIME_INFO_KEY_LOCATION_SERVICE_ENABLED,				/**<Indicates whether the location service is allowed to use location data from GPS satellites. */
	RUNTIME_INFO_KEY_LOCATION_ADVANCED_GPS_ENABLED,			/**<@internal Indicates whether the location service is allowed to download location data for GPS operation. */
	RUNTIME_INFO_KEY_LOCATION_NETWORK_POSITION_ENABLED,		/**<Indicates whether the location service is allowed to use location data from cellular and Wi-Fi. */
	RUNTIME_INFO_KEY_PACKET_DATA_ENABLED,					/**<Indicates Whether the packet data through 3G network is enabled. */
	RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED,					/**<Indicates whether data roaming is enabled. */
	RUNTIME_INFO_KEY_SILENT_MODE_ENABLED,					/**<@internal Indicates whether the device is in silent mode. */
	RUNTIME_INFO_KEY_VIBRATION_ENABLED,						/**<Indicates whether vibration is enabled. */
	RUNTIME_INFO_KEY_24HOUR_CLOCK_FORMAT_ENABLED,			/**<@internal Indicates whether 24-hour clock is enabled. */
	RUNTIME_INFO_KEY_FIRST_DAY_OF_WEEK,						/**<@internal Indicates the first day of week. */
	RUNTIME_INFO_KEY_LANGUAGE,								/**<@internal Indicates the current language setting. */
	RUNTIME_INFO_KEY_REGION,								/**<@internal Indicates the current region setting. */
	RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED,					/**<Indicates whether audio jack is connected. */
	RUNTIME_INFO_KEY_GPS_STATUS,							/**<Indicates the current status of GPS. */
	RUNTIME_INFO_KEY_BATTERY_IS_CHARGING,					/**<Indicates the battery is currently charging. */
	RUNTIME_INFO_KEY_TV_OUT_CONNECTED,						/**<Indicates whether TV out is connected. */
	RUNTIME_INFO_KEY_AUDIO_JACK_STATUS,						/**<Indicates the current status of audio jack. */
	RUNTIME_INFO_KEY_SLIDING_KEYBOARD_OPENED,				/**<@internal Indicates whether sliding keyboard is opened. */
	RUNTIME_INFO_KEY_USB_CONNECTED,							/**<Indicates whether USB is connected. */
	RUNTIME_INFO_KEY_CHARGER_CONNECTED,						/**<Indicates whether charger is connected. */
	RUNTIME_INFO_KEY_VIBRATION_LEVEL_HAPTIC_FEEDBACK,		/**<@internal Indicates the current vibration level of haptic feedback. */
	RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED,					/**<Indicates whether auto rotation is enabled. */
} runtime_info_key_e;


/**
 * @brief Enumeration for Wi-Fi status.
 */
typedef enum {
	RUNTIME_INFO_WIFI_STATUS_DISABLED,				/**< GPS is disabled. */
	RUNTIME_INFO_WIFI_STATUS_UNCONNECTED,			/**< Wi-Fi is enabled and network connection is not established. */
	RUNTIME_INFO_WIFI_STATUS_CONNECTED,				/**< Network connection is established in Wi-Fi network. */
} runtime_info_wifi_status_e;

/**
 * @brief Enumeration for GPS status.
 */
typedef enum {
	RUNTIME_INFO_GPS_STATUS_DISABLED,				/**< GPS is disabled. */
	RUNTIME_INFO_GPS_STATUS_SEARCHING,				/**< GPS is searching for satellites. */
	RUNTIME_INFO_GPS_STATUS_CONNECTED,				/**< GPS connection is established. */
} runtime_info_gps_status_e;

/**
 * @internal
 * @brief Enumeration for first day of week.
 */
typedef enum {
	RUNTIME_INFO_FIRST_DAY_OF_WEEK_SUNDAY,			/**< Sunday */
	RUNTIME_INFO_FIRST_DAY_OF_WEEK_MONDAY,			/**< Monday */
	RUNTIME_INFO_FIRST_DAY_OF_WEEK_TUESDAY,			/**< Tuesday */
	RUNTIME_INFO_FIRST_DAY_OF_WEEK_WEDNESDAY,		/**< Wednesday */
	RUNTIME_INFO_FIRST_DAY_OF_WEEK_THURSDAY,		/**< Thursday */
	RUNTIME_INFO_FIRST_DAY_OF_WEEK_FRIDAY,			/**< Friday */
	RUNTIME_INFO_FIRST_DAY_OF_WEEK_SATURDAY,		/**< Saturday */
} runtime_info_first_day_of_week_e;

/**
 * @brief Enumeration for audio jack status.
 */
typedef enum {
	RUNTIME_INFO_AUDIO_JACK_STATUS_UNCONNECTED,		/**< Audio jack is not connected */
	RUNTIME_INFO_AUDIO_JACK_STATUS_CONNECTED_3WIRE,	/**< 3-conductor wire is connected. */
	RUNTIME_INFO_AUDIO_JACK_STATUS_CONNECTED_4WIRE,	/**< 4-conductor wire is connected. */
} runtime_info_audio_jack_status_e;


/**
 * @brief   Called when the runtime information changes
 * @since_tizen 2.3
 *
 * @param[in] key       The type of notification
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @pre runtime_info_set_changed_cb() will invoke this callback function.
 *
 * @see runtime_info_set_changed_cb()
 * @see runtime_info_unset_changed_cb()
 */
typedef void (*runtime_info_changed_cb)(runtime_info_key_e key, void *user_data);

/**
 * @brief   Gets the integer value of the runtime information.
 * @details This function gets current state of the given key which represents specific runtime information.
 *
 * @since_tizen 2.3
 *
 * @param[in]  key   The runtime information status key from which data should be read
 * @param[out] value The current value of the given key
 *
 * @return  @c 0 on success,
 *          otherwise a negative error value
 *
 * @retval  #RUNTIME_INFO_ERROR_NONE              Successful
 * @retval  #RUNTIME_INFO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #RUNTIME_INFO_ERROR_IO_ERROR          An input/output error occurred when read value from system
 * @retval  #RUNTIME_INFO_ERROR_PERMISSION_DENIED No permission to use the api
 * @retval  #RUNTIME_INFO_ERROR_NOT_SUPPORTED     Not supported parameter @if MOBILE (Since 2.3.1) @endif
 */
int runtime_info_get_value_int(runtime_info_key_e key, int *value);

/**
 * @brief   Gets the boolean value from the runtime information.
 * @details This function gets current state of the given key which represents specific runtime information.
 *
 * @since_tizen 2.3
 *
 * @param[in]  key   The runtime information key from which data should be read
 * @param[out] value The current value of the given key
 *
 * @return  @c 0 on success,
 *          otherwise a negative error value
 *
 * @retval  #RUNTIME_INFO_ERROR_NONE              Successful
 * @retval  #RUNTIME_INFO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #RUNTIME_INFO_ERROR_IO_ERROR          An input/output error occurred when read value from system
 * @retval  #RUNTIME_INFO_ERROR_PERMISSION_DENIED No permission to use the api
 * @retval  #RUNTIME_INFO_ERROR_NOT_SUPPORTED     Not supported parameter @if MOBILE (Since 2.3.1) @endif
 */
int runtime_info_get_value_bool(runtime_info_key_e key, bool *value);

/**
 * @brief   Gets the double value from the runtime information.
 * @details This function gets current state of the given key which represents specific runtime information.
 *
 * @since_tizen 2.3
 *
 * @param[in]  key   The runtime information key from which data should be read
 * @param[out] value The current value of the given key
 *
 * @return  @c 0 on success,
 *          otherwise a negative error value
 *
 * @retval  #RUNTIME_INFO_ERROR_NONE              Successful
 * @retval  #RUNTIME_INFO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #RUNTIME_INFO_ERROR_IO_ERROR          An input/output error occurred when read value from system
 * @retval  #RUNTIME_INFO_ERROR_PERMISSION_DENIED No permission to use the api
 * @retval  #RUNTIME_INFO_ERROR_NOT_SUPPORTED     Not supported parameter @if MOBILE (Since 2.3.1) @endif
 */
int runtime_info_get_value_double(runtime_info_key_e key, double *value);

/**
 * @brief   Gets the string value for specified runtime information.
 * @details This function gets current state of the given key which represents specific runtime information.
 *
 * @since_tizen 2.3
 *
 * @remarks  You must release @a value using free().
 *
 * @param[in]  key   The runtime information key from which data should be read
 * @param[out] value The current value of the given key
 *
 * @return  @c 0 on success,
 *          otherwise a negative error value
 *
 * @retval  #RUNTIME_INFO_ERROR_NONE              Successful
 * @retval  #RUNTIME_INFO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #RUNTIME_INFO_ERROR_IO_ERROR          An input/output error occurred when read value from system
 * @retval  #RUNTIME_INFO_ERROR_OUT_OF_MEMORY     Out of memory
 * @retval  #RUNTIME_INFO_ERROR_PERMISSION_DENIED No permission to use the api
 * @retval  #RUNTIME_INFO_ERROR_NOT_SUPPORTED     Not supported parameter @if MOBILE (Since 2.3.1) @endif
 */
int runtime_info_get_value_string(runtime_info_key_e key, char **value);


/**
 * @brief   Registers a change event callback for given runtime information key.
 * @since_tizen 2.3
 *
 * @param[in] key       The runtime information type
 * @param[in] callback  The callback function to invoke
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return  @c 0 on success,
 *          otherwise a negative error value
 *
 * @retval  #RUNTIME_INFO_ERROR_NONE              Successful
 * @retval  #RUNTIME_INFO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #RUNTIME_INFO_ERROR_PERMISSION_DENIED No permission to use the api
 * @retval  #RUNTIME_INFO_ERROR_NOT_SUPPORTED     Not supported parameter @if MOBILE (Since 2.3.1) @endif
 * @post runtime_info_changed_cb() will be invoked.
 *
 * @see runtime_info_unset_changed_cb()
 * @see runtime_info_changed_cb()
*/
int runtime_info_set_changed_cb(runtime_info_key_e key, runtime_info_changed_cb callback, void *user_data);


/**
 * @brief   Unregisters the callback function.
 * @since_tizen 2.3
 *
 * @param[in] key The runtime information type
 *
 * @return  @c 0 on success,
 *          otherwise a negative error value
 *
 * @retval  #RUNTIME_INFO_ERROR_NONE              Successful
 * @retval  #RUNTIME_INFO_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see runtime_info_set_changed_cb()
 */
int runtime_info_unset_changed_cb(runtime_info_key_e key);

/**
 * @brief Structure for memory information.
 * @since_tizen 2.4
 */
typedef struct {
	int total;  /**< Total memory (KiB) */
	int used;   /**< Used memory (KiB) */
	int free;   /**< Free memory (KiB) */
	int cache;  /**< Cache memory (KiB) */
	int swap;   /**< Swap memory (KiB) */
} runtime_memory_info_s;

/**
 * @brief   Gets system memory information
 * @since_tizen 2.4
 *
 * @param[out] info The system memory information structure
 *
 * @return  @c 0 on success,
 *          otherwise a negative error value
 *
 * @retval  #RUNTIME_INFO_ERROR_NONE              Successful
 * @retval  #RUNTIME_INFO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #RUNTIME_INFO_ERROR_IO_ERROR          An Input/Output error occured while reading from system
 *
 * @see runtime_info_get_process_memory_info()
 */
int runtime_info_get_system_memory_info(runtime_memory_info_s *info);

/**
 * @brief Structure for memory information per processes.
 * @since_tizen 2.4
 */
typedef struct {
	int vsz;            /**< Virtual memory size (KiB) */
	int rss;            /**< Resident set size (KiB) */
	int pss;            /**< Proportional set size (KiB) */
	int shared_clean;   /**< Not modified and mapped by other processes (KiB) */
	int shared_dirty;   /**< Modified and mapped by other processes (KiB) */
	int private_clean;  /**< Not modified and available only to that process (KiB) */
	int private_dirty;  /**< Modified and available only to that process (KiB) */
} process_memory_info_s;

/**
 * @brief   Gets memory information per processes
 * @since_tizen 2.4
 * @privlevel public
 * @privilege %http://tizen.org/privilege/systemmonitor
 *
 * @remarks You must release @a s value using free(). \n
 *          The size of @a s is the same with @a size.
 *
 * @param[in]  pid The process unique id array
 * @param[in]  size The size of pid array
 * @param[out] info The memory information structure array of the processes
 *
 * @return  @c 0 on success,
 *          otherwise a negative error value
 *
 * @retval  #RUNTIME_INFO_ERROR_NONE              Successful
 * @retval  #RUNTIME_INFO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #RUNTIME_INFO_ERROR_OUT_OF_MEMORY	  Not able to allocate memory (for output param/other operations)
 * @retval  #RUNTIME_INFO_ERROR_REMOTE_IO	  Call to resource daemon failed (dbus errors/resource daemon errors)
 * @retval  #RUNTIME_INFO_ERROR_IO_ERROR	  An I/O error during dbus message operations
 * @retval  #RUNTIME_INFO_PERMISSION_DENIED	  Process not authorized to request process usage info
 *
 * @see runtime_info_get_system_memory_info()
 */
int runtime_info_get_process_memory_info(int *pid, int size, process_memory_info_s **info);

/**
 * @brief Structure for cpu usage.
 * @since_tizen 2.4
 */
typedef struct {
	double user;   /**< Time running un-niced user processes (Percent) */
	double system; /**< Time running kernel processes (Percent) */
	double nice;   /**< Time running niced user processes (Percent) */
	double iowait; /**< Time waiting for I/O completion (Percent) */
} runtime_cpu_usage_s;

/**
 * @brief   Gets cpu information
 * @since_tizen 2.4
 *
 * @param[out] usage The cpu usage structure
 *
 * @return  @c 0 on success,
 *          otherwise a negative error value
 *
 * @retval  #RUNTIME_INFO_ERROR_NONE              Successful
 * @retval  #RUNTIME_INFO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #RUNTIME_INFO_ERROR_IO_ERROR          An input/output error occured while reading from system
 *
 * @see runtime_info_get_process_cpu_usage()
 */
int runtime_info_get_cpu_usage(runtime_cpu_usage_s *usage);

/**
 * @brief Structure for cpu usage per processes.
 * @since_tizen 2.4
 */
typedef struct {
	int utime;    /**< Amount of time that this process has been scheduled in user mode (clock ticks) */
	int stime;    /**< Amount of time that this process has been scheduled in kernel mode (clock ticks) */
} process_cpu_usage_s;

/**
 * @brief   Gets cpu usage per processes
 * @since_tizen 2.4
 * @privlevel public
 * @privilege %http://tizen.org/privilege/systemmonitor
 *
 * @remarks You must release @a s value using free(). \n
 *          The size of @a s is the same with @a size.
 *
 * @param[in]  pid The process unique id array
 * @param[in]  size The size of pid array
 * @param[out] usage The cpu usage structure array of the processes
 *
 * @return  @c 0 on success,
 *          otherwise a negative error value
 *
 * @retval  #RUNTIME_INFO_ERROR_NONE              Successful
 * @retval  #RUNTIME_INFO_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #RUNTIME_INFO_ERROR_OUT_OF_MEMORY	  Not able to allocate memory (for output param/other operations)
 * @retval  #RUNTIME_INFO_ERROR_REMOTE_IO	  Call to resource daemon failed (dbus errors/resource daemon errors)
 * @retval  #RUNTIME_INFO_ERROR_IO_ERROR	  An I/O error occured (during dbus message operations/other IO operations)
 * @retval  #RUNTIME_INFO_PERMISSION_DENIED	  Process not authorized to request process usage info
 *
 * @see runtime_info_get_cpu_usage()
 */
int runtime_info_get_process_cpu_usage(int *pid, int size, process_cpu_usage_s **usage);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_SYSTEM_RUNTIME_INFO_H__ */
