#include "stdafx.h"
#include "printer.h"
#include "StringHelpers.h"

using namespace printer;
using namespace System;
using namespace System::Collections::Generic;

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

	Console::WriteLine(String::Format("You have chosen printer `{0}`.", printersCollection[printerPosition]));

	
}

void Printer::choosePrinter(String^ printerName) {
	HANDLE hndl;
	DEVMODE* devmode;

	std::string _printer = std::string();
	StringHelpers::MarshalString(printerName, _printer);

	HDC printerDC = CreateDC(L"WINSPOOL", StringHelpers::MarshalWString(_printer), NULL, devmode);

	LPWSTR szPrinter = StringHelpers::SwitchToLongString(StringHelpers::MarshalWString(_printer));
	OpenPrinter(szPrinter, &hndl, NULL);
}