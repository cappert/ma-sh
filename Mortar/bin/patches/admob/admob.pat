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

LOG Starting Admob patching process...

//copyFile( ADMOB_JAR, PROJ_PATH + "/libs/admob.jar" );
//COF fileFrom fileTo
COF %THIS%/admob-sdk-android.jar 			§§§ %PROJ%/libs/admob.jar
COF D:\Program Files\Common Files\test.txt 	§§§ %PROJ%/misc.txt

//Replace in file:
//replaceInFile( PROJ_PATH + "/AndroidManifest.xml", "android:launchMode=\"singleInstance\"",	"android:launchMode=\"standard\"" );
//RIF file findString replaceItWith
RIF myFile.xml §§§ The string to find §§§ The string to replace it with...

//IFA after insert
IFA %GAME%			§§§	java_import_a.txt 	§§§ java_import_i.txt
IFB %PROJ%/test		§§§	java_visible_b.txt 	§§§ java_visible_i.txt

ISA %GAME%			§§§	java_import_a.txt 	§§§ java_import_i.txt
ISB %PROJ%/test		§§§	java_visible_b.txt 	§§§ java_visible_i.txt