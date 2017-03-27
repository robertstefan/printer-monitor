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
		HANDLE printerHndl;
		BOOL IsPrinterError(HANDLE hndl);

	public:
		Printer() {
			printersCollection = gcnew List<String^>();
		}

		void listSystemMountedPrinters();

		void generateMenu();

		Printer^ choosePrinter(String^ printerName);

		BOOL GetJobs(HANDLE hndl, JOB_INFO_2 **jobInfo, int *pcJobs, DWORD *printQueueStatus);

		Printer^ createDocument(System::Guid documentTitle, System::String^ documentText);
	};
}