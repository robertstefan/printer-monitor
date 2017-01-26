#pragma once
#include "stdafx.h"

using namespace System;
using json = nlohmann::json;

extern "C" {
	public ref class PrinterDocument
	{
	public:
		PrinterDocument() {};
		void CreateDocument();
		void Bind();
	private:


	};

}