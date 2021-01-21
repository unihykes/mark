Oracle SBT（或者叫BSP）
Oracle 数据库使用 RMAN 进行备份时，允许加载和调用一个库文件，使得第三方介质管理软件可以通过该库的接口获取备份的数据流，从而实现自定义的数据备份形式（比如备份到磁带库）。

该库一般由介质管理软件根据接口文档和开发规范进行开发，在运行期由Oracle加载，并且和介质管理软件进行通讯。
该文件在Linux系统通常为 libobk.so，在Windows系统上为orasbt.dll。

RMAN
恢复管理器（recovery manager，RMAN）是数据库的备份工具，通过启动操作系统进程将数据备份到磁盘或磁带上；
可以使用copy命令将数据库文件拷贝到磁盘或者磁带上，也可以使用BACKUP命令对整个数据库，一个指定的表空间，控制文件或日志文件进行备份；
RMAN是一个Client/Server程序，她使用Oracle服务器会话进行备份与恢复。
RMAN备份的元数据存储在备份目标数据库的控制文件中，或者是一个单独的称之为catalog的数据库中。

BACKUP命令可以将数据库备份分为多个数据包，每一个包称为一个备份子集（Backup set）,一个备份子集又可以分为多个备份片（Backup Piece）,RMAN可以在不同的操作系统上进行备份；

为什么要使用RMAN?
可以管理复杂的备份与恢复操作
最小化人为错误的可能性。
使备份具有可扩展性与可靠性。
备份可以写到不同存储介质上。
只备份使用过的数据块，而不是整个数据库。
提供增量备份，减少备份及恢复的时间。

RMAN备份对象：
可以使用RMAN进行的备份对象如下：
--整个数据库：备份所有的数据文件和控制文件；
--数据文件：备份指定的一个或多个数据文件；
--表空间：备份指定的一个或多个表空间；
--归档重做日志文件：备份归档重做日志文件；
--控制文件：在线备份目标数据库当前的控制文件；
--服务器初始化参数文件：备份目标数据库的服务器初始化参数文件；
--数据文件的镜像复制：备份使用BACKUP AS COPY命令创建数据文件的镜像复制；
--控制文件的镜像复制：备份使用BACKUP AS COPY命令创建控制文件的镜像复制；
--备份集：备份使用BACKUP命令创建的备份集。


RMAN备份类型

完全备份
完全备份的概念：RMAN中的完全备份（FULL Backup）不是指对整个数据库进行完全备份，而是对数据文件进行备份时，不管数据文件中的数据块是否被修改都复制到备份中。


增量备份
增量备份的概念：RMAN中的增量备份（Incremental Backup）是指备份数据文件时，只备份上次增量备份后被修改过的数据块，因此，增量备份要比完全备份小得多，但增量备份的时间不一定比完全备份的时间短，因为增量备份也要读取数据文件中所有的数据块。
根据增量备份所参照的基础不同，增量备份又分为差异增量备份（Differential Incremental Backup）和累积增量备份(Cumulative Incremental Backup)两种。
	* 
差异增量备份：以最近级别为0或1的增量备份为基础，复制所有被修改过的数据块。 默认为差异增量备份。
	* 
累积增量备份：以最近级别为0的增量备份为基础，复制所有被修改过的数据块。


例子1.差异增量备份
如果每周周日对数据库做级别为0的增量备份,即备份数据库中所有被使用的数据块，其余每天对数据库做差异增量备份，即周一备份相对周日的增量备份发生数据变化的数据块，周二备份相对于周一的增量备份发生数据变化的数据块，…，以此类推。备份策略应该如下图:

例子2.累积增量备份
如果每周周日对数据库做级别为0的增量备份,即备份数据库中所有被使用的数据块，其余每天对数据库做累积增量备份，即周一备份相对周日的增量备份发生数据变化的数据块，周二也备份相对于周日的增量备份发生数据变化的数据块，…，以此类推。备份策略应该如下图:


