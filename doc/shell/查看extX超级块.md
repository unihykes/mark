


# 查看文件系统的超级块等信息
	dumpe2fs /dev/sda1


# 查看extX的日志超级块起始地址
	echo "stat <8>" | debugfs /dev/sda2 | grep "(0-" | awk {'print $1'}
	上面解析的ext3de
	echo "stat <8>" | debugfs /dev/sda4 | grep "(0-" | awk {'print $2'}
	后面发的是ext4