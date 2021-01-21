#关闭PE的防火墙
    netsh firewall set opmode disable



#设置休眠/关机命令
    开启休眠功能：powercfg -h on
    关闭休眠功能：powercfg -h off
    执行休眠/睡眠：rundll32.exe powrprof.dll,SetSuspendState

    关机：shutdown     /s
    重启：shutdown     /r
    立刻重启：shutdown /r /t 0


#修改win10的onedriver图标重叠注册表
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers



#删除win10系统文件夹
    HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\MyComputer\NameSpace\


    {1CF1260C-4DD0-4ebb-811F-33C572699FDE} 音乐
    {374DE290-123F-4565-9164-39C4925E4678} 下载
    {3ADD1653-EB32-4cb0-BBD7-DFA0ABB5ACCA} 图片
    {A0953C92-50DC-43bf-BE83-3742FED03C9C} 视频
    {A8CDFF1C-4878-43be-B5FD-F8091C1C60D0} 文档
    {B4BFCC3A-DB2C-424C-BO29-7FE99A87C641} 桌面

    注意到win10和8.1的还是有点不同所以  之前的批处理应该也不行，只能手动自己删吧！
    

#dxdiag判断电脑是32位还是64位
     win7系统直接右键【计算机】，选择属性即可；对于xp系统：方法一:开始＞运行中输入“cmd“，然后在命令提示符窗口中输入systeminfo 如果你的系统是64位的，会在“OS 名称: Microsoft Windows XP Professional”一行后明确标示出“x64 Edition”，否则你的系统就是32位的。 



    方法二:
    开始>运行中输入“winver”，如果你的系统是64位的，同样会明确标示出“x64 Edition”。


    方法三：
    cmd输入：dxdiag
#强制杀进程
杀进程
taskkill /F /IM explorer.exe