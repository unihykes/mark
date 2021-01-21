#ORA-1804错误
OCI环境初始化失败
    在SUSE10上安装了ORACLE 11G，
结果编写OCI测试程序时，老是初始化环境失败（OCIInitialize），
报1804错误，在GOOGLE上搜索了一下，
原来是没有设置ORACLE_BASE、ORACLE_HOME等环境变量导致的，设置后，程序正常了。
    如：
    export ORACLE_BASE=/data/oracle
    export ORACLE_HOME=$ORACLE_BASE/product/11.2.0/dbhome_1
    export ORACLE_SID=orcl2
    export PATH=$ORACLE_HOME/bin:$PATH
    

# ORA-00845: MEMORY_TARGET not supported on this system

https://www.cnblogs.com/killkill/archive/2010/09/10/1823690.html

SQL> show parameter memory_target
show parameter memory_max_target
alter system set memory_max_target=2G scope=spfile;
alter system set memory_target=1G scope=spfile;
alter system set memory_max_target=2G;
alter system set memory_target=768m;
ALTER SYSTEM SET MEMORY_MAX_TARGET=1G SCOPE=SPFILE;
startup pfile='/usr/oracle/admin/orcl/pfile/init.ora.8292017172346';
现在可以通过重启使这个配置生效，也可以通过重新挂载来修改其大小：
[root@FWDB ~]# mount -o remount,size=4G /dev/shm
[root@FWDB ~]# df -h | grep shm
tmpfs                 4.0G     0  4.0G   0% /dev/shm
      再次启动数据库，没有报错了。
于是手动修改数据库参数文件：app/Administrator/product/11.1.0/db_1/database/SPFILEORCL.ORA
 
 
# ORA-01034: ORACLE not available  ORA-27101: shared memory realm does not exist
服务未开启
情形1
    可能是没开启oracle服务:
情形2
        附加信息：ORA-01034: ORACLE not available
ORA-27101: shared memory realm does not exist
Linux-x86_64 Error: 2: No such file or directory

解决办法:
       su - oracle
       lsnrctl start
       
# ORA-00922: missing or invalid option
oracle 10g版本不支持备份pfile选项,关闭之;


