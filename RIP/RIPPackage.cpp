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
	header.fromIP.address = ipTable[0].address;
	ripMessage.header.command = Command;
	ripMessage.header.fromIP.address = ipTable[0].address;
	ripMessage.header.version = Version;
}

void RIPPacket::setData(MessageData *Data)
{
	memcpy(messageData, Data, 10 * sizeof(MessageData));
	memcpy(ripMessage.messageData, Data, 10 * sizeof(MessageData));

}

void RIPPacket::setMessage(MessageData *Data)
{
	ripMessage.header = header;
	memcpy(ripMessage.messageData, Data, sizeof(ripMessage.messageData));
}

void RIPPacket::getData(MessageData *Data)
{
	Data = messageData;
}

void RIPPacket::getMessage(RIPMessage *RipMessage)
{
	*RipMessage = ripMessage;
}

void RIPPacket::setIPTable(Address *IPTable)
{
	memcpy(ipTable, IPTable, sizeof(ipTable));
}