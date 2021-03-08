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
	Linux信号量 sem_t简介 
	信号量的数据类型为结构sem_t，它本质上是一个长整型的数。
	
	int sem_init (sem_t *sem, int pshared, unsigned int value);
	用来初始化一个信号量,
	sem为指向信号量结构的一个指针；
	pshared不为0时此信号量在进程间共享，否则只能为当前进程的所有线程共享；
	value给出了信号量的初始值。
	信号量用sem_init函数创建的，
	
	
	sem_open功能：
	创建并初始化有名信号灯
	name   信号灯的外部名字(不能为空，为空会出现段错误) 
	oflag  选择创建或打开一个现有的信号灯  
	mode 权限位  
	value 信号灯初始值  
	返回值：成功时返回指向信号灯的指针，出错时为SEM_FAILED，
	oflag参数能是0（打开一个已创建的）、O_CREAT（创建一个信号灯）或O_CREAT|O_EXCL（如果没有指定的信号灯就创建），
	如果指定了O_CREAT，那么第三个和第四个参数是需要的；
		其中mode参数指定权限位，value参数指定信号灯的初始值，通常用来指定共享资源的书面。该初始不能超过 SEM_VALUE_MAX，这个常值必须低于为32767。
		二值信号灯的初始值通常为1，计数信号灯的初始值则往往大于1。
	
	sem_close 关闭有名信号灯。
	若成功则返回0，否则返回-1。一个进程终止时，内核还对其上仍然打开着的所有有名信号灯自动执行这样的信号灯关闭操作。
	不论该进程是自愿终止的还是非自愿终止的，这种自动关闭都会发生。但应注意的是关闭一个信号灯并没有将他从系统中删除。
	这就是说，Posix有名信号灯至少是随内核持续的：即使当前没有进程打开着某个信号灯，他的值仍然保持。
	多进程打开时候，一边sem_close后，仍可以打开已经打开的信号量。
	
	sem_unlink 从系统中删除信号灯 
	定义：int sem_unlink(const char *name);若成功则返回0，否则返回-1。
	有名信号灯使用sem_unlink从系统中删除。每个信号灯有一个引用计数器记录当前的打开次数，
	sem_unlink必须等待这个数为0时才能把name所指的信号灯从文件系统中删除。也就是要等待最后一个sem_close发生。
	
	sem_getvalue 
	测试信号灯
	
	函数int sem_post( sem_t *sem )用来增加信号量的值。
	当有线程阻塞在这个信号量上时，调用这个函数会使其中的一个线程不在阻塞，选择机制同样是由线程的调度策略决定的。
	int sem_post(sem_t *sem);sem_post() 成功时返回 0；错误时，信号量的值没有更改，-1 被返回，并设置errno 来指明错误。
	错误   EINVAL 　sem 不是一个有效的信号量。 　EOVERFLOW 信号量允许的最大值将要被超过。
	
	函数int sem_wait( sem_t *sem )
	被用来阻塞当前线程直到信号量sem的值大于0，解除阻塞后将sem的值减一，表明公共资源经使用后减少。
	
	sem_post函数的作用是给信号量的值加上一个“1”，它是一个“原子操作”
	－－－即同时对同一个信号量做加“1”操作的两个线程是不会冲突的；而同 时对同一个文件进行读、加和写操作的两个程序就有可能会引起冲突。
	信号量的值永远会正确地加一个“2”－－因为有两个线程试图改变它。
	
	sem_wait函数也是一个原子操作，它的作用是从信号量的值减去一个“1”，但它永远会先等待该信号量为一个非零值才开始做减法。
	也就是说，如果你对 一个值为2的信号量调用sem_wait(),线程将会继续执行，介信号量的值将减到1。
	如果对一个值为0的信号量调用sem_wait()，这个函数就 会地等待直到有其它线程增加了这个值使它不再是0为止。
	如果有两个线程都在sem_wait()中等待同一个信号量变成非零值，那么当它被第三个线程增加 一个“1”时，
	等待线程中只有一个能够对信号量做减法并继续执行，另一个还将处于等待状态。
	信号量这种“只用一个函数就能原子化地测试和设置”的能力下正是它的价值所在。 还有另外一个信号量函数sem_trywait，它是sem_wait的非阻塞搭档。
	
	
	函数sem_trywait ( sem_t *sem )
	是函数sem_wait（）的非阻塞版本，它直接将信号量sem的值减一。在成功完成之后会返回零。其他任何返回值都表示出现了错误
	
	函数sem_destroy(sem_t *sem)
	用来释放信号量sem，属于无名信号量。　
	在清理信号量的时候如果还有线程在等待它，用户就会收到一个错误。与其它的函数一样，这些函数在成功时都返回“0”。
	
	sem_t分为有名和无名。有名的sem_t通过sem_open来创建， 而无名的sem_t通过sem_init的初始化。
	有名和无名的sem_t主要区别：
	1. 效率：有名sem_t是放在文件，无名的sem_t是放在内存。
	2.限制：有名的sem_t可以用来同步多线程，任意多进程。而无名的sem_t可以用来同步多线程，以及Fork出来的进程间的同步。
	
	typedef union
	{
		char __size[__SIZEOF_SEM_T];
		long int __align;
	} sem_t;
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include<semaphore.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>


////////////////////////////////////////////////////////////////////////////////
// semUT
//

class semUT : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};


////////////////////////////////////////////////////////////////////////////////
// 无名信号
//
sem_t bin_sem;  

