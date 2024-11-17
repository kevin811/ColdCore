#ifndef cs_it
#define cs_it

#include <iostream>
#include <windows.h>
using namespace std;
struct POS
{
	int x = 0;
	int y = 0;
};

struct more
{
	int num = -1;			//整数型
	string str = "None";	//字符型
	int time = -1;			//时间（戳）
	string path = "None";	//路径
	HWND hwnd = (HWND)-1;	//窗口句柄
	POS pos{ -1, -1 };		//坐标、大小
};
#endif