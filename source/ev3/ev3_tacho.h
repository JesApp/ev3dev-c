
/*  ev3_tacho.h was generated by yup.py (yupp) 1.0b2
    out of ev3_tacho.yu-h 
 *//**
 *  \file  ev3_tacho.h (ev3_tacho.yu-h)
 *  \brief  EV3 Tacho Motors.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#ifndef EV3_TACHO_H
#define EV3_TACHO_H

#ifdef  EV3_TACHO_IMPLEMENT
#define EV3_TACHO_EXT
#define EV3_TACHO_EXT_INIT( dec, init ) \
	dec = init
#define EV3_TACHO_EXT_C
#define EV3_TACHO_EXT_C_INIT( dec, init ) \
	dec = init
#define EV3_TACHO_INL
#else
#define EV3_TACHO_EXT extern
#define EV3_TACHO_EXT_INIT( dec, init ) \
	extern dec
#ifdef __cplusplus
#define EV3_TACHO_C "C"
#else
#define EV3_TACHO_C
#endif
#define EV3_TACHO_EXT_C extern EV3_TACHO_C
#define EV3_TACHO_EXT_C_INIT( dec, init ) \
	extern EV3_TACHO_C dec
#if __GNUC__ && !__GNUC_STDC_INLINE__
#define EV3_TACHO_INL extern inline
#else
#define EV3_TACHO_INL inline
#endif
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 *  \defgroup ev3_tacho Tacho motors
 *  \brief Access to EV3 tacho motors.
 *  \see http://www.ev3dev.org/docs/motors/
 *  \see http://www.ev3dev.org/docs/drivers/tacho-motor-class/
 *  \{
 */

#define TACHO_DIR  "/sys/class/tacho-motor"  /**< Directory of tachos. */

/**
 *  \brief Structure of a tacho descriptor.
 */
typedef struct {
	INX_T type_inx;  /**< Tacho type. */
	uint8_t port;  /**< Tacho EV3 port. */
	uint8_t extport;  /**< Tacho extended port. */

} EV3_TACHO;

#define TACHO_DESC__LIMIT_  DESC_LIMIT  /**< Limit of tacho descriptors. */

#define TACHO__NONE_  TACHO_DESC__LIMIT_  /**< Tacho is not found. */

/**
 *  \brief Vector of tacho descriptors (filled by \ref ev3_tacho_init).
 */
EV3_TACHO_EXT_C EV3_TACHO ev3_tacho[ TACHO_DESC__LIMIT_ ];

/**
 *  \brief Identifiers of tacho types.
 */
enum {
	TACHO_TYPE__NONE_ = 0,  /* XXX: memset( 0 ) is used */

	LEGO_EV3_L_MOTOR,
	LEGO_EV3_M_MOTOR,
	FI_L12_EV3,

	TACHO_TYPE__COUNT_,  /**< Count of tacho types. */
	TACHO_TYPE__UNKNOWN_ = TACHO_TYPE__COUNT_
};

/**
 *  \brief Common identifiers of tacho "command" attribute.
 */
enum {
	TACHO_COMMAND__NONE_ = 0,

	TACHO_RUN_FOREVER,
	TACHO_RUN_TO_ABS_POS,
	TACHO_RUN_TO_REL_POS,
	TACHO_RUN_TIMED,
	TACHO_RUN_DIRECT,
	TACHO_STOP,
	TACHO_RESET,

	TACHO_COMMAND__COUNT_,  /**< Count of tacho "command" attribute. */
	TACHO_COMMAND__UNKNOWN_ = TACHO_COMMAND__COUNT_
};

/**
 *  \brief Common identifiers of tacho "polarity" attribute.
 */
enum {
	TACHO_POLARITY__NONE_ = 0,

	TACHO_NORMAL,
	TACHO_INVERSED,

	TACHO_POLARITY__COUNT_,  /**< Count of tacho "polarity" attribute. */
	TACHO_POLARITY__UNKNOWN_ = TACHO_POLARITY__COUNT_
};

