磁盘读写（写的时候注意路径，不明确指定则默认当前路径）：
查看磁盘/dev/sdb读速度：（因为/dev/sdb1是一个物理分区，对它的读取会产生IO，/dev/null是伪设备，相当于黑洞，of到该设备不会产生IO，所以，这个命令的IO只发生在/dev/sdb1上，也相当于测试磁盘的读能力）
time dd if=/dev/sdb of=/dev/null bs=4M  count=10000

查看磁盘/dev/sdb写速度：（其中/dev/zero是一个伪设备，它只产生空字符流，对它不会产生IO，所以，IO都会集中在of文件中，of文件只用于写，所以这个命令相当于测试磁盘的写能力。）
time dd if=/dev/zero of=test.dbf bs=4M count=25000