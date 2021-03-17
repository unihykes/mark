http://blog.sina.com.cn/s/blog_825ad93f0102yl59.html


find_path用于查找包含的头文件，其查找顺序为：
从CMAKE_INCLUDE_PATH中查找。
从系统默认头目录即/usr/include、/usr/local/inlucde中查找。

         其中如果从CMAKE_INCLUDE_PATH中查找的话，需要在~/.profile或者/etc/profile中设置（注意：设置后需重启系统），如下：
export CMAKE_INCLUDE_PATH=/home/dansir/work/mygit/
其中紫红色是你要设置的查找目录。只有从CMAKE_INCLUDE_PATH找不到的话，才从系统默认目录中查找。



find_library用于查找包含的库文件，其查找顺序为：
从CMAKE_LIBRARY_PATH中查找。
从系统默认库目录即/usr/lib、/usr/local/lib中查找。

         其中如果从CMAKE_LIBRARY_PATH中查找的话，需要在~/.profile或者/etc/profile中设置（注意：设置后需重启系统），如下：
export CMAKE_LIBRARY_PATH=/home/dansir/work/mygit
其中紫红色是你要设置的查找库目录。只有从CMAKE_LIBRARY_PATH找不到的话，才从系统默认库目录中查找。

