
GMP下载地址：
ftp://ftp.gnu.org/gnu/gmp/
```shell
wget ftp://ftp.gnu.org/gnu/gmp/gmp-5.0.1.tar.bz2
tar -vxf gmp-5.0.1.tar.bz2
cd gmp-5.0.1/
./configure --prefix=/usr/local/gmp-5.0.1
make
sudo make install
```
MPFR下载地址：
https://ftp.gnu.org/gnu/mpfr/
```shell
wget https://ftp.gnu.org/gnu/mpfr/mpfr-3.1.5.tar.xz
tar -vxf mpfr-3.1.5.tar.gz
cd mpfr-3.1.5/
./configure --prefix=/usr/local/mpfr-3.1.5 --with-gmp=/usr/local/gmp-5.0.1
make
sudo make install
```


MPC下载地址：
http://www.multiprecision.org/mpc/download.html
```shell
wget http://www.multiprecision.org/downloads/mpc-0.9.tar.gz
tar -vxf mpc-0.9.tar.gz
cd mpc-0.9/
./configure --prefix=/usr/local/mpc-0.9 --with-gmp=/usr/local/gmp-5.0.1 --with-mpfr=/usr/local/mpfr-3.1.5
make
sudo make install
```


gcc下载地址：
https://ftp.gnu.org/gnu/gcc/
```shell
../configure --prefix=/usr/local/gcc-10.2.0/ --enable-checking=release --enable-languages=c,c++ --disable-multilib --with-gmp=/usr/local/gmp-5.0.1 --with-mpfr=/usr/local/mpfr-3.1.5 --with-mpc=/usr/local/mpc-0.9

make
sudo make install 

```
gcc高版本（gcc-10.2.0）编译
https://blog.csdn.net/weixin_38184741/article/details/107681479