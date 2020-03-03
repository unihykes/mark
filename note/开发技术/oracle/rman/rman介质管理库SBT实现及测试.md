http://blog.itpub.net/30246290/viewspace-1654063/


    首先什么是机制管理器，以下是我在网络上粘贴的关于介质管理器的介绍。
    通过使用介质管理器，RMAN将数据备份到磁带上。介质管理器（Media Manager）由第三方软件商提供，它将数据块中的数据流从RMAN通道进程传递到相应的磁带中。

    计算机系统必需安装了介质管理（MM）客户端才能使用介质管理器。介质管理的客户端可以连接MM服务器，并通过网络传送数据。还必须为介质管理器安装Oracle模块。Oracle模块（Oracle Moudle）是一个用于Oracle RDBMS的软件插件，它可以连接RMAN与客户端介质管理软，后者可以把数据传送到MM服务器。Oracle的插件名称是介质管理库（MEDIA MANAGEMENT LIBRARY 简写MML）。

    oracle 自带默认的sbt库，我们可以使用如下的语句来测试：

CONFIGURE CHANNEL DEVICE TYPE 'SBT_TAPE' clear;
run
{
allocate channel ch1 type 'sbt_tape' maxpiecesize=3072M PARMS="SBT_LIBRARY=oracle.disksbt,ENV=(BACKUP_DIR=E:\backup)";
backup incremental level 0 format 'E:\backup\ORDB_%d_%s_%p_%t' database tag '2013_09_24_15_53_05';
release channel ch1;
}

    他会将数据库与通过sbt库备份到本地磁盘上你指定的目录中，eg：E:\backup。


那么我们如何自己实现一份定制功能的sbt库呢？
win 下rman备份到带库时会默认加载orasbt.dll，Linux下会默认加载libobk.so 文件，unix 下除开AIX加载libobk.a 外，其他的与Linux相同。另外值得注意的是，编译sbt需要使用原生的编译器，例如aix 下用xlc， solaris下使用CC
我实验的环境是win，我的想法很简单，就是实现一个和oracle默认的带库一致的库文件，将数据备份到本地。oracle公布了sbt的接口文档，你只需要实现对应的接口就可以。编译成orasbt.dll文件，放到C:\Windows\System32 下。
然后执行rman备份命令：
run {
allocate channel ch1 device type 'sbt_tape';
allocate channel ch2 device type 'sbt_tape';
backup incremental level 0 format 'C:\anybacktemp\ORDB_%d_%s_%p_%t' database tag '2013_09_25_15_23_55';
release channel ch1;
release channel ch2;
}

