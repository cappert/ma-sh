/*
 *  maof.c
 *  Modern Alchemists OpenFeint
 *
 *  Created by Christian Herzog.
 *  Copyright 2011 Modern Alchemists. All rights reserved.
 *
 */

#ifndef MAOF_C
#define MAOF_C

//----------------------------------------------------------------------
#include "S3DXAIVariable.h"
#include "S3DClient_Wrapper.h"
//----------------------------------------------------------------------
#ifndef LOGD
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "MAOF-NATIVE", __VA_ARGS__)
#endif 
#ifndef LOGE
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "MAOF-NATIVE", __VA_ARGS__)
#endif 
//----------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif 
 
	//- helpers ------------------------------------------------------------
	static JavaVM *maof_JavaVM;
	
	// get Java Environment
	static JNIEnv *maof_getJNIEnv ( )
	{
		JNIEnv *pJNIEnv ;
		
		if ( maof_JavaVM && ( maof_JavaVM->GetEnv ( (void**) &pJNIEnv, JNI_VERSION_1_4 ) >= 0 ) )
		{
			return pJNIEnv ;
		}
		return NULL ;
	}
	

	// -- ShiVa > C > Java -------------------------------------------
	void onInitMAOF(unsigned char argumentCount, const void *arguments, void *userData )
	{
		//Args: sProductKey sSecret sName
		LOGD("onInitMAOF()");
		LOGD("#################################################");
		LOGD("WARNING: onInitMAOF currently not supported on Android! You need to use the static config!");
		LOGD("#################################################");

		// get Java Environment
		JNIEnv* pJNIEnv = maof_getJNIEnv ( ) ;
		if(!pJNIEnv) {
			LOGE("MAOF ERROR: Java Environment is missing (null)!");	
			return;
		}
		
		if ( arguments && ( argumentCount == 4 ) )
		{
			const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
			
			if ( ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString )
				&& ( variables[1].GetType ( ) == S3DX::AIVariable::eTypeString )
				&& ( variables[2].GetType ( ) == S3DX::AIVariable::eTypeString )
				&& ( variables[3].GetType ( ) == S3DX::AIVariable::eTypeString )  )
			{
				LOGD(variables[0].GetStringValue());
				
				// JAVA -> get Product INFO
				//jclass    pJNIActivityClass = pJNIEnv->FindClass ( "com/modernalchemists/maof/android/OpenFeintWrapper" ) ;
				//jmethodID pJNIMethodID		= pJNIEnv->GetStaticMethodID ( pJNIActivityClass, "initOF", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" ) ;
				//pJNIEnv->CallStaticVoidMethod ( pJNIActivityClass, pJNIMethodID, pJNIEnv->NewStringUTF ( variables[0].GetStringValue() ), pJNIEnv->NewStringUTF ( variables[1].GetStringValue() ), pJNIEnv->NewStringUTF ( variables[2].GetStringValue() ), pJNIEnv->NewStringUTF ( variables[3].GetStringValue() ) ) ;
			}
		}
	}

	void onShutdownMAOF(unsigned char argumentCount, const void *arguments, void *userData )
	{
		LOGD("C - onShutdownMAOF()");
		
		// get Java Environment
		JNIEnv* pJNIEnv = maof_getJNIEnv ( ) ;
		if(!pJNIEnv) {
			LOGE("MAOF ERROR: Java Environment is missing (null)!");	
			return;
		}

		jclass    pJNIActivityClass = pJNIEnv->FindClass ( "com/modernalchemists/maof/android/OpenFeintWrapper" ) ;
		jmethodID pJNIMethodID		= pJNIEnv->GetStaticMethodID ( pJNIActivityClass, "shutdownOF", "()V" ) ;
		pJNIEnv->CallStaticVoidMethod ( pJNIActivityClass, pJNIMethodID ) ;
	}	
	
	void onLaunchDashboard(unsigned char argumentCount, const void *arguments, void *userData )
	{
		LOGD("C - onLaunchDashboard()");
		
		// get Java Environment
		JNIEnv* pJNIEnv = maof_getJNIEnv ( ) ;
		if(!pJNIEnv) {
			LOGE("MAOF ERROR: Java Environment is missing (null)!");	
			return;
		}

		jclass    pJNIActivityClass = pJNIEnv->FindClass ( "com/modernalchemists/maof/android/OpenFeintWrapper" ) ;
		jmethodID pJNIMethodID		= pJNIEnv->GetStaticMethodID ( pJNIActivityClass, "launchDashboard", "()V" ) ;
		pJNIEnv->CallStaticVoidMethod ( pJNIActivityClass, pJNIMethodID ) ;
	}

	void onLaunchDashboardWithHighscorePage(unsigned char argumentCount, const void *arguments, void *userData )
	{
		//Args: sProductKey sSecret sName
		LOGD("onLaunchDashboardWithHighscorePage()");

		// get Java Environment
		JNIEnv* pJNIEnv = maof_getJNIEnv ( ) ;
		if(!pJNIEnv) {
			LOGE("MAOF ERROR: Java Environment is missing (null)!");	
			return;
		}
		
		if ( arguments && ( argumentCount == 1 ) )
		{
			const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
			
			if ( ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString ) )
			{
				LOGD(variables[0].GetStringValue());
				
				// JAVA -> get Product INFO
				jclass    pJNIActivityClass = pJNIEnv->FindClass ( "com/modernalchemists/maof/android/OpenFeintWrapper" ) ;
				jmethodID pJNIMethodID		= pJNIEnv->GetStaticMethodID ( pJNIActivityClass, "launchDashboardWithHighscorePage", "(Ljava/lang/String;)V" ) ;
				pJNIEnv->CallStaticVoidMethod ( pJNIActivityClass, pJNIMethodID, pJNIEnv->NewStringUTF ( variables[0].GetStringValue() ) ) ;
			}
		}
	}
	
	void onSubmitHighscore(unsigned char argumentCount, const void *arguments, void *userData )
	{
		//SubmitHighscore nScore, sId
	
		//Args: sProductKey sSecret sName
		LOGD("onSubmitHighscore()");

		// get Java Environment
		JNIEnv* pJNIEnv = maof_getJNIEnv ( ) ;
		if(!pJNIEnv) {
			LOGE("MAOF ERROR: Java Environment is missing (null)!");	
			return;
		}
		
		if ( arguments && ( argumentCount == 2 ) )
		{
			const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
			
			if ( ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeNumber )
				&& ( variables[1].GetType ( ) == S3DX::AIVariable::eTypeString ) )
			{
				// JAVA -> get Product INFO
				jclass    pJNIActivityClass = pJNIEnv->FindClass ( "com/modernalchemists/maof/android/OpenFeintWrapper" ) ;
				jmethodID pJNIMethodID		= pJNIEnv->GetStaticMethodID ( pJNIActivityClass, "submitHighscore", "(FLjava/lang/String;)V" ) ;
				pJNIEnv->CallStaticVoidMethod ( pJNIActivityClass, pJNIMethodID, variables[0].GetNumberValue(), pJNIEnv->NewStringUTF ( variables[1].GetStringValue() ) ) ;
			}
		}
	}	
	
	void onUnlockAchievement(unsigned char argumentCount, const void *arguments, void *userData )
	{
		//UnlockAchievement sId, nProgress, bShowNotification, bDeferred  //ACHTUNG: nProgress von 0.0 bis 100.0!
	
		//Args: sProductKey sSecret sName
		LOGD("onUnlockAchievement()");

		// get Java Environment
		JNIEnv* pJNIEnv = maof_getJNIEnv ( ) ;
		if(!pJNIEnv) {
			LOGE("MAOF ERROR: Java Environment is missing (null)!");	
			return;
		}
		
		if ( arguments && ( argumentCount == 4 ) )
		{
			const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
			
			if ( ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString )
				&& ( variables[1].GetType ( ) == S3DX::AIVariable::eTypeNumber ) 
				&& ( variables[2].GetType ( ) == S3DX::AIVariable::eTypeBoolean ) 
				&& ( variables[3].GetType ( ) == S3DX::AIVariable::eTypeBoolean ) )
			{
				// JAVA -> get Product INFO
				jclass    pJNIActivityClass = pJNIEnv->FindClass ( "com/modernalchemists/maof/android/OpenFeintWrapper" ) ;
				jmethodID pJNIMethodID		= pJNIEnv->GetStaticMethodID ( pJNIActivityClass, "unlockAchievement", "(Ljava/lang/String;FZZ)V" ) ;
				pJNIEnv->CallStaticVoidMethod ( pJNIActivityClass, pJNIMethodID, 
					pJNIEnv->NewStringUTF ( variables[0].GetStringValue() ),
					variables[1].GetNumberValue(), 
					variables[2].GetBooleanValue(), 
					variables[3].GetBooleanValue() 
				) ;
			}
		}
	}	
	
	void onFlushUnlockedAchievements(unsigned char argumentCount, const void *arguments, void *userData )
	{
		LOGD("C - onFlushUnlockedAchievements()");
		
		// get Java Environment
		JNIEnv* pJNIEnv = maof_getJNIEnv ( ) ;
		if(!pJNIEnv) {
			LOGE("MAOF ERROR: Java Environment is missing (null)!");	
			return;
		}

		jclass    pJNIActivityClass = pJNIEnv->FindClass ( "com/modernalchemists/maof/android/OpenFeintWrapper" ) ;
		jmethodID pJNIMethodID		= pJNIEnv->GetStaticMethodID ( pJNIActivityClass, "flushUnlockedAchievements", "()V" ) ;
		pJNIEnv->CallStaticVoidMethod ( pJNIActivityClass, pJNIMethodID ) ;
	}	
	
	// -- JAVA > C > ShiVa -------------------------------------------
	// Nothing todo... =)
	
	
	// -- init - this is the method which starts it all --------------------
	void maof_registerCallbacks(JavaVM* pJavaVM)
	{
		LOGD("maof_registerCallbacks()");
		
		// init: set Java VM
		maof_JavaVM = pJavaVM;
		if(!maof_JavaVM) {
			LOGE("MAOF ERROR: Java VM is missing (null)!");	
			return;
		}
		
		// init: register ShiVa callbacks (java needs no callbacks, functions are called directly from JavaVM using the JNI API)
		S3DClient_InstallCurrentUserEventHook("MAOF", "onInitMAOF",							onInitMAOF,							NULL);
		S3DClient_InstallCurrentUserEventHook("MAOF", "onShutdownMAOF",						onShutdownMAOF,						NULL);
		
		S3DClient_InstallCurrentUserEventHook("MAOF", "onLaunchDashboard",					onLaunchDashboard,					NULL);
		S3DClient_InstallCurrentUserEventHook("MAOF", "onLaunchDashboardWithHighscorePage",	onLaunchDashboardWithHighscorePage,	NULL);
		
		//S3DClient_InstallCurrentUserEventHook("MAOF", "onSendSocialNotification",			onSendSocialNotification,			NULL);
		S3DClient_InstallCurrentUserEventHook("MAOF", "onSubmitHighscore",					onSubmitHighscore,					NULL);
		S3DClient_InstallCurrentUserEventHook("MAOF", "onUnlockAchievement",				onUnlockAchievement,				NULL);
		S3DClient_InstallCurrentUserEventHook("MAOF", "onFlushUnlockedAchievements",		onFlushUnlockedAchievements,		NULL);
	}	

#ifdef __cplusplus
}
#endif 
	
#endif