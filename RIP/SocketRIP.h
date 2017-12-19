#pragma once
//�̳�socket���࣬��Ͽͻ�������������һЩ����
//���ӽ���
//�����շ�
#include "SocketBasic.h"
#include"TimeCounter.h"
#include "RIPDataStruct.h"
class SocketRIP :public socketBasic
{
public:
	SocketRIP();
	int begin(bool StopWait);  	//��ʼ��WSA
	int socketConnect(const char *ip, int port);//���׽���Ҫ���ʵķ���������
	int recvSocket(char *RecvData, int Length);//������Ϣ
	int recvSocket(char *RecvData, int Length, const char *FromIp, int Port);
	int recvMessage(RIPMessage *ripMessage);    //���ձ���
	int recvMessage(RIPMessage *ripMessage, const char *FromIp, int Port);
	void sendSocket(char *SendData, int Length);//������Ϣ
	void sendSocket(char* SendvData, int Length, const char *ToIp, int Port);
	void sendMessage(RIPMessage *ripMessage);   //���ͱ���
	void sendMessage(RIPMessage *ripMessage, const char *ToIp, int Port);
	void setSocket(SOCKET S); //����socket�׽���
private:
	static bool stopWait;
	static bool isACK;
	Clock clock;


};
