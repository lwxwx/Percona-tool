/*
 * @Author: liu
 * @Date: 2020-07-09 10:00
 * @LastEditors: Do not edit
 * @LastEditTime: 2021-05-26 14:00
 * @Description: file content
 * @FilePath: /multi-master-tool/id-increment/part-coordinator/part_server.cpp
 */

#include <brpc/server.h>
#include <brpc/channel.h>
#include <butil/logging.h>
#include "./build/id.pb.h"
#include "./build/coorMess.pb.h"
#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include <set>
#include <mutex>
#include <vector>
#include <thread>

using namespace std;

long long  s_id = 0, m_id = 0; //  sinple LSN / multi LSN
int part_id;
mutex id_lock;
brpc::Channel multi_part_channel;


class IDIncreImpl : public IDIncrement::IDService {
public:
    IDIncreImpl() {};
    virtual ~IDIncreImpl() {};
    virtual void IDInc(google::protobuf::RpcController* cntl_base, const IDIncrement::IDRequest* request, IDIncrement::IDResponse* response, google::protobuf::Closure* done) {
        brpc::ClosureGuard done_guard(done);

        brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

        lock_guard<mutex> guard(id_lock);
        response->set_part_id(part_id);
        if(part_id == 0)
        {
            m_id++;
            cout<<"Received request from " << cntl->remote_side() << " to " << cntl->local_side()<< ": " << request->page_table_no()<<" ,allot id: "<< part_id << "-0-" << m_id << endl;
            //发送m_id至其他单分区节点
            CoorMessage::CoorService_Stub* coor_stub = new CoorMessage::CoorService_Stub(&multi_part_channel);
            CoorMessage::CoorRequest coor_request;
            CoorMessage::CoorResponse coor_response;
            brpc::Controller coor_cntl;
            coor_request.set_m_id(m_id);
            coor_stub->CoorMess(&coor_cntl, &coor_request, &coor_response, NULL);
            if(coor_cntl.Failed()){
                cout << "failed to send m-id to single partition" << endl;
            }else{
                cout << "shoudao " << coor_response.part_id() << "-" <<coor_response.s_id()<< "-" << coor_response.m_id()<< endl;
                response->set_s_id(0);
                response->set_m_id(m_id);   
            }
        }
        else//单分区事务
        {
            s_id++;
            cout<<"Received request from " << cntl->remote_side() << " to " << cntl->local_side()<< ": " << request->page_table_no()<<" ,allot id: "<< part_id << "-" << s_id << "-" << m_id << endl;
            response->set_s_id(s_id);
            response->set_m_id(m_id);
        }
    }
};

class CoorMessImpl : public CoorMessage::CoorService {
public:
    CoorMessImpl() {};
    virtual ~CoorMessImpl() {};
    virtual void CoorMess(google::protobuf::RpcController* cntl_base, const CoorMessage::CoorRequest* request, CoorMessage::CoorResponse* response, google::protobuf::Closure* done) {
        brpc::ClosureGuard done_guard(done);
        brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
        cout << "Received request from " << cntl->remote_side()<<endl;
        lock_guard<mutex> guard(id_lock);
        response->set_part_id(part_id);
        response->set_s_id(s_id);
        response->set_m_id(m_id);
        m_id = request->m_id();
    }
};


brpc::Server server;
void run_id_allocator()
{
    server.RunUntilAskedToQuit();
}

brpc::Server coor_server;
void run_coor_comm()
{
    coor_server.RunUntilAskedToQuit();
}

int main(int argc, char* argv[]) {

    part_id = atoi(argv[1]);
    int port = atoi(argv[2]);

    //allocate id
    IDIncreImpl id_service_impl;
    if (server.AddService(&id_service_impl, brpc::SERVER_OWNS_SERVICE) != 0) {
        cout << "Fail to add service"<<endl;
        return -1;
    }
    brpc::ServerOptions options;
    options.idle_timeout_sec = -1;    
    if (server.Start(port, &options) != 0) {
        cout << "Fail to start Server"<<endl;
        return -1;
    }
    cout<<"IDServer start"<<endl;
    thread allocator(run_id_allocator);
    allocator.detach();
    cout << "sds"<<endl;

    if(part_id == 0)
    {
        cout << "part 0" << endl;
        brpc::ChannelOptions c_options;
        c_options.timeout_ms=-1;
        c_options.connect_timeout_ms=-1;
        if (multi_part_channel.Init("10.11.6.121:60086", &c_options) != 0) {
            cout << "Fail to initialize channel"<<endl;;
            return -1;
        }
        CoorMessage::CoorService_Stub* coor_stub = new CoorMessage::CoorService_Stub(&multi_part_channel);
            CoorMessage::CoorRequest coor_request;
            CoorMessage::CoorResponse coor_response;
            brpc::Controller coor_cntl;
            coor_request.set_m_id(m_id);
            coor_stub->CoorMess(&coor_cntl, &coor_request, &coor_response, NULL);
    }
    else{
        cout << "part 1" << endl;
        CoorMessImpl coor_mess_impl;
        if (coor_server.AddService(&coor_mess_impl, brpc::SERVER_OWNS_SERVICE) != 0) {
            cout << "Fail to add coor service"<<endl;
            return -1;
        }
        brpc::ServerOptions coor_options;
        coor_options.idle_timeout_sec = -1;    
        if (coor_server.Start(60086, &options) != 0) {
            cout << "Fail to start coor Server"<<endl;
            return -1;
        }
        cout<<"CoorServer start"<<endl;
        thread commer(run_coor_comm);
        commer.detach();
    }

    cout << "over" << endl;
    sleep(120);

    return 0;
}
