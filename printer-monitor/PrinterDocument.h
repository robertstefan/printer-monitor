#pragma once
#include "stdafx.h"

using namespace System;

DllExport public ref class PrinterDocument
{
public:
	PrinterDocument();
	void CreateDocument();
	void Bind(HANDLE hndl);
private:
	HANDLE printerHndl;
};

