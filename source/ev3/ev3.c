
/*  ev3.c was generated by yup.py (yupp) 0.7b6
    out of ev3.yu-c at 2014-09-26 18:33
 *//**
 *  \file  ev3.c (ev3.yu-c)
 *  \brief  EV3 file operations.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define EV3_IMPLEMENT

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "modp_numtoa.h"
#include "ev3.h"

/**
 *  \addtogroup ev3
 *  \{
 */

// EV3 BRICK /////////////////////////////////////
#ifdef __ARM_ARCH_4T__

#include <sys/types.h>
#include <dirent.h>

int ev3_init( void )
{
	return ( 1 );
}

void ev3_uninit( void )
{

}

size_t ev3_write_binary( const char *fn, char *data, size_t sz )
{
	FILE *f;
	size_t result;

	f = fopen( fn, "w" );
	if ( f == NULL ) return ( 0 );

	result = fwrite( data, 1, sz, f );
	fclose( f );
	return ( result );
}

size_t ev3_read_binary( const char *fn, char *buf, size_t sz )
{
	FILE *f;
	size_t result;

	f = fopen( fn, "r" );
	if ( f == NULL ) return ( 0 );

	result = fread( buf, 1, sz, f );
	fclose( f );
	return ( result );
}

static size_t __ev3_listdir( char *fn, void *buf, size_t sz )
{
	DIR *d;
	struct dirent *de;
	char *p;

	d = opendir( fn );
	if ( d == NULL ) return ( 0 );

	p = buf;
	while (( de = readdir( d ))) {
		size_t l = strlen( de->d_name ) + 1;
		if ( sz > l ) {
			sz -= l;
			memcpy( p, de->d_name, l - 1 );
			p[ l - 1 ] = ' ';
			p += l;
		}
	}
	closedir( d );
	return (( void* ) p - buf );
}

bool ev3_poweroff( void )
{
	system( "shutdown -h now" );
	return ( true );
}

// CLIENT ////////////////////////////////////////
#else

#include "ev3_link.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

#define BRICK_WAIT_DELAY  1000  /* msec */
#define BRICK_WAIT_TRIES  10

int ev3_init( void )
{
	int i;

	if ( udp_ev3_open( ev3_brick_addr, ev3_brick_port ) == EOF ) return ( EV3_NONE );

	if ( ev3_brick_addr == NULL ) {
		for ( i = 0; i < BRICK_WAIT_TRIES; i++ ) {
			if ( udp_ev3_catch_address()) return ( 1 );
			Sleep( BRICK_WAIT_DELAY );
		}
	}
	return ( 0 );
}

void ev3_uninit( void )
{
	udp_ev3_close();
}

size_t ev3_write_binary( const char *fn, char *data, size_t sz )
{
	return udp_ev3_write(( char* ) fn, data, sz );
}

size_t ev3_read_binary( const char *fn, char *buf, size_t sz )
{
	return udp_ev3_read(( char* ) fn, buf, sz );
}

static size_t __ev3_listdir( char *fn, char *buf, size_t sz )
{
	return udp_ev3_listdir( fn, buf, sz );
}

bool ev3_poweroff( void )
{
	return udp_ev3_poweroff();
}

//////////////////////////////////////////////////
#endif

size_t ev3_write( const char *fn, char *value )
{
	return ev3_write_binary( fn, value, strlen( value ));
}

size_t ev3_write_int( const char *fn, int value )
{
	char s[ 12 ];

	modp_itoa10( value, s );
	return ev3_write( fn, s );
}

size_t ev3_write_dword( const char *fn, uint32_t value )
{
	char s[ 11 ];

	modp_uitoa10( value, s );
	return ev3_write( fn, s );
}

size_t ev3_write_float( const char *fn, float value )
{
	char s[ 32 ];

	modp_dtoa2( value, s, 4 );
	return ev3_write( fn, s );
}

size_t ev3_write_bool( const char *fn, bool value )
{
	return ev3_write_binary( fn, ( value ) ? "1" : "0", 1 );
}

size_t ev3_write_char_array( const char *fn, char *value )
{
	return ev3_write( fn, value );
}

size_t ev3_write_byte_array( const char *fn, uint8_t *value, size_t sz )
{
	return ev3_write_binary( fn, ( char* ) value, sz );
}

size_t ev3_read( const char *fn, char *buf, size_t sz )
{
	size_t c;

	if ( sz < 1 ) return ( 0 );

	c = ev3_read_binary( fn, buf, sz );
	buf[ c - 1 ] = '\x00';
	return ( c );
}

size_t ev3_read_int( const char *fn, int *buf )
{
	char s[ 12 ];
	char *end;

	if ( ev3_read( fn, s, sizeof( s ))) {
		*buf = strtol( s, &end, 0 );
		if ( *end ) return ( 0 );

		return ( sizeof( int ));
	}
	return ( 0 );
}

size_t ev3_read_dword( const char *fn, uint32_t *buf )
{
	char s[ 11 ];
	char *end;

	if ( ev3_read( fn, s, sizeof( s ))) {
		*buf = strtoul( s, &end, 0 );
		if ( *end ) return ( 0 );

		return ( sizeof( uint32_t ));
	}
	return ( 0 );
}

size_t ev3_read_float( const char *fn, float *buf )
{
	char s[ 16 ];
	char *end;

	if ( ev3_read( fn, s, sizeof( s ))) {
		*buf = ( float ) strtod( s, &end );
		if ( *end ) return ( 0 );

		return ( sizeof( float ));
	}
	return ( 0 );
}

size_t ev3_read_bool( const char *fn, bool *buf )
{
	int _int;
	if ( ev3_read_int( fn, &_int )) {
		*buf = !!_int;

		return ( sizeof( bool ));
	}
	return ( 0 );
}

size_t ev3_read_char_array( const char *fn, char *buf, size_t sz )
{
	return ev3_read( fn, buf, sz );
}

size_t ev3_read_byte_array( const char *fn, uint8_t *buf, size_t sz )
{
	return ev3_read_binary( fn, ( char* ) buf, sz );
}

size_t ev3_listdir( const char *fn, char *buf, size_t sz )
{
	size_t c;

	if ( sz < 1 ) return ( 0 );

	c = __ev3_listdir(( char* ) fn, buf, sz );
	buf[ c - 1 ] = '\x00';
	return ( c );
}

/** \} */
