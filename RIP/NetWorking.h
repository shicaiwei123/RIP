#pragma once
#include "RIPDataStruct.h"
class NetWorking
{
public:
	NetWorking();
	void begin();//��ʼ��
	void setNet(NetWork *Network);//����·�����������
	void getNet(NetWork *Network);//��ȡ�������
protected:
	NetWork netWork[10];
};
