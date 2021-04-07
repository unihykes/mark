

set SRC_PATH=%MK_PATH%/3rd_Party/protobuf/protobuf/cmake
set BUILD_PATH=%MK_DEPS_PKGS%/__build/protobuf
set PREFIX_PATH=%MK_DEPS_PKGS%/protobuf

mkdir %BUILD_PATH:/=\%
cd %BUILD_PATH%

set CMAKE_BUILD_TYPE=Release
set MAKE_VERSION=x64

cmake  -G  "Visual Studio 16 2019" -A x64  %SRC_PATH% ^
                    -DCMAKE_INSTALL_PREFIX=%PREFIX_PATH%  ^
                     -DBUILD_SHARED_LIBS=ON ^
                     -Dprotobuf_BUILD_TESTS=OFF

:: 执行编译
msbuild ALL_BUILD.vcxproj -p:Configuration=%CMAKE_BUILD_TYPE% -p:Platform=%MAKE_VERSION% -m:4  -verbosity:minimal

cd %MK_PATH%/3rd_Party/protobuf