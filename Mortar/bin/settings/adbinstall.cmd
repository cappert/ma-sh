:: Just some debug output:
echo Attempting to install file: %1
 
:: Install file:
"%ANDROID_SDK_HOME%\tools\adb" install -r "%1"
::PAUSE