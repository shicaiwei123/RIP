#pragma once
#include<ctime>  
#include<iostream>  
#include <process.h>  
#include <windows.h>  
using std::cout;
using std::cin;
using std::endl;
using std::flush;

class Clock {
	int h;
	int m;
	int s;
	HANDLE m_handle[2];
	int handleCnt;
	int flag;
	bool endFlag;
	char mac[18];
public:
	void begin(int hour, int min, int sec); //初始化函数，初始设定租约时间为0:0:2，2s
	void set(int hour, int min, int sec);//set(int ,int ,int )  
	void tick();
	void show();
	friend DWORD WINAPI runFuction(LPVOID lpParameter);
	void run();
	bool getEndFlag();

};

