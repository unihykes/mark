
按钮控件类：
asBitmapTextButton：封装于 #include "sharecmn/baseui/bitmapbtn.h"
asBackgroundDlg：封装于 #include "sharecmn/baseui/backgrounddlg.h"

DEFPUSHBUTTON:
DEFPUSHBUTTON与PUSHBUTTON的区别居然搞半天才明白，原来defbutton就是默认选中的按钮。

可移动窗口:
void asSetDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
        //添加这句可使窗口移动
PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
asBackgroundDlg::OnLButtonDown(nFlags, point);
}

自动调节按钮大小：
Window::SizeToContent 属性 

文件变化监控：
FILE_NOTIFY_CHANGE_FILE_NAME
文件被建立，删除，移动
FILE_NOTIFY_CHANGE_DIR_NAME
文件夹被建立，删除，移动
FILE_NOTIFY_CHANGE_ATTRIBUTES  
文件或文件夹的任何属性改变
FILE_NOTIFY_CHANGE_SIZE
文件或文件夹的尺寸改变，仅当任何缓存写回到磁盘时才有这个感觉。
FILE_NOTIFY_CHANGE_LAST_WRITE
文件或文件夹的最近写入时间改变，
仅当任何缓存写回到磁盘时才有这个感觉。
FILE_NOTIFY_CHANGE_SECURITY
文件或文件夹的任何安全描述符改变

Overlay Icon shell：
http://www.codeproject.com/Articles/7484/How-to-overlay-an-icon-over-existing-shell-objects

