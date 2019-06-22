// publicvoid test(){


// 打开子键

HKEY hRootKey = HKEY_LOCAL_MACHINE;

String targetKey = _T("Software\\Eisoo Software\\ShareClient");

HKEY hKey;

if (RegOpenKeyEx (hRootKey, targetKey.getCStr(), 0, KEY_ALL_ACCESS,  &hKey) != ERROR_SUCCESS)

return;

// 获取子键信息

DWORD NameCnt,NameMaxLen;

DWORD KeyCnt,KeyMaxLen;

DWORD MaxDateLen;

if(RegQueryInfoKey(hKey,NULL,NULL,NULL,&KeyCnt,&KeyMaxLen,NULL,&NameCnt,&NameMaxLen,&MaxDateLen,NULL,NULL) != ERROR_SUCCESS)

return;

KeyMaxLen++;

NameMaxLen++;

MaxDateLen++;

// 枚举子键

for(int i = 0;i != KeyCnt; i++) {


TCHAR achKey[MAX_KEY_LENGTH];

if(RegEnumKeyEx(hKey, i, achKey, &KeyMaxLen, NULL, NULL, NULL, NULL) != ERROR_SUCCESS)

break;

// 子键的子键键名

String valueName = LPCTSTR(achKey);

          }
          // 枚举子键值
          for(int i = 0;i != NameCnt; i++) {


TCHAR achKey[MAX_KEY_LENGTH];

DWORD dwcbData =  MaxDateLen ;

BYTE byteData[255];

ZeroMemory (byteData, sizeof (BYTE) *  MaxDateLen );

// 获取索引为i的键值

if(RegEnumValue (hKey, i, achKey, &NameMaxLen, NULL, NULL, (LPBYTE)byteData, &dwcbData) != ERROR_SUCCESS)

break;

// 键值名称

String valueName = LPCTSTR(achKey);

String valueDate = (LPCTSTR)byteData;

// 测试 RegQueryValueEx()

DWORD dwcbData2 =  MaxDateLen ;

BYTE byteData2[255];

ZeroMemory (byteData2, sizeof (BYTE) *  MaxDateLen );

if (RegQueryValueEx (hKey, valueName.getCStr(), NULL, NULL, (LPBYTE)byteData2, &dwcbData2) != ERROR_SUCCESS)

return;

          }

          // 关闭该键
          RegCloseKey (hKey);
}