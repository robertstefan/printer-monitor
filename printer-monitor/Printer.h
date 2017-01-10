#pragma once
ref class Printer
{
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
	Printer();
};

