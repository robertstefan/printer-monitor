// printer-monitor.cpp : main project file.

#include "stdafx.h"
#include "Printer.h"

using namespace System;

int main(String^ printerName)
{
	Printer^ monitor = gcnew Printer();
	
	if (String::IsNullOrEmpty(printerName) || String::IsNullOrWhiteSpace(printerName)) {
		Console::WriteLine(L"Here is a list of available printers.\nPlease provide the number corresponding to the printer you want to use.");
		Console::WriteLine();

		monitor->listSystemMountedPrinters();
		Console::Write("Printer id: ");

		int printerId = 0;
		string printerIdx = string();
		Helpers::MarshalString(Console::ReadLine(), printerIdx);

		printerId = System::Convert::ToInt32(printerIdx.c_str());

		if (printerId < 0 || printerId > monitor->getPrintersCount()) {
			Console::WriteLine(L"Incorrect provided index");
			return 0;
		}

		monitor->usePrinter(printerId);
	}
	else {
		Console::Write("Using printer ");
		Console::Write(printerName);

		return 1;
	}

	//monitor->usePrinter();
	monitor->PrintDocument(L"Hello world!");

	Console::ReadLine();
	return 0;
}
