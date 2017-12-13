#pragma once
//socket的基类，包含了socket的一些基本方法
//初始化，创建套接字
#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib")   //连接ws2_32.lib库.只要程序中用到Winsock API 函数，都要用到 Ws2_32.lib  
#include<stdio.h>
#include <string.h>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
class socketBasic
{
private:
	int verA;
	int verB;
	int protocol;
protected:
	SOCKET s;  //属于自己套接字
public:
	socketBasic();//构造函数
	int begin(bool StopWait);  	//初始化WSA
	int socketCreate(int protocol);//创建基础socket套接字
	int bindSocket(char *Ip, int Port); //绑定套接字地址
	int recvSocket(char *RecvData, int Length);//接收信息
	int recvSocket(char *RecvData, int Length, const char *FromIp, int Port);
	int sendSocket(char *SendData, int Length);//发送信息
	int sendSocket (char* SendvData, int Length, const char *ToIp, int Port);
	SOCKET socketGet();  //获取创建的套接字


};
