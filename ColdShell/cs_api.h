#ifndef cs_winapi
#define cs_winapi

#include <bits/stdc++.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#define ADMIN
using namespace std;

bool IsAdmin()
{
	BOOL b;
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;
	b = AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdministratorsGroup);
	if (b)
	{
		if (!CheckTokenMembership(NULL, AdministratorsGroup, &b))
		{
			b = FALSE;
		}
		FreeSid(AdministratorsGroup);
	}

	return (b);
}

POINT GetPos()
{
	POINT pt;
	GetCursorPos(&pt); //获取鼠标指针位置到pt
	return pt;
}

string GBKToUTF8(const std::string& strGBK)
{
	string strOutUTF8 = "";
	WCHAR* wchar_array;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	wchar_array = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, wchar_array, n);
	n = WideCharToMultiByte(CP_UTF8, 0, wchar_array, -1, NULL, 0, NULL, NULL);
	char* char_array = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, wchar_array, -1, char_array, n, NULL, NULL);
	strOutUTF8 = char_array;
	delete[] wchar_array;
	wchar_array = NULL;
	delete[] char_array;
	char_array = NULL;
	return strOutUTF8;
}

std::string UTF8ToGB(const char* str)
{
	std::string result;
	WCHAR* strSrc;
	LPSTR szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

string UserName()
{
	char currentUser[256] = { 0 };
	DWORD dwSize_currentUser = 256;
	GetUserName(
		currentUser,			// 接收当前登录用户的用户名
		&dwSize_currentUser		// 缓冲区大小
	);
	return (string)currentUser;
}

#define ME_LEFT MOUSEEVENTF_LEFTDOWN
#define ME_RIGHT MOUSEEVENTF_RIGHTDOWN
#define ME_WHEEL 3
#define ME_MIDDLE MOUSEEVENTF_MIDDLEDOWN

void MouseP(UINT uLR = ME_LEFT)	//按下鼠标 
{
	switch (uLR) {
	case ME_LEFT:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); //左键按下
		break;
	case ME_RIGHT:
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0); //右键按下
		break;
	case ME_MIDDLE:
		mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0); //滚轮按下
		break;
	default:
		break;
	}
	return;
}

void MouseR(UINT uLR = ME_LEFT)	//松开鼠标 
{
	switch (uLR) {
	case ME_LEFT:
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); //左键松开
		break;
	case ME_RIGHT:
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0); //右键松开
		break;
	case ME_MIDDLE:
		mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0); //滚轮松开
		break;
	default:
		break;
	}
	return;
}

#define MouseD MouseP
#define MouseU MouseR

void Click(UINT uLR = ME_LEFT, DWORD dwInternalGap = 5) {	//单击 
	switch (uLR) {
	case ME_LEFT:
		MouseP();
		Sleep(dwInternalGap);
		MouseR(); //左键
		break;
	case ME_RIGHT:
		MouseP(ME_RIGHT);
		Sleep(dwInternalGap);
		MouseR(ME_RIGHT); //右键
		break;
	case ME_MIDDLE:
		MouseP(ME_MIDDLE);
		Sleep(dwInternalGap);
		MouseR(ME_MIDDLE); //滚轮
		break;
	default:
		break;
	}
	return;
}

VOID Execute(LPCSTR lpFile, LPCSTR lpArguments = NULL, INT iCmdShow = SW_HIDE) {
	ShellExecute(0, "open", lpFile, lpArguments, "", iCmdShow);
	return;
}
BOOL SetPrivilege(LPCSTR lpPrivilegeName, bool fEnable = TRUE)
{ 							//SE_XXX_NAME
	HANDLE hToken;
	TOKEN_PRIVILEGES NewState;
	LUID luidPrivilegeLUID;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		/*If opening token failed...*/
		return FALSE;
	}

	if (fEnable == FALSE) /*We disable all the privileges... */
	{
		if (!AdjustTokenPrivileges(hToken, TRUE, NULL, NULL, NULL, NULL))
		{
			return FALSE;
		}
		else return TRUE;
	}
	/*Look up the LUID value of the privilege... */
	LookupPrivilegeValue(NULL, lpPrivilegeName, &luidPrivilegeLUID);
	NewState.PrivilegeCount = 1;
	NewState.Privileges[0].Luid = luidPrivilegeLUID;
	NewState.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	/*Improve this process's privilege, so we can shut down the system next. */
	if (!AdjustTokenPrivileges(hToken, FALSE, &NewState, NULL, NULL, NULL))
	{
		return FALSE;
	}
	/*We should not only check if the improving was successed... */
	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		return FALSE;
	}
	return TRUE;
}

bool ADMIN SetPrivilegeAndOutput(LPCSTR lpPrivilegeName, BOOL fEnable = TRUE)
{
	bool r = SetPrivilege(lpPrivilegeName, fEnable);
	if (r)
	{
		SetColor(Color::Green, 0);
		cout << "* ";
		SetColor(Color::Cyan, 0);
		cout << lpPrivilegeName;
		SetColor(Color::Green, 0);
		cout << " Privilege Set Success.\n";
		SetColor(Color::White, 0);
	}
	else
	{
		SetColor(Color::Red, 0);
		cout << "* ";
		SetColor(Color::Cyan, 0);
		cout << lpPrivilegeName;
		SetColor(Color::Red, 0);
		cout << " Privilege Set Fail.\n";
		SetColor(Color::White, 0);
	}
	return r;
}

