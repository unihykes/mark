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
    mkMultiChannel() :mkIOption(false){}
    virtual bool SetAttribute (const string& key, const string& value) override{return false;}
    virtual void Apply(){}
    
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
    virtual bool SetAttribute (const string& key, const string& value) override{return false;}
    virtual void Apply(){}
    
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
    virtual bool SetAttribute (const string& key, const string& value) override{return false;}
    virtual void Apply(){}
    
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
        UnregisterOption<mkMultiChannel>();
        UnregisterOptionAll();
    }
    
private:
    virtual void imp_ApplyOptionAll() override
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
    switchs.SetOptionAttribute("test_key1", "test_value1");
    switchs.SetOptionAttribute("test_key2", "test_value2");
    switchs.SetOptionAttribute("test_key3", "test_value3");
    switchs.SetOptionAttribute("test_key4", "test_value4");
    switchs.ApplyOptionAll();
    
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
        auto pOption = switchs.ModifyOption<mkMultiChannel>();
        pOption->SetAttribute("test_keyxxx", "test_valuexxxx");
        pOption->Apply();
    }
    
    //禁用选项
    {
        switchs.DisableOption<mkMultiChannel>();
    }
}