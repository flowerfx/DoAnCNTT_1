#include "stdafx.h"
#include "ccObjectSystem.h"
namespace DoAn
{

	WIN32_FIND_DATA	* ccObjectSystem::cloneData(WIN32_FIND_DATA data)
	{
		WIN32_FIND_DATA * res = new WIN32_FIND_DATA();
		memcpy(res, &data, sizeof(WIN32_FIND_DATA));
		return res;
	}

	ccObjectSystem::ccObjectSystem()
		: _name(L"")
		, _path_in_win(L"")
		, _parent(nullptr)
		, _type(TYPE_SYSTEM::T_NONE)
	{
	}


	ccObjectSystem::~ccObjectSystem()
	{

	}


	//get and set method
	std::string ccObjectSystem::getDateCreate()
	{
		return "";
	}

	std::string ccObjectSystem::getDateModified()
	{
		return "";
	}

	void ccObjectSystem::addChild(ccObjectSystem * child)
	{
		if (child)
		{
			child->setParent(this);
			this->_child.Insert(child, this->_child.Size());
		}
	}

	void ccObjectSystem::setParent(ccObjectSystem * parent)
	{
		this->_parent = parent;
	}

	std::wstring ccObjectSystem::getMonth(WORD m)
	{
		if (m == 1)
			return L"Jan";
		else if (m == 2)
			return L"Feb";
		else if (m == 3)
			return L"Mar";
		else if (m == 4)
			return L"Apr";
		else if (m == 5)
			return L"May";
		else if (m == 6)
			return L"Jun";
		else if (m == 7)
			return L"Jul";
		else if (m == 8)
			return L"Aug";
		else if (m == 9)
			return L"Sep";
		else if (m == 10)
			return L"Oct";
		else if (m == 11)
			return L"Nov";
		return L"Dec";
	}

	void ccObjectSystem::printDate(const SYSTEMTIME & st)
	{
		std::wcout << st.wHour << L":" << st.wMinute << L" "<< getMonth(st.wMonth) << L"/" << st.wDay << L"/" << st.wYear;
	}

	void ccObjectSystem::printDateCreate()
	{
		SYSTEMTIME st;
		FileTimeToSystemTime(&(_data_win32->ftCreationTime), &st);

		std::wcout << L" [CRE] ";
		printDate(st);
	}
	void ccObjectSystem::printDateModifed()
	{
		SYSTEMTIME st;
		FileTimeToSystemTime(&(_data_win32->ftLastWriteTime), &st);

		std::wcout << L" [MOD] ";
		printDate(st);
	}

	void ccObjectSystem::print(int num)
	{
		for (int i = 0; i < num; i++)
		{
			std::wcout << "  ";
		}
		std::wcout << L"[ " << _name << L" ]" << " " << L"[PATH : " << _path_in_win << L" ]" << " " << L"[DIR SIZE(Byte)] :" << getSize();
		printDateCreate();
		printDateModifed();
		std::wcout << std::endl;
	}

	void ccObjectSystem::printSubChild(int num)
	{
		print(num);

		for (int i = 0; i < _child.Size(); i++)
		{
			_child[i]->print(num + 1);
		}
	}

	void ccObjectSystem::printAllChild(int num)
	{
		print(num);
		for (int i = 0; i < _child.Size(); i++)
		{
			_child[i]->printAllChild(num + 1);
		}
	}
}