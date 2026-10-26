//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_DisplayObject.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_DisplayObject_H
#define INC_AS3_Obj_Display_DisplayObject_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
#include "GFx/GFx_DisplayObject.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class DisplayObjectContainer;
    class Stage;
    class Rectangle;
    class Transform;
    class Point;
    class LoaderInfo;
    class Loader;
    class AccessibilityProperties;
    class Vector3D;  
}
typedef PtrReleaseProxy<Mem_Stat> ReleaseProxy;
//##protect##"forward_declaration"

namespace ClassTraits
{
    class DisplayObject;
}

namespace InstanceTraits
{
    class DisplayObject;
}

namespace Classes
{
    class DisplayObject;
}

namespace Instances
{
    class DisplayObject : public Instances::EventDispatcher
    {
        friend class InstanceTraits::DisplayObject;
        
    public:
        typedef DisplayObject SelfType;
        typedef Classes::DisplayObject ClassType;
        typedef InstanceTraits::DisplayObject TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::DisplayObject"; }
#endif
    protected:
        DisplayObject(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        ~DisplayObject();

        virtual GFx::DisplayObject* CreateStageObject();
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;

        bool FindLibarySymbol(CharacterCreateInfo* pccinfo, MovieDefImpl* pdefImpl) const;
        bool HasDisplayObject() const { return pDispObj != NULL; }

        // sets pLoaderInfo = Loader.contentLoaderInfo.
        void SetLoaderInfo(const Loader&);
        void SetLoaderInfo(LoaderInfo*);

        // returns true if pLoaderInfo is set for the instance
        bool HasLoaderInfo() const;

#ifdef GFX_AS3_VERBOSE
        virtual Scaleform::String GetAS3ObjectName() const 
        { 
            if (pDispObj) return Scaleform::String(pDispObj->GetName().ToCStr());
            return Instances::EventDispatcher::GetAS3ObjectName();
        }
#endif
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_accessibilityPropertiesGet, 
            mid_accessibilityPropertiesSet, 
            mid_alphaGet, 
            mid_alphaSet, 
            mid_blendModeGet, 
            mid_blendModeSet, 
            mid_cacheAsBitmapGet, 
            mid_cacheAsBitmapSet, 
            mid_filtersGet, 
            mid_filtersSet, 
            mid_heightGet, 
            mid_heightSet, 
            mid_loaderInfoGet, 
            mid_maskGet, 
            mid_maskSet, 
            mid_mouseXGet, 
            mid_mouseYGet, 
            mid_nameGet, 
            mid_nameSet, 
            mid_opaqueBackgroundGet, 
            mid_opaqueBackgroundSet, 
            mid_parentGet, 
            mid_rootGet, 
            mid_rotationGet, 
            mid_rotationSet, 
            mid_rotationXGet, 
            mid_rotationXSet, 
            mid_rotationYGet, 
            mid_rotationYSet, 
            mid_rotationZGet, 
            mid_rotationZSet, 
            mid_scale9GridGet, 
            mid_scale9GridSet, 
            mid_scaleXGet, 
            mid_scaleXSet, 
            mid_scaleYGet, 
            mid_scaleYSet, 
            mid_scaleZGet, 
            mid_scaleZSet, 
            mid_scrollRectGet, 
            mid_scrollRectSet, 
            mid_stageGet, 
            mid_transformGet, 
            mid_transformSet, 
            mid_visibleGet, 
            mid_visibleSet, 
            mid_widthGet, 
            mid_widthSet, 
            mid_xGet, 
            mid_xSet, 
            mid_yGet, 
            mid_ySet, 
            mid_zGet, 
            mid_zSet, 
            mid_getBounds, 
            mid_getRect, 
            mid_globalToLocal, 
            mid_globalToLocal3D, 
            mid_hitTestObject, 
            mid_hitTestPoint, 
            mid_localToGlobal, 
            mid_local3DToGlobal, 
        };
        void accessibilityPropertiesGet(Value& result);
        void accessibilityPropertiesSet(Value& result, Instances::AccessibilityProperties* value);
        void alphaGet(Value::Number& result);
        void alphaSet(Value& result, Value::Number value);
        void blendModeGet(ASString& result);
        void blendModeSet(Value& result, const ASString& value);
        void cacheAsBitmapGet(bool& result);
        void cacheAsBitmapSet(Value& result, bool value);
        void filtersGet(Value& result);
        void filtersSet(Value& result, Instances::Array* value);
        void heightGet(Value::Number& result);
        void heightSet(Value& result, Value::Number value);
        void loaderInfoGet(Value& result);
        void maskGet(Value& result);
        void maskSet(Value& result, Instances::DisplayObject* value);
        void mouseXGet(Value::Number& result);
        void mouseYGet(Value::Number& result);
        void nameGet(Value& result);
        void nameSet(Value& result, const Value& value);
        void opaqueBackgroundGet(Value& result);
        void opaqueBackgroundSet(Value& result, const Value& value);
        void parentGet(Value& result);
        void rootGet(Value& result);
        void rotationGet(Value::Number& result);
        void rotationSet(Value& result, Value::Number value);
        void rotationXGet(Value::Number& result);
        void rotationXSet(Value& result, Value::Number value);
        void rotationYGet(Value::Number& result);
        void rotationYSet(Value& result, Value::Number value);
        void rotationZGet(Value::Number& result);
        void rotationZSet(Value& result, Value::Number value);
        void scale9GridGet(Value& result);
        void scale9GridSet(Value& result, Instances::Rectangle* value);
        void scaleXGet(Value::Number& result);
        void scaleXSet(Value& result, Value::Number value);
        void scaleYGet(Value::Number& result);
        void scaleYSet(Value& result, Value::Number value);
        void scaleZGet(Value::Number& result);
        void scaleZSet(Value& result, Value::Number value);
        void scrollRectGet(Value& result);
        void scrollRectSet(Value& result, Instances::Rectangle* value);
        void stageGet(Value& result);
        void transformGet(Value& result);
        void transformSet(Value& result, Instances::Transform* value);
        void visibleGet(bool& result);
        void visibleSet(Value& result, bool value);
        void widthGet(Value::Number& result);
        void widthSet(Value& result, Value::Number value);
        void xGet(Value::Number& result);
        void xSet(Value& result, Value::Number value);
        void yGet(Value::Number& result);
        void ySet(Value& result, Value::Number value);
        void zGet(Value::Number& result);
        void zSet(Value& result, Value::Number value);
        void getBounds(Value& result, Instances::DisplayObject* targetCoordinateSpace);
        void getRect(Value& result, Instances::DisplayObject* targetCoordinateSpace);
        void globalToLocal(Value& result, Instances::Point* point);
        void globalToLocal3D(Value& result, Instances::Point* point);
        void hitTestObject(bool& result, Instances::DisplayObject* obj);
        void hitTestPoint(bool& result, Value::Number x, Value::Number y, bool shapeFlag);
        void localToGlobal(Value& result, Instances::Point* point);
        void local3DToGlobal(Value& result, Instances::Vector3D* point);

//##protect##"instance$data"
    public:
        SPtr<LoaderInfo>        pLoaderInfo;
        Ptr<GFx::DisplayObject> pDispObj;
        Ptr<ReleaseProxy>       pReleaseProxy;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class DisplayObject : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::DisplayObject"; }
#endif
    public:
        DisplayObject(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::DisplayObject> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 62 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class DisplayObject : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::DisplayObject"; }
#endif
    public:
        typedef Classes::DisplayObject ClassType;

    public:
        DisplayObject(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"

// Helper method - quickly determines that BuiltinTraitsType belong to display object.
inline bool AreDisplayObjectTraits(AS3::Object* obj)
{
    const BuiltinTraitsType tt = obj->GetTraitsType();
    return ((unsigned)(tt-Traits_DisplayObject_Begin) <
            (unsigned)(Traits_DisplayObject_End-Traits_DisplayObject_Begin) &&
            obj->GetTraits().IsInstanceTraits());
}
inline bool AreDisplayObjectContainerTraits(AS3::Object* obj)
{
    BuiltinTraitsType tt = obj->GetTraitsType();
    return ((unsigned)(tt-Traits_DisplayObjectContainer) <
            (unsigned)(Traits_DisplayObject_End-Traits_DisplayObjectContainer) &&
            obj->GetTraits().IsInstanceTraits());
}


//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

