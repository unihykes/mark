wstring getCurrentModulePath()
{
         wchar_t buf[ MAX_PATH ];
         memset (buf, 0, sizeof (buf));
         unsigned len = MAX_PATH ;

         if ((len = :: GetModuleFileName (HMODULE(husbkeyModuleHandler ), buf, len)) > 0) {
                 wstring result(buf );
                 string ::size_type pos = result.find_last_of (_T( "\\" ));
                 return result.substr (0, pos);
        }
         else {
                 return _T( "" );
        }
         return _T( "" );
}