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
	int num = -1;			//������
	string str = "None";	//�ַ���
	int time = -1;			//ʱ�䣨����
	string path = "None";	//·��
	HWND hwnd = (HWND)-1;	//���ھ��
	POS pos{ -1, -1 };		//���ꡢ��С
};
#endif