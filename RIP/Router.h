#pragma once
#include "RIPDataStruct.h"
class  Router
{
public:
	void begin();//��ʼ��·����
	int update();//����·�ɱ���
	int sendData();//����·����Ϣ
	int recvData();//����·����Ϣ
private:
	RouterTable localTable[10];//���汾�ص�·�ɱ�
	RouterTable tempTable[10]; //������յ���·�ɱ�
	MessageData recvMessage[10]; //���͵�·����Ϣ
	MessageData sendMessage[10]; //���յ�·����Ϣ
};
