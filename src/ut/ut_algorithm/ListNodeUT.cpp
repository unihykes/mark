/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ListNodeUT : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

struct ncNode
{
	ncNode* next;
	int value;
	
	ncNode(int val) 
		: next(nullptr)
		, value(val)
	{
		cout<<"value = "<<value<<endl;
	}
	
};

bool hasCycle(ncNode* pNode)
{
	if(pNode == nullptr || pNode->next == nullptr) {
		return false;
	}
	
	ncNode* tempNode = pNode->next;
	while(tempNode) {
		if(tempNode->next == pNode) {
			return true;
		}
		if(tempNode->next == nullptr) {
			break;
		}
		tempNode = tempNode->next;
	}
	return false;
}

bool hasCycle2(ncNode* pNode, ncNode** pEnter)
{
	if(pNode == nullptr || pNode->next == nullptr) {
		return false;
	}
	
	ncNode* fast = pNode;
	ncNode* slow = pNode;
	
	//判断环是否存在
	while(fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		cout<<"fast="<<fast->value<<",slow="<<slow->value<<endl;
		//存在
		if(fast == slow) {
			cout<<"\nbreak="<<fast->value<<endl<<endl;
			break;
		}
	}
	
	//不存在
	if(fast == nullptr || fast->next == nullptr) {
		return false;
	}
	
	//有环时,计算入口点
	{
		*pEnter = pNode;
		//一个头指针，一个相遇点指针，两个第一次相等时为环入口点
		while(*pEnter != fast) {
			*pEnter=(*pEnter)->next;
			fast=fast->next;
			cout<<"fast="<<fast->value<<",pEnter="<<(*pEnter)->value<<endl;
		}
	}
	
	return true;
}

TEST_F(ListNodeUT, HasCycle)
{
	ncNode* header = new ncNode(0);
	ncNode* node = header;
	
	for(int i = 1; i != 33; ++i) {
		node->next = new ncNode(i);
		node = node->next;
	}
	ncNode* end = node;
	
	node = header;
	for(int i = 0; i != 15; ++i) {
		node = node->next;
	}
	end->next = node;
	cout<<"\nenter = "<<end->next->value<<endl<<endl;
	
	
	ncNode* pEnter = nullptr;
	bool ret = hasCycle2(header, &pEnter);
	if (pEnter) {
		cout <<"\nresult="<<pEnter->value<<endl<<endl;
	}
}

