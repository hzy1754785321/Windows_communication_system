#include "fun.h"

void main()
{
	WORD wVersionRequested;
	WSAData wsadata;
	HANDLE hpthread = NULL;
	int err;

	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsadata);
	if (err != 0)
	{
		cout << "bind failed" << endl;
		return;
	}
	if (LOBYTE(wsadata.wVersion) != 1 || HIBYTE(wsadata.wVersion) != 1)
	{
		WSACleanup();
		return;
	}
	SOCKET socksrv = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrsrv;
	addrsrv.sin_addr.S_un.S_addr = inet_addr("172.20.10.10");
	addrsrv.sin_family = AF_INET;
	addrsrv.sin_port = htons(9000);
	bind(socksrv, (SOCKADDR*)&addrsrv, sizeof(SOCKADDR));
	listen(socksrv, 20);
	int id = 0;
	SOCKADDR_IN addrclient;
	int len = sizeof(SOCKADDR);
	SOCKET tsock = accept(socksrv, (SOCKADDR*)&addrclient, &len);
	if (tsock == INVALID_SOCKET)
	{
		cout << "accept failed" << endl;
		return;
	}
	SockInfo si;
	si.sock = tsock;
	si.id = id;
	hpthread = CreateThread(NULL, 0, clientThread, (LPVOID)&si, 0, NULL);
	id++;

	//		SockInfo sk;
	while (1)
	{
		char recvbuf[255];
		cin >> recvbuf;
		int ret = send(si.sock, recvbuf, 255, 0);
		if (ret == 0 || ret == SOCKET_ERROR)
		{
			cout << "send failed" << endl;
			break;
		}
	}
	closesocket(socksrv);
	WSACleanup();
}

DWORD WINAPI clientThread(LPVOID lpParameter)
{
	SockInfo* sockinfo = (SockInfo*)lpParameter;
	while (1)
	{
		char recvbuf[255];
		recvbuf[0] = '\0';
		int nrecv = recv(sockinfo->sock, recvbuf, 255, 0);
		if (nrecv == 0 || nrecv == SOCKET_ERROR)
		{
			cout << "the" << sockinfo->id << "client has exit" << endl;
			return 0;
		}
		cout << "the" << sockinfo->id << "-time:" << "·¢ËÍÏûÏ¢:" <<recvbuf << endl;
	}
		return 0;
}