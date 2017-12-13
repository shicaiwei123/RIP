#include "SocketBasic.h"

socketBasic::socketBasic()
{

}

int socketBasic::begin(bool StopWait)
{

	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
}
int socketBasic::socketCreate(int Protocol)
{
	protocol = Protocol;
	if (Protocol == IPPROTO_TCP)
	{
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			printf("invalid socket !");
			return -1;
		}

	}
	else if (Protocol == IPPROTO_UDP)
	{
		s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (s == INVALID_SOCKET)
		{
			printf("invalid socket !");
			return -1;
		}
	}
	else
		return -2;


}

int socketBasic::bindSocket(char *Ip, int Port)
{
	int err;
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(Port);
	serAddr.sin_addr.S_un.S_addr = inet_addr(Ip);
	err = bind(s, (sockaddr *)&serAddr, sizeof(serAddr));
	if (err == SOCKET_ERROR)
	{
		printf("bind error !");
		closesocket(s);
		return -1;
	}
	return 0;
}

int socketBasic::recvSocket(char *RecvData, int Length)
{
	int ret;
	memset(RecvData, 0, Length);     //清空接收缓存
	while (true)
	{
		ret = recv(s, RecvData, Length, 0);
		if (ret > 0)
		{
			cout << "收到一个数据" << endl;
			return 0;
		}
	}
	

}

int socketBasic::recvSocket(char *RecvData, int Length, const char *FromIp, int Port)
{
	int ret;
	memset(RecvData, 0, Length);     //清空接收缓存
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(Port);
	serAddr.sin_addr.S_un.S_addr = inet_addr(FromIp);
	int len = sizeof(serAddr);
	while (true)
	
	{
		ret = recvfrom(s, RecvData, Length, 0, (sockaddr *)&serAddr, &len);
		if (ret > 0)
		{
			cout << "收到一个数据" << endl;
			return 0;
		}
	}


}

int socketBasic::sendSocket(char *SendData, int Length)
{
	int err;
	int ret;
		err = send(s, SendData, Length, 0);
		if (err == -1)
		{
			cout << "发送失败" << endl;
			return -1;
		}


	return 0;

}

int socketBasic::sendSocket(char* SendData, int Length, const char *ToIp, int Port)
{
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(Port);
	serAddr.sin_addr.S_un.S_addr = inet_addr(ToIp);
	int len = sizeof(serAddr);
	int setNum = sendto(s, SendData, Length, 0, (sockaddr *)&serAddr, sizeof(serAddr));
	if (setNum>0)
	{
		cout << "发送完成" << endl;
		return 0;
	}
}

SOCKET socketBasic::socketGet()
{
	return s;
}







