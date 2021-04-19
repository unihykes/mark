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

Time:2017-8

info:

***************************************************************************************************/

#include <mkheaders.h>
#include "mkModuleInstance.h"
#include "print/mkPrint.h"
#include "mkBinaryTree.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
mkBinaryNode::mkBinaryNode(const unsigned char& ch)
    : data(ch)
{
}
void 
mkBinaryNode::Visit()
{
    MK_PRINT("%c ",data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
mkBinaryTree::mkBinaryTree(std::shared_ptr<mkBinaryNode> pRootNode)
    : _pRootNode(pRootNode)
{
}

mkBinaryTree::~mkBinaryTree()
{
}

void 
mkBinaryTree::VisitByPreorder_recursive()
{
    std::function<void(std::shared_ptr<mkBinaryNode>)> Visit = [&](std::shared_ptr<mkBinaryNode> pNode) {
        if(pNode) {
            pNode->Visit();
            Visit(pNode->lchild);
            Visit(pNode->rchild);
        }
    };
    
    Visit(_pRootNode);
}

void 
mkBinaryTree::VisitByInorder_recursive()
{
    std::function<void(std::shared_ptr<mkBinaryNode>)> Visit = [&](std::shared_ptr<mkBinaryNode> pNode) {
        if(pNode) {
            Visit(pNode->lchild);
            pNode->Visit();
            Visit(pNode->rchild);
        }
    };
    
    Visit(_pRootNode);
}

void 
mkBinaryTree::VisitByPostorder_recursive()
{
    std::function<void(std::shared_ptr<mkBinaryNode>)> Visit = [&](std::shared_ptr<mkBinaryNode> pNode) {
        if(pNode) {
            Visit(pNode->lchild);
            Visit(pNode->rchild);
            pNode->Visit();
        }
    };
    
    Visit(_pRootNode);
}

void 
mkBinaryTree::VisitByPreorder()
{
    stack<std::shared_ptr<mkBinaryNode>> tempStack;
    std::shared_ptr<mkBinaryNode> pTemp = _pRootNode;
    
    while(true){
        if(!pTemp && tempStack.empty()){
            break;//栈空且 pTemp 空,则结束循环
        }
        
        if(pTemp){
            tempStack.push(pTemp);//入栈
            pTemp->Visit();
            pTemp = pTemp->lchild;//遍历左子树
        }
        else{
            
            pTemp = tempStack.top();//出栈
            tempStack.pop();
            pTemp = pTemp->rchild;//访问右子树
        }
    }
}

void 
mkBinaryTree::VisitByInorder()
{
    //中序遍历要求在遍历完左子树后，访问根，再遍历右子树
    stack<std::shared_ptr<mkBinaryNode>> tempStack;
    std::shared_ptr<mkBinaryNode> pTemp = _pRootNode;
    
    //栈不空或者p不空时循环
    while(true){
        if(!pTemp && tempStack.empty()){
            break;//栈空且 pTemp 空,则结束循环
        }
        
        if(pTemp){
            tempStack.push(pTemp);//入栈
            pTemp = pTemp->lchild;//遍历左子树
        }
        else{
            pTemp = tempStack.top();//出栈
            tempStack.pop();
            pTemp->Visit();
            pTemp = pTemp->rchild;//访问右子树
        }
    }
}

void 
mkBinaryTree::VisitByPostorder()
{
    struct mkBinaryNodePost
    {
        std::shared_ptr<mkBinaryNode> pNode;
        char type = 0;
    };
    
    stack<std::shared_ptr<mkBinaryNodePost>> tempStack;
    std::shared_ptr<mkBinaryNode> pTemp = _pRootNode;
    std::shared_ptr<mkBinaryNodePost> pTempWithType;
    
    while(true){
        if(!pTemp && tempStack.empty()){
            break;//栈空且 pTemp 空,则结束循环
        }
        
        //遍历左子树
        while(pTemp){
            pTempWithType = std::make_shared<mkBinaryNodePost>();
            pTempWithType->pNode = pTemp;
            pTempWithType->type = 'L';//访问过左子树
            tempStack.push(pTempWithType);
            pTemp = pTemp->lchild;
        }
        
        //左右子树访问完毕访问根节点
        while(!tempStack.empty() && tempStack.top()->type == 'R'){
            pTempWithType = tempStack.top();
            tempStack.pop();//出栈
            pTempWithType->pNode;
            pTempWithType->pNode->Visit();
        }
        
        //遍历右子树
        if(!tempStack.empty()){
            pTempWithType = tempStack.top();
            pTempWithType->type = 'R';//访问过右子树
            pTemp = pTempWithType->pNode;
            pTemp = pTemp->rchild;
        }
    }
}

void 
mkBinaryTree::VisitByLevelorder()
{
    std::shared_ptr<mkBinaryNode> pTemp = _pRootNode;
    queue<std::shared_ptr<mkBinaryNode>> queue;//队列
    queue.push(pTemp);

    while(!queue.empty()){//队列不空循环
        pTemp = queue.front();//对头元素出队
        pTemp->Visit();//访问p指向的结点
        queue.pop();//退出队列
        
        if(pTemp->lchild){//左子树不空，将左子树入队
            queue.push(pTemp->lchild);
        }
        //右子树不空
        if(pTemp->rchild){
            queue.push(pTemp->rchild);
        }
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////////

mkBinaryTreeBuilder::mkBinaryTreeBuilder(const mkBinaryTreeBuilder::Order& order)
    : _order(order)
{
}

mkBinaryTreeBuilder::~mkBinaryTreeBuilder()
{
}

void 
mkBinaryTreeBuilder::Insert_recursive()
{
    unsigned char data = 0;
    std::function<void(std::shared_ptr<mkBinaryNode>&)> CreateByPreorder = [&](std::shared_ptr<mkBinaryNode>& pNode) {
        if(data == '\n'){
            return;//终止递归
        }
        
        scanf("%c",&data);
        //按先序次序输入二叉树中结点的值（一个字符），‘#’表示空树
        if(data == '#'){
            return;
        }
        else{
            if(data == '\n'){
                return;//终止递归
            }
            //生成结点
            pNode = std::make_shared<mkBinaryNode>(data);
            
            //构造左子树
            CreateByPreorder(pNode->lchild);
            //构造右子树
            CreateByPreorder(pNode->rchild);
        }
    };
    
    CreateByPreorder(_pRootNode);
}

void 
mkBinaryTreeBuilder::Insert(const unsigned char& data)
{
    //先序插入
    auto InsertByPreorder = [&](const unsigned char& data) {
        if(data != '#') {
            if(!_pCurrentNode) {
                _pRootNode = std::make_shared<mkBinaryNode>(data);
                _pCurrentNode = _pRootNode;
            }
            else {
                if(!_pCurrentNode->lchild) {
                    _pCurrentNode->lchild = std::make_shared<mkBinaryNode>(data);
                    _pCurrentNode = _pCurrentNode->lchild;
                }
                else if(!_pCurrentNode->rchild){
                    _pCurrentNode->rchild = std::make_shared<mkBinaryNode>(data);
                    _pCurrentNode = _pCurrentNode->rchild;
                }
                else {
                    MK_PRINT("error,something is wrong!");
                }
            }
            _nodeStack.push(_pCurrentNode);
        }
        else {
            if(!_nodeStack.empty()) {
                _pCurrentNode = _nodeStack.top();
                _nodeStack.pop();
            }
            else {
                MK_PRINT("insert end.");
            }
        }
    };
    
    switch(_order) {
    case Order::PRE_ORDER :
        InsertByPreorder(data);
        break;
    default:
        break; 
    }
}

std::shared_ptr<mkBinaryTree> 
mkBinaryTreeBuilder::Get()
{
    std::shared_ptr<mkBinaryTree> result = std::make_shared<mkBinaryTree>(_pRootNode);
    return result;
}