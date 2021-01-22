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
    实现一个集成开关,每个开关(switch)有多个选项(option),每个选项有多个属性(key-value)
    可用同时继承mkIOption_base和mkIOptionSwitch_base, 从而实现optionswitch嵌套optionswitch的场景;
    但这种接口看起来不友好,因此暂不支持
***************************************************************************************************/

#ifndef __mkOptionSwitch
#define __mkOptionSwitch

#include <sstream>
#include <typeindex>
#include "print/mkPrint.h"

//前置声明
template<class TypeKey, class TypeValue> class mkIOptionSwitch_base;

//选项接口
template<class TypeKey, class TypeValue>
class mkIOption_base
{
public:
    mkIOption_base(std::initializer_list<TypeKey> keyList = {})
    {
        //注册可用的key-list
        _keySet = keyList;
    }
    
    virtual ~mkIOption_base()
    {
    }
    
private:
    //设置key-value(需要派生类实现)
    virtual bool OnSetValue(const TypeKey& key, const TypeValue& value) = 0;
    
    //应用全部属性,在应用时有特殊逻辑的话,请重载之;
    virtual void OnApply()
    {
    }
    
private:
    //设置某属性,如果key对当前选项无效,则返回false(供 mkIOptionSwitch_base调用)
    friend class mkIOptionSwitch_base<TypeKey, TypeValue>;
    bool SetAttribute (const TypeKey& key, const TypeValue& value)
    {
        //未注册,逐个遍历
        if(_keySet.empty()) {
            return OnSetValue(key, value);
        }
        //已注册,则在注册列表里查找key是否存在,不存在则不用遍历(减少无效调用)
        if(_keySet.count(key) == 0) {
            return false;
        }
        else {
            return OnSetValue(key, value);
        }
    }
    
private:
    std::set<TypeKey>                       _keySet;//该选项支持的key-list
};


//开关接口
template<class TypeKey, class TypeValue>
class mkIOptionSwitch_base
{
public:
    mkIOptionSwitch_base()
    {
    }
    
    virtual ~mkIOptionSwitch_base()
    {
        // Unregister Option
        for(auto& elem : _options) {
            delete elem.second;
            elem.second = nullptr;
        }
        _options.clear();
    }
    
    //批量设置选项的某个属性
    virtual void SetOptions(const TypeKey& key, const TypeValue& value, bool unshared) final
    {
        bool validKey = false;
        for(auto& elem : _options) {
            if(elem.second->SetAttribute(key, value)) {
                validKey = true;
                if(unshared) {
                    break;
                }
            }
        }
        if(!validKey) {
            mkPrint p("markcore"); p(__FILE__, __LINE__, __func__, "key is invalid");
        }
    }
    
    //应用所有选项
    virtual void Applys()
    {
        for(auto& elem : _options) {
            elem.second->OnApply();
        }
    }
    
    //单独重新设置某个选项的某些属性
    template<class T> 
    void SetOption(const TypeKey& key, const TypeValue& value)
    {
        const static std::type_index index(typeid(T));
        
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            if(iter->second->SetAttribute(key, value)) {
                return;
            }
            else {
                //key无效
                mkPrint p("markcore"); p(__FILE__, __LINE__, __func__, "key is invalid");
            }
        }
        else {
            //选项不存在
            mkPrint p("markcore"); p(__FILE__, __LINE__, __func__, "T is invalid");
        }
    }
    
    //应用该选项
    template<class T> 
    void Apply()
    {
        const static std::type_index index(typeid(T));
        
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            iter->second->OnApply();
        }
        else {
            //todo
            mkPrint p("markcore"); p(__FILE__, __LINE__, __func__, "T is invalid");
        }
    }

    //重置某选项
    template<class T> void ClearOption()
    {
        RemoveOption<T>();
        Register<T>();
    }
    
    //获取指定选项[只读]
    template<class T> 
    const T* GetOption() const
    {
        const static std::type_index index(typeid(T));
        
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            const T* result = dynamic_cast<const T*>(iter->second);
            return result;
        }
        else {
            stringstream err; err<<index.name()<<" is invalid.";
            mkPrint p("markcore"); p(__FILE__, __LINE__, __func__, err.str().c_str());
            throw std::logic_error(err.str());//todo
        }
    }
    
    //禁用某选项
    template<class T> void RemoveOption()
    {
        const static std::type_index index(typeid(T));
        
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            delete iter->second;
            iter->second = nullptr;
            _options.erase(iter);
        }
        else {
            //todo
            mkPrint p("markcore"); p(__FILE__, __LINE__, __func__, "T is invalid");
        }
    }
    
protected:
    //注册指定选项,供派生类构造函数中调用
    template<class T> void Register()
    {
        const static std::type_index index(typeid(T));
        
        _options.insert(make_pair(index, new T) );
    }
    
protected:
    std::map<std::type_index, mkIOption_base<TypeKey, TypeValue>*> _options;
};


//默认std::string作为key-value
using mkIOption = mkIOption_base<string,string>;
using mkIOptionSwitch = mkIOptionSwitch_base<string,string>;


class MK_DLL_EXPORT mkOptionSwitch  : public mkIOptionSwitch
{
public:
    mkOptionSwitch();
    virtual ~mkOptionSwitch();

    //解析执行参数,返回gtest参数
    pair<int, char**> InitEnv(int argc, char** argv);
    
    //加载配置文件中的参数
    void LoadByConfig(const string& configFileName);
    
    //加载命令行参数
    virtual void Applys();
    
    template<class T> 
    void LoadOption(const string& configFileName)
    {
    }
    
    template<class T> 
    void ApplyOption()
    {
        for(const auto& elem : _mapArgs) {
            const string& key = elem.first;
            for(const auto& value : elem.second) {
                this->SetOption<T>(key, value);
            }
        }
        this->Apply<T>();//应用之
    }
    
private:
    int                             _gtest_argc;
    char**                          _gtest_argv;
    vector<std::string>             _vGtestArgs;
    map<string, vector<string>>     _mapArgs;
};


#endif //__mkOptionSwitch