---
标题: 设计模式作业题
作者: unihykes (liu.hao@aishu.cn)
日期: 2021/7/16
markdown:
  image_dir: ./assets
  path: exam.md
  ignore_from_front_matter: true
  absolute_image_path: false
---

[toc]

# 前提:
#### 前提1:
已知2个集合类
class ObjectList; 
class ObjectMap;
已经实现了一种查询功能(**map优先**):
批量查询一组key, 并将每个key对应的value拼接到指定字符串中;
如果key在objMap中存在, 则直接拼接之,
如果key在objMap中不存在, 则从objList中查询, 如果在objList中存在,则拼接之,否则拼接一个星号替代之;

```cpp
/***************************************************************************************************
Author: unihykes
Time:   2021-7
Info:   demo
***************************************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <optional>
#include <random>
#include <chrono>
using namespace std;

class ObjectList
{
public:
    void Put(int&& key, string&& value)
    {
        _data.emplace_back(ObjectInfo{ key, value});
    }
private:
    std::optional<string> Find(const int& key)
    {
        auto iter = find_if(_data.begin(), _data.end(),
            [&](const ObjectInfo& info) ->bool {return info.key == key; });

        if (iter == _data.end()) {
            return std::nullopt;
        }
        else {
            return iter->value;
        }
    }
    friend class ObjectMap;
private:
    struct ObjectInfo
    {
        int key;
        std::string value;
    };
    std::list<ObjectInfo> _data;
};

class ObjectMap
{
public:
    ObjectMap(ObjectList* pList) 
        : _pList(pList)
    {
    }

    void Put(int&& key, string&& value)
    {
        _data.emplace(key, value);
    }
    std::string FindRange(const vector<int>& keys)
    {
        string result;
        for (const auto& elem : keys) {
            auto ret = Find(elem);
            if (ret) {
                result.append(*ret).append("_");
            }
            else {
                auto ret2 = _pList->Find(elem);
                if (ret2) {
                    result.append(*ret2).append("_");
                }
                else {
                    result.append("*").append("_");
                }
            }
        }
        return result;
    }
    
private:
    std::optional<string> Find(const int& key)
    {
        auto iter = _data.find(key);
        if (iter == _data.end()) {
            return std::nullopt;
        }
        else {
            return iter->second;
        }
    }
private:
    std::map<int, std::string> _data;
    ObjectList* _pList;
};
```

#### 前提2:
已知测试代码如下:

```cpp
//模拟一些业务数据的生成,非关键代码
void Init(ObjectList& objList, ObjectMap& objMap, vector<int>& keys)
{
    const int minKey = 0;
    const int maxKey = 20;

    std::default_random_engine randomEngine;
    randomEngine.seed(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dis(minKey, maxKey);
    
    for (int i = minKey; i != maxKey; ++i) {
        auto key1 = dis(randomEngine);
        objList.Put(int(key1), std::to_string(key1));

        auto key2 = dis(randomEngine);
        objMap.Put(int(key2), std::to_string(key2));

        keys.emplace_back(dis(randomEngine));
    }
}

int main()
{
    ObjectList objList;
    ObjectMap objMap(&objList);
    vector<int> keys;
    
    //模拟初始化
    Init(objList, objMap, keys);

    //进行一次查询操作
    auto result = objMap.FindRange(keys);
    cout << result << endl;
}
```

# 作业题:
#### 作业题1:
扩展以上业务逻辑功能, 使其额外支持一种新的查询功能(**list优先**):
批量查询一组key, 并将每个key对应的value拼接到指定字符串中;
如果key在objList中存在, 则直接拼接之,
如果key在objList中不存在, 则从objMap中查询, 如果在objMap中存在,则拼接之,否则拼接一个星号替代之;

#### 作业题2:
在实现题目1的过程中, 用任意的设计模式重构代码, 
使class ObjectList与class ObjectMap解耦;


#### 作业题-备注:
1.以上示例代码兼容了C++17;
  完成作业时可使用C++任意版本(C++03,C++11,C++14,C++17,C++20),
  一些不兼容的特性需要自行处理;
2.如果使用其他开发语言(Golang等),请按照示例代码的业务逻辑自行转换;