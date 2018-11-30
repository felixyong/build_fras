@echo off
::----------------------------------------------------------------------------------------------------------------------------
:: Set Python directory unless already set *PYTHONDIR is defined as PC's environment variable
::----------------------------------------------------------------------------------------------------------------------------
setlocal
if "%PYTHONDIR%"=="" (
    set PYTHONDIR=C:\build\ACS580MV-v1\Python27
) else (
    echo build.bat: Python directory set by environment variable PYTHONDIR: %PYTHONDIR%
)

if NOT exist "%PYTHONDIR%" (
    echo build.bat: Invalid python directory: %PYTHONDIR%
    goto end:
)

::----------------------------------------------------------------------------------------------------------------------------
:: Use the default SCons version unless a specific version already set
::----------------------------------------------------------------------------------------------------------------------------
if "%SCONS_VERSION%"=="" (
    set SCONS_SCRIPT=%PYTHONDIR%\Scripts\scons.py
) else (
    echo build.bat: SCons version set by environment variable SCONS_VERSION: %SCONS_VERSION%
    set SCONS_SCRIPT=%PYTHONDIR%\Scripts\scons-%SCONS_VERSION%.py
)

if NOT exist "%SCONS_SCRIPT%" (
    echo build.bat: SCons not found: %SCONS_SCRIPT%
    goto end:
)

::----------------------------------------------------------------------------------------------------------------------------
:: Check path variables
::----------------------------------------------------------------------------------------------------------------------------
if exist "%PYTHONDIR%" goto env_ok

echo build.bat: Invalid PYTHONDIR definition! ( %PYTHONDIR% )
EXIT /B 1

:env_ok
:: Print build tool version information
echo build.bat (INFO):
echo Software construction tool versions:
call %PYTHONDIR%\python.exe -V
call %PYTHONDIR%\python.exe %SCONS_SCRIPT% -version
echo.

::----------------------------------------------------------------------------------------------------------------------------
:: Build with SCons
::----------------------------------------------------------------------------------------------------------------------------
set BUILD_ERR=0
set BUILD_WRN=0
call %PYTHONDIR%\python.exe %SCONS_SCRIPT% %* 2>&1 | Tools\tee.exe build.log

::----------------------------------------------------------------------------------------------------------------------------
:: Run result
::----------------------------------------------------------------------------------------------------------------------------
echo Result:
program
echo UnitTest:
unittest_SimpleMath
clPICtrl_UnitTest

::****************************************************************************************************************************
:: END
::****************************************************************************************************************************
:end
exit /B %BUILD_ERR%