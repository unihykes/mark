/***************************************************************************************************
Author:liu.hao

Time:2018-8

info:

***************************************************************************************************/

#ifndef __mkString
#define __mkString


class mkString
{
public:
    operator std::basic_string<auto_char>()
    {
        return _imp;
    }
    
    mkString()
    {
    }
    
    
    mkString(auto_char ch)
    {
        
    }
    
    mkString(auto_char* ptr)
    {
        
    }
    
private:
    std::basic_string<auto_char>    _imp;
};



#endif //__mkString
