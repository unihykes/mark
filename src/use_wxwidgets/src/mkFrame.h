/***************************************************************************************************
LICENSE:
    Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
Author:liu.hao(33852613@163.com)

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