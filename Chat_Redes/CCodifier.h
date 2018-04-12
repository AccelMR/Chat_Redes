#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <locale>  
#include <codecvt>

using std::vector;

#define ROW 3
#define FILE_NAME "Coder.txt"
//#define KEY_WORD "UDVUVVDU"
class CCodifier
{
private:
	const int _secretMat	[3][3]	{ 1,0,2,1,1,0,1,0,3 };
	const int _inverseMat	[3][3]	{ 3,0,-2,-3,1,2,-1,0,1 };

	std::wstring _strToEncode;
	std::wstring _stuff;

	vector<vector<int>> _encodedMat;
	vector<vector<int>> _decodedMat;

	std::wfstream _file;
	std::wfstream _fichero;

	int NumOfCol(std::wstring _sizer);
	void MatrixToString();
	bool Prove(std::wstring IP, std::wstring port);



public:
	CCodifier();
	~CCodifier();

	bool Coder(std::wstring IP, std::wstring port);
	bool Decoder();
	void getIPandPort();

};

