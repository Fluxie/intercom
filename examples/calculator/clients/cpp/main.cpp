// main.cpp : Defines the entry point for the console application.
//

#define _WIN32_DCOM

#include <stdio.h>
#include <tchar.h>

#include <comdef.h>

#include "calculator_h.h"
#include <iostream>

#pragma comment(linker, "\"/manifestdependency:name='Calculator.X' type='win32' version='1.0.0.0'\"" )

#define IS_OK( hr ) if( IS_ERROR( hr ) ) { return -1; }

int main()
{
	// Initialize COM.
	CoInitializeEx( nullptr, COINIT_APARTMENTTHREADED );
	
	// Get the ICalculator interface.
	ICalculator* pCalculator = nullptr;
	IS_OK(CoCreateInstance(
		CLSID_Calculator,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_ICalculator,
		reinterpret_cast<void**>(&pCalculator)));

	int value = 0;
	IS_OK(pCalculator->Add(20, &value));       // 0 + 20 = 20
	IS_OK(pCalculator->Add(5, &value));        // 20 + 5 = 25
	IS_OK(pCalculator->Multiply(4, &value));   // 25 * 4 = 100
	IS_OK(pCalculator->Substract(10, &value));  // 100 - 10 = 90

	std::cout << "(20 + 5) * 4 - 10 = " << value << std::endl;

	IMemory* pMemory = nullptr;
	IS_OK(pCalculator->QueryInterface(IID_IMemory, reinterpret_cast<void**>(&pMemory)));

	size_t slot;
	IS_OK(pMemory->Store(&slot));
	std::cout << "-> M" << std::endl;

	IS_OK(pCalculator->Add(10000, &value));
	std::cout << "M + 10000 = " << value << std::endl;

	IS_OK(pMemory->Recall(slot));
	IS_OK(pCalculator->Add(20000, &value));
	std::cout << "M + 20000 = " << value << std::endl;

	// Shut down COM.
	CoUninitialize();
    return 0;
}

