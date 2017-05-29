#include "RKHeap.h"
#include <algorithm>
#include <vector>
namespace extension
{
	void* RKHeap_Alloc(uint32 size, const char* tag)
	{
		return malloc(size);
	}

	void* RKHeap_AllocAndZero(uint32 size, const char* tag)
	{
		void* p = malloc(size);
		if (p)
		{
			memset(p, 0, size);
		}
		return p;
	}

	void* RKHeap_Realloc(void* p, uint32 newSize)
	{
		return realloc(p, newSize);
	}

	void  RKHeap_Free(void* p, const char* tag)
	{
		free(p);
	}

	void* RKHeap_AllocAligned(uint32 size, uint32 alignment, const char *tag)
	{
		return _aligned_malloc(size, alignment);
	}

	void  RKHeap_FreeAligned(void* p, const char *tag)
	{
		_aligned_free(p);
	}

	uint32 RKHeap_GetUsage()
	{
		return 0;
	}

	void RKHeap_CheckIntegrity()
	{
		if (_CrtCheckMemory() != 1)
		{
			RKASSERT(0, "Some memory has been corrupted!");
			char *p = 0; *p = 0;  //temp for disabled asserts..
		}
	}
}