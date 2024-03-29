//-----------------------------------------------------------------------------
#ifndef __S3DXPlatform_h__
#define __S3DXPlatform_h__
//-----------------------------------------------------------------------------
#include "S3DXConfig.h"
//-----------------------------------------------------------------------------
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//-----------------------------------------------------------------------------
#ifndef __THROW
#define __THROW
#endif
//-----------------------------------------------------------------------------
// Declaration of some standard C handy functions
// Note: do *not* include <stlib.h> and <math.h> to avoid conflicts with 
// "system" and "math" APIs
//
#if (defined _WIN32)
extern "C"  _CRTIMP double  strtod  ( const char *, char ** ) ;
#define                     strtof  (float)strtod
#elif (defined ANDROID_NDK)
extern "C"          double  strtod  ( const char *, char ** ) ;
#define                     strtof  (float)strtod
#elif (defined __MANDREEL__)
//??? FIXME
#else
extern "C"          float   strtof  ( const char *, char ** ) __THROW ;
#endif
//-----------------------------------------------------------------------------
inline bool streq ( const char *_p1, const char *_p2 )
{
    while ( *_p1 || *_p2 )
    {
        if ( *_p1++ != *_p2++ ) return false ;
    }
    return true ;
}
//-----------------------------------------------------------------------------

#if (defined _WIN32) || (defined __CYGWIN__)
#   define S3DX_API __declspec(dllexport)
#else
#   if __GNUC__ >= 4
#       define S3DX_API __attribute__ ((visibility("default")))
#   else
#       define S3DX_API
#   endif
#endif

#if (__LP64__) || (defined _WIN64) || (defined _M_IA64) || (defined __ia64__) || (defined _M_AMD64) || (defined __x86_64__)
#   define S3DX_ARCH_LP64   1
#   define S3DX_ARCH_ILP32  0
#else
#   define S3DX_ARCH_LP64   0
#   define S3DX_ARCH_ILP32  1
#endif


#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#define S3DX_MAX(__a__,__b__)           (((__a__) > (__b__)) ? (__a__) : (__b__))
#define S3DX_MIN(__a__,__b__)           (((__a__) < (__b__)) ? (__a__) : (__b__))
#define S3DX_CLAMP(__a__,__b__,__c__)   (((__a__) > (__b__)) ? (((__a__) < (__c__)) ? (__a__) : (__c__)) : (__b__))
#define S3DX_ABS(__a__)                 (((__a__) < 0) ? (-(__a__)) : (__a__))
#define S3DX_SQR(__a__)                 ((__a__)*(__a__))

#define S3DX_STRTOF                 strtof
#define S3DX_SPRINTF                sprintf
#define S3DX_STRCPY                 strcpy
#define S3DX_STRCAT                 strcat
#define S3DX_STRLEN   (S3DX::uint32)strlen
#define S3DX_STRCMP                 strcmp
#define S3DX_STREQ                  streq
#define S3DX_ISSPACE                isspace
#define S3DX_MEMCPY                 memcpy

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
