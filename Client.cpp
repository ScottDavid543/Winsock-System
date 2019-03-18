#include "stdafx.h"
#include "Client.h"


Client::Client()
{
}

void Client::Connect()
{
	try {
		sockaddr_in clientService;
		clientService.sin_family = AF_INET;
		InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
		clientService.sin_port = htons(port);
		if (connect(Socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
			//cout << "Client: connect() - Failed to connect." << endl;
			throw "Client: connect() - Failed to connect.";
			WSACleanup();
			connectSuccess = false;
			return;
		}
		else {
			cout << "Client: connect() is OK." << endl;
			cout << "Client: Can start sending and receiving data..." << endl;
			cout << "Client: Type ... QUIT ... to terminate..." << endl;
			connectSuccess = true;
		}
	}
	catch (const char error[]) {
		cout << error << endl;
	}
}
void Client::Recieve() {
	try {
		char receiveBuffer[200] = "";
		int byteCount = recv(Socket, receiveBuffer, 200, 0);
		if (byteCount < 0) {
			//printf("Server: error %Id.\n", WSAGetLastError());
			throw "Server: error %Id.\n";
			return;
		}
		else {
			printf("Received data : %s \n", receiveBuffer);
		}
	}
	catch (const char error[]) {
		cout << error << WSAGetLastError << endl;
	}
}
void Client::Send() {
	try {
		char buffer[200];
		printf("Enter your message ");
		cin.getline(buffer, 200);
		int byteCount = send(Socket, buffer, 200, 0);
		if (byteCount == SOCKET_ERROR) {
			//printf("Client send error %Id.\n", WSAGetLastError());
			throw "Client send error %Id.\n";
			return;
		}
		else {
			printf("Client: sent %Id bytes \n", byteCount);
			if (buffer[0] == 'Q'&& buffer[1] == 'U'&& buffer[2] == 'I'&& buffer[3] == 'T') {
				WSACleanup();
				exit(0);
			}
		}
	}
	catch (const char error[]) {
		cout << error << WSAGetLastError << endl;
	}
}

Client::~Client()
{
}
