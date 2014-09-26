
/*  ev3.i was generated by yup.py (yupp) 0.7b6
    out of ev3.yu-i at 2014-09-26 15:50
 *//**
 *  \file  ev3.i (ev3.yu-i)
 *  \brief  SWIG interface file.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

%module ev3
%include "cstring.i"
%include "stdint.i"

%{
#include "../source/ev3/ev3.h"
#include "../source/ev3/ev3_led.h"
#include "../source/ev3/ev3_light.h"
#include "../source/ev3/ev3_sensor.h"
#include "../source/ev3/ev3_tacho.h"
%}

/* Unfortunately incompatible with %typemap( default ) size_t sz { $1 = DEFAULT_BUF_SIZE; } */
%cstring_output_maxsize( char *buf, size_t sz );

%apply bool *OUTPUT { bool *buf };
%apply int *OUTPUT { int *buf };
%apply uint8_t *OUTPUT { uint8_t *buf };
%apply uint8_t *OUTPUT { byte *buf };
%apply uint32_t *OUTPUT { uint32_t *buf };
%apply uint32_t *OUTPUT { dword *buf };
%apply float *OUTPUT { float *buf };

%apply uint32_t { dword };

/*
 *  ev3
 */

#define EV3_NONE  -1

%include "./platform.h"

// CLIENT ////////////////////////////////////////
#if EV3_BRICK == 0

%rename( brick_addr ) ev3_brick_addr;
extern char *ev3_brick_addr;
%rename( brick_port ) ev3_brick_port;
extern uint16_t ev3_brick_port;

//////////////////////////////////////////////////
#endif

extern int ev3_init( void );
extern void ev3_uninit( void );

extern size_t ev3_write_binary( const char *fn, char *STRING, size_t LENGTH );
extern size_t ev3_write( const char *fn, char *value );
extern size_t ev3_write_bool( const char *fn, bool value );
extern size_t ev3_write_int( const char *fn, int value );
extern size_t ev3_write_dword( const char *fn, uint32_t value );
extern size_t ev3_write_float( const char *fn, float value );

extern size_t ev3_read_binary( const char *fn, char *buf, size_t sz );
extern size_t ev3_read( const char *fn, char *buf, size_t sz );
extern size_t ev3_read_bool( const char *fn, bool *buf );
extern size_t ev3_read_int( const char *fn, int *buf );
extern size_t ev3_read_dword( const char *fn, uint32_t *buf );
extern size_t ev3_read_float( const char *fn, float *buf );

extern size_t ev3_listdir( const char *fn, char *buf, size_t sz );
extern bool ev3_poweroff( void );

/*
 *  ev3_led
 */

enum {
	EV3_GREEN_LEFT,
	EV3_GREEN_RIGHT,
	EV3_RED_LEFT,
	EV3_RED_RIGHT,

	LED__COUNT_
};

enum {
	TRIGGER_NONE,
	TRIGGER_MMC0,
	TRIGGER_TIMER,
	TRIGGER_HEARTBEAT,
	TRIGGER_DEFAULT_ON,
	TRIGGER_LEGOEV3_BATTERY_CHARGING_OR_FULL,
	TRIGGER_LEGOEV3_BATTERY_CHARGING,
	TRIGGER_LEGOEV3_BATTERY_FULL,
	TRIGGER_LEGOEV3_BATTERY_CHARGING_BLINK_FULL_SOLID,
	TRIGGER_PHY0RX,
	TRIGGER_PHY0TX,
	TRIGGER_PHY0ASSOC,
	TRIGGER_PHY0RADIO,
	TRIGGER_PHY0TPT,

	TRIGGER__COUNT_
};

extern size_t get_led_brightness( uint8_t id, int *buf );
extern size_t set_led_brightness( uint8_t id, int value );
extern size_t get_led_delay_off( uint8_t id, int *buf );
extern size_t set_led_delay_off( uint8_t id, int value );
extern size_t get_led_delay_on( uint8_t id, int *buf );
extern size_t set_led_delay_on( uint8_t id, int value );
extern size_t get_led_trigger( uint8_t id, char *buf, size_t sz );
extern size_t set_led_trigger( uint8_t id, char *value );

extern uint8_t get_led_trigger_inx( uint8_t id );
extern size_t set_led_trigger_inx( uint8_t id, uint8_t inx );

/*
 *  ev3_light
 */

enum {
	LIT_LEFT,
	LIT_RIGHT,

	LIT__LOC__
};

enum {
	LIT_OFF,
	LIT_GREEN,
	LIT_RED,
	LIT_AMBER,

	LIT__COL__
};

extern void set_light( uint8_t loc, uint8_t col );
extern uint8_t get_light( uint8_t loc );

extern void set_light_trigger( uint8_t loc, uint8_t col, uint8_t trigger );
extern uint8_t get_light_trigger( uint8_t loc, uint8_t col );

extern bool set_light_blink( uint8_t loc, uint8_t col, int delay_on, int delay_off );
extern bool get_light_blink( uint8_t loc, uint8_t col );

