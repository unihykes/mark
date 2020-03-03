http://www.docin.com/p-944212275-f3.html

http://blog.itpub.net/30246290/viewspace-1654063/

https://wenku.baidu.com/view/25b6473ca22d7375a417866fb84ae45c3b35c2f3.html




RMAN 系列（三） ---- 介质管理问题
http://blog.csdn.net/xueaizhong/article/details/7712289

rman语法教程：
http://www.docin.com/p-70456711.html?docfrom=rrela


RMAN备份FORMAT格式中%的含义
http://blog.csdn.net/cuiyan1982/article/details/53492422


oracle sbt
RMAN和介质管理器
通过使用介质管理器，RMAN将数据备份到磁带上。介质管理器（Media Manager）由第三方软件商提供，它将数据块中的数据流从RMAN通道进程传递到相应的磁带中。
计算机系统必需安装了介质管理（MM）客户端才能使用介质管理器。介质管理的客户端可以连接MM服务器，并通过网络传送数据。还必须为介质管理器安装Oracle模块。Oracle模块（Oracle Moudle）是一个用于Oracle RDBMS的软件插件，它可以连接RMAN与客户端介质管理软，后者可以把数据传送到MM服务器。
Oracle的插件名称是介质管理库（MEDIA MANAGEMENT LIBRARY 简写MML）。

介质管理库
MML是一个库文件，它将RMAN的一致性的备份或还原请求解释为在介质管理服务器上的体的系统调用，以实现要求的操作。MML与MM客户端软件和MM服务器软件一样是由同一个供应商提供的，但是我们需要单独购买MML和取得许可。
首次分配磁带通道时，MML作为一个集成的库文件加载到Oracle内存空间， 它是RDBMS软件的逻辑部分，RMAN可以生成正确的MM客户端软件调用。
集成过程：分配磁带通道时，Oracle加载ORACLE_HOME/bin目录下的libobk.so的文件。它只是一个到要使用的MML文件的符号连接。
在Windows上，会搜索orasbt.dll。

SBT API
RMAN可以不受影响地使用不同的介质管理器，这是因为不管加载了哪一种MML，RMAN都会发送相同的命令。Oracle使用SBT API来开发RMAN。SBT API是一种通用API。提供给Oracle数据库备份操作编码集成产品的第三方软件商，是RMAN向介质管理器发送命令的工具.


还原数据库
    rman>restore database
        从备份还原数据库,并放置于正确位置
    rman>recover database
        提取归档重做日志,将它们应用于数据库
    rman>alter database open
        打开数据库,应用联机重做日志文件中的重要信息;
        




rman命令行参数
usage
    Argument     Value          Description
    -----------------------------------------------------------------------------
    target       quoted-string  connect-string for target database
    catalog      quoted-string  connect-string for recovery catalog
    auxiliary    quoted-string  connect-string for auxiliary database
    nocatalog    none           if specified, then no recovery catalog
    cmdfile      quoted-string  name of input command file
    log          quoted-string  name of output message log file
    trace        quoted-string  name of output debugging message log file
    append       none           if specified, log is opened in append mode
    debug        optional-args  activate debugging
    msgno        none           show RMAN-nnnn prefix for all messages
    send         quoted-string  send a command to the media manager
    pipe         string         building block for pipe names
    script       string         name of catalog script to execute
    using        list of args   arguments for rman variables
    timeout      integer        number of seconds to wait for pipe input
    checksyntax  none           check the command file for syntax errors
    salxdebug
    
    
    
查看备份记录
查看备份记录
    数据库备份
        RMAN> list backup of database summary;
            
    归档日志备份
        RMAN> list backup of archivelog all summary;
            
    usage
        输出信息包含如下内容
Key     TY LV S Device Type Completion Time #Pieces #Copies Compressed Tag
        可以看到设备类型,时间,是否压缩,tag等