因为lambda表达式是匿名函数,所以不能直接调用自身,但使用function存储后就变成了一个有名变量,就可以被捕获并调用;


```cpp


	std::function<void(int)> func = [&](int i) {
		if(i > 100){
			return;
		}
		cout <<++i<<endl;
		func(i);
	};
```