RMAN通道
RMAN在执行数据库备份与恢复操作时，都要使用操作系统进程，启动进程通过分配通道而实现；
每分配一个通道，RMAN启动一个服务器进程，通道包括自动通道分配与采用RUN命令手动分配通道；
一个通道与一个设备相关联；

并行备份
默认情况下，RMAN在创建备份集时只会使用一个通道向一个磁盘或磁带中写入数据，如果要备份的文件较多，可以启动多个通道同时向多个磁盘写入数据，即并行备份。
可以通过以下几种方式启用并行备份：
--使用CONFIGURE DEVICE TYPE disk/sbt命令将 PARALLELISM 参数设置大于1
--在执行BACKUP命令之前手动分配多个通道，然后在BACKUP命令中设置FILESPERSET参数，这样在备份时RMAN会根据参数设置备份集的数量，使用手动分配的通道进行并行备份。


通道分配
在使用RMAN对目标数据库进行备份、修复、及恢复时，必须为操作系统分配通道。可以手动分配，也可以自动分配。
（5.1）自动分配
自动分配通道相关预定义参数包括：
--CONFIGURE DEFAULT DEVICE TYPE TO disk|sbt ：指定自动通道的默认设备；
--CONFIGURE DEVICE TYPE disk|sbt PARALLELISM n ：设置自动通道的数量；
--CONFIGURE CHANNEL DEVICE TYPE：对自动分配的所有通道进行设置；
--CONFIGURE CHANNEL n DEVICE TYPE：对自动分配的通道编号为n的进行设置。
（5.2）手动分配
可以使用RUN命令手动分配通道，语法为：
RUN{
ALLOCATE CHANNEL 通道名称 DEVICE TYPE 设备类型;
BACKUP …
}
例子.为user01表空间的备份分配一个通道，设备类型为磁盘
RUN{
ALLOCATE CHANNEL ch1 DEVICE TYPE disk FORMAT ‘/home/%U’;
BACKUP TABLESPACE usre01;
}
在RMAN命令执行器中，单独执行BACKUP命令时，使用自动分配的通道，在RUN内使用BACKUP命令，但没有手动分配通道，则使用自动分配的通道。
可以同时定义多个通道并行备份数据库，例如，使用2个通道并行备份两个数据文件。
RMAN > RUN {
ALLOCATE CHANNEL ch1 DEVICE TYPE disk;
ALLOCATE CHANNEL ch2 DEVICE TYPE disk;
BACKUP DATAFILE 1,2;
}
如果每个BACKUP语句只对应一个数据文件，则在同一时间只有一个数据文件备份，只有一个通道被激活。
RMAN > RUN{
ALLOCATE CHANNEL ch1 DEVICE TYPE disk1;
ALLOCATE CHANNEL ch2 DEVICE TYPE disk1;
BACKUP DATAFILE 1;
BACKUP DATAFILE 2;
}


