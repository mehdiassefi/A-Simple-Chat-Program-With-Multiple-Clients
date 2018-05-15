
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS 50
using namespace std;

#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <winsock2.h>
#include <process.h>
#pragma comment(lib,"ws2_32.lib" )
unsigned int __stdcall  ServClient(void *data);
int _tmain(int argc, _TCHAR* argv[])
{
	int port=2222;
	string PORT;
	PORT = "2222";
	WSADATA wsaData;
	int iResult;
	sockaddr_in addr;
	SOCKET sock;
	char hash[10];
	cout << "Home:\\Cleint>Please enter the port number(It's 2222): ";
	cin >> hash;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


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
	while (1)
	{
		iResult = connect(sock, (SOCKADDR*)&addr, sizeof(sockaddr_in));
		int i = 0;
		if (iResult)
		{
			system("cls");
			cout << "Home:\\Cleint>Connecing...";
			for (int cnt = 0; cnt <= (i % 3); cnt++)cout << ".";
		}
		else
		{
			cout << "\nHome:\\Cleint>Connection succed!\n";
			cout << "Home:\\Cleint>";
			break;
		}
	}
	char ptr[100];
	send(sock, hash, sizeof(hash), 0);
	while(1)
	{
		
		int idx = 0;
		char tmp[100];
		cin >> tmp;
		
		cout << "Home:\\Cleint>";
		if (!strcmp(tmp, "exit"))
		{
			send(sock, tmp, sizeof(ptr), 0);
			Sleep(1000);
			break;
		}
		send(sock, tmp, sizeof(ptr), 0);	
	}
	closesocket(sock);
	return 0;
}