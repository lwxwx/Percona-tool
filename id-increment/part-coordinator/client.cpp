/*
 * @Author: liu
 * @Date: 2020-07-09 09:30
 * @LastEditors: Do not edit
 * @LastEditTime: 2020-07-12 16:30
 * @Description: file content
 * @FilePath: /multi-master-tool/id-increment/client.cpp
 */

#include <gflags/gflags.h>
#include <butil/time.h>
#include <brpc/channel.h>
#include "id.pb.h"
#include "coorMess.pb.h"
#include "coor_server.h"
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <thread>
#include <unistd.h>

#include <mutex>
#include <condition_variable>

std::mutex locker;
std::condition_variable cv;
int cnt_thread = 0;

void execute_trsanction(int num)
{
    for(int i = 0;i < num; i++){
        coor_node_id_apply_ptr->send_id_request();
        // if(ret == -1)
        // int cnt = 0;
        usleep(250);
        int ret = coor_node_id_apply_ptr->get_id();
        while(ret == -1)
        {
            // if((cnt++)%3 == 0)
            // coor_node_id_apply_ptr->send_id_request();
            // coor_node_id_apply_ptr->wait_for_id();
            // while(coor_node_id_apply_ptr->id_set_is_empty());
            ret = coor_node_id_apply_ptr->get_id();
        }
        // std::cout << " get id = " <<  ret <<std::endl;
    }
    std::unique_lock<std::mutex> lock(locker);
    cnt_thread++;
    if(cnt_thread == 16)
    {
        cv.notify_one();
    }
    lock.unlock();
}

int main(int argc, char* argv[]) {

    // std::stringstream out_path_tmp ;
    // out_path_tmp << std::this_thread::get_id(); 
    // std::string out_path = "client-" +  out_path_tmp.str() + ".log";
    // std::cout << out_path<< std::endl;
    // freopen("client.log","w",stdout);

    coor_node_id_apply_ptr = new ClientForId;
    coor_node_id_apply_ptr->init(argv[1]);

    uint64_t before_get_id = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch())).count();

    for(int i = 0; i < 16; i++)
    {
        std::thread sender(execute_trsanction, atoi(argv[2]));//16个线程在一个计算节点执行事务
        sender.detach();
    }
    std::unique_lock<std::mutex> lock(locker);
    cv.wait(lock);
    lock.unlock();
    // while(cnt < atoi(argv[2]))
    // {
    //     std::cout <<"cnt = " << cnt << std::endl;
    // }
    uint64_t end_get_id = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch())).count();
    // int n = cnt;
    unsigned long long time_sum = end_get_id - before_get_id;
    // sleep(12);
    std::cout << "get id time = " << time_sum <<std::endl;
    // std::cout <<"cnt final = " << n << std::endl;
    return 0;
}
