/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#ifndef __mkOutputMsg__
#define __mkOutputMsg__

#include <iostream>
#include <fstream>
#include <io.h>//for access()
//wchar -> char
inline string WcharToChar(const wchar_t* wp)
{
	std::string str;
	
	#ifdef __WINDOWS__ 
		const unsigned int m_encode = CP_ACP;//默认
		int len = WideCharToMultiByte(m_encode, 0, wp, (int)wcslen(wp), NULL, 0, NULL, NULL);
		char* m_char = new char[len + 1];
		WideCharToMultiByte(m_encode, 0, wp, (int)wcslen(wp), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		str = m_char;
		delete [] m_char;
	#endif
	return str;
}


//根据开关判断是否需要输出
inline bool EnableOutputLog(const string& onOfffilePath)
{
	//int   access(const   char   *filename,   int   amode); 
	//amode参数为0时表示检查文件的存在性，如果文件存在，返回0，不存在，返回-1
	bool fileExist = (access (onOfffilePath.c_str(), 0) == 0);
	return fileExist;
}

inline void WriteOutputLog(const string& logfilePath, const char* logbuf)
{
	fstream fs (logfilePath, fstream::app | fstream::out | fstream::ate);
	fs << logbuf << endl;
	fs.close ();
}

inline void PrintOutputLog(const char* logbuf)
{
	std::cout<<logbuf<<endl;
}

//format日志
inline void formatlog(char* logbuf, const char* moduleName, const char* file, int line, const char* funcName, const char* fmt, ...)
{
	//获取文件名
	#ifdef __WINDOWS__ 
		const char identify = '\\';
	#else 
		const char identify = '/';
	#endif
	const char* fileName = strrchr(file, identify) ? strrchr(file, identify) + 1 : file;
	
	//获取用户自定义buff
	char customBuf[2048];
	va_list ap;
	va_start(ap, fmt);
	::vsprintf (customBuf, fmt, ap);
	va_end (ap);
	
	//获取日志buff: [modulename] [date time]: (file:line) func() custom
	::sprintf(logbuf,"[%s] [%s %s]: (%s:%d) %s() %s", moduleName, __DATE__, __TIME__, fileName, line, funcName, customBuf);
}

//format日志
inline void formatlog(char* logbuf, const char* moduleName, const char* file, int line, const char* funcName, const wchar_t* fmt, ...)
{
	//获取文件名
	#ifdef __WINDOWS__ 
		const char identify = '\\';
	#else 
		const char identify = '/';
	#endif
	const char* fileName = strrchr(file, identify) ? strrchr(file, identify) + 1 : file;
	
	//获取用户自定义buff
	wchar_t customBuf[2048];
	va_list ap;
	va_start(ap, fmt);
	::vswprintf(customBuf, 2048, fmt, ap);
	//vswprintf_s(customBuf, 2048, fmt, ap);
	va_end (ap);
	string customBufStr = WcharToChar(customBuf);
	
	//获取日志buff: [modulename] [date time]: (file:line) func() custom
	::sprintf(logbuf,"[%s] [%s %s]: (%s:%d) %s() %s", moduleName, __DATE__, __TIME__, fileName, line, funcName, customBufStr.c_str());
}

//输出日志
#ifdef __WINDOWS__
	#define MK_OUTPUT_LOG(moduleName, WriterFunc, formatStr, ...)									\
		do {																						\
			char logbuf[4096];																		\
			formatlog(logbuf, moduleName, __FILE__, __LINE__, __func__, formatStr, __VA_ARGS__);	\
			WriterFunc(logbuf);																		\
		}while(0)
#else
	#define MK_OUTPUT_LOG(moduleName, WriterFunc, formatStr, ...)									\
		do {																						\
			char logbuf[4096];																		\
			formatlog(logbuf, moduleName, __FILE__, __LINE__, __func__, formatStr, ##__VA_ARGS__);	\
			WriterFunc(logbuf);																		\
		}while(0)
			
#endif //__WINDOWS__



#ifdef __WINDOWS__
	//将消息报写入日志文件中
	#define MK_WRITE_LOG(formatStr, ...)															\
	do {																							\
		if(!EnableOutputLog("C:\\monk\\on_off.txt") ) {break;}										\
		auto WriterFunc = std::bind(WriteOutputLog, "C:\\monk\\monk.log",std::placeholders::_1);	\
		MK_OUTPUT_LOG("monk", WriterFunc, formatStr, __VA_ARGS__);									\
	} while(0)
	
	//将消息打印到标志输出
	#define MK_PRINT_MSG(formatStr, ...)															\
	do {																							\
		MK_OUTPUT_LOG("monk", PrintOutputLog, formatStr, __VA_ARGS__);								\
	} while(0)
#else
	#define MK_WRITE_LOG(formatStr, ...)															\
	do {																							\
		if(!EnableOutputLog("/monk/on_off.txt") ) {break;}											\
		auto WriterFunc = std::bind(WriteOutputLog, "/monk/monk.log",std::placeholders::_1);		\
		MK_OUTPUT_LOG("monk", WriterFunc, formatStr, ##__VA_ARGS__);								\
	} while(0)
	
	#define MK_PRINT_MSG(formatStr, ...)															\
	do {																							\
		MK_OUTPUT_LOG("monk", PrintOutputLog, formatStr, ##__VA_ARGS__);							\
	} while(0)
#endif //__WINDOWS__


#endif //__mkOutputMsg__
