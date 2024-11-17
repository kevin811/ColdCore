#ifndef cs_init
#define cs_init

#include <windows.h>
#include <stdio.h>
using namespace std;
#define ANTIVIRUS_CODE "X5O!P%@AP[4\\PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*"

// 一些宏定义
#ifdef csdef
	#define forever while(true)
	#define SYSTEMTIME TIME
	#define GetLocalTime GetTime
	#define SetLocalTime SetTime
	#define YES true
	#define NO false
	#define NEXTLINE '\n'
	#define TAB '\t'
	#define REMOVE '\r' // ?
	#define Return(value) return value
	#define var auto
	#define HWND_CONSOLE GetConsoleWindow()
	#define CONSOLE_HWND HWND_CONSOLE
	#define ll LONGLONG
	#define and &&
	#define or ||
#endif 


#endif