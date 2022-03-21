import sys
from configparser import ConfigParser
import pymysql
import random
import string
import time
import traceback
import datetime
import numpy
import threading
import os
# from DBUtils.PooledDB import PooledDB

# config_path = "./config.ini"
path = os.path.dirname(os.path.abspath(__file__))
cfg = ConfigParser()
cfg.read(path+"/config.ini")

update_bench_load = int(cfg.get('update_benchmark', 'update_bench_load'))
data_size=int(cfg.get('update_benchmark', 'data_size'))
time_s=float(cfg.get('update_benchmark', 'time_s'))
thread_num=int(cfg.get('update_benchmark', 'thread_num'))
sql_cnt=int(cfg.get('update_benchmark', 'sql_cnt'))

port = int(cfg.get('build_env', 'port'))
user = cfg.get('build_env', 'usr')
password = cfg.get('build_env', 'pass')

# conflict_row_rate=cfg.get('update_benchmark', 'conflict_row_rate')
# conflict_page_rate=cfg.get('update_benchmark', 'conflict_page_rate')

operation_id=int(cfg.get('update_benchmark', 'operation_id'))
node_count=int(cfg.get('update_benchmark', 'node_count'))

my_thread_type=numpy.dtype({'names':['count','time','trx_time'],'formats':['i','f','f']})
list_thread_item=numpy.array([(0.,0.,0.)]*thread_num,dtype=my_thread_type)


def update_run(thread_id):
    print("thread ",thread_id,"run")
    cnt=0
    trx_run_time=0.0
    trx_success_time=0.0
    thread_begin=datetime.datetime.now()
    conn = pymysql.connect(host='127.0.0.1', port=port, user=user, passwd=password)
    cursor = conn.cursor()
    cursor.execute('use test')
    while((datetime.datetime.now()-thread_begin).total_seconds()<time_s):     
    # for kk in range(0,sql_cnt):
        try:
            # conn = POOL.connection()
            # cursor = conn.cursor(pymysql.cursors.DictCursor)
            sql_for_update="update test"+str(operation_id)+" set val='"+str(thread_id+cnt)+"' where ID="+str(thread_id+70)+";"
            # sql_for_update="update test"+str(thread_id*5)+" set val='"+str(thread_id+cnt)+"' where ID="+str(thread_id+1)+";"
            # print(sql_for_update)
            # sql_for_update="update test6 set val='"+str(thread_id+cnt)+"' where ID=8;"#+str(thread_id+1)+";"
            # time.sleep(random.randint(5,30)/1000000.0)
            trx_begin=datetime.datetime.now()
            result_update = cursor.execute(sql_for_update)
        except Exception as e:
            print(e)
            conn.rollback()
        else:
            conn.commit()
        trx_end=datetime.datetime.now()
        trx_run_time=trx_run_time+(trx_end-trx_begin).total_seconds()
        if(result_update==1):
            cnt=cnt+1
    if cursor:   
        cursor.close()  
    if conn:
        conn.close()

    list_thread_item[thread_id]['time']=(datetime.datetime.now()-thread_begin).total_seconds()
    list_thread_item[thread_id]['count']=cnt
    list_thread_item[thread_id]['trx_time']=trx_run_time


if(update_bench_load == 1):
    try:
        print("create database test...")
        conn = pymysql.connect(host='127.0.0.1', port=port, user=user, passwd=password)
        cur = conn.cursor()
        sql = 'create database test;'
        cur.execute(sql)
        sql = 'use test'
        cur.execute(sql)
        for j in range(0,node_count+1):
            sql = 'create table test'+str(j)+' (ID INT PRIMARY KEY,val char(96));'
            cur.execute(sql)

        for j in range(0,node_count+1):
            for i in range(1, data_size+1):
                ran_str1 = ''.join(random.sample(string.ascii_letters, 50))
                ran_str2 = ''.join(random.sample(string.ascii_letters, 46))
                ran_str = ran_str1+ran_str2
                sql = 'insert into test'+str(j)+' VALUES (' + str(i) + ",'" + ran_str + "');"
                try:
                    cur.execute(sql)
                    conn.commit()
                except:
                    conn.rollback()
        print('create database success!')
    except:
        info = sys.exc_info()
        print( info[0], ":", info[1]) 
    cur.close()
    conn.close()
else:
    try:  
        print("[",time.strftime("%H:%M:%S", time.localtime()),"]start test",time_s,"sec...")
        threads =[]
        for i in range (0,thread_num):
            thread=threading.Thread(target=update_run,kwargs={"thread_id":i})
            thread.start()
            threads.append(thread)
        for t in threads:
            t.join()
    except:
        print ("Error: unable to start thread")

    sum_trx_time=0.0
    sum_trx_count=0
    for i in range (0,thread_num):
        print("trx_count = ", list_thread_item[i]['count'],", thread_time = ",list_thread_item[i]['time'],", trx_time = ",list_thread_item[i]['trx_time'])
        # if(list_thread_item[i]['time']<time_s):
        #     print ("thread ",i," exit early at ",list_thread_item[i]['time'])
        sum_trx_time=(sum_trx_time+list_thread_item[i]['trx_time'])
        sum_trx_count=sum_trx_count+list_thread_item[i]['count']
    sum_trx_time=sum_trx_time/thread_num
    print("transactions = ",sum_trx_count)
    print ("tps = ",sum_trx_count/sum_trx_time,"transactions/sec")
    print("avg trx time = ",sum_trx_time)
