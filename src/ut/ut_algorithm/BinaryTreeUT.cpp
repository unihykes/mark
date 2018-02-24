/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include<stack>
#include<queue>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class BinaryTreeUT : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

//二叉树结点
typedef struct BiTNode
{
	//数据
	char data;
	//左右孩子指针
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;


//按先序序列创建二叉树
int CreateBiTree(BiTree &T)
{
	char data;
	//按先序次序输入二叉树中结点的值（一个字符），‘#’表示空树
	scanf("%c",&data);
	if(data == '#'){
		T = NULL;
	}
	else{
		T = (BiTree)malloc(sizeof(BiTNode));
		//生成根结点
		T->data = data;
		//构造左子树
		CreateBiTree(T->lchild);
		//构造右子树
		CreateBiTree(T->rchild);
	}
	return 0;
}

//访问节点
void Visit(BiTree T)
{
	if(T->data != '#'){
		printf("%c ",T->data);
	}
}

//先序遍历
void PreOrder(BiTree T)
{
	if(T != NULL){
		//访问根节点
		Visit(T);
		//访问左子结点
		PreOrder(T->lchild);
		//访问右子结点
		PreOrder(T->rchild);
	}
}
//中序遍历  
void InOrder(BiTree T){  
	if(T != NULL){  
		//访问左子结点  
		InOrder(T->lchild);  
		//访问根节点  
		Visit(T);  
		//访问右子结点  
		InOrder(T->rchild);  
	}  
}  
//后序遍历
void PostOrder(BiTree T){
	if(T != NULL){
		//访问左子结点
		PostOrder(T->lchild);
		//访问右子结点
		PostOrder(T->rchild);
		//访问根节点
		Visit(T);
	}
}

/* 先序遍历(非递归)
思路：访问T->data后，将T入栈，遍历左子树；遍历完左子树返回时，栈顶元素应为T，出栈，再先序遍历T的右子树。
*/
void PreOrder2(BiTree T)
{
	stack<BiTree> stack;
	//p是遍历指针
	BiTree p = T;
	//栈不空或者p不空时循环
	while(p || !stack.empty()){
		if(p != NULL){
			//存入栈中
			stack.push(p);
			//访问根节点
			printf("%c ",p->data);
			//遍历左子树
			p = p->lchild;
		}
		else{
			//退栈
			p = stack.top();
			stack.pop();
			//访问右子树
			p = p->rchild;
		}
	}//while
}

/* 中序遍历(非递归)
思路：T是要遍历树的根指针，中序遍历要求在遍历完左子树后，访问根，再遍历右子树。
先将T入栈，遍历左子树；遍历完左子树返回时，栈顶元素应为T，出栈，访问T->data，再中序遍历T的右子树。
*/
void InOrder2(BiTree T){
	stack<BiTree> stack;
	//p是遍历指针
	BiTree p = T;
	//栈不空或者p不空时循环
	while(p || !stack.empty()){
		if(p != NULL){
			//存入栈中
			stack.push(p);
			//遍历左子树
			p = p->lchild;
		}
		else{
			//退栈，访问根节点
			p = stack.top();
			printf("%c ",p->data);
			stack.pop();
			//访问右子树
			p = p->rchild;
		}
	}//while
}


//后序遍历(非递归)
typedef struct BiTNodePost{
	BiTree biTree;
	char tag;
}BiTNodePost,*BiTreePost;


void PostOrder2(BiTree T)
{
	stack<BiTreePost> stack;
	//p是遍历指针
	BiTree p = T;
	BiTreePost BT;
	//栈不空或者p不空时循环
	while(p != NULL || !stack.empty()){
		//遍历左子树
		while(p != NULL){
			BT = (BiTreePost)malloc(sizeof(BiTNodePost));
			BT->biTree = p;
			//访问过左子树
			BT->tag = 'L';
			stack.push(BT);
			p = p->lchild;
		}
		//左右子树访问完毕访问根节点
		while(!stack.empty() && (stack.top())->tag == 'R'){
			BT = stack.top();
			//退栈
			stack.pop();
			BT->biTree;
			printf("%c ",BT->biTree->data);
		}
		//遍历右子树
		if(!stack.empty()){
			BT = stack.top();
			//访问过右子树
			BT->tag = 'R';
			p = BT->biTree;
			p = p->rchild;
		}
	}//while
}

//层次遍历
void LevelOrder(BiTree T)
{
	BiTree p = T;
	//队列
	queue<BiTree> queue;
	//根节点入队
	queue.push(p);
	//队列不空循环
	while(!queue.empty()){
		//对头元素出队
		p = queue.front();
		//访问p指向的结点
		printf("%c ",p->data);
		//退出队列
		queue.pop();
		//左子树不空，将左子树入队
		if(p->lchild != NULL){
			queue.push(p->lchild);
		}
		//右子树不空，将右子树入队
		if(p->rchild != NULL){
			queue.push(p->rchild);
		}
	}
}

TEST_F(BinaryTreeUT, List)
{
	BiTree T;
	//ABE##F##CG### 
	CreateBiTree(T);
	printf("先序遍历：\n");
	PreOrder(T);
	printf("\n");
	printf("先序遍历(非递归)：\n");
	PreOrder2(T);
	printf("\n");
	printf("中序遍历：\n");
	InOrder(T);
	printf("\n");
	printf("中序遍历(非递归)：\n");
	InOrder2(T);
	printf("\n");
	printf("后序遍历：\n");
	PostOrder(T);
	printf("\n");
	printf("后序遍历(非递归)：\n");
	PostOrder2(T);
	printf("\n");
	printf("层次遍历：\n");
	LevelOrder(T);
	printf("\n");
	system("pause");
}