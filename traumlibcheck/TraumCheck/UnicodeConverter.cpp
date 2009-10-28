#include "common.h"

#include "UnicodeConverter.h"

#include <Windows.h>

bool ansi_to_unicode_convert(std::wstring& result, const char* str, unsigned int str_len, unsigned int codepage)
{
	if(str == NULL || str_len == 0){
		result.erase();
		return true;
	}

	//если str_len == -1, то MBTWC учитывает завершающий нулевой символ
	int wlen = ::MultiByteToWideChar(codepage, 0, str, static_cast<int>(str_len), NULL, 0);

	if(wlen == 0 || (wlen == 1 && str_len == -1)){ //error или str==""
		result.erase();
		return ::GetLastError() != 0;
	}

	if(str_len != -1)
		wlen += 1;//учитываем завершающий UNICODE-символ

	//резервируем место под все символы (включая и терминальный)
	result.resize(wlen);

	::MultiByteToWideChar(codepage, 0, str, static_cast<int>(str_len), const_cast<wchar_t*>(result.c_str()), wlen);

	//удаляем терминальный UNICODE-символ
	result.erase(result.size() - 1, 1);
	
	return true;
}

// --------------------------------------------------------------------------

bool unicode_to_ansi_convert(std::string& result, const wchar_t* wstr, unsigned int wstr_len, unsigned int codepage)
{
	if(wstr == NULL || wstr_len == 0){
		result.erase();
		return true;
	}

	//если wstr_len == -1, то WCTMB учитывает завершающий нулевой символ
	int alen = ::WideCharToMultiByte(codepage, 0, wstr, static_cast<int>(wstr_len) ,NULL, 0, NULL, NULL);

	if(alen == 0 || (alen == 1 && wstr_len == -1)){ //error или wstr==L""
		result.erase();
		return ::GetLastError() != 0;
	}

	//HINT: Здесь предполагается, что для всех ANSI кодировок терминальный символ
	//      занимает 1 байт
	if(wstr_len != -1)
		alen += 1;//учитываем завершающий символ

	//резервируем место под все символы (включая и терминальный)
	result.resize(alen);

	::WideCharToMultiByte(codepage, 0, wstr, static_cast<int>(wstr_len), const_cast<char*>(result.c_str()), alen, NULL, NULL);

	//исключаем терминальный символ
	result.erase(result.size() - 1, 1);

	return true;
}