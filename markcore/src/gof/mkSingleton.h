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
    //创建单例
    template<typename... Args>
    static void Create(Args&&... args)
    {
        Instance(Option::INSTANCE_ADD, std::make_shared<T>(std::forward<Args>(args)...));
    }
    //重设单例
    template<typename... Args>
    static void Reset(Args&&... args)
    {
        Instance(Option::INSTANCE_DEL, nullptr);
        Instance(Option::INSTANCE_SET, std::make_shared<T>(std::forward<Args>(args)...));
    }
    //获取单例,在调用该接口时如果其他线程正在调用Create/Reset/Delete,则线程不安全
    static T& Get()
    {
        return *Instance(Option::INSTANCE_GET, nullptr);
    }
    
    //获取单例,在调用该接口时如果其他线程正在调用Create/Reset/Delete,线程安全,但上层可能会接管单例的生命周期
    static std::shared_ptr<T> SafeGet()
    {
        return Instance(Option::INSTANCE_SAFE_GET, nullptr);
    }
    
    //删除单例
    static void Delete()
    {
        Instance(Option::INSTANCE_DEL, nullptr);
    }
    
private:
    enum class Option
    {
        INSTANCE_ADD,//增
        INSTANCE_GET,//查
        INSTANCE_SAFE_GET,//查
        INSTANCE_SET,//改
        INSTANCE_DEL,//删
    };
    
    static std::shared_ptr<T> Instance(const Option& option, std::shared_ptr<T> newInstance)
    {
        static std::shared_ptr<T> instance = {newInstance ? newInstance : std::make_shared<T>()};
        static std::mutex instanceMutex;
        
        switch (option) {
            case Option::INSTANCE_ADD:
                if(!newInstance) {
                    throw std::exception("something is wrong");
                }
                break;
                
            case Option::INSTANCE_SET:
                if(!newInstance) {
                    throw std::exception("something is wrong");
                }
                else {
                    std::lock_guard<std::mutex> lock(instanceMutex);
                    instance = newInstance;
                }
                break;
                
            case Option::INSTANCE_GET:
                if(!instance) {
                    throw std::exception("something is wrong");
                }
                break;
                
            case Option::INSTANCE_SAFE_GET:
                {
                    std::lock_guard<std::mutex> lock(instanceMutex);
                    std::shared_ptr<T> ret = instance;
                    if(!ret) {
                        throw std::exception("something is wrong");
                    }
                    return ret;
                }
                break;
                
            case Option::INSTANCE_DEL:
                if(instance) {
                    std::lock_guard<std::mutex> lock(instanceMutex);
                    instance.reset();
                }
                break;
                
            default:
                throw std::exception("something is wrong");
                break;
        }
        
        return instance;
    };
    
    mkSingleton() = delete;
    virtual ~mkSingleton() = delete;
    mkSingleton(const mkSingleton&) = delete;
    mkSingleton& operator=(const mkSingleton&) = delete;
};


#endif
