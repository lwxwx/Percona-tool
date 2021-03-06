###
 # @Author: liuwenxin
 # @Date: 2021-03-19
###

source $( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )/build.sh

echo "build_path = $BUILD_PATH"

if [ ! -d "$BUILD_PATH" ]
then
    mkdir $BUILD_PATH
else
    rm -rf $BUILD_PATH/*
    echo "$BUILD_PATH is ready !"
fi

cd $BUILD_PATH

# cmake ${PERCONA_PATH}/percona-server/ -DCMAKE_PREFIX_PATH=$BRPC_PROTOBUF_LIB:$BRPC_LEVELDB_LIB:$BRPC_GFLAGS_LIB:$BRPC_LIB -DCMAKE_INCLUDE_PATH=$BRPC_GFLAGS_INCLUDE:$BRPC_LEVELDB_INCLUDE:$BRPC_PROTOBUF_INCLUDE:$BRPC_INCLUDE -DCMAKE_LIBRARY_PATH=$BRPC_PROTOBUF_LIB:$BRPC_LEVELDB_LIB:$BRPC_GFLAGS_LIB:$BRPC_LIB -DDOWNLOAD_BOOST=1  -DWITH_BOOST=${PERCONA_PATH}/boost_1_70_0/ -DWITHOUT_TOKUDB=1  -DWITHOUT_ROCKSDB=1 -DENABLE_DOWNLOADS=1  -DWITH_MYSQLX=OFF  -DWITH_GROUP_REPLICATION=OFF -DCMAKE_INSTALL_PREFIX=${PERCONA_PATH}/build-install -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake ${PERCONA_PATH}/percona-server/ -DCMAKE_PREFIX_PATH=$BRPC_PROTOBUF_LIB:$BRPC_LIB -DCMAKE_INCLUDE_PATH=$BRPC_PROTOBUF_INCLUDE:$BRPC_INCLUDE -DCMAKE_LIBRARY_PATH=$BRPC_PROTOBUF_LIB:$BRPC_LIB -DDOWNLOAD_BOOST=1  -DWITH_BOOST=${PERCONA_PATH}/boost_1_70_0/ -DWITHOUT_TOKUDB=1  -DWITHOUT_ROCKSDB=1 -DENABLE_DOWNLOADS=1  -DWITH_MYSQLX=OFF  -DWITH_GROUP_REPLICATION=OFF -DCMAKE_INSTALL_PREFIX=${PERCONA_PATH}/build-install -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# cmake 

