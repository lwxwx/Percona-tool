###
 # @Author: liuwenxin
 # @Date: 2021-03-19
###

PWD_PATH=$(pwd)

ROOT_PATH=$( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )/..

BUILD_PATH=$ROOT_PATH/build
echo build_path = $BUILD_PATH

RUN_PATH=/root/part-mtc/run-percona/mysql_out_50
echo run_path = $RUN_PATH