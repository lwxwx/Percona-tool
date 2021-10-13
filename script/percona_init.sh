###
 # @Author: liuwenxin
 # @Date: 2021-03-19
###

rm -rf ${HOME}/mysql_out_50/percona_22303/data/*
rm ${HOME}/mysql_out_50/percona_22303/percona_error.log

source $( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )/build.sh

$BUILD_PATH/bin/mysqld --defaults-file=/home/liuwenxin/mysql_out_50/percona_22303.conf --initialize --multi_master_log_plugin=OFF

cat /home/liuwenxin/mysql_out_50/percona_22303/percona_error.log | grep password