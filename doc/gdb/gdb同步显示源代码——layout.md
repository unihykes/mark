
	显示结构体数据
	set print pretty on

	GDB同步显示源代码——layout
	GDB调试的时候，很多人会忽略一个强大的命令layout。
	快捷键ctrl+x+a(有顺序，先ctrl+x再按a)

	1. 显示源代码窗口

	(gdb) layout src  
	2. 显示寄存器窗口
	(gdb) layout regs
	3. 显示汇编代码窗口

	(gdb) layout asm
	4. 显示源代码和汇编代码

	(gdb) layout split 

	5. 显示窗口的大小
	info win    

	6. 切换到下一个布局模式

	layout next 

	7. 切换到上一个布局模式

	layout prev 

	8. 切换当前窗口
	focus cmd/src/asm/regs/next/prev 
	9. 刷新所有窗口

	refresh     
	10. 更新源代码窗口和当前执行点

	update      
	11. 调整name窗口的高度,要执行程序后再执行该命令

	winheight src +/- line 
	winheight src + 10

