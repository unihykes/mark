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

Time:2018-2

info:
    限制某类型对象同时达到某状态时的总数量
***************************************************************************************************/
#ifndef __mkScopeLimiter
#define __mkScopeLimiter

#include <gof/mkSingleton.h>

template<typename T>
class mkScopeLimiter
{
public:
    template<typename AbortFunc>
    mkScopeLimiter(AbortFunc&& needAbort)
        : _needUnblock(false)
    {
        while(true) {
            if(needAbort()) {
                _needUnblock = true;
                break;
            }
            
            if(mkSingleton<mkScopeCount>::Get().Increase()) {
                break;
            }
            else {
                this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }
    
    ~mkScopeLimiter()
    {
        if(!_needUnblock) {
            mkSingleton<mkScopeCount>::Get().Decrease();
        }
    }
    
    static void SetMax(const int max)
    {
        mkSingleton<mkScopeCount>::Create(max);
    }
    
private:
    class mkScopeCount
    {
    public:
        mkScopeCount()
            : _max(0)
            , _current(0)
        {
        }
        
        mkScopeCount(const int max)
            : _max(max)
            , _current(0)
        {
        }
        
        bool Increase()
        {
            std::lock_guard<std::mutex> lock(_currentLock);
            if(_current >= _max) {
                return false;
            }
            else {
                ++_current;
                return true;
            }
        }
        
        void Decrease()
        {
            std::lock_guard<std::mutex> lock(_currentLock);
            --_current;
        }
        
        int GetCurrent()
        {
            std::lock_guard<std::mutex> lock(_currentLock);
            return _current;
        }
        
    private:
        int             _max; 
        int             _current;
        std::mutex      _currentLock;
    };
private:
    bool                    _needUnblock;//解除阻塞
};
#endif