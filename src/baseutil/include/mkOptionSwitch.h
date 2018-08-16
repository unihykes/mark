/***************************************************************************************************
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
template<class TypeKey, class TypeValue> class mkIOption_base_imp;


//选项接口
template<class TypeKey, class TypeValue>
class mkIOption_base
{
public:
    mkIOption_base(const bool& enable);
    virtual ~mkIOption_base();
    
    //该选项是否生效(应用层调用)
    virtual const bool IsEnable() const final;
    
protected:
    //注册可用的key-list(派生类构造函数中调用)
    virtual void RegisterKeyList(std::initializer_list<TypeKey> keyList) final;
    
    //启用/禁用该选项(派生类的Apply函数中调用)
    virtual void SetEnable(const bool& val) final;
    
private:
    //设置key-value(需要派生类实现)
    virtual void SetVaule(const TypeKey& key, const TypeValue& value) = 0;
    
    //应用全部属性((需要派生类实现))
    virtual void Apply() = 0;
    
private:
    friend class mkIOptionSwitch_base<TypeKey, TypeValue>;
    friend class mkIOption_base_imp<TypeKey, TypeValue>;
    mkIOption_base_imp<TypeKey, TypeValue>* _imp;
};


//开关接口
template<class TypeKey, class TypeValue>
class mkIOptionSwitch_base
{
public:
    virtual ~mkIOptionSwitch_base(){UnregisterOptionAll();}
    
    //批量设置某个选项的某个属性,这里用了契约,假定所有选项的任一属性都有唯一的key标志
    //全部属性设置完成后,需要与 ApplyOptionAll() 配对使用,使所有选项的设置生效
    virtual void SetOptionAttrBatch (const TypeKey& attributeKey, const TypeValue& value) final;
    virtual void ApplyOptionAttrBatch() final;
    
    //单独重新设置某个选项的某些属性
    //全部属性修改完成后,需要与ApplyOption()配对使用,使修改生效
    template<class T> void SetOptionAttr(const TypeKey& attributeKey, const TypeValue& value);
    template<class T> void ApplyOptionAttr();
    
    //获取指定选项[只读]
    template<class T> const T* GetOption() const;
    
    //禁用某选项
    template<class T> void DisableOption() const;
    
protected:
    //注册:指定选项
    //解注册:指定选项
    template<class T> void RegisterOption();
    template<class T> void UnregisterOption();

private:
    //派生类实现,在函数 ApplyOptionAttrBatch() 内部调用;
    //处理一些额外逻辑:
    //1.禁用一些相互冲突的开关,例如:A开关和B开关不能同时打开
    //2.检测到某些开关未打开则抛异常,例如C开关在任何情况下都必须打开,否则逻辑错误
    //3.取消注册某些开关, 例如D开关在流程1中需要,但是流程2中不需要,则流程2时可以取消掉该选项;
    //4.等等
    virtual void BeforeApplyAttrBatch() = 0;
    
    //解注册:所有选项
    virtual void UnregisterOptionAll() final;
protected:
    std::map<std::type_index, mkIOption_base<TypeKey, TypeValue>*> _options;
};

//默认std::string作为key-value
using mkIOption = mkIOption_base<string,string>;
using mkIOptionSwitch = mkIOptionSwitch_base<string,string>;













//
//具体实现: mkIOption_base
//
template<class TypeKey, class TypeValue>
class mkIOption_base_imp
{
public:
    mkIOption_base_imp(mkIOption_base<TypeKey, TypeValue>* pOption, const bool& enable)
        : _pOption(pOption)
        , _enable(enable)
    {
    }
    
    //设置某属性,如果key对当前选项无效,则返回false
    bool SetAttribute (const TypeKey& key, const TypeValue& value)
    {
        //未注册,逐个遍历
        if(_keySet.empty()) {
            _pOption->SetVaule(key, value);
            return false;
        }
        //已注册,则在注册列表里查找key是否存在,不存在则不用遍历(减少无效调用)
        else {
            if(_keySet.count(key) == 0) {
                return false;
            }
            else {
                _pOption->SetVaule(key, value);
                return true;
            }
        }
    }
    
    //启用或禁用该选项
    void SetEnable(const bool& val)
    {
        _enable = val;
    }
    
    bool IsEnable()
    {
        return _enable;
    }
    
    void RegisterKeyList(std::initializer_list<TypeKey> keyList)
    {
        _keySet = keyList;
    }
    
private:
    mkIOption_base<TypeKey, TypeValue>*     _pOption;
    std::set<TypeKey>                       _keySet;//该选项支持的key-list
    bool                                    _enable;//该选项是否生效
};

template<class TypeKey, class TypeValue>
mkIOption_base<TypeKey, TypeValue>::mkIOption_base(const bool& enable) 
    : _imp(nullptr)
{
    _imp = new mkIOption_base_imp<TypeKey, TypeValue>(this, enable);
}

template<class TypeKey, class TypeValue>
mkIOption_base<TypeKey, TypeValue>::~mkIOption_base() 
{
    if(_imp) {
        delete _imp;
        _imp = nullptr;
    }
}

template<class TypeKey, class TypeValue>
const bool mkIOption_base<TypeKey, TypeValue>::IsEnable() const
{
    return _imp->IsEnable();
}

template<class TypeKey, class TypeValue>
void mkIOption_base<TypeKey, TypeValue>::SetEnable(const bool& val)
{
    _imp->SetEnable(val);
}

template<class TypeKey, class TypeValue>
void mkIOption_base<TypeKey, TypeValue>::RegisterKeyList(std::initializer_list<TypeKey> keyList)
{
    _imp->RegisterKeyList(keyList);
}

//
//具体实现: mkIOptionSwitch_base
//
template<class TypeKey, class TypeValue>
void mkIOptionSwitch_base<TypeKey, TypeValue>::SetOptionAttrBatch (const TypeKey& attributeKey, const TypeValue& value)
{
    bool validKey = false;
    for(auto& elem : _options) {
        if(elem.second->_imp->SetAttribute(attributeKey, value)) {
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

template<class TypeKey, class TypeValue>
void mkIOptionSwitch_base<TypeKey, TypeValue>::ApplyOptionAttrBatch()
{
    BeforeApplyAttrBatch();
    
    for(auto& elem : _options) {
        elem.second->Apply();
    }
}

template<class TypeKey, class TypeValue>
template<class T> 
void mkIOptionSwitch_base<TypeKey, TypeValue>::SetOptionAttr(const TypeKey& attributeKey, const TypeValue& value)
{
    const static std::type_index index(typeid(T));
    
    auto iter = _options.find(index);
    if(iter != _options.end()) {
        if(iter->second->_imp->SetAttribute(attributeKey, value)) {
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

template<class TypeKey, class TypeValue>
template<class T> 
void mkIOptionSwitch_base<TypeKey, TypeValue>::ApplyOptionAttr()
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


template<class TypeKey, class TypeValue>
template<class T> 
const T* mkIOptionSwitch_base<TypeKey, TypeValue>::GetOption() const
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

template<class TypeKey, class TypeValue>
template<class T>
void mkIOptionSwitch_base<TypeKey, TypeValue>::DisableOption() const
{
    const static std::type_index index(typeid(T));
    auto iter = _options.find(index);
    if(iter != _options.end()) {
        iter->second->_imp->SetEnable(false);
        iter->second->Apply();
    }
    else {
        //todo
        MK_PRINT(_T("T is invalid."));
    }
}

template<class TypeKey, class TypeValue>
template<class T> 
void mkIOptionSwitch_base<TypeKey, TypeValue>::RegisterOption()
{
    const static std::type_index index(typeid(T));
    
    _options.insert(make_pair(index, new T) );
}

template<class TypeKey, class TypeValue>
template<class T> 
void mkIOptionSwitch_base<TypeKey, TypeValue>::UnregisterOption()
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

template<class TypeKey, class TypeValue>
void mkIOptionSwitch_base<TypeKey, TypeValue>::UnregisterOptionAll()
{
    for(auto& elem : _options) {
        delete elem.second;
        elem.second = nullptr;
    }
    _options.clear();
}

#endif //__mkOptionSwitch