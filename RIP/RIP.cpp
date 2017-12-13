
#include <STDIO.H>
#include "SocketRIP.h"
#include <process.h>  
#include "RIPPackage.h"
#include <windows.h>  
#include"RIPDataStruct.h"
#pragma comment(lib,"ws2_32.lib")

#define  messageSendDebug  //测试报文的封装和发送
#define TCP IPPROTO_TCP
#define UDP IPPROTO_UDP
const char myIp[] = { "127.0.0.1 "};
const char connectIP[] = { "127.0.0.2" };
int port = 8889;
//定义接收线程
DWORD WINAPI RIPRecvThread(LPVOID lpParameter)
{
	//报文测试

	char recvData[4096];
	SOCKET sClient = (SOCKET)lpParameter;
	SocketClient socketRecv;
	socketRecv.setSocket(sClient);
	while (1)
	{
		socketRecv.recvSocket(recvData, 4096, connectIP, port);
		cout << recvData << endl;
	}
	closesocket(sClient);
	WSACleanup();
	return 0;

}

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
	SocketClient socketSend;
	socketSend.setSocket(sClient);
	memcpy(sendData, "我是R1", 7);
	while (1)
	{
	//	socketSend.sendSocket(sendData, 1024, connectIP, port);
		socketSend.sendMessage(&message, connectIP, port);
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
	//

	bool stopWait = false;
	memcpy(sendData,"我是R1",7);
	SocketClient socketClinet;                     //例化连接建立维护类
	socketClinet.begin(stopWait);
	socketClinet.socketCreate(UDP);
	socketClinet.bindSocket((char *)myIp, 8888);
	//socketClinet.socketConnect(connectIP, 8888);
	SOCKET sclient = socketClinet.socketGet();
	handle[i] = CreateThread(NULL, 0, RIPSendThread, (LPVOID)sclient, 0, NULL);
	//i = i + 1;
	//handle[i] = CreateThread(NULL, 0, RIPRecvThread, (LPVOID)sclient, 0, NULL);
	while (1)
	{
		socketClinet.recvSocket(recvData, 4096, connectIP, port);
		cout << recvData << endl;
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