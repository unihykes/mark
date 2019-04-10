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


