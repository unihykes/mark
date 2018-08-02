/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#ifndef __mkOutputMsg__
#define __mkOutputMsg__

#include <iostream>
#include <fstream>
#include <ctime>

#ifdef __WINDOWS__
    #include <io.h>//for access()
#endif

#define MK_PRINT_MSG(...)															\
    mkOutputMsg().OutputMsg(mkOutputMsg::mkOutputMsgType::MK_PRINT, "monk", __FILE__, __LINE__, __func__, ##__VA_ARGS__);
    
#define MK_TRACE(...)		    													\
    mkOutputMsg().OutputMsg(mkOutputMsg::mkOutputMsgType::MK_TRACE, "monk", __FILE__, __LINE__, __func__, ##__VA_ARGS__);

#define MK_LOG(...)		    													\
    mkOutputMsg().OutputMsg(mkOutputMsg::mkOutputMsgType::MK_LOG, "monk", __FILE__, __LINE__, __func__, ##__VA_ARGS__);

#define MK_PRINT        MK_PRINT_MSG
#define mkPrint         MK_PRINT
#define mkTrace         MK_TRACE
#define mkLog           MK_LOG

class mkOutputMsg
{
public:
    //消息输出类型
    enum class mkOutputMsgType
    {
        MK_PRINT,
        MK_TRACE,
        MK_LOG,
    };
    
    //空msg
    inline void OutputMsg(mkOutputMsgType type, const char* moduleName, const char* file, int line, const char* funcName)
    {
        OutputMsg(type, moduleName, file, line, funcName, "");
    }
    
    //T可以为char或者wchar_t
    template<typename T>
    inline void OutputMsg(mkOutputMsgType type, const char* moduleName, const char* file, int line, const char* funcName, const T* fmt, ...)
    {
        #ifdef __WINDOWS__
            #define TRACE_FILE_PATH         "C:\\monk\\monk.trace"
            #define LOG_FILE_PATH           "/monk/monk.log"
        #else
            #define TRACE_FILE_PATH           "C:\\monk\\monk.trace"
            #define LOG_FILE_PATH           "/monk/monk.log"
        #endif
        
        //检查trace是否打开,未打开直接返回
        if(type == mkOutputMsgType::MK_TRACE) {
            //int   access(const   char   *filename,   int   amode); 
            //amode参数为0时表示检查文件的存在性，如果文件存在，返回0，不存在，返回-1
            bool fileExist = (access (TRACE_FILE_PATH, 0) == 0);
            if(!fileExist) {
                return;
            }
        }
        
        //解析消息体buff
        char msgBuf[4096];
        va_list args;
        va_start(args, fmt);
        //消息buff: [modulename] [date time]: (file:line) func() custom
        ::sprintf(msgBuf,"[%s] [%s]: (%s:%d) %s() %s", 
            moduleName, GetCurrentTime().c_str(), FormatFileName(file), line, funcName, GetMsgBuf(fmt, args).c_str());
        va_end (args);
        
        //do it!
        switch(type) {
            case mkOutputMsgType::MK_PRINT:
                std::cout<<msgBuf<<endl;//将消息打印到标准输出
                break;
                
            case mkOutputMsgType::MK_TRACE:
                WriteOutputBuf(TRACE_FILE_PATH, msgBuf);//将消息写入trace文件中
                break;
                
            case mkOutputMsgType::MK_LOG:
                WriteOutputBuf(LOG_FILE_PATH, msgBuf);//将消息写入log文件中
                break;
                
            default:
                break;
        }
    }
    
private:
    //format日志, fmt为char*
    string GetMsgBuf(const char* fmt, va_list& args)
    {
        //获取用户自定义buff
        char customBuf[2048];
        ::vsprintf (customBuf, fmt, args);
        string customBufStr = customBuf;
        return customBufStr;
    }
    
    //format日志, fmt为wchar_t*
    string GetMsgBuf(const wchar_t* fmt, va_list& args)
    {
        //wchar -> char
        auto WcharToChar = [](const wchar_t* wp) ->string {
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
        };
        
        //获取用户自定义buff
        wchar_t customBuf[2048];
        ::vswprintf(customBuf, 2048, fmt, args);
        string customBufStr = WcharToChar(customBuf);
        return customBufStr;
    }
    
    //获取当前时间
    string GetCurrentTime()
    {
        time_t rawtime;
        time(&rawtime); 
        string result = ctime(&rawtime);
        result.erase(result.find('\n'), 1);//移除末尾\n
        return result;
    };
    
    //获取文件名
    const char* FormatFileName(const char* file)
    {
        #ifdef __WINDOWS__ 
            const char identify = '\\';
        #else 
            const char identify = '/';
        #endif
        const char* fileName = strrchr(file, identify) ? strrchr(file, identify) + 1 : file;
        return fileName;
    }
    
    //将buf写入文件
    void WriteOutputBuf(const string& msgFilePath, char* msgBuf) 
    {
        fstream fs (msgFilePath, fstream::app | fstream::out | fstream::ate);//追加写
        fs << msgBuf << endl;
        fs.close ();
    };
};


#endif //__mkOutputMsg__
