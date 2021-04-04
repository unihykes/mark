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

class use_env : public testing::Test
{
protected:
	static void SetUpTestCase()
    {
    }
	static void TearDownTestCase()
    {
    }
	
    virtual void SetUp()
    {
        _env = leveldb::Env::Default();
    }
	
    virtual void TearDown()
    {
        _env = nullptr;
    }
	
    void Logv(leveldb::Logger* log, const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        
        log->Logv(fmt, args);
        
        va_end (args);
    }
protected:
    leveldb::Env*            _env;
};

TEST_F(use_env, common)
{
	
    std::string fname = "use_leveldb.config";
    std::string dir = "use_leveldb_dir";
    bool ret = false;
    leveldb::Status status;
    
    //FileExists
    {
        ret = _env->FileExists(fname);
        MK_PRINT("ret = %d", int(ret));
    }
    
    //GetChildren
    {
        std::vector<std::string> result;
        status = _env->GetChildren(dir, &result);
        
        for(auto& elem : result) {
            MK_PRINT("ret = %s", elem.c_str());
        }
    }
    
    //DeleteFile
    {
        string todo = "DeleteFile.txt";
        status = _env->DeleteFile(todo);
        MK_PRINT("ret = %d", int(ret));
    }
    
    //CreateDir && DeleteDir
    {
        string todo = "CreateDir.txt";
        status = _env->CreateDir(todo);
        MK_PRINT("ret = %d", int(ret));
        
        status = _env->DeleteDir(todo);
        MK_PRINT("ret = %d", int(ret));
    }
    
    //GetFileSize
    {
        uint64_t file_size = 0;
        status = _env->GetFileSize(fname, &file_size);
        MK_PRINT("file_size = %lld", file_size);
    }
    
    //RenameFile
    {
        string src = fname;
        string target = "rename.txt";
        
        status = _env->RenameFile(fname, target);
        MK_PRINT("ret = %s", status.ToString().c_str());
        
        status = _env->RenameFile(target, src);
        MK_PRINT("ret = %s", status.ToString().c_str());
    }
    
    //LockFile&&UnlockFile
    {
        leveldb::FileLock* lock = nullptr;
        
        status = _env->LockFile(fname, &lock);
        MK_PRINT("ret = %s", status.ToString().c_str());
        
        status = _env->UnlockFile(lock);
        MK_PRINT("ret = %s", status.ToString().c_str());
    }
    
    //Schedule
    {
        //todo
    }
    
    //StartThread
    {
        //todo
    }
    
    //GetTestDirectory
    {
        std::string path;
        status = _env->GetTestDirectory(&path);
        //C:\Users\ADMINI~1\AppData\Local\Temp\ 
        MK_PRINT("ret = %s", path.c_str());
    }
    
    //NowMicros
    {
        uint64_t micros = 0;
        micros = _env->NowMicros();
        MK_PRINT("micros = %lld", micros);
    }
    
    //SleepForMicroseconds
    {
        //1微秒=百万分之一秒
        int micros = 1000*1000;
        _env->SleepForMicroseconds(micros);
    }
}

//日志
TEST_F(use_env, NewLogger)
{
    //NewLogger
    {
        string logfile("use_leveldb.log");
        leveldb::Logger* log = nullptr;
        
        leveldb::Status status = _env->NewLogger(logfile, &log);
        MK_PRINT("ret = %s", status.ToString().c_str());
        
        //use_env::Logv
        Logv(log, "just for test: %s, %d...", "xxx", 123);
        
        
        //全局函数::leveldb::Log
        leveldb::Log(log, "just for test22222222: %s, %d...", "fafaefe", 467);
        
    }
}

