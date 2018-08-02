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