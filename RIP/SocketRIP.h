#pragma once
//继承socket基类，结合客户端需求，增加了一些方法
//连接建立
//报文收发
#include "SocketBasic.h"
#include"TimeCounter.h"
#include "RIPDataStruct.h"
class SocketRIP :public socketBasic
{
public:
	SocketRIP();
	int begin(bool StopWait);  	//初始化WSA
	int socketConnect(const char *ip, int port);//绑定套接字要访问的服务器参数
	int recvSocket(char *RecvData, int Length);//接收信息
	int recvSocket(char *RecvData, int Length, const char *FromIp, int Port);
	int recvMessage(RIPMessage *ripMessage);    //接收报文
	int recvMessage(RIPMessage *ripMessage, const char *FromIp, int Port);
	void sendSocket(char *SendData, int Length);//发送信息
	void sendSocket(char* SendvData, int Length, const char *ToIp, int Port);
	void sendMessage(RIPMessage *ripMessage);   //发送报文
	void sendMessage(RIPMessage *ripMessage, const char *ToIp, int Port);
	void setSocket(SOCKET S); //传入socket套接字
private:
	static bool stopWait;
	static bool isACK;
	Clock clock;


};
