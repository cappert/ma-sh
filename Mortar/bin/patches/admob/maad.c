/*
 *  maad.c
 *  Modern Alchemists AdMob
 *
 *  Created by Christian Herzog.
 *  Copyright 2011 Modern Alchemists. All rights reserved.
 *
 */

#ifndef MAAD_C
#define MAAD_C

//----------------------------------------------------------------------
#include "S3DXAIVariable.h"
#include "S3DClient_Wrapper.h"
//----------------------------------------------------------------------
#ifndef LOGD
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "MAAD-NATIVE", __VA_ARGS__)
#endif 
#ifndef LOGE
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "MAAD-NATIVE", __VA_ARGS__)
#endif 
//----------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif 
 
	//- helpers ------------------------------------------------------------
	static JavaVM *MAAD_JavaVM;
	
	// get Java Environment
	static JNIEnv *MAAD_getJNIEnv ( )
	{
		JNIEnv *pJNIEnv ;
		
		if ( MAAD_JavaVM && ( MAAD_JavaVM->GetEnv ( (void**) &pJNIEnv, JNI_VERSION_1_4 ) >= 0 ) )
		{
			return pJNIEnv ;
		}
		return NULL ;
	}
	

	// -- ShiVa > C > Java -------------------------------------------
	void AdMobRegisterPublisherCallback ( unsigned char _iArgumentCount, const void *_pArguments, void *_pUserData )
	{
	    if ( _pArguments && ( _iArgumentCount == 1 ) )
	    {
	        const S3DX::AIVariable *pVariables = (const S3DX::AIVariable *)_pArguments ;
	        
	        if ( pVariables[0].GetType ( ) == S3DX::AIVariable::eTypeString )
	        {
		        if ( MAAD_JavaVM )
		        {
		            JNIEnv *pEnv ;
		            if ( MAAD_JavaVM->GetEnv ( (void**) &pEnv, JNI_VERSION_1_4 ) >= 0 )
		            {
		                jclass pClass  = pEnv->FindClass ( "com/modernalchemists/maad/android/AdMobWrapper" );
		                if ( pClass != 0 )
		                {
		                    jmethodID pMethod = pEnv->GetStaticMethodID ( pClass, "registerPublisher", "(Ljava/lang/String;)V");
							if ( pMethod )
		                    {
								pEnv->CallStaticVoidMethod ( pClass, pMethod, pEnv->NewStringUTF ( pVariables[0].GetStringValue ( ) ) ) ;
		                    }
		                }
		            }
		        }
	        }
	    }
	}
	
	void AdMobSetVisibleCallback ( unsigned char _iArgumentCount, const void *_pArguments, void *_pUserData )
	{
		LOGD( "AdMobSetVisibleCallback" ) ;
	   
		if ( _pArguments && ( _iArgumentCount == 1 ) )
	    {
	        const S3DX::AIVariable *pVariables = (const S3DX::AIVariable *)_pArguments ;
	        
	        if ( pVariables[0].GetType ( ) == S3DX::AIVariable::eTypeBoolean )
	        {
	             //bAdMobWantVisible = pVariables[0].GetBooleanValue ( ) ;

				if ( MAAD_JavaVM )
		        {
		            JNIEnv *pEnv ;
		            if ( MAAD_JavaVM->GetEnv ( (void**) &pEnv, JNI_VERSION_1_4 ) >= 0 )
		            {
		                jclass pClass  = pEnv->FindClass ( "com/modernalchemists/maad/android/AdMobWrapper" );
		                if ( pClass != 0 )
		                {
		                    jmethodID pMethod = pEnv->GetStaticMethodID ( pClass, "setVisible", "(Z)V");
							if ( pMethod )
		                    {
								pEnv->CallStaticVoidMethod ( pClass, pMethod, pVariables[0].GetBooleanValue ( )  ) ;
		                    }
		                }
		            }
		        }

	        }
	    }
	}	
	
	
	
	// -- init - this is the method which starts it all --------------------
	void maad_registerCallbacks(JavaVM* pJavaVM)
	{
		LOGD("MAAD_registerCallbacks()");
		
		// init: set Java VM
		MAAD_JavaVM = pJavaVM;
		if(!MAAD_JavaVM) {
			LOGE("MAAD ERROR: Java VM is missing (null)!");	
			return;
		}
		
		// init: register ShiVa callbacks (java needs no callbacks, functions are called directly from JavaVM using the JNI API)
		S3DClient_InstallCurrentUserEventHook   ( "AdMob", "onRegisterPublisher", AdMobRegisterPublisherCallback, NULL ) ;
	    //S3DClient_InstallCurrentUserEventHook   ( "AdMob", "onRegisterUseTestAd", AdMobRegisterUseTestAdCallback, NULL ) ;
	    //S3DClient_InstallCurrentUserEventHook   ( "AdMob", "onRegisterBackColor", AdMobRegisterBackColorCallback, NULL ) ;
	    //S3DClient_InstallCurrentUserEventHook   ( "AdMob", "onRegisterTextColor", AdMobRegisterTextColorCallback, NULL ) ;
	    S3DClient_InstallCurrentUserEventHook   ( "AdMob", "onSetVisible",        AdMobSetVisibleCallback,        NULL ) ;
	}	

#ifdef __cplusplus
}
#endif 
	
#endif