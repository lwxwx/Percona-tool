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
    echo "$BUILD_PATH is ready !"
fi

cd $BUILD_PATH

cmake ${ROOT_PATH}/percona-server/  -DDOWNLOAD_BOOST=1  -DWITH_BOOST=${ROOT_PATH}/boost_1_70_0/ -DWITHOUT_TOKUDB=1  -DWITHOUT_ROCKSDB=1 -DENABLE_DOWNLOADS=1  -DWITH_MYSQLX=OFF  -DWITH_GROUP_REPLICATION=OFF -DCMAKE_INSTALL_PREFIX=${BUILD_DIR}/../build-install -DCMAKE_EXPORT_COMPILE_COMMANDS=ON



# cmake 

