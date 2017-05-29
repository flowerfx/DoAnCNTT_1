// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "conio.h"

#include "ccFolderSystem.h"
int main()
{
	std::wstring str_path;
	wint_t wc;
	fputws(L"Input the first path: ", stdout);
	wscanf(L"%ls", str_path.c_str());

	auto pd = new DoAn::ccFolderSystem(str_path);
    return 0;
}

