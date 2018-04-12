#include "stdafx.h"
#include "CCodifier.h"


CCodifier::CCodifier()
{
	_encodedMat.resize(0);
}

CCodifier::~CCodifier()
{
}

int CCodifier::NumOfCol(std::wstring _sizer)
{
	int col = _sizer.size();
	if (col == 0) {
		std::cout << "No existe cadena dentro del archivo, error\n";
	}
	if (col % ROW != 0) {
		return (col / 3) + 1;
	}
	return col / 3;

}

void CCodifier::MatrixToString()
{
}

bool CCodifier::Prove(std::wstring IP, std::wstring port)
{
	if (IP.find_first_not_of(L"0123456789.") == std::string::npos) {
		int correct = 0;
		wchar_t* char_line = (wchar_t*)IP.c_str();
		wchar_t* char_port = (wchar_t*)port.c_str();
		wchar_t* token = NULL;
		wchar_t* context = NULL;
		wchar_t  delims = '.';

		token = wcstok_s(char_line, &delims, &context);
		while (token != NULL) {

			if (_wtoi(token) > 255 || _wtoi(token) < 0) return false;
			token = wcstok_s(NULL, &delims, &context);
			correct++;
		}
		return (correct == 4 && _wtoi(char_port) < 60001 && _wtoi(char_port) > 1023);
	}
	return false;
}

bool CCodifier::Coder(std::wstring IP, std::wstring port)
{
	if (Prove(IP,port))
	{
		_strToEncode = IP + L" " + port;
		int col = NumOfCol(_strToEncode);
		_strToEncode.resize(ROW*col);


		_encodedMat.resize(ROW);
		for (int i = 0; i < ROW; i++) {
			_encodedMat[i].resize(col);
		}

		std::wstring insert; 

		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < col; j++) {
				for (int k = 0; k < ROW; k++) {
					_encodedMat[i][j] += _secretMat[i][k] *_strToEncode[(j * 3) + k];
				}
				insert.push_back(_encodedMat[i][j]);
			}
		}
		_file.open(FILE_NAME, std::ios::out);
		_fichero.open("tlog.log", std::ios::out);
		_file.imbue(std::locale(_file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
		_fichero.imbue(std::locale(_file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
		_file << insert;
		_fichero << insert;
		_file.close();
		_fichero.close();
		return true;
	}
	return false;
}

bool CCodifier::Decoder()
{
	_file.open(FILE_NAME, std::ios::in);
	_fichero.open("tlog.log", std::ios::in);
	if (_file.fail() || _fichero.fail()) {
		return false;
	}
	std::wstring get;
	std::wstring compare;
	_file.imbue(std::locale(_file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	_fichero.imbue(std::locale(_file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	_file >> get;
	_fichero >> compare;
	_fichero.close();
	_file.close();

	int col = NumOfCol(get);
	

	_decodedMat.resize(ROW);
	for (int i = 0; i < ROW; i++) {
		_decodedMat[i].resize(col);
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < col; j++) {
			for (int k = 0; k < ROW; k++) {
				_decodedMat[i][j] += _inverseMat[i][k] * (int)get[(j * 3) + k];
			}
			//_stuff.push_back(_decodedMat[i][j]);
		}
	}
	return get == compare;
}

void CCodifier::getIPandPort()
{

}
