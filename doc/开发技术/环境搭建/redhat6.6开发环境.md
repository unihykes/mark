安装系统；

配置网络；

gcc依赖包安装：
http://blog.csdn.net/u011150719/article/details/42815857
./configure --prefix=/usr/local/gmp-5.0.1
make
make install

./configure --prefix=/usr/local/mpfr-3.1.0 --with-gmp＝/usr/local/gmp-5.0.1
make
make install

./configure --prefix=/usr/local/mpc-0.9    --with-gmp＝/usr/local/gmp-5.0.1 --with- mpfr=/usr/local/mpfr-3.1.0
make
make install

设置环境变量：
export  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/mpc-0.9/lib:/usr/local/mpfr-3.1.0/lib:/usr/local/gmp-5.0.1/lib

vi /etc/profile
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/gcc-4.9.2/lib64:/usr/local/mpc-0.9/lib:/usr/local/mpfr-3.1.0/lib:/usr/local/gmp-5.0.1/lib

:/home/program/targets/Redhat_5_x64/libs/Debug/lib64


gcc安装：
下载gcc:
http://ftp.gnu.org/gnu/gcc/

安装gcc-4.9.2
./configure --prefix=/usr/local/gcc-4.9.2 --with-mpfr=/usr/local/mpfr-3.1.0 --with-gmp=/usr/local/gmp-5.0.1 --with-mpc=/usr/local/mpc-0.9
make
make install


运行gdb报错：
./x86_64-unknown-linux-gdb: error while loading shared libraries: libexpat.so.0: cannot open shared object file: No such file or directory
则运行：
ln -s /lib64 libexpat.so.1 libexpat.so.0

安装cmake
上传文件 cmake-2.8.12.2-4.el6.x86_64.rpm
rpm -ivh cmake-2.8.12.2-4.el6.x86_64.rpm

创建挂载点；
cd /
mkdir /opt/cdplog
mkdir /opt/liuhaopc_E

添加磁盘并格式化，挂载；
mkfs.ext4 /dev/sdb     
mkfs.ext4 /dev/sdc
vi /etc/fstab
/dev/sdb                     /home              ext4     defaults        0 0
/dev/sdc                     /opt/cdplog      ext4     defaults        0 0 
重启；

配置共享盘;
vi /etc/fstab
//192.168.52.223/e     /opt/liuhaopc_E       cifs     auto,username=aaaaaa,password=aaaaaaa 0 0
mount -a
