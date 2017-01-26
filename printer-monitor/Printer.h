#pragma once
#include "stdafx.h"
#include "Printer.h"
#include "Helpers.h"
#include "PrinterDocument.h"

#include <Windows.h>
#include <wingdi.h>
#include <winspool.h>
#pragma comment(lib, "winspool.lib")

using namespace System::Collections::Generic;

extern "C" {

	public ref class Printer
	{
	private:
		List<String^> ^ printersCollection;
		String ^ printerToUse;


	public:
		int getPrintersCount() {
			return printersCollection->Capacity;
		}

		PrinterDocument^ printerDocument;

		int listSystemMountedPrinters();
		void usePrinter(String ^printerName);
		void usePrinter(int printerId);
		//int PrintDocument(String ^documentContent);

		Printer() {
			printerDocument = gcnew PrinterDocument();
		}
	};

}