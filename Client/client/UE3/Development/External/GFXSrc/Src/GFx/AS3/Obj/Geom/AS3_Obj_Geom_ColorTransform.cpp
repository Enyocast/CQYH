//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_ColorTransform.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Geom_ColorTransform.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::ColorTransform, Instances::ColorTransform::mid_colorGet, UInt32> TFunc_Instances_ColorTransform_colorGet;
typedef ThunkFunc1<Instances::ColorTransform, Instances::ColorTransform::mid_colorSet, Value, UInt32> TFunc_Instances_ColorTransform_colorSet;
typedef ThunkFunc1<Instances::ColorTransform, Instances::ColorTransform::mid_concat, Value, Instances::ColorTransform*> TFunc_Instances_ColorTransform_concat;
typedef ThunkFunc0<Instances::ColorTransform, Instances::ColorTransform::mid_toString, ASString> TFunc_Instances_ColorTransform_toString;

template <> const TFunc_Instances_ColorTransform_colorGet::TMethod TFunc_Instances_ColorTransform_colorGet::Method = &Instances::ColorTransform::colorGet;
template <> const TFunc_Instances_ColorTransform_colorSet::TMethod TFunc_Instances_ColorTransform_colorSet::Method = &Instances::ColorTransform::colorSet;
template <> const TFunc_Instances_ColorTransform_concat::TMethod TFunc_Instances_ColorTransform_concat::Method = &Instances::ColorTransform::concat;
template <> const TFunc_Instances_ColorTransform_toString::TMethod TFunc_Instances_ColorTransform_toString::Method = &Instances::ColorTransform::toString;

