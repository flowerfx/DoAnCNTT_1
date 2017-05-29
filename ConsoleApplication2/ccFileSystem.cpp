#include "stdafx.h"
#include "ccFileSystem.h"

namespace DoAn
{
	ccFileSystem * ccFileSystem::GetFile(const std::wstring & path, const std::wstring & name, WIN32_FIND_DATA * handler)
	{
		if (path == L"" || path == L"." || path == L"..")
			return nullptr;

		return new ccFileSystem(path, name , handler);
	}

	ccFileSystem::ccFileSystem()
	{
		init();
	}

	ccFileSystem::ccFileSystem(const std::wstring & path, const std::wstring & name, WIN32_FIND_DATA * handler)
	{
		_path_in_win = path.c_str();
		_name		 = name;
		_data_win32  = handler;
		init();
	}

	ccFileSystem::~ccFileSystem()
	{
	}

	int ccFileSystem::init()
	{
		if (_path_in_win == L"" || _path_in_win == L"." || _path_in_win == L"..")
			return 0;

		_type = TYPE_SYSTEM::T_FILE;
		return 1;
	}

	u64 ccFileSystem::getSize()
	{
		return _data_win32->nFileSizeLow;
	}

	void ccFileSystem::print(int num)
	{
		for (int i = 0; i < num; i++)
		{
			std::wcout << "  ";
		}
		std::wcout << L" :" << _name << " " << L" [SIZE(Byte)] :" << getSize();
		printDateCreate();
		printDateModifed();
		std::wcout << std::endl;
	}

}
