cmake_minimum_required(VERSION 3.16)
project(distributed_cluster_chat_server)

# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
set(CMAKE_CXX_STANDARD 11)

#配置头文件和库文件的搜索路径
include_directories(/usr/include)
link_directories(/usr/local/lib)

#设置需要编译的源文件列表
#set (SRC_LIST main.cpp)
# 把. 指定路径下的所有源文件放入变量名SRC_LIST里面
# aux_source_directory(. SRC_LIST)

#设置可执行文件最终存储的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#生成可执行文件
add_executable(distributed_cluster_chat_server main.cpp
        )

add_executable(test_muduo_server test_muduo_server.cpp)
# 目标程序需要连接的库文件
target_link_libraries(distributed_cluster_chat_server muduo_net muduo_base pthread)
target_link_libraries(test_muduo_server muduo_net muduo_base pthread)