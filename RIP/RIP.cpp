
#include <STDIO.H>
#include "SocketRIP.h"
#include <process.h>  
#include "RIPPackage.h"
#include "Router.h"
#include <windows.h>  
#include"RIPDataStruct.h"
#pragma comment(lib,"ws2_32.lib")

//#define  messageSendDebug  //测试报文的封装和发送
#define TCP IPPROTO_TCP
#define UDP IPPROTO_UDP
const char myIP[] = { "127.0.0.1" };
Address IPTabe[10];
NetWork myNet[10];
Router R1;
DestinationRouter destRouter[10];
////定义接收线程
//DWORD WINAPI RIPRecvThread(LPVOID lpParameter)
//{
//	//报文测试
//
//	char recvData[4096];
//	SOCKET sClient = (SOCKET)lpParameter;
//	SocketClient socketRecv;
//	socketRecv.setSocket(sClient);
//	while (1)
//	{
//		socketRecv.recvSocket(recvData, 4096, connectIP, port);
//		cout << recvData << endl;
//	}
//	closesocket(sClient);
//	WSACleanup();
//	return 0;
//
//}

//定义发送线程

DWORD WINAPI RIPSendThread(LPVOID lpParameter)
{
#ifdef messageSendDebug
	RIPMessage message;
	MessageData data[3];
	data[0].cost = 1;
	data[0].net.ip.seg[0] = 192;
	data[0].net.ip.seg[1] = 1;
	data[0].net.ip.seg[2] = 1;
	data[0].net.ip.seg[3] = 0;
	data[0].net.mask = 16;
	data[1].cost = 1;
	data[1].net.ip.seg[0] = 192;
	data[1].net.ip.seg[1] = 1;
	data[1].net.ip.seg[2] = 1;
	data[1].net.ip.seg[3] = 8;
	data[1].net.mask = 16;
	data[2].cost = 1;
	data[2].net.ip.seg[0] = 192;
	data[2].net.ip.seg[1] = 1;
	data[2].net.ip.seg[2] = 1;
	data[2].net.ip.seg[3] = 64;
	data[2].net.mask = 24;
	RIPPacket packet;
	packet.begin();
	packet.setHeader(1, 2);
	packet.setMessage(data);
	packet.getMessage(&message);
#endif
	char sendData[1024];
	SOCKET sClient = (SOCKET)lpParameter;
	//SocketClient socketSend;
	//socketSend.setSocket(sClient);
	R1.setSocket(sClient);
	memcpy(sendData, "我是R1", 7);
	while (1)
	{
	//	socketSend.sendSocket(sendData, 1024, connectIP, port);
		R1.sendMessage(destRouter[0].destIP, destRouter[0].port);
		Sleep(15000);
	}
	closesocket(sClient);
	WSACleanup();
	return 0;

}





int main(int argc, char* argv[])
{
	//发送接收缓存
	char sendData[1024];
	char recvData[4096];
	//线程
	const int THREAD_NUM = 2;
	HANDLE handle[THREAD_NUM];
	int i = 0;
	//初IP始化信息
	IPTabe[0].seg[0] = 127;
	IPTabe[0].seg[1] = 0;
	IPTabe[0].seg[2] = 0;
	IPTabe[0].seg[3] = 1;
	IPTabe[1].seg[0] = 127;
	IPTabe[1].seg[1] = 0;
	IPTabe[1].seg[2] = 0;
	IPTabe[1].seg[3] = 2;
	//初始化临近路由器信息
	memcpy(destRouter[0].destIP, "127.0.0.2", 10);
	destRouter[0].port = 8889;
	int routerNum = 1;
	//初始网络信息
	myNet[0].ip.seg[0] = 205;
	myNet[0].ip.seg[1] = 5;
	myNet[0].ip.seg[2] = 6;
	myNet[0].ip.seg[3] = 0;
	myNet[1].ip.seg[0] = 130;
	myNet[1].ip.seg[1] = 11;
	myNet[1].ip.seg[2] = 0;
	myNet[1].ip.seg[3] = 0;
	myNet[2].ip.seg[0] = 130;
	myNet[2].ip.seg[1] = 10;
	myNet[2].ip.seg[2] = 0;
	myNet[2].ip.seg[3] = 0;
	for (int k = 0; k < 3; k++)
	{
		myNet[k].mask = 24;
	}

	bool stopWait = false;
	SocketRIP socketClinet;                     //例化连接建立维护类
	socketClinet.begin(stopWait);
	socketClinet.socketCreate(UDP);
	socketClinet.bindSocket((char *)myIP, 8888);
	SOCKET sclient = socketClinet.socketGet();

	//初始化路由器
	R1.begin(IPTabe,myNet);
	R1.setSocket(sclient);

	memcpy(sendData, "我是R1", 7);
	handle[i] = CreateThread(NULL, 0, RIPSendThread, (LPVOID)sclient, 0, NULL);
	//i = i + 1;
	//handle[i] = CreateThread(NULL, 0, RIPRecvThread, (LPVOID)sclient, 0, NULL);
	while (1)
	{
		//socketClinet.recvSocket(recvData, 4096, connectIP, port);
		//cout << recvData << endl;
		R1.recvMessage(destRouter[0].destIP, destRouter[0].port);
		R1.printfRouter();

	}
	closesocket(sclient);
	WSACleanup();
	return 0;
	   //while (1)
	   //{
		  // socketClinet.recvSocket(recvData, 4096, connectIP, port);
		  // socketClinet.sendSocket(sendData, 1024, connectIP, port);


		  // //socketClinet.sendSocket(sendData, 1024);
		  // //socketClinet.recvSocket(recvData, 4096);
		  // cout << "i" << endl;
	   //}



	//closesocket(sclient);
	//WSACleanup();
	return 0;
}