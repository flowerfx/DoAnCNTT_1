#ifndef __RK_HEAP_H__
#define __RK_HEAP_H__
#include <crtdbg.h>
#include <new>
typedef size_t uint32;
typedef unsigned long long u64;
#define RKASSERT(x , msg)
#define RKMAX(a,b)           (((a) > (b)) ? (a) : (b))
#define RKMIN(a,b)           (((a) < (b)) ? (a) : (b))
#define RKSQUARE(a)          (a*a)
#define RKCLAMP(MIN,MAX,VAL) (RKMAX(MIN,RKMIN(MAX,VAL)))
namespace extension
{
	void* RKHeap_Alloc(uint32 size, const char* tag);

	void* RKHeap_AllocAndZero(uint32 size, const char* tag);

	void* RKHeap_Realloc(void* p, uint32 newSize);

	void  RKHeap_Free(void* p, const char* tag);

	void* RKHeap_AllocAligned(uint32 size, uint32 alignment, const char *tag);
	void  RKHeap_FreeAligned(void* p, const char *tag);
	uint32 RKHeap_GetUsage();

	void RKHeap_CheckIntegrity();
}
#endif //