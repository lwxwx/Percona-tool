/***
 * 随机生成事务负载
 * OUTPUT
 * data_count 数据量
 * alph = 0.1 这个就暂且先定着
 * origin_partition 初始分区情况
 * sigle_trx 单分区事务
 * data_access_info 事务所访问的数据
 * 
 * 运行两次同样的负载 就可以看出分区算法的效果
 */

#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <map>
#include <set>
using namespace std; 

int data_count;
// int origin_partition_num; 
std::map<int, std::set<int>> data_access_info;//trx->rw_set
std::map<int, std::set<int>> single_trx;//single partition trx
std::map<int, std::set<int>> origin_partition;
std::map<int, int> origin_data_belong;

int main()
{ 
    //****** data_count = page count ***********
    srand((unsigned)time(NULL)); 
    data_count = (rand() % (100-20+1))+ 20;//[20,100]

    //******* origin_partition *******
    int origin_partition_num = data_count / 51 + 3;
    int tmp_data = 1;
    for(int p = 1; p <= origin_partition_num; p++)
    {
        for(; tmp_data <= data_count && tmp_data <= data_count / origin_partition_num * p; tmp_data++)
        {
            origin_partition[p].insert(tmp_data);
            origin_data_belong[tmp_data] = p;
        }
    }

    //********** trx *************
    int trx_num = (rand() % (50-10+1))+ 10;//[10,50]
    int trx_count = 1;
    //***** multi trx 40% ******
    for(; trx_count <= trx_num * 0.4; trx_count++)
    {
        int multi_cnt = (rand() % (origin_partition_num-2+1))+ 2;//访问到几个分区
        std::map<int, int> multi_part_cnt;//每个分区访问了几次
        while(multi_part_cnt.size() < multi_cnt)
        {
            int tmp_data = (rand() % (data_count-1+1))+ 1;
            if(multi_part_cnt[origin_data_belong[tmp_data]] < 1)
            {
                data_access_info[trx_count].insert(tmp_data);
                multi_part_cnt[origin_data_belong[tmp_data]]++;
            }
        }
    }
    //****** single trx ********
    for(; trx_count <= trx_num; trx_count++)
    {
        int single_part_id = (rand() % (origin_partition_num-1+1))+ 1;//选择访问哪个分区
        int access_data_num = ((rand() % origin_partition[single_part_id].size()) + 1) % 4;
        if(access_data_num == 0) access_data_num++;
        while(data_access_info[trx_count].size() < access_data_num)
        {
            auto it = origin_partition[single_part_id].begin();
            for(int i = 0; i < rand() % origin_partition[single_part_id].size(); i++)
            {
                it++;
            }
            int tmp_data = *it;
            data_access_info[trx_count].insert(tmp_data);
        }
        single_trx[single_part_id].insert(trx_count);
    }

    //***** OUTPUT ******
    std::cout << "data_count = " << data_count << "( 1 ~ " << data_count << ")\n";
    std::cout << "alph = 0.1 \n";
    std::cout << "origin_partition have " << origin_partition.size() <<":\n";
    for(auto p : origin_partition)
    {
        std::cout << "origin_partition[" << p.first << "] = {";
        for(auto page : p.second)
        {
            std::cout << page << ", ";
        }
        std::cout << "}\n";
    }
    std::cout << "single_trx :\n";
    for(auto p :single_trx)
    {
        std::cout << "single_trx[" << p.first << "] = {";
        for(auto t : p.second)
        {
            std::cout << t << ", ";
        }
        std::cout << "}\n";
    }
    std::cout << "data_access_info : \n";
    for(auto t : data_access_info)
    {
        std::cout << "data_access_info[" << t.first << "] = {";
        for(auto d : t.second)
        {
            std::cout << d << ", ";
        }
        std::cout << "}\n";
    }

    return 0;
}