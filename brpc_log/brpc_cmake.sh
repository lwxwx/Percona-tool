BRPC_SOURCE_PATH=$(cd $(dirname ${BASH_SOURCE[0]}); pwd )/incubator-brpc
cmake $BRPC_SOURCE_PATH -DCMAKE_INSTALL_PREFIX=$BRPC_SOURCE_PATH/../brpc-install -DCMAKE_INCLUDE_PATH=$BRPC_PROTOBUF_INCLUDE;$BRPC_LEVELDB_INCLUDE;$BRPC_GFLAGS_INCLUDE -DCMAKE_LIBRARY_PATH=$BRPC_PROTOBUF_LIB;$BRPC_LEVELDB_LIB;$BRPC_GFLAGS_LIB -DCMAKE_PREFIX_PATH=$BRPC_PROTOBUF_LIB;$BRPC_LEVELDB_LIB;$BRPC_GFLAGS_LIB

cmake .. -DCMAKE_INCLUDE_PATH="/root/dev_env/brpc_env/gflags-install/include;/root/dev_env/brpc_env/leveldb-install/include;/root/dev_env/brpc_env/protobuf-install/include" \
-DCMAKE_LIBRARY_PATH="/root/dev_env/brpc_env/gflags-install/lib;/root/dev_env/brpc_env/leveldb-install/lib64;/root/dev_env/brpc_env/protobuf-install/lib" \
-DCMAKE_INSTALL_PREFIX=/root/dev_env/brpc_env/brpc-install\
-DBUILD_SHARED_LIBS=ON
