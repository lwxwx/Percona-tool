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
#include "./build/id.pb.h"
#include <iostream>
#include <ctime>
using namespace std;

DEFINE_string(protocol, "baidu_std", "Protocol type. Defined in src/brpc/options.proto");
DEFINE_string(connection_type, "", "Connection type. Available values: single, pooled, short");
DEFINE_string(server, "10.11.6.121:60006", "IP Address of server");
DEFINE_string(load_balancer, "", "The algorithm for load balancing");
DEFINE_int32(timeout_ms, 900000000, "RPC timeout in milliseconds");
DEFINE_int32(max_retry, 5, "Max retries(not including the first RPC)"); 
DEFINE_int32(interval_ms, 1000, "Milliseconds between consecutive requests");

void HandleIDcreResponse(brpc::Controller* cntl,IDIncrement::IDResponse* response)
{
    // std::unique_ptr makes sure cntl/response will be deleted before returning.
    unique_ptr<brpc::Controller> cntl_guard(cntl);
    unique_ptr<IDIncrement::IDResponse> response_guard(response);
    
    if (cntl->Failed()) {
        cout << "Fail to send EchoRequest, " << cntl->ErrorText()<<endl;
        return;
    }
    cout << "---------------------- part id = " << response->part_id() << endl;
    cout<<"id = "<<response->g_id()<< " " << response->s_id() << " " <<response->m_id() << endl;

    cout << "own part version = " << response->own_part_message().part_version() << " , own part address : ";
    for(int i = 0; i < response->own_part_message().part_address().size(); i++)
        cout << response->own_part_message().part_address(i) << " , ";
    cout << endl;

    cout << "either part version : " <<endl;
    for(auto it = response->either_part_message().begin(); it != response->either_part_message().end(); it++){
        cout << "part id = " << it->first << " , part version = "<< it->second.part_version() << " , either part address = " ;
        for(auto s : it->second.part_address())
            cout << s << " , ";
        cout << endl;
    }
    
    // for(int i = 0; i < response->partition_message().part_address().size(); i++)
    //     cout << response->partition_message().part_address(i) << " , ";
    // cout << endl;
    cout << "partition lsn message :";
    for(auto it = response->partition_alloc_lsn().begin(); it != response->partition_alloc_lsn().end(); it++){
        cout << "id = " << it->first << ", lsns = ";
        for(auto s : it->second.lsn())
            cout << s << ", ";
    }
    cout << endl;
    // brpc::AskToQuit();
}


int main(int argc, char* argv[]) {

    // Parse gflags
    google::ParseCommandLineFlags(&argc, &argv, true);

    //log
    // logging::LoggingSettings log_setting;
    // log_setting.logging_dest=logging::LOG_TO_FILE;
    // string log_path="./id_client.log";
    // log_setting.log_file=log_path.c_str();
    // logging::InitLogging(log_setting);

    freopen("id_client.log","w",stdout);
    // A Channel represents a communication line to a Server. Notice that Channel is thread-safe and can be shared by all threads in your program.
    brpc::Channel channel;

    // Initialize the channel, NULL means using default options.
    brpc::ChannelOptions options;
    options.protocol = FLAGS_protocol;
    options.connection_type = FLAGS_connection_type;
    options.timeout_ms = FLAGS_timeout_ms/*milliseconds*/;
    options.max_retry = FLAGS_max_retry;
    if (channel.Init(FLAGS_server.c_str(), FLAGS_load_balancer.c_str(), &options) != 0) {
        cout << "Fail to initialize channel"<<endl;;
        return -1;
    }

    // Normally, you should not call a Channel directly, but instead construct a stub Service wrapping it. stub can be shared by all threads as well.
    IDIncrement::IDService_Stub stub(&channel);

    // Send a request 
    // int log_id = 0;
    // while (!brpc::IsAskedToQuit()) {
    for(int i=0;i<1000;i++){
        // We will receive response synchronously, safe to put variables on stack.
        IDIncrement::IDRequest request;
        // IDIncrement::IDResponse response;
        IDIncrement::IDResponse* response=new IDIncrement::IDResponse();
        brpc::Controller* cntl = new brpc::Controller();
        // brpc::Controller cntl;

        request.set_page_table_no("request id");
        request.set_brpc_address("10.11.6.121:22595");
        // cntl->set_log_id(log_id ++);  // set by user

        //callback
        google::protobuf::Closure* done = brpc::NewCallback(&HandleIDcreResponse,cntl,response);
        stub.IDInc(cntl, &request, response, done);

        usleep(FLAGS_interval_ms * 1000L);
    }
    sleep(120);
    cout<<"Client is going to quit"<<endl;
    return 0;
}
