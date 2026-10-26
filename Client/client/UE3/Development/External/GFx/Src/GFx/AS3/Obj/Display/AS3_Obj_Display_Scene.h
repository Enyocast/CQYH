//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Scene.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_Scene_H
#define INC_AS3_Obj_Display_Scene_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "GFx/GFx_MovieDef.h"
#include "GFx/GFx_Sprite.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Scene;
}

namespace InstanceTraits
{
    class Scene;
}

namespace Classes
{
    class Scene;
}

namespace Instances
{
    class Scene : public Instances::Object
    {
        friend class InstanceTraits::Scene;
        
    public:
        typedef Scene SelfType;
        typedef Classes::Scene ClassType;
        typedef InstanceTraits::Scene TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Scene"; }
#endif
    protected:
        Scene(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        void Set(const MovieDataDef::SceneInfo* sceneInfo);
        void Set(GFx::Sprite* spr);

//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_labelsGet, 
            mid_nameGet, 
            mid_numFramesGet, 
        };
        void labelsGet(Value& result);
        void nameGet(ASString& result);
        void numFramesGet(SInt32& result);

//##protect##"instance$data"
        const MovieDataDef::SceneInfo* SceneInfo;
        Ptr<GFx::Sprite>               SpriteObj;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Scene : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Scene"; }
#endif
    public:
        Scene(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Scene> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 3 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Scene : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Scene"; }
#endif
    public:
        typedef Classes::Scene ClassType;

    public:
        Scene(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