namespace Instances
{
    ColorTransform::ColorTransform(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , alphaMultiplier()
    , alphaOffset()
    , blueMultiplier()
    , blueOffset()
    , greenMultiplier()
    , greenOffset()
    , redMultiplier()
    , redOffset()
//##protect##"instance::ColorTransform::ColorTransform()$data"
//##protect##"instance::ColorTransform::ColorTransform()$data"
    {
//##protect##"instance::ColorTransform::ColorTransform()$code"
        alphaMultiplier = blueMultiplier = greenMultiplier = redMultiplier =  1.0;
        alphaOffset = blueOffset = greenOffset = redOffset = 0;
//##protect##"instance::ColorTransform::ColorTransform()$code"
    }

    void ColorTransform::colorGet(UInt32& result)
    {
//##protect##"instance::ColorTransform::colorGet()"
        UInt8 rc = (UInt8)redOffset;
		UInt8 bc = (UInt8)blueOffset;
		UInt8 gc = (UInt8)greenOffset;

		result = (rc << 16) | (gc << 8) | bc;
//##protect##"instance::ColorTransform::colorGet()"
    }
    void ColorTransform::colorSet(Value& result, UInt32 value)
    {
//##protect##"instance::ColorTransform::colorSet()"
		// When you set this property, it changes the three color offset values 
		// (redOffset, greenOffset, and blueOffset) accordingly, and it sets the 
		// three color multiplier values (redMultiplier, greenMultiplier, and 
		// blueMultiplier) to 0. The alpha transparency multiplier and offset 
		// values do not change.
        // first extract rgb components out of value
		UInt32 rc = 0, gc = 0, bc = 0;
		rc = (value >> 16) & 0x000000ff;
		gc = (value >> 8) & 0x000000ff;
		bc = value & 0x000000ff;
		
		redMultiplier = greenMultiplier = blueMultiplier = 0;
		redOffset = static_cast<float>(rc);
		greenOffset = static_cast<float>(gc);
		blueOffset = static_cast<float>(bc);

		result.SetUndefined();
//##protect##"instance::ColorTransform::colorSet()"
    }
    void ColorTransform::concat(Value& result, Instances::ColorTransform* second)
    {
//##protect##"instance::ColorTransform::concat()"
		redOffset += redMultiplier*second->redOffset;
		blueOffset += blueMultiplier*second->blueOffset;
		greenOffset += greenMultiplier*second->greenOffset;
		alphaOffset += alphaMultiplier*second->alphaOffset;

		redMultiplier *= second->redMultiplier;
		greenMultiplier *= second->greenMultiplier;
		blueMultiplier *= second->blueMultiplier;
		alphaMultiplier *= second->alphaMultiplier;

		result.SetUndefined();
		
//##protect##"instance::ColorTransform::concat()"
    }
    void ColorTransform::toString(ASString& result)
    {
//##protect##"instance::ColorTransform::toString()"
		result += GetStringManager().CreateConstString("(redMultiplier=") + GetVM().AsString(Value(redMultiplier)) + 
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("greenMultiplier=") + 
			GetVM().AsString(Value(greenMultiplier)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("blueMultiplier=") + 
			GetVM().AsString(Value(blueMultiplier)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("alphaMultiplier=") + 
			GetVM().AsString(Value(alphaMultiplier)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("redOffset=") + 
			GetVM().AsString(Value(redOffset)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("greenOffset=") + 
			GetVM().AsString(Value(greenOffset)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("blueOffset=") + 
			GetVM().AsString(Value(blueOffset)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("alphaOffset=") + 
			GetVM().AsString(Value(alphaOffset)) +
			GetStringManager().CreateConstString(")");
//##protect##"instance::ColorTransform::toString()"
    }

//##protect##"instance$methods"
	void ColorTransform::AS3Constructor(unsigned argc, const Value* argv)
	{
		// Initialize to default values

		if (argc > 0)
		{
			// According to doc, x will not be modified if there is an exception
			if (!argv[0].Convert2Number(redMultiplier))
			{
				return;
			}
			if (argc > 1)
			{
				if (!argv[1].Convert2Number(greenMultiplier))
				{
					return;
				}
				if (argc > 2)
				{
					if (!argv[2].Convert2Number(blueMultiplier))
					{
						return;
					}
					if (argc > 3)
					{
						if (!argv[3].Convert2Number(alphaMultiplier))
						{
							return;
						}
						if (argc > 4)
						{
							if (!argv[4].Convert2Number(redOffset))
							{
								return;
							}
							if (argc > 5)
							{
								if (!argv[5].Convert2Number(greenOffset))
								{
									return;
								}
								if (argc > 6)
								{
									if (!argv[6].Convert2Number(blueOffset))
									{
										return;
									}
									if (argc > 7)
									{
										if (!argv[7].Convert2Number(alphaOffset))
										{
											return;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo ColorTransform::ti[ColorTransform::ThunkInfoNum] = {
        {TFunc_Instances_ColorTransform_colorGet::Func, &uintCI, "color", NULL, CT_Get, 0, 0},
        {TFunc_Instances_ColorTransform_colorSet::Func, NULL, "color", NULL, CT_Set, 1, 1},
        {TFunc_Instances_ColorTransform_concat::Func, NULL, "concat", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ColorTransform_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };
    const MemberInfo ColorTransform::mi[ColorTransform::MemberInfoNum] = {
        {"alphaMultiplier", OFFSETOF(Instances::ColorTransform, alphaMultiplier), SlotInfo::BT_Number, 0},
        {"alphaOffset", OFFSETOF(Instances::ColorTransform, alphaOffset), SlotInfo::BT_Number, 0},
        {"blueMultiplier", OFFSETOF(Instances::ColorTransform, blueMultiplier), SlotInfo::BT_Number, 0},
        {"blueOffset", OFFSETOF(Instances::ColorTransform, blueOffset), SlotInfo::BT_Number, 0},
        {"greenMultiplier", OFFSETOF(Instances::ColorTransform, greenMultiplier), SlotInfo::BT_Number, 0},
        {"greenOffset", OFFSETOF(Instances::ColorTransform, greenOffset), SlotInfo::BT_Number, 0},
        {"redMultiplier", OFFSETOF(Instances::ColorTransform, redMultiplier), SlotInfo::BT_Number, 0},
        {"redOffset", OFFSETOF(Instances::ColorTransform, redOffset), SlotInfo::BT_Number, 0},
    };


    ColorTransform::ColorTransform(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::ColorTransform::ColorTransform()"
//##protect##"InstanceTraits::ColorTransform::ColorTransform()"
        SetMemSize(sizeof(Instances::ColorTransform));

    }

    Pickable<Instances::ColorTransform> ColorTransform::MakeInstance(Traits& t)
    {
        return Pickable<Instances::ColorTransform>(new(t.Alloc()) Instances::ColorTransform(t));
    }

    void ColorTransform::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    ColorTransform::ColorTransform(VM& vm)
    : Traits(vm, ColorTransformCI)
    {
//##protect##"ClassTraits::ColorTransform::ColorTransform()"
//##protect##"ClassTraits::ColorTransform::ColorTransform()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::ColorTransform(vm, ColorTransformCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ColorTransform::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ColorTransform(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ColorTransformCI = {
    ClassInfo::CompileTime,
    "ColorTransform", "flash.geom", &ObjectCI,
    ClassTraits::ColorTransform::MakeClassTraits,
    0,
    0,
    InstanceTraits::ColorTransform::ThunkInfoNum,
    InstanceTraits::ColorTransform::MemberInfoNum,
    NULL,
    NULL,
    InstanceTraits::ColorTransform::ti,
    InstanceTraits::ColorTransform::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

