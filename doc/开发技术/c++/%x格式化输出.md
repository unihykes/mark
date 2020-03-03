

#%x什么意思
```cpp
%a,%A 读入一个浮点值(仅C99有效) 　　
%c 读入一个字符 　　
%d 读入十进制整数 　　
%i 读入十进制，八进制，十六进制整数 　　
%o 读入八进制整数 　　
%x,%X 读入十六进制整数 　　
%s 读入一个字符串，遇空格、制表符或换行符结束。 　　
%f,%F,%e,%E,%g,%G 用来输入实数，可以用小数形式或指数形式输入。 　　
%p 读入一个指针 　　
%u 读入一个无符号十进制整数 　　
%n 至此已读入值的等价字符数 　　
%[] 扫描字符集合 　　
%% 读%符号


# c语言中%c与%s的区别、以及补充%%
%c格式对应的是单个字符，%s格式对应的是字符串。
例：char  a;
     char b[20];
     scanf("%c",&a);          //只能输入一个字符。
     scanf("%s",b);            //可以输入一串字符串。


要输出百分号，则可以:
String msg;
msg.format(_T("%d%%"), i);
```



#%x和%X
```cpp
%X跟%x是输出十六进制数字，%X是输出的十以上的字母大写，%x是输出十以上的字母小写。

关于char型与unsigned char型数据使用格式化输出注意点
https://www.cnblogs.com/fogcell/p/6714294.html


　　在使用 socket(AF_INET, SOCK_DGRAM, 0); 打开一个套接字流，通过 ioctl(s, SIOCGIFHWADDR, &ifr) 获取网卡的mac地址的时候，需要将 struct ifreq ifr; 结构体中 ifr.ifr_hwaddr.sa_data 数组中的信息按照十六进制提取到字符串中去，程序中使用到了

sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
            ifreq.ifr_hwaddr.sa_data[0],
            ifreq.ifr_hwaddr.sa_data[1],
            ifreq.ifr_hwaddr.sa_data[2],
            ifreq.ifr_hwaddr.sa_data[3],
            ifreq.ifr_hwaddr.sa_data[4],
            ifreq.ifr_hwaddr.sa_data[5]);

　　提取到mac中，但是原本Mac地址为 48:4d:7e:b1:e2:7e 存在结果字符输出 48:4D:7E:FFFFFFB1:FFFFFFE2:7E 。这明显不正常，如果使用如下的方式获取则没有问题
unsigned char mac[6];
memcpy(mac, ifr.ifr_hwaddr.sa_data, sizeof(mac));
sprintf(buffer, "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
　　当时考虑到是否是因为不同Linux内核中的结构体 struct ifreq ifr; 中存在差异才导致问题，后来查找到.ifr_hwaddr.sa_data原型为char sa_data[14]。经过相关搜索，问题的原因如下：
　　有符号char型的数值范围是-128-127因此大于0x7F的数在char型下其符号位则为1,因此当以%X格式化输出的时候，会把这个类型的值拓展，通常拓展到int型的32位，那么会对char类型的最高位进行拓展，%x期望的数据类型应该是unsigned int型，因此char转换到unsigned int也会拓展符号位，也就是强制类型转换了。
　　当为char类型的时候，如果最高位是1,意思是超过了0x7F的数则会被拓展为32位的FFFFFFB1。所以会出现这种情况。但是第二种方法则是直接指定从指针指向的值提取，因此不会出现这种带有符号位的情况。即，使用%x格式化输出的时候，一般char数据会被拓展到int型大小，一般为32位。
　　可以通过(unsigned char)ifreq.ifr_hwaddr.sa_data[5]来解决问题。使用%x输出格式的时候需要将所需要的数据转换为无符号类型，因为%x期望对应的参数应该为unsigned int型。
```

#printf按8进制、16进制输出
```cpp
printf()8进制、16进制输出格式控制：
    int num = 0x9;


    /*输出4位8进制的num*/
    printf("%04o/n",num);


    /*输出2位16进制的num*/
    printf("%02x",num);
 
结果：
     0011
     09
	 

```


#输出小数点

```cpp
	double currentProgress = double(currentBlockNum*100) / (double)_totleBlockNum;
	if ((currentProgress - _lastProgress) >= 1.0) {
	   String msg;
	   msg.format(_T("%.2f"), currentProgress);
	   _listener->OnMessage (msg);
	}
```


#vsnprintf和snprintf
```cpp

#include <stdio.h>
       int printf(const char *format, ...); //输出到标准输出
       int fprintf(FILE *stream, const char *format, ...); //输出到文件
       int sprintf(char *str, const char *format, ...); //输出到字符串str中
       int snprintf(char *str, size_t size, const char *format, ...); //按size大小输出到字符串str中
   
以下函数功能与上面的一一对应相同，只是在函数调用时，把上面的...对应的一个个变量用va_list调用所替代。在函数调用前ap要通过va_start()宏来动态获取。
#include <stdarg.h>
       int vprintf(const char *format, va_list ap);
       int vfprintf(FILE *stream, const char *format, va_list ap);
       int vsprintf(char *str, const char *format, va_list ap);
       int vsnprintf(char *str, size_t size, const char *format, va_list ap);



可变参数列表va_list宏说明：
       void va_start(va_list ap, last);
       void va_end(va_list ap搜索);
•va_start与va_end是成对被调用的，
•开始的时候被调用va_start，获得各输出变量地址
•结束的时候被调用va_end，释放相应的资源

```