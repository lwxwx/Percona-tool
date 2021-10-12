###
 # @Author: liuwenxin
 # @Date: 2021-03-19
###

source /home/liuwenxin/Percona/script/build.sh

$BUILD_PATH/bin/mysqld --defaults-file=/home/liuwenxin/mysql_out_50/percona_22303.conf --initialize --multi_master_log_plugin=OFF

cat /home/liuwenxin/mysql_out_50/percona_22303/percona_error.log | grep password