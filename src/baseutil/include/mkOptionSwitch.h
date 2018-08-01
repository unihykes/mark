/***************************************************************************************************
Author:liu.hao(33852613@163.com)

Time:2018-8

info:

***************************************************************************************************/

#ifndef __mkOptionSwitch
#define __mkOptionSwitch

#include <typeindex>


//前置声明
template<class T1, class T2> class mkIOptionSwitch_base;


//选项接口
template<class TypeKey, class TypeValue>
class mkIOption_base
{
public:
    mkIOption_base(const bool& enable) 
        : _enable(enable)
    {
    }
    
    virtual ~mkIOption_base() 
    {
    }
    
    //设置某属性
    virtual bool SetAttribute (const TypeKey& key, const TypeValue& value) = 0;
    
    //该选项是否可用
    virtual const bool IsEnable() const final 
    {
        return _enable;
    }
    
private:
    friend class mkIOptionSwitch_base<TypeKey,TypeValue>;
    
     //应用全部属性
     virtual void Apply() = 0;
    
    //启用或禁用该选项
    virtual void SetEnable(const bool& val) final 
    {
        _enable = val;
    }
    
private:
    bool    _enable;//该选项是否生效
};

//集成开关接口
template<class TypeKey, class TypeValue>
class mkIOptionSwitch_base
{
public:
    virtual ~mkIOptionSwitch_base()
    {
    }
    
    //设置某个选项的某个属性,这里用了契约,假定所有选项的任一属性都有唯一的key标志
    //全部属性设置完成后,需要与 ApplyOptionAll() 配对使用,使所有选项的设置生效
    void SetOptionAttribute (const TypeKey& attributeKey, const TypeValue& value)
    {
        for(auto& elem : _options) {
            if(elem.second->SetAttribute(attributeKey, value)) {
                break;
            }
        }
    }
    
    virtual void ApplyOptionAll() final
    {
        imp_ApplyOptionAll();
        
        for(auto& elem : _options) {
            elem.second->SetEnable(true);
            elem.second->Apply();
        }
    }
    
    
    //获取指定选项[可修改]
    template<class T> 
    T* ModifyOption() const
    {
        const static std::type_index index(typeid(T));
        
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            T* result = dynamic_cast<T*>(iter->second);
            return result;
        }
        else {
            //todo
            throw string("todo");
        }
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
            //todo
             throw string("todo");
        }
    }
    
    //禁用某选项
    template<class T>
    void DisableOption() const
    {
        const static std::type_index index(typeid(T));
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            iter->second->SetEnable(false);
            iter->second->Apply();
        }
        else {
            //todo
            throw string("todo");
        }
    }
    
protected:
    //注册:指定选项
    template<class T> 
    void RegisterOption()
    {
        const static std::type_index index(typeid(T));
        
        _options.insert(make_pair(index, new T) );
    }
    
    //解注册:指定选项
    template<class T> 
    void UnregisterOption()
    {
        const static std::type_index index(typeid(T));
        
        auto iter = _options.find(index);
        if(iter != _options.end()) {
            delete iter->second;
            iter->second = nullptr;
        }
        else {
            //todo
            throw string("todo");
        }
        _options.erase(iter);
    }
    
    //解注册:所有选项
    virtual void UnregisterOptionAll() final
    {
        for(auto& elem : _options) {
            delete elem.second;
            elem.second = nullptr;
        }
        _options.clear();
    }
    
private:
    //派生类实现,处理一些额外逻辑
    virtual void imp_ApplyOptionAll() = 0;
    
protected:
    std::map<std::type_index, mkIOption_base<TypeKey, TypeValue>*>      _options;
};

using mkIOption = mkIOption_base<string,string>;
using mkIOptionSwitch = mkIOptionSwitch_base<string,string>;

#endif //__mkOptionSwitch