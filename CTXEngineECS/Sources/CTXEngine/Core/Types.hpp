#pragma once

/*
	This file defines data types used for CTXEngine. To use this file don't need
	any includes.
*/

typedef signed char			int8;  // Equivalent to int8_t
typedef signed short		int16; // Equivalent to int16_t
typedef signed int			int32; // Equivalent to int32_t
typedef signed long long	int64; // Equivalent to int64_t

typedef unsigned char		uint8;  // Equivalent to uint8_t
typedef unsigned short		uint16; // Equivalent to uint16_t
typedef unsigned  int		uint32; // Equivalent to uint32_t
typedef unsigned long long	uint64; // Equivalent to uint64_t

typedef uint32	uint;  // Equivalent to uint32_t, unsigned int
typedef uint8	cubyte; // Equivalent to uint8_t, unsigned char
typedef char	cbyte;  // Equivalent to int8_t, char
typedef bool    cboolean;

#define ctxclass class;
#define ctxstruct struct;
#define ctxenum enum;
#define ctxenumclass enum class;
#define ctxinterface class;