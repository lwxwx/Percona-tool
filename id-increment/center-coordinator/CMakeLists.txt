cmake_minimum_required(VERSION 2.8.10)

project("id-increment")

# list(APPEND CMAKE_INCLUDE_PATH $ENV{BRPC_LEVELDB_INCLUDE})
# list(APPEND CMAKE_INCLUDE_PATH $ENV{BRPC_PROTOBUF_INCLUDE})
# list(APPEND CMAKE_INCLUDE_PATH $ENV{BRPC_GFLAGS_INCLUDE})
# list(APPEND CMAKE_INCLUDE_PATH $ENV{BRPC_SSL_INCLUDE})
# list(APPEND CMAKE_INCLUDE_PATH $ENV{BRPC_INCLUDE})

# list(APPEND CMAKE_LIBRARY_PATH $ENV{BRPC_LEVELDB_LIB})
# list(APPEND CMAKE_LIBRARY_PATH $ENV{BRPC_PROTOBUF_LIB})
# list(APPEND CMAKE_LIBRARY_PATH $ENV{BRPC_GFLAGS_LIB})
# list(APPEND CMAKE_LIBRARY_PATH $ENV{BRPC_SSL_LIB})
# list(APPEND CMAKE_LIBRARY_PATH $ENV{BRPC_LIB})

include_directories($ENV{BRPC_LEVELDB_INCLUDE})
include_directories($ENV{BRPC_PROTOBUF_INCLUDE})
include_directories($ENV{BRPC_GFLAGS_INCLUDE})
include_directories($ENV{BRPC_SSL_INCLUDE})
include_directories($ENV{BRPC_INCLUDE})

# SET(BRPC_STATIC_DEP_LIB
#     ${DEP_STATIC_LIB_DIR}/libprotobuf.a
#     ${DEP_STATIC_LIB_DIR}/libprotoc.a
#     ${DEP_STATIC_LIB_DIR}/libleveldb.a
#     ${DEP_STATIC_LIB_DIR}/libgflags.a
#     #${DEP_STATIC_LIB_DIR}/libssl.a
#     #${DEP_STATIC_LIB_DIR}/libcrypto.a
#     libssl.so
#     libcrypto.so
#     snappy
# )

SET(BRPC_DYNAMIC_DEP_LIB
    $ENV{BRPC_PROTOBUF_LIB}/libprotobuf.so
    $ENV{BRPC_PROTOBUF_LIB}/libprotoc.so
   # ${DEP_STATIC_LIB_DIR}/libprotobuf.a
    $ENV{BRPC_LEVELDB_LIB}/libleveldb.so
    $ENV{BRPC_GFLAGS_LIB}/libgflags.so.2.2
    libssl.so
    libcrypto.so
)

SET(BRPC_DYNAMIC_LIB
    $ENV{BRPC_LIB}/libbrpc.so
)


# SET(BRPC_STATIC_LIB
#     ${DEP_STATIC_LIB_DIR}/libbrpc.a
# )

set(BRPC_LINK_LIB
    ${BRPC_DYNAMIC_LIB}
    ${BRPC_DYNAMIC_DEP_LIB}
)


# find_package(Protobuf 3 REQUIRED)
# SET(OUTPUT_DIR ./)
# SET(PROTO_META_BASE_DIR ${MESSAGE_DIR})
# #设置protoc的搜索路径
# LIST(APPEND PROTO_FLAGS -I${CMAKE_SOURCE_DIR}/)
# #获取需要编译的proto文件
# file(GLOB_RECURSE MSG_PROTOS ${CMAKE_SOURCE_DIR}/*.proto)
# set(MESSAGE_SRC "")
# set(MESSAGE_HDRS "")
# foreach(msg ${MSG_PROTOS})
#         get_filename_component(FIL_WE ${msg} NAME_WE)

#         list(APPEND MESSAGE_SRC "${PROJECT_BINARY_DIR}/message/${FIL_WE}.pb.cc")
#         list(APPEND MESSAGE_HDRS "${PROJECT_BINARY_DIR}/message/${FIL_WE}.pb.h")
        
#         # 生成源码
#         execute_process(
#             COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO_FLAGS} --cpp_out=${DST_DIR} ${msg}
#             )
# endforeach()
# # 使用自定义命令
# add_custom_command(
#     OUTPUT "id.pb.cc"
#             "id.pb.h"
#     COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
#           ARGS --cpp_out  ${PROTO_META_BASE_DIR}
#             -I ./
#             ${msg}
#           DEPENDS ${msg}
#           COMMENT "Running C++ protocol buffer compiler on ${msg}"
#           VERBATIM
#         )

find_package(Protobuf REQUIRED)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS id.proto)
# execute_process(COMMAND bash "-c" "rm *.cc *.h && protoc ./id.proto --cpp_out=./"
# 	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
# 	)

add_executable(client client.cpp ${PROTO_SRCS} ${PROTO_HDRS})
add_executable(server server.cpp ${PROTO_SRCS} ${PROTO_HDRS})
# add_executable(client client.cpp)
# add_executable(server server.cpp)

target_link_libraries(client  ${BRPC_LINK_LIB})
target_link_libraries(server  ${BRPC_LINK_LIB})
