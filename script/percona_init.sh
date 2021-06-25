###
 # @Author: liuwenxin
 # @Date: 2021-03-19
###

source $( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )/build.sh

rm -rf $RUN_PATH/percona_22303/data/*
rm $RUN_PATH/percona_22303/percona_error.log

$BUILD_PATH/bin/mysqld --defaults-file=$RUN_PATH/percona_22303.conf --initialize --multi_master_log_plugin=OFF

echo [ERROR]
cat $RUN_PATH/percona_22303/percona_error.log | grep ERROR

echo [PASSWORD]
cat $RUN_PATH/percona_22303/percona_error.log | grep password