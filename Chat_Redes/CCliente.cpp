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

string CCliente::ReceiveData(string userInput)
{
	char buff[4096];
	// Send the text
	if (userInput.size() > 0) {
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
		if (sendResult != SOCKET_ERROR) {
			// Wait for response 
			ZeroMemory(buff, 4096);
			int bytesRecived = recv(sock, buff, 4096, 0);
			if (bytesRecived > 0) {
				// Echo response to console 
				//cout << "server>" << string(buff, 0, bytesRecived) << endl;
				return "server>" + string(buff, 0, bytesRecived);
			}
		}
	}
	return '\0';
}