backup常用命令总结
1.设置备份标记
        backup database tag='full_bak1';
        注：每个标记必须唯一，相同的标记可以用于多个备份只还原最新的备份。
    2.设置备份集大小(一次备份的所有结果为一个备份集，要注意备份集大小)
        backup database maxsetsize=100m tag='datafile1';
        注：maxsetsize限定备份集的大小。所以必须大于数据库总数据文件的大小，否则会报错。
      RMAN-06183: datafile or datafile copy larger than MAXSETSIZE: file# 1 /data/oradata/system01.dbf
    3.设置备份片大小(磁带或文件系统限制)
        run {
        allocate channel c1 type disk maxpicecsize 100m format '/data/backup/full_0_%U_%T';
        backup database tag='full_0';
        release channel c1;
        }
        可以在allocate子句中设定每个备份片的大小，以达到磁带或系统限制。
        也可以在configure中设置备份片大小。
        Configure channel device type disk maxpiecesize 100 m;
        configure channel device type disk clear;
    4.备份集的保存策略
        backup database keep forever;                  --永久保留备份文件
        backup database keep until time='sysdate+30'; --保存备份30天
    5.重写configure exclude命令
        backup databas noexclude keep forever tag='test backup';
    6.检查数据库错误
        backup validate database;
        使用RMAN来扫描数据库的物理/逻辑错误，并不执行实际备份。
    7.跳过脱机，不可存取或只读文件
        backup database skip readonly;
        backup database skip offline;
        backup database skip inaccessible;
        backup database ship readonly skip offline ship inaccessible;
    8.强制备份
        backup database force;
    9.基于上次备份时间备份数据文件
        1>只备份添加的新数据文件
            backup database not backed up;
        2>备份"在限定时间周期内"没有被备份的数据文件
            backup database not backed up since time='sysdate-2';
    10.备份操作期间检查逻辑错误
        backup check logical database;
        backup validate check logical database;
    11.生成备份副本
        backup database copies=2;
    12.备份控制文件
        backup database device type disk includ current controlfile;


FORMAT格式串
先看例子：Configure channel 1 device type disk format 'd:/backup/orcl/backup_%U';
在configure 命令中经常使用格式串，在backup,resotre,allocate channel 等其他RMAN 命令中也会经常看到格式串。RMAN 提供了与格式串关联的一些语法元素。 这些元素称： 占位符， rman 将使用相应的定义值来替换他们。 例如示例中的 %U 语法元素告诉RMAN要使用系统生成的唯一表示符替换文件名。
使用FORMAT参数时可使用的各种替换变量，如下（注意大小写）所示：
%a：Oracle数据库的activation ID即RESETLOG_ID。
%c：备份片段的复制数（从1开始编号，最大不超过256）。
%d：Oracle数据库名称。
%D：当前时间中的日，格式为DD。
%e：归档序号。
%f：绝对文件编号。
%F：基于"DBID+时间"确定的唯一名称，格式的形式为c-IIIIIIIIII-YYYYMMDD-QQ,其中IIIIIIIIII 为该数据库的DBID，YYYYMMDD为日期，QQ是一个1～256的序列。
%h：归档日志线程号。
%I：Oracle数据库的DBID。
%M：当前时间中的月，格式为MM。
%N：表空间名称。
%n：数据库名称，并且会在右侧用x字符进行填充，使其保持长度为8。比如数据库名JSSBOOK，则生成的名称则是JSSBOOKx。
%p：备份集中备份片段的编号，从1开始。
%s：备份集号。
%t：备份集时间戳。
%T：当前时间的年月日格式（YYYYMMDD）。
%u：是一个由备份集编号和建立时间压缩后组成的8字符名称。利用%u可以为每个备份集生成一个唯一的名称。
%U：默认是%u_%p_%c的简写形式，利用它可以为每一个备份片段（即磁盘文件）生成一个唯一名称，这是最常用的命名方式，执行不同备份操作时，生成的规则也不同，如下所示：
生成备份片段时，%U=%u_%p_%c；
生成数据文件镜像复制时，%U=data-D-%d_id-%I_TS-%N_FNO-%f_%u；
生成归档文件镜像复制时，%U=arch-D_%d-id-%I_S-%e_T-%h_A-%a_%u；
生成控制文件镜像复制时，%U=cf-D_%d-id-%I_%u。
%Y：当前时间中的年，格式为YYYY。
注：如果在BACKUP命令中没有指定FORMAT选项，则RMAN默认使用%U为备份片段命名。


RMAN增量备份

增量备份有两大优点：
减少数据库恢复的时间。
    数据库恢复是利用归档日志，不断的应用归档日志，将数据库恢复到最新（或者指定状态）。
    但是增量备份只备份被修改了的数据块，在执行恢复时，直接用备份出来的数据块去覆盖数据文件中被更改的数据块。
减少备份时间
    增量备份只需备份被修改过的数据块，备份时间和备份存储空间都有相应的减少。

