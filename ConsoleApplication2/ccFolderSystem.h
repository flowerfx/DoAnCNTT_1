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

		ccObjectSystem* findChildByPath(const std::wstring & path);
		extension::RKList<ccObjectSystem*> findListChildInPath(const std::wstring & path);
		extension::RKList<ccObjectSystem*> findChildByName(const std::wstring & name);
		extension::RKList<ccObjectSystem*> findChildByExtension(const std::wstring & ex);


	};
}

#endif // __CC_FOLDER_SYSTEM_H__

