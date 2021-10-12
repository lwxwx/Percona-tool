# 脚本文件说明
## 短事务测试脚本
update_benchmark.py & config.ini，输入参数在config.ini文件中改
```
python3 update_benchmark.py
pip install ...//安装模块
```

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