做增量备份的前提，是需要一个基准备份，所有的增量都是针对这个基准来说的。要不然，增量备份无从谈起。
   增量备份使用INCREMENTAL LEVEL=integer 关键字指定。integer可以是0到4之间的任意整数。
必须将0 级备份作为增量策略的基础备份。0 级增量备份在内容上与完全备份相同，但与完全备份不同的是，0 级备份被看作是增量策略的一部分。如果在运行1 级或更高级别的备份时，0 级备份不存在，RMAN 会自动制作0 级备份。

增量备份的方式分两种：
差异增量备份
  n 级备份，备份自最近n 级或更低级别备份以来更改过的所有块。



累计增量备份
  n 级备份，它包含自上次n-1 级或更低级别备份以来更改过的所有块。

累计增量备份使用cumulative关键字，如：
  BACKUP INCREMENTAL level 2 cumulative DATABASE;





1 Or a c l eBSP的基本原理
1.1.oracle BSP集成体系结构
在BSP技术机制中,Oracle提供的一组 API，称为 MML(Media Management Library)。
介质管理软件(或备份软件)就是通过MML，把Oracle数据库的备份恢复管理及存储介质管理结合起来，实现更加健壮的备份恢复功能。
RMAN执行备份操作将Oracle数据备份存储到磁带上,必须有介质管理软件(即结合MML)支持才能完成。
介质管理软件:
是一组程序，它管理存储备份恢复数据的顺序存储介质诸如磁带驱动装载、标签、卸载等操作活动 。
Oracle服务会话:
其会话功能是提供Oracle数据库处理备份恢复操作服务。
介质管理库(MML):
代表第三方支持的介质管理软件与Oracle数据库交互，Oracle调用MML软件子程序,在介质管理软件控制下，完成在存储磁带介质上备份(写介质)／恢复(读介质)数据。
1.2 Oraclel BSP的技术本质
Oracle提供备份恢复读写磁带介质的解决方案，实质上就是利用Oracle管理数据库的卓越技术优势，开放Oracle数据库备份恢复体系中相关的API编程接口，
以提供给第三方开发磁带等介质管理软件，以便与Oracle的整体备份恢复方案进行程序代码级的集成。
Oracle BSP是Oracle公司与第三方合作的众多伙伴项目之一，它促进最主要的一些介质管理软件开发销售商组成了一个会员组织。
这些介质管理软件产品在内部设计上完全符合Oracle的MML规格要求，它能够让 Or ac l e服务会话备份数据到介质管理器上，同时要求介质管理对备份能够恢复还原。
在OracleBSP方案中，备份工具RMAN不发出任何特殊的操作磁带介质的命令如加载、卸载磁带或标签磁带。
当进行备份时，RMAN传送给介质管理软件一个字节流及与此数据流相关的一个唯一性的名字。
当RMAN需要恢复备份的数据时，它要求介质管理软件检索出完全相同的那个命名字节流。
至于那个备份字节流如何存储及存储到哪里等所有细节，完全 由介质管理器来承担处理。
MML是OracleBSP的实质接口，整个备份恢复方案中MML的实现是能否正确备份恢复到磁带介质的关键。
MML的角色就是Oracle为集成实现BSP方案开放的编程API，它提供了用磁带作介质进行备份恢 复的详细规格说明，
而介质管理软件在MML层呈现的角色按MML的规格要求用程序代码实现MML，在实现MML的API的程序代码中，同时实现与介质管理软件中介质管理操作的交互、通讯等功能。
1.3 MML API概要说明
MML主要是由介质管理API(Media Management API)函数组成，MML API定义了Oracle软件与非Oracle产品的介质管理软件包之间的接口，
任何一个遵守这个API的介质管理软件包能够与Oracle7的EBU及Oracle8以后版本的RMAN协同工作。
MML API主要定义了一些标准C语言编写的函数头，这些函数名字上都以SBT(System Backup to Tape)作为开头，用来创建备份文件、从备份存储介质读、写、查找和删除备份文件。
API不负责备份设备、备份介质和备份介质库等的管理问题，诸如此类相关细节问题，包括每一个备份文件具体备份到哪个备份介质上，都由介质管理软件来负责实现。
1.几个基本概念
介质管理 API：
指实现MML的由Oracle提供的一组函数组成的接口，这些函数的名称、参数等规格说明由Oracle规定，函数体实现由介质管理软件来实现。
介质管理软件：
指MML API的程序代码实现者和存储介质驱动管理者。
API客户：
指介质管理软件的调用者，它既可以指Oracle7的EBU，也可以指由备份工具RMAN调用的Oracle8或以后版本的服务器进程。
工作单元 ：
指一个Unix进程或一个WindowsNT的线程。
API会话：
API函数被调用的一个序列，通常开始于s btinit函数，结束于sbtend函数。
一个工作单元只能开始一个API会话，但可以在结束一个会话后启动另一个API会话。相互分隔的工作单元可以启动并发的API会话。
在同一个API会话中，可以执行多个备份和恢复操作，但是一次仅能执行一个备份或恢复操作。
API环境上下文：
为运行备份介质管理软件由API客户分配的一个内存区域。
介质管理软件应把与API会话有关的所有状态信息存储到此内存区域。在多线程操作系统环境中，API客户保证为每一个API会话分配一个相互独立的API环境上下文。
在API会话开始时，由介质管理软件提出需要的API环境上下文存储区域的大小，然后由API客户创建并把它作为一个参数传递给每一个随后将要调用的 API函数序列中去。
API环境上下文的最大容量是10MB，如不够介质管理软件使用，可以自己另外单独再分配，在 API环境上下文中定义一个指向单独分配的区域的指针，即可使用。
2．MML API版本问题。
MML API的版本控制与大多数软件版本控制不大一样，不能向前兼容，即Oracle7的EBU不能升级支持 2．0版本的及以后版本的MML API，只能支持 版本1．1，
对于版本2．0的MML API的客户，则仅仅指由RMAN调用下的Oracle8或 Oracle9的服务器进程 。
其中，2．0版本对1．1版本有很多重大的扩充，如新增一些函数、修改一些数据结构，同时也保留了其中一些1．1版本的函数继续使用，如sbtbackup、sbtrestore。
3．MM API执行环境 。
在错误日志的处理方面，API客户会记录下由介质管理软件返回的任何一个错误，因此介质管理软件没必要在实现MML API时在自己的日志文件重复记录这些错误。
当然，当使用追踪文件时，可以记录在 MM API的追踪文件中。
在执行过程的追踪方面，介质管理软件必须写追踪数据到追踪文件，其文件名要传递给 API的sbtinit函数使用。
在版本2．0中，API客户提供三个级别的追踪，其中
级别0追踪所有的错误环境，
级别l追踪每一个SBT函数的入口和出口，
级别2除追踪每个SBT函数的入口和出口外，还包括所有函数的参数值，用十六进制形式表示的每个读写缓冲的开始32个字节的内容。
4．操作员接口。
对有些操作如手工更换磁带等需要人工干预时，介质管理软件必须将需人工执行的操作提示给操作员，并在人工操作完成后能够响应继续执行。
在早期版本中， 这种人工干预操作的提示和响应由介质管理软件自身之间的接口完成，完全不涉及API客户，
但在2．0及以后版本中，API客户通过消息形式告知介质管理软件，它能够发布消息给操作员并当操作完成后再给予响应． 这是通过 API函数sbtinit2的入口参数sbtinit2_input来实现的。
5．主要的数据结构和函数。
结构体sbtobject：正在备份或恢复的数据库对象；
结构体sbtinit_input：由API客户传递给函数sbtinit的初始化信息；
结构体sbtinit_output：由函数sbtinit返回给API客户的初始化信息；
结构体sbtbfinfo：备份文件信息；
结构体sbt_mms_fptr：由介质管理软件提供的指向实现的API函数的指针；
结构体sbtsiginit：指示介质管理软件需要处理的信号量的数据类型；
API中的接口函数有两大类，以2．0版本为例，分为常规API函数(Vendor API Routines) 和代理复制特征(Proxy Copy Feature)支持函数。
其中常规API函数包括12个函数．它们是：
sbtbackup
sbtclose2
sbtcommand
sbtend
sbterror
sbtinfo2
sbtinit
sbtinit2
sbtread2
sbtremove2
sbtrestore
sbtwrite2
以sbtwrite2为例说明其入口参数及功能情况：
int sbtwrite2(void* ctx, unsigned long flags，void* buf)，
函数sbtwrite2用来把buf指针指向的一段数据块(磁带块)写到在此之前用sbtbackup函数打开的备份文件中。
参数flags目前未用，保留作将来扩充，而参数ctx是指向API环境上下文结构体变量的指针。
代理复制特征的支持， 是可选的MML API的扩充，
目的是提供介质管理软件对数据库的备份恢复更复杂更高级的控制。
它共包括10个函数， 即
sbtpcbackup、
sbtpccancel、
sbtpccommit、
sbtpcend、
sbtpcquerybackup、
sbtwxtueryrestore、
sbtperestore、
sbtpcstart、
sbtpcstatus、
sbtpcvalidate等。
1．4 API实现注意问题
在编码实现API函数时，需注意以下几个问题 ，
首先，在同一个顺序介质设备上，介质管理软件不能从两个并发的API会话中同时地读入或写出数据流；
其次，所有的API函数不能递归调用；
第三，由于Oracle在备份时，可能会将多个数据库文件备份生成一个文件，这样可能会造成文件长度远远大于操作系统支持的文件长度最大字节限制，
    介质管理软件应通过sbtinit函数返回sbtinit_maxsize参数来设定单个文件的最大的长度；