/**
 *  \brief Common identifiers of tacho "stop_action" attribute.
 */
enum {
	TACHO_STOP_ACTION__NONE_ = 0,

	TACHO_COAST,
	TACHO_BRAKE,
	TACHO_HOLD,

	TACHO_STOP_ACTION__COUNT_,  /**< Count of tacho "stop_action" attribute. */
	TACHO_STOP_ACTION__UNKNOWN_ = TACHO_STOP_ACTION__COUNT_
};

/**
 *  \brief Common identifiers of tacho "state" attribute.
 */
enum {
	TACHO_STATE__NONE_ = 0,

	TACHO_RUNNING = 0x1L,
	TACHO_RAMPING = 0x2L,
	TACHO_HOLDING = 0x4L,
	TACHO_OVERLOADED = 0x8L,
	TACHO_STALLED = 0x10L,

};

/**
 *  \brief Read "address" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_address( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Write "command" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_command( uint8_t sn, char *value );

/**
 *  \brief Write "command" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_command( uint8_t *sn, char *value );

/**
 *  \brief Read "commands" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_commands( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Read "count_per_rot" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_count_per_rot( uint8_t sn, int *buf );

/**
 *  \brief Read "count_per_m" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_count_per_m( uint8_t sn, int *buf );

/**
 *  \brief Read "full_travel_count" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_full_travel_count( uint8_t sn, int *buf );

/**
 *  \brief Read "driver_name" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_driver_name( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Read "duty_cycle" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_duty_cycle( uint8_t sn, int *buf );

/**
 *  \brief Read "duty_cycle_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_duty_cycle_sp( uint8_t sn, int *buf );

/**
 *  \brief Write "duty_cycle_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_duty_cycle_sp( uint8_t sn, int value );

/**
 *  \brief Write "duty_cycle_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_duty_cycle_sp( uint8_t *sn, int value );

/**
 *  \brief Read "hold_pid/Kd" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_hold_pid_Kd( uint8_t sn, int *buf );

/**
 *  \brief Write "hold_pid/Kd" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_hold_pid_Kd( uint8_t sn, int value );

/**
 *  \brief Write "hold_pid/Kd" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_hold_pid_Kd( uint8_t *sn, int value );

/**
 *  \brief Read "hold_pid/Ki" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_hold_pid_Ki( uint8_t sn, int *buf );

/**
 *  \brief Write "hold_pid/Ki" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_hold_pid_Ki( uint8_t sn, int value );

/**
 *  \brief Write "hold_pid/Ki" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_hold_pid_Ki( uint8_t *sn, int value );

/**
 *  \brief Read "hold_pid/Kp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_hold_pid_Kp( uint8_t sn, int *buf );

/**
 *  \brief Write "hold_pid/Kp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_hold_pid_Kp( uint8_t sn, int value );

/**
 *  \brief Write "hold_pid/Kp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_hold_pid_Kp( uint8_t *sn, int value );

/**
 *  \brief Read "max_speed" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_max_speed( uint8_t sn, int *buf );

/**
 *  \brief Read "polarity" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_polarity( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Write "polarity" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_polarity( uint8_t sn, char *value );

/**
 *  \brief Write "polarity" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_polarity( uint8_t *sn, char *value );

/**
 *  \brief Read "position" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_position( uint8_t sn, int *buf );

/**
 *  \brief Write "position" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_position( uint8_t sn, int value );

/**
 *  \brief Write "position" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_position( uint8_t *sn, int value );

/**
 *  \brief Read "position_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_position_sp( uint8_t sn, int *buf );

/**
 *  \brief Write "position_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_position_sp( uint8_t sn, int value );

/**
 *  \brief Write "position_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_position_sp( uint8_t *sn, int value );

/**
 *  \brief Read "ramp_down_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_ramp_down_sp( uint8_t sn, int *buf );

/**
 *  \brief Write "ramp_down_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_ramp_down_sp( uint8_t sn, int value );

/**
 *  \brief Write "ramp_down_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_ramp_down_sp( uint8_t *sn, int value );

/**
 *  \brief Read "ramp_up_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_ramp_up_sp( uint8_t sn, int *buf );

/**
 *  \brief Write "ramp_up_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_ramp_up_sp( uint8_t sn, int value );

/**
 *  \brief Write "ramp_up_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_ramp_up_sp( uint8_t *sn, int value );

/**
 *  \brief Read "speed" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_speed( uint8_t sn, int *buf );

/**
 *  \brief Read "speed_pid/Kd" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_speed_pid_Kd( uint8_t sn, int *buf );

/**
 *  \brief Write "speed_pid/Kd" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_speed_pid_Kd( uint8_t sn, int value );

/**
 *  \brief Write "speed_pid/Kd" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_speed_pid_Kd( uint8_t *sn, int value );

/**
 *  \brief Read "speed_pid/Ki" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_speed_pid_Ki( uint8_t sn, int *buf );

/**
 *  \brief Write "speed_pid/Ki" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_speed_pid_Ki( uint8_t sn, int value );

/**
 *  \brief Write "speed_pid/Ki" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_speed_pid_Ki( uint8_t *sn, int value );

/**
 *  \brief Read "speed_pid/Kp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_speed_pid_Kp( uint8_t sn, int *buf );

/**
 *  \brief Write "speed_pid/Kp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_speed_pid_Kp( uint8_t sn, int value );

/**
 *  \brief Write "speed_pid/Kp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_speed_pid_Kp( uint8_t *sn, int value );

/**
 *  \brief Read "speed_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_speed_sp( uint8_t sn, int *buf );

/**
 *  \brief Write "speed_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_speed_sp( uint8_t sn, int value );

/**
 *  \brief Write "speed_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_speed_sp( uint8_t *sn, int value );

/**
 *  \brief Read "state" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_state( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Read "stop_action" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_stop_action( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Write "stop_action" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_stop_action( uint8_t sn, char *value );

/**
 *  \brief Write "stop_action" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_stop_action( uint8_t *sn, char *value );

/**
 *  \brief Read "stop_actions" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_stop_actions( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Read "time_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_time_sp( uint8_t sn, int *buf );

/**
 *  \brief Write "time_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_time_sp( uint8_t sn, int value );

/**
 *  \brief Write "time_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_time_sp( uint8_t *sn, int value );

/**
 *  \brief Get name of the specified tacho type.
 *  \param type_inx Index of the tacho type.
 *  \return Requested value.
 */