int ADMIN GetAllPrivileges()
{
	int s = 0;
	s += SetPrivilege(SE_CREATE_TOKEN_NAME);
	s += SetPrivilege(SE_ASSIGNPRIMARYTOKEN_NAME);
	s += SetPrivilege(SE_LOCK_MEMORY_NAME);
	s += SetPrivilege(SE_INCREASE_QUOTA_NAME);
	s += SetPrivilege(SE_UNSOLICITED_INPUT_NAME);
	s += SetPrivilege(SE_MACHINE_ACCOUNT_NAME);
	s += SetPrivilege(SE_TCB_NAME);
	s += SetPrivilege(SE_SECURITY_NAME);
	s += SetPrivilege(SE_TAKE_OWNERSHIP_NAME);
	s += SetPrivilege(SE_LOAD_DRIVER_NAME);
	s += SetPrivilege(SE_SYSTEM_PROFILE_NAME);
	s += SetPrivilege(SE_SYSTEMTIME_NAME);
	s += SetPrivilege(SE_PROF_SINGLE_PROCESS_NAME);
	s += SetPrivilege(SE_INC_BASE_PRIORITY_NAME);
	s += SetPrivilege(SE_CREATE_PAGEFILE_NAME);
	s += SetPrivilege(SE_CREATE_PERMANENT_NAME);
	s += SetPrivilege(SE_BACKUP_NAME);
	s += SetPrivilege(SE_RESTORE_NAME);
	s += SetPrivilege(SE_SHUTDOWN_NAME);
	s += SetPrivilege(SE_DEBUG_NAME);
	s += SetPrivilege(SE_AUDIT_NAME);
	s += SetPrivilege(SE_SYSTEM_ENVIRONMENT_NAME);
	s += SetPrivilege(SE_CHANGE_NOTIFY_NAME);
	s += SetPrivilege(SE_REMOTE_SHUTDOWN_NAME);
	s += SetPrivilege(SE_UNDOCK_NAME);
	s += SetPrivilege(SE_SYNC_AGENT_NAME);
	s += SetPrivilege(SE_ENABLE_DELEGATION_NAME);
	s += SetPrivilege(SE_MANAGE_VOLUME_NAME);
	s += SetPrivilege(SE_IMPERSONATE_NAME);
	s += SetPrivilege(SE_CREATE_GLOBAL_NAME);
	s += SetPrivilege(SE_TRUSTED_CREDMAN_ACCESS_NAME);
	s += SetPrivilege(SE_RELABEL_NAME);
	s += SetPrivilege(SE_INC_WORKING_SET_NAME);
	s += SetPrivilege(SE_TIME_ZONE_NAME);
	s += SetPrivilege(SE_CREATE_SYMBOLIC_LINK_NAME);
	return s;
}

int ADMIN GetAllPrivilegesAndOutput()
{
	int s = 0;
	s += SetPrivilegeAndOutput(SE_CREATE_TOKEN_NAME);
	s += SetPrivilegeAndOutput(SE_ASSIGNPRIMARYTOKEN_NAME);
	s += SetPrivilegeAndOutput(SE_LOCK_MEMORY_NAME);
	s += SetPrivilegeAndOutput(SE_INCREASE_QUOTA_NAME);
	s += SetPrivilegeAndOutput(SE_UNSOLICITED_INPUT_NAME);
	s += SetPrivilegeAndOutput(SE_MACHINE_ACCOUNT_NAME);
	s += SetPrivilegeAndOutput(SE_TCB_NAME);
	s += SetPrivilegeAndOutput(SE_SECURITY_NAME);
	s += SetPrivilegeAndOutput(SE_TAKE_OWNERSHIP_NAME);
	s += SetPrivilegeAndOutput(SE_LOAD_DRIVER_NAME);
	s += SetPrivilegeAndOutput(SE_SYSTEM_PROFILE_NAME);
	s += SetPrivilegeAndOutput(SE_SYSTEMTIME_NAME);
	s += SetPrivilegeAndOutput(SE_PROF_SINGLE_PROCESS_NAME);
	s += SetPrivilegeAndOutput(SE_INC_BASE_PRIORITY_NAME);
	s += SetPrivilegeAndOutput(SE_CREATE_PAGEFILE_NAME);
	s += SetPrivilegeAndOutput(SE_CREATE_PERMANENT_NAME);
	s += SetPrivilegeAndOutput(SE_BACKUP_NAME);
	s += SetPrivilegeAndOutput(SE_RESTORE_NAME);
	s += SetPrivilegeAndOutput(SE_SHUTDOWN_NAME);
	s += SetPrivilegeAndOutput(SE_DEBUG_NAME);
	s += SetPrivilegeAndOutput(SE_AUDIT_NAME);
	s += SetPrivilegeAndOutput(SE_SYSTEM_ENVIRONMENT_NAME);
	s += SetPrivilegeAndOutput(SE_CHANGE_NOTIFY_NAME);
	s += SetPrivilegeAndOutput(SE_REMOTE_SHUTDOWN_NAME);
	s += SetPrivilegeAndOutput(SE_UNDOCK_NAME);
	s += SetPrivilegeAndOutput(SE_SYNC_AGENT_NAME);
	s += SetPrivilegeAndOutput(SE_ENABLE_DELEGATION_NAME);
	s += SetPrivilegeAndOutput(SE_MANAGE_VOLUME_NAME);
	s += SetPrivilegeAndOutput(SE_IMPERSONATE_NAME);
	s += SetPrivilegeAndOutput(SE_CREATE_GLOBAL_NAME);
	s += SetPrivilegeAndOutput(SE_TRUSTED_CREDMAN_ACCESS_NAME);
	s += SetPrivilegeAndOutput(SE_RELABEL_NAME);
	s += SetPrivilegeAndOutput(SE_INC_WORKING_SET_NAME);
	s += SetPrivilegeAndOutput(SE_TIME_ZONE_NAME);
	s += SetPrivilegeAndOutput(SE_CREATE_SYMBOLIC_LINK_NAME);
	return s;
}

#endif