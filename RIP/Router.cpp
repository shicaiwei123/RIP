#include "Router.h"

Router::Router()
{

}

void Router::begin(Address *IPTable, NetWork *Network)
{
	tableLen = 0;
	NetWorking::begin();
	RIPPacket::begin();
	setIPTable(IPTable);
	setNet(Network);
	setHeader(1, 2);
	initRouter();
	isFinish = true;

		
}

void Router::initRouter()
{
	bool finish = false;
	int i = 0;
	while (!finish)
	{
		if (netWork[i].mask == 0)
		{
			finish = true;
			break;
		}
		localTable[i].messageData.cost = 1;
		localTable[i].messageData.net = netWork[i];
		localTable[i].nextHop.address = 0;
		i++;

	}
	tableLen = i + 1;
	//����·�ɱ�󣬽����Ÿ��·�����Ϣ
	for (int i = 0; i < 10;i++)
	{
		memcpy(&sendRouter[i], &localTable[i].messageData, sizeof(MessageData));
	}
}

int Router::recvMessage()
{
	
	SocketRIP::recvMessage(&messageRecv);
	memcpy(recvRouter, messageRecv.messageData,sizeof(recvRouter));
	update();
	return 0;
}

int Router::recvMessage(const char *FromIp, int Port)
{
	isFinish = false;
	SocketRIP::recvMessage(&messageRecv, FromIp, Port);
	memcpy(recvRouter, messageRecv.messageData, sizeof(recvRouter));
	update();
	return 0;
}

int Router::update()
{
	int i = 0;
	bool isequal = false;
	while (1)
	{
		if (recvRouter[i].net.ip.address==0)  //���ݴ������
		{
			break;
		}
		//�����յ���·�ɱ���
		for (int j = 0; j < 10;j++)
		{
			if ((recvRouter[i].net.ip.address==localTable[j].messageData.net.ip.address)&&
				(recvRouter[i].net.mask == localTable[j].messageData.net.mask)
			) //IP������ͬ
			{
				if (localTable[j].messageData.cost>recvRouter[i].cost+1)      //���ԭ·�ɱ�����������
				{
					localTable[j].messageData.cost = recvRouter[i].cost + 1;
					localTable[j].nextHop = messageRecv.header.fromIP;
					isequal = true;
				}
				else   //���ͬһ�����������µĿ���Ҳû��С����ô�˳��˴�forѭ����
				{
					isequal = true;
					break;
				}
			}
		}
		if (!isequal)       //��������,���ӵ�����·�ɱ�
		{
			localTable[tableLen - 1].messageData.net = recvRouter[i].net;
			localTable[tableLen - 1].messageData.cost = recvRouter[i].cost + 1;
			localTable[tableLen - 1].nextHop = messageRecv.header.fromIP;
			tableLen++;
		}
		isequal = false;

		i++;
	}
	for (int i = 0; i < 10; i++)
	{
		memcpy(&sendRouter[i], &localTable[i].messageData, sizeof(MessageData));
	}
	return 0;
}


int Router::sendMessage()
{
	memset(&messageSend, 0, sizeof(messageSend));
	//��װ����
	setHeader(header.command,header.version);
	setData(sendRouter);
	getMessage(&messageSend);
	//����
	SocketRIP::sendMessage(&messageSend);
	return 0;

}

int Router::sendMessage(const char *ToIp, int Port)
{
	memset(&messageSend, 0, sizeof(messageSend));
	//��װ����
	setHeader(header.command, header.version);
	setData(sendRouter);
	getMessage(&messageSend);
	//����
	SocketRIP::sendMessage(&messageSend,ToIp,Port);
	return 0;
}

void Router::printfRouter()
{
	bool equalZero = false;
	int i=0;
	while (!equalZero)
	{
		if ((int)localTable[i].messageData.cost == 0)
		{
			equalZero = true;
			i = 0;
			break;
		}
		cout << "Ŀ��������" << endl;
		cout << (int)localTable[i].messageData.net.ip.seg[0] << ".";
		cout << (int)localTable[i].messageData.net.ip.seg[1] << ".";
		cout << (int)localTable[i].messageData.net.ip.seg[2] << ".";
		cout << (int)localTable[i].messageData.net.ip.seg[3] << ".";
		cout << "/";
		cout << (int)localTable[i].messageData.net.mask;
		cout << "----------cost:";
		cout << (int)localTable[i].messageData.cost << endl;
		i++;
	}

}

bool Router::getFinishFlag()
{
	return isFinish;
}