首先贴上我的库文件运行的日志文件。
[May 12 2015 15:38:18] sbtinit begin ..\skgfqsbt_windows.cpp, 742
[May 12 2015 15:38:18] sbtpvt_strscat begin, ..\skgfqsbt_windows.cpp, 3114
[May 12 2015 15:38:18] sbtpvt_strscat end, ..\skgfqsbt_windows.cpp, 3126
[May 12 2015 15:38:18] sbtinit end  ..\skgfqsbt_windows.cpp, 823
[May 12 2015 15:38:18] sbtinit2 begin  ..\skgfqsbt_windows.cpp, 1247
[May 12 2015 15:38:18] sbtinit2 oraclepid= 2084  ..\skgfqsbt_windows.cpp, 1298
[May 12 2015 15:38:18] sbtinit2 end, ..\skgfqsbt_windows.cpp, 1455
[May 12 2015 15:38:18] sbtinit begin ..\skgfqsbt_windows.cpp, 742
[May 12 2015 15:38:18] sbtpvt_strscat begin, ..\skgfqsbt_windows.cpp, 3114
[May 12 2015 15:38:18] sbtpvt_strscat end, ..\skgfqsbt_windows.cpp, 3126
[May 12 2015 15:38:18] sbtinit end  ..\skgfqsbt_windows.cpp, 823
[May 12 2015 15:38:18] sbtinit2 begin  ..\skgfqsbt_windows.cpp, 1247
[May 12 2015 15:38:18] sbtinit2 oraclepid= 3348  ..\skgfqsbt_windows.cpp, 1298
[May 12 2015 15:38:18] sbtinit2 end, ..\skgfqsbt_windows.cpp, 1455
[May 12 2015 15:38:18] sbtbackup begin  ..\skgfqsbt_windows.cpp, 840
[May 12 2015 15:38:18] sbtbackup buffer=C:\anybacktemp\ORDB_DUPDB2_66_1_879492872  ..\skgfqsbt_windows.cpp, 877
[May 12 2015 15:38:18] sbtbackup fPtr[84]=0000000000000000  ..\skgfqsbt_windows.cpp, 879
[May 12 2015 15:38:18] sbtbackup fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 881
[May 12 2015 15:38:18] sbtpvt_sbtobject begin, ..\skgfqsbt_windows.cpp, 3147
[May 12 2015 15:38:18] sbtpvt_sbtobject end, ..\skgfqsbt_windows.cpp, 3162
[May 12 2015 15:38:18] sbtbackup end  ..\skgfqsbt_windows.cpp, 916
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtbackup begin  ..\skgfqsbt_windows.cpp, 840
[May 12 2015 15:38:18] sbtbackup buffer=C:\anybacktemp\ORDB_DUPDB2_67_1_879492872  ..\skgfqsbt_windows.cpp, 877
[May 12 2015 15:38:18] sbtbackup fPtr[1348]=0000000000000000  ..\skgfqsbt_windows.cpp, 879
[May 12 2015 15:38:18] sbtbackup fPtr[1348]=000000007586F690  ..\skgfqsbt_windows.cpp, 881
[May 12 2015 15:38:18] sbtpvt_sbtobject begin, ..\skgfqsbt_windows.cpp, 3147
[May 12 2015 15:38:18] sbtpvt_sbtobject end, ..\skgfqsbt_windows.cpp, 3162
[May 12 2015 15:38:18] sbtbackup end  ..\skgfqsbt_windows.cpp, 916
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[1348]=000000007586F690  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[1348]=000000007586F690  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
··········//省略部分日志
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtwrite2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtclose2 begin  ..\skgfqsbt_windows.cpp, 922
[May 12 2015 15:38:18] sbtclose2 fPtr[84]=000000007586F660  ..\skgfqsbt_windows.cpp, 956
[May 12 2015 15:38:18] sbtclose2 fPtr[84]=0000000000000000  ..\skgfqsbt_windows.cpp, 961
[May 12 2015 15:38:18] sbtclose2 end  ..\skgfqsbt_windows.cpp, 962
[May 12 2015 15:38:18] sbtinfo2 begin  ..\skgfqsbt_windows.cpp, 1149
[May 12 2015 15:38:18] sbtinfo2 ,backup_file_name = ORDB_DUPDB2_68_1_879492898, ..\skgfqsbt_windows.cpp, 1183
[May 12 2015 15:38:18] sbtinfo2 end  ..\skgfqsbt_windows.cpp, 1236
[May 12 2015 15:38:18] sbtbackup begin  ..\skgfqsbt_windows.cpp, 840
[May 12 2015 15:38:18] sbtbackup buffer=C:\anybacktemp\ORDB_DUPDB2_69_1_879492901  ..\skgfqsbt_windows.cpp, 877
[May 12 2015 15:38:18] sbtbackup fPtr[1348]=0000000000000000  ..\skgfqsbt_windows.cpp, 879
[May 12 2015 15:38:18] sbtbackup fPtr[1348]=000000007586F660  ..\skgfqsbt_windows.cpp, 881
[May 12 2015 15:38:18] sbtpvt_sbtobject begin, ..\skgfqsbt_windows.cpp, 3147
[May 12 2015 15:38:18] sbtpvt_sbtobject end, ..\skgfqsbt_windows.cpp, 3162
[May 12 2015 15:38:18] sbtbackup end  ..\skgfqsbt_windows.cpp, 916
[May 12 2015 15:38:18] sbtwrite2 fPtr[1348]=000000007586F660  ..\skgfqsbt_windows.cpp, 1652
[May 12 2015 15:38:18] sbtclose2 begin  ..\skgfqsbt_windows.cpp, 922
[May 12 2015 15:38:18] sbtclose2 fPtr[1348]=000000007586F660  ..\skgfqsbt_windows.cpp, 956
[May 12 2015 15:38:18] sbtclose2 fPtr[1348]=0000000000000000  ..\skgfqsbt_windows.cpp, 961
[May 12 2015 15:38:18] sbtclose2 end  ..\skgfqsbt_windows.cpp, 962
[May 12 2015 15:38:18] sbtinfo2 begin  ..\skgfqsbt_windows.cpp, 1149
[May 12 2015 15:38:18] sbtinfo2 ,backup_file_name = ORDB_DUPDB2_69_1_879492901, ..\skgfqsbt_windows.cpp, 1183
[May 12 2015 15:38:18] sbtinfo2 end  ..\skgfqsbt_windows.cpp, 1236
[May 12 2015 15:38:18] sbtend begin  ..\skgfqsbt_windows.cpp, 1011
[May 12 2015 15:38:18] sbtend fPtr[84]=0000000000000000  ..\skgfqsbt_windows.cpp, 1073
[May 12 2015 15:38:18] sbtend fPtr[84]=0000000000000000  ..\skgfqsbt_windows.cpp, 1078
[May 12 2015 15:38:18] sbtend end  ..\skgfqsbt_windows.cpp, 1079
[May 12 2015 15:38:18] sbtend begin  ..\skgfqsbt_windows.cpp, 1011
[May 12 2015 15:38:18] sbtend fPtr[1348]=0000000000000000  ..\skgfqsbt_windows.cpp, 1073
[May 12 2015 15:38:18] sbtend fPtr[1348]=0000000000000000  ..\skgfqsbt_windows.cpp, 1078
[May 12 2015 15:38:18] sbtend end  ..\skgfqsbt_windows.cpp, 1079

