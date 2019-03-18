#pragma once
//#include "pch.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <tchar.h>

using namespace std;

class Comms
{
private:

public:
	string dllError = "The Winsock dll not found!";

	Comms();
	void Setup();
	~Comms();

	SOCKADDR_STORAGE from;
	int retval, fromlen, socket_type;
	char servstr[NI_MAXSERV], hoststr[NI_MAXHOST];
	SOCKET Socket, acceptSocket;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	const int port = 55555;
};

