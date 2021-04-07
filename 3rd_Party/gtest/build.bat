

set SRC_PATH=%MK_PATH%/3rd_Party/gtest/googletest/googletest
set BUILD_PATH=%MK_DEPS_PKGS%\__build\gtest
set PREFIX_PATH=%MK_DEPS_PKGS%/gtest

mkdir %BUILD_PATH:/=\%
cd %BUILD_PATH%

set CMAKE_BUILD_TYPE=Release
set MAKE_VERSION=x64

::SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4819")
::

cmake  -G  "Visual Studio 16 2019" -A x64  %SRC_PATH% ^
                    -DCMAKE_INSTALL_PREFIX=%PREFIX_PATH%  ^
                    -DBUILD_SHARED_LIBS=ON  ^
                    -DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE%  ^
                    
:: ÷¥––±‡“Î
msbuild ALL_BUILD.vcxproj -p:Configuration=%CMAKE_BUILD_TYPE% -p:Platform=%MAKE_VERSION% -m:4  -verbosity:minimal

cd %MK_PATH%/3rd_Party/gtest