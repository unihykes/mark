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

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <mkOptionSwitch.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class mkMultiChannel final : public mkIOption
{
public:
    mkMultiChannel() 
        : mkIOption(false)
        , _dataChannelCount(12)
        , _metaChannelCount(33)
    {
        RegisterKeyList({
            "aaa",
            "bbb",
            "ccc"
        });
    }
    
    virtual void SetVaule (const string& key, const string& value) override
    {
    }
    
    virtual void Apply() override
    {
    }
    
    const int GetDataChannelCount() const 
    {
        return _dataChannelCount;
    }
    
    const int GetMetaChannelCount() const 
    {
        return _metaChannelCount;
    }
    
private:
    int     _dataChannelCount;//data通道数量
    int     _metaChannelCount;//meta通道数量
};

class mkOptionA final : public mkIOption
{
public:
    mkOptionA() 
        :mkIOption(false)
    {
        RegisterKeyList({
            "ddd",
            "eee",
            "fff"
        });
    }
    
    virtual void SetVaule (const string& key, const string& value) override
    {
    }
    
    virtual void Apply() override
    {
    }
    
    int GetfuncA() const
    {
         return 100;
    }
    
private:
    int _value;
};

class mkOptionB final : public mkIOption
{
public:
    mkOptionB() 
        :mkIOption(false)
    {
        RegisterKeyList({
            "ggg",
            "hhh",
            "iii"
        });
    }
    
    virtual void SetVaule (const string& key, const string& value) override
    {
    }
    
    virtual void Apply() override
    {
    }
    
    string GetFuncB() const
    {
        return "abc";
    }
private:
    string _value;
};

//备份选项
class mkBackupSwitch  final : public mkIOptionSwitch
{
public:
    mkBackupSwitch()
    {
        RegisterOption<mkMultiChannel>();
        RegisterOption<mkOptionA>();
        RegisterOption<mkOptionB>();
    }

    ~mkBackupSwitch()
    {
    }
    
private:
    virtual void BeforeApplyAttrBatch() override
    {
    }
};


class ut_mkIOptionSwitch : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
};

TEST_F(ut_mkIOptionSwitch, mkBackupSwitch)
{
    mkBackupSwitch switchs;
    
    try {
        //设置选项
        switchs.SetOptionAttrBatch("aaa", "test_value1");
        switchs.SetOptionAttrBatch("ddd", "test_value2");
        switchs.SetOptionAttrBatch("fff", "test_value3");
        switchs.SetOptionAttrBatch("hhh", "test_value4");
        switchs.ApplyOptionAttrBatch();
        MK_PRINT();
        
        //使用选项
        {
            auto pOption = switchs.GetOption<mkMultiChannel>();
            MK_PRINT("cout = %d", pOption->GetDataChannelCount());
            MK_PRINT("cout = %d", pOption->GetMetaChannelCount());
        }
        {
            auto pOption = switchs.GetOption<mkOptionA>();
            int id = pOption->GetfuncA();
            MK_PRINT("id = %d", id);
        }
        {
            auto pOption = switchs.GetOption<mkOptionB>();
            string name = pOption->GetFuncB();
            MK_PRINT("name = %s", name);
        }
        
        //修改选项
        {
            switchs.SetOptionAttr<mkMultiChannel>("aaa", "test_valuexxx");
            switchs.SetOptionAttr<mkMultiChannel>("bbb", "test_valueyyy");
            switchs.SetOptionAttr<mkMultiChannel>("ccc", "test_valuezzz");
            switchs.ApplyOptionAttr<mkMultiChannel>();
        }
        
        //禁用选项
        {
            switchs.DisableOption<mkMultiChannel>();
        }
    }
    catch(string& e) {
        MK_PRINT("e = %s", e.c_str());
    }

}

class mkIStruct : public mkIOptionSwitch, public mkIOption
{
public:
    mkIStruct(const bool& enable)
        : mkIOption(enable)
    {
    }
    
    virtual ~mkIStruct()
    {
    }
    
private:
    virtual void BeforeApplyAttrBatch() = 0;//在 ApplyOptionAttrBatch() 之前调用
    virtual void SetVaule (const string& key, const string& value) = 0;//设置自己的属性
    virtual void Apply() = 0;//让自身属性生效
    
public:
    using mkIOptionSwitch::SetOptionAttrBatch;
    using mkIOptionSwitch::ApplyOptionAttrBatch;
    using mkIOptionSwitch::SetOptionAttr;
    using mkIOptionSwitch::ApplyOptionAttr;
    using mkIOptionSwitch::GetOption;
    using mkIOptionSwitch::DisableOption;
    using mkIOption::IsEnable;
    
protected:
    using mkIOptionSwitch::RegisterOption;
    using mkIOptionSwitch::UnregisterOption;
    using mkIOption::RegisterKeyList;
    using mkIOption::SetEnable;
private:
    
};

class mkStructA : public mkIStruct
{
public:
    mkStructA()
        : mkIStruct(false)
    {
        //注册子项目
        RegisterOption<mkMultiChannel>();
        
        //注册自身 key-list
        RegisterKeyList({
            "AAA",
            "BBB",
        });
    }
    
    virtual void BeforeApplyAttrBatch()
    {
        //do nothing
    }
    
    virtual void SetVaule (const string& key, const string& value)
    {
        if(key == "AAA") {
            aaa = value;
        }
        else if(key == "BBB"){
            bbb = value;
        }
    }
    
    virtual void Apply()
    {
        SetEnable(true);
    }
    
    string      aaa;
    string      bbb;
};

class mkStructB : public mkIStruct
{
public:
    mkStructB()
        : mkIStruct(false)
    {
        //注册子项目
        RegisterOption<mkMultiChannel>();
        RegisterOption<mkStructA>();
        
        //注册自身 key-list
        RegisterKeyList({
            "CCC",
            "DDD",
        });
    }
    
