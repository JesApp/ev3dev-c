
/*  ev3.h was generated by yup.py (yupp) 1.0b2
    out of ev3.yu-h 
 *//**
 *  \file  ev3.h (ev3.yu-h)
 *  \brief  EV3 file operations.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#ifndef EV3_H
#define EV3_H

#ifdef  EV3_IMPLEMENT
#define EV3_EXT
#define EV3_EXT_INIT( dec, init ) \
	dec = init
#define EV3_EXT_C
#define EV3_EXT_C_INIT( dec, init ) \
	dec = init
#define EV3_INL
#else
#define EV3_EXT extern
#define EV3_EXT_INIT( dec, init ) \
	extern dec
#ifdef __cplusplus
#define EV3_C "C"
#else
#define EV3_C
#endif
#define EV3_EXT_C extern EV3_C
#define EV3_EXT_C_INIT( dec, init ) \
	extern EV3_C dec
#if __GNUC__ && !__GNUC_STDC_INLINE__
#define EV3_INL extern inline
#else
#define EV3_INL inline
#endif
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "ev3_both.h"

/**
 *  \defgroup ev3 File operations
 *  \brief Access to the file system of the EV3 brick.
 *
 *  This module contains functions for the local access to the file system of the EV3 brick,
 *  in case of the remote access appropriate functions from \ref ev3_link "ev3_link" module will be called.
 *  \{
 */

// CLIENT ////////////////////////////////////////
#ifndef __ARM_ARCH_4T__

/**
 *  \brief Predefined IP address of the EV3 brick.
 */
EV3_EXT_C_INIT( char *ev3_brick_addr, NULL );

/**
 *  \brief UDP port of the EV3 brick.
 */
EV3_EXT_C_INIT( uint16_t ev3_brick_port, 8800 );

//////////////////////////////////////////////////
#endif

#ifndef DEFINE_H
typedef uint8_t byte;
typedef uint32_t dword;

#endif

typedef uint8_t INX_T;
typedef uint8_t FLAGS_T;

#define STR_unknown_  "<unknown>"

/**
 *  \brief Initialize the remote access and detect the EV3 brick.
 *  This function do nothing in the case of the local access.
 *  To disable the brick detection just specify IP address before the call of this function.
 *  \return 0 - the brick is NOT found or auto-detection is disabled; 1 - the brick is found;
 *  -1 - an error has occurred.
 */
EV3_EXT_C int ev3_init( void );

/**
 *  \brief Uninitialize the remote access.
 */
EV3_EXT_C void ev3_uninit( void );

/**
 *  \brief Write binary data into the specified file of the EV3 brick.
 *  \param fn Filename.
 *  \param data Data.
 *  \param sz Data size.
 *  \return Count of written bytes.
 */
EV3_EXT_C size_t ev3_write_binary( const char *fn, char *data, size_t sz );

/**
 *  \brief Write a string into the specified file.
 *  \param fn Filename.
 *  \param value Value.
 *  \return Count of written bytes.
 */
EV3_EXT_C size_t ev3_write( const char *fn, char *value );

/**
 *  \brief Write a boolean value into the specified file.
 *  \param fn Filename.
 *  \param value Value.
 *  \return Count of written bytes.
 */
EV3_EXT_C size_t ev3_write_bool( const char *fn, bool value );

/**
 *  \brief Write an integer value into the specified file.
 *  \param fn Filename.
 *  \param value Value.
 *  \return Count of written bytes.
 */
EV3_EXT_C size_t ev3_write_int( const char *fn, int value );

/**
 *  \brief Write an unsigned integer value into the specified file.
 *  \param fn Filename.
 *  \param value Value.
 *  \return Count of written bytes.
 */
EV3_EXT_C size_t ev3_write_dword( const char *fn, uint32_t value );

/**
 *  \brief Write a byte value into the specified file.
 *  \param fn Filename.
 *  \param value Value.
 *  \return Count of written bytes.
 */
EV3_EXT_C size_t ev3_write_byte( const char *fn, uint8_t value );

/**
 *  \brief Write a float value into the specified file.
 *  \param fn Filename.
 *  \param value Value.
 *  \return Count of written bytes.
 */
EV3_EXT_C size_t ev3_write_float( const char *fn, float value );

EV3_EXT_C size_t ev3_write_char_array( const char *fn, char *value );
EV3_EXT_C size_t ev3_write_byte_array( const char *fn, uint8_t *value, size_t sz );

/**
 *  \brief Write binary data into several specified files of the EV3 brick.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param pos Position of the sequence number field into the template.
 *  \param fn Filename template.
 *  \param data Data.
 *  \param sz Data size.
 *  \return Count of written bytes.
 */
