// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "conio.h"

#include "ccFolderSystem.h"

void printListFileResult(extension::RKList<DoAn::ccObjectSystem*> res)
{
	if (res.Size() > 0)
	{
		for (int i = 0; i < res.Size(); i++)
		{
			auto c = res[i];
			std::wcout << L"[NAME] : " << c->getName() << " " << L"[PATH] : " << c->getPath() << std::endl;
		}
	}
	else
	{
		std::wcout << "ERROR : NO MATCHING FILE FOUND !";
	}
	std::wcout << std::endl;
}

void printListFOLDERResult(extension::RKList<DoAn::ccObjectSystem*> res)
{
	if (res.Size() > 0)
	{
		for (int i = 0; i < res.Size(); i++)
		{
			auto c = res[i];
			std::wcout << L"[NAME] : " << c->getName() << " " << L"[PATH] : " << c->getPath() << L"[SIZE] : " << c->getSize() << std::endl;
		}
	}
	else
	{
		std::wcout << "ERROR : NO MATCHING FOLDER FOUND !";
	}
	std::wcout << std::endl;
}

int main()
{
	std::wstring str_path;
	wint_t wc;
	fputws(L"Input the first path: ", stdout);
	wscanf(L"%ls", str_path.c_str());

	auto pd = new DoAn::ccFolderSystem(str_path, str_path);

	pd->printAllChild();

	std::wcout << L"SORT PATH AS DATE CREATE:" << std::endl;
	pd->sortChildAsCreateDate(0);
	pd->printAllChild();

	std::wcout << L"SORT PATH AS DATE MODIFIED:" << std::endl;
	pd->sortChildAsModifedDate(0);
	pd->printAllChild();

	std::wcout << L"SORT PATH AS SIZE:" << std::endl;
	pd->sortChildAsSize(0);
	pd->printAllChild();

	std::wcout << L"FIND ALL FILE WITH NAME: vc141.idb" << std::endl;
	auto res = pd->searchFile(L"vc141.idb", true);
	printListFileResult(res);

	std::wcout << L"FIND ALL FILE WITH CONTAIN NAME: System" << std::endl;
	res = pd->searchFile(L"System", false);
	printListFileResult(res);

	std::wcout << L"LIST ALL FOLDER WITH SIZE : 507,127 Byte" << std::endl;
	res = pd->listFolder(507127, 0);
	printListFOLDERResult(res);

	std::wcout << L"LIST ALL FOLDER WITH SIZE : 100000 Byte" << std::endl;
	res = pd->listFolder(100000, 0);
	printListFOLDERResult(res);

	std::wcout << L"LIST ALL FOLDER WITH SIZE FROM 100 Byte TO 1000000 Byte" << std::endl;
	res = pd->listFolder(100, 1000000);
	printListFOLDERResult(res);

    return 0;
}