/*
 *  ev3_sensor
 */

/**
 *  \brief EV3 ports to plug in a sensor.
 */
enum {
	INPUT_1,
	INPUT_2,
	INPUT_3,
	INPUT_4,

	INPUT__COUNT_  /**< Count of EV3 "in" ports. */
};

/**
 *  \brief Structure of a sensor descriptor.
 */
typedef struct {
	bool     connected;  /**< Flag - the sensor is connected. */
	uint32_t id;         /**< Identifier of the sensor. */
	uint32_t type_id;    /**< The sensor type. */

} EV3_SENSOR;

/**
 *  \brief Vector of sensor descriptors for each port (filled by \ref ev3_sensor_init).
 */
extern EV3_SENSOR ev3_sensor[ INPUT__COUNT_ ];

/**
 *  \brief Types of sensors.
 */
enum {
	EV3_TOUCH = 16,
	EV3_COLOR = 29,
	EV3_ULTRASONIC = 30,
	EV3_GYRO = 32,
	EV3_INFRARED = 33,

};

/**
 *  \brief Get "bin_data" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_sensor_bin_data( uint8_t id, byte *buf, size_t sz );
/**
 *  \brief Set "bin_data" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param value Attribute value.
 *  \param sz Size of attribute value.
 *  \return Count of written bytes.
 */
extern size_t set_sensor_bin_data( uint8_t id, byte *value, size_t sz );

/**
 *  \brief Get "bin_data_format" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_sensor_bin_data_format( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "dp" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_dp( uint8_t id, dword *buf );

/**
 *  \brief Get "fw_version" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_sensor_fw_version( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "i2c_addr" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_i2c_addr( uint8_t id, int *buf );

/**
 *  \brief Get "mode" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_sensor_mode( uint8_t id, char *buf, size_t sz );
/**
 *  \brief Set "mode" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param value Attribute value.
 *  \param sz Size of attribute value.
 *  \return Count of written bytes.
 */
extern size_t set_sensor_mode( uint8_t id, char *value );

/**
 *  \brief Get "modes" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_sensor_modes( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "num_values" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_num_values( uint8_t id, dword *buf );

/**
 *  \brief Get "poll_ms" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_poll_ms( uint8_t id, dword *buf );
/**
 *  \brief Set "poll_ms" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_sensor_poll_ms( uint8_t id, dword value );

/**
 *  \brief Get "port_name" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_sensor_port_name( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "units" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_sensor_units( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "type_id" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_type_id( uint8_t id, dword *buf );

/**
 *  \brief Get "value0" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_value0( uint8_t id, float *buf );

/**
 *  \brief Get "value1" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_value1( uint8_t id, float *buf );

/**
 *  \brief Get "value2" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_value2( uint8_t id, float *buf );

/**
 *  \brief Get "value3" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_value3( uint8_t id, float *buf );

/**
 *  \brief Get "value4" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_value4( uint8_t id, float *buf );

/**
 *  \brief Get "value5" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_value5( uint8_t id, float *buf );

/**
 *  \brief Get "value6" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_value6( uint8_t id, float *buf );

/**
 *  \brief Get "value7" attribute of the sensor.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_value7( uint8_t id, float *buf );

/**
 *  \brief Get "value" attribute of the sensor.
 *  \param inx Attribute index.
 *  \param id Identifier of the sensor.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_sensor_value( uint8_t inx, uint8_t id, int *buf );

/**
 *  \brief Get the name of the specified sensor type.
 *  \param type_id The sensor type.
 *  \return Name of the sensor type.
 */
extern char *ev3_sensor_type( uint8_t type_id );

/**
 *  \brief Search the port of the specified sensor type.
 *  \param type_id The sensor type.
 *  \return EV3 port.
 */
extern int ev3_sensor_port( uint8_t type_id );

/**
 *  \brief Get the descriptor of a sensor connected to the specified port.
 *  \param port EV3 port.
 *  \return Pointer to the sensor descriptor.
 */
extern EV3_SENSOR *ev3_get_sensor( uint8_t port );

extern int ev3_sensor_init( void );

/*
 *  ev3_tacho
 */

/**
 *  \brief EV3 ports to plug in a tacho.
 */
enum {
	OUTPUT_A,
	OUTPUT_B,
	OUTPUT_C,
	OUTPUT_D,

	OUTPUT__COUNT_  /**< Count of EV3 "out" ports. */
};

/**
 *  \brief Structure of a tacho descriptor.
 */
typedef struct {
	bool     connected;  /**< Flag - the tacho is connected. */
	uint32_t id;         /**< Identifier of the tacho. */
	uint32_t type_id;    /**< The tacho type. */

} EV3_TACHO;

/**
 *  \brief Vector of tacho descriptors for each port (filled by \ref ev3_tacho_init).
 */
extern EV3_TACHO ev3_tacho[ OUTPUT__COUNT_ ];

/**
 *  \brief Types of tachos.
 */
