#include "stdafx.h"
#include "ccFolderSystem.h"
#include "ccFileSystem.h"
namespace DoAn
{
	ccFolderSystem * ccFolderSystem::GetFolder(const std::wstring & path, const std::wstring & name)
	{
		if (path == L"" || path == L"." || path == L"..")
			return nullptr;

		return new ccFolderSystem(path, name);
	}

	ccFolderSystem::ccFolderSystem()
	{
	}

	ccFolderSystem::ccFolderSystem(const std::wstring &  path, const std::wstring & name)
	{
		_name = name.c_str();
		_path_in_win = path.c_str();
		init();
	}

	ccFolderSystem::~ccFolderSystem()
	{

	}

	u64 ccFolderSystem::getSize()
	{
		u64 size_data = 0;
		for (int i = 0; i < _child.Size(); i++)
		{
			 size_data += _child.GetAt(i)->getSize();
		}
		size_data += this->_data_win32->nFileSizeLow;
		return size_data;
	}

	int ccFolderSystem::init()
	{
		if (_path_in_win == L"" || _path_in_win == L"." || _path_in_win == L"..")
			return 0;

		_type = TYPE_SYSTEM::T_FOLDER;

		//associate with WIN API to get list of file and folder in its;
		WIN32_FIND_DATA  FindFileData;
		HANDLE hFind;

		hFind = FindFirstFile((_path_in_win + L"/*.*").c_str(), &FindFileData);
		if (hFind != INVALID_HANDLE_VALUE) 
		{
			_data_win32 = ccObjectSystem::cloneData(FindFileData);
			do {
				// read all (real) files in current folder
				// , delete '!' read other 2 default folder . and ..
				WIN32_FIND_DATA  * _temp_data = ccObjectSystem::cloneData(FindFileData);
				if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

					extension::recorrectFilePath(_path_in_win);
					auto fl = ccFileSystem::GetFile(_path_in_win + FindFileData.cFileName, FindFileData.cFileName,_temp_data);
					this->addChild(fl);
				}
				else
				{
					if (wcscmp(_temp_data->cFileName , L".") != 0 && wcscmp(_temp_data->cFileName , L"..") != 0)
					{
						extension::recorrectFilePath(_path_in_win);
						auto pd = ccFolderSystem::GetFolder(_path_in_win + _temp_data->cFileName, _temp_data->cFileName);
						this->addChild(pd);
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
