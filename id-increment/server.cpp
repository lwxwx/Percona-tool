/*
 * @Author: liu
 * @Date: 2020-07-09 10:00
 * @LastEditors: Do not edit
 * @LastEditTime: 
 * @Description: file content
 * @FilePath: /multi-master-tool/id-increment/server.cpp
 */


#include <gflags/gflags.h>
#include <brpc/server.h>
#include <butil/logging.h>
#include "./build/id.pb.h"
#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include <set>
#include <mutex>

using namespace std;

DEFINE_int32(port, 60006, "TCP Port of this server");
DEFINE_int32(idle_timeout_s, -1, "Connection will be closed if there is no read/write operations during the last `idle_timeout_s'");

long long g_id = 0, s_id = 0, m_id = 0; // global LSN / sinple LSN / multi LSN
map < long long, string > idmap;
mutex id_lock;
map < int, mutex > part_lock; //partID --> lock
map < int, pair< int , set < string > > > partition_message;//partID + part_version + addressesIP
map < int, set <long long > > total_partition_lsn_message;//partID + global_LSNs
map < int, set <long long > > send_partition_lsn_message;//partID + global_LSNs (latest message)
map < string, int > address_part;//address belong to which partition 


class IDIncreImpl : public IDIncrement::IDService {
public:
    IDIncreImpl() {};
    virtual ~IDIncreImpl() {};
    virtual void IDInc(google::protobuf::RpcController* cntl_base, const IDIncrement::IDRequest* request, IDIncrement::IDResponse* response, google::protobuf::Closure* done) {
        brpc::ClosureGuard done_guard(done);

        brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

        IDIncrement::PartMessage* partMess = new IDIncrement::PartMessage;//send partition_message
        // std::stringstream ip_address;
        // ip_address << cntl->remote_side().ip;

        IDIncrement::LogMessage* logMess = new IDIncrement::LogMessage;

        lock_guard<mutex> guard(id_lock);
        g_id++;
        response->set_g_id(g_id);
        // lock_guard< mutex > guard(part_lock[address_part[ip_address.str()]]);
        // int part_id = address_part[ip_address.str()];
        int part_id = address_part[request->brpc_address()];
        int s_id = total_partition_lsn_message[part_id].size() + 1;
        int m_id = 0;
        //TODO: s_id 和 m_id要不要size+1 取决于mysql里面找空洞是从 1 还是 0 开始找的
        
        cout<<"Received request from " << cntl->remote_side() << " to " << cntl->local_side()<< ": " << request->page_table_no()<<" ,allot id: "<<g_id<< endl;//" ,time:"<<dt<<endl;
        cout << "part_id = " << part_id << endl;
        // response->set_allocated_partition_message(partMess);
        total_partition_lsn_message[part_id].insert(g_id);
        send_partition_lsn_message[part_id].insert(g_id);

        if(part_id == 0){
            //P0不用知道m-id，他是通过s-id来实现排序的
            // m_id = total_partition_lsn_message[0].size();

            //只用告诉P0其他分区的lsn分配情况
            auto it = send_partition_lsn_message.begin();
            for(it++; it != send_partition_lsn_message.end(); it++){
                // logMess.add_lsn(s);
                auto *m = response->mutable_partition_alloc_lsn();
                for(auto s : it->second)
                    (*m)[it->first].add_lsn(s);
                send_partition_lsn_message[it->first].clear();
            }

            //告诉P0其他分区的地址情况
            auto *p = response->mutable_either_part_message();
            auto it1 = partition_message.begin();
            for(it1++; it1 != partition_message.end(); it1++){
                // partMess->set_part_version(it->second.first);
                (*p)[it1->first].set_part_version(it1->second.first);
                for(auto s : it1->second.second)
                    (*p)[it1->first].add_part_address(s);
            }
        }
        else{
            //Pi的m-id应该和P0的s-id一致，就是表示要等到几号id来
            m_id = total_partition_lsn_message[0].size();
            //告诉Pi：P0分区的地址情况
            auto *p = response->mutable_either_part_message();
            (*p)[0].set_part_version(partition_message[0].first);
            for(auto s : partition_message[0].second)
                (*p)[0].add_part_address(s);
        }

        response->set_s_id(s_id);
        response->set_m_id(m_id);
        //告诉自己分区的地址情况
        partMess->set_part_version(partition_message[part_id].first);//TODO: 分区有改变的时候这个版本号也应该会改变，这个后期再改，现在版本号不改变就都是1
        for(auto it : partition_message[part_id].second)
            partMess->add_part_address(it); 
        response->set_allocated_own_part_message(partMess);
    }
};

int main(int argc, char* argv[]) {

    //TODO: 先假设没有动态分区，而是在调度器这边就划分好了分区；动态分区后期用并查集在server这边改一下就好，client应该是不用大改的
    //这边现在没有设端口了，就是一台服务器上的一定是一个分区||这里是需要设置端口的，这是BRPC交流的端口啊
    partition_message[1].first = 1;
    partition_message[1].second.insert("10.11.6.117:22595");
    partition_message[0] .first = 1;
    partition_message[0].second.insert("10.11.6.121:22595");
    address_part["10.11.6.117:22595"] = 1;
    address_part["10.11.6.121:22595"] = 0;

    google::ParseCommandLineFlags(&argc, &argv, true);

    brpc::Server server;

    IDIncreImpl id_service_impl;

    // Add the service into server. 
    if (server.AddService(&id_service_impl, brpc::SERVER_OWNS_SERVICE) != 0) {
        cout << "Fail to add service"<<endl;
        return -1;
    }

    // Start the server.
    brpc::ServerOptions options;
    options.idle_timeout_sec = FLAGS_idle_timeout_s;
    
    if (server.Start(FLAGS_port, &options) != 0) {
        cout << "Fail to start Server"<<endl;
        return -1;
    }
    cout<<"Server start"<<endl;


    server.RunUntilAskedToQuit();
    
    return 0;
}
