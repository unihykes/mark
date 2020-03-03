```
log4j用多了,最近在用go写东东,log package又封装的很简陋
随即打算山寨个log4go
大体架构好说(- -!山寨嘛,哈哈)
就是不太清楚怎么获取调用log.Debug的函数名和代码所在的行数
研究了一下,直接贴代码吧,呵呵

C代码  
	1. 
package main
	2. 
import "runtime"
	3. 
import "log"
	4. 
func main() {
	5. 
test()
	6. 
}
	7. 
func test() {
	8. 
test2()
	9. 
}
	10. 
func test2(){
	11. 
pc,file,line,ok := runtime.Caller(2)
	12. 
log.Println(pc)
	13. 
log.Println(file)
	14. 
log.Println(line)
	15. 
log.Println(ok)
	16. 
f := runtime.FuncForPC(pc)
	17. 
log.Println(f.Name())
	18. 
pc,file,line,ok = runtime.Caller(0)
	19. 
log.Println(pc)
	20. 
log.Println(file)
	21. 
log.Println(line)
	22. 
log.Println(ok)
	23. 
f = runtime.FuncForPC(pc)
	24. 
log.Println(f.Name())
	25. 
pc,file,line,ok = runtime.Caller(1)
	26. 
log.Println(pc)
	27. 
log.Println(file)
	28. 
log.Println(line)
	29. 
log.Println(ok)
	30. 
f = runtime.FuncForPC(pc)
	31. 
log.Println(f.Name())
	32. 
}




package main

import "runtime"
import "log"

func main() {
test()
}

func test() {
test2()
}

func test2(){
pc,file,line,ok := runtime.Caller(2)
log.Println(pc)
log.Println(file)
log.Println(line)
log.Println(ok)
f := runtime.FuncForPC(pc)
log.Println(f.Name())
pc,file,line,ok = runtime.Caller(0)
log.Println(pc)
log.Println(file)
log.Println(line)
log.Println(ok)
f = runtime.FuncForPC(pc)
log.Println(f.Name())
pc,file,line,ok = runtime.Caller(1)
log.Println(pc)
log.Println(file)
log.Println(line)
log.Println(ok)
f = runtime.FuncForPC(pc)
log.Println(f.Name())
}
output:
2011/12/30 22:55:17 8216
2011/12/30 22:55:17 /Users/jarcher/workspace/go/test/src/linetest.go
2011/12/30 22:55:17 7
2011/12/30 22:55:17 true
2011/12/30 22:55:17 main.main
2011/12/30 22:55:17 9065
2011/12/30 22:55:17 /Users/jarcher/workspace/go/test/src/linetest.go
2011/12/30 22:55:17 23
2011/12/30 22:55:17 true
2011/12/30 22:55:17 main.test2
2011/12/30 22:55:17 8241
2011/12/30 22:55:17 /Users/jarcher/workspace/go/test/src/linetest.go
2011/12/30 22:55:17 11
2011/12/30 22:55:17 true
2011/12/30 22:55:17 main.test
```