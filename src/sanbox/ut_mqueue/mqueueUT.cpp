/***************************************************************************************************
Author:liu.hao

Time:2017-6

info:
	附-查看已经成功创建的Posix消息队列
	#其存在与一个虚拟文件系统中, 需要将其挂载到系统中才能查看
	注意是使用root用户才能成
	mkdir /dev/mqueue
	mount -t mqueue none /dev/mqueue
	还可以使用cat查看该消息队列的状态, rm删除:
	cat /dev/mqueue/abc 
	rm abc
	还可umount该文件系统
	umount /dev/mqueue
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <mqueue.h>


////////////////////////////////////////////////////////////////////////////////
// mqueueUT
//

class mqueueUT : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

//实例消息结构体
struct Student
{
	char name[36];
	int age;
};

/*
参考: 
http://blog.csdn.net/nk_test/article/details/50286309/

struct mq_attr
{
	long mq_flags;		// message queue flag : 0, O_NONBLOCK 
	long mq_maxmsg;		// max number of messages allowed on queue
	long mq_msgsize;	// max size of a message (in bytes)
	long mq_curmsgs;	// number of messages currently on queue 
};
*/


TEST_F(mqueueUT, Send)
{
	mq_unlink("/test");
	cout << "unlink success" << endl;
	
	/*创建一个消息队列
	mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
	name:  消息队列名字;必须以”/”开头, 并且后面不能还有”/”, 形如:/file-name;名字长度不能超过NAME_MAX
	oflag: 与open函数类型, 可以是O_RDONLY, O_WRONLY, O_RDWR, 还可以按位或上O_CREAT, O_EXCL, O_NONBLOCK.
	mode: 如果oflag指定了O_CREAT, 需要指定mode参数;
	attr: 指定消息队列的属性;
	返回值:成功: 返回消息队列文件描述符;失败: 返回-1;
	*/
	mqd_t mqid = mq_open("/test", O_WRONLY|O_CREAT, 0666, NULL);
	if (mqid == -1) {
		throw("mq_open error");	 
	}
	
	//获取消息队列属性
	//返回：成功时为0， 出错时为-1
	struct mq_attr attr;
	if (mq_getattr(mqid, &attr) == -1) {
		throw("mq_getattr error");
	}
	cout << "mq_flags: " << attr.mq_flags << endl;//0
	cout << "Max messages on queue: " << attr.mq_maxmsg << endl;//10
	cout << "Max message size: " << attr.mq_msgsize << endl;//8192
	cout << "current messages: " << attr.mq_curmsgs << endl;//0
	
	//设置消息队列属性
	struct mq_attr newattr = attr;
	if (mq_setattr(mqid, &attr, &newattr) == -1) {
		throw("mq_getattr error");
	}
	
	/*发送消息/读取消息
	int mq_send(mqd_t mqdes, const char *ptr, size_t len, unsigned int prio);
	返回：成功时为0，出错为－1
	
	ssize_t mq_receive(mqd_t mqdes, char *ptr, size_t len, unsigned int *priop);
	返回：成功时为消息中的字节数，出错为－1
	
	消息队列的限制：
	MQ_OPEN_MAX : 一个进程能够同时拥有的打开着消息队列的最大数目
	MQ_PRIO_MAX : 任意消息的最大优先级值加1
	*/
	Student stu = {"abcdef", 23};
	unsigned prio = 1;
	
	while(stu.age) {
		--stu.age;
		if (mq_send(mqid, (const char *)&stu, sizeof(stu), prio) == -1) {
			throw("mq_send error");
		}
		cout << "mq_send success" << stu.age << endl; 
		sleep(1);
	}
	// 关闭已打开的消息队列。
	//int mq_close(mqd_t mqdes);
	//返回： 成功时为0，出错时为-1。
	mq_close(mqid);
	cout << "mq_close success" << endl; 
	
	/*从系统中删除消息队列。
	int mq_unlink(const char *name);
	返回： 成功时为0，出错时为－1
	*/
	//mq_unlink("/test");
	cout << "unlink success" << endl;
}

TEST_F(mqueueUT, Receive)
{
	//获取一个消息队列
	mqd_t mqid = mq_open("/test", O_RDONLY);
	if (mqid == -1) {
		throw("mq_open error");
	}
	
	// 获取消息的最大长度
	struct mq_attr attr;
	if (mq_getattr(mqid, &attr) == -1) {
		throw("mq_getattr error");
	}
	long size = attr.mq_msgsize;
	
	//获取消息
	Student stu;
	do {
		unsigned prio;
		int nrcv = mq_receive(mqid, (char *)&stu, size, &prio);
		if(nrcv == -1) {
			throw("mq_receive error"); 
		}
		cout << "receive " << nrcv << " bytes, priority: "
			<< prio << ", name: "<< stu.name << ", age: " << stu.age << endl;
	} while(stu.age);
	
	mq_close(mqid);
	cout << "mq_open success" << endl;
}








