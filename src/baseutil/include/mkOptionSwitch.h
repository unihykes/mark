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

#include <typeindex>

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
    virtual void SetVaule(const TypeKey& key, const TypeValue& value) = 0;
    
    //应用全部属性((需要派生类实现))
    virtual void Apply() = 0;
    
    //设置某属性,如果key对当前选项无效,则返回false(供 mkIOptionSwitch_base调用)
    bool SetAttribute (const TypeKey& key, const TypeValue& value)
    {
        //未注册,逐个遍历
        if(_keySet.empty()) {
            SetVaule(key, value);
            return false;
        }
        //已注册,则在注册列表里查找key是否存在,不存在则不用遍历(减少无效调用)
        else {
            if(_keySet.count(key) == 0) {
                return false;
            }
            else {
                SetVaule(key, value);
                return true;
            }
        }
    }
private:
    friend class mkIOptionSwitch_base<TypeKey, TypeValue>;
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
        UnregisterOptionAll();
    }
    
    //批量设置某个选项的某个属性,这里用了契约,假定所有选项的任一属性都有唯一的key标志
    //全部属性设置完成后,需要与 ApplyOptionAll() 配对使用,使所有选项的设置生效
    virtual void SetOptionAttrBatch (const TypeKey& attributeKey, const TypeValue& value) final
    {
        bool validKey = false;
        for(auto& elem : _options) {
            if(elem.second->SetAttribute(attributeKey, value)) {
                validKey = true;
                break;
            }
        }
        
        if(!validKey) {
            //todo
            //无效的key
            //MK_PRINT("key is invalid.");
        }
    }
    
    virtual void ApplyOptionAttrBatch() final
    {
        BeforeApplyAttrBatch();
        
        for(auto& elem : _options) {
            elem.second->Apply();
        }
    }
    
    //单独重新设置某个选项的某些属性
    //全部属性修改完成后,需要与ApplyOption()配对使用,使修改生效
    template<class T> void SetOptionAttr(const TypeKey& attributeKey, const TypeValue& value)
    {
        const static std::type_index index(typeid(T));
        
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            if(iter->second->SetAttribute(attributeKey, value)) {
                return;
            }
            else {
                //key无效
                //todo
                //MK_PRINT("key is invalid.");
            }
        }
        else {
            //todo
            //选项不存在
            MK_PRINT(_T("T is invalid."));
        }
        
    }
    
    
    template<class T> void ApplyOptionAttr()
    {
        const static std::type_index index(typeid(T));
        
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            iter->second->Apply();
        }
        else {
            //todo
            MK_PRINT(_T("T is invalid."));
        }
    }

    
    //获取指定选项[只读]
    template<class T> const T* GetOption() const
    {
        const static std::type_index index(typeid(T));
        
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            const T* result = dynamic_cast<const T*>(iter->second);
            return result;
        }
        else {
            //todo 
            MK_PRINT(_T("T is invalid."));
            throw string("T is invalid.");
        }
    }

    //禁用某选项
    template<class T> void DisableOption() const
    {
        const static std::type_index index(typeid(T));
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            iter->second->Apply();
        }
        else {
            //todo
            MK_PRINT(_T("T is invalid."));
        }
    }

protected:
    //注册:指定选项
    //解注册:指定选项
    template<class T> void RegisterOption()
    {
        const static std::type_index index(typeid(T));
        
        _options.insert(make_pair(index, new T) );
    }

    template<class T> void UnregisterOption()
    {
        const static std::type_index index(typeid(T));
        
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            delete iter->second;
            iter->second = nullptr;
        }
        else {
            //todo
            MK_PRINT(_T("T is invalid."));
        }
        _options.erase(iter);
    }

private:
    //派生类实现,在函数 ApplyOptionAttrBatch() 内部调用;
    //处理一些额外逻辑:
    //1.禁用一些相互冲突的开关,例如:A开关和B开关不能同时打开
    //2.检测到某些开关未打开则抛异常,例如C开关在任何情况下都必须打开,否则逻辑错误
    //3.取消注册某些开关, 例如D开关在流程1中需要,但是流程2中不需要,则流程2时可以取消掉该选项;
    //4.等等
    virtual void BeforeApplyAttrBatch() = 0;
    
    //解注册:所有选项
    virtual void UnregisterOptionAll() final
    {
        for(auto& elem : _options) {
            delete elem.second;
            elem.second = nullptr;
        }
        _options.clear();
    }

protected:
    std::map<std::type_index, mkIOption_base<TypeKey, TypeValue>*> _options;
};



//默认std::string作为key-value
using mkIOption = mkIOption_base<string,string>;
using mkIOptionSwitch = mkIOptionSwitch_base<string,string>;


#endif //__mkOptionSwitch