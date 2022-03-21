/***
 * data_access_info ： 数据访问信息，<trx, rw_Set>
 * single_trx : 仅访问单分区的事务，实时记录的
 * 
 * a~z(1~25) ： 表示26个page
 * 设置一个最开始的分区 : origin_part<part_id, data>，将这26个页面放到不同的分区，不如就{a~g}{h~l}{m~t}{u~z} 等分一下
 * data_access_info 和 single_trx 由负载生成记录
 * origin-partition.size() = 4 {P0,P1,P2,P3,P4}
 */
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <math.h>
#include <random>
#include <stdlib.h>
#include <time.h> 

std::vector<int> parent;
std::vector<int> rank;

// INPUT
std::map<int, std::set<int>> data_access_info;//trx->rw_set
std::map<int, std::set<int>> single_trx;//single partition trx
std::map<int, std::set<int>> origin_partition;//origin partition number
int data_count;//1~25
double alph;//跨分区事务的比例

// OUTPUT
std::map<int, std::set<int>> new_partition;//新的分区中每个分区管理的数据
std::map<int, int> data_belong;//每个数据属于哪个分区
int new_partition_cnt = 0;

int  DEBUG_CODE = 0;
std::vector<std::vector<int>> count;
int multi_part_trx_sum;

void init_disjSet(int max_size)
{
    parent.resize(max_size);
    rank.resize(max_size, 0);
    for (int i = 0; i < max_size; ++i)
        parent[i] = i;
}
int find(int x)
{
    return x == parent[x] ? x : (parent[x] = find(parent[x]));
}
void to_union(int x1, int x2)
{
    int f1 = find(x1);
    int f2 = find(x2);
    if (rank[f1] > rank[f2])
        parent[f2] = f1;
    else
    {
        parent[f1] = f2;
        if (rank[f1] == rank[f2])
            ++rank[f2];
    }
}
bool is_same(int e1, int e2)
{
    return find(e1) == find(e2);
}

void print_new_part_status()
{
    for(auto p : new_partition)
    {
        std::cout << "P-" << p.first << " : ";
        for(auto data : p.second)
        {
            std::cout << data << ", ";
        }
        std::cout << std::endl;
    }
}

void splitPart()
{
    if(DEBUG_CODE != 0)
    {
        std::cout << "*********** IN splitPart() ***********\n";
    }
    //************** STEP 1 **********************
    for(auto p : origin_partition)
    {
        for(auto trx : single_trx[p.first])
        {
            // std::set<int> access_part;
            int access_part_cnt  = 0;
            for(auto data : data_access_info[trx])
            {
                // access_part.insert(find(data));
                if(data_belong.find(data) != data_belong.end())
                    access_part_cnt ++;
            }
            if(access_part_cnt == 0)
            {
                new_partition_cnt++;
                auto data = data_access_info[trx].begin();
                int root = *data;
                new_partition[new_partition_cnt].insert(root);
                data_belong[root] = new_partition_cnt;
                while(++data != data_access_info[trx].end())
                {
                    to_union(root, *data);
                    new_partition[new_partition_cnt].insert(*data);
                    data_belong[*data] = new_partition_cnt;
                }
            }
        }
    }
    //************** STEP 2 **********************
    for(auto p :origin_partition)
    {
        for(auto trx : single_trx[p.first])
        {
            std::set<int> access_part_cnt;
            for(auto data : data_access_info[trx])
            {
                if(data_belong.find(data) != data_belong.end())
                    access_part_cnt.insert(data_belong[data]);
            }

            if(DEBUG_CODE != 0)
            {
                std::cout << "trx-" << trx << " access " << access_part_cnt.size() << " partition \n";
            }

            if(access_part_cnt.size() <= 1)
            {
                auto data = data_access_info[trx].begin();
                int root = *data;
                if(access_part_cnt.size() == 0)
                {
                    new_partition[++new_partition_cnt].insert(*data);
                    data_belong[*data] = new_partition_cnt;
                }
                while(++data != data_access_info[trx].end())
                {
                    if(DEBUG_CODE != 0)
                    {
                        std::cout << "data-" << *data << ";";
                    }
                    if(data_belong[*data] != data_belong[root])
                    {
                        if(DEBUG_CODE != 0)
                        {
                            std::cout << "insert to part -" << data_belong[root];
                        }
                        to_union(*data, root);
                        data_belong[*data] = data_belong[root];
                        new_partition[data_belong[root]].insert(*data);
                    }
                }
                if(DEBUG_CODE != 0)
                {
                    std::cout << "\n";
                }
            }
        }
    }
    //OUTPUT: data_belong & new_partition
}

