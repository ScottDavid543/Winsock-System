// Task2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Comms.h"
#include "Client.h"
#include "Server.h"

#define servDef  
//#define cliDef

using namespace std;

int main()
{
#ifdef servDef
	// Configure a Server START
	cout << "		__SETTING UP SERVER__" << endl;
	Server* server = new Server;
	server->Setup();
	server->Bind();
	while (server->bindSuccess == true) {
		server->Recieve();
		server->Send();
	}
	// Configure a Server END
#endif

#ifdef cliDef
	cout << "		__SETTING UP CLIENT__" << endl;
	// Configure a Client START
	Client* client = new Client;
	client->Setup();
	client->Connect();
	while (client->connectSuccess == true) {
		client->Send();
		client->Recieve();
	}
	// Configure a Client END
#endif

	system("pause");
	WSACleanup();
    return 0;
}

