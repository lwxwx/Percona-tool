/*
 * @Author: liu
 * @Date: 2020-07-09 10:00
 * @LastEditors: Do not edit
 * @LastEditTime: 2021-05-29 02:00
 * @Description: file content
 * @FilePath: /multi-master-tool/id-increment/part-coordinator/coor_server.h
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
#include <shared_mutex>
#include <mutex>
#include <vector>
#include <thread>
#include <stdio.h>
#include <condition_variable>


extern std::mutex id_lock;
extern int64_t s_id, m_id;
extern int32_t part_id;
extern int trx_num;
/**
 * each part communicate for lastest tsn 
 */
//p0 send id message to pn
class ClientForCoor
{
    private:
    std::vector<std::string> pn_addr;
    brpc::Channel channel;
    CoorMessage::CoorService_Stub * stub;

    public:
    int init(std::string addr);
    int send_mid_update(int64_t new_mid);
    int set_pn_addr(std::vector<std::string> addrs);
};

class CoorMessImpl : public CoorMessage::CoorService{
    // private:

    public:
    CoorMessImpl(){};
    virtual ~CoorMessImpl(){};
    virtual void CoorMess(google::protobuf::RpcController* cntl_base, const CoorMessage::CoorRequest* request, CoorMessage::CoorResponse* response, google::protobuf::Closure* done);
};

//pn receive id message from p0
class ServerForCoor
{
    private:
        int port;
        brpc::Server server;
        CoorMessImpl coor_service_impl;

    public:
    int set_port(int p);
    int init();
    int run();
};

/**
 * id allocator 
 */

class ClientForId
{
    private:
        // std::string server_addr;
        brpc::Channel channel;
        IDIncrement::IDService_Stub * stub;
        // void HandleIDcreResponse(brpc::Controller* cntl,IDIncrement::IDResponse* response);

    public:
        int init(std::string addr, int part);
        int send_id_request();
};

class IDIncreImpl : public IDIncrement::IDService{
    public:
    IDIncreImpl(){};
    virtual ~IDIncreImpl(){};
    virtual void IDInc(google::protobuf::RpcController* cntl_base, const IDIncrement::IDRequest* request, IDIncrement::IDResponse* response, google::protobuf::Closure* done);
};

class ServerForId
{
    private:
    int port;
    brpc::Server server;
    IDIncreImpl id_service_impl;

    public:
    int set_port(int p);
    int init();
    int run();
    int set_partid(int32_t p_id);
};

extern std::vector<ClientForCoor*> coor_node_id_heartbeat_send_message_ptr_list;
extern ClientForId *coor_node_id_apply_ptr;
extern ServerForCoor *coor_node_id_heartbeat_receive_message_ptr;
extern ServerForId *coor_node_id_allocator_ptr;