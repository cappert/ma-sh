/*
 *  mass.h
 *  Modern Alchemists Store for Shiva
 *
 *  Created by Georg  Kamptner on 06/04/11.
 *  Copyright 2010 Modern Alchemists. All rights reserved.
 *
 */

#ifndef MASS_C
#define MASS_C

//----------------------------------------------------------------------
#include "S3DXAIVariable.h"
#include "S3DClient_Wrapper.h"
//----------------------------------------------------------------------
#ifndef LOGD
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "MASS-NATIVE", __VA_ARGS__)
#endif 
#ifndef LOGE
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "MASS-NATIVE", __VA_ARGS__)
#endif 
//----------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif 
 
	//- helpers ------------------------------------------------------------
	static JavaVM *mass_JavaVM;
	
	// get Java Environment
	static JNIEnv *mass_getJNIEnv ( )
	{
		JNIEnv *pJNIEnv ;
		
		if ( mass_JavaVM && ( mass_JavaVM->GetEnv ( (void**) &pJNIEnv, JNI_VERSION_1_4 ) >= 0 ) )
		{
			return pJNIEnv ;
		}
		return NULL ;
	}
	

	// -- ShiVa > C > Java -------------------------------------------
	void onRequestProductHandle(unsigned char argumentCount, const void *arguments, void *userData )
	{
		LOGD("onRequestProductHandle()");
		
		// deprecated
		LOGE("onRequestProductHandle() is deprecated, do not use it!");
	}

	void onRequestProductInfo(unsigned char argumentCount, const void *arguments, void *userData )
	{
		LOGD("onRequestProductInfo()");
		
		// get Java Environment
		JNIEnv* pJNIEnv = mass_getJNIEnv ( ) ;
		if(!pJNIEnv) {
			LOGE("MASS ERROR: Java Environment is missing (null)!");	
			return;
		}
		
		if ( arguments && ( argumentCount == 1 ) )
		{
			const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
			
			if ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString )
			{
				LOGD(variables[0].GetStringValue());
				
				// JAVA -> get Product INFO
				jclass    pJNIActivityClass = pJNIEnv->FindClass ( "com/modernalchemists/mass/android/Store" ) ;
				jmethodID pJNIMethodID		= pJNIEnv->GetStaticMethodID ( pJNIActivityClass, "requestProductInfo", "(Ljava/lang/String;)V" ) ;
				pJNIEnv->CallStaticVoidMethod ( pJNIActivityClass, pJNIMethodID, pJNIEnv->NewStringUTF ( variables[0].GetStringValue() ) ) ;
			}
		}
	}

	void onRequestProductPurchase(unsigned char argumentCount, const void *arguments, void *userData)
	{
		LOGD("onRequestProductPurchase()");
	
		// get Java Environment
		JNIEnv* pJNIEnv = mass_getJNIEnv ( ) ;
		if(!pJNIEnv) {
			LOGE("MASS ERROR: Java Environment is missing (null)!");	
			return;
		}
	
		if ( arguments && ( argumentCount == 1 ) )
		{
			const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
			
			if ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString )
			{
				LOGD(variables[0].GetStringValue());
				
				// JAVA -> buy Product
				jclass    pJNIActivityClass = pJNIEnv->FindClass ( "com/modernalchemists/mass/android/Store" ) ;
				jmethodID pJNIMethodID		= pJNIEnv->GetStaticMethodID ( pJNIActivityClass, "buyProduct", "(Ljava/lang/String;)V" ) ;
				pJNIEnv->CallStaticVoidMethod ( pJNIActivityClass, pJNIMethodID, pJNIEnv->NewStringUTF ( variables[0].GetStringValue() ) ) ;
				
				//S3DClient_SendEventToCurrentUser("MASS", "onDeliverProductHandle", 1, &variable); // deprecated
			}
		}
	}
	
	
	// -- JAVA > C > ShiVa -------------------------------------------
	JNIEXPORT void JNICALL Java_com_modernalchemists_mass_android_Store_productInfoCallback( JNIEnv* env, jobject thiz, jstring id, jstring title, jstring description, jstring price )
	{
		LOGD("MASS: productInfoCallback()");
	
		// convert jstring(s) to char*(s)
		const char* sId 		 = env->GetStringUTFChars(id, NULL);
		const char* sTitle 		 = env->GetStringUTFChars(title, NULL);
		const char* sDescription = env->GetStringUTFChars(description, NULL);
		const char* sPrice 		 = env->GetStringUTFChars(price, NULL);
		
		S3DX::AIVariable variables[5];
		
		// nHandle, sId, sName, nPrice 
		variables[0].SetNumberValue(0); // handle is deprectaed
		variables[1].SetStringValue(sId);
		variables[2].SetStringValue(sTitle);
		variables[3].SetStringValue(sPrice);
		variables[4].SetStringValue(sDescription);
		
		S3DClient_SendEventToCurrentUser("MASS", "onDeliverProductInfo", 5, &variables);
		
		// release strings
		if ( sId ) env->ReleaseStringUTFChars ( id, sId ) ;
		if ( sTitle ) env->ReleaseStringUTFChars ( title, sTitle ) ;
		if ( sDescription ) env->ReleaseStringUTFChars ( description, sDescription ) ;
		if ( sPrice ) env->ReleaseStringUTFChars ( price, sPrice ) ;
	}
	
	JNIEXPORT void JNICALL Java_com_modernalchemists_mass_android_Store_productBoughtCallback( JNIEnv* env, jobject thiz, jstring id, jstring title, jstring description, jstring price )
	{
		LOGD("MASS: productBoughtCallback()");
		
		// convert jstring(s) to char*(s)
		const char* sId 		 = env->GetStringUTFChars(id, NULL);
		const char* sTitle 		 = env->GetStringUTFChars(title, NULL);
		const char* sDescription = env->GetStringUTFChars(description, NULL);
		const char* sPrice 		 = env->GetStringUTFChars(price, NULL);
		
		S3DX::AIVariable variables[5];
		
		// nHandle, sId, sName, nPrice 
		variables[0].SetNumberValue(0); // handle is deprectaed
		variables[1].SetStringValue(sId);
		variables[2].SetStringValue(sTitle);
		variables[3].SetStringValue(sPrice);
		variables[4].SetStringValue(sDescription);
		
		S3DClient_SendEventToCurrentUser("MASS", "onPerformProductPurchase", 5, &variables);	
		
		// release strings
		if ( sId ) env->ReleaseStringUTFChars ( id, sId ) ;
		if ( sTitle ) env->ReleaseStringUTFChars ( title, sTitle ) ;
		if ( sDescription ) env->ReleaseStringUTFChars ( description, sDescription ) ;
		if ( sPrice ) env->ReleaseStringUTFChars ( price, sPrice ) ;
	}
	
	JNIEXPORT void JNICALL Java_com_modernalchemists_mass_android_Store_transactionFailedCallback( JNIEnv* env, jobject thiz, jstring id, jstring title, jstring description, jstring price )
	{
		LOGD("MASS: transactionFailedCallback()");
	
		// convert jstring(s) to char*(s)
		const char* sId 		 = env->GetStringUTFChars(id, NULL);
		const char* sTitle 		 = env->GetStringUTFChars(title, NULL);
		const char* sDescription = env->GetStringUTFChars(description, NULL);
		const char* sPrice 		 = env->GetStringUTFChars(price, NULL);
		
		S3DX::AIVariable variables[5];
		
		// nHandle, sId, sName, nPrice 
		variables[0].SetNumberValue(0); // handle is deprectaed
		variables[1].SetStringValue(sId);
		variables[2].SetStringValue(sTitle);
		variables[3].SetStringValue(sPrice);
		variables[4].SetStringValue(sDescription);
		
		S3DClient_SendEventToCurrentUser("MASS", "onTransactionFailed", 5, &variables);	
		
		// release strings
		if ( sId ) env->ReleaseStringUTFChars ( id, sId ) ;
		if ( sTitle ) env->ReleaseStringUTFChars ( title, sTitle ) ;
		if ( sDescription ) env->ReleaseStringUTFChars ( description, sDescription ) ;
		if ( sPrice ) env->ReleaseStringUTFChars ( price, sPrice ) ;
	}
	
	JNIEXPORT void JNICALL Java_com_modernalchemists_mass_android_Store_productRefundedCallback( JNIEnv* env, jobject thiz, jstring id, jstring title, jstring description, jstring price )
	{
		LOGD("MASS: productRefundedCallback()");
	
		// convert jstring(s) to char*(s)
		const char* sId 		 = env->GetStringUTFChars(id, NULL);
		const char* sTitle 		 = env->GetStringUTFChars(title, NULL);
		const char* sDescription = env->GetStringUTFChars(description, NULL);
		const char* sPrice 		 = env->GetStringUTFChars(price, NULL);
		
		S3DX::AIVariable variables[5];
		
		// nHandle, sId, sName, nPrice 
		variables[0].SetNumberValue(0); // handle is deprectaed
		variables[1].SetStringValue(sId);
		variables[2].SetStringValue(sTitle);
		variables[3].SetStringValue(sPrice);
		variables[4].SetStringValue(sDescription);

		// TODO: implement in ShiVa MASS	
		S3DClient_SendEventToCurrentUser("MASS", "onPerformProductRefund", 5, &variables);	
		
		// release strings
		if ( sId ) env->ReleaseStringUTFChars ( id, sId ) ;
		if ( sTitle ) env->ReleaseStringUTFChars ( title, sTitle ) ;
		if ( sDescription ) env->ReleaseStringUTFChars ( description, sDescription ) ;
		if ( sPrice ) env->ReleaseStringUTFChars ( price, sPrice ) ;
	}
	
	
	// -- init - this is the method which starts it all --------------------
	void mass_registerCallbacks(JavaVM* pJavaVM)
	{
		LOGD("mass_registerCallbacks()");
		
		// init: set Java VM
		mass_JavaVM = pJavaVM;
		if(!mass_JavaVM) {
			LOGE("MASS ERROR: Java VM is missing (null)!");	
			return;
		}
		
		// init: register ShiVa callbacks (java needs no callbacks, functions are called directly from JavaVM using the JNI API)
		S3DClient_InstallCurrentUserEventHook("MASS", "onRequestProductInfo",		onRequestProductInfo,		NULL);
		S3DClient_InstallCurrentUserEventHook("MASS", "onRequestProductPurchase",	onRequestProductPurchase,	NULL);
		S3DClient_InstallCurrentUserEventHook("MASS", "onRequestProductHandle",		onRequestProductHandle,		NULL); // deprecated
	}	

#ifdef __cplusplus
}
#endif 
	
#endif