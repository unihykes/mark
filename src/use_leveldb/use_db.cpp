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

Time:2020-2

info:

***************************************************************************************************/
#include <markcore.h>
#include <gtest/gtest.h>
#include "leveldb/env.h"
#include "leveldb/db.h"
#include "leveldb/comparator.h"
#include "leveldb/write_batch.h"

class use_db : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	
    virtual void SetUp()
    {
        leveldb::Options options;
        
        //leveldb::Comparator
        //options.comparator = 默认用字典顺序比较
        cout<<options.comparator->Name();
        
        //create_if_missing
        options.create_if_missing = true;
        
        
        //error_if_exists,如果为true,则数据库已存在的话,报错
        options.error_if_exists = false;
        
        //paranoid_checks
        options.paranoid_checks = false;
        
        //env
        options.env = leveldb::Env::Default();
        
        //info_log
        //leveldb::Logger* log = nullptr;
        //leveldb::Status status = _storageEnv->NewLogger(logfile, &log);
        options.info_log = nullptr;//使用默认日志文件
        
        //write_buffer_size 默认4MB
        //options.write_buffer_size = 
        
        //max_open_files:默认1000
        //options.max_open_files = 
        
        //block_cache
        //leveldb::Cache 默认NULL,8M缓存
        //ptions.block_cache = 
        
        
        //block_size 默认4K
        //ptions.block_size =
        
        //block_restart_interval 默认16
        //ptions.block_restart_interval =
        
        //max_file_size 默认2MB
        //ptions.max_file_size =
        
        //compression 默认kSnappyCompression
        //ptions.compression =
        
        //reuse_logs 
        //ptions.reuse_logs =
        
        //filter_policy 默认NULL
        //ptions.filter_policy =
        
        string dbname = "use_leveldb";
        _status = leveldb::DB::Open(options, dbname, &_db);
    }
	
    virtual void TearDown()
    {
        delete _db;
        _db = nullptr;
    }
    
protected:
    leveldb::DB*            _db;
    leveldb::Status         _status;
};

TEST_F(use_db, Put)
{
    leveldb::WriteOptions writeOptions;
    writeOptions.sync = true;
    _status = _db->Put(writeOptions, "use_leveldb/1", "true");
    MK_PRINT("ret=%s", _status.ToString().c_str());
    
    writeOptions.sync = false;
    _status = _db->Put(writeOptions, "use_leveldb/2", "false");
    MK_PRINT("ret=%s", _status.ToString().c_str());
}

TEST_F(use_db, Get)
{
    leveldb::ReadOptions readOptions;
    readOptions.verify_checksums = false;
    readOptions.fill_cache = true;
    readOptions.snapshot = nullptr;
    
    string value;
    _status = _db->Get(readOptions, "use_leveldb/1", &value);
    MK_PRINT("ret=%s", _status.ToString().c_str());
    
    _status = _db->Get(readOptions, "use_leveldb/2", &value);
    MK_PRINT("ret=%s", _status.ToString().c_str());
}

TEST_F(use_db, Delete)
{
    leveldb::WriteOptions writeOptions;
    writeOptions.sync = true;
    
    _status = _db->Delete(writeOptions, "use_leveldb/1");
    MK_PRINT("ret=%s", _status.ToString().c_str());
    
    _status = _db->Delete(writeOptions, "use_leveldb/2");
    MK_PRINT("ret=%s", _status.ToString().c_str());
}

TEST_F(use_db, Write1)
{
    leveldb::WriteOptions writeOptions;
    writeOptions.sync = true;
    
    leveldb::WriteBatch updates;
    updates.Put("use_leveldb/1", "true");
    updates.Put("use_leveldb/2", "false");
    updates.Delete("use_leveldb/1");
    updates.Clear();
    updates.Put("use_leveldb/3", "true");
    updates.Put("use_leveldb/4", "false");
    updates.Delete("use_leveldb/5");
    
    _status = _db->Write(writeOptions, &updates);
    MK_PRINT("ret=%s", _status.ToString().c_str());
}

TEST_F(use_db, Write2)
{
    class WriteBatchHandler : public leveldb::WriteBatch::Handler
    {
        virtual void Put(const leveldb::Slice& key, const leveldb::Slice& value)
        {
            MK_PRINT("%s=%s", key.ToString().c_str(), value.ToString().c_str());
        }
        virtual void Delete(const leveldb::Slice& key)
        {
            MK_PRINT("%s", key.ToString().c_str());
        }
    };
    
    leveldb::WriteOptions writeOptions;
    writeOptions.sync = true;
    
    leveldb::WriteBatch updates;
    updates.Put("use_leveldb/1", "true");
    updates.Put("use_leveldb/2", "false");
    updates.Delete("use_leveldb/1");
    updates.Clear();
    updates.Put("use_leveldb/3", "true");
    updates.Put("use_leveldb/4", "false");
    updates.Delete("use_leveldb/5");
    
    WriteBatchHandler handler;
    _status = updates.Iterate(&handler);
    
    _status = _db->Write(writeOptions, &updates);
    MK_PRINT("ret=%s", _status.ToString().c_str());
}

TEST_F(use_db, NewIterator)
{
    leveldb::ReadOptions readOptions;
    readOptions.verify_checksums = false;
    readOptions.fill_cache = true;
    readOptions.snapshot = nullptr;
    
    std::shared_ptr<leveldb::Iterator> iter(_db->NewIterator(readOptions));
    
    iter->SeekToFirst();
    while(iter->Valid()) {
        _status = iter->status();
        auto key = iter->key();
        auto value = iter->value();
        cout<<key.ToString()<<" = "<< value.ToString()<<endl;
        //MK_PRINT("%s=%s", key.ToString().c_str(), value.ToString().c_str());
        iter->Next();
    }
    
    iter->SeekToLast();
    while(iter->Valid()) {
        _status = iter->status();
        auto key = iter->key();
        auto value = iter->value();
        MK_PRINT("%s=%s", key.ToString().c_str(), value.ToString().c_str());
        iter->Next();
    }
    
    iter->Seek("use_leveldb/3");
    while(iter->Valid()) {
        _status = iter->status();
        auto key = iter->key();
        auto value = iter->value();
        MK_PRINT("%s=%s", key.ToString().c_str(), value.ToString().c_str());
        iter->Next();
    }
    
    //RegisterCleanup
    //todo
}

TEST_F(use_db, readdelete)
{
    leveldb::WriteOptions writeOptions;
    writeOptions.sync = true;
    
    string firstkey = "/readdelete/";
    for(int i = 0; i != 10; ++i) {
        string curKey1 = firstkey + std::to_string(i) + "/";
        for(int j = 0; j != 100; ++j) {
            string curKey = curKey1 + std::to_string(j);
            _status = _db->Put(writeOptions, curKey, "true");
        }
    }
    leveldb::ReadOptions readOptions;
    readOptions.verify_checksums = false;
    readOptions.fill_cache = true;
    readOptions.snapshot = nullptr;
    std::shared_ptr<leveldb::Iterator> iter(_db->NewIterator(readOptions));
    
    int64 count = 0;
    iter->Seek(firstkey);
    while(iter->Valid()) {
        auto key = iter->key();
        if (key.starts_with(firstkey) == false) {
            break;
        }
        
        auto value = iter->value();
        ++count;
        cout<<key.ToString()<<" = "<< value.ToString()<<endl;
        
        //删除
        auto status = _db->Delete(writeOptions, key);
        
        iter->Next();
    }
    MK_PRINT("count = %lld", count);
}





