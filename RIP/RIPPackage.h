#pragma once
/*客户端报文处理类*/
//结合客户端需求，基于报文处理基类增加了一些方法和数据
//封装了选项中的报文类型
//报文封装和选项提供了两种接口，兼容需要生成指定报文类型的需求
#include "RIPDataStruct.h"
class RIPPacket
{
public:
	RIPPacket();
	void begin();
	void setHeader(uint8_t Command, uint8_t Version); //设定头部
	void setData(MessageData *Data);				  //设定数据
	void setMessage(MessageData *Data);               //设定报文
	void getData(MessageData *Data);                  //获取数据
	void getMessage(RIPMessage *RipMessage);          //获取报文


private:
	
	RIPHeader header;
	MessageData messageData;
	RIPMessage ripMessage;
};


