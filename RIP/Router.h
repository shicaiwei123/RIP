#pragma once
#include "RIPDataStruct.h"
#include "RIPPackage.h"
#include "NetWorking.h"
#include "SocketRIP.h"
class  Router:public RIPPacket,public SocketRIP,public NetWorking
{
public:
	Router();
	void begin(Address *IPTable,NetWork *Network);//��ʼ��·����
	int recvMessage();//����·����Ϣ
	int recvMessage( const char *FromIp, int Port);
	int update();//����·�ɱ���

	int sendMessage();//����·����Ϣ
	int sendMessage(const char *ToIp, int Port);
	void printfRouter();  //��ӡ���·�ɱ�
	bool getFinishFlag();

private:
	void initRouter();  //·��������ʱ����ʼ��·�ɱ�
	RouterTable localTable[10];//���汾�ص�·�ɱ�
	MessageData tempMessage[10]; //������յ���·����Ϣ
	MessageData recvRouter[10]; //���յ�·����Ϣ
	MessageData sendRouter[10]; //���͵�·����Ϣ
	RIPMessage messageRecv;
	RIPMessage messageSend;
	bool isFinish;    //��־�����Ƿ������
	int tableLen;    //����·�ɱ���

};
