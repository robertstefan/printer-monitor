#include "StdAfx.h"
#include "StringHelpers.h"

using namespace printer;
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

void StringHelpers::MarshalString(String ^s, string& os) {
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

LPCWSTR StringHelpers::MarshalWString(std::string s) {
	std::wstring stemp = StringHelpers::s2ws(s);
	//LPCWSTR result;
	
	return stemp.c_str();

	//return result;
}

LPWSTR StringHelpers::SwitchToLongString(LPCWSTR str) {
	std::wstring tempStr(str);

	return &tempStr[0];
}
