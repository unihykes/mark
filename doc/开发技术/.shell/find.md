
查找并删除*.so文件

find . -name "*.so" | xargs rm 
查找并拷贝*.so文件

find . -name "*.so" | xargs -i cp {} ./tmp/
拷贝当前目录下所有*.so文件到./tmp/下
	
	
ls *.so | xargs -i cp {} ./tmp/





#linux下查找关键字所在的文件
	find /home  -type f | perl -e 'while (<>) {s/\n//; s/.*\.svn.*//; if (! -B) {print $_."\n"} }' | xargs grep -n "PushVolumePoint"  2> /dev/null    | grep "\.cpp"

	find .  -type f | perl -e 'while (<>) {s/\n//; s/.*\.svn.*//; if (! -B) {print $_."\n"} }' | xargs grep -n "PushVolumePoint"  2> /dev/null

	find .  -type f | perl -e 'while (<>) {s/\n//; s/.*\.svn.*//; if (! -B) {print $_."\n"} }' | xargs grep -n "PushVolumePoint"  2> /dev/null    | grep "cpp"

	find .  -type f | perl -e 'while (<>) {s/\n//; s/.*\.svn.*//; if (! -B) {print $_."\n"} }' | xargs grep -n "PushVolumePoint"  2> /dev/null    | grep "\.h"


