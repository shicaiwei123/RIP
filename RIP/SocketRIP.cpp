#include "SocketRIP.h"

SocketClient::SocketClient()
{

}

bool SocketClient::isACK = false;
bool SocketClient::stopWait = false;

int SocketClient::begin(bool StopWait)
{
	stopWait = StopWait;
	clock.begin(0,0,2);
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return -1;
	}
	return 0;
}
int SocketClient::socketConnect(const char *ip, int port)
{
	int err;
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port);
	serAddr.sin_addr.S_un.S_addr = inet_addr(ip);
	err = connect(s, (sockaddr *)&serAddr, sizeof(serAddr));
	if(err==SOCKET_ERROR)
	{
		printf("connect error !");
		closesocket(s);
		return -1;
	}
	return 0;
}

int SocketClient::recvSocket(char *RecvData, int Length)
{
	int ret;
	memset(RecvData, 0, Length);     //清空接收缓存
	while (true)
	{
		ret = recv(s, RecvData, Length, 0);
		if (ret > 0)
		{
			cout << "收到一个数据" << endl;
			if (stopWait)
			{
				int isequal = strcmp(RecvData, "ACK");  //如果收到ACK，那就改变变量
				if (isequal == 0)
					isACK = true;
				else                                     //如果不是，那就回复ACK
				{
					send(s, "ACK", 3, 0);
				}

			}
			return 0;
		}
	}

}

int SocketClient::recvSocket(char *RecvData, int Length, const char *FromIp, int Port)
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
			if (stopWait)
			{
				int isequal = strcmp(RecvData, "ACK");  //如果收到ACK，那就改变变量
				if (isequal == 0)
					isACK = true;
				else                                     //如果不是，那就回复ACK
				{
					sendto(s, "ACK", 3, 0, (sockaddr *)&serAddr, len);
				}

			}
			return 0;
		}
	}
	return 0;

}

void SocketClient::sendSocket(char *SendData, int Length)
{
	int err;
	bool endFlag = false;
	if (stopWait)
	{
		send(s, SendData, Length, 0);
		clock.run();
		while (!isACK)
		{
			endFlag = clock.getEndFlag();
			if (endFlag)
			{
				send(s, SendData, Length, 0);
				clock.set(0, 0, 2);
				clock.run();
			}

		}

	}
	else
	{
		err = send(s, SendData, Length, 0);
		if (err == -1)
		{
			cout << "发送失败" << endl;
		//	return -1;
		}
	//	return 0;
	}
//	return 0;

}

void SocketClient::sendSocket(char* SendData, int Length, const char *ToIp, int Port)
{
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(Port);
	serAddr.sin_addr.S_un.S_addr = inet_addr(ToIp);
	int len = sizeof(serAddr);
	bool endFlag = false;
	if (stopWait)
	{
		sendto(s, SendData, Length, 0, (sockaddr *)&serAddr, len);
		clock.begin(0, 0, 2);
		clock.run();
		while (!isACK)
		{
			endFlag = clock.getEndFlag();
			if (endFlag)
			{
				sendto(s, SendData, Length, 0, (sockaddr *)&serAddr, len);
				clock.set(0, 0, 2);
				clock.run();
			}

		}
		//return 0;

	}
	else
	{
		int setNum = sendto(s, SendData, Length, 0, (sockaddr *)&serAddr, sizeof(serAddr));
		if (setNum > 0)
		{
			cout << "发送完成" << endl;
			//return 0;
		}
	}

}

void SocketClient::setSocket(SOCKET S)
{
	s = S;
}