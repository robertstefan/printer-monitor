// printer.testapp.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace printer;
using namespace std;

int main(array<System::String ^> ^args)
{
	//printer::Printer::Welcome();
	printer::Printer^ _printer = gcnew printer::Printer();

	//HANDLE printerMem;
	_printer->listSystemMountedPrinters()->generateMenu();



	Console::Read();

    return 0;
}
