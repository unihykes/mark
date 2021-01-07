/**
*
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  The ASF licenses
* this file to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef __ncMsgLogger
#define __ncMsgLogger

#ifndef _WIN32
    #include <sys/syscall.h>
#endif
#include <fstream>


class MsgLogger
{
    __interface_body__(MsgLogger)
public:
    enum log_level
    {
        Level_debug = 0x0,
        Level_info,
        Level_warn,
        Level_error
    };
public:
    virtual void debug(const std::string& log_line) = 0;
    virtual void info(const std::string& log_line) = 0;
    virtual void warn(const std::string& log_line) = 0;
    virtual void err(const std::string& log_line) = 0;
    virtual void flush()  = 0;
};

// logger implementation
class ncMsgLogger : public MsgLogger
{
public:
    ncMsgLogger(const std::string& log_file, MsgLogger::log_level level)
        : level_(level)
        , fs_(log_file)
        , buffer_()
        , lock_()
    {
    }

    virtual ~ncMsgLogger()
    {
        flush();
        fs_.flush();
        fs_.close();
    }

    __nocopy__(ncMsgLogger)

public:
    virtual void debug(const std::string& log_line)
    {
        if (level_ <= 0) {
            write_log("dbug", log_line);
        }
    }

    virtual void info(const std::string& log_line)
    {
        if (level_ <= 1) {
            write_log("info", log_line);
        }
    }

    virtual void warn(const std::string& log_line)
    {
        if (level_ <= 2) {
            write_log("warn", log_line);
        }
    }

    virtual void err(const std::string& log_line)
    {
        if (level_ <= 3) {
            write_log("errr", log_line);
        }
    }

    virtual void flush()
    {
        std::queue<std::string> backup;
        {
            std::lock_guard<std::mutex> guard(lock_);
            if (buffer_.size() > 0) {
                backup.swap(buffer_);
            }
        }

        while (backup.size() > 0) {
            std::string& line = backup.front();
            fs_ << line << std::endl;
            backup.pop();
        }
    }

private:
    unsigned int GetThreadId()
    {
        #ifdef _WIN32
        return (unsigned int)GetCurrentThreadId();
        #else
        return (unsigned int)syscall(SYS_gettid);
        #endif
    }
    
    void write_log(const std::string& level, const std::string& log_line)
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        int ms = (int)(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000);
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm* tm = std::localtime(&now_c);
        std::string line(LStrFmt("%02d/%02d/%04d %02d:%02d:%02d.%03d\t[%08u]\t%s\t").fmt(
            tm->tm_mon + 1, tm->tm_mday, tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec, ms, GetThreadId(), level.c_str()));
        line += log_line;
        {
            std::lock_guard<std::mutex> guard(lock_);
            buffer_.push(line);
        }
    }

private:
    MsgLogger::log_level level_;
    std::ofstream fs_;
    std::queue<std::string> buffer_;
    std::mutex lock_;
};


#endif //__ncMsgLogger