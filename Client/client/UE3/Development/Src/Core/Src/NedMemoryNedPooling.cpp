/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2009 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "CorePrivate.h"
// #include "NedPrerequisites.h"
#include "NedMemoryNedPooling.h"
// #include "NedMemoryTracker.h"

void __ned_free_thread_cache(DWORD threadID)
{
#if !_WIN64
	NedMemory::NedPoolingImpl::freeThreadAllCache(threadID);
#endif
}


#if NED_MEMORY_ALLOCATOR == NED_MEMORY_ALLOCATOR_NEDPOOLING

#pragma warning(push)
#pragma warning(disable : 4565 4706)
// include ned implementation
#include "nedmalloc/nedmalloc.c"
#pragma warning(pop)

namespace NedMemory
{
	namespace _NedPoolingIntern
	{
		const size_t s_poolCount = 14; // Needs to be greater than 4
		void* s_poolFootprint = reinterpret_cast<void*>(0xBB1AA45A);
		nedalloc::nedpool* s_pools[s_poolCount + 1] = { 0 };
		nedalloc::nedpool* s_poolsAligned[s_poolCount + 1] = { 0 };

		size_t poolIDFromSize(size_t a_reqSize)
		{
			// Requests size 16 or smaller are allocated at a 4 byte granularity.
			// Requests size 17 or larger are allocated at a 16 byte granularity.
			// With a s_poolCount of 14, requests size 177 or larger go in the default pool.

			// spreadsheet style =IF(B35<=16; FLOOR((B35-1)/4;1); MIN(FLOOR((B35-1)/16; 1) + 3; 14))

			size_t poolID = 0;

			if (a_reqSize > 0)
			{
				if (a_reqSize <= 16)
				{
					poolID = (a_reqSize - 1) >> 2;
				}
				else
				{
					poolID = std::min<size_t>(((a_reqSize - 1) >> 4) + 3, s_poolCount);
				}
			}

			return poolID;
		}

		void internalFree(void* a_mem)
		{
			if (a_mem)
			{
				nedalloc::nedpool* pool(0);

				// nedalloc lets us get the pool pointer from the memory pointer
				void* footprint = nedalloc::nedgetvalue(&pool, a_mem);

				// Check footprint
				if (footprint == s_poolFootprint)
				{
					// If we allocated the pool, deallocate from this pool...
					nedalloc::nedpfree(pool, a_mem);
				}
				else
				{
					// ...otherwise let nedalloc handle it.
					nedalloc::nedfree(a_mem);
				}
			}
		}

		void pfreeThreadCache(nedalloc::nedpool* p, DWORD threadID, size_t debugPoolIdx)
		{
#ifdef _DEBUG
			DWORD thrdID = CURRENT_THREAD;			
#endif
			ACQUIRE_LOCK(&p->mutex);			
			for (int j = 0; j < THREADCACHEMAXCACHES; ++j)
			{
				nedalloc::threadcache* tc = p->caches[j];
				if(tc && tc->threadid == threadID)
				{
					int n = tc->mymspace;
#if 0
					
					const int MaxBlkSz = (THREADCACHEMAXBINS+1)*2;
					for (int k = 0; k < MaxBlkSz; ++k)
					{
						nedalloc::threadcacheblk* mem = tc->bins[k];
						if(mem)
						{
							//nedalloc::threadcache_free(p, tc, tc->mymspace, mem, mem->size);
							nedalloc::nedpfree(p, mem);
						}
					}
#else
					// already freed
					//internalFree((void*)tc);

					tc->frees++;
					RemoveCacheEntries(p, tc, 0);
					assert(!tc->freeInCache);
					tc->mymspace=-1;
					tc->threadid=0;
					mspace_free(0, tc);
					p->caches[j]=0;

					//destroy_mspace(p->m[n]);
					//p->m[n] = 0;
#endif
				}
			}
			RELEASE_LOCK(&p->mutex);
		}

		void freeThreadCache(nedalloc::nedpool* p, DWORD threadID, size_t debugPoolIdx)
		{
#ifdef _DEBUG
			DWORD thrdID = CURRENT_THREAD;			
#endif
			ACQUIRE_LOCK(&p->mutex);			
			for (int j = 0; j < THREADCACHEMAXCACHES; ++j)
			{
				nedalloc::threadcache* tc = p->caches[j];
				if(tc && tc->threadid == threadID)
				{
					int n = tc->mymspace;

					// already freed
					//internalFree((void*)tc);

					tc->frees++;
					RemoveCacheEntries(p, tc, 0);
					assert(!tc->freeInCache);
					tc->mymspace=-1;
					tc->threadid=0;
					mspace_free(0, tc);
					p->caches[j]=0;

					//destroy_mspace(p->m[n]);
					//p->m[n] = 0;
				}
			}
			RELEASE_LOCK(&p->mutex);
		}

		void internalFreeThreadAllCache(DWORD threadID)
		{
			for (size_t i = 0; i < s_poolCount; ++i)
			{
				nedalloc::nedpool* p = s_pools[i];
				if(p)
				{
					//freeThreadCache(p, threadID, i);
					neddisablethreadcache(p);

				}
				
				p = s_poolsAligned[i];
				if(p)
				{
					//pfreeThreadCache(p, threadID, i);
					neddisablethreadcache(p);
				}
			}
		}

