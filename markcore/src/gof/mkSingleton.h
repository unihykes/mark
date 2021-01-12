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

#include <mutex>

template<typename T>
class mkSingleton
{
public:
    template<typename... Args>
    static void Set(Args&&... args)
    {
        std::shared_ptr<T> newInstance(new T{std::forward<Args>(args)...});
        Instance(Option::INSTANCE_SET, newInstance);
    }
    
    static T& Get()
    {
        return *Instance(Option::INSTANCE_GET, nullptr);
    }
    
    static void Delete()
    {
        Instance(Option::INSTANCE_DEL, nullptr);
    }
    
private:
    enum class Option
    {
        INSTANCE_SET,
        INSTANCE_GET,
        INSTANCE_DEL,
    };
    
    static std::shared_ptr<T> Instance(const Option& option, std::shared_ptr<T> newInstance)
    {
        // static静态变量线程安全(c++11)
        static std::shared_ptr<T> instance(new T());
        static std::mutex instanceMutex;
        if(option == Option::INSTANCE_SET) {
            if(newInstance) {
                std::lock_guard<std::mutex> lock(instanceMutex);
                instance = newInstance;
            }
        }
        //获取单例
        else if(option == Option::INSTANCE_GET) {
            if(!instance) {
                std::lock_guard<std::mutex> lock(instanceMutex);
                throw std::exception("something is wrong");
            }
        }
        //释放单例
        else if(option == Option::INSTANCE_DEL) {
            std::lock_guard<std::mutex> lock(instanceMutex);
            instance.reset();
        }
        
        return instance;
    };
    
    mkSingleton() = delete;
    virtual ~mkSingleton() = delete;
    mkSingleton(const mkSingleton&) = delete;
    mkSingleton& operator=(const mkSingleton&) = delete;
    
private:
    std::shared_ptr<T> _instance;
};


#endif
