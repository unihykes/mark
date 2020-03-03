oracle压缩选项


Rman compressed 分为三种，前两种是默认的。后一种需要手动。
1.null compression
2.unused block compression
3.binary compression
在10.1版本之前默认的是null compression,10.2以后的默认是1+2啦。
下面就来解释下这三个名词
null compression:在执行rman备份的时候未分配的block不会被备份。
unused block compression:就算是block已经被分配但是数据被delete掉啦。那delete这部分的数据也不会被备份
举例说明，我现在有一个datafile 100m,如果已经分配了50m的block，但是又被人delete了25m,如果在10.1版本的时候会备份50m,10.2之后的只会备份25m.
binary compression:这个是手动在执行rman命令的时候要加as compressed命令的。当磁盘空间不够的时候可以考虑压缩备份这种特性。压缩率比较惊人。可以达到1/2-1/4。但是这种高压缩也是有缺点的。就是恢复起来比较慢。这个主要是在磁盘和cpu之间来做衡量。11g 又出来了zlib压缩算法，这种算法比之前要快。但是压缩率不如之前的bzip2.

RMAN> backup as compressed backupset archivelog all;
RMAN> backup as compressed backupset database;
RMAN> backup as compressed backupset current controlfile;
 
CONFIGURE COMPRESSION ALGORITHM '';
 
在restore的时候如果你不执行compression backset，oracle是不会选择它的。。只会去选择不压缩的


额外参考：
blog.itpub.net/35489/viewspace-701761/