    virtual void BeforeApplyAttrBatch()
    {
        //准备让所有子项目生效
    }
    
    virtual void SetVaule (const string& key, const string& value)
    {
        if(key == "CCC") {
            ccc = value;
        }
        else if(key == "DDD"){
            ddd = value;
        }
        else {
            SetOptionAttrBatch(key, value);
        }
    }
    
    virtual void Apply()
    {
        SetEnable(true);
    }
    
    string     ccc;
    string  ddd;
};


class mkStructC : public mkIStruct
{
public:
    mkStructC()
        : mkIStruct(false)
    {
        //注册子项目
        RegisterOption<mkMultiChannel>();
        
        //注册自身 key-list
        RegisterKeyList({
            "EEE",
            "FFF",
        });
    }
    
    virtual void BeforeApplyAttrBatch()
    {
        //准备让所有子项目生效
    }
    
    virtual void SetVaule (const string& key, const string& value)
    {
        if(key == "EEE") {
            eee = value;
        }
        else if(key == "FFF"){
            fff = value;
        }
    }
    
    virtual void Apply()
    {
        SetEnable(true);
    }
    
    string     eee;
    string  fff;
};


class mkBackupConfig : public mkIStruct
{
public:
    mkBackupConfig()
        : mkIStruct(false)
    {
        //注册子项目
        RegisterOption<mkStructA>();
        RegisterOption<mkStructB>();
        RegisterOption<mkStructC>();
    }
    
    virtual void BeforeApplyAttrBatch()
    {
    }
    
    virtual void SetVaule (const string& key, const string& value)
    {
    }
    
    virtual void Apply()
    {
        SetEnable(true);
    }
    
    string      xxx;
    string      yyy;
};

TEST_F(ut_mkIOptionSwitch, mkBackupConfig)
{
    mkBackupConfig config;
    config.xxx = "test_123";
    config.yyy = "test_456";
    
    try {
        //设置选项
        config.SetOptionAttrBatch("AAA", "test_value1");
        config.SetOptionAttrBatch("BBB", "test_value2");
        config.SetOptionAttrBatch("CCC", "test_value3");
        config.SetOptionAttrBatch("DDD", "test_value4");
        config.SetOptionAttrBatch("EEE", "test_value5");
        config.SetOptionAttrBatch("FFF", "test_value6");
        config.ApplyOptionAttrBatch();
        MK_PRINT();
        
        //使用选项
        {
            MK_PRINT("xxx = %s", config.xxx);
            MK_PRINT("yyy = %s", config.yyy);
        }
        
        {
            auto subConfig = config.GetOption<mkStructA>();
            MK_PRINT("aaa = %s", subConfig->aaa);
            MK_PRINT("bbb = %s", subConfig->bbb);
            {
                auto subsubConfig = subConfig->GetOption<mkMultiChannel>();
                MK_PRINT("GetDataChannelCount = %d", subsubConfig->GetDataChannelCount());
            }
        }
        {
            auto subConfig = config.GetOption<mkStructB>();
            MK_PRINT("ccc = %s", subConfig->ccc);
            MK_PRINT("ddd = %s", subConfig->ddd);
        }
        {
            auto subConfig = config.GetOption<mkStructC>();
            MK_PRINT("eee = %s", subConfig->eee);
            MK_PRINT("fff = %s", subConfig->fff);
        }
        
        //修改选项
        {
            config.SetOptionAttr<mkStructA>("AAA", "test_valuexxx");
            config.SetOptionAttr<mkStructB>("CCC", "test_valueyyy");
            config.SetOptionAttr<mkStructC>("EEE", "test_valuezzz");
        }
        
        //禁用选项
        {
            config.DisableOption<mkStructA>();
            config.DisableOption<mkStructB>();
            config.DisableOption<mkStructC>();
        }
    }
    catch(string& e) {
        MK_PRINT("e = %s", e.c_str());
    }
}

class mkOption : public mkIOption
{
public:
    mkOption():mkIOption(false){}
    mkOption(const bool& ebable):mkIOption(ebable){}
    virtual void SetVaule (const string& key, const string& value) = 0;//设置自己的属性
    virtual void Apply() = 0;//让自身属性生效
};


class mkOptionSwitch : public mkIOptionSwitch
{
private:
    virtual void BeforeApplyAttrBatch() = 0;
};


class mkOption1 : public mkOption
{
private:
    virtual void SetVaule (const string& key, const string& value)
    {
        if(key == "xxx") {
            
        }
        else {
            
        }
    }
    virtual void Apply()
    {
        SetEnable(true);
    }
};


class mkOptionSwitch1 :public mkOptionSwitch
{
public:
    mkOptionSwitch1()
    {
        RegisterOption<mkOption1>();
    }
private:
    virtual void BeforeApplyAttrBatch()
    {
        //nothong todo
    }
};

TEST_F(ut_mkIOptionSwitch, mkOptionSwitch1)
{
    mkOptionSwitch1 config;
    try {
        //设置选项
        config.SetOptionAttrBatch("AAA", "test_value1");
        config.SetOptionAttrBatch("BBB", "test_value2");
        config.ApplyOptionAttrBatch();
        MK_PRINT();
        
        //使用选项
        {
            auto subConfig = config.GetOption<mkOption1>();
        }
        
        //修改选项
        {
            config.SetOptionAttr<mkOption1>("AAA", "test_valuexxx");
        }
        
        //禁用选项
        {
            config.DisableOption<mkOption1>();
        }
    }
    catch(string& e) {
        MK_PRINT("e = %s", e.c_str());
    }
}