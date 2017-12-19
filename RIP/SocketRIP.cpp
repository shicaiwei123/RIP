#include "SocketRIP.h"

SocketRIP::SocketRIP()
{

}

bool SocketRIP::isACK = false;
bool SocketRIP::stopWait = false;

int SocketRIP::begin(bool StopWait)
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
int SocketRIP::socketConnect(const char *ip, int port)
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

int SocketRIP::recvSocket(char *RecvData, int Length)
{
	int ret;
	memset(RecvData, 0, Length);     //��ս��ջ���
	while (true)
	{
		ret = recv(s, RecvData, Length, 0);
		if (ret > 0)
		{
			cout << "�յ�һ������" << endl;
			if (stopWait)
			{
				int isequal = strcmp(RecvData, "ACK");  //����յ�ACK���Ǿ͸ı����
				if (isequal == 0)
				{
					isACK = true;
					continue;                           //�յ�ACK����������
				}

				else                                     //������ǣ��Ǿͻظ�ACK
				{

					send(s, "ACK", 3, 0);
				}

			}
			return 0;
		}
	}

}

int SocketRIP::recvSocket(char *RecvData, int Length, const char *FromIp, int Port)
{
	int ret;
	memset(RecvData, 0, Length);     //��ս��ջ���
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
			cout << "�յ�һ������" << endl;
			if (stopWait)
			{
				int isequal = strcmp(RecvData, "ACK");  //����յ�ACK���Ǿ͸ı����
				if (isequal == 0)
				{
					isACK = true;
					continue;                           //�յ�ACK����������
				}
				
				else                                     //������ǣ��Ǿͻظ�ACK
				{
					sendto(s, "ACK", 3, 0, (sockaddr *)&serAddr, len);
					return 0;
				}

			}
			return 0;

		}
	
	}
	return 0;

}

int SocketRIP::recvMessage(RIPMessage *ripMessage)
{
	char recvData[4096];
	recvSocket(recvData, 4096);
	memcpy(ripMessage, recvData, sizeof(RIPMessage));
	return 0;
}

int SocketRIP::recvMessage(RIPMessage *ripMessage, const char *FromIp, int Port)
{
	char recvData[4096];
	recvSocket(recvData, 4096, FromIp, Port);
	memcpy(ripMessage, recvData, sizeof(RIPMessage));
	return 0;
}


void SocketRIP::sendSocket(char *SendData, int Length)
{
	int err;
	bool endFlag = false;
	if (stopWait)
	{
		send(s, SendData, Length, 0);
		//clock.run();
		while (!isACK)
		{
			isACK = false;
			//endFlag = clock.getEndFlag();
			//if (endFlag)
			//{
			//	send(s, SendData, Length, 0);
			//	clock.set(0, 0, 2);
			//	clock.run();
			//}
			send(s, SendData, Length, 0);
			Sleep(2000);

		}

	}
	else
	{
		err = send(s, SendData, Length, 0);
		if (err == -1)
		{
			cout << "����ʧ��" << endl;
		//	return -1;
		}
	//	return 0;
	}
//	return 0;

}

void SocketRIP::sendSocket(char* SendData, int Length, const char *ToIp, int Port)
{
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(Port);
	serAddr.sin_addr.S_un.S_addr = inet_addr(ToIp);
	int len = sizeof(serAddr);
	bool endFlag = false;
	if (stopWait)
	{
		isACK = false;
		sendto(s, SendData, Length, 0, (sockaddr *)&serAddr, len);
		//clock.begin(0, 0, 2);
		//clock.run();
		while (!isACK)
		{
			//endFlag = clock.getEndFlag();
			//if (endFlag)
			//{
			//	sendto(s, SendData, Length, 0, (sockaddr *)&serAddr, len);
			//	clock.set(0, 0, 2);
			//	clock.run();
			//}
			sendto(s, SendData, Length, 0, (sockaddr *)&serAddr, len);
			Sleep(2000);

		}
		//return 0;

	}
	else
	{
		int setNum = sendto(s, SendData, Length, 0, (sockaddr *)&serAddr, sizeof(serAddr));
		if (setNum > 0)
		{
			cout << "�������" << endl;
			//return 0;
		}
	}

}

void SocketRIP::sendMessage(RIPMessage *ripMessage)
{
	char sendData[1024];
	memcpy(sendData, ripMessage, sizeof(RIPMessage));
	sendSocket( sendData, 1024);
}

void SocketRIP::sendMessage(RIPMessage *ripMessage, const char *ToIp, int Port)
{
	char sendData[1024];
	memcpy(sendData, ripMessage, sizeof(RIPMessage));
	sendSocket(sendData, 1024, ToIp, Port);
}

void SocketRIP::setSocket(SOCKET S)
{
	s = S;
}