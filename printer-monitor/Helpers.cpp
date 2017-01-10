#include "stdafx.h"
#include "Helpers.h"
// https://msdn.microsoft.com/en-us/library/ms235631?f=255&MSPPError=-2147217396#Converting from System::String

using namespace System;

Helpers::Helpers()
{
}

wchar_t * Helpers::StringToWchar(String ^str)
{
	const size_t newsizew = sizeof(str);
	pin_ptr<const wchar_t> wch = PtrToStringChars(str);

	wchar_t *wcstring = new wchar_t[newsizew];

	wcscpy_s(wcstring, newsizew, wch);

	return wcstring;
}