//线程1
void* thread_function1(void *arg)
{
	printf("thread_function1--------------sem_wait\n");  
	printf("sem_wait --begin\n");
	sem_wait(&bin_sem);  
	printf("sem_wait --end\n");
	while (1) {  
		printf("th1 running!\n");  
		sleep(1);  
	}
	
	return NULL;
}

//线程2
void* thread_function2(void *arg)  
{  
	printf("thread_function2--------------sem_post\n");
	sem_post(&bin_sem);  
	printf("sem_post --end\n");  
	while (1){  
		printf("th2 running!\n");  
		sleep(1);  
	}  
	
	return NULL;
}

TEST_F(semUT, SemWait)
{
	int res;
	pthread_t a_thread;
	//void* thread_result;
	
	//初始化信号量
	res = sem_init(&bin_sem, 0, 0);
	if (res != 0) {
		perror("Semaphore initialization failed");  
	}
	printf("sem_init\n");  
	
	//创建线程1
	res = pthread_create(&a_thread, NULL, thread_function1, NULL);  
	if (res != 0){
		perror("Thread creation failure");  
	}
	printf("thread_function1\n");
	
	sleep(5);
	printf("sleep\n");  
	
	//创建线程2
	res = pthread_create(&a_thread, NULL, thread_function2, NULL);
	if (res != 0) {
		perror("Thread creation failure");  
	}
	
	while (true) {
		printf("main() running !\n");
		sleep(3);
	}
}

////////////////////////////////////////////////////////////////////////////////
// 有名信号
//

/*
有名信号量的特点是把信号量的值保存在文件中。这决定了它的用途非常广：
既可以用于线程，也可以用于相关进程间，甚至是不相关进程。
由于有名信号量的值是保存在文件中的，所以对于相关进程来说，子进程是继承了父进程的文件描述符，
那么子进程所继承的文件描述符所指向的文件是和父进程一样的，当然文件里面保存的有名信号量值就共享了。
有名信号量是位于共享内存区的，那么它要保护的资源也必须是位于共享内存区，只有这样才能被无相关的进程所共享。
在下面这个例子中，服务进程和客户进程都使用shmget和shmat来获取得一块共享内存资源。然后利用有名信号量来对这块共享内存资源进行互斥保护。
*/



#define SHMSZ 27
char SEM_NAME[]= "vik";

TEST_F(semUT, Server)
{
	char ch;
	int shmid;
	key_t key;
	char* shm, *s;
	sem_t *mutex;
	
	//name the shared memory segment
	key = 1000;

	//create & initialize semaphore
	//创建一个有名信号量
	//name表示有名信号量的名字，这个路径名字会映射到/dev/shm/目录下，形成sem.name的文件，
	mutex = sem_open(SEM_NAME,O_CREAT,0644,1);
	if(mutex == SEM_FAILED) {
		perror("unable to create semaphore");
		sem_unlink(SEM_NAME);
		return;
	}
	printf("sem_open():mutex = %ld\n", mutex->__align);
	
	//创建一个共享内存
	//create the shared memory segment with this key
	shmid = shmget(key,SHMSZ,IPC_CREAT|0666);
	if(shmid<0) {
		perror("failure in shmget");
		return;
	}
	
	//获取共享内存地址
	//attach this segment to virtual memory
	shm = (char*)shmat(shmid,NULL,0);
	
	//向共享内存中写入数据
	//start writing into memory
	printf("start...\n");
	s = shm;
	for(ch='A';ch<='Z';ch++) {
		printf("sem_wait()--begin(),mutex = %ld\n", mutex->__align);
		sem_wait(mutex);
		printf("sem_wait()--end(),mutex = %ld\n", mutex->__align);
		*s++ = ch;
		printf("%c\n", ch);
		sem_post(mutex);
		sleep(1);
		printf("sem_post()--end(),mutex = %ld\n", mutex->__align);
	}

	//the below loop could be replaced by binary semaphore
	//while(*shm != '*') {
	//	sleep(1);
	//}
	
	//阻塞进程
	getchar();
	
	sem_close(mutex);
	sem_unlink(SEM_NAME);
	shmctl(shmid, IPC_RMID, 0);
}

TEST_F(semUT, Client)
{
	//char ch;
	int shmid;
	key_t key;
	char *shm,*s;
	sem_t *mutex;

	//name the shared memory segment
	key = 1000;

	//create & initialize existing semaphore
	mutex = sem_open(SEM_NAME,0,0644,0);
	if(mutex == SEM_FAILED)
	{
		perror("reader:unable to execute semaphore");
		sem_close(mutex);
		return;
	}
	printf("sem_open():mutex = %ld\n", mutex->__align);
	
	//create the shared memory segment with this key
	shmid = shmget(key,SHMSZ,0666);
	if(shmid<0)
	{
		perror("reader:failure in shmget");
		return;
	}

	//attach this segment to virtual memory
	shm = (char*)shmat(shmid,NULL,0);

	//start reading
	s = shm;
	for(s=shm;*s!=NULL;s++)
	{
		printf("sem_wait()--begin(),mutex = %ld\n", mutex->__align);
		sem_wait(mutex);
		printf("sem_wait()--end(),mutex = %ld\n", mutex->__align);
		//putchar(*s);
		printf("%c\n", *s);
		
		sleep(1);
		sem_post(mutex);
		printf("sem_post()--end(),mutex = %ld\n", mutex->__align);
	}

	//once done signal exiting of reader:This can be replaced by another semaphore
	//*shm = '*';
	
	sem_close(mutex);
	//shmctl(shmid, IPC_RMID, 0);
}















