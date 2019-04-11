

一般在C或C++中(VC当然是C++的一种)，DLL的模块入口点有个默认函数，是_DllMainCRTStartup()，它的原形与 DllMain()一样，链接器在链接的时候就是以它作为模块的入口函数，那样它就可以进行一些模块全局变量等的初始化操作，当然用户也可对模块入口地址 进行自行设定，不过不建议这么做！


当链接器在链接时，它会自动查找当前DLL模块工程中的各个.obj文件，如果找到有DllMain()函数，这时就会 在_DllMainCRTStartup()函数中调用用户的入口点函数，也就是DllMain()函数；如果找不到，就会调用到CRT的默认DllMain()，这个DllMain()函数中只有很少的一些代码，那就是在传递DLL_PROCESS_ATTACH通知中调用 DisableThreadLibraryCalls()函数，以告诉系统以后有线程的创建或撤消时不必调用此DLL的入口点通知。
所以说在DLL模块中没有DllMain()用户自定义的入口点模块是可以的。
