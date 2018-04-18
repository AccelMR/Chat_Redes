#pragma once

#include <WS2tcpip.h>
#include <iostream>
#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

typedef void(*RecvMsg)(string);

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
	void ReceiveData();
	bool SendData(string userInput);

	void RunEnAlgunaPArte(RecvMsg RM);
	static DWORD  MsgThread (void* param);
	RecvMsg OnMessageRecieved;
};

