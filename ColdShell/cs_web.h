#ifndef cs_web
#define cs_web

#include <bits/stdc++.h>
#include <windows.h>
#include <vector>
using namespace std;
#pragma comment(lib, "WS2_32")
vector<string> GetCurrentIPAddresses()
{
	vector<string> cur_ips{};
	WORD v = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(v, &wsaData); // ¼ÓÔØÌ×½Ó×Ö¿â     	
	int i = 0;
	struct hostent* phostinfo = gethostbyname("");
	for (i = 0; NULL != phostinfo && NULL != phostinfo->h_addr_list[i]; ++i)
	{
		char* pszAddr = inet_ntoa(*(struct in_addr*)phostinfo->h_addr_list[i]);
		cur_ips.push_back(string(pszAddr));
	}
	WSACleanup();
	return cur_ips;
}


#endif
