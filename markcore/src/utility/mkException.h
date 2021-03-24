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
   
Time:2018-8

info:

***************************************************************************************************/

#ifndef __mkException
#define __mkException

#include "string/mkFormat.h"

class MK_DLL_EXPORT mkException : public std::exception
{
public:
	mkException ()noexcept
        : _line (0)
        , _id (0)
        , _cause (nullptr)
        , _what(nullptr)
    {
    }
    
	mkException(const string& msg, const char* file, int line, int id) noexcept
        : _msg (msg)
        , _file (file)
        , _line (line)
        , _id (id)
        , _cause (nullptr)
        , _what(nullptr)
    {
    }


    mkException(const string& msg, const char* file, int line, int id, const mkException& exp) noexcept
        : _msg (msg)
        , _file (file)
        , _line (line)
        , _id (id)
        , _cause (nullptr)
        , _what(nullptr)
    {
        _cause = new mkException(exp);
    }


	mkException(const mkException& exp) noexcept
        : _msg (exp._msg)
        , _file (exp._file)
        , _line (exp._line)
        , _id (exp._id)
        , _cause (nullptr)
        , _what(nullptr)
    {
        if(exp._cause) {
            _cause = new mkException(*exp._cause);
        }
    }

	mkException& operator= (const mkException& exp) noexcept
    {
        _msg = exp._msg;
        _file = exp._file;
        _line = exp._line;
        _id = exp._id;
        if(exp._cause) {
            _cause = new mkException(*exp._cause);
        }
        _what = nullptr;
        
        return *this;
    }
    
    virtual ~mkException ()
    {
        if(_what) {
            delete [] _what;
            _what = nullptr;
        }
        
        if (_cause != 0) {
            delete _cause;
        }
    }
    
    
    virtual const char* what() const noexcept
    {
        if(_what)  {
            return _what;
        }
        
        const char* fmt = nullptr;
        if(_cause) {
            fmt = "%s(%s:%d id = %d, cause = %s)";
        }
        else {
            fmt = "%s(%s:%d id = %d%s)";
        }
        
        //计算缓冲区size
        int size = std::snprintf(nullptr, 0, fmt, _msg.c_str(), _file.c_str(), _line, _id, (_cause ? _cause->what() : ""));
        _what = new char[size + 1];//为空终止符 +1
        std::snprintf(_what, size+1, fmt, _msg.c_str(), _file.c_str(), _line, _id, (_cause ? _cause->what() : ""));
        return _what;
    }

protected:
	string _msg;
	string _file;
    int _line;
	int _id;
	const mkException* _cause;
    mutable char* _what;
}; // End mkException


class mkErrorCode
{
    static int GetLastError (void)
    {
    	#ifdef __WINDOWS__
    		return ::GetLastError();
    	#else
    		return errno;
    	#endif
    }

    static void SetLastError (int err)
    {
    	#ifdef __WINDOWS__
    		::SetLastError(err);
    	#else
    		errno = err;
    	#endif
    }
};
    
#endif //__mkException
