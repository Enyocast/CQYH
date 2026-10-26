/*
    Copyright 2005-2011 Intel Corporation.  All Rights Reserved.

    The source code contained or described herein and all documents related
    to the source code ("Material") are owned by Intel Corporation or its
    suppliers or licensors.  Title to the Material remains with Intel
    Corporation or its suppliers and licensors.  The Material is protected
    by worldwide copyright laws and treaty provisions.  No part of the
    Material may be used, copied, reproduced, modified, published, uploaded,
    posted, transmitted, distributed, or disclosed in any way without
    Intel's prior express written permission.

    No license under any patent, copyright, trade secret or other
    intellectual property right is granted to or conferred upon you by
    disclosure or delivery of the Materials, either expressly, by
    implication, inducement, estoppel or otherwise.  Any license under such
    intellectual property rights must be express and approved by Intel in
    writing.
*/

#include "TypeDefinitions.h" // Customize.h and proxy.h get included

#include "../tbb/itt_notify.h" // for __TBB_load_ittnotify()

#include "../tbb/tbb_assert_impl.h" // Out-of-line TBB assertion handling routines are instantiated here.

#undef UNICODE

#if USE_PTHREAD
#include <dlfcn.h>
#elif USE_WINTHREAD
#include "tbb/machine/windows_api.h"
#endif

#if MALLOC_CHECK_RECURSION

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#if __sun
#include <string.h> /* for memset */
#include <errno.h>
#endif

#if MALLOC_LD_PRELOAD

extern "C" {

void   safer_scalable_free( void*, void (*)(void*) );
void * safer_scalable_realloc( void*, size_t, void* );

bool __TBB_internal_find_original_malloc(int num, const char *names[], void *table[])  __attribute__ ((weak));

}

#endif /* MALLOC_LD_PRELOAD */
#endif /* MALLOC_CHECK_RECURSION */

