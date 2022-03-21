# 脚本文件说明
## 短事务测试脚本
update_benchmark.py & config.ini，输入参数在config.ini文件中改
```
python3 update_benchmark.py
pip install ...//安装模块
```
### 参数说明
- update_bench_load ： 1表示初始化加载数据，0表示运行测试
- data_size ：表示每张表的行数
> 以时间为单位测试还是以SQL运行数量测试这个二者选一
- time_s ： 表示运行时间
- sql_cnt ： 表示运行的SQL个数
- operation_id ： 表示操作的表的编号，是为了控制是否访问同一张表而设定的
- node_count ： 表示表的个数
- thread_num ： 线程数

## Percona构建
```
bash cmake.sh
make -j
```
## Percona初始化 & 运行
```
bash percona_init.sh
bash percona_run.sh
bash percona_conn.sh
```

## Percona关闭
```
bash percona_kill.sh
```