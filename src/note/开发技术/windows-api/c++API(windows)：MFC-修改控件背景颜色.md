

简介：
在MFC类库提供了CWnd::OnCtlColor函数,在工作框架的子窗口被重画时将调用该成员函数.
因此可以重载WM_CTLCOLOR消息的响应函数.此函数的原型:
  afx_msg HBRUSH OnCtlColor(CDC *pDC,CWnd *pWnd,UINT nCtlColor);
           参数nCtlColor用于指定控件的类型,可以是:
           .CTLCOLOR_BTN                按钮控件   //(注意check box 属于button控件)
           .CTLCOLOR_DLG                对话框
           .CTLCOLOR_EDIT               编辑框
           .CTLCOLOR_LISTBOX            列表控件
           .CTLCOLOR_MSGBOX             消息控件
           .CTLCOLOR_SCROLLBAR 滚动条控件
           .CTLCOLOR_STATIC             静态控件

程序实现：
假设你已有了名为My的对话框工程.你有了一个STATIC的控件，ID为IDC_STATIC1.
HBRUSH CMyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
// TODO: Change any attributes of the DC here
if (nCtlColor==CTLCOLOR_STATIC)
{
pDC->SetTextColor(RGB(255,0,0));  //字体颜色
pDC->SetBkColor(RGB(0, 0, 255));   //字体背景色  
}
// TODO: Return a different brush if the default is not desired
return hbr;
}

如果要指定某个特定控件可以这样写：ID为IDC_STATIC1
if (pWnd->GetDlgCtrlID()==IDC_STATIC1)
{
pDC->SetTextColor(RGB(255,0,0));  //设置字体颜色
pDC->SetBkMode(TRANSPARENT); //设置字体背景为透明
// TODO: Return a different brush if the default is not desired
return (HBRUSH)::GetStockObject(BLACK_BRUSH);  // 设置背景色
}
else
return hbr;

【注】
BLACK_BRUSH:黑色
WHITE_BRUSH:白色
GRAY_BRUSH:灰色
NULL_BRUSH:透明
HOLLOW_BRUSH ：透明

1.为对话框类添加WM_CTLCOLOR的响应函数afx_msg HBRUSH OnCtlColor（CDC*pDC,CWnd*pWnd,UINT nCtlColor）{...}
2.定义一个m_brush（CBrush类型）的成员变量和一个m_font(CFont类型)成员变量，在构造函数中初始化，例 如：m_brush.CreateSolidBrush（RGB（0，0，255））;
m_font.CreatePointFont(200,"华文行 楷");
3.改变背景颜色和文本颜色和字体：在OnCtlColor（）添加代码：
if(pWnd->GetDlgCtrlID()==IDC_LINE_STYLE)
{

pDC->SetTextColor(RGB(255,0,0));
pDC->SetBkMode(TRANSPARENT);//设置文本背景色为透明
pDC->SelectObject(&m_font);//设置字体
return m_brush；//设置控件背景颜色

}

//对于按钮来说上面的方法无效
3. 设置控件ID为IDC_SYSFONTSAMPLE的背景颜色与其背景图片一致方法如下：
if(pWnd->GetDlgCtrlID()==IDC_SYSFONTSAMPLE)
{
   // 设置控件背景色与背景图片颜色一致
     COLORREF bkColor = RGB(239,239,239); //背景图片的颜色值
    pDC->SetBkColor(bkColor);
    return (HBRUSH)::GetStockObject(NULL_BRUSH); 
}
