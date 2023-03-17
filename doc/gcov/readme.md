## 用pip3命令安装，-U可以保证是最新版本会自动下载需要的3个python库：
yum -y install python3
pip3 install -U gcovr

下载安装：
git clone https://github.com/gcovr/gcovr.git
cd gcovr
python setup.py install --user


屏蔽相关代码的统计
如果需要屏蔽源代码中指定的代码行，则需要修改源代码内容，在源代码内容上加上屏蔽注释，然后重新进行代码编译，这样生成的新库，在执行程序时会自动跳过 打了注释的代码，自然就不会统计进去了
标签说明：
1、多行屏蔽：在需要屏蔽的代码前面加 // LCOV_EXCL_START
在代码后面加 // LCOV_EXCL_STOP
2、单行屏蔽：直接在单行代码后面加注释 // LCOV_EXCL_LINE
3、以上两种是直接将代码去掉不统计，还有一种屏蔽方法是，代码纳入统计，只是代码内的分支不纳入统计，用法类似：
//LCOV_EXCL_BR_START // LCOV_EXCL_BR_STOP
// LCOV_EXCL_BR_LINE
————————————————
版权声明：本文为CSDN博主「w慢慢」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_44073346/article/details/122809778