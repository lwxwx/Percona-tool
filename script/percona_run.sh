###
 # @Author: liuwenxin
 # @Date: 2021-03-19
###

source $( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )/build.sh

$BUILD_PATH/scripts/mysqld_safe --defaults-file=$RUN_PATH/percona_22303.conf --user=root &#--multi_master_log_plugin=ON &