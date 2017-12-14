#pragma once
#include "RIPDataStruct.h"
class NetWorking
{
public:
	NetWorking();
	void begin();//初始化
	void setNet(NetWork *Network);//设置路由器网络参数
	void getNet(NetWork *Network);//获取网络参数
protected:
	NetWork netWork[10];
};
