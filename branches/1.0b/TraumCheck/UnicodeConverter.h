#pragma once

#define DEFAULT_ANSI 0

bool ansi_to_unicode_convert(std::wstring& result, const char* src, unsigned int len = -1, unsigned int codepage = DEFAULT_ANSI);
bool unicode_to_ansi_convert(std::string& result, const wchar_t* src, unsigned int len = -1, unsigned int codepage = DEFAULT_ANSI);
