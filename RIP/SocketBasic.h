#pragma once
//socket�Ļ��࣬������socket��һЩ��������
//��ʼ���������׽���
#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib")   //����ws2_32.lib��.ֻҪ�������õ�Winsock API ��������Ҫ�õ� Ws2_32.lib  
#include<stdio.h>
#include <string.h>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
class socketBasic
{
private:
	int verA;
	int verB;
	int protocol;
protected:
	SOCKET s;  //�����Լ��׽���
public:
	socketBasic();//���캯��
	int begin(bool StopWait);  	//��ʼ��WSA
	int socketCreate(int protocol);//��������socket�׽���
	int bindSocket(char *Ip, int Port); //���׽��ֵ�ַ
	int recvSocket(char *RecvData, int Length);//������Ϣ
	int recvSocket(char *RecvData, int Length, const char *FromIp, int Port);
	int sendSocket(char *SendData, int Length);//������Ϣ
	int sendSocket (char* SendvData, int Length, const char *ToIp, int Port);
	SOCKET socketGet();  //��ȡ�������׽���


};
