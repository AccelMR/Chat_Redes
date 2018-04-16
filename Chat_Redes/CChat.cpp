#include "stdafx.h"
#include "CChat.h"


void CChat::Menu()
{
	char ans;
	std::wstring IP;
	std::wstring port;
	bool zz = true;
	bool flag = true;

	while (zz) {
		cout << "\n(Tener en cuenta que no se podra inicar chat sin tener los datos antes): \n"
			<< "\nInsertar datos \t\t\t'0'"
			<< "\nCargar datos \t\t\t'1'"
			//<< "\nMostrar IP y Puerto actuales \t'2'"
			<< "\nSalir del chat \t\t\t'9'\n"
			<< "\n\n **En caso que no se hayan introducido datos, se usaran los de la sesión pasada ** \n";
		std::cin >> ans;
		std::cin.ignore();
		system("cls");

		switch (ans) {
		case '0':
			while (true)
			{

				cout << "Inserta IP: ";
				std::wcin >> IP;
				cout << "\nInsert port: ";
				std::wcin >> port;
				if (!elcodi->Coder(IP, port)) {
					system("cls");
					cout << "\nLos datos ingresados son invalidos!!!! \n\n";
					_getch();
				}
				else {
					system("cls");
					m_myself = new CCliente(IP, _wtoi(port.c_str()));
					cout << "\nHas llenado los datos correctamente.\n\n";
					break;
				}
			}

			break;

		case '1':
			if (!elcodi->Decoder()) {
				MessageBox(nullptr, TEXT("Archivo corrupto o inexistente\nTus mensajes no podran ser entregados"), TEXT("Message"), MB_OK);
			}
			else {
				if(m_myself->initilize()) {
					Chat();
					zz = false;
				}
				else {
					std::cout << "Error al inicializar, achis achis los mariachis " << std::endl;
				}
			}
		
			break;
		case '3':

		case '9':
			exit(0);

		default:
			cout << "Opcion invalida ";
			break;
		}
	}
}

CChat::CChat():
	chatHistory (nullptr),
	m_myself(nullptr)
{
	elcodi = new CCodifier;
}


CChat::~CChat()
{
}

void CChat::Chat()
{
	std::string line;
	std::string strRecieved = " ";
	chatHistory = new std::list<std::string>;
	chatHistory->clear();

	while (true) {
		cout << "\t\t\t\t|****************************|\n"
			<< "\t\t\t\t|*****      CHAT        *****|\n"
			<< "\t\t\t\t|****************************|\n\n\n";

		//std::cout << strRecieved << std::endl;
		std::getline(std::cin, line);


		if (line == "-e") { break; }

		else if (line == "-c") {
			chatHistory->clear();
			system("cls");
		}

		else if (line == "-h") {
			system("cls");
			cout << "Tu historial: \n";
			if (chatHistory->empty()) { std::cout << "\n\nNo existe historial.\n"; }
			else {
			for (auto v : *chatHistory)
				std::cout << v << "\n";
			cout << "\n\n";
			}
			_getch();
			system("cls");
		}

		else {
			strRecieved = m_myself->ReceiveData(line);
			chatHistory->push_back(line);
			system("cls");

		}
	}
}
