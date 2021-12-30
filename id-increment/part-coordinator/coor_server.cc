/*
 * @Author: liu
 * @Date: 2020-07-09 10:00
 * @LastEditors: Do not edit
 * @LastEditTime: 2021-05-29 02:00
 * @Description: file content
 * @FilePath: /multi-master-tool/id-increment/part-coordinator/coor_server.cc
 */

#include "coor_server.h"

int DEBUG_CODE = 1;

std::mutex id_lock;
int64_t s_id = 0, m_id = 0;
int32_t part_id;

ServerForId *coor_node_id_allocator_ptr;
std::vector<ClientForCoor*> coor_node_id_heartbeat_send_message_ptr_list;
ClientForId *coor_node_id_apply_ptr;
ServerForCoor *coor_node_id_heartbeat_receive_message_ptr;

std::map<int, std::map<int, int>> each_mid_pn_sid;
std::mutex each_mid_pn_sid_lock;
std::condition_variable each_mid_pn_sid_lock_condition;
std::mutex coor_node_id_heartbeat_send_message_ptr_list_lock;

/**
 * each part communicate for lastest tsn 
 */
int ClientForCoor::init(std::string addr)
{
    brpc::ChannelOptions c_options;
    c_options.timeout_ms=-1;
    c_options.connect_timeout_ms=-1;
    if (channel.Init(addr.c_str(), &c_options) != 0) {
        std::cout << "Fail to initialize channel for addr :" << addr << std::endl;
        return -1;
    }  
    return 1;
}

void HandleCoorResponse(brpc::Controller* cntl,CoorMessage::CoorResponse* response)
{
    std::unique_ptr<brpc::Controller> cntl_guard(cntl);
    std::unique_ptr<CoorMessage::CoorResponse> response_guard(response);
    
    if(cntl->Failed()){
        std::cout << "failed to send m-id to single partition " << cntl->ErrorText() << std::endl;
        return;
    }else{
        if(DEBUG_CODE != 0)
        {
            std::cout << "[SERVER GET EITHER PART INFO] for m-id = " << m_id<< " shoudao " << response->part_id() << "-" <<response->s_id() << std::endl;            
        }
        std::unique_lock<std::mutex> each_lock(each_mid_pn_sid_lock);
        each_mid_pn_sid[m_id][response->part_id()] = response->s_id();
        // each_mid_pn_sid_lock_condition.notify_one();
    }
}

int ClientForCoor::send_mid_update(int64_t m_id)
{
    stub = new CoorMessage::CoorService_Stub(&channel);                
    CoorMessage::CoorRequest request;
    CoorMessage::CoorResponse *response = new CoorMessage::CoorResponse();
    brpc::Controller *cntl = new brpc::Controller();
    request.set_m_id(m_id);
    cntl->set_timeout_ms(1000);
    if(DEBUG_CODE != 0)
    {
        std::cout << "send_mid_update(" << m_id << ")\n";
    }

    google::protobuf::Closure* done = brpc::NewCallback(&HandleCoorResponse,cntl,response);
    stub->CoorMess(cntl, &request, response, done);

    // stub->CoorMess(cntl, &request, response, NULL);
    // if(cntl->Failed()){
    //     std::cout << "failed to send m-id to single partition" << std::endl;
    //     return -1;
    // }else{
    //     if(DEBUG_CODE != 0)
    //     {
    //         std::cout << "[SERVER GET EITHER PART INFO] for m-id = " << m_id<< " shoudao " << response->part_id() << "-" <<response->s_id() << std::endl;            
    //     }
    //     std::unique_lock<std::mutex> lock_guard(each_mid_pn_sid_lock);
    //     each_mid_pn_sid[m_id][response->part_id()] = response->s_id();
    //     // each_mid_pn_sid_lock_condition.notify_one();
    // }

    if(DEBUG_CODE != 0)
    {
        std::cout << "send over \n";
    }
    return 1;
}

void CoorMessImpl::CoorMess(google::protobuf::RpcController* cntl_base, const CoorMessage::CoorRequest* request, CoorMessage::CoorResponse* response, google::protobuf::Closure* done)
{
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
    
    if(DEBUG_CODE != 0)
    {
        std::cout << "receive from " << cntl->remote_side() << " " << request->m_id() << std::endl;
    }

    std::lock_guard<std::mutex> guard(id_lock);
    response->set_part_id(part_id);
    response->set_s_id(s_id);
    m_id = request->m_id();
    if(DEBUG_CODE != 0)
    {
        std::cout << "set m-id = " << m_id << std::endl;
    }
}

int ServerForCoor::set_port(int p)
{
    port = p;
    return 1;
}

int ServerForCoor::init()
{
    if (server.AddService(&coor_service_impl, brpc::SERVER_OWNS_SERVICE) != 0) 
    {
        std::cout << "Fail to add coor service" << std::endl;
        return -1;
    }
    brpc::ServerOptions options;
    options.idle_timeout_sec = -1;    
    if (server.Start(port, &options) != 0) 
    {
        std::cout << "Fail to start coor Server" << std::endl;
        return -1;
    }
    return 1;
}

int ServerForCoor::run()
{
    server.RunUntilAskedToQuit();
    return 1;
}

/**
 * id allocator 
 */