EV3_TACHO_EXT_C const char *ev3_tacho_type( INX_T type_inx );

/**
 *  \brief Read "driver_name" attribute and get index of the tacho type.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_TACHO_EXT_C INX_T get_tacho_type_inx( uint8_t sn );

/**
 *  \brief Read tacho attributes that are required for filling the descriptor.
 *  \param sn Sequence number.
 *  \param desc Buffer for the descriptor.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_desc( uint8_t sn, EV3_TACHO *desc );

/**
 *  \brief Get descriptor of the tacho.
 *  \param sn Sequence number.
 *  \return Pointer to the tacho descriptor.
 */
EV3_TACHO_EXT_C EV3_TACHO *ev3_tacho_desc( uint8_t sn );

/**
 *  \brief Get type from the tacho descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_TACHO_EXT_C INX_T ev3_tacho_desc_type_inx( uint8_t sn );

/**
 *  \brief Get EV3 port from the tacho descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_TACHO_EXT_C uint8_t ev3_tacho_desc_port( uint8_t sn );

/**
 *  \brief Get extended port from the tacho descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_TACHO_EXT_C uint8_t ev3_tacho_desc_extport( uint8_t sn );

/**
 *  \brief Assemble EV3 port name from the tacho descriptor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \return Requested value.
 */
EV3_TACHO_EXT_C char *ev3_tacho_port_name( uint8_t sn, char *buf );

