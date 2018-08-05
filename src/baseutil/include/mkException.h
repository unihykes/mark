/***************************************************************************************************
Author:liu.hao

Time:2018-8

info:

***************************************************************************************************/

#ifndef __mkException
#define __mkException

class mkException
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

#endif //__mkException
