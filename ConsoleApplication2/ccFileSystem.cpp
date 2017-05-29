#include "stdafx.h"
#include "ccFileSystem.h"

namespace DoAn
{
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
}
