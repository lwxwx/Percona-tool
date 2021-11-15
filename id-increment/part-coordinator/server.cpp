/*
 * @Author: liu
 * @Date: 2020-07-09 10:00
 * @LastEditors: Do not edit
 * @LastEditTime: 2021-05-26 14:00
 * @Description: file content
 * @FilePath: /multi-master-tool/id-increment/part-coordinator/part_server.cpp
 * @bash cmd : ./server 1 60006 #part_id port
 */

#include <brpc/server.h>
#include <brpc/channel.h>
#include <butil/logging.h>
#include "id.pb.h"
#include "coorMess.pb.h"
#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include <set>
#include <mutex>
#include <vector>
#include <thread>
#include <stdio.h>
#include "coor_server.h"
// long long  s_id = 0, m_id = 0; //  sinple LSN / multi LSN
// int part_id;
// mutex id_lock, remote_lock;
// brpc::Channel multi_part_channel;
// int cnt = 1,remote_cnt = 0;

void id_allocator_run()
{
    coor_node_id_allocator_ptr->run();
}

void coor_run()
{
    coor_node_id_heartbeat_receive_message_ptr->run();
}

int main(int argc, char* argv[]) {

    int part_id = atoi(argv[1]);
    int port = atoi(argv[2]);

    // std::string out_path = "server-" + std::to_string(part_id) + ".log";
    // std::cout << out_path<< std::endl;
    // freopen(out_path.c_str(),"w",stdout);

    coor_node_id_allocator_ptr = new ServerForId;
    coor_node_id_allocator_ptr->set_partid(part_id);
    coor_node_id_allocator_ptr->set_port(port);
    std::cout << "set port" << std::endl;
    coor_node_id_allocator_ptr->init();
    std::thread allocator(id_allocator_run);
    allocator.detach();    

    std::string pn_addr[] = {"10.11.6.121:60086", "10.11.6.117:60086"};//,"10.11.6.119:60086"};
    if(part_id == 0)
    {
        std::cout << "part 0" << std::endl;
        for(int i = 0; i < 2; i++)
        {
            ClientForCoor* coor_node_id_heartbeat_send_message_ptr_tmp = new ClientForCoor;
            coor_node_id_heartbeat_send_message_ptr_tmp->init(pn_addr[i]);
            coor_node_id_heartbeat_send_message_ptr_list.push_back(coor_node_id_heartbeat_send_message_ptr_tmp);
        }
    }
    else
    {
        std::cout << "part "<< part_id << std::endl;
        coor_node_id_heartbeat_receive_message_ptr = new ServerForCoor;
        coor_node_id_heartbeat_receive_message_ptr->set_port(60086);
        coor_node_id_heartbeat_receive_message_ptr->init();
        std::thread coor_message(coor_run);
        coor_message.detach();
    }

    // std::cout << "over" << std::endl;
    sleep(1200);

    return 0;
}
