
#include "stdafx.h"
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS 50
using namespace std;
#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <winsock2.h>
#include <process.h>
#pragma comment(lib,"ws2_32.lib" )

unsigned int __stdcall  ServClient(void *data);
unsigned int __stdcall  ServClientTerminal(void *data);
int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	int iResult;
	sockaddr_in addr;
	SOCKET sock, client;
	int PORT = 2222;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	cout << "Home:\\Server>";
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult)
	{
		printf("WSA startup failed");
		return 0;
	}
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		printf("Invalid socket");
		return 0;
	}

	iResult = bind(sock, (sockaddr*)&addr, sizeof(sockaddr_in));

	if (iResult)
	{

		printf("bind failed %u", GetLastError());

		return 0;
	}

	iResult = listen(sock, SOMAXCONN);

	if (iResult)
	{

		printf("iResult failed %u", GetLastError());

		return 0;
	}

	while (client = accept(sock, 0, 0))
	{
		if (client == INVALID_SOCKET)
		{
			printf("invalid client socket", GetLastError());
			continue;
		}
		_beginthreadex(0, 0, ServClient, (void*)&client, 0, 0);
		_beginthreadex(0, 0, ServClientTerminal, (void*)&client, 0, 0);

	}


	return 0;
}

unsigned int __stdcall ServClient(void *data)
{
	SOCKET* client = (SOCKET*)data;
	SOCKET Client = *client;
	int ID = GetCurrentThreadId();
	char hash[10];
	char chunk[200];
	recv(Client, hash, 200, 0);
	int sizeofhash=0;
	int hashvalue = 0;
	for (sizeofhash = 0; hash[sizeofhash] != '\0'; sizeofhash++);
	for (int i = 0; i < sizeofhash; i++) 
	{
		hashvalue = (hashvalue * 10) + (hash[i]-48);
	}

	cout << "\nHome:\\Server>Name server " << ID << " connected!\n";
	while (recv(Client, chunk, 200, 0))
	{
		if (!strcmp(chunk, "exit")) {
			cout << "Home:\\Server>Name server " << ID << " left!\n";
			break;
		}
		cout << "Home:\\Server>Message from name server " << ID<< ": "<<chunk<< "\n";
	}
	return 0;
}

unsigned int __stdcall ServClientTerminal(void *data)
{
	SOCKET* client = (SOCKET*)data;
	SOCKET Client = *client;
	int ID = GetCurrentThreadId();
	char chunk[200];
	while (1)
	{
		
		cin >> chunk;
		cout << "Home:\\Server>Hey!";
	}
	return 0;
}