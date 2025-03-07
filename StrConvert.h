#pragma once
#include <string>
#include <cassert>
#ifdef _MSC_VER
#include <windows.h>
#else
#include <string.h>
#include <iconv.h>
#endif

class StrConvert {
public:
#ifdef _MSC_VER
	static int mbs_to_u16(char16_t* u16, int buff_len, const char* mbs) {
		int len = (int)strlen(mbs);
		int count = MultiByteToWideChar(CP_ACP, 0, mbs, len, NULL, 0);
		count = min(count, buff_len - 1);
		len = MultiByteToWideChar(CP_ACP, 0, mbs, len, (LPWSTR)u16, count);
		if (len == 0 && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			len = buff_len - 1;
			u16[len] = '\0';
		}
		return len;
	}

	static std::u16string mbs_to_u16(const char* mbs) {
		int len = (int)strlen(mbs);
		int count = MultiByteToWideChar(CP_ACP, 0, mbs, len, NULL, 0);
		std::u16string u16str(count, '\0');
		MultiByteToWideChar(CP_ACP, 0, mbs, len, (LPWSTR)u16str.data(), count);
		return u16str;
	}

	static int u16_to_mbs(char* mbs, int buff_len, const char16_t* u16) {
		int len = (int)wcslen((const wchar_t*)u16);
		int count = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)u16, len, NULL, 0, NULL, NULL);
		count = min(count, buff_len - 1);
		len = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)u16, len, mbs, count, NULL, NULL);
		if (len == 0 && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			len = buff_len - 1;
			mbs[len] = '\0';
		}
		return len;
	}

	static std::string u16_to_mbs(const char16_t* u16) {
		int len = (int)wcslen((const wchar_t*)u16);
		int count = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)u16, len, NULL, 0, NULL, NULL);
		std::string str(count, '\0');
		WideCharToMultiByte(CP_ACP, 0, (LPCWCH)u16, len, str.data(), count, NULL, NULL);
		return str;
	}

	static int u16_to_utf8(char* utf8, int buff_len, const char16_t* u16) {
		int len = (int)wcslen((const wchar_t*)u16);
		int count = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)u16, len, NULL, 0, NULL, NULL);
		count = min(count, buff_len - 1);
		len = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)u16, len, utf8, count, NULL, NULL);
		if (len == 0 && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			len = buff_len - 1;
			utf8[len] = '\0';
		}
		return len;
	}

	static std::string u16_to_utf8(const char16_t* u16) {
		int len = (int)wcslen((const wchar_t*)u16);
		int count = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)u16, len, NULL, 0, NULL, NULL);
		std::string u8str(count, '\0');
		WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)u16, len, u8str.data(), count, NULL, NULL);
		return u8str;
	}

	static int utf8_to_u16(char16_t* u16, int buff_len, const char* utf8) {
		int len = (int)strlen(utf8);
		int count = MultiByteToWideChar(CP_UTF8, 0, utf8, len, NULL, 0);
		count = min(count, buff_len - 1);
		len = MultiByteToWideChar(CP_UTF8, 0, utf8, len, (LPWSTR)u16, count);
		if (len == 0 && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			len = buff_len - 1;
			u16[len] = '\0';
		}
		return len;
	}

	static std::u16string utf8_to_u16(const char* utf8) {
		int len = (int)strlen(utf8);
		int count = MultiByteToWideChar(CP_UTF8, 0, utf8, len, NULL, 0);
		std::u16string u16str(count, '\0');
		MultiByteToWideChar(CP_UTF8, 0, utf8, len, (LPWSTR)u16str.data(), count);
		return u16str;
	}

	static int mbs_to_utf8(char* utf8, int buff_len, const char* mbs) {
		int len = (int)strlen(mbs);
		int count = MultiByteToWideChar(CP_ACP, 0, mbs, len, NULL, 0);
		wchar_t* buff = new wchar_t[count + 1];
		len = MultiByteToWideChar(CP_ACP, 0, mbs, len, buff, count);
		if (len > 0) {
			count = WideCharToMultiByte(CP_UTF8, 0, buff, len, NULL, 0, NULL, NULL);
			count = min(count, buff_len - 1);
			len = WideCharToMultiByte(CP_UTF8, 0, buff, len, utf8, count, NULL, NULL);
			if (len == 0 && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
				len = buff_len - 1;
				utf8[len] = '\0';
			}
		}
		delete[] buff;
		return len;
	}

	static std::string mbs_to_utf8(const char* mbs) {
		int len = (int)strlen(mbs);
		int count = MultiByteToWideChar(CP_ACP, 0, mbs, len, NULL, 0);
		std::string u8str;
		wchar_t* buff = new wchar_t[count + 1];
		len = MultiByteToWideChar(CP_ACP, 0, mbs, len, buff, count);
		if (len > 0) {
			count = WideCharToMultiByte(CP_UTF8, 0, buff, len, NULL, 0, NULL, NULL);
			u8str.resize(count);
			WideCharToMultiByte(CP_UTF8, 0, buff, len, u8str.data(), count, NULL, NULL);
		}
		delete[] buff;
		return u8str;
	}

	static int utf8_to_mbs(char* mbs, int buff_len, const char* utf8) {
		int len = (int)strlen(utf8);
		int count = MultiByteToWideChar(CP_UTF8, 0, utf8, len, NULL, 0);
		wchar_t* buff = new wchar_t[count + 1];
		len = MultiByteToWideChar(CP_UTF8, 0, utf8, len, buff, count);
		if (len > 0) {
			count = WideCharToMultiByte(CP_ACP, 0, buff, len, NULL, 0, NULL, NULL);
			count = min(count, buff_len - 1);
			len = WideCharToMultiByte(CP_ACP, 0, buff, len, mbs, count, NULL, NULL);
			if (len == 0 && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
				len = buff_len - 1;
				mbs[len] = '\0';
			}
		}
		delete[] buff;
		return len;
	}

	static std::string utf8_to_mbs(const char* utf8) {
		int len = (int)strlen(utf8);
		int count = MultiByteToWideChar(CP_UTF8, 0, utf8, len, NULL, 0);
		std::string str;
		wchar_t* buff = new wchar_t[count + 1];
		len = MultiByteToWideChar(CP_UTF8, 0, utf8, len, buff, count);
		if (len > 0) {
			count = WideCharToMultiByte(CP_ACP, 0, buff, len, NULL, 0, NULL, NULL);
			str.resize(count);
			WideCharToMultiByte(CP_ACP, 0, buff, len, str.data(), count, NULL, NULL);
		}
		delete[] buff;
		return str;
	}
