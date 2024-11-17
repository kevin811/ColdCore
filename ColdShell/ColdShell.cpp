#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <map>
#include <string>
#include <shlobj.h>
#define csdef
#include "cs_init.h"
#include "cs_it.h"
#include "cs_color.h"
#include "cs_api.h"
#include "cs_web.h"

using namespace std;

bool OutPut = true;
more it;

#define version "0.1a";
#define name "ColdShell"

void OutPutTitle()
{
	SetColor(Color::Yellow, 0);
	cout << name << " - By ColdCore";
	if (IsAdmin())
	{
		SetColor(Color::Red, Color::Black);
		cout << "\n已获得管理员权限！";
	}
	SetColor(Color::Green, 0);
	cout << "\n版本：" << version;
	SetColor(Color::White, 0);
	cout << "\n一切准备完毕，请输入您的指令！";
}

int GetSpaceCount(string str)
{
	int c = 0;
	for (int i = 0; i <= str.length(); i++)
	{
		if (str[i] == ' ')
		{
			c++;
		}
	}
	return c;
}

void mythware(string argu[])
{
	if ("kill" == argu[0])
	{
		Execute("taskkill /f /im StudentMain.exe");
	}
}
int stoi2(string str, int failRet=-1)
{
	int ret = failRet;
	try
	{
		ret = stoi(str);
	}
	catch (const std::exception&)
	{
		
	}
	return ret;
}

void delay(string argu[])
{
	int time = stoi2(argu[0]);
	Sleep(time);
}

void showIt(string argu[])
{
	SetColor(Color::White, 0);

	cout << "\n类型：int [整数]";
	cout << "\n值：" << it.num;
	cout << endl << endl;

	cout << "\n类型：string [字符串]";
	cout << "\n值：" << it.str;
	cout << endl << endl;

	cout << "\n类型：hwnd [窗口句柄]";
	cout << "\n值：" << it.hwnd;
	cout << endl << endl;

	cout << "\n类型：path [路径]";
	cout << "\n值：" << it.path;
	cout << endl << endl;

	cout << "\n类型：time [时间戳]";
	cout << "\n值：" << it.time;
	cout << endl << endl;

	cout << "\n类型：pos [坐标]";
	cout << "\n值：" << "x=" << it.pos.x << "    " << "y=" << it.pos.y;
	cout << endl;
}
void setIt_int(string argu[])
{
	it.num = stoi2(argu[0]);
}

void setIt_str(string argu[])
{
	it.str = argu[0];
}

void stredit(string argu[])
{
	if ("add" == argu[0])
	{
		it.str += argu[1];
	}
	else if ("del" == argu[0])
	{
		int start = stoi2(argu[1], 0);
		int end = stoi2(argu[2], it.str.length());
		it.str.erase(start, end);
	}
	else if ("clear" == argu[0])
	{
		it.str = "";
	}
}

void check_hwnd(string argu[])
{
	HWND hwnd;
	if ("it" != argu[0])
		hwnd = HWND(stoi2(argu[0]));
	else
	{
		if((HWND)-1 != it.hwnd)
			hwnd = it.hwnd;
		else
		{
			SetColor(Color::Red);
			cout << "[E] hwnd 类型的 it 暂时没有值";
		}
	}

}

void listip(string argu[])
{
	vector<string> ip = GetCurrentIPAddresses();
	SetColor(Color::Yellow, 0);
	cout << "\n本机ip地址：";
	SetColor(Color::White, 0);
	for (int i = 0; i < ip.size(); i++)
	{
		cout << "\n    " << ip[i] << endl;
	}
}

void cmd(string argu[])
{
	system("cmd.exe");
}

void taskmgr(string argu[])
{
	system("taskmgr.exe");
}

void regedit(string argu[])
{
	system("regedit.exe");
}

void notepad(string argu[])
{
	system("notepad.exe");
}

void calc(string argu[])
{
	system("calc.exe");
}

void gpedit(string argu[])
{
	system("gpedit.msc");
}

void echo(string argu[])
{
	cout << endl << argu[0];
}

int main()
{
	system("chcp 936");
	//init();
	OutPutTitle();
	while (true)
	{
		SetConsoleTitleA("ColdShell");
		SetColor(Color::White, Color::Black);

		while (!OutPut)
		{
			;
		}

		cout << "\n==> ";

		SetColor(Color::Brown, Color::Black);
		string str, line;
		getline(cin, line);

		str = UTF8ToGB(line.c_str()).c_str();
		//cout << "str= " << str << "len(str)=" << str.length() << endl;
		string* strs;
		SetColor(Color::White, Color::Black);


		string command = "";
		//cout << GetSpaceCount(str);
		
		string argu[50] {};

		int SpaceCount = 0;
		for (int j = 0; j < str.length(); j++)
		{
			if (str[j] == ' ')
			{
				SpaceCount++;
				continue;
			}

			if (SpaceCount == 0)
			{
				command += str[j];
				continue;
			}
			else
			{
				argu[SpaceCount - 1] += str[j];
				continue;
			}
		}
		using func = void(*)(string[]);

		map<string, func> funcMap = {
			// 功能
			//{"specPath", GetSpecPath}, {"specpath", GetSpecPath}
			{"mythware", mythware},
			{"sleep", delay}, {"delay", delay}, {"wait", delay},
			{"it", showIt},
			{"int", setIt_int},
			{"str", setIt_str}, {"strint", setIt_str},
			{"stredit", stredit},
			{"check", check_hwnd}, {"isok", check_hwnd}, {"ok", check_hwnd},
			{"getip", listip},
			{"cmd", cmd}, {"taskmgr", taskmgr}, {"regedit", regedit}, {"calc", calc}, {"gpedit", gpedit}, {"notepad", notepad},
			{"echo", echo}
		};
		if (funcMap.find(command) != funcMap.end())
		{
			funcMap[command](argu);
		}
		else
		{
			SetColor(Color::Red, 0);
			cout << "\ncommand '" << command << "' not found";
		}
		SetColor(Color::White, 0);
	}
}