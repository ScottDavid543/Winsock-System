#include "stdafx.h"
#include "Server.h"


Server::Server()
{

}


void Server::Bind() {
	try {
		sockaddr_in service;
		service.sin_family = AF_INET;
		InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
		service.sin_port = htons(port);
		if (bind(Socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
			//cout << "bind() failed: " << WSAGetLastError() << endl;
			throw "bind() failed: ";
			closesocket(Socket);
			WSACleanup();
			bindSuccess = false;
			return;
		}
		else {
			cout << "bind() is OK!" << endl;
			bindSuccess = true;
		}

		if (listen(Socket, 1) == SOCKET_ERROR) { 
			//cout << "listen(): Error listening on socket " << WSAGetLastError() << endl; 
			throw "listen(): Error listening on socket ";
			closesocket(Socket);
			WSACleanup();
			return;
		}
		else cout << "listen() is OK, im waiting for connections..." << endl;

		fromlen = sizeof(socket_type);
		retval = getsockopt(Socket, SOL_SOCKET, SO_TYPE, (char *)&socket_type, &fromlen);
		fromlen = sizeof(from);
		acceptSocket = accept(Socket, (SOCKADDR*)&from, &fromlen);
		if (acceptSocket == INVALID_SOCKET) {
			//cout << "accept failed: " << WSAGetLastError() << endl;
			throw "accept failed: ";
			WSACleanup();
			return;
		}
		retval = getnameinfo((SOCKADDR*)&from,
			fromlen,
			hoststr,
			NI_MAXHOST,
			servstr,
			NI_MAXSERV,
			NI_NUMERICHOST | NI_NUMERICSERV);
		if (retval != 0) {
			//cout << "getnameinfo failed: " << retval << endl;
			throw retval;
			WSACleanup();
			return;
		}

		cout << "Accepted connection from host " << hoststr << " and port " << servstr << endl;

		cout << "Accepted Connection" << endl;
	}
	catch (const char error[]) {
		cout << error << WSAGetLastError() << endl;
	}
	catch (int error) {
		cout << "getnameinfo failed: " << error << endl;
	}
}

void Server::Recieve() {
	try {
		char receiveBuffer[200] = "";
		int byteCount = recv(acceptSocket, receiveBuffer, 200, 0);
		if (byteCount < 0) {
			//printf("Server: error %Id.\n", WSAGetLastError());
			throw "Client: error &Id.\n";
			return;
		}
		else {
			printf("Received data : %s \n", receiveBuffer);
			if (receiveBuffer[0] == 'Q'&& receiveBuffer[1] == 'U'&& receiveBuffer[2] == 'I'&& receiveBuffer[3] == 'T') {
				WSACleanup();
				exit(0);
			}
		}
	}
	catch (const char error[]) {
		cout << error << WSAGetLastError << endl;
	}
}
void Server::Send() {
	try {
		char buffer[200];
		printf("Enter your message ");
		cin.getline(buffer, 200);
		int byteCount = send(acceptSocket, buffer, 200, 0);
		if (byteCount == SOCKET_ERROR) {
			//printf("Client send error %Id.\n", WSAGetLastError());
			throw "Server send error %Id.\n";
			return;
		}
		else {
			printf("Server: sent %Id bytes \n", byteCount);
		}
	}
	catch (const char error[]) {
		cout << error << WSAGetLastError << endl;
	}
}

Server::~Server()
{
}
