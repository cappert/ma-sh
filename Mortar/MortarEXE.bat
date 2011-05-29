@echo off

:: AIR application packaging
:: More information:
:: http://livedocs.adobe.com/flex/3/html/help.html?content=CommandLineTools_5.html#1035959

:: adt -package -storetype pkcs12 -keystore myCert.p12 
:: -target native NativeProcessTest.exe NativeProcessTest-app.xml 
:: NativeProcessTest.swf NativeApps/Windows/bin/echoTestWindows icons

:: Path to Flex SDK binaries
set PATH=%PATH%;D:\flex_sdk_4.1.0.16076\bin

:: Signature (see 'CreateCertificate.bat')
set CERTIFICATE="Mortar.pfx"
set SIGNING_OPTIONS=-storetype pkcs12 -keystore %CERTIFICATE% -target native 
if not exist %CERTIFICATE% goto certificate

:: Output
if not exist air md air
set AIR_FILE=air/Mortar.air

:: Input
set APP_XML=application.xml 
set FILE_OR_DIR=-C bin .

echo Signing AIR setup using certificate %CERTIFICATE%.
::call adt -package %SIGNING_OPTIONS% %AIR_FILE% %APP_XML% %FILE_OR_DIR%
::call adt -package  %SIGNING_OPTIONS% bin/Mortar.exe  bin/Mortar.swf 
::NativeApps/Windows/bin/echoTestWindows icons
::call adt -package -storetype pkcs12 -keystore %CERTIFICATE% -target native -storetype pkcs12 -keystore %CERTIFICATE% Mortar.exe APP_XML index.html resources

::call adt -package -storetype pkcs12 -keystore %CERTIFICATE% -target native -storetype pkcs12 -keystore %CERTIFICATE% Mortar.exe %APP_XML% index.html bin

::Works:
::call adt -package -storetype pkcs12 -keystore %CERTIFICATE% -target native Mortar.exe  %APP_XML% %FILE_OR_DIR%
call adt -package -storetype pkcs12 -keystore %CERTIFICATE% -target native -storetype pkcs12 -keystore %CERTIFICATE% Mortar.exe %APP_XML% %FILE_OR_DIR%





if errorlevel 1 goto failed

echo.
echo AIR setup created: %AIR_FILE%
echo.
goto end

:certificate
echo Certificate not found: %CERTIFICATE%
echo.
echo Troubleshotting: 
echo A certificate is required, generate one using 'CreateCertificate.bat'
echo.
goto end

:failed
echo AIR setup creation FAILED.
echo.
echo Troubleshotting: 
echo did you configure the Flex SDK path in this Batch file?
echo.

:end
pause
