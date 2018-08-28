/***************************************************************************************************
Author:liu.hao

Time:2018-7

info:

***************************************************************************************************/

#ifndef __mkFrame
#define __mkFrame

/// 主窗口
class mkFrame : public wxFrame 
{
public:
	mkFrame(const wxString & title, const wxPoint & pos, const wxSize & size);
    
private:
	void OnHello(wxCommandEvent & event)
    {
        wxLogMessage("Hello world from wxWidgets!");
    }
    
	void OnExit(wxCommandEvent & event)
    {
        Close(true);
    }
    
	void OnAbout(wxCommandEvent & event)
    {
        wxMessageBox("This is a wxWidgets' Hello World sample", "About Hello World", wxOK | wxICON_INFORMATION);
    }
    
	wxDECLARE_EVENT_TABLE();
    
private:
    wxTreeCtrl* 		_hdtTreeCtrl;           //目录树控件
};


#endif