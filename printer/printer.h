// printer.h

#pragma once
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace System;
using namespace System::Collections::Generic;

namespace printer {

	public ref class Printer
	{
	private:
		List<String^>^ printersCollection;
		String^ printerToUse;

	public:
		Printer() {
			printersCollection = gcnew List<String^>();
		}

		void listSystemMountedPrinters();

		void generateMenu();

		void choosePrinter(String^ printerName);
	};
}