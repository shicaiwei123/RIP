#pragma once
/*�ͻ��˱��Ĵ�����*/
//��Ͽͻ������󣬻��ڱ��Ĵ������������һЩ����������
//��װ��ѡ���еı�������
//���ķ�װ��ѡ���ṩ�����ֽӿڣ�������Ҫ����ָ���������͵�����
#include "RIPDataStruct.h"
class RIPPacket
{
public:
	RIPPacket();
	void begin();
	void setHeader(uint8_t Command, uint8_t Version); //�趨ͷ��
	void setData(MessageData *Data);				  //�趨����
	void setMessage(MessageData *Data);               //�趨����
	void getData(MessageData *Data);                  //��ȡ����
	void getMessage(RIPMessage *RipMessage);          //��ȡ����


private:
	
	RIPHeader header;
	MessageData messageData;
	RIPMessage ripMessage;
};


