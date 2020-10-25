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
#include "main.h"
#include "mkFrame.h"

enum {
	ID_Hello = 1
};


wxBEGIN_EVENT_TABLE(mkFrame, wxFrame)
    EVT_MENU(ID_Hello, mkFrame::OnHello)
    EVT_MENU(wxID_EXIT, mkFrame::OnExit)
    EVT_MENU(wxID_ABOUT, mkFrame::OnAbout)
wxEND_EVENT_TABLE()

mkFrame::mkFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H","Hello string show in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu * menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
    
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
    
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
    
    //目录树
    /*
    _hdtTreeCtrl = new wxTreeCtrl( this, HDT_TREE_EVENT, wxDefaultPosition, 
        wxSize(WX_SCREEN_WIDTH/4 , WX_SCREEN_HEIGHT), wxTR_DEFAULT_STYLE);
    _hdtTreeCtrl->AddRoot("aaa");
    */
}