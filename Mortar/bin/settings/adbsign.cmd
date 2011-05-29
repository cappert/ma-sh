:: Just some debug output:
::echo Attempting to sign file: %1
::echo Keystore: %2
::echo Pass: %3
::echo Alias: %4
 
"%JAVA_HOME%\bin\jarsigner" -verbose -keystore "%2" -storepass "%3" -keypass "%3" "%1" "%4"

echo VERIFY IF SIGNED WORKED:
"%JAVA_HOME%\bin\jarsigner" -verify "%1"

::PAUSE