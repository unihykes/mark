/***************************************************************************************************
Author:liu.hao

Time:2018-7

info:

***************************************************************************************************/
#include "main.h"
#include "mkFrame.h"


///程序入口
class ncApp : public wxApp
{
public:
    ncApp()
    {
    }
    
    ~ncApp()
    {
    }
    
    virtual bool OnInit()
    {
        mkFrame *frame = new mkFrame("Hello World", wxPoint(100, 100), wxSize(1024, 768));
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(ncApp);


