//-----------------------------------------------------------------------------
#ifndef __S3DXConfig_h__
#define __S3DXConfig_h__
//-----------------------------------------------------------------------------
#ifndef S3DX_SDK_VERSION
#define S3DX_SDK_VERSION    0x01090008  // 1.9.0.8
#endif
//-----------------------------------------------------------------------------
#if ( S3DX_SDK_VERSION >= 0x01090000 )
#   define S3DX_AVAILABLE_0x01090000( __exp__ ) __exp__
#else
#   define S3DX_AVAILABLE_0x01090000( ) 
#endif
#if ( S3DX_SDK_VERSION >= 0x01090001 )
#   define S3DX_AVAILABLE_0x01090001( __exp__ ) __exp__
#else
#   define S3DX_AVAILABLE_0x01090001( ) 
#endif
#if ( S3DX_SDK_VERSION >= 0x01090002 )
#   define S3DX_AVAILABLE_0x01090002( __exp__ ) __exp__
#else
#   define S3DX_AVAILABLE_0x01090002( ) 
#endif
#if ( S3DX_SDK_VERSION >= 0x01090003 )
#   define S3DX_AVAILABLE_0x01090003( __exp__ ) __exp__
#else
#   define S3DX_AVAILABLE_0x01090003( ) 
#endif
#if ( S3DX_SDK_VERSION >= 0x01090004 )
#   define S3DX_AVAILABLE_0x01090004( __exp__ ) __exp__
#else
#   define S3DX_AVAILABLE_0x01090004( ) 
#endif
#if ( S3DX_SDK_VERSION >= 0x01090005 )
#   define S3DX_AVAILABLE_0x01090005( __exp__ ) __exp__
#else
#   define S3DX_AVAILABLE_0x01090005( ) 
#endif
#if ( S3DX_SDK_VERSION >= 0x01090006 )
#   define S3DX_AVAILABLE_0x01090006( __exp__ ) __exp__
#else
#   define S3DX_AVAILABLE_0x01090006( ) 
#endif
#if ( S3DX_SDK_VERSION >= 0x01090007 )
#   define S3DX_AVAILABLE_0x01090007( __exp__ ) __exp__
#else
#   define S3DX_AVAILABLE_0x01090007( ) 
#endif
#if ( S3DX_SDK_VERSION >= 0x01090008 )
#   define S3DX_AVAILABLE_0x01090008( __exp__ ) __exp__
#else
#   define S3DX_AVAILABLE_0x01090008( ) 
#endif
//-----------------------------------------------------------------------------
#define S3DX_AVAILABLE( __exp__, __sdk__ ) S3DX_AVAILABLE_##__sdk__( __exp__ )
//-----------------------------------------------------------------------------
#ifndef S3DX_MODULE_GUID
#define S3DX_MODULE_GUID    S3DX
#endif
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