void caculate_count()
{
    count.resize(data_count, std::vector<int>(data_count, 0));
    multi_part_trx_sum = 0;
    for(auto trx :data_access_info)
    {
        std::set<int> all_access_part;
        for(auto data : trx.second)
        {
            all_access_part.insert(data_belong[data]);
        }
        if(all_access_part.size() > 1)
        {
            if(DEBUG_CODE != 0)
            {
                std::cout << "\ntrx-" << trx.first << " is mulit_trx access ";
            }
            multi_part_trx_sum++;
            for(auto i = all_access_part.begin(); i != all_access_part.end(); i++)
            {
                if(DEBUG_CODE != 0) std::cout << "part-" << *i << " & ";
                std::set<int>::iterator j = i;
                j++;
                for(; j != all_access_part.end(); j++)
                {
                    // if(i != j)
                        count[std::min(*i,*j)][std::max(*i,*j)]++;
                }
            }
        }
    }
}

void mergePart()
{
    if(DEBUG_CODE != 0)
    {
        std::cout << "*********** IN mergePart() ***********\n";
    }
    //allocate every data to one partition
    // int part_have_num = 0;
    // for(auto p : new_partition)
    // {
    //     part_have_num += p.second.size();
    // }


    //********* get all partition ******************
    for(int data = 1; data < data_count; data++)
    {
        if(data_belong.find(data) == data_belong.end())
        {
            data_belong[data] = ++new_partition_cnt;
            new_partition[new_partition_cnt].insert(data);
        }
    }

    if(DEBUG_CODE != 0)
    {
        std::cout << "************ begin merge part status ***********\n";
        print_new_part_status();
    }

    //************** caculate count vector ***********************
    caculate_count();

    if(DEBUG_CODE != 0)
    {
        std::cout << "\n[count vector] \n";
        for(int i = 0; i < count.size(); i++)
            for(int j = 0; j < count[i].size(); j++)
                if(count[i][j])
                    std::cout << "[" << i << "," << j << "] = " << count[i][j] << std::endl;
        std::cout << "multi_part_trx number = " << multi_part_trx_sum << std::endl << "**************************\n";
    }

    
    //******************** merge *************
    int cnt = 0;
    while(multi_part_trx_sum > ceil(alph * data_access_info.size()))
    {cnt++;
        if(DEBUG_CODE != 0)
        {
            std::cout << "[count vector] in while \n";
            for(int i = 0; i < count.size(); i++)
                for(int j = 0; j < count[i].size(); j++)
                    if(count[i][j])
                        std::cout << "[" << i << "," << j << "] = " << count[i][j] << std::endl;

            std::cout << "multi_part_trx number = " << multi_part_trx_sum << std::endl << "**************************\n";
        }
        
        int max_i = 0, max_j = 0, max_multi = 0;
        for(int i = 0; i < count.size(); i++)
            for(int j = 0; j < count[i].size(); j++)
            {
                if(count[i][j] > max_multi ||(count[i][j] == max_multi && (new_partition[i].size() + new_partition[j].size()) < (new_partition[max_i].size() + new_partition[max_j].size())))
                {
                    max_i = i;
                    max_j = j;
                    max_multi = count[i][j];
                }
            }
        if(DEBUG_CODE != 0 && count[max_i][max_j]) 
            std::cout << "max count = count[" << max_i << "," <<max_j << "]=" << count[max_i][max_j] << std::endl;
        // int i_s_part = data_belong[max_i];
        // int j_s_part = data_belong[max_j];
        for(auto data : new_partition[max_j])
        {
            new_partition[max_i].insert(data);
            data_belong[data] = max_i;
        }
        new_partition.erase(max_j);
        to_union(find(max_i), find(max_j));
        count[max_i][max_j] = 0;
        multi_part_trx_sum -= max_multi;
        if(DEBUG_CODE != 0)
        {
            std::cout << "multi_part_trx_sum = " << multi_part_trx_sum << std::endl;
            print_new_part_status();
        }
        caculate_count();
    }
}