mqd_t mqid;
long size;
void sigHandlerForUSR1(int signo)
{
	//将数据的读取转移到对信号SIGUSR1的响应函数中来
	struct Student buf;
	int nrcv;
	unsigned prio;
	if ((nrcv = mq_receive(mqid, (char *)&buf, size, &prio)) == -1) {
		throw("mq_receive error");
	}
	cout << "receive " << nrcv << " bytes, priority: " 
		<< prio << ", name: " << buf.name << ", age: " << buf.age << endl;
}

TEST_F(mqueueUT, Receive2)
{
	/*
	建立/删除消息到达通知事件
	int mq_notify(mqd_t mqdes, const struct sigevent *notification); 
	返回： 成功时为0，出错时为－1
	功能： 给指定队列建立或删除异步事件通知
	sigev_notify代表通知的方式: 一般常用两种取值:SIGEV_SIGNAL, 以信号方式通知; SIGEV_THREAD, 以线程方式通知
	如果以信号方式通知: 则需要设定一下两个参数:
	   sigev_signo: 信号的代码
	   sigev_value: 信号的附加数据(实时信号)
	如果以线程方式通知: 则需要设定以下两个参数:
	   sigev_notify_function
	   sigev_notify_attributes
	union sigval
	{
		int sival_int;      / Integer value
		void *sival_ptr;    / pointer value
	};

	struct sigevent  
	{  
		int     sigev_notify;   // SIGEV_{ NONE, ISGNAL, THREAD} 
		int     sigev_signo;    // signal number if SIGEV_SIGNAL 
		union sigval sigev_value;   // passed to signal handler or thread 
		void    (*sigev_notify_function)(union sigval);
		pthread_attr_t *sigev_notify_attribute;
	};
	mq_notify 注意点总结:
	   1. 任何时刻只能有一个进程可以被注册为接收某个给定队列的通知;
	   2. 当有一个消息到达某个先前为空的队列, 而且已有一个进程被注册为接收该队列的通知时, 
			只有没有任何线程阻塞在该队列的mq_receive调用的前提下, 通知才会发出;
	   3. 当通知被发送给它的注册进程时, 该进程的注册被撤销. 
		进程必须再次调用mq_notify以重新注册(如果需要的话),但是要注意: 重新注册要放在从消息队列读出消息之前而不是之后(如同示例程序);
	*/

	// 安装信号响应函数
	if (signal(SIGUSR1, sigHandlerForUSR1) == SIG_ERR) {
		throw("signal error");
	}
	
	//获取一个消息队列
	mqid = mq_open("/test", O_RDONLY);
	if (mqid == -1) {
		throw("mq_open error");
	}
	
	// 获取消息的最大长度
	struct mq_attr attr;
	if (mq_getattr(mqid, &attr) == -1) {
		throw("mq_getattr error");
	}
	size = attr.mq_msgsize;
	
	// 注册消息到达通知事件
	struct sigevent event;
	event.sigev_notify = SIGEV_SIGNAL;  //指定以信号方式通知
	event.sigev_signo = SIGUSR1;        //指定以SIGUSR1通知
	if (mq_notify(mqid, &event) == -1) {
		throw("mq_notify error");
	}
	
	//死循环, 等待信号到来
	while (true) {
		sleep(1);
	}
	
	mq_close(mqid);
	cout << "mq_open success" << endl;
}

void sigHandlerForUSR1_2(int signo)
{
	// 注意: 是在消息被读走之前进行注册
	// 不然该程序就感应不到消息队列"从空->非空"的一个过程变化了
	struct sigevent event;
	event.sigev_notify = SIGEV_SIGNAL;  //指定以信号方式通知
	event.sigev_signo = SIGUSR1;        //指定以SIGUSR1通知
	if (mq_notify(mqid, &event) == -1) {
		throw("mq_notify error");
	}
	//将数据的读取转移到对信号SIGUSR1的响应函数中来
	struct Student buf;
	int nrcv;
	unsigned prio;
	if ((nrcv = mq_receive(mqid, (char *)&buf, size, &prio)) == -1) {
		throw("mq_receive error");
	}
	cout << "receive " << nrcv << " bytes, priority: " 
		<< prio << ", name: " << buf.name << ", age: " << buf.age << endl;
}

TEST_F(mqueueUT, Receive3)
{
	// 安装信号响应函数
	if (signal(SIGUSR1, sigHandlerForUSR1_2) == SIG_ERR) {
		throw("signal error");
	}
	
	//获取一个消息队列
	mqid = mq_open("/test", O_RDONLY);
	if (mqid == -1) {
		throw("mq_open error");
	}
	
	// 获取消息的最大长度
	struct mq_attr attr;
	if (mq_getattr(mqid, &attr) == -1) {
		throw("mq_getattr error");
	}
	size = attr.mq_msgsize;
	
	// 注册消息到达通知事件
	struct sigevent event;
	event.sigev_notify = SIGEV_SIGNAL;  //指定以信号方式通知
	event.sigev_signo = SIGUSR1;        //指定以SIGUSR1通知
	if (mq_notify(mqid, &event) == -1) {
		throw("mq_notify error");
	}
	
	//死循环, 等待信号到来
	while (true) {
		sleep(1);
	}
	
	mq_close(mqid);
	cout << "mq_open success" << endl;
}