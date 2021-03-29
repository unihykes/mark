PROJECT(3rd_Party)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)


ADD_SUBDIRECTORY(gtest)

execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/benchmark/build.sh)

execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/gflags/build.sh
                COMMAND sh $ENV{MK_PATH}/3rd_Party/leveldb/build.sh
                COMMAND sh $ENV{MK_PATH}/3rd_Party/protobuf/build.sh)
                
#由于与其他库有依赖的顺序问题,brpc需要手动编译
#execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/brpc/build.sh)