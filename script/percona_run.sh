###
 # @Author: liuwenxin
 # @Date: 2021-03-19
###

source /home/liuwenxin/Percona/script/build.sh

$BUILD_PATH/scripts/mysqld_safe --defaults-file=/home/liuwenxin/mysql_out_50/percona_22303.conf --multi_master_log_plugin=ON &