//##########################################################
//pre.pat
//If you use any JNI stuff, you probably need to include this patch in your patching process.
//##########################################################

LOG Starting pre patch...

COF %THIS%/S3DXAIConstant.h		§§§ %PROJ%/jni/S3DXAIConstant.h
COF %THIS%/S3DXAIEngineAPI.h	§§§ %PROJ%/jni/S3DXAIEngineAPI.h
COF %THIS%/S3DXAIFunction.h		§§§ %PROJ%/jni/S3DXAIFunction.h
COF %THIS%/S3DXAIModel.h		§§§ %PROJ%/jni/S3DXAIModel.h
COF %THIS%/S3DXAIPackage.h		§§§ %PROJ%/jni/S3DXAIPackage.h
COF %THIS%/S3DXAIVariable.h	 	§§§ %PROJ%/jni/S3DXAIVariable.h
COF %THIS%/S3DXAIVariables.h	§§§ %PROJ%/jni/S3DXAIVariables.h
COF %THIS%/S3DXConfig.h 		§§§ %PROJ%/jni/S3DXConfig.h
COF %THIS%/S3DXMacros.h 		§§§ %PROJ%/jni/S3DXMacros.h
COF %THIS%/S3DXPlatform.h	 	§§§ %PROJ%/jni/S3DXPlatform.h
COF %THIS%/S3DXPlugin.h 		§§§ %PROJ%/jni/S3DXPlugin.h
COF %THIS%/S3DXTypes.h	 		§§§ %PROJ%/jni/S3DXTypes.h

RIF %PROJ%/AndroidManifest.xml §§§ android:launchMode="singleInstance" §§§ android:launchMode="standard"

IFA %PROJ%/jni/S3DClient.cpp §§§ %THIS%/cpp_client_header_a.txt 	§§§ %THIS%/cpp_client_header_i.txt
