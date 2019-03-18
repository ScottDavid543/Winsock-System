#pragma once
#include "Comms.h"
class Client: public Comms
{
public:
	bool connectSuccess = false;

	Client();
	void Connect();
	void Recieve();
	void Send();
	~Client();
};

