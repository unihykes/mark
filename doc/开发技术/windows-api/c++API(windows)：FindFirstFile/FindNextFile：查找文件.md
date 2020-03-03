http://baike.baidu.com/link?url=lbhaLSViwYDcdOT6He8FJAsVT3mgNhG-1YcYbd_p29ihpg7eClBqw3Jo3URlHHAuEJR_Ju9tBWVni0DZgVt_S_


unsigned int
ncDisasterBackupExec ::getDriverCacheFileCount (void )
{
         NC_DISASTER_BACKUP_TRACE (_T( "ncDisasterBackupExec::getDriverCacheFileCount ()----->Begin"));
         unsigned int cacheFileCount = 0;
         WIN32_FIND_DATA findFileData;
         // driver cache file format like "c:\\0_*.log".
         String cacheFileName;
         cacheFileName .format(_T ("%s\\%s_*.log"), _journalVolume .getCStr(), Int ::toString(_cdpId ).getCStr());
        
         /// 查找所有名称为"%s\\%s_*.log"的文件，并返回数量
         void* handle = :: FindFirstFile (cacheFileName.getCStr (), & findFileData );
         if (handle != INVALID_HANDLE_VALUE) {
                 BOOL findFileResult = true;
                 while (findFileResult) {
                         findFileResult = :: FindNextFile (handle, &findFileData);
                        ++ cacheFileCount ;
                }

                :: FindClose (handle);
        }
         NC_DISASTER_BACKUP_TRACE (_T( "ncDisasterBackupExec::getDriverCacheFileCount ()----->End"));
         return cacheFileCount;
}


