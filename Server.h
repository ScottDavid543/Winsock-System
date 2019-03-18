#pragma once
#include "Comms.h"

class Server : public Comms
{
private:

public:
	bool bindSuccess = false;

	Server();
	void Bind();
	void Recieve();
	void Send();
	~Server();
};

