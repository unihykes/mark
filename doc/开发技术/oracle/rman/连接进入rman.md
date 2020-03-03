连接进入rman
    本地只有一个实
        如果使用操作系统验证，则用 rman target /  
            目标数据库为ORACLE_SID
                

        如果没有使用操作系统验证: 则使用 rman target user/passwd
        也可以直接rman,再在里面用connect 用户名/密码
    本地有多少实例
        需要先设置环境变量
            ORACLE_SID

