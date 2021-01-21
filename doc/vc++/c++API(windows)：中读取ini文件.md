WritePrivateProfileString
http://baike.baidu.com/link?url=kIvCobLMqXS99NCX7Q7_Tfdge5bV9ANDmEat2-JSOM_ghri9zsc_7OP-CiGeqUlOWnDJyD7rfLXE0hgy8TQ6qK


GetPrivateProfileString
http://baike.baidu.com/view/1290400.htm


GetPrivateProfileInt
http://baike.baidu.com/view/1290395.htm




```cpp
//TODO:模拟数据库操作：将数据写入文件
void SaveToFile(const String& key, const String& value)
{
     String path = Path::getCurrentPath();
     String filePath = Path::combine(path, _T("userInfo.info"));
     WritePrivateProfileString(L"userInfo", key.getCStr(),value.getCStr(), filePath.getCStr());
}

// TODO:模拟数据库操作:读取数据
String ReadFromFile(const String& key)
{
     String path = Path::getCurrentPath();
     String filePath = Path::combine(path, _T("userInfo.info"));
    
     wchar_t buff[80] = {0};
     GetPrivateProfileString(L"userInfo", key.getCStr(), L"default", buff, 80, filePath.getCStr());
     String result(buff);
     return result;
}

String cidCSVFile = Path::combine(outputDirPath, ncGNSUtil::getCID(iter->GetGnsPath()));
cidCSVFile << _T(".csv");
StreamWriter write (cidCSVFile, true, UTF8_ENCODING);
String infoMsg;
infoMsg.format(_T("%s,%s,%s,%s,%s,%s"), _T("大小(byte)"), _T("大小(KB)"), _T("大小(MB)"), _T("大小(GB)"), _T("类型"), _T("gns路径"));
write.writeLine (infoMsg);
iter->PrintSubGnsInfo (write, callback);
write.close ();
```