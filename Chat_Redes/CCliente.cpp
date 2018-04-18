#include "stdafx.h"
#include "CCliente.h"


CCliente::CCliente(wstring ipAdress, int port):
	port(port)
{
	wchar_t* buffer;

	// Toma el tamaño necesario para crear el arreglo de caracteres.  wcslen documentación  https://msdn.microsoft.com/en-us/library/78zh94ax.aspx?f=255&MSPPError=-2147217396
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, ipAdress.c_str(), (int)wcslen(ipAdress.c_str()), NULL, 0, NULL, NULL);

	//Genera un string del tamaño especificado por usuario y lo llena con caracteres del alfabeto    http://www.cplusplus.com/reference/cstdlib/malloc/ 
	//char* strTo = (char*)malloc((size_needed + 1) * sizeof(char));
	char* strTo = new char[size_needed + 1];

	// Convierte la linea de caracteres y lo almacena en la hecha previamente 
	WideCharToMultiByte(CP_UTF8, 0, ipAdress.c_str(), (int)wcslen(ipAdress.c_str()), strTo, size_needed, NULL, NULL);
	strTo[size_needed] = '\0';
	this->ipAdress = strTo;
}


CCliente::~CCliente()
{
}

bool CCliente::initilize()
{
	// Initialize win sock
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);

	if (wsResult != 0) {
		cerr << "Can't start winsock Err#" << endl;
		return false;
	}

	// Create socket AF_INET6 is to use IPV6
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cerr << "Can't create socket, Err#" << WSAGetLastError() << endl;
		return false;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAdress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		cerr << "Can't connect to server, Err#" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return false;
	}
	return true;
}

bool CCliente::SendData(string userInput)
{
	int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	if (sendResult != SOCKET_ERROR) {
		return true;
	}
	else return false;
}

void CCliente::ReceiveData()
{
	while (true)
	{
		char buff[4096];
		// Send the text	
		ZeroMemory(buff, 4096);
		int bytesRecived = recv(sock, buff, 4096, 0);
		if (bytesRecived > 0) {
			OnMessageRecieved(string(buff, 0, bytesRecived));
		}
	}
}

void CCliente::RunEnAlgunaPArte(RecvMsg RM)
{
	this->OnMessageRecieved = RM;
	DWORD threadID_1;
	HANDLE thread1 = CreateThread(
		nullptr,
		0,
		(LPTHREAD_START_ROUTINE)MsgThread,
		this,
		0,
		&threadID_1);
}

DWORD  CCliente::MsgThread(void* param)
{
	CCliente* nClient = (CCliente*)param;
	nClient->ReceiveData();
	return 0;
}
