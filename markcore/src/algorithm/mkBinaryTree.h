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

Time:2018-2

info:

***************************************************************************************************/

#ifndef __mkBinaryTree
#define __mkBinaryTree

//二叉树结点
class mkBinaryNode
{
public:
    mkBinaryNode(const unsigned char& ch)
        : data(ch)
    {
    }
    void Visit()
    {
        MK_PRINT("%c ",data);
    }
    
public:
    unsigned char data = 0;//数据
    std::shared_ptr<mkBinaryNode>    lchild;//左孩
    std::shared_ptr<mkBinaryNode>    rchild;//右孩
    
};

class MK_DLL_EXPORT mkBinaryTree
{
public:
    mkBinaryTree(std::shared_ptr<mkBinaryNode> pRootNode);
    ~mkBinaryTree();
    
    void VisitByPreorder_recursive();//先序遍历-递归
    void VisitByInorder_recursive();//中序遍历-递归
    void VisitByPostorder_recursive();//后序遍历-递归
    
    void VisitByPreorder();//先序遍历-非递归
    void VisitByInorder();//中序遍历-非递归
    void VisitByPostorder();//后序遍历-非递归
    void VisitByLevelorder();//层次遍历-非递归
    

private:
    std::shared_ptr<mkBinaryNode>   _pRootNode;
};

class MK_DLL_EXPORT mkBinaryTreeBuilder 
{
public:
    enum class Order{
        PRE_ORDER,
        IN_ORDER,
        POST_ORDER,
    };
    mkBinaryTreeBuilder(const mkBinaryTreeBuilder::Order& order);
    ~mkBinaryTreeBuilder();
    
    void Insert_recursive();//插入元素-递归
    void Insert(const unsigned char& data);//插入元素-非递归
    std::shared_ptr<mkBinaryTree> Get();
    
private:
    const mkBinaryTreeBuilder::Order _order;
    std::shared_ptr<mkBinaryNode>   _pRootNode;
    std::shared_ptr<mkBinaryNode>   _pCurrentNode;
    stack<std::shared_ptr<mkBinaryNode>>    _nodeStack;
};

#endif