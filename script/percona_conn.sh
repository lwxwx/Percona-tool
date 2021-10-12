###
 # @Author: liuwenxin
 # @Date: 2021-03-19
###

source /home/liuwenxin/Percona/script/build.sh

cat /home/liuwenxin/mysql_out_50/percona_22303/percona_error.log | grep password

echo "ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY '123';"

$BUILD_PATH/bin/mysql -h127.0.0.1 -uroot -P22303 -p