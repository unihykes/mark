         _ULARGE_INTEGER journalVolumeTotalSpace;
         if(::GetDiskFreeSpaceEx (_journalVolume.getCStr (), NULL, &journalVolumeTotalSpace, NULL )) {
                 if (journalVolumeTotalSpace .QuadPart < (ULONGLONG)(_volumeLimitSize << 30 )) {
                         // set journal volume limit size equal to the eighty percent of journal volume total space.
                         _volumeLimitSize = journalVolumeTotalSpace.QuadPart / 1342177280;
                         if (_volumeLimitSize < 1) {
                                 _volumeLimitSize = 1;
                        }
                         String warnMsg;
                         warnMsg .format (LOAD_STRING (_T ("IDS_SET_JOURNAL_LIMIT_SIZE_WARNING")).getCStr (), _volumeLimitSize );
                         ncCoreWarnException warnExcp (__FILE__ , __LINE__, warnMsg );
                         _listener -> OnWarning (warnExcp);
                }
        }
         else {
                 String errMsg;
                 errMsg .format (LOAD_STRING (_T( "IDS_GET_JOURNAL_FREE_SPACE_FAILED" )).getCStr (), LOAD_SYS_STRING (GetLastError ()));
                 THROW_DISASTER_BACKUP_ERROR (errMsg, ERROR_CALL_WINDOWS_SYSTEM_API_ERROR );
        }