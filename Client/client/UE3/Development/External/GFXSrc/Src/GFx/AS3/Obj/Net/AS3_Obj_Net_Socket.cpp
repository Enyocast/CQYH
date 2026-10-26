//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_Socket.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_Socket.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Utils/AS3_Obj_Utils_ByteArray.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo Socket_ti[70] = {
        {ThunkInfo::EmptyFunc, &uintCI, "bytesAvailable", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "connected", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "endian", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "endian", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &uintCI, "objectEncoding", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "objectEncoding", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "close", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "connect", NULL, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "flush", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "readBoolean", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "readByte", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "readBytes", NULL, CT_Method, 1, 3},
        {ThunkInfo::EmptyFunc, &NumberCI, "readDouble", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &NumberCI, "readFloat", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "readInt", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "readMultiByte", NULL, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "readObject", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "readShort", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &uintCI, "readUnsignedByte", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &uintCI, "readUnsignedInt", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &uintCI, "readUnsignedShort", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "readUTF", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "readUTFBytes", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeBoolean", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeByte", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeBytes", NULL, CT_Method, 1, 3},
        {ThunkInfo::EmptyFunc, NULL, "writeDouble", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeFloat", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeInt", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeMultiByte", NULL, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "writeObject", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeShort", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUnsignedInt", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUTF", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUTFBytes", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &uintCI, "bytesAvailable", "flash.utils:IDataInput", CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "endian", "flash.utils:IDataInput", CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "endian", "flash.utils:IDataOutput", CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "endian", "flash.utils:IDataInput", CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "endian", "flash.utils:IDataOutput", CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &uintCI, "objectEncoding", "flash.utils:IDataInput", CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &uintCI, "objectEncoding", "flash.utils:IDataOutput", CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "objectEncoding", "flash.utils:IDataInput", CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "objectEncoding", "flash.utils:IDataOutput", CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "readBoolean", "flash.utils:IDataInput", CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "readByte", "flash.utils:IDataInput", CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "readBytes", "flash.utils:IDataInput", CT_Method, 1, 3},
        {ThunkInfo::EmptyFunc, &NumberCI, "readDouble", "flash.utils:IDataInput", CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &NumberCI, "readFloat", "flash.utils:IDataInput", CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "readInt", "flash.utils:IDataInput", CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "readMultiByte", "flash.utils:IDataInput", CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "readObject", "flash.utils:IDataInput", CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "readShort", "flash.utils:IDataInput", CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &uintCI, "readUnsignedByte", "flash.utils:IDataInput", CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &uintCI, "readUnsignedInt", "flash.utils:IDataInput", CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &uintCI, "readUnsignedShort", "flash.utils:IDataInput", CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "readUTF", "flash.utils:IDataInput", CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "readUTFBytes", "flash.utils:IDataInput", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeBoolean", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeByte", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeBytes", "flash.utils:IDataOutput", CT_Method, 1, 3},
        {ThunkInfo::EmptyFunc, NULL, "writeDouble", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeFloat", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeInt", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeMultiByte", "flash.utils:IDataOutput", CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "writeObject", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeShort", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUnsignedInt", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUTF", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUTFBytes", "flash.utils:IDataOutput", CT_Method, 1, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    Socket::Socket(VM& vm)
    : Traits(vm, SocketCI)
    {
//##protect##"ClassTraits::Socket::Socket()"
//##protect##"ClassTraits::Socket::Socket()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, SocketCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Socket::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Socket(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SocketCI = {
    ClassInfo::CompileTime,
    "Socket", "flash.net", &EventDispatcherCI,
    ClassTraits::Socket::MakeClassTraits,
    0,
    0,
    70,
    0,
    NULL,
    NULL,
    InstanceTraits::Socket_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

