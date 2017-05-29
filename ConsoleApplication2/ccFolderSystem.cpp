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

	extension::RKList<ccObjectSystem*> ccFolderSystem::searchFile(const std::wstring & name, bool exactly)
	{
		extension::RKList<ccObjectSystem*> res;
		for (int i = 0; i < _child.Size(); i++)
		{
			auto c = _child[i];
			if (c->getType() == TYPE_SYSTEM::T_FILE)
			{
				auto exname = c->getName();
				if (!exactly)
				{
					std::size_t found = exname.find(name);
					if (found != std::wstring::npos)
					{
						res.Insert(c, res.Size());
					}
				}
				else
				{
					if (exname == name)
					{
						res.Insert(c, res.Size());
					}
				}
			}
			else
			{
				auto res_child = static_cast<ccFolderSystem*>(c)->searchFile(name, exactly);
				for (int j = 0; j < res_child.Size(); j++)
				{
					res.Insert(res_child[j], res.Size());
				}
			}
		}
		return res;
	}
	//list folder by size
	extension::RKList<ccObjectSystem*> ccFolderSystem::listFolder(u64 size_begin, u64 size_end)
	{
		extension::RKList<ccObjectSystem*> res;
		for (int i = 0; i < _child.Size(); i++)
		{
			auto c = _child[i];
			if (c->getType() == TYPE_SYSTEM::T_FOLDER)
			{
				u64 size_folder = c->getSize();
				if (size_end == 0)
				{
					if (size_begin == size_folder) //exactly 
					{
						res.Insert(c, res.Size());
					}
				}
				else
				{
					if(size_folder <= size_end && size_folder >= size_begin)
					{
						res.Insert(c, res.Size());
					}
				}

				auto res_child = static_cast<ccFolderSystem*>(c)->listFolder(size_begin, size_end);
				for (int j = 0; j < res_child.Size(); j++)
				{
					res.Insert(res_child[j], res.Size());
				}
			}
		}
		return res;
	}
}
