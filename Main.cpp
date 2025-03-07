#include "StrConvert.h"
#include <iostream>

int main()
{
#if defined __linux__ || defined __CYGWIN__
	setlocale(LC_ALL, "ko_KR.utf8");
#else
	std::locale::global(std::locale(""));
#endif

	std::string src(u8"Hello World! ¾È³ç, ¼¼»ó¾Æ! á¦Í£¡¢ª³ªóªËªÁªÏ¡£\n");
	auto str = StrConvert::utf8_to_mbs(src.c_str());
	std::cout << str << str.length() << std::endl;

	auto wstr = StrConvert::mbs_to_u16(str.c_str());
    std::wcout << (LPCWSTR)wstr.c_str() << wstr.length() << std::endl;

	char u8str[100] = { 0 };
	int n = StrConvert::u16_to_utf8(u8str, 100, wstr.c_str());
	//int n = StrConvert::mbs_to_utf8(u8str, _countof(u8str), src.c_str());
	std::cout << u8str << n << std::endl << std::endl;

	assert(StrConvert::u16_to_mbs(wstr.c_str()) == str);
	assert(StrConvert::mbs_to_utf8(str.c_str()) == src);

	auto u16str = StrConvert::utf8_to_u16(u8str);
	std::wcout << (LPCWSTR)u16str.c_str() << u16str.length() << std::endl;

	str = StrConvert::utf8_to_mbs(u8str);
	std::cout << str << str.length() << std::endl;
}
