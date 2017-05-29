#ifndef __CC_OBJECT_SYSTEM_H__
#define __CC_OBJECT_SYSTEM_H__

/*----------------------------------------------------------------------
Converter	:	Nguyen Thi My Linh
Email		:	1512289@student.hcmus.edu.vn
MSSV		:	1512289
File		:	ccObjectSystem.h
Description :	abstrat class define the object on system WIn32
///----------------------------------------------------------------------*/


#include <windows.h>
#include <string>
#include <wchar.h>
#include <time.h>
#include <assert.h>
#include <iostream>
#include <iomanip>
//use list define instead of STL container
#include "Utility/RKList.h"
#include "Utility/Utils.h"
namespace DoAn
{
	enum class TYPE_SYSTEM
	{
		T_NONE = 0,
		T_FILE,
		T_FOLDER,
		T_UNKNOW,
		T_COUNT
	};
	class ccObjectSystem
	{
	protected:
		TYPE_SYSTEM		   _type;
		/*
		*	name of the object system : mnust be in wchar format
		*/
		std::wstring		_name;
		std::wstring		_path_in_win;
		/*
		*	contain the child and parent
		*/
		extension::RKList<ccObjectSystem*>  _child;
		ccObjectSystem*						_parent;

		//associate with WIN32_FIND_DATA
		WIN32_FIND_DATA	*					_data_win32;

	protected:
		time_t		_getDateCreate() { return  _data_win32->ftCreationTime.dwHighDateTime; } //return at format time_t
		time_t		_getDateModifed() { return _data_win32->ftLastWriteTime.dwHighDateTime; } // return at format time_t
	public:
		static WIN32_FIND_DATA	* cloneData(WIN32_FIND_DATA data);

		ccObjectSystem();
		virtual ~ccObjectSystem();

		//pure virtual function
		virtual int	   init() = 0;
		virtual	u64	   getSize() = 0;

		//get and set method

		std::string getDateCreate(); //return at format string
		std::string getDateModified(); //return at format string

		//add child
		void addChild(ccObjectSystem * child);

		//set parent
		void setParent(ccObjectSystem * parent);

		//print
		virtual void print(int num);
		void printSubChild(int num = 0);
		void printAllChild(int num = 0);
	protected:
		void printDate(const SYSTEMTIME & st);
		void printDateCreate();
		void printDateModifed();

		std::wstring getMonth(WORD m);


	};
}

#endif // __CC_OBJECT_SYSTEM_H__

