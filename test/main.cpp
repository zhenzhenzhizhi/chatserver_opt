#include "include/json.hpp"
using nlohmann::json;
#include<iostream>
#include <vector>
#include <map>
#include<string>
#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
using namespace std;
//json 序列化
string func1()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";

    string sendBuf = js.dump();
    cout<<sendBuf.c_str()<<endl;
    return sendBuf;
}

void func2()
{
    json js;
// 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;
// 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;
    cout<<js<<endl;
}

int main()
{
    string recvBuf = func1();
    func2();

    //数据的反序列化 json字符串 =》反序列化 数据对象(看作容器，方便访问）
    json buf = json::parse(recvBuf);
    cout << buf["msg_type"]<<endl;
    return 0;
}