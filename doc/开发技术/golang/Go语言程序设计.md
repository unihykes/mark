```go
数组切片Slice，我们可以认为数组切片是一种可动态增长的数组，数组切片与C++的vector非常类似；

下划线_可以作为占位符来忽略函数不关心的返回值；

Go语言引入3个关键字用于标准的错误处理：defer，panic，recover
defer语句的含义是不管程序是否出现异常，均在函数退出时自动执行相关代码；

type Encoder struct {
w io.Writer
e encodeState
err error

}
// NewEncoder returns a new encoder that writes to w.
func NewEncoder(w io.Writer) *Encoder {
return &Encoder{w: w}


}





















```