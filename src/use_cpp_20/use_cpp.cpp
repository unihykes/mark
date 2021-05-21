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
   
Author:liu.hao

Time:2021-5

info:
***************************************************************************************************/
#include <markcore.h>
#include <gtest/gtest.h>
using namespace std::rel_ops;

class ncObject1
{
public:
    ncObject1()=default;
    ncObject1(const int& key, const std::string& content)
        : _key(key)
        , _content(content)
    {
    }
    
    void do_something() const
    {
        cout<<_key<<_content<<endl;
    }
    
    friend auto operator == (const ncObject1& lhs, const ncObject1& rhs)
    {
        return lhs._key == rhs._key;
    }
    friend auto operator < (const ncObject1& lhs, const ncObject1& rhs)
    {
        return lhs._key < rhs._key;
    }
    
    
    friend auto operator == (const ncObject1& target, const int& key)
    {
        return target._key == key;
    }
    friend auto operator < (const ncObject1& target, const int& key)
    {
        return target._key < key;
    }
    friend auto operator != (const ncObject1& target, const int& key)
    {
        return !(target == key);
    }
    friend auto operator <= (const ncObject1& target, const int& key)
    {
        return (target < key) || (target == key);
    }

    friend auto operator > (const ncObject1& target, const int& key)
    {
        return !(target <= key);
    }
    friend auto operator >= (const ncObject1& target, const int& key)
    {
        return !(target < key);
    }
    
    
    friend auto operator == (const int& key, const ncObject1& target)
    {
        return key == target._key;
    }
    friend auto operator < (const int& key, const ncObject1& target)
    {
        return key < target._key;
    }
    friend auto operator != (const int& key, const ncObject1& target)
    {
        return !(key == target);
    }
    friend auto operator <= (const int& key, const ncObject1& target)
    {
        return (key == target) || (key < target);
    }
    friend auto operator > (const int& key, const ncObject1& target)
    {
        return !(key <= target);
    }
    friend auto operator >= (const int& key, const ncObject1& target)
    {
        return !(key < target);
    }
    
public:
    int _key = -1;
    std::string _content;
};


TEST(use_cpp, compare1)
{
    ncObject1 lhs{1, "name1"};
    ncObject1 rhs{2, "name2"};

    if(lhs == rhs) {
        cout<<endl;
    }
    if(lhs != rhs) {
        cout<<endl;
    }
    if(lhs > rhs) {
        cout<<endl;
    }
    if(lhs >= rhs) {
        cout<<endl;
    }
    if(lhs < rhs) {
        cout<<endl;
    }
    if(lhs <= rhs) {
        cout<<endl;
    }
    
    ncObject1 target{1, "name1"};
    if(target == 100) {
        cout<<endl;
    }
    if(target != 100) {
        cout<<endl;
    }
    if(target > 100) {
        cout<<endl;
    }
    if(target >= 100) {
        cout<<endl;
    }
    if(target < 100) {
        cout<<endl;
    }
    if(target <= 100) {
        cout<<endl;
    }
    
    if(200 == target) {
        cout<<endl;
    }
    if(200 != target) {
        cout<<endl;
    }
    if(200 > target) {
        cout<<endl;
    }
    if(200 >= target) {
        cout<<endl;
    }
    if(200 < target) {
        cout<<endl;
    }
    if(200 <= target) {
        cout<<endl;
    }
}
class ncObject2
{
public:
    ncObject2()=default;
    ncObject2(const int& key, const std::string& content)
        : _key(key)
        , _content(content)
    {
    }
    
    void do_something() const
    {
        cout<<_key<<_content<<endl;
    }
    
    friend auto operator <=> (const ncObject2& lhs, const ncObject2& rhs)
    {
        return lhs._key <=> rhs._key;
    }
    friend auto operator == (const ncObject2& lhs, const ncObject2& rhs)
    {
        return lhs._key == rhs._key;
    }
    friend auto operator <=> (const ncObject2& target, const int& key)
    {
        return target._key <=> key;
    }
    friend auto operator == (const ncObject2& target, const int& key)
    {
        return target._key == key;
    }
public:
    int _key = -1;
    std::string _content;
};
TEST(use_cpp, compare2)
{
    ncObject2 lhs{1, "name1"};
    ncObject2 rhs{2, "name2"};

    if(lhs == rhs) {
        cout<<endl;
    }
    if(lhs != rhs) {
        cout<<endl;
    }
    if(lhs > rhs) {
        cout<<endl;
    }
    if(lhs >= rhs) {
        cout<<endl;
    }
    if(lhs < rhs) {
        cout<<endl;
    }
    if(lhs <= rhs) {
        cout<<endl;
    }
    
    ncObject2 target{1, "name1"};
    if(target == 100) {
        cout<<endl;
    }
    if(target != 100) {
        cout<<endl;
    }
    if(target > 100) {
        cout<<endl;
    }
    if(target >= 100) {
        cout<<endl;
    }
    if(target < 100) {
        cout<<endl;
    }
    if(target <= 100) {
        cout<<endl;
    }
    
    if(200 == target) {
        cout<<endl;
    }
    if(200 != target) {
        cout<<endl;
    }
    if(200 > target) {
        cout<<endl;
    }
    if(200 >= target) {
        cout<<endl;
    }
    if(200 < target) {
        cout<<endl;
    }
    if(200 <= target) {
        cout<<endl;
    }
}