//顺序读, 单线程使用
TEST_F(use_env, NewSequentialFile)
{
    std::string fname = "use_leveldb.config";
    leveldb::Status status;
    leveldb::SequentialFile* file;
    status = _env->NewSequentialFile(fname, &file);
    MK_PRINT("ret = %s", status.ToString().c_str());
    if(!status.ok()) {
        return;
    }
    
    
    //Read
    for(;;) {
        //一次最多读取n个字节
        const size_t n = 2;
		char scratch[n+1]; memset(scratch,0,n+1); scratch[n] = '\0';
        leveldb::Slice result;
        status = file->Read(n, &result, scratch);
        cout <<"ret = " <<status.ToString()<<endl;
        MK_PRINT("ret = %s", result.ToString().c_str());
        if(result.empty()) {
            break;
        }
        cout<<scratch<<endl;
        
        //跳过x个字节
        uint64_t x = 1;
        status = file->Skip(x);
        MK_PRINT("ret = %s", status.ToString().c_str());
    }
}

//随机读, 可多线程使用
TEST_F(use_env, NewRandomAccessFile)
{
    std::string fname = "use_leveldb.config";
    leveldb::Status status;
    leveldb::RandomAccessFile* file;
    status = _env->NewRandomAccessFile(fname, &file);
    MK_PRINT("ret = %s", status.ToString().c_str());
    if(!status.ok()) {
        return;
    }
    
    //Read
    uint64_t offset = 0;
    for(;;) {
		constexpr size_t n = 2;
		char scratch[n+1]; memset(scratch,0,n+1); scratch[n] = '\0';
        leveldb::Slice result;
        status = file->Read(offset, n, &result, scratch);
		cout <<"ret = " <<status.ToString()<<endl;
        MK_PRINT("ret = %s", result.ToString().c_str());
        if(result.empty()) {
            break;
        }
        
        offset += n;
    }
}

//顺序写,单线程使用,如果文件已存在,会清空文件
TEST_F(use_env, NewWritableFile)
{
    std::string fname = "use_leveldb.config";
    leveldb::Status status;
    leveldb::WritableFile* file;
    status = _env->NewWritableFile(fname, &file);
    MK_PRINT("ret = %s", status.ToString().c_str());
    if(!status.ok()) {
        return;
    }
    
    for(int i = 0; i != 5; ++i) {
        for(int j = 0; j != 10; ++j) {
            file->Append("juest for a test !!!!\n");//追加写
        }
        file->Flush();//调用WriteFile写入磁盘
    }
    file->Sync();//Sync内部包含Flush操作,Flush之后.调用FlushFileBuffers函数, 保证在文件关闭之前所有的调用WriteFile写入磁盘的数据真正被写入磁盘
    file->Close();//Close内部包含Flush操作, Flush之后关闭文件
}


//顺序写,单线程使用,如果文件已存在,会追加写
TEST_F(use_env, NewAppendableFile)
{
    std::string fname = "use_leveldb.config";
    leveldb::Status status;
    leveldb::WritableFile* file;
    status = _env->NewAppendableFile(fname, &file);
    MK_PRINT("ret = %s", status.ToString().c_str());
    if(!status.ok()) {
        return;
    }
    
    for(int i = 0; i != 5; ++i) {
        for(int j = 0; j != 10; ++j) {
            file->Append("juest for a test !!!!\n");//追加写
        }
        file->Flush();//调用WriteFile写入磁盘
    }
    file->Sync();//Sync内部包含Flush操作,Flush之后.调用FlushFileBuffers函数, 保证在文件关闭之前所有的调用WriteFile写入磁盘的数据真正被写入磁盘
    file->Close();//Close内部包含Flush操作, Flush之后关闭文件
}

//全局函数
TEST_F(use_env, ReadWrite)
{
    leveldb::Status status;
    std::string fname = "use_leveldb.config";
    
    //write,如果原文件有内容,清空之
    leveldb::Slice data("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    status = leveldb::WriteStringToFile(_env, data, fname);
    
    //read
    string buf;
    status = leveldb::ReadFileToString(_env, fname, &buf);
}










