#include "stdafx.h"
#include "ccObjectSystem.h"
namespace DoAn
{

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

}