#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>

#include "atlbase.h"
#include "atlstr.h"
#include "comutil.h"
#include "vcclr.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

namespace printer {
	public ref class StringHelpers
	{
	public:
		static wchar_t* StringToWchar(String ^str);
		static void MarshalString(String ^ s, string& os);
		static void MarshalString(String ^ s, wstring& os);
		static LPCWSTR MarshalWString(std::string s);
		static LPWSTR SwitchToLongString(LPCWSTR str);
	};

}