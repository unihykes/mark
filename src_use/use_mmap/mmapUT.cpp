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

Time:2017-6

info:
	共享内存文件
	shm_open：创建内存文件，路径要求类似/filename，以/起头，然后文件名，中间不能带/
	
	可以使用cat查看该内存文件的内容
	cat /dev/shm/xxxxx
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
////////////////////////////////////////////////////////////////////////////////
// mmapUT
//

class mmapUT : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

/*封装打印出错函数*/
void sys_err(const char *str,int num){
	perror(str);
	exit(num);
}

TEST_F(mmapUT, Write)
{
	int fd = shm_open("/hello.txt",O_RDWR|O_CREAT|O_EXCL,0777);
	
	//O_EXCL|O_CREAT,若文件已经存在，则报错
	if(fd < 0){
		/*直接打开文件读写*/
		fd = shm_open("/hello.txt",O_RDWR,0777);
	}
	else {
		//若为自己创建的文件，则为文件分配内存空间大小
		//ftruncate会将参数fd指定的文件大小改为参数length指定的大小。
		ftruncate(fd,4096);
	}
	
	//mmap将一个文件或者其它对象映射进内存。
	//void* mmap ( void * addr , size_t len , int prot , int flags , int fd , off_t offset )
	void *ptr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	//写文件
	printf("start writeing  data....\n");
	strcpy((char*)ptr,"mmap:do something!");
	printf("write over\n");
	
	//阻塞进程
	getchar();
	
	//删除内存映射文件
	shm_unlink("/hello.txt");
	close(fd);
}

TEST_F(mmapUT, Read)
{
	int fd = shm_open("/hello.txt",O_RDWR|O_CREAT|O_EXCL,0777);
	if(fd < 0){
		fd = shm_open("/hello.txt",O_RDWR,0777);
	}
	else {
		ftruncate(fd,4096);
	}
	
	void *ptr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	//读文件
	printf("start reading data....\n");
	printf("%s\n", (char*)ptr);
	printf("read over\n");
	
	//删除内存映射文件
	shm_unlink("/hello.txt");
	close(fd);
}