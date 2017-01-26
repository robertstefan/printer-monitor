// printer.h

#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace printer {

	public ref class Printer
	{
	private:
		List<String^>^ printersCollection;

	public:		
		Printer() {
			printersCollection = gcnew List<String^>();
		}
		void listSystemMountedPrinters();

		void generateMenu();

		void choosePrinter(String^ printerName);
	};
}
