#pragma once

#include "CCliente.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <list>
#include "CCodifier.h"
#include <conio.h>

using std::cout;

class CChat
{
private:

	std::list<std::string> *chatHistory ;
	CCodifier* elcodi;
	CCliente *m_myself;

	void Chat();

public:
	CChat();
	~CChat();

	inline void PRINT_ELEMENTS(const std::string& coll, const char* optcstr = "")
	{
		typename std::string::const_iterator pos;

		std::cout << optcstr;
		for (pos = coll.begin(); pos != coll.end(); ++pos) {
			std::cout << *pos << ' ';
		}
		std::cout << std::endl;
	}
	void Menu();

	int numOfCol;
};

