#include "stdafx.h"
#include "StringHelpers.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace printer;

wchar_t * StringHelpers::StringToWchar(String ^str)
{
	const size_t newsizew = sizeof(str);
	pin_ptr<const wchar_t> wch = PtrToStringChars(str);

	wchar_t *wcstring = new wchar_t[newsizew];

	wcscpy_s(wcstring, newsizew, wch);

	return wcstring;
}

void StringHelpers::MarshalString(String ^ s, string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void StringHelpers::MarshalString(String ^ s, wstring& os) {
	using namespace Runtime::InteropServices;
	const wchar_t* chars =
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

LPCWSTR StringHelpers::MarshalWString(std::string s) {
	std::wstring stemp = std::wstring(s.begin(), s.end());

	return (LPCWSTR)stemp.c_str();
}

LPWSTR StringHelpers::SwitchToLongString(LPCWSTR str) {
	std::wstring tempStr(str);

	return &tempStr[0];
}