/*
 * @Author: liu
 * @Date: 2020-07-09 10:00
 * @LastEditors: Do not edit
 * @LastEditTime: 2021-05-29 02:00
 * @Description: file content
 * @FilePath: /multi-master-tool/id-increment/part-coordinator/coor_server.cc
 */

#include "coor_server.h"

ServerForId *coor_node_id_allocator_ptr = NULL;
std::vector<ClientForCoor*> coor_node_id_heartbeat_send_message_ptr_list;
ClientForId *coor_node_id_apply_ptr = NULL;
ServerForCoor *coor_node_id_heartbeat_receive_message_ptr = NULL;
std::mutex id_lock, id_set_lock;
int64_t s_id = 0, m_id = 0;
int32_t part_id;
int cnt = 0;
std::set<uint64_t> id_set;
std::mutex get_id_locker;
std::condition_variable get_id_cv;
// std::map<int64_t, std::pair<std::mutex ,std::condition_variable>> shared_cv;
/**
 * each part communicate for lastest tsn 
 */
int ClientForCoor::init(std::string addr)
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

int ClientForCoor::send_mid_update(int64_t m_id)
{
    stub = new CoorMessage::CoorService_Stub(&channel);                
    CoorMessage::CoorRequest request;
    CoorMessage::CoorResponse response;
    brpc::Controller cntl;
    request.set_m_id(m_id);
    stub->CoorMess(&cntl, &request, &response, NULL);
    // std::unique_lock<std::mutex> locker(shared_cv[request.m_id()].first);
    // locker.unlock();
    // shared_cv[request.m_id()].second.notify_all();
    if(cntl.Failed()){
        std::cout << "failed to send m-id to single partition" << std::endl;
        return -1;
    }else{
        // std::cout << "shoudao " << response.part_id() << "-" <<response.s_id()<< "-" << response.m_id()<< std::endl;
    }
    return 1;
}

void CoorMessImpl::CoorMess(google::protobuf::RpcController* cntl_base, const CoorMessage::CoorRequest* request, CoorMessage::CoorResponse* response, google::protobuf::Closure* done)
{
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
    // std::cout << "hhReceived request from " << cntl->remote_side() << std::endl;
    // std::lock_guard<std::mutex> guard(id_lock);
    response->set_part_id(part_id);
    response->set_s_id(s_id);
    response->set_m_id(m_id);    
    std::lock_guard<std::mutex> guard(id_lock);
    m_id = request->m_id();
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

int ClientForId::wait_for_id()
{
    std::unique_lock<std::mutex> locker(get_id_locker);
    get_id_cv.wait(locker);
    locker.unlock();
}

bool ClientForId::id_set_is_empty()
{
    // std::lock_guard<std::mutex> guard(id_set_lock);
    return id_set.empty();  
}

void notify_id_waiter()
{
    std::unique_lock<std::mutex> locker(get_id_locker);
    locker.unlock();
    get_id_cv.notify_one();
    // std::cout << "get over isset.size = " << id_set.size()<<std::endl ;
}
void HandleIDcreResponse(brpc::Controller* cntl,IDIncrement::IDResponse* response)
{
    std::unique_ptr<brpc::Controller> cntl_guard(cntl);
    std::unique_ptr<IDIncrement::IDResponse> response_guard(response);
    
    if (cntl->Failed()) {
        std::cout << "Fail to send EchoRequest, " << cntl->ErrorText() << std::endl;
        return;
    }
    std::cout<<"id = "<<response->part_id()<< "-" << response->s_id() << "-" <<response->m_id() << std::endl;

    // std::lock_guard<std::mutex> guard(id_set_lock);
    // std::unique_lock<std::mutex> locker(get_id_locker);
    // cnt++;
    // id_set.insert(cnt);
    // notify_id_waiter();
    // locker.unlock();
    // get_id_cv.notify_one();
    // std::cout << "get over isset.size = " << id_set.size()<<std::endl ;
}

int ClientForId::send_id_request()
{
    stub = new IDIncrement::IDService_Stub(&channel);                
    IDIncrement::IDRequest request;
    IDIncrement::IDResponse* response = new IDIncrement::IDResponse();;
    brpc::Controller* cntl = new brpc::Controller();
    request.set_page_table_no("request id");
    google::protobuf::Closure* done = brpc::NewCallback(&HandleIDcreResponse,cntl,response);
    stub->IDInc(cntl, &request, response, done);
    std::cout << "send over" << std::endl;
    return 1;
}

int ClientForId::get_id()
{
    std::lock_guard<std::mutex> guard(id_set_lock);
    if(id_set.empty())
        return -1;
    int get_id = *id_set.begin();
    id_set.erase(id_set.begin());
    // std::cout << "get over isset.size = " << id_set.size()<<std::endl ;
    return get_id;
}


void send_thread(int64_t mid)
{
    for(int i = 0; i < coor_node_id_heartbeat_send_message_ptr_list.size(); i++)
    {
        coor_node_id_heartbeat_send_message_ptr_list[i]->send_mid_update(m_id);
    }
    // std::lock_guard<std::mutex> guard(cnt_lock);
    // cnt++;
}

void IDIncreImpl::IDInc(google::protobuf::RpcController* cntl_base, const IDIncrement::IDRequest* request, IDIncrement::IDResponse* response, google::protobuf::Closure* done) 
{
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
    std::lock_guard<std::mutex> guard(id_lock);
    // std::cout<<"Received request from " << cntl->remote_side() << " to " << cntl->local_side()<< ": " << request->page_table_no()<< std::endl;
    if(part_id == 0)
    {
        m_id++;
        // std::cout<<"Received request from " << cntl->remote_side() << " to " << cntl->local_side()<< ": " << request->page_table_no()<<" ,allot id: "<< part_id << "-0-" << m_id << std::endl;
        //发送m_id至其他单分区节点
        // coor_node_id_heartbeat_send_message_ptr->send_mid_update(m_id);
        std::thread sender(send_thread,m_id);
        sender.detach();
        //好像是可以异步，就是p1传回来的数据可以是[0,0,2]->[1,3,1]这样的对应数据，所以你发送也把自己的全部都发送出去就好
        //wait
        // std::unique_lock<std::mutex> locker(shared_cv[m_id].first);
        // shared_cv[m_id].second.wait(locker);
        // locker.unlock();
    }
    else//单分区事务
    {
        s_id++;
    }
    response->set_part_id(part_id);
    response->set_s_id(s_id);
    response->set_m_id(m_id);
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