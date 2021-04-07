#!/bin/sh

#开启回显
set -x

#参数检查
if [ "$1" = "32" ];
then
    export MK_SYSTEM_TYPE=i386
else
	export MK_SYSTEM_TYPE=x64
fi


# 进入根目录
cd ../../

#设置环境变量
export MK_PATH=`pwd`
export MK_PACKAGE=/unihykes/mark_linux_all_${MK_SYSTEM_TYPE}
export MK_DEPS_PKGS=/unihykes/depspkgs

export PATH=$PATH:${MK_PATH}/make/script_unix
chmod -R +x $MK_PATH/make/script_unix/*.sh

#关闭回显
set +x