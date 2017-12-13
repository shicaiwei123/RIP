#include "RIPPackage.h"

RIPPacket::RIPPacket()
{

}

void RIPPacket::begin()
{
	memset(&header, 0, sizeof(header));
	memset(&messageData, 0, sizeof(messageData));
	memset(&ripMessage, 0, sizeof(ripMessage));
}

void RIPPacket::setHeader(uint8_t Command, uint8_t Version)
{
	header.command = Command;
	header.version = Version;
}

void RIPPacket::setData(MessageData *Data)
{
	messageData = *Data;
}

void RIPPacket::setMessage(MessageData *Data)
{
	ripMessage.header = header;
	memcpy(ripMessage.messageData, Data, sizeof(ripMessage.messageData));
}

void RIPPacket::getData(MessageData *Data)
{
	*Data = messageData;
}

void RIPPacket::getMessage(RIPMessage *RipMessage)
{
	*RipMessage = ripMessage;
}