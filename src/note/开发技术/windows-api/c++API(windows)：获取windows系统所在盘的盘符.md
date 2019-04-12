
#include "stdafx.h"
#include <atlstr.h>
#include <iostream>
using namespace std;

int main( int argc, char** argv )    
{
char str[MAX_PATH];    
char outstr[] = "系统的盘符是";    
GetSystemDirectory(str, MAX_PATH);    
outstr[12] = str[0];
cout<<outstr<<endl;
//MessageBox( NULL, outstr, "系统消息", MB_OK); 
return 0; 
}


以上是获取系统所在盘的盘符，以下是获取所有分区的盘符：

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
TCHAR szBuf[100];
memset(szBuf,0,100);

DWORD len=GetLogicalDriveStrings(sizeof(szBuf)/sizeof(TCHAR),szBuf);

for (TCHAR * s= szBuf;  *s;  s+=_tcslen(s)+1){
LPCTSTR sDrivePath = s;
cout<<sDrivePath<<endl;
}
Sleep(2000);
return 0;

}