## 编译方式
cd \mark\3rd_Party\gflags\gflags
mkdir build_gflags
cmake ..
在 build_gflags 目录中会生成 include 目录
备注:不同平台生成的include目录不一样,不可混用;

将include 拷贝到 \mark\3rd_Party\gflags\include

cd \mark\3rd_Party\gflags
maked cleanall
maked
