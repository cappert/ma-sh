@echo off

:: AIR certificate generator
:: More information:
:: http://livedocs.adobe.com/flex/3/html/help.html?content=CommandLineTools_5.html#1035959
:: http://livedocs.adobe.com/flex/3/html/distributing_apps_4.html#1037515

:: Path to Flex SDK binaries
set PATH=%PATH%;D:\SDK\flex_sdk_4.1.0.16076\bin
::set PATH=%PATH%;D:\flex_sdk_4.1.0.16076\bin

:: Certificate information
set NAME="Mortar"
set PASSWORD=fd
set CERTIFICATE="Mortar.pfx"

call adt -certificate -cn %NAME% 1024-RSA %CERTIFICATE% %PASSWORD%
if errorlevel 1 goto failed

echo.
echo Certificate created: %CERTIFICATE%
echo With password: %PASSWORD%
if "%PASSWORD%" == "fd" echo (WARNING: you did not change the default password)
echo.
echo Hint: you may have to wait a few minutes before using this certificate to build your AIR application setup.
echo.
goto end

:failed
echo.
echo Certificate creation FAILED.
echo.
echo Troubleshotting: did you configure the Flex SDK path in this Batch file?
echo.

:end
pause