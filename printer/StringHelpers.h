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
		static std::wstring s2ws(const std::string& s)
		{
			int len;
			int slength = (int)s.length() + 1;
			len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
			wchar_t* buf = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
			std::wstring r(buf);
			//delete[] buf;
			return r;
		}
		static void MarshalString(String ^s, string& os);
		static LPCWSTR MarshalWString(std::string s);
		static LPWSTR SwitchToLongString(LPCWSTR str);
		static std::wstring Wide(std::string str) {
			return std::wstring(str.begin(), str.end());
		};
	};

}