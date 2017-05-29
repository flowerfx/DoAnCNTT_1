#include "stdafx.h"
#include "ccFolderSystem.h"

namespace DoAn
{
	ccFolderSystem * ccFolderSystem::GetFolder(const std::wstring & path)
	{
		if (path == L"" || path == L"." || path == L"..")
			return nullptr;

		return new ccFolderSystem(path);
	}

	ccFolderSystem::ccFolderSystem()
	{
	}

	ccFolderSystem::ccFolderSystem(const std::wstring &  path)
	{
		_path_in_win = path.c_str();
		init();
	}

	ccFolderSystem::~ccFolderSystem()
	{

	}

	u64 ccFolderSystem::getSize()
	{
		u64 size_data;
		for (int i = 0; i < _child.Size(); i++)
		{
			return size_data += _child.GetAt(i)->getSize();
		}
		return size_data;
	}

	int ccFolderSystem::init()
	{
		if (_path_in_win == L"" || _path_in_win == L"." || _path_in_win == L"..")
			return 0;

		_type = TYPE_SYSTEM::T_FOLDER;

		//associate with WIN API to get list of file and folder in its;
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind;

		hFind = FindFirstFile((_path_in_win + L"/*.*").c_str(), &FindFileData);
		if (hFind != INVALID_HANDLE_VALUE) 
		{
			_data_win32 = &FindFileData;
			do {
				// read all (real) files in current folder
				// , delete '!' read other 2 default folder . and ..
				if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {


					//names.push_back(FindFileData.cFileName);
				}
				else
				{
					if (wcscmp(FindFileData.cFileName , L".") != 0 && wcscmp(FindFileData.cFileName , L"..") != 0)
					{
						extension::recorrectFilePath(_path_in_win);
						auto pd = ccFolderSystem::GetFolder(_path_in_win + FindFileData.cFileName);
						if (pd)
						{
							this->_child.Insert(pd, this->_child.Size());
						}
					}
				}
			} while (::FindNextFile(hFind, &FindFileData));
			::FindClose(hFind);
		}
		else
		{
			//assert(false);
			//printf_s(" ");
		}
		return 1;
	}

	ccObjectSystem* ccFolderSystem::findChildByPath(const std::wstring & path)
	{
		ccObjectSystem* res = nullptr;

		return res;
	}

	extension::RKList<ccObjectSystem*> ccFolderSystem::findListChildInPath(const std::wstring & path)
	{
		extension::RKList<ccObjectSystem*> res;

		return res;
	}

	extension::RKList<ccObjectSystem*> ccFolderSystem::findChildByName(const std::wstring & name)
	{
		extension::RKList<ccObjectSystem*> res;

		return res;
	}

	extension::RKList<ccObjectSystem*> ccFolderSystem::findChildByExtension(const std::wstring & ex)
	{
		extension::RKList<ccObjectSystem*> res;

		return res;
	}
}
