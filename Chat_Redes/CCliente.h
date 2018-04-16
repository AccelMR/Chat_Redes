#pragma once

#include <WS2tcpip.h>
#include <iostream>
#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

class CCliente
{
private:
	int port;
	string ipAdress;
	SOCKET sock;
public:
	CCliente(wstring ipAdress, int port);
	~CCliente();

	bool initilize();
	string ReceiveData(string userInput);
};