enum {
	TACHO = 7,
	MINITACHO = 8,

};

/**
 *  \brief Get "duty_cycle" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_duty_cycle( uint8_t id, int *buf );

/**
 *  \brief Get "duty_cycle_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_duty_cycle_sp( uint8_t id, int *buf );
/**
 *  \brief Set "duty_cycle_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_duty_cycle_sp( uint8_t id, int value );

/**
 *  \brief Get "polarity_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_tacho_polarity_mode( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "port_name" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_tacho_port_name( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "position" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_position( uint8_t id, int *buf );
/**
 *  \brief Set "position" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_position( uint8_t id, int value );

/**
 *  \brief Get "position_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_tacho_position_mode( uint8_t id, char *buf, size_t sz );
/**
 *  \brief Set "position_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.
 *  \param sz Size of attribute value.
 *  \return Count of written bytes.
 */
extern size_t set_tacho_position_mode( uint8_t id, char *value );

/**
 *  \brief Get "position_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_position_sp( uint8_t id, int *buf );
/**
 *  \brief Set "position_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_position_sp( uint8_t id, int value );

/**
 *  \brief Get "pulses_per_second" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_pulses_per_second( uint8_t id, int *buf );

/**
 *  \brief Get "pulses_per_second_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_pulses_per_second_sp( uint8_t id, int *buf );
/**
 *  \brief Set "pulses_per_second_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_pulses_per_second_sp( uint8_t id, int value );

/**
 *  \brief Get "ramp_down_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_ramp_down_sp( uint8_t id, dword *buf );
/**
 *  \brief Set "ramp_down_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_ramp_down_sp( uint8_t id, dword value );

/**
 *  \brief Get "ramp_up_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_ramp_up_sp( uint8_t id, dword *buf );
/**
 *  \brief Set "ramp_up_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_ramp_up_sp( uint8_t id, dword value );

/**
 *  \brief Get "regulation_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_tacho_regulation_mode( uint8_t id, char *buf, size_t sz );
/**
 *  \brief Set "regulation_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.
 *  \param sz Size of attribute value.
 *  \return Count of written bytes.
 */
extern size_t set_tacho_regulation_mode( uint8_t id, char *value );

/**
 *  \brief Set "reset" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_reset( uint8_t id, bool value );

/**
 *  \brief Get "run" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_run( uint8_t id, bool *buf );
/**
 *  \brief Set "run" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_run( uint8_t id, bool value );

/**
 *  \brief Get "run_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_tacho_run_mode( uint8_t id, char *buf, size_t sz );
/**
 *  \brief Set "run_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.
 *  \param sz Size of attribute value.
 *  \return Count of written bytes.
 */
extern size_t set_tacho_run_mode( uint8_t id, char *value );

/**
 *  \brief Get "speed_regulation_D" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_speed_regulation_D( uint8_t id, int *buf );
/**
 *  \brief Set "speed_regulation_D" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_speed_regulation_D( uint8_t id, int value );

/**
 *  \brief Get "speed_regulation_I" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_speed_regulation_I( uint8_t id, int *buf );
/**
 *  \brief Set "speed_regulation_I" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_speed_regulation_I( uint8_t id, int value );

/**
 *  \brief Get "speed_regulation_K" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_speed_regulation_K( uint8_t id, int *buf );
/**
 *  \brief Set "speed_regulation_K" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_speed_regulation_K( uint8_t id, int value );

/**
 *  \brief Get "speed_regulation_P" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_speed_regulation_P( uint8_t id, int *buf );
/**
 *  \brief Set "speed_regulation_P" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_speed_regulation_P( uint8_t id, int value );

/**
 *  \brief Get "state" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_tacho_state( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "stop_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_tacho_stop_mode( uint8_t id, char *buf, size_t sz );
/**
 *  \brief Set "stop_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.
 *  \param sz Size of attribute value.
 *  \return Count of written bytes.
 */
extern size_t set_tacho_stop_mode( uint8_t id, char *value );

/**
 *  \brief Get "stop_modes" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_tacho_stop_modes( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "time_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
extern size_t get_tacho_time_sp( uint8_t id, dword *buf );
/**
 *  \brief Set "time_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
extern size_t set_tacho_time_sp( uint8_t id, dword value );

/**
 *  \brief Get "type" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern size_t get_tacho_type( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get the name of the specified tacho type.
 *  \param type_id The tacho type.
 *  \return Name of the tacho type.
 */
extern char *ev3_tacho_type( uint8_t type_id );

/**
 *  \brief Search the port of the specified tacho type.
 *  \param type_id The tacho type.
 *  \return EV3 port.
 */
extern int ev3_tacho_port( uint8_t type_id );

/**
 *  \brief Get the descriptor of a tacho connected to the specified port.
 *  \param port EV3 port.
 *  \return Pointer to the tacho descriptor.
 */
extern EV3_TACHO *ev3_get_tacho( uint8_t port );

extern int ev3_tacho_init( void );

