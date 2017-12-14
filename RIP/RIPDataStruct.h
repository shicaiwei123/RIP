#pragma once
/*数据结构头文件*/
//包含了所有用到的数据结构和数据的定义
#include<iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;



//地址
union Address
{
	unsigned char seg[4]; //IP地址共4字节，或者看成无符号字符数组所指4部分
	unsigned int address; //或者看成一个整体


};

struct DestinationRouter
{
	 char destIP[10];
	int port;

};

//基本数据结构
//DHCP报文类型标识
enum RIPType {
	RIPRequest = 1,
	RIPResponse = 2
};


//网络信息
struct NetWork
{
	Address ip;
	uint8_t mask;
};

//struct BasicData
//{
//
//};
//交互信息，接收和要发送的数据
struct MessageData
{
	NetWork net;
	uint8_t cost;
};

//路由表,本地路由表，接收信息后暂存新的路由表
struct RouterTable
{
	MessageData messageData;
	Address nextHop;
};




//RIP报文报文基本首部
 struct RIPHeader
{
	uint8_t command;      // message op code, message type
	uint8_t version;   // versin 0f RIP
	Address fromIP;
 };

//DHCP报文选项
 struct RIPMessage
{
//	uint8_t series;    // series of protocol
	RIPHeader header;
	MessageData messageData[10];

};