/**
 *  \brief Search of a sequence number of the specified tacho type.
 *  \param type_inx Tacho type.
 *  \param[out] sn Buffer for the sequence number.
 *  \param from Search initial value.
 *  \return Flag - the tacho is found.
 */
EV3_TACHO_EXT_C bool ev3_search_tacho( INX_T type_inx, uint8_t *sn, uint8_t from );

/**
 *  \brief Search of a sequence number the tacho by plug-in attributes.
 *  \param port EV3 port.
 *  \param extport Extended port.
 *  \param[out] sn Buffer for the sequence number.
 *  \param from Search initial value.
 *  \return Flag - the tacho is found.
 */
EV3_TACHO_EXT_C bool ev3_search_tacho_plugged_in( uint8_t port, uint8_t extport, uint8_t *sn, uint8_t from );

/**
 *  \brief Get name of the specified tacho command.
 *  \param command_inx Index of the tacho command.
 *  \return Requested value.
 */
EV3_TACHO_EXT_C const char *ev3_tacho_command( INX_T command_inx );

/**
 *  \brief Write "command" attribute of the tacho by the index.
 *  \param sn Sequence number.
 *  \param command_inx Index of the tacho command.
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_command_inx( uint8_t sn, INX_T command_inx );

/**
 *  \brief Write "command" attribute of several tachos by the index.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param command_inx Index of the tacho command.
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_command_inx( uint8_t *sn, INX_T command_inx );

/**
 *  \brief Get name of the specified tacho polarity.
 *  \param polarity_inx Index of the tacho polarity.
 *  \return Requested value.
 */
EV3_TACHO_EXT_C const char *ev3_tacho_polarity( INX_T polarity_inx );

/**
 *  \brief Read "polarity" attribute of the tacho and get the index.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_TACHO_EXT_C INX_T get_tacho_polarity_inx( uint8_t sn );

/**
 *  \brief Write "polarity" attribute of the tacho by the index.
 *  \param sn Sequence number.
 *  \param polarity_inx Index of the tacho polarity.
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_polarity_inx( uint8_t sn, INX_T polarity_inx );

/**
 *  \brief Write "polarity" attribute of several tachos by the index.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param polarity_inx Index of the tacho polarity.
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_polarity_inx( uint8_t *sn, INX_T polarity_inx );

/**
 *  \brief Get name of the specified tacho stop_action.
 *  \param stop_action_inx Index of the tacho stop_action.
 *  \return Requested value.
 */
EV3_TACHO_EXT_C const char *ev3_tacho_stop_action( INX_T stop_action_inx );

/**
 *  \brief Read "stop_action" attribute of the tacho and get the index.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_TACHO_EXT_C INX_T get_tacho_stop_action_inx( uint8_t sn );

/**
 *  \brief Write "stop_action" attribute of the tacho by the index.
 *  \param sn Sequence number.
 *  \param stop_action_inx Index of the tacho stop_action.
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t set_tacho_stop_action_inx( uint8_t sn, INX_T stop_action_inx );

/**
 *  \brief Write "stop_action" attribute of several tachos by the index.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param stop_action_inx Index of the tacho stop_action.
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT_C size_t multi_set_tacho_stop_action_inx( uint8_t *sn, INX_T stop_action_inx );

/**
 *  \brief Read "state" attribute of the tacho and get the flags.
 *  \param sn Sequence number.
 *  \param flags Buffer for the flags.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT_C size_t get_tacho_state_flags( uint8_t sn, FLAGS_T *flags );

/**
 *  \brief Detect connected tachos.
 *  \return Number of found tachos or -1 in case of an error.
 */
EV3_TACHO_EXT_C int ev3_tacho_init( void );

/** \} */

#undef EV3_TACHO_EXT
#undef EV3_TACHO_EXT_INIT
#undef EV3_TACHO_EXT_C
#undef EV3_TACHO_EXT_C_INIT
#undef EV3_TACHO_INL
#undef EV3_TACHO_C
#endif

