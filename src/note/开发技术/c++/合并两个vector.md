


```cpp
#include <iostream>  
#include <string>  
#include <vector>  
using namespace std;  
int main()  
{  
  vector<string> vec1, vec2;  
  vec1.push_back("aa");  
  vec1.push_back("bb");  
  vec1.push_back("cc");  
  vec2.push_back("dd");  
  vec2.push_back("ee");  
  vec2.push_back("ff");  
  vector<string> vec(vec1.size() + vec2.size());  
  merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec.begin());    
  for (int j = 0; j < vec.size(); ++j) {  
    cout << vec[j] << endl;  

  }   

v.insert(pos,elem)　　　　　　 在pos位置插入一个elem拷贝，传回新数据位置（位置指传回地址值）
v.insert(pos,n,elem)　　　　　　在pos位置插入在[beg,end)区间的数据。无返回值。
v.insert(pos,beg,end)　　　　 在pos位置插入n个elem数据。无返回值。
v.erase(pos)　　　　　　　　　 删除pos位置的数据，传回下一个数据的位置。
v.erase(beg,end)　　　　　　　删除[beg,end)区间的数据，传回下一个数据的位置。
```