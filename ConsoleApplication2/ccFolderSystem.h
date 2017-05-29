#ifndef __CC_FOLDER_SYSTEM_H__
#define __CC_FOLDER_SYSTEM_H__
#include "ccObjectSystem.h"

namespace DoAn
{
	class ccFolderSystem : public ccObjectSystem
	{
	public:
		static ccFolderSystem * GetFolder(const std::wstring & path, const std::wstring & name);

		ccFolderSystem();
		ccFolderSystem(const std::wstring & path, const std::wstring & name);
		virtual ~ccFolderSystem();

		virtual int init()		override;
		virtual u64 getSize()	override;

		size_t getNumberChild();
		size_t getNumberChildSub();

		//search files and folder
		extension::RKList<ccObjectSystem*> searchFile(const std::wstring & name, bool exactly);
		//list folder by size
		extension::RKList<ccObjectSystem*> listFolder(u64 size_begin, u64 size_end = 0);
		
	};
}

#endif // __CC_FOLDER_SYSTEM_H__

