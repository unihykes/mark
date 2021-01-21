http://baike.baidu.com/view/652360.htm

http://www.baidu.com/link?url=gVRUazTVCCDoAdZzfk3LCqFyil_D09kCEQaOkO1nWq4oq8agZa960pAniweuLefgxfsxyZWL5GBwCc8HGLCPo5CcUTl0nStMTeOcFs7WUOG&wd=GlobalMemoryStatusEx&issp=1&f=8&ie=utf-8&tn=baiduhome_pg&inputT=1220



         /// 获取当前系统可用内存空间
         MEMORYSTATUSEX mem;
         mem.dwLength = sizeof(MEMORYSTATUSEX );
         if(::GlobalMemoryStatusEx (& mem)) {
                 /// CDP 驱动内存配置超出当前系统内存，需要修改实际配置
                 /// a<< 30 等于 a×××= a (GB)
                 if (mem .ullTotalPhys < (ULONGLONG)(_memoryLimitSize << 30)) {
                         // set memory limit size equal to the eighty percent of system total physical memory.
                         /// 设置内存限制大小等于系统总物理内存的百分之八十
                         /// 1342177280 = 1280*1024*1024 = 1280MB ，
                         /// 1024/1280 = 80%
                         _memoryLimitSize = mem. ullTotalPhys / 1342177280;
                         if (_memoryLimitSize < 1) {
                                 _memoryLimitSize = 1;
                        }
                         String warnMsg;
                         warnMsg .format (LOAD_STRING (_T ("IDS_SET_MEMORY_LIMIT_SIZE_WARNING")).getCStr (), _memoryLimitSize );
                         ncCoreWarnException warnExcp (__FILE__ , __LINE__, warnMsg );
                         _listener -> OnWarning (warnExcp);
                }
        }
         else {
                 String errMsg;
                 errMsg .format (LOAD_STRING (_T( "IDS_GET_SYSTEM_MEMORY_FAILED" )).getCStr (), LOAD_SYS_STRING (GetLastError ()));
                 THROW_DISASTER_BACKUP_ERROR (errMsg, ERROR_CALL_WINDOWS_SYSTEM_API_ERROR );
        }











