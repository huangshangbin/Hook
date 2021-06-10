#include <iostream>
#include <string>

#include <WinSock2.h>
#include <Windows.h>
#include "Tlhelp32.h"
#include <Iphlpapi.h>



#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

using namespace std;

#include <hook/HookLoader.h>

int _stdcall mySend(SOCKET s, const char *buf, int len, int flags)
{
	cout << "hook_send function" << endl;

	return 0;
}

int main()
{
	string str;
	cin >> str;

	SOCKET clientSocket = NULL;
	string data = "huang";
	::send(clientSocket, data.c_str(), data.length(), 0);
	cout << "first GetLastError = " << GetLastError() << endl;

	HookLoader sendHook(&send, &mySend);
	sendHook.enable();

	SetLastError(0);
	::send(clientSocket, data.c_str(), data.length(), 0);
	cout << "second GetLastError = " << GetLastError() << endl;

	sendHook.disable();

	SetLastError(0);
	::send(clientSocket, data.c_str(), data.length(), 0);
	cout << "third GetLastError = " << GetLastError() << endl;
	

	cin >> str;

	return 0;
}