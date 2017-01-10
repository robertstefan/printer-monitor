// printer-monitor.cpp : main project file.

#include "stdafx.h"

using namespace System;

public ref class PrinterMonitor {
private:
	array<String^> ^printersCollection;
	String^ printerToUse;
public:
	int getPrintersCount() {
		return printersCollection->Length;
	}
	int listSystemMountedPrinters();
	void usePrinter(String^ printerName);
	void usePrinter(int printerId);
	int PrintDocument(String^ documentContent);
};

int main(array<System::String^> ^args)
{
	PrinterMonitor^ monitor = gcnew PrinterMonitor();
	
	if (args->Length == 0) {
		Console::WriteLine(L"Here is a list of available printers.\nPlease provide the number corresponding to the printer you want to use.");
		Console::WriteLine();

		monitor->listSystemMountedPrinters();
		Console::Write("Printer id: ");

		int printer = System::Convert::ToInt32(Console::ReadLine);
		if (printer < 0 || printer > monitor->getPrintersCount()) {
			Console::WriteLine(L"Incorrect provided index");
			return 0;
		}

		monitor->usePrinter(printer);
		monitor->PrintDocument(L"Hello world!");
	}

	Console::ReadLine();
	return 0;
}

int PrinterMonitor::listSystemMountedPrinters()
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
		printersCollection = gcnew array<String^>(returned);

		for (int i = 0; i < (int)returned; i++)
		{
			Console::WriteLine(String::Format("{0}. {1}", i+1, gcnew String(prninfo[i].pPrinterName)));
			printersCollection[i] = gcnew String(prninfo[i].pPrinterName);
		}
	}
	GlobalFree(prninfo);

	return 0;
}

void PrinterMonitor::usePrinter(String^ printerName) {
	printerToUse = printerName;
}

void PrinterMonitor::usePrinter(int printerId) {
	printerToUse = printersCollection[printerId];
}

int PrinterMonitor::PrintDocument(String^ documentContent) {
	HANDLE hndl;
	DEVMODE* devmode;

	wchar_t szPrinter[MAX_PATH] = Helpers::StringToWchar(printerToUse);

	DWORD chPrinter(ARRAYSIZE(szPrinter));
	OpenPrinter(szPrinter, &hndl, NULL);

	int size = DocumentProperties(NULL, hndl, szPrinter, NULL, NULL, 0);

	devmode = (DEVMODE*)malloc(size);
	DocumentProperties(NULL, hndl, szPrinter, devmode, NULL, DM_OUT_BUFFER);

	HDC printerDC = CreateDC(L"WINSPOOL", szPrinter, NULL, devmode);
	
	DOCINFO info;
	
	memset(&info, 0, sizeof(info));
	info.cbSize = sizeof(info);
	
	StartDoc(printerDC, &info);
	StartPage(printerDC);
	Rectangle(printerDC, 100, 100, 200, 200);
	EndPage(printerDC);
	EndDoc(printerDC);
	DeleteDC(printerDC);
	ClosePrinter(hndl);

	return 0;
}