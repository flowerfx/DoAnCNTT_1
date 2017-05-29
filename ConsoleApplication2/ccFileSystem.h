#ifndef __CC_FILE_SYSTEM_H__
#define __CC_FILE_SYSTEM_H__
#include "ccObjectSystem.h"

namespace DoAn
{
	class ccFileSystem : public ccObjectSystem
	{
	public:
		ccFileSystem();
		ccFileSystem(const std::wstring & path, const std::wstring & name, WIN32_FIND_DATA * handler);
		~ccFileSystem();

		virtual int init()		override;
		virtual u64 getSize()	override;
	};
}

#endif // __CC_FILE_SYSTEM_H__

