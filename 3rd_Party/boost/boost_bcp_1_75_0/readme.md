

## 1.75.0
bcp裁剪
./dist/bin/bcp 
unordered_set.hpp
unordered_map.hpp
smart_ptr.hpp
atomic.hpp
asio.hpp
thread.hpp
filesystem
system


```shell
# 部分模块
./dist/bin/bcp atomic               /unihykes/depspkgs/boost_bcp

# 全部模块
./dist/bin/bcp atomic chrono container context contract coroutine date_time exception fiber filesystem graph graph_parallel headers iostreams json  locale log  math  mpi  nowide program_options  python random  regex serialization  stacktrace system test thread timer type_erasure wave   /unihykes/depspkgs/boost_bcp

./b2 --show-libraries
The following libraries require building:
    - atomic
    - chrono
    - container
    - context
    - contract
    - coroutine
    - date_time
    - exception
    - fiber
    - filesystem
    - graph
    - graph_parallel
    - headers
    - iostreams
    - json
    - locale
    - log
    - math
    - mpi
    - nowide
    - program_options
    - python
    - random
    - regex
    - serialization
    - stacktrace
    - system
    - test
    - thread
    - timer
    - type_erasure
    - wave
```