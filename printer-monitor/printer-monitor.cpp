// printer-monitor.cpp : main project file.

#include "stdafx.h"

using namespace System;

int main(array<System::String^> ^args)
{
	Printer^ monitor = gcnew Printer();
	
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