EV3_EXT_C size_t ev3_multi_write_binary( uint8_t *sn, uint16_t pos, const char *fn, char *data, size_t sz );

EV3_EXT_C size_t ev3_multi_write( uint8_t *sn, uint16_t pos, const char *fn, char *value );
EV3_EXT_C size_t ev3_multi_write_bool( uint8_t *sn, uint16_t pos, const char *fn, bool value );
EV3_EXT_C size_t ev3_multi_write_int( uint8_t *sn, uint16_t pos, const char *fn, int value );
EV3_EXT_C size_t ev3_multi_write_dword( uint8_t *sn, uint16_t pos, const char *fn, uint32_t value );
EV3_EXT_C size_t ev3_multi_write_byte( uint8_t *sn, uint16_t pos, const char *fn, uint8_t value );
EV3_EXT_C size_t ev3_multi_write_float( uint8_t *sn, uint16_t pos, const char *fn, float value );
EV3_EXT_C size_t ev3_multi_write_char_array( uint8_t *sn, uint16_t pos, const char *fn, char *value );
EV3_EXT_C size_t ev3_multi_write_byte_array( uint8_t *sn, uint16_t pos, const char *fn, uint8_t *value, size_t sz );

/**
 *  \brief Read binary data from the specified file.
 *  \param fn Filename.
 *  \param[out] buf Buffer for data.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_EXT_C size_t ev3_read_binary( const char *fn, char *buf, size_t sz );

/**
 *  \brief Read a string from the specified file.
 *  \param fn Filename.
 *  \param[out] buf Buffer for string.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_EXT_C size_t ev3_read( const char *fn, char *buf, size_t sz );

/**
 *  \brief Read a boolean value from the specified file.
 *  \param fn Filename.
 *  \param[out] buf Buffer for a value.
 *  \return Count of read bytes.
 */
EV3_EXT_C size_t ev3_read_bool( const char *fn, bool *buf );

/**
 *  \brief Read an integer value from the specified file.
 *  \param fn Filename.
 *  \param[out] buf Buffer for a value.
 *  \return Count of read bytes.
 */
EV3_EXT_C size_t ev3_read_int( const char *fn, int *buf );

/**
 *  \brief Read an unsigned integer value from the specified file.
 *  \param fn Filename.
 *  \param[out] buf Buffer for a value.
 *  \return Count of read bytes.
 */
EV3_EXT_C size_t ev3_read_dword( const char *fn, uint32_t *buf );

/**
 *  \brief Read a byte value from the specified file.
 *  \param fn Filename.
 *  \param[out] buf Buffer for a value.
 *  \return Count of read bytes.
 */
EV3_EXT_C size_t ev3_read_byte( const char *fn, uint8_t *buf );

/**
 *  \brief Read a float value from the specified file.
 *  \param fn Filename.
 *  \param[out] buf Buffer for a value.
 *  \return Count of read bytes.
 */
EV3_EXT_C size_t ev3_read_float( const char *fn, float *buf );

EV3_EXT_C size_t ev3_read_char_array( const char *fn, char *buf, size_t sz );
EV3_EXT_C size_t ev3_read_byte_array( const char *fn, uint8_t *buf, size_t sz );

/**
 *  \brief List files in the specified directory of the EV3 brick.
 *  \param fn Directory name.
 *  \param[out] buf Buffer for files list.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_EXT_C size_t ev3_listdir( const char *fn, char *buf, size_t sz );

/**
 *  \brief Read state of the EV3 brick's keys.
 *  \param[out] buf Buffer for a state.
 *  \return Count of read bytes.
 */
EV3_EXT_C size_t ev3_read_keys( uint8_t *buf );

/**
 *  \brief Power-off the EV3 brick.
 *  \return false - no reply; true - OK.
 */
EV3_EXT_C bool ev3_poweroff( void );

/**
 *  \brief Get a numerical suffix of the string.
 *  \param prefix Prefix string.
 *  \param s in - pointer to the string (char *); out - pointer to the next character after the suffix.
 *  \param[out] buf Buffer for a numerical suffix.
 *  \return 0 - suffix is not found; 1 - suffix is found at the string end;
 *  2 - suffix is found but the string is not over.
 */
EV3_EXT_C int ev3_string_suffix( const char *prefix, char **s, uint32_t *buf );

/** \} */

#undef EV3_EXT
#undef EV3_EXT_INIT
#undef EV3_EXT_C
#undef EV3_EXT_C_INIT
#undef EV3_INL
#undef EV3_C
#endif

