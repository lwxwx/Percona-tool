/*
 * @Author: liu
 * @Date: 2020-07-09 09:30
 * @LastEditors: Do not edit
 * @LastEditTime: 2020-07-12 16:30
 * @Description: file content
 * @FilePath: /multi-master-tool/id-increment/client.cpp
 * @bash cmd : ./client 127.0.0.1:60006 100 #addr:port send_num
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

void execute_trsanction(int num)
{
    // srand((unsigned)time(NULL));
    for(int i = 0;i < num; i++){
        if(part_id == 0)
            // usleep(100000);
            sleep(1);
        // uint64_t before_get_id = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch())).count();
        coor_node_id_apply_ptr->send_id_request();
        // uint64_t end_get_id = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch())).count();

        // int sleep_time = rand() % 1 + 1;
        // std::cout << "[INFO] cost " << end_get_id - before_get_id <<"us , sleep " << sleep_time << "s\n";
    }
}

int main(int argc, char* argv[]) {

    // freopen("client.log","w",stdout);

    coor_node_id_apply_ptr = new ClientForId;
    coor_node_id_apply_ptr->init(argv[2], atoi(argv[1]));

    trx_num = 1 * atoi(argv[3]);
    std::cout << (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch())).count() << std::endl;

    for(int i = 0; i < 1; i++)//线程数量
    {
        std::thread sender(execute_trsanction, atoi(argv[3]));//16个线程在一个计算节点执行事务
        sender.detach();
    }

    // std::cout << (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch())).count() << std::endl;

    sleep(20000);
    
    return 0;
}
