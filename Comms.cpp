#include "stdafx.h"
#include "Comms.h"


Comms::Comms()
{

}

void Comms::Setup() 
{	
	try {
		wsaerr = WSAStartup(wVersionRequested, &wsaData);

		if (wsaerr != 0) {
			throw(dllError);
			//cout << "The Winsock dll not found!" << endl;			
		}
		else {
			cout << "The Winsock dll found!" << endl;
			cout << "The Status: " << wsaData.szSystemStatus << endl;
		}

		Socket = INVALID_SOCKET;
		Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (Socket == INVALID_SOCKET) {
			//cout << "Error at socket(): " << WSAGetLastError() << endl;
			throw"Error at socket(): ";
			WSACleanup();
			return;
		}
		else {
			cout << "socket() is OK!" << endl;
		}
	}
	catch (string error) {
		cout << "Exception: " << error << endl;
	}
	catch (const char error[]) {
		cout << "Exception: " << error << WSAGetLastError() << endl;
	}
}



Comms::~Comms()
{
}
