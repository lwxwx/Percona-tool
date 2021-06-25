ROOT_PATH=$( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )/
echo ${ROOT_PATH}

PRE_INCLUDE=/root/part-mtc/build-percona/percona-env/brpc_env/pre-install
cmake ${ROOT_PATH} -DCMAKE_INCLUDE_PATH="$PRE_INCLUDE/gflags/gflags-install/include;$PRE_INCLUDE/leveldb/leveldb-install/include;$PRE_INCLUDE/protobuf/protobuf-install/include" -DCMAKE_LIBRARY_PATH="$PRE_INCLUDE/gflags/gflags-install/lib;$PRE_INCLUDE/leveldb/leveldb-install/lib64;$PRE_INCLUDE/protobuf/protobuf-install/lib" -DCMAKE_PREFIX_PATH="$PRE_INCLUDE/gflags/gflags-install/lib;$PRE_INCLUDE/leveldb/leveldb-install/lib64;$PRE_INCLUDE/protobuf/protobuf-install/lib"