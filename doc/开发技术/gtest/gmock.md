Google Mock(Gmock)简单使用和源码分析——简单使用
https://blog.csdn.net/breaksoftware/article/details/51384083


Google Mock(Gmock)简单使用和源码分析——源码分析
https://blog.csdn.net/breaksoftware/article/details/51438033


Google Mock 入门
http://www.cnblogs.com/welkinwalker/archive/2011/11/29/2267225.html



#使用说明:
```cpp

   EXPECT_CALL(mock_object, Method(argument-matchers))
       .With(multi-argument-matchers)
       .Times(cardinality)
       .InSequence(sequences)
       .After(expectations)
       .WillOnce(action)
       .WillRepeatedly(action)
       .RetiresOnSaturation();
/*
以上为所有选项,其中InSequence()和After()和WillOnce()可以调用任意次数;

*/
```

EXPECT_CALL声明一个调用期待，就是我们期待这个对象的这个方法按什么样的逻辑去执行。
	mock_object是我们mock的对象，上例中就是TestUser的一个对象。
	Method是mock对象中的mock方法，它的参数可以通过argument-matchers规则去匹配。
	With是多个参数的匹配方式指定。
	Times表示这个方法可以被执行多少次。如果超过这个次数，则按默认值返回了。
	InSequence用于指定函数执行的顺序。它是通过同一序列中声明期待的顺序确定的。
	After方法用于指定某个方法只能在另一个方法之后执行。
	WillOnce表示执行一次方法时，将执行其参数action的方法。一般我们使用Return方法，用于指定一次调用的输出。
	WillRepeatedly表示一直调用一个方法时，将执行其参数action的方法。需要注意下它和WillOnce的区别，WillOnce是一次，WillRepeatedly是一直。
	RetiresOnSaturation用于保证期待调用不会被相同的函数的期待所覆盖。