namespace rml {
namespace internal {

#if MALLOC_CHECK_RECURSION

void* (*original_malloc_ptr)(size_t) = 0;
void  (*original_free_ptr)(void*) = 0;
static void* (*original_calloc_ptr)(size_t,size_t) = 0;
static void* (*original_realloc_ptr)(void*,size_t) = 0;

#endif /* MALLOC_CHECK_RECURSION */

#if DO_ITT_NOTIFY
/** Caller is responsible for ensuring this routine is called exactly once. */
void MallocInitializeITT() {
    tbb::internal::__TBB_load_ittnotify();
}
#else
void MallocInitializeITT() {}
#endif /* DO_ITT_NOTIFY */

extern "C" 
void ITT_DoOneTimeInitialization() {
    MallocInitializeITT();
} // required for itt_notify.cpp to work

#if TBB_USE_DEBUG
#define DEBUG_SUFFIX "_debug"
#else
#define DEBUG_SUFFIX
#endif /* TBB_USE_DEBUG */

// MALLOCLIB_NAME is the name of the TBB memory allocator library.
#if _WIN32||_WIN64
#define MALLOCLIB_NAME "tbbmalloc" DEBUG_SUFFIX ".dll"
#elif __APPLE__
#define MALLOCLIB_NAME "libtbbmalloc" DEBUG_SUFFIX ".dylib"
#elif __linux__
#define MALLOCLIB_NAME "libtbbmalloc" DEBUG_SUFFIX  __TBB_STRING(.so.TBB_COMPATIBLE_INTERFACE_VERSION)
#elif __FreeBSD__ || __NetBSD__ || __sun || _AIX
#define MALLOCLIB_NAME "libtbbmalloc" DEBUG_SUFFIX ".so"
#else
#error Unknown OS
#endif

void init_tbbmalloc() {
#if MALLOC_LD_PRELOAD
    if (malloc_proxy && __TBB_internal_find_original_malloc) {
        const char *alloc_names[] = { "malloc", "free", "realloc", "calloc"};
        void *orig_alloc_ptrs[4];

        if (__TBB_internal_find_original_malloc(4, alloc_names, orig_alloc_ptrs)) {
            (void *&)original_malloc_ptr  = orig_alloc_ptrs[0];
            (void *&)original_free_ptr    = orig_alloc_ptrs[1];
            (void *&)original_realloc_ptr = orig_alloc_ptrs[2];
            (void *&)original_calloc_ptr  = orig_alloc_ptrs[3];
            MALLOC_ASSERT( original_malloc_ptr!=malloc_proxy,
                           "standard malloc not found" );
/* It's workaround for a bug in GNU Libc 2.9 (as it shipped with Fedora 10).
   1st call to libc's malloc should be not from threaded code.
 */
            original_free_ptr(original_malloc_ptr(1024));
            original_malloc_found = 1;
        }
    }
#endif /* MALLOC_LD_PRELOAD */

#if DO_ITT_NOTIFY
    MallocInitializeITT();
#endif

/* Preventing TBB allocator library from unloading to prevent
   resource leak, as memory is not released on the library unload.
*/
#if USE_WINTHREAD && __TBB_DYNAMIC_LOAD_ENABLED
    // Prevent Windows from displaying message boxes if it fails to load library
    UINT prev_mode = SetErrorMode (SEM_FAILCRITICALERRORS);
    LoadLibrary(MALLOCLIB_NAME);
    SetErrorMode (prev_mode);
#endif /* USE_PTHREAD */
}

#if !(_WIN32||_WIN64)
struct RegisterProcessShutdownNotification {
    RegisterProcessShutdownNotification() {
#if USE_PTHREAD && __TBB_DYNAMIC_LOAD_ENABLED
        // prevents unloading, POSIX case
        dlopen(MALLOCLIB_NAME, RTLD_NOW);
#endif
    }
    ~RegisterProcessShutdownNotification() {
        mallocProcessShutdownNotification();
    }
};

static RegisterProcessShutdownNotification reg;
#endif

#if MALLOC_CHECK_RECURSION

bool  original_malloc_found;

#if MALLOC_LD_PRELOAD

extern "C" {

void * __TBB_internal_malloc(size_t size)
{
    return scalable_malloc(size);
}

void * __TBB_internal_calloc(size_t num, size_t size)
{
    return scalable_calloc(num, size);
}

int __TBB_internal_posix_memalign(void **memptr, size_t alignment, size_t size)
{
    return scalable_posix_memalign(memptr, alignment, size);
}

void* __TBB_internal_realloc(void* ptr, size_t sz)
{
    return safer_scalable_realloc(ptr, sz, (void*&)original_realloc_ptr);
}

void __TBB_internal_free(void *object)
{
    safer_scalable_free(object, original_free_ptr);
}

} /* extern "C" */

#endif /* MALLOC_LD_PRELOAD */

#endif /* MALLOC_CHECK_RECURSION */

#include "../tbb/tbb_version.h"

/** The leading "\0" is here so that applying "strings" to the binary
    delivers a clean result.
    volatile added to prevent possible dropping of constant by linker. */
volatile char VersionString[] = "\0" TBB_VERSION_STRINGS;

} } // namespaces

#ifdef _WIN32

extern "C" BOOL WINAPI DllMain( HINSTANCE hInst, DWORD callReason, LPVOID )
{

    if (callReason==DLL_THREAD_DETACH)
    {
        mallocThreadShutdownNotification(NULL);
    }
    else if (callReason==DLL_PROCESS_DETACH)
    {
        mallocProcessShutdownNotification();
    }
    return TRUE;
}

#endif //_WIN32

#if __TBB_ipf
/* It was found that on IPF inlining of __TBB_machine_lockbyte leads
   to serious performance regression with ICC 10.0. So keep it out-of-line.

   This code is copy-pasted from tbb_misc.cpp.
 */
extern "C" intptr_t __TBB_machine_lockbyte( volatile unsigned char& flag ) {
    if ( !__TBB_TryLockByte(flag) ) {
        tbb::internal::atomic_backoff b;
        do {
            b.pause();
        } while ( !__TBB_TryLockByte(flag) );
    }
    return 0;
}
#endif
