// This is the main DLL file.

#include "stdafx.h"
#include "printer.h"

using namespace printer;
using namespace System;
using namespace System::Collections::Generic;

#include "StringHelpers.h"

void Printer::listSystemMountedPrinters() {
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
		Console::WriteLine("Error");
	}
	else
	{
		for (int i = 0; i < (int)returned; i++)
		{
			printersCollection->Add(gcnew String(prninfo[i].pPrinterName));
		}
	}
	GlobalFree(prninfo);

	//return this;
}

void Printer::generateMenu() {

	Console::WriteLine("Available printers on the system:\n");

	byte i;
	i = 0;
	for each (String^ printer in printersCollection)
	{
		Console::WriteLine(String::Format("{0}. {1}", ++i, printer));
	}

	Console::WriteLine("\n\nChoose the one you want to use by typing the ID and pressing \"Enter\"...\n");

	int printerPosition;
	printerPosition = Int32::Parse(Console::ReadLine()) - 1;

	printerToUse = printersCollection[printerPosition];

	Console::WriteLine(String::Format("You have chosen printer `{0}`.", printerToUse));

	//choosePrinter(printerToUse);
}

Printer^ Printer::choosePrinter(String^ printerName) {
	HANDLE hndl;
	DEVMODE* devmode;

	if (String::IsNullOrEmpty(printerName)) {
		printerName = printerToUse;
	}

	std::string _printer = std::string();
	StringHelpers::MarshalString(printerName, _printer);

	HDC printerDC = CreateDC(L"WINSPOOL", StringHelpers::Wide(_printer).c_str(), NULL, devmode);
	OpenPrinter(NULL, &hndl, NULL);

	if (hndl != NULL) {
		Console::Write("Got printer handler\n\n");

		Printer::printerHndl = hndl;
	}
	else {
		Console::Write("Error.");
	}

	return this;
}

BOOL Printer::GetJobs(HANDLE hndl, JOB_INFO_2 **jobInfo, int *pcJobs, DWORD *printQueueStatus) {

	DWORD cByteNeeded,
		nReturned,
		cByteUsed;

	JOB_INFO_2 *pJobStorage = NULL;
	PRINTER_INFO_2 *pPrinterInfo = NULL;

	if (hndl == NULL)
		hndl = Printer::printerHndl;

	if (!GetPrinter(hndl, 2, NULL, 0, &cByteNeeded)) {
		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
			return FALSE;
		
		pPrinterInfo = (PRINTER_INFO_2 *)malloc(cByteNeeded);
		if (!pPrinterInfo)
			return FALSE;

		if (!GetPrinter(hndl, 2, (LPBYTE)pPrinterInfo, cByteNeeded, &cByteUsed)) {
			free(pPrinterInfo);

			pPrinterInfo = NULL;

			return FALSE;
		}

		if (!EnumJobs(hndl, 0, pPrinterInfo->cJobs, 2, NULL, 0, (LPDWORD)&cByteNeeded, (LPDWORD)&nReturned)) {
			if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
				free(pPrinterInfo);
				pPrinterInfo = NULL;

				return FALSE;
			}
		}

		pJobStorage = (JOB_INFO_2 *)malloc(cByteNeeded);
		if (!pJobStorage) {
			free(pPrinterInfo);

			pPrinterInfo = NULL;

			return FALSE;
		}

		ZeroMemory(pJobStorage, cByteNeeded);

		if (!EnumJobs(hndl, 0, pPrinterInfo->cJobs, 2, (LPBYTE)pJobStorage, cByteNeeded, (LPDWORD)&cByteUsed, (LPDWORD)&nReturned)) {
			free(pPrinterInfo);
			free(pJobStorage);

			pJobStorage = NULL;
			pPrinterInfo = NULL;

			return FALSE;
		}

		*pcJobs = nReturned;
		*printQueueStatus = pPrinterInfo->Status;
		*jobInfo = pJobStorage;

		free(pPrinterInfo);

		return TRUE;
	}
};

BOOL Printer::IsPrinterError(HANDLE hndl) {
	JOB_INFO_2 *pJobInfo;
	int cJobs,
		i;
	DWORD dwPrinterStatus;

	if (!GetJobs(hndl, &pJobInfo, &cJobs, &dwPrinterStatus))
		return FALSE;

	if (dwPrinterStatus & (
		PRINTER_STATUS_ERROR |
		PRINTER_STATUS_PAPER_JAM |
		PRINTER_STATUS_PAPER_OUT |
		PRINTER_STATUS_PAPER_PROBLEM |
		PRINTER_STATUS_OUTPUT_BIN_FULL |
		PRINTER_STATUS_NOT_AVAILABLE |
		PRINTER_STATUS_NO_TONER |
		PRINTER_STATUS_OUT_OF_MEMORY |
		PRINTER_STATUS_OFFLINE |
		PRINTER_STATUS_DOOR_OPEN)) {
		free(pJobInfo);

		return TRUE;
	}

	for (i = 0; i < cJobs; i++) {
		if (pJobInfo[i].Status & JOB_STATUS_PRINTING) {
			if (pJobInfo[i].Status & (
				JOB_STATUS_ERROR |
				JOB_STATUS_OFFLINE |
				JOB_STATUS_PAPEROUT |
				JOB_STATUS_BLOCKED_DEVQ))
			{
				free(pJobInfo);

				return TRUE;
			}
		}
	}

	free(pJobInfo);

	return FALSE;
}

Printer^ Printer::createDocument(System::Guid documentTitle, System::String^ documentText) {
	DOC_INFO_1 doc;

	char docName[] = "test document";
	char dataType[] = "text";

	doc.pDocName = (LPWSTR)docName;
	doc.pOutputFile = NULL;
	doc.pDatatype = (LPWSTR)dataType;

	int temp;
	temp = StartPagePrinter(Printer::printerHndl);

	std::string _documentContent = std::string();
	StringHelpers::MarshalString(documentText, _documentContent);

	char content[] = _documentContent.c_str();

	temp = WritePrinter(Printer::printerHndl, sizeof(content), _documentContent, );

	return this;
}