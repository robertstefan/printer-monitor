#include "stdafx.h"
#include "Printer.h"
#include "Helpers.h"

using namespace System::Collections::Generic;

Printer::Printer()
{
	printerDocument = gcnew PrinterDocument();
}

int Printer::listSystemMountedPrinters()
{
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
		return 1;
	}
	else
	{
		printersCollection = gcnew List<String^>(returned);

		for (int i = 0; i < (int)returned; i++)
		{
			Console::WriteLine(String::Format("{0}. {1}", i + 1, gcnew String(prninfo[i].pPrinterName)));
			printersCollection->Add(gcnew String(prninfo[i].pPrinterName));
		}
	}
	GlobalFree(prninfo);

	return 0;
}

void Printer::usePrinter(String ^printerName) {
	//Helpers::MarshalString(printerName, &printerToUse);
	printerToUse = printerName;
}

void Printer::usePrinter(int printerId) {
	printerToUse = printersCollection[printerId];
}

int Printer::PrintDocument(String ^documentContent) {
	HANDLE hndl;
	DEVMODE* devmode;

	std::string _printer = std::string();
	Helpers::MarshalString(printerToUse, _printer);

	HDC printerDC = CreateDC(L"WINSPOOL", Helpers::MarshalWString(_printer), NULL, devmode);
	
	LPWSTR szPrinter = Helpers::SwitchToLongString(Helpers::MarshalWString(_printer));
	OpenPrinter(szPrinter, &hndl, NULL);

	int size = DocumentProperties(NULL, hndl, szPrinter, NULL, NULL, 0);

	devmode = (DEVMODE*)malloc(size);
	DocumentProperties(NULL, hndl, szPrinter, devmode, NULL, DM_OUT_BUFFER);

	DOCINFO info;

	memset(&info, 0, sizeof(info));
	info.cbSize = sizeof(info);

	StartDoc(printerDC, &info);
	StartPage(printerDC);

	// Draw text A requires a rectangle area to draw the text so we set it up
	RECT lRect = { 0 };
	lRect.left = 0;
	lRect.right = 300;
	lRect.top = 0;
	lRect.bottom = 300;
	
	
	std::string _documentContent = std::string();
	Helpers::MarshalString(documentContent, _documentContent);


	// Draws the text on to the device context of the print job
	DrawTextA(printerDC, _documentContent.c_str(), strlen(_documentContent.c_str()), &lRect, DT_LEFT);
	
	EndPage(printerDC);
	EndDoc(printerDC);

	DeleteDC(printerDC);
	ClosePrinter(hndl);

	return 0;
}