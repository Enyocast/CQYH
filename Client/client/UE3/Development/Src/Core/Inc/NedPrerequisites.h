/*-------------------------------------------------------------------------
This source file is a part of OGRE
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
THE SOFTWARE
-------------------------------------------------------------------------*/
#ifndef __NedPrerequisites_H__
#define __NedPrerequisites_H__

/* Include all the standard header *after* all the configuration
settings have been made.
*/

#include <cstdio>
#include <cassert>
#include <numeric>
#include <limits>
#include <sstream>
#include <fstream>
#include <iostream>

#include <hash_set>
#include <hash_map>


// #if _MSC_VER >= 1600 // VC++ 10.0
// #	define HashMap ::std::tr1::unordered_map
// #    define HashSet ::std::tr1::unordered_set
// #elif _MSC_VER > 1300 && !defined(_STLP_MSVC)
// #    define HashMap ::stdext::hash_map
// #    define HashSet ::stdext::hash_set
// #else
// #    define HashMap ::std::hash_map
// #    define HashSet ::std::hash_set
// #endif


#define NED_MEMORY_TRACKER 0

#define NED_SIMD_ALIGNMENT 16

// define the memory allocator configuration to use
#define NED_MEMORY_ALLOCATOR_STD 1
#define NED_MEMORY_ALLOCATOR_NED 2
#define NED_MEMORY_ALLOCATOR_USER 3
#define NED_MEMORY_ALLOCATOR_NEDPOOLING 4

#ifndef NED_MEMORY_ALLOCATOR
#  define NED_MEMORY_ALLOCATOR NED_MEMORY_ALLOCATOR_NEDPOOLING
#endif

//Strings
#define NED_STRING_USE_CUSTOM_MEMORY_ALLOCATOR	1

//Containers
#define NED_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR 1

// #include "NedMemoryAllocatorConfig.h"

#endif // __NedPrerequisites_H__


