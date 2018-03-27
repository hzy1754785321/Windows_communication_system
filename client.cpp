#include "fun.h"

void main()
{
	WORD wVersionRequested;
	WSAData wsadata;
	int err;
	HANDLE hpthread = NULL;

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
	SOCKET sockclient = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrsrv;
	addrsrv.sin_addr.S_un.S_addr = inet_addr("172.20.10.10");
	addrsrv.sin_family = AF_INET;
	addrsrv.sin_port = htons(9000);
	connect(sockclient, (SOCKADDR*)&addrsrv, sizeof(SOCKADDR));
	SockInfo si;
	si.sock = sockclient;
	hpthread = CreateThread(NULL, 0, clientThread, (LPVOID)&si, 0, NULL);
	while (1)
	{
		char recvbuf[255];
		recvbuf[0] = '\n';
		int n = recv(sockclient, recvbuf, 255, 0);
		cout << "收到信息:" << recvbuf << endl;
	}
	closesocket(sockclient);
	WSACleanup();
}

DWORD WINAPI clientThread(LPVOID lpParameter)
{
	SockInfo* sockinfo = (SockInfo*)lpParameter;
	while (1)
	{
		char recvbuf[255];
		cin >> recvbuf;
		int ret = send(sockinfo->sock, recvbuf, 255, 0);
		if (ret == 0 || ret == SOCKET_ERROR)
		{
			cout << "send failed" << endl;
			return 0;
		}
	}
}