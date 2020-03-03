
## 使用 OpenSSL API 进行安全编程
http://www.ibm.com/developerworks/cn/linux/l-openssl.html


## Linux下调用openssl找不到头文件
    查看当前机器是否已经安装OpenSSL以及其版本
    openssl version -a

    [root@rhel6 ~]# rpm -qa | grep openssl
    openssl-1.0.0-4.el6.i686    <------看 我安装了openssl
    [root@rhel6 ~]# gcc test.c -lcrypto  <------编译你的代码 找不到头文件 和你一样一堆错误 错误就不贴了

    [root@rhel6 ~]# yum -y install openssl-devel  <---------安装openssl-devel
    [root@rhel6 ~]# gcc test.c -lcrypto   <--------------再次编译你的代码 OK了！
    [root@rhel6 ~]# ./a.out
    cleartext:hehehe Encrypted! ciphertext:d999dbcfc047a504 Decrypted! cleartext:hehehe [root@rhel6 ~]#    <-------执行也OK了（貌似你输出没有换行）


## linux下编译openssl
    查看当前机器是否已经安装OpenSSL以及其版本
    openssl version -a


    下载zlib库
    地址：http://zlib.net/zlib-1.2.11.tar.gz
    上传至/home目录下


    编译安装zlib库
    $ cd /home
    $ tar -zxvf zlib-1.2.11.tar.gz
    $ cd zlib-1.2.11
    $ ./configure --prefix=/home/depslibs/zlib
    $ make
    $ make install
    $ make clean



    下载OpenSSL
    地址：http://www.openssl.org/source/
    openssl-1.0.1p.tar.gz上传至/home目录下


    解压OpenSSL
    $ cd /home
    $ tar -zxvf openssl-1.0.1p.tar.gz
    $ cd openssl-1.0.1p


    编译并安装openssl
    $ ./config enable-shared --prefix=/home/depslibs/openssl/ --openssldir=/home/depslibs/zlib
    $ make
    $ make install
    $ make clean


    然后把响应的include和lib文件copy到deps目录指定位置；