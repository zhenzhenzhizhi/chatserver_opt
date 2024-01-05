#include"chatserver.hpp"
#include"json.hpp"
#include <iostream>
#include"chatservice.hpp"

using namespace std;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop* loop,  //事件循环
               const InetAddress& listenAddr, //IP+Port
               const string& nameArg)
               :_server(loop,listenAddr,nameArg)
               ,_loop(loop)
{
    // 注册连接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    //注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2 ,_3));

    //设置线程数量
    _server.setThreadNum(4);
}



void ChatServer:: start()
{
    _server.start();
}
    //专门处理用户的连接创建和断开 epoll listen accept
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    if(conn->connected())
    {
        cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() <<
        " state:online"<<endl;
    }
    else //客户端断开连接
    {
        cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() <<
                " state:offline"<<endl;

        //客户端异常断开处理
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
        //_loop->quit();
    }
}
//专门处理用户的读写事件
void ChatServer::onMessage(const TcpConnectionPtr &conn,
                Buffer *buffer, //缓冲区
                Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    //数据的反序列化
    json js = json::parse(buf);
    //通过js["msgid"] 获取业务handler
    //达到目的，完全解耦网络模块的代码和业务模块的代码
    auto MsgHandler = ChatService::instance() ->getHandler(js["msgid"].get<int>());

    //回调消息绑定好的事件处理器，来执行相应的业务处理
    MsgHandler(conn, js, time);
    
}