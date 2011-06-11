//-----------------------------------------------------------
// Mortar Patching Language v0.8.
//-----------------------------------------------------------
// Commands:
// LOG: log message
// COF: copy file
// RIF: replace in file
// IFA: insert file after
// IFB: insert file before
// ISA: insert string after
// ISB: insert string before

// Variables:
// %GAME%: YourGame.java
// %GAMEDIR%: Dir YourGame.java is in
// %PROJ%: Path to project 
// %SRC%: Path to src folder
// %MORTAR_BIN%: Path to Mortar/bin
// %MORTAR_PATCHES%: Path to Mortar/bin/patches
// %THIS%: dir, in which this PAT file is in.

//Code Hookups:
// TODO...as variables
// e.g.: @@ACTIVITY STARTED etc.
// Not needed for first iteration though...


//#################################

LOG Starting Admob patching process...

COF %THIS%/admob-sdk-android.jar 		§§§ %PROJ%/libs/admob.jar
COF %THIS%/AdMobWrapper.java 			§§§ %PROJ%/src/com/modernalchemists/maad/android/AdMobWrapper.java
COF %THIS%/maad.c						§§§ %PROJ%/jni/maad.c


ISB %PROJ%/.classpath §§§ </classpath> §§§ <classpathentry kind="lib" exported="true" path="libs/admob.jar"/>\n

//Game.java:
IFA %GAME%	§§§	%THIS%/java_import_a.txt 		§§§ %THIS%/java_import_i.txt
IFA %GAME%	§§§ %THIS%/java_view_a.txt 			§§§ %THIS%/java_view_i.txt
IFB %GAME%	§§§ %THIS%/java_visible_b.txt 		§§§ %THIS%/java_visible_i.txt
IFA %GAME%	§§§ %THIS%/java_addToView_a.txt 	§§§ %THIS%/java_addToView_i.txt


//Manifest.xml:
IFA %PROJ%/AndroidManifest.xml §§§ %THIS%/amanifest_inet_a.txt §§§ %THIS%/amanifest_inet_i.txt
IFB %PROJ%/AndroidManifest.xml §§§ %THIS%/amanifest_puid_b.txt §§§ %THIS%/amanifest_puid_i.txt

//JNI:
IFA %PROJ%/jni/S3DClient.cpp §§§ %THIS%/cpp_client_include_a.txt 	§§§ %THIS%/cpp_client_include_i.txt
IFA %PROJ%/jni/S3DClient.cpp §§§ %THIS%/cpp_client_load_a.txt 		§§§ %THIS%/cpp_client_load_i.txt
