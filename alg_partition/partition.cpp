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
    data_count = 16;
    alph = 0.1;
    origin_partition[1] = {1, 2,3 ,4, 5}; origin_partition[2] = {6, 7, 8, 9, 10, 11, 12};
    origin_partition[3] = {13, 14, 15, 16};
    single_trx[1] = {1, 3}; single_trx[2] = {4, 5, 7}; single_trx[3] = {9, 10};
    data_access_info[1] = {1, 3}; data_access_info[2] = {2, 5, 8}; 
    data_access_info[3] = {4, 5}; data_access_info[4] = {7, 8};
    data_access_info[5] = {6, 9}; data_access_info[6] = {3, 9, 11};
    data_access_info[7] = {7, 10, 12}; data_access_info[8] = {12, 13};
    data_access_info[9] = {14, 15}; data_access_info[10] = {14, 16};
    count.resize(data_count, std::vector<int>(data_count, 0));
}

int main()
{
    init_input();
    init_disjSet(data_count);

    splitPart();
    if(DEBUG_CODE != 0)
    {
        std::cout << "************ over split part status ***********\n";
        print_new_part_status();
    }

    mergePart();

    std::cout << "************ final part status ***********\n";
    print_new_part_status();
    
}