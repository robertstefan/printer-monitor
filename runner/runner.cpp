// runner.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace printer;

int main(array<System::String ^> ^args)
{
    printer::Printer^ _printer = gcnew printer::Printer();
	
	_printer->listSystemMountedPrinters();
	_printer->generateMenu();
	_printer->choosePrinter("");

	Console::Read();

    return 0;
}
