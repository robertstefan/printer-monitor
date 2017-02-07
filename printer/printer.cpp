// This is the main DLL file.

#include "stdafx.h"
#include "printer.h"

using namespace printer;
using namespace System;
using namespace System::Collections::Generic;

#include "StringHelpers.h"

void Printer::listSystemMountedPrinters() {
	PRINTER_INFO_2* prninfo = NULL;
	DWORD needed, returned;
	DWORD flags = PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS | PRINTER_ENUM_NETWORK;

	//find required size for the buffer
	EnumPrinters(flags, NULL, 2, NULL, 0, &needed, &returned);

	//allocate array of PRINTER_INFO structures
	prninfo = (PRINTER_INFO_2*)GlobalAlloc(GPTR, needed);

	//call again

	if (!EnumPrinters(flags, NULL, 2, (LPBYTE)prninfo, needed, &needed, &returned))
	{
		//Place Error Code Here
		Console::WriteLine("Error");
	}
	else
	{
		for (int i = 0; i < (int)returned; i++)
		{
			printersCollection->Add(gcnew String(prninfo[i].pPrinterName));
		}
	}
	GlobalFree(prninfo);

	//return this;
}

void Printer::generateMenu() {

	Console::WriteLine("Available printers on the system:\n");

	byte i;
	i = 0;
	for each (String^ printer in printersCollection)
	{
		Console::WriteLine(String::Format("{0}. {1}", ++i, printer));
	}

	Console::WriteLine("\n\nChoose the one you want to use by typing the ID and pressing \"Enter\"...\n");

	int printerPosition;
	printerPosition = Int32::Parse(Console::ReadLine()) - 1;

	printerToUse = printersCollection[printerPosition];

	Console::WriteLine(String::Format("You have chosen printer `{0}`.", printerToUse));

	//choosePrinter(printerToUse);
}

void Printer::choosePrinter(String^ printerName) {
	HANDLE hndl;
	DEVMODE* devmode;

	if (String::IsNullOrEmpty(printerName)) {
		printerName = printerToUse;
	}

	std::string _printer = std::string();
	StringHelpers::MarshalString(printerName, _printer);

	LPCWSTR _printerName = StringHelpers::MarshalWString(_printer);

	LPWSTR szPrinter = StringHelpers::SwitchToLongString(_printerName);
	OpenPrinter(szPrinter, &hndl, NULL);

	int size = DocumentProperties(NULL, hndl, szPrinter, NULL, NULL, 0);
	devmode = (DEVMODE*)malloc(size);

	HDC printerDC = CreateDC(L"WINSPOOL", _printerName, NULL, devmode);
	
	if (hndl != NULL) {
		Console::WriteLine("Got printer handler");
	}
}
