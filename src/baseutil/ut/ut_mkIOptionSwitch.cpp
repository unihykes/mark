/***************************************************************************************************
Author:liu.hao

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
        :mkIOption(false)
    {
        RegisterKeyList("aaa");
        RegisterKeyList("bbb");
        RegisterKeyList("ccc");
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
    mkOptionA() :mkIOption(false){}
    
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
    int value;
};

class mkOptionB final : public mkIOption
{
public:
    mkOptionB() :mkIOption(false){}
    
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
    int value;
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
        UnregisterOptionAll();
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

TEST_F(ut_mkIOptionSwitch, lambda)
{
    mkBackupSwitch switchs;
    
    //设置选项
    switchs.SetOptionAttrBatch("test_key1", "test_value1");
    switchs.SetOptionAttrBatch("test_key2", "test_value2");
    switchs.SetOptionAttrBatch("test_key3", "test_value3");
    switchs.SetOptionAttrBatch("test_key4", "test_value4");
    switchs.ApplyOptionAttrBatch();
    
    //使用选项
    {
        auto pOption = switchs.GetOption<mkMultiChannel>();
        pOption->GetDataChannelCount();
        pOption->GetMetaChannelCount();
    }
    {
        auto pOption = switchs.GetOption<mkOptionA>();
        int id = pOption->GetfuncA();
    }
    {
        auto pOption = switchs.GetOption<mkOptionB>();
        string name = pOption->GetFuncB();
    }
    
    
    //修改选项
    {
        switchs.SetOptionAttr<mkMultiChannel>("test_keyxxx", "test_valuexxx");
        switchs.SetOptionAttr<mkMultiChannel>("test_keyyyy", "test_valueyyy");
        switchs.SetOptionAttr<mkMultiChannel>("test_keyzzz", "test_valuezzz");
        switchs.ApplyOptionAttr<mkMultiChannel>();
    }
    
    //禁用选项
    {
        switchs.DisableOption<mkMultiChannel>();
    }
}