		void* internalAlloc(size_t a_reqSize)
		{
			size_t poolID = poolIDFromSize(a_reqSize);
			nedalloc::nedpool* pool(0); // A pool pointer of 0 means the default pool.

			if (poolID < s_poolCount)
			{
				if (s_pools[poolID] == 0)
				{
					// Init pool if first use

					s_pools[poolID] = nedalloc::nedcreatepool(0, 8);
					nedalloc::nedpsetvalue(s_pools[poolID], s_poolFootprint); // All pools are stamped with a footprint
				}

				pool = s_pools[poolID];
			}

			return nedalloc::nedpmalloc(pool, a_reqSize);
		}

		void* internalAllocAligned(size_t a_align, size_t a_reqSize)
		{
			size_t poolID = poolIDFromSize(a_reqSize);
			nedalloc::nedpool* pool(0); // A pool pointer of 0 means the default pool.

			if (poolID < s_poolCount)
			{
				if (s_poolsAligned[poolID] == 0)
				{
					// Init pool if first use

					s_poolsAligned[poolID] = nedalloc::nedcreatepool(0, 8);
					nedalloc::nedpsetvalue(s_poolsAligned[poolID], s_poolFootprint); // All pools are stamped with a footprint
				}

				pool = s_poolsAligned[poolID];
			}

			return nedalloc::nedpmemalign(pool, a_align, a_reqSize);
		}

		void* internalRealloc(void* mem, size_t a_reqSize)
		{
			if(mem)
			{
				nedalloc::nedpool* pool(0);

				// nedalloc lets us get the pool pointer from the memory pointer
				void* footprint = nedalloc::nedgetvalue(&pool, mem);

				// Check footprint
				if (footprint == _NedPoolingIntern::s_poolFootprint)
				{
					return nedalloc::nedprealloc(pool, mem, a_reqSize);
				}
				else
				{
					return nedalloc::nedrealloc(mem, a_reqSize);
				}
			}
			else
			{
				return internalAlloc(a_reqSize);
			}
		}

		void* internalReallocAligned(size_t a_align, void* mem, size_t a_reqSize)
		{
			if (a_reqSize == 0)
			{
				internalFree(mem);
				return NULL;
			}

			// todo: optimize if mem is bigger than a_reqSize, 

			if(mem)
			{
				//size_t memsize=nedalloc::nedblksize(mem);
				size_t memsize=nedalloc::nedmemsize(mem);
				//if (memsize >= a_reqSize)
				//{
				//	return mem;
				//}
				//else
				{
					void* pNew = internalAllocAligned(a_align, a_reqSize);
					memcpy(pNew, mem, memsize < a_reqSize ? memsize : a_reqSize);
					internalFree(mem);
					return pNew;
				}
			}
			else
			{
				return internalAllocAligned(a_align, a_reqSize);
			}
		}

// 		void trim()
// 		{
// 			//nedalloc:
// 		}
	}

	//---------------------------------------------------------------------
	void* NedPoolingImpl::allocBytes(size_t count, 
		const char* file, int line, const char* func)
	{
		void* ptr = _NedPoolingIntern::internalAlloc(count);
#if NED_MEMORY_TRACKER
		MemoryTracker::get()._recordAlloc(ptr, count, 0, file, line, func);
#else
		// avoid unused params warning
		file = func = "";
        line = 0;
#endif
		return ptr;
	}
	//---------------------------------------------------------------------
	void NedPoolingImpl::deallocBytes(void* ptr)
	{
		// deal with null
		if (!ptr)
			return;
#if NED_MEMORY_TRACKER
		MemoryTracker::get()._recordDealloc(ptr);
#endif
		_NedPoolingIntern::internalFree(ptr);
	}
	//---------------------------------------------------------------------
	void* NedPoolingImpl::reallocBytes(void *mem, size_t size)
	{
		return _NedPoolingIntern::internalRealloc(mem, size);
	}
	//---------------------------------------------------------------------
	void* NedPoolingImpl::allocBytesAligned(size_t align, size_t count, 
		const char* file, int line, const char* func)
	{
		// default to platform SIMD alignment if none specified
		void* ptr =  align ? _NedPoolingIntern::internalAllocAligned(align, count)
			: _NedPoolingIntern::internalAllocAligned(NED_SIMD_ALIGNMENT, count);
#if NED_MEMORY_TRACKER
		MemoryTracker::get()._recordAlloc(ptr, count, 0, file, line, func);
#else
		// avoid unused params warning
		file = func = "";
        line = 0;
#endif
		return ptr;
	}
	//---------------------------------------------------------------------
	void NedPoolingImpl::deallocBytesAligned(size_t align, void* ptr)
	{
		// deal with null
		if (!ptr)
			return;
#if NED_MEMORY_TRACKER
		MemoryTracker::get()._recordDealloc(ptr);
#endif
		_NedPoolingIntern::internalFree(ptr);
	}

	void* NedPoolingImpl::reallocBytesAligned(size_t align, void *mem, size_t size)
	{
		return _NedPoolingIntern::internalReallocAligned(align, mem, size);
	}

	void NedPoolingImpl::freeThreadAllCache( DWORD threadID )
	{
		_NedPoolingIntern::internalFreeThreadAllCache(threadID);
	}

	int NedPoolingImpl::memsize( void* mem )
	{
		return nedalloc::nedmemsize(mem);;
		//return nedalloc::nedblksize(mem);
	}

// 	void NedPoolingImpl::trim()
// 	{
// 		return _NedPoolingIntern::trim();
// 	}

}


#endif