第四，在 API函数实现上，尽可能少地创建或不创建新的进程或线程，以避免性能急剧下降；
第五，在 API会话期间，序列化的API函数调用之问，由于有的函数执行会有一个较长的时间，介质管理软件不能用限时中止 的方法来响应 API函 数在时间上的等待 。
2 MML API开发及调试、测试方法
无论是备份还是恢复，它们有两个相同点，
其一是在运行时API函数是处于一个共同的API会话进程之中，
其二是都要进行必须的初始化和结束终止会话等。
在编程开发API的每个函数体时，必须清楚这些函数被API客户调用的执行顺序，
当Oracle备份进程执行时，API调用的基本序列是：sbtbackup，sbtwrite，sbtclose，
其中sbtwrite被重复调用执行直到所有的数据被写完为止；
当Oracle恢复进程执行时，API调用的基本序列是：sbtrestore，sbtread，sbtclose，
其中sbtread被重复调用执行直到所有的数据被读完为止。
明确了MML API中备份与恢复执行的基本执行序列，就可以进一步编码实现每一个函数体应具备的功能。
因为所有这些API函数均是被Oracle服务会话调用，所以贯彻这些API函数实现上的一个宗旨是：
备份是从Oracle服务会话引出一个数据流，把它写到存储介质上去 ；
恢复则是从存储介质向Oracle服务会话导入一个数据流。
据此， 按照每个API函数的入口参数说明及功能编写相应的C语言代码编译生成.dll文件或.so文件。
实现API函数后，生成相应的库文件可以按Oracle的要求放到指定的目录位置，进行测试或与介质管理软件集成。
测试的基本方法有两个，
第一是利用 Oracle提供的测试程序sbttest进行调试或测试，sbttest是一个强大的功能程序，提供丰富多样的测试参数选项 ；
第二是使用 RMAN进行测试，即在RMAN中执行备份脚本程序，使Oracle会话调用API函数，从而对其调试或测试。