int ClientForId::init(std::string addr)
{
    brpc::ChannelOptions c_options;
    c_options.timeout_ms=-1;
    c_options.connect_timeout_ms=-1;
    if (channel.Init(addr.c_str(), &c_options) != 0) {
        std::cout << "Fail to initialize channel"<< std::endl;
        return -1;
    }
    return 1;
}

void HandleIDcreResponse(brpc::Controller* cntl,IDIncrement::IDResponse* response)
{
    std::unique_ptr<brpc::Controller> cntl_guard(cntl);
    std::unique_ptr<IDIncrement::IDResponse> response_guard(response);
    
    if (cntl->Failed()) {
        std::cout << "Fail to send EchoRequest, " << cntl->ErrorText() << std::endl;
        return;
    }
    if(DEBUG_CODE != 0)
    {
        std::cout<<"[CLIENT GET ID] id = "<<response->part_id()<< "-" << response->s_id() << "-" <<response->m_id() << std::endl;
        std::cout << "for p0 either_part_tsn.size() =  " << response->either_part_tsn_size() << " : ";
        for(auto it = response->either_part_tsn().begin(); it != response->either_part_tsn().end(); it++)
            std::cout << it->first << " - " << it->second << ", ";
        std::cout << std::endl;
    }
}

int ClientForId::send_id_request()
{
    stub = new IDIncrement::IDService_Stub(&channel);                
    IDIncrement::IDRequest request;
    IDIncrement::IDResponse* response = new IDIncrement::IDResponse();
    brpc::Controller* cntl = new brpc::Controller();
    request.set_page_table_no("request id");
    cntl->set_timeout_ms(1000);
    if(DEBUG_CODE != 0)
    {
        std::cout << "send id\n";
    }
    google::protobuf::Closure* done = brpc::NewCallback(&HandleIDcreResponse,cntl,response);
    stub->IDInc(cntl, &request, response, done);
    return 1;
}

void send_thread(ClientForCoor* ptr,int64_t mid)
{
    // std::unique_lock<std::mutex> each_lock(each_mid_pn_sid_lock);

    int res = ptr->send_mid_update(m_id);
    while(res != 1)
    {
        if(DEBUG_CODE != 0)
        {
            std::cout << "send_thread(" << mid <<") have error\n";
        }
        res = ptr->send_mid_update(m_id);
    }
    
    // each_mid_pn_sid_lock_condition.wait_for(each_lock,std::chrono::seconds(5));	
}

void IDIncreImpl::IDInc(google::protobuf::RpcController* cntl_base, const IDIncrement::IDRequest* request, IDIncrement::IDResponse* response, google::protobuf::Closure* done) 
{
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
    std::lock_guard<std::mutex> guard(id_lock);

    if(DEBUG_CODE != 0)
    {
        std::cout << "here start send to client\n";
    }
    if(part_id == 0)
    {
        m_id++;
        std::vector<std::thread> sender_list(coor_node_id_heartbeat_send_message_ptr_list.size());
        for(int i = 0; i < coor_node_id_heartbeat_send_message_ptr_list.size(); i++)
        {
            // sender_list[i] = std::thread(send_thread,coor_node_id_heartbeat_send_message_ptr_list[i],m_id);
            // sender_list[i].detach();
            coor_node_id_heartbeat_send_message_ptr_list[i]->send_mid_update(m_id);
        }
        // each_mid_pn_sid_lock.lock();
        // if(each_mid_pn_sid[m_id].size() < coor_node_id_heartbeat_send_message_ptr_list.size()){
            while(each_mid_pn_sid[m_id].size() < coor_node_id_heartbeat_send_message_ptr_list.size())
            {
                // usleep(500);
                // std::cout << "wait [" << m_id << "]\n";
            }
        // }
        // std::unique_lock<std::mutex> each_lock(each_mid_pn_sid_lock);
        // each_mid_pn_sid_lock_condition.wait_for(each_lock,std::chrono::seconds(5));	
        response->mutable_either_part_tsn()->insert(each_mid_pn_sid[m_id].begin(), each_mid_pn_sid[m_id].end());
    }
    else//单分区事务
    {
        s_id++;
    }

    if(DEBUG_CODE != 0)
    {
        std::cout << "okok send to client\n";
    }

    response->set_part_id(part_id);
    response->set_s_id(s_id);
    response->set_m_id(m_id);
    
    if(DEBUG_CODE != 0)
    {
        std::cout<<"[SERVER ALLOCATE ID] " << cntl->remote_side() << " : " << part_id << "-" << s_id << "-" << m_id << std::endl;
    }
}

int ServerForId::set_port(int p)
{
    port = p;
    return 1;
}

int ServerForId::init()
{
    if (server.AddService(&id_service_impl, brpc::SERVER_OWNS_SERVICE) != 0) {
        std::cout << "Fail to add service"<<std::endl;
        return -1;
    }
    brpc::ServerOptions options;
    options.idle_timeout_sec = -1;
    // options.max_concurrency = 1; 
    if (server.Start(port, &options) != 0) {
        std::cout << "Fail to start Server"<<std::endl;
        return -1;
    }
    return 1;
}

int ServerForId::run()
{
    server.RunUntilAskedToQuit();
}

int ServerForId::set_partid(int p_id)
{
    part_id = p_id;
    return 1;
}