从日志里，大家可以更清晰的看到执行顺序，sbtinit() -> sbtinit2() -> sbtbackup() -> sbtwrite2() -> sbtclose2() -> sbtinfo2() ->sbtend()
init函数顾名思义是执行初始化，backup函数开始执行备份生成备份片，write2 函数测循环的每次写块，默认262144(256K)到备份片中。close2 结束当前备份片的备份，info2 记录当前备份片的信息，end释放通道结束备份。

备份出来的备份片是否可以恢复，我不敢确定，所以使用了上文提到的dbms_backup_restore包，来验证是否可以提取其中的文件。
脚本如下：

DECLARE
devtype varchar2(256);
done boolean;
BEGIN
devtype:=sys.dbms_backup_restore.deviceAllocate(type=>'sbt_tape',ident=>'T1');
sys.dbms_backup_restore.restoreSetDatafile;
sys.dbms_backup_restore.restoreDatafileTo(dfnumber=>1,toname=>'C:\anybacktemp\system01.dbf');
sys.dbms_backup_restore.restoreDatafileTo(dfnumber=>2,toname=>'C:\anybacktemp\undotbs01.dbf');
sys.dbms_backup_restore.restoreDatafileTo(dfnumber=>4,toname=>'C:\anybacktemp\users01.dbf');
sys.dbms_backup_restore.restoreBackupPiece(done=>done,handle=>'C:\anybacktemp\ORDB_DUPDB2_66_1_879492872',params=>null); 
sys.dbms_backup_restore.deviceDeallocate;
end;
/

注意此处分配的通道也必须是sbt_tape ，相应的调用的还是我们自己编写的sbt库。最终验证通过，成功提取出了对应的数据文件。

