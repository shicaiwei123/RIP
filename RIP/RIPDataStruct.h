#pragma once
/*���ݽṹͷ�ļ�*/
//�����������õ������ݽṹ�����ݵĶ���
#include<iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;



//��ַ
union Address
{
	unsigned char seg[4]; //IP��ַ��4�ֽڣ����߿����޷����ַ�������ָ4����
	unsigned int address; //���߿���һ������


};

struct DestinationRouter
{
	 char destIP[10];
	int port;

};

//�������ݽṹ
//DHCP�������ͱ�ʶ
enum RIPType {
	RIPRequest = 1,
	RIPResponse = 2
};


//������Ϣ
struct NetWork
{
	Address ip;
	uint8_t mask;
};

//struct BasicData
//{
//
//};
//������Ϣ�����պ�Ҫ���͵�����
struct MessageData
{
	NetWork net;
	uint8_t cost;
};

//·�ɱ�,����·�ɱ�������Ϣ���ݴ��µ�·�ɱ�
struct RouterTable
{
	MessageData messageData;
	Address nextHop;
};




//RIP���ı��Ļ����ײ�
 struct RIPHeader
{
	uint8_t command;      // message op code, message type
	uint8_t version;   // versin 0f RIP
	Address fromIP;
 };

//DHCP����ѡ��
 struct RIPMessage
{
//	uint8_t series;    // series of protocol
	RIPHeader header;
	MessageData messageData[10];

};

