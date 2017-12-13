#pragma once
#include "RIPDataStruct.h"
class  Router
{
public:
	void begin();//初始化路由器
	int update();//更新路由表项
	int sendData();//发送路由信息
	int recvData();//接收路由信息
private:
	RouterTable localTable[10];//储存本地的路由表
	RouterTable tempTable[10]; //缓存接收到的路由表
	MessageData recvMessage[10]; //发送的路由信息
	MessageData sendMessage[10]; //接收的路由信息
};
