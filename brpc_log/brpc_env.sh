
BRPC_ENV_PATH=$(cd $(dirname ${BASH_SOURCE[0]}); pwd )

#echo $BRPC_ENV_PATH

#============= brpc
#export CPLUS_INCLUDE_PATH="$BRPC_ENV_PATH/brpc-install/include/:$CPLUS_INCLUDE_PATH"
#export C_INCLUDE_PATH="$BRPC_ENV_PATH/brpc-install/include/:$C_INCLUDE_PATH"
# export LIBRARY_PATH="$BRPC_ENV_PATH/brpc-install/lib64/:$LIBRARY_PATH"
# export LD_LIBRARY_PATH="$BRPC_ENV_PATH/brpc-install/lib:$LD_LIBRARY_PATH"
export BRPC_INCLUDE="$BRPC_ENV_PATH/brpc-install/include/"
export BRPC_LIB="$BRPC_ENV_PATH/brpc-install/lib64/"

#============= porotobuf
export PATH="$BRPC_ENV_PATH/pre-install/protobuf/protobuf-install/bin/:$PATH"
export CPLUS_INCLUDE_PATH="$BRPC_ENV_PATH/pre-install/protobuf/protobuf-install/include/:$CPLUS_INCLUDE_PATH"
export C_INCLUDE_PATH="$BRPC_ENV_PATH/pre-install/protobuf/protobuf-install/include/:$C_INCLUDE_PATH"
export LIBRARY_PATH="$BRPC_ENV_PATH/pre-install/protobuf/protobuf-install/lib/:$LIBRARY_PATH"
export LD_LIBRARY_PATH="$BRPC_ENV_PATH/pre-install/protobuf/protobuf-install/lib/:$LD_LIBRARY_PATH"
export PKG_CONFIG_PATH="$BRPC_ENV_PATH/pre-install/protobuf/protobuf-install/lib/pkgconfig/:$PKG_CONFIG_PATH"
export BRPC_PROTOBUF_INCLUDE="$BRPC_ENV_PATH/pre-install/protobuf/protobuf-install/include/"
export BRPC_PROTOBUF_LIB="$BRPC_ENV_PATH/pre-install/protobuf/protobuf-install/lib/"

export BRPC_PROTOBUF_LIB_DIR="$BRPC_ENV_PATH/pre-install/protobuf/protobuf-install/lib/"

#============= leveldb
export CPLUS_INCLUDE_PATH="$BRPC_ENV_PATH/pre-install/leveldb/leveldb-install/include/:$CPLUS_INCLUDE_PATH"
export C_INCLUDE_PATH="$BRPC_ENV_PATH/pre-install/leveldb/leveldb-install/include/:$C_INCLUDE_PATH"
export LIBRARY_PATH="$BRPC_ENV_PATH/pre-install/leveldb/leveldb-install/lib64/:$LIBRARY_PATH"
export LD_LIBRARY_PATH="$BRPC_ENV_PATH/pre-install/leveldb/leveldb-install/lib64/:$LD_LIBRARY_PATH"
export BRPC_LEVELDB_INCLUDE="$BRPC_ENV_PATH/pre-install/leveldb/leveldb-install/include/"
export BRPC_LEVELDB_LIB="$BRPC_ENV_PATH/pre-install/leveldb/leveldb-install/lib64/"


#============= gflags
export PATH="$BRPC_ENV_PATH/pre-install/gflags/gflags-install/bin/:$PATH"
export CPLUS_INCLUDE_PATH="$BRPC_ENV_PATH/pre-install/gflags/gflags-install/include/:$CPLUS_INCLUDE_PATH"
export C_INCLUDE_PATH="$BRPC_ENV_PATH/pre-install/gflags/gflags-install/include/:$C_INCLUDE_PATH"
export LIBRARY_PATH="$BRPC_ENV_PATH/pre-install/gflags/gflags-install/lib/:$LIBRARY_PATH"
export LD_LIBRARY_PATH="$BRPC_ENV_PATH/pre-install/gflags/gflags-install/lib/:$LD_LIBRARY_PATH"
export BRPC_GFLAGS_INCLUDE="$BRPC_ENV_PATH/pre-install/gflags/gflags-install/include/"
export BRPC_GFLAGS_LIB="$BRPC_ENV_PATH/pre-install/gflags/gflags-install/lib/"

export CMAKE_PREFIX_PATH="$BRPC_INCLUDE:$BRPC_PROTOBUF_INCLUDE:$BRPC_LEVELDB_INCLUDE:$BRPC_GFLAGS_INCLUDE:$BRPC_LIB:$BRPC_PROTOBUF_LIB:$BRPC_LEVELDB_LIB:$BRPC_GFLAGS_LIB:$CMAKE_PREFIX_PATH"
