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
   
Time:2021-1

info:

***************************************************************************************************/

#ifndef __mkSingleton
#define __mkSingleton


template<typename T>
class mkSingleton
{
public:
    enum class Mode
    {
        GET,
        DEL,
    };
    
    template<typename... Args>
    static T& Instance(const Mode& mode, Args&&... args)
    {
        static std::shared_ptr<T> instance{ std::forward<Args>(args)... };
        
        //使用单例
        if(mode == Mode::GET) {
            // static静态变量线程安全(c++11)
            return *instance;
        }
        else if(mode == Mode::DEL) {//释放单例
            instance = nullptr;
        }
    }
    
    mkSingleton() = delete;
    virtual ~mkSingleton() = delete;
    mkSingleton(const mkSingleton&) = delete;
    mkSingleton& operator=(const mkSingleton&) = delete;
};


#endif
