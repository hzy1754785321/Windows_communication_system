#ifndef __FUN_H__
#define __FUN_H__

#include <iostream>
#include <WinSock2.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib")

typedef struct _SockInfo
{
	SOCKET sock;
	int id;
}SockInfo;

DWORD WINAPI clientThread(LPVOID lpPaarameter);




#endif