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

#include <markcore.h>
#include <gtest/gtest.h>
#include <algorithm/mkBinaryTree.h>

TEST(mkBinaryTree, recursive)
{
    mkBinaryTreeBuilder builder(mkBinaryTreeBuilder::Order::PRE_ORDER);
    builder.Insert_recursive();//初始化: ABE##F##CG### 
    std::shared_ptr<mkBinaryTree> pTree = builder.Get();
    
    MK_PRINT("先序遍历：");
    pTree->VisitByPreorder_recursive();
    
    MK_PRINT("中序遍历：");
    pTree->VisitByInorder_recursive();
    
    MK_PRINT("后序遍历：");
    pTree->VisitByPostorder_recursive();
}

TEST(mkBinaryTree, non_recursive)
{
    mkBinaryTreeBuilder builder(mkBinaryTreeBuilder::Order::PRE_ORDER);
    //初始化: ABE##F##CG###
    while(true) {
        unsigned char data;
        scanf("%c",&data);
        if(data == '\n') {
            break;
        }
        builder.Insert(data);
    }
    std::shared_ptr<mkBinaryTree> pTree = builder.Get();
    
    MK_PRINT("先序遍历(非递归)：");
    pTree->VisitByPreorder();
    
    MK_PRINT("中序遍历(非递归)：");
    pTree->VisitByInorder();
    
    MK_PRINT("后序遍历(非递归)：");
    pTree->VisitByPostorder();
    
    MK_PRINT("层次遍历：");
    pTree->VisitByLevelorder();
}