相应的贴上对应的日志：
[May 12 2015 15:38:18] sbtinit begin ..\skgfqsbt_windows.cpp, 742
[May 12 2015 15:38:18] sbtpvt_strscat begin, ..\skgfqsbt_windows.cpp, 3114
[May 12 2015 15:38:18] sbtpvt_strscat end, ..\skgfqsbt_windows.cpp, 3126
[May 12 2015 15:38:18] sbtinit end  ..\skgfqsbt_windows.cpp, 823
[May 12 2015 15:38:18] sbtinit2 begin  ..\skgfqsbt_windows.cpp, 1247
[May 12 2015 15:38:18] sbtinit2 oraclepid= 3952  ..\skgfqsbt_windows.cpp, 1298
[May 12 2015 15:38:18] sbtinit2 end, ..\skgfqsbt_windows.cpp, 1455
[May 12 2015 15:38:18] sbtinfo2 begin  ..\skgfqsbt_windows.cpp, 1149
[May 12 2015 15:38:18] sbtinfo2 ,backup_file_name = ORDB_DUPDB2_66_1_879492872, ..\skgfqsbt_windows.cpp, 1183
[May 12 2015 15:38:18] sbtinfo2 ,backup_file_name = ORDB_DUPDB2_67_1_879492872, ..\skgfqsbt_windows.cpp, 1183
[May 12 2015 15:38:18] sbtinfo2 end  ..\skgfqsbt_windows.cpp, 1236
[May 12 2015 15:38:18] sbtrestore begin backup_file_name：ORDB_DUPDB2_66_1_879492872, ..\skgfqsbt_windows.cpp, 1568
[May 12 2015 15:38:18] sbtrestore fPtr[1952]=0000000000000000  ..\skgfqsbt_windows.cpp, 1599
[May 12 2015 15:38:18] sbtrestore buffer=C:\anybacktemp\ORDB_DUPDB2_66_1_879492872  ..\skgfqsbt_windows.cpp, 1603
[May 12 2015 15:38:18] sbtrestore fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1606
[May 12 2015 15:38:18] sbtrestore end, ..\skgfqsbt_windows.cpp, 1630
[May 12 2015 15:38:18] sbtread2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1475
[May 12 2015 15:38:18] sbtread2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1475
[May 12 2015 15:38:18] sbtread2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1475
[May 12 2015 15:38:18] sbtread2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1475
······//省略部分日志
[May 12 2015 15:38:18] sbtread2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1475
[May 12 2015 15:38:18] sbtread2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1475
[May 12 2015 15:38:18] sbtread2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1475
[May 12 2015 15:38:18] sbtread2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1475
[May 12 2015 15:38:18] sbtread2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1475
[May 12 2015 15:38:18] sbtread2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1475
[May 12 2015 15:38:18] sbtread2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 1475
[May 12 2015 15:38:18] sbtpvt_error begin, ..\skgfqsbt_windows.cpp, 3723
[May 12 2015 15:38:18] sbtpvt_error end, ..\skgfqsbt_windows.cpp, 3758
[May 12 2015 15:38:18] sbtread2, ..\skgfqsbt_windows.cpp, 1479
[May 12 2015 15:38:18] sbterror begin  ..\skgfqsbt_windows.cpp, 1089
[May 12 2015 15:38:18] sbterror end  ..\skgfqsbt_windows.cpp, 1139
[May 12 2015 15:38:18] sbtclose2 begin  ..\skgfqsbt_windows.cpp, 922
[May 12 2015 15:38:18] sbtclose2 fPtr[1952]=000000007586F660  ..\skgfqsbt_windows.cpp, 956
[May 12 2015 15:38:18] sbtclose2 fPtr[1952]=0000000000000000  ..\skgfqsbt_windows.cpp, 961
[May 12 2015 15:38:18] sbtclose2 end  ..\skgfqsbt_windows.cpp, 962
[May 12 2015 15:38:18] sbtend begin  ..\skgfqsbt_windows.cpp, 1011
[May 12 2015 15:38:18] sbtend fPtr[1952]=0000000000000000  ..\skgfqsbt_windows.cpp, 1073
[May 12 2015 15:38:18] sbtend fPtr[1952]=0000000000000000  ..\skgfqsbt_windows.cpp, 1078
[May 12 2015 15:38:18] sbtend end  ..\skgfqsbt_windows.cpp, 1079


因为是单通道，这里大家可以更加清晰的看到函数的执行顺序。

当然并不是sbt只有这些接口而已，只是我的实现中主要用到了这些接口，所以用日志的方式展现出来，达到简洁明了的效果。
下面我会将大部分接口名称贴出来，供大家参考：
#define sbtbackup_p(s)         (*(s).sbt_mms_fptr_sbtbackup)
#define sbtclose2_p(s)         (*(s).sbt_mms_fptr_sbtclose2)
#define sbtcommand_p(s)        (*(s).sbt_mms_fptr_sbtcommand)
#define sbtend_p(s)            (*(s).sbt_mms_fptr_sbtend)
#define sbterror_p(s)          (*(s).sbt_mms_fptr_sbterror)
#define sbtinfo2_p(s)          (*(s).sbt_mms_fptr_sbtinfo2)
#define sbtinit2_p(s)          (*(s).sbt_mms_fptr_sbtinit2)
#define sbtread2_p(s)          (*(s).sbt_mms_fptr_sbtread2)
#define sbtremove2_p(s)        (*(s).sbt_mms_fptr_sbtremove2)
#define sbtrestore_p(s)        (*(s).sbt_mms_fptr_sbtrestore)
#define sbtwrite2_p(s)         (*(s).sbt_mms_fptr_sbtwrite2)
#define sbtpcbackup_p(s)       (*(s).sbt_mms_fptr_sbtpcbackup)
#define sbtpccancel_p(s)       (*(s).sbt_mms_fptr_sbtpccancel)
#define sbtpccommit_p(s)       (*(s).sbt_mms_fptr_sbtpccommit)
#define sbtpcend_p(s)          (*(s).sbt_mms_fptr_sbtpcend)
#define sbtpcquerybackup_p(s)  (*(s).sbt_mms_fptr_sbtpcquerybackup)
#define sbtpcqueryrestore_p(s) (*(s).sbt_mms_fptr_sbtpcqueryrestore)
#define sbtpcrestore_p(s)      (*(s).sbt_mms_fptr_sbtpcrestore)
#define sbtpcstart_p(s)        (*(s).sbt_mms_fptr_sbtpcstart)
#define sbtpcstatus_p(s)       (*(s).sbt_mms_fptr_sbtpcstatus)
#define sbtpcvalidate_p(s)     (*(s).sbt_mms_fptr_sbtpcvalidate)

以上就是我初次与大家分享的实践经验，不足之处请大家指教。
