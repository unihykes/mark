:: debug | release
set CMAKE_BUILD_TYPE=Debug

::64 | 32
set CMAKE_BUILD_VERSION=i386

::build|target
set CUR_CMAKELISTS_PATH=%cd%\wxWidgets
set BUILD_TEMP=%CUR_CMAKELISTS_PATH%\..\build_temp
set BUILD_TARGET=%CUR_CMAKELISTS_PATH%\..\build_target


::call vs
if "%CMAKE_BUILD_VERSION%" == "x64" (
    set MAKE_VERSION=x64
    set CMAKE_GENERATOR="Visual Studio 14 2015 Win64"
    call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat" x64
)
if "%CMAKE_BUILD_VERSION%" == "i386" (
    set MAKE_VERSION=x86
    set CMAKE_GENERATOR="Visual Studio 14 2015"
    call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat" x86
)


:make
if not exist %BUILD_TEMP% (
    mkdir %BUILD_TEMP%
)
cd %BUILD_TEMP%

if not exist ALL_BUILD.vcxproj (
    cmake -T v140_xp -G%CMAKE_GENERATOR%  %* %CUR_CMAKELISTS_PATH% ^
    -DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE% ^
    -DAUTO_RUN=0 ^
    -DwxBUILD_MONOLITHIC=ON ^
    -DCMAKE_INSTALL_PREFIX=%BUILD_TARGET%
)

::msbuild ALL_BUILD.vcxproj /nologo /p:Configuration=%CMAKE_BUILD_TYPE% /p:Platform=%MAKE_VERSION% /m  /verbosity:minimal
cmake --build . --target install
goto make_end


:make_end
echo ** ---make end------
@echo on
cd %CUR_CMAKELISTS_PATH%
cd..