#else
	static constexpr const char* DefaultCodePage = "EUC-KR";

	static int mbs_to_u16(char16_t* u16, int buff_len, const char* mbs) {
		iconv_t icv = iconv_open("UTF-16LE", DefaultCodePage);
		if (icv == (iconv_t)-1)
			return 0;
		size_t nSrcLen = strlen(mbs);
		size_t nDstLen = buff_len * sizeof(char16_t);
		char* inbuf = const_cast<char*>(mbs);
		char* outbuf = reinterpret_cast<char*>(u16);
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return 0;
		return (int)(outbuf - (char*)u16) / sizeof(char16_t);
	}

	static std::u16string mbs_to_u16(const char* mbs) {
		iconv_t icv = iconv_open("UTF-16LE", DefaultCodePage);
		if (icv == (iconv_t)-1)
			return u"";
		size_t nSrcLen = strlen(mbs);
		size_t nDstLen = nSrcLen * sizeof(char16_t);
		std::u16string u16(nSrcLen, '\0');
		char* inbuf = const_cast<char*>(mbs);
		char* outbuf = reinterpret_cast<char*>(u16.data());
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return u"";
		u16.resize(u16.size() - nDstLen / sizeof(char16_t));
		return u16;
	}

	static int u16_to_mbs(char* mbs, int buff_len, const char16_t* u16) {
		iconv_t icv = iconv_open(DefaultCodePage, "UTF-16LE");
		if (icv == (iconv_t)-1)
			return 0;
		size_t nSrcLen = std::char_traits<char16_t>::length(u16) * sizeof(char16_t);
		size_t nDstLen = buff_len;
		char* inbuf = (char*)u16;
		char* outbuf = mbs;
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return 0;
		return (int)(outbuf - mbs);
	}

	static std::string u16_to_mbs(const char16_t* u16) {
		iconv_t icv = iconv_open(DefaultCodePage, "UTF-16LE");
		if (icv == (iconv_t)-1)
			return "";
		size_t nSrcLen = std::char_traits<char16_t>::length(u16) * sizeof(char16_t);
		size_t nDstLen = nSrcLen;
		std::string str(nDstLen, '\0');
		char* inbuf = (char*)u16;
		char* outbuf = str.data();
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return "";
		str.resize(str.size() - nDstLen);
		return str;
	}

	static int u16_to_wstr(wchar_t* wsz, int buff_len, const char16_t* u16) {
		iconv_t icv = iconv_open("UTF-32LE", "UTF-16LE");
		if (icv == (iconv_t)-1)
			return 0;
		size_t nSrcLen = std::char_traits<char16_t>::length(u16) * sizeof(char16_t);
		size_t nDstLen = buff_len * sizeof(wchar_t);
		char* inbuf = (char*)u16;
		char* outbuf = (char*)wsz;
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return 0;
		return (int)(outbuf - (char*)wsz) / sizeof(wchar_t);
	}

	static std::wstring u16_to_wstr(const char16_t* u16) {
		iconv_t icv = iconv_open("UTF-32LE", "UTF-16LE");
		if (icv == (iconv_t)-1)
			return L"";
		size_t len = std::char_traits<char16_t>::length(u16);
		size_t nSrcLen = len * sizeof(char16_t);
		size_t nDstLen = len * sizeof(wchar_t);
		std::wstring wstr(len, '\0');
		char* inbuf = (char*)u16;
		char* outbuf = reinterpret_cast<char*>(wstr.data());
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return L"";
		wstr.resize(wstr.size() - nDstLen / sizeof(wchar_t));
		return wstr;
	}

	static int u16_to_utf8(char* utf8, int buff_len, const char16_t* u16) {
		iconv_t icv = iconv_open("UTF-8", "UTF-16LE");
		if (icv == (iconv_t)-1)
			return 0;
		size_t nSrcLen = std::char_traits<char16_t>::length(u16) * sizeof(char16_t);
		size_t nDstLen = buff_len;
		char* inbuf = (char*)u16;
		char* outbuf = utf8;
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return 0;
		return (int)(outbuf - utf8);
	}

	static std::string u16_to_utf8(const char16_t* u16) {
		iconv_t icv = iconv_open("UTF-8", "UTF-16LE");
		if (icv == (iconv_t)-1)
			return "";
		size_t len = std::char_traits<char16_t>::length(u16);
		size_t nSrcLen = len * sizeof(char16_t);
		size_t nDstLen = nSrcLen + len;
		std::string u8str(nDstLen, '\0');
		char* inbuf = (char*)u16;
		char* outbuf = u8str.data();
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return "";
		u8str.resize(u8str.size() - nDstLen);
		return u8str;
	}

	static int utf8_to_u16(char16_t* u16, int buff_len, const char* utf8) {
		iconv_t icv = iconv_open("UTF-16LE", "UTF-8");
		if (icv == (iconv_t)-1)
			return 0;
		size_t nSrcLen = strlen(utf8);
		size_t nDstLen = buff_len * sizeof(char16_t);
		char* inbuf = (char*)utf8;
		char* outbuf = (char*)u16;
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return 0;
		return (int)(outbuf - (char*)u16) / sizeof(char16_t);
	}

	static std::u16string utf8_to_u16(const char* utf8) {
		iconv_t icv = iconv_open("UTF-16LE", "UTF-8");
		if (icv == (iconv_t)-1)
			return u"";
		size_t nSrcLen = strlen(utf8);
		size_t nDstLen = nSrcLen * sizeof(char16_t);
		std::u16string u16(nSrcLen, '\0');
		char* inbuf = (char*)utf8;
		char* outbuf = (char*)u16.data();
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return u"";
		u16.resize(u16.size() - nDstLen / sizeof(char16_t));
		return u16;
	}

	static int mbs_to_utf8(char* utf8, int buff_len, const char* mbs) {
		iconv_t icv = iconv_open("UTF-8", DefaultCodePage);
		if (icv == (iconv_t)-1)
			return 0;
		size_t nSrcLen = strlen(mbs);
		size_t nDstLen = buff_len;
		char* inbuf = const_cast<char*>(mbs);
		char* outbuf = utf8;
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return 0;
		return (int)(outbuf - utf8);
	}

	static std::string mbs_to_utf8(const char* mbs) {
		iconv_t icv = iconv_open("UTF-8", DefaultCodePage);
		if (icv == (iconv_t)-1)
			return "";
		size_t nSrcLen = strlen(mbs);
		size_t nDstLen = nSrcLen * 3;
		std::string u8str(nDstLen, '\0');
		char* inbuf = const_cast<char*>(mbs);
		char* outbuf = u8str.data();
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return "";
		u8str.resize(u8str.size() - nDstLen);
		return u8str;
	}

	static int utf8_to_mbs(char* mbs, int buff_len, const char* utf8) {
		iconv_t icv = iconv_open(DefaultCodePage, "UTF-8");
		if (icv == (iconv_t)-1)
			return 0;
		size_t nSrcLen = strlen(utf8);
		size_t nDstLen = buff_len;
		char* inbuf = const_cast<char*>(utf8);
		char* outbuf = mbs;
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return 0;
		return (int)(outbuf - mbs);
	}

	static std::string utf8_to_mbs(const char* utf8) {
		iconv_t icv = iconv_open(DefaultCodePage, "UTF-8");
		if (icv == (iconv_t)-1)
			return "";
		size_t nSrcLen = strlen(utf8);
		size_t nDstLen = nSrcLen;
		std::string str(nDstLen, '\0');
		char* inbuf = const_cast<char*>(utf8);
		char* outbuf = str.data();
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return "";
		str.resize(str.size() - nDstLen);
		return str;
	}

	static int wstr_to_u16(char16_t* u16, int buff_len, const wchar_t* wsz) {
		iconv_t icv = iconv_open("UTF-16LE", "UTF-32LE");
		if (icv == (iconv_t)-1)
			return 0;
		size_t nSrcLen = wcslen(wsz) * sizeof(wchar_t);
		size_t nDstLen = buff_len * sizeof(char16_t);
		char* inbuf = (char*)wsz;
		char* outbuf = (char*)u16;
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return 0;
		return (int)(outbuf - (char*)u16) / sizeof(char16_t);
	}

	static std::u16string wstr_to_u16(const wchar_t* wsz) {
		iconv_t icv = iconv_open("UTF-16LE", "UTF-32LE");
		if (icv == (iconv_t)-1)
			return u"";
		size_t nSrcLen = wcslen(wsz) * sizeof(wchar_t);
		size_t nDstLen = nSrcLen / 2;
		std::u16string u16str(nDstLen, '\0');
		char* inbuf = (char*)wsz;
		char* outbuf = (char*)u16str.data();
		size_t cc = iconv(icv, &inbuf, &nSrcLen, &outbuf, &nDstLen);
		iconv_close(icv);
		if (cc == (size_t)-1)
			return u"";
		u16str.resize(u16str.size() - nDstLen / sizeof(char16_t));
		return u16str;
	}
#endif
};
