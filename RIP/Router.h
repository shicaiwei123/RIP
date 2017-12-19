#pragma once
#include "RIPDataStruct.h"
#include "RIPPackage.h"
#include "NetWorking.h"
#include "SocketRIP.h"
class  Router:public RIPPacket,public SocketRIP,public NetWorking
{
public:
	Router();
	void begin(Address *IPTable,NetWork *Network);//初始化路由器
	int recvMessage();//接收路由信息
	int recvMessage( const char *FromIp, int Port);
	int update();//更新路由表项

	int sendMessage();//发送路由信息
	int sendMessage(const char *ToIp, int Port);
	void printfRouter();  //打印输出路由表。
	bool getFinishFlag();

private:
	void initRouter();  //路由器启动时，初始化路由表
	RouterTable localTable[10];//储存本地的路由表
	MessageData tempMessage[10]; //缓存接收到的路由信息
	MessageData recvRouter[10]; //接收的路由信息
	MessageData sendRouter[10]; //发送的路由信息
	RIPMessage messageRecv;
	RIPMessage messageSend;
	bool isFinish;    //标志报文是否处理完成
	int tableLen;    //本地路由表长度

};
