//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filesystem_File.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filesystem_File.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class Icon;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo File_ti[33] = {
        {ThunkInfo::EmptyFunc, &BooleanCI, "exists", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &IconCI, "icon", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isDirectory", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isHidden", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isPackage", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isSymbolicLink", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "nativePath", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "nativePath", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &FileCI, "parent", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "url", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "url", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "browseForDirectory", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "browseForOpen", NULL, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "browseForOpenMultiple", NULL, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "browseForSave", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "cancel", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "canonicalize", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &FileCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "copyTo", NULL, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "copyToAsync", NULL, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "createDirectory", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "deleteDirectory", NULL, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "deleteDirectoryAsync", NULL, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "deleteFile", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "deleteFileAsync", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &ArrayCI, "getDirectoryListing", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "getDirectoryListingAsync", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "getRelativePath", NULL, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "moveTo", NULL, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "moveToAsync", NULL, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "moveToTrash", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "moveToTrashAsync", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &FileCI, "resolvePath", NULL, CT_Method, 1, 1},
    };

} // namespace InstanceTraits

namespace Classes
{
    File::File(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::File::File()"
//##protect##"class_::File::File()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const ThunkInfo File_ti[7] = {
        {ThunkInfo::EmptyFunc, &FileCI, "applicationDirectory", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &FileCI, "applicationStorageDirectory", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &FileCI, "desktopDirectory", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &FileCI, "documentsDirectory", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &FileCI, "createTempDirectory", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &FileCI, "createTempFile", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &ArrayCI, "getRootDirectories", NULL, CT_Method, 0, 0},
    };
    File::File(VM& vm)
    : Traits(vm, FileCI)
    {
//##protect##"ClassTraits::File::File()"
//##protect##"ClassTraits::File::File()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, FileCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::File(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> File::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) File(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FileCI = {
    ClassInfo::CompileTime,
    "File", "flash.filesystem", &FileReferenceCI,
    ClassTraits::File::MakeClassTraits,
    7,
    0,
    33,
    0,
    ClassTraits::File_ti,
    NULL,
    InstanceTraits::File_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