void init_input()
{
    // data_count = 16;
    // origin_partition[1] = {1, 2,3 ,4, 5}; origin_partition[2] = {6, 7, 8, 9, 10, 11, 12};
    // origin_partition[3] = {13, 14, 15, 16};
    // single_trx[1] = {1, 3}; single_trx[2] = {4, 5, 7}; single_trx[3] = {9, 10};
    // data_access_info[1] = {1, 3}; data_access_info[2] = {2, 5, 8}; 
    // data_access_info[3] = {4, 5}; data_access_info[4] = {7, 8};
    // data_access_info[5] = {6, 9}; data_access_info[6] = {3, 9, 11};
    // data_access_info[7] = {7, 10, 12}; data_access_info[8] = {12, 13};
    // data_access_info[9] = {14, 15}; data_access_info[10] = {14, 16};

    //***** create INPUT data ******
    std::map<int, int> origin_data_belong;
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
    
    alph = 0.1;
    count.resize(data_count, std::vector<int>(data_count, 0));

    //***** OUTPUT ******
    if(DEBUG_CODE != 0)
    {
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
    }
}

int main()
{
    init_input();
    init_disjSet(data_count);

    //**** evaluate data ****
    std::cout << "origin part run trx\n";
    std::set<int> run_eval_trx;
    int run_multi_cnt = 0;
    int origin_multi_cnt = data_access_info.size() * 0.4;
    while(run_eval_trx.size() < data_access_info.size())
    {
        int trx_id;
        if(run_eval_trx.size() < data_access_info.size() * 0.5)
        {   
            trx_id = rand() % (data_access_info.size() - origin_multi_cnt) + origin_multi_cnt + 1;
        }
        // int trx_id = (run_eval_trx.size() % 3 == 2) ? ((rand() % origin_multi_cnt)+ 1) : (rand() % (data_access_info.size() - origin_multi_cnt) + origin_multi_cnt + 1);//(rand() % (data_access_info.size() * 0.4) + 1) : (1);
        trx_id = rand() % data_access_info.size() + 1;
        if(run_eval_trx.find(trx_id) == run_eval_trx.end())
        {
            run_eval_trx.insert(trx_id);
            if(trx_id <= data_access_info.size() * 0.4)
                run_multi_cnt ++;
            std::cout << (run_multi_cnt * 1.0) / run_eval_trx.size() << std::endl;;
        }   
    }

    splitPart();
    if(DEBUG_CODE != 0)
    {
        std::cout << "************ over split part status ***********\n";
        print_new_part_status();
    }

    mergePart();
    if(DEBUG_CODE != 0)
    {
        std::cout << "************ final part status ***********\n";
        print_new_part_status();
        std::cout << "trx num = "<< data_access_info.size() <<"\nfinal multi trx num = " << multi_part_trx_sum << std::endl;
    }
    
    //**** evaluate data ****
    std::cout << "new part run trx\n";
    run_eval_trx.clear();
    // run_multi_cnt = 0;
    while(run_eval_trx.size() < data_access_info.size())
    {
        int trx_id = rand() % data_access_info.size() + 1;
        if(run_eval_trx.find(trx_id) == run_eval_trx.end())
        {
            run_eval_trx.insert(trx_id);
            std::set<int> tmp_access_part;
            for(auto d : data_access_info[trx_id])
            {
                tmp_access_part.insert(data_belong[d]);
            }
            if(tmp_access_part.size() > 1)//跨分区事务
                run_multi_cnt ++;
            std::cout << (run_multi_cnt * 1.0) / (run_eval_trx.size() + data_access_info.size()) << std::endl;;
        }   
    }

}