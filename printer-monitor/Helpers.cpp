#include "stdafx.h"
#include "Helpers.h"
// https://msdn.microsoft.com/en-us/library/ms235631?f=255&MSPPError=-2147217396#Converting from System::String

using namespace System;

wchar_t * Helpers::StringToWchar(String ^str)
{
	const size_t newsizew = sizeof(str);
	pin_ptr<const wchar_t> wch = PtrToStringChars(str);

	wchar_t *wcstring = new wchar_t[newsizew];

	wcscpy_s(wcstring, newsizew, wch);

	return wcstring;
}

void Helpers::MarshalString(String ^ s, string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void Helpers::MarshalString(String ^ s, wstring& os) {
	using namespace Runtime::InteropServices;
	const wchar_t* chars =
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

LPCWSTR Helpers::MarshalWString(std::string s) {
	std::wstring stemp = std::wstring(s.begin(), s.end());
	
	return (LPCWSTR) stemp.c_str();
}

LPWSTR Helpers::SwitchToLongString(LPCWSTR str) {
	std::wstring tempStr(str);

	return &tempStr[0];
}