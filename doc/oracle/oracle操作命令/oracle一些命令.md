查看归档日志序号

list backup of archivelog all;




查询oracle版本信息
    root下运行: su - oracle -c "sqlplus -h"

. oraenv
    运行 oraenv 之前要 点（dot)空格(space)oraenv  --> . oraenv  如果不这样运行的话,脚本无效
    作用:设置一些oracle环境变量,如$ORACLE_HOME等;
    也可将这些变量写入对用用户的.bash_profile文件中,就不用每次运行了。
    oraenv文件在 $ORACLE_HOME/bin 下面，可以直接运行。
    如果用户把 $ORACLE_HOME/bin 已经加入了在 .base_profile 的 PATH 参数里面，就可以直接运行了。
    
开启监听
    linux下:
        su - oracle
        lsnrctl start
    windows下,直接进入cmd窗口(不要进入sqlplus)输入lsnrctl start

关闭监听
    lsnrctl stop

强制重启服务
    ps -ef|grep ora_dbw0_$ORACLE_SID
    kill -9 xxx
    sqlplus /nolog
    重新启动oracle
    sqlplus sys as sysdba
    startup;

    
启动数据库
    sqlplus /nolog
    conn /as sysdba


启动数据库实例
    SQL> startup
    

查看实例状态
    select instance_name,status from v$instance;

关闭数据库实例
    SQL> shutdown immediate


退出SQL
    SQL>exit


开启实例状态为open
    alter database open;
    如果报错：ORA-01589: 要打开数据库则必须使用 RESETLOGS 或 NORESETLOGS 选项
    则：
    SQL> alter database open resetlogs;
    
    
查看表
    select * from 表名

数据插入
    insert into 表名 values (   );
    
    
创建表空间
    create tablespace A1 datafile'E:\orcldata\DATAFILET2.dbf' size 100m
    extent management local autoallocate;
    
    
创建表
        create table a1(n number) tablespace A1;
        A1是表空间
    
    
使用FRA
    设置FRA
        alter system set db_recovery_file_dest_size=2G;
        alter system set db_recovery_file_dest='/u01/FRA';
    
    查询FRA
            select name, space_limit, space_used, space_reclaimable from v$recovery_file_dest;
    
    
开启归档模式
    需要关闭数据库然后重启
    usage
    sqlplus /nolog
    conn /as sysdba
    
    关闭数据库:
    SQL>shutdown immediate

    挂载数据库
    SQL> startup mount

    归档->非归档
    SQL> alter database noarchivelog;      (注意末尾带分号)

    非归档->归档
    SQL> alter database archivelog;(注意末尾带分号)

    检查是否成功
    SQL> archive log list;(注意末尾带分号)

    启动数据库实例:
    SQL> alter database open;
    SQL> alter database noarchivelog;  
    
查看备份信息
    select start_time, end_time, status, input_type, output_bytes_display from v$rman_backup_job_details;

查询数据库状态
    select log_mode from v$database;

