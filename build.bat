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
:: Check SCons return value
:: NOTE: This does not work because return value will be from tee.exe
::----------------------------------------------------------------------------------------------------------------------------
:: if errorlevel 0 goto check_warnings
:: set BUILD_ERR = 1

::----------------------------------------------------------------------------------------------------------------------------
:: Check for any build tool warnings in the build log
:: Note: More text patterns can be concatenated to WRN_PATTERNS when needed
::----------------------------------------------------------------------------------------------------------------------------
:: :check_warnings
set COMPILER_WRN=warning:
set SCONS_WRN=Subcon builds might fail
set BUILD_WRN_PATTERNS="%COMPILER_WRN%|%SCONS_WRN%"
Tools\grep.exe -n -E %BUILD_WRN_PATTERNS% build.log > warnings.log
if errorlevel 1 goto check_for_errors

::Spam the output only if warnings were found
set BUILD_WRN=1
echo Checking the following text patterns from build.log "%COMPILER_WRN%", "%SCONS_WRN%"
echo.
echo Build tool warnings:
echo.
type warnings.log

if "%1"=="--ignore_warnings" goto warning_from_warnings
:: :error_from_warnings
echo.
echo *** ERROR: Build tools reported warning(s), please correct!
echo.
set BUILD_ERR=1
goto check_for_errors

:warning_from_warnings
echo.
echo *** WARNING: Build tools reported warning(s), please correct!
echo.
goto check_for_errors

::----------------------------------------------------------------------------------------------------------------------------
:: Check for a SCons error report in the build log
::----------------------------------------------------------------------------------------------------------------------------
:check_for_errors
set SCONS_ERR="*** ERROR:"
Tools\grep.exe -F "*** ERROR:" build.log > nul
if errorlevel 1 goto run_result

:: Print error messages from build log
set COMPILER_ERR=error:
set LINKER_ERR=error:
::set LINKER_ERR=/       NOTE: This happens to work with gcc in Windows
set BUILD_ERR_PATTERNS="%COMPILER_ERR%|%LINKER_ERR%"

Tools\grep.exe -n -E %BUILD_ERR_PATTERNS% build.log

:: Print the SCons error message again if warnings spammed the output
echo.
if %BUILD_WRN%==1 echo *** ERROR: Build has errors, please correct!
set BUILD_ERR=1

::----------------------------------------------------------------------------------------------------------------------------
:: Run result
::----------------------------------------------------------------------------------------------------------------------------
:run_result
echo Result:
program
echo UnitTest:
unittest_SimpleMath
goto end
::****************************************************************************************************************************
:: END
::****************************************************************************************************************************
:end
exit /B %BUILD_ERR%

pause