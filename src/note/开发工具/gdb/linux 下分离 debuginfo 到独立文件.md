	
	https://blog.csdn.net/force_eagle/article/details/51980558

# linux 下分离 debuginfo 到独立文件.

	gcc -ggdb utmp.c -o utmp
	readelf -S utmp
	# 创建一个包含 debuginfo 文件
	objcopy --only-keep-debug utmp utmp.debug
	# 添加一个包含路径文件的 .gnu_debuglink section, 文件必须存在.
	objcopy --add-gnu-debuglink=utmp.debug utmp
	# 查看 .gnu_debuglink section
	objdump -s -j .gnu_debuglink utmp


	utmp:     file format elf64-x86-64


	Contents of section .gnu_debuglink:
	0000 75746d70 2e646562 75670000 0068651a  utmp.debug...he.


	#
	objcopy --strip-debug utmp


	指定gdb 加载 debuginfo 即可
	gdb utmp -s utmp.debug
	or
	(gdb) file utmp
	(gdb) symbol utmp.debug
	---------------------
	作者：功名半纸
	来源：CSDN
	原文：https://blog.csdn.net/force_eagle/article/details/51980558
	版权声明：本文为博主原创文章，转载请附上博文链接！