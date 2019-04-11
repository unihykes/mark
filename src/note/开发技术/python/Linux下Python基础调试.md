    方法1：import pdb;pdb.set_trace();

    方法2：
    当手边没有IDE,面对着python调试犯愁时，你就可以参考下本文；（pdb 命令调试）
    参考：http://docs.python.org/library/pdb.html 和 (pdb)help
    首先你选择运行的 py
    python -m pdb myscript.py
    (Pdb) 会自动停在第一行，等待调试,这时你可以看看 帮助

    (Pdb) h
    说明下这几个关键 命令
    >断点设置
    (Pdb)b 10 #断点设置在本py的第10行
    或(Pdb)b ots.py:20 #断点设置到 ots.py第20行
    删除断点（Pdb）b #查看断点编号
    (Pdb)cl 2 #删除第2个断点
    >运行
    (Pdb)n #单步运行
    (Pdb)s #细点运行 也就是会下到，方法
    (Pdb)c #跳到下个断点
    >查看
    (Pdb)p param #查看当前 变量值
    (Pdb)l #查看运行到某处代码
    (Pdb)a #查看全部栈内变量
    >如果是在 命令行里的调试为：
    import pdb
    def tt():
    pdb.set_trace()
    for i in range(1, 5):
    print i
    >>> tt()
    这里支持 n p c 而已
    > (3)tt()
    (Pdb) n
