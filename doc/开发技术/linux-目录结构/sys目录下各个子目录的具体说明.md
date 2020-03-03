
```
http://tscsh.blog.163.com/blog/static/20032010320131051738843/

/sys下的子目录

内容
 # ls /sys/
block     class     firmware  kernel    power
bus       devices   fs        module
-----------------------------------------------------------------------------------------------------------------------------
1./sys/devices
# ls /sys/devices/
platform  system

# ls /sys/devices/platform/
dm9000.0        s3c2410-rtc     s3c2440-uart.0  s3c24xx_led.2 
power           s3c2410-wdt     s3c2440-uart.1  s3c24xx_led.3
s3c2410-iis     s3c2440-i2c     s3c2440-uart.2  serial8250
s3c2410-lcd     s3c2440-nand    s3c24xx_led.0   serial8250.0
s3c2410-ohci    s3c2440-sdi     s3c24xx_led.1   uevent
# ls /sys/devices/system/
clocksource   s3c2410-core  s3c2440-core  s3c2443-core  timekeeping
cpu           s3c2412-core  s3c2442-core  s3c24xx-dma   timer
该目录下是全局设备结构体系，包含所有被发现的注册在各种总线上的各种物理设备。一般来说，所有的物理设备都按其在总线上的拓扑结构来显示，但有两个例外，即platform devices和system devices。platform devices一般是挂在芯片内部的高速或者低速总线上的各种控制器和外设，它们能被CPU直接寻址；system devices不是外设，而是芯片内部的核心结构，比如CPU，timer等，它们一般没有相关的驱动，但是会有一些体系结构相关的代码来配置它们。
(sys/devices是内核对系统中所有设备的分层次表达模型，也是/sys文件系统管理设备的最重要的目录结构)
 ----------------------------------------------------------------------------------------------------------------------------
2.sys/dev
该目录下维护一个按照字符设备和块设备的主次号码(major:minor)链接到真是设备(/sys/devices)的符号链接文件。
---------------------------------------------------------------------------------------------------------------------------- 
3./sys/class
# ls /sys/class/
graphics      misc          printer       sound         vc
hwmon         mmc_host      rtc           spi_master    vtconsole
i2c-adapter   mtd           scsi_device   tty
input         net           scsi_disk     usb_endpoint
mem           ppdev         scsi_host     usb_host
该目录下包含所有注册在kernel里面的设备类型，这是按照设备功能分类的设备模型，每个设备类型表达具有一种功能的设备。每个设备类型子目录下都是这种设备类型的各种具体设备的符号链接，这些链接指向/sys/devices/name下的具体设备。设备类型和设备并没有一一对应的关系，一个物理设备可能具备多种设备类型；一个设备类型只表达具有一种功能的设备，比如：系统所有输入设备都会出现在/sys/class/input之下，而不论它们是以何种总线连接到系统的。(/sys/class也是构成linux统一设备模型的一部分)
---------------------------------------------------------------------------------------------------------------------------- 
/sys/block
# ls /sys/block/
loop0      loop4      mtdblock0  ram0       ram12      ram2       ram6
loop1      loop5      mtdblock1  ram1       ram13      ram3       ram7
loop2      loop6      mtdblock2  ram10      ram14      ram4       ram8
loop3      loop7      mtdblock3  ram11      ram15      ram5       ram9
该目录下的所有子目录代表着系统中当前被发现的所有块设备。按照功能来说放置在/sys/class下会更合适，但由于历史遗留因素而一直存在于/sys/block，但从linux2.6.22内核开始这部分就已经标记为过去时，只有打开了CONFIG_SYSFS_DEPRECATED配置编译才会有这个目录存在，并且其中的内容在从linux2.6.26版本开始已经正式移到了/sys/class/block，旧的接口/sys/block为了向后兼容而保留存在，但其中的内容已经变为了指向它们在/sys/devices/中真实设备的符号链接文件。
 ----------------------------------------------------------------------------------------------------------------------------
/sys/bus
# ls /sys/bus/
i2c       mmc       platform  scsi      serio     spi       usb
该目录下的每个子目录都是kernel支持并且已经注册了的总线类型。这是内核设备按照总线类型分层放置的目录结构，/sys/devices中的所有设备都是连接于某种总线之下的，bus子目录下的每种具体总线之下可以找到每个具体设备的符号链接，一般来说每个子目录(总线类型)下包含两个子目录，一个是devices，另一个是drivers；其中devices下是这个总线类型下的所有设备，这些设备都是符号链接，它们分别指向真正的设备(/sys/devices/name/下)；而drivers下是所有注册在这个总线上的驱动，每个driver子目录下 是一些可以观察和修改的driver参数。
(它也是构成linux统一设备模型的一部分)
-----------------------------------------------------------------------------------------------------------------------------
/sys/fs
【空】
按照设计，该目录使用来描述系统中所有的文件系统，包括文件系统本身和按照文件系统分类存放的已挂载点。
-----------------------------------------------------------------------------------------------------------------------------
/sys/kernel
# ls /sys/kernel/
uevent_helper  uevent_seqnum
这个目录下存放的是内核中所有可调整的参数
-----------------------------------------------------------------------------------------------------------------------------
/sys/firmware
【空】
该目录下包含对固件对象(firmware object)和属性进行操作和观察的接口，即这里是系统加载固件机制的对用户空间的接口.(关于固件有专用于固件加载的一套API)
-----------------------------------------------------------------------------------------------------------------------------
/sys/hypervisor【X】
该目录是与虚拟化Xen相关的装置。(Xen是一个开放源代码的虚拟机监视器)
-----------------------------------------------------------------------------------------------------------------------------
/sys/module
# ls /sys/module/
8250          loop          rcupdate      snd_pcm       usb_storage
atkbd         lp            rd            snd_soc_core  usbcore
dm9dev9000c   mousedev      s3c2410_wdt   snd_timer     usbhid
hid           nfs           s3c_ts        sunrpc        vt
keyboard      ohci_hcd      scsi_mod      tcp_cubic     yaffs
lockd         printk        snd           tsdev
该目录下有系统中所有的模块信息，不论这些模块是以内联(inlined)方式编译到内核映像文件中还是编译为外模块(.ko文件)，都可能出现在/sys/module中。即module目录下包含了所有的被载入kernel的模块。
---------------------------------------------------------------------------------------------------------------------------- 
/sys/power
\# ls /sys/power/
state
该目录是系统中的电源选项，对正在使用的power子系统的描述。这个目录下有几个属性文件可以用于控制整个机器的电源状态，如可以向其中写入控制命令让机器关机/重启等等。

```