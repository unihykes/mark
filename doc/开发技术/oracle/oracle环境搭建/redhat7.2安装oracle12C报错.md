参考资料:http://www.cnblogs.com/xi52qian/p/4187019.htmlhttp://blog.csdn.net/zhongyifly/article/details/42610399总体安装流程参考:linux下安装oracle12C如果发生下图报错:log文件中:INFO: /usr/bin/ld: /usr/oracle/product/lib//libnls12.a(lxhlang.o): undefined reference to symbol '__tls_get_addr@@GLIBC_2.3'/usr/bin/ld: note: '__tls_get_addr@@GLIBC_2.3' is defined in DSO /lib64/ld-linux-x86-64.so.2 so try adding it to the linker command line/lib64/ld-linux-x86-64.so.2: could not read symbols: Invalid operationINFO: collect2: error: ld returned 1 exit status请参考帖子:http://bbs.csdn.net/topics/390743335需要删除 {ORACLE_HOME}/lib/stubs 这个目录 (对于我的设置,就是 /usr/oracle/product/12.1.0.1.0/lib/stubscd /usr/oracle/product/12.1.0.1.0/librm -rf stubs)出现"/usr/bin/ld: cannot find -lz"错误，需要安装zlib-dev这个包，或者使用zlib-1.2.11.tar.gz


出现如下错误:

修改 rdbms/lib/ins_rdbms.mk 的 883行 和 901 行
$(PLSHPROF) : $(ALWAYS) $(PLSHPROF_DEPS)
        $(SILENT)$(ECHO)
        $(SILENT)$(ECHO) " - Linking hierarchical profiler utility (plshprof)"
        $(RMF) $@
        $(PLSHPROF_LINKLINE) -lons
....
$(RMAN) : $(ALWAYS) $(RMAN_DEPS)
        $(SILENT)$(ECHO)
        $(SILENT)$(ECHO) " - Linking recovery manager (rman)"
        $(RMF) $@
        $(RMAN_LINKLINE) -lons




出现如下错误:

ins_rdbms.mk
houzi.o: undefined reference to symbol 'ztcsh'
libnnz12.so: could not read symbols: Invalid operation
修改 ins_rdbms.mk 的 1067行

1063 $(TG4PWD) : $(ALWAYS) $(TG4PWD_DEPS)
1064         $(SILENT)$(ECHO)
1065         $(SILENT)$(ECHO) " - Linking $(TG4DG4)pwd utility"
1066         $(RMF) $@
1067         $(TG4PWD_LINKLINE) -lnnz12