/**************************************************************************

Filename    :   AS3_AvmTextField.cpp
Content     :   Implementation of AS3 part of TextField character
Created     :   Jan, 2010
Authors     :   Artem Bolgar

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
#include "GFx/AS3/AS3_AvmTextField.h"
#include "Render/Text/Text_DocView.h"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "GFx/AS3/Obj/Events/AS3_Obj_Events_TextEvent.h"
#include "GFx/AS3/Obj/Gfx/AS3_Obj_Gfx_TextEventEx.h"

namespace Scaleform {
namespace GFx {
namespace AS3 {

AvmTextField::AvmTextField(TextField* ptf) 
:
    AvmInteractiveObj(ptf)
{
    ptf->SetHtml(true); // seems to me AS3 text fields are always html-enabled
    ptf->SetSelection(0, 0);
}

TextFieldDef* AvmTextField::GetTextFieldDef() const
{
    SF_ASSERT(pDispObj); 
    SF_ASSERT(pDispObj->GetType() == CharacterDef::TextField);
    return static_cast<TextField*>(pDispObj)->GetTextFieldDef();
}

bool AvmTextField::HasStyleSheet() const 
{ 
#ifdef GFX_ENABLE_CSS
    SF_ASSERT(pDispObj); 
    SF_ASSERT(pDispObj->GetType() == CharacterDef::TextField);
    const TextField::CSSHolderBase* pcss = GetTextField()->GetCSSData();
    return pcss && static_cast<const CSSHolder*>(pcss)->pASStyleSheet != NULL; 
#else
    return false;
#endif
}

const Text::StyleManager* AvmTextField::GetStyleSheet() const 
{ 
#ifdef GFX_ENABLE_CSS
    SF_ASSERT(pDispObj); 
    SF_ASSERT(pDispObj->GetType() == CharacterDef::TextField);
    const TextField::CSSHolderBase* pcss = GetTextField()->GetCSSData();
    return (HasStyleSheet()) ? static_cast<const CSSHolder*>(pcss)->pASStyleSheet->GetTextStyleManager() : NULL; 
#else
    return NULL;
#endif
}

bool AvmTextField::OnMouseEvent(const EventId& event)
{ 
    AvmInteractiveObj::OnEvent(event);
    if (event.Id == EventId::Event_Click)
    {
        TextField* ptf       = GetTextField();
        
        // PPS: If selection length > 1, then we are in the process of selecting text
        //      In this case, don't fire an event
        if (ptf->GetBeginIndex() != ptf->GetEndIndex())
            return false;

        // if url is clicked - execute the action
        if (ptf->IsHtml() && ptf->MayHaveUrl())
        {
            Render::PointF p;
            if (ptf->IsUrlUnderMouseCursor(event.MouseIndex, &p))
            {
                UPInt pos = ptf->GetCharIndexAtPoint(p.x, p.y);
                if (!Alg::IsMax(pos))
                {
                    const Text::TextFormat* ptextFmt;
                    if (ptf->GetTextAndParagraphFormat(&ptextFmt, NULL, pos))
                    {
                        if (ptextFmt->IsUrlSet())
                        {
                            const char* url = ptextFmt->GetUrl();

                            // url should represent link in event protocol:
                            // "event:eventString"
                            MovieImpl* proot = GetMovieImpl();
                            if (proot && String::CompareNoCase(url, "event:", sizeof("event:") - 1) == 0)
                            {
                                url += sizeof("event:") - 1;
                                
                                // fire the link event
                                const ASString& evtName = GetAS3Root()->GetStringManager()->CreateString("link");
                                Instances::DisplayObject* as3obj = GetAS3Obj();
                                if (as3obj->WillTrigger(evtName, false))
                                {
                                    SPtr<Instances::TextEvent> evt;
                                    Value params[] = { Value(evtName), Value(true), Value(true) };
                                    ASVM* asvm = GetAS3Root()->GetAVM();
                                    asvm->ConstructInstance(evt, asvm->ExtensionsEnabled ? asvm->TextEventExClass : asvm->TextEventClass, 3, params);
                                    SF_ASSERT(evt);
                                    evt->Target = as3obj;
                                    evt->SetText(GetAS3Root()->GetStringManager()->CreateString(url));

                                    if (asvm->ExtensionsEnabled)
                                    {
                                        Instances::TextEventEx* evtExt = static_cast<Instances::TextEventEx*>(evt.GetPtr());
                                        evtExt->SetControllerIdx(event.ControllerIndex);
                                        evtExt->SetButtonIdx(event.ButtonId);
                                    }

                                    as3obj->Dispatch(evt, GetDispObj());
                                }
                            }
                            //printf ("%s\n", url);
                        }
                    }
                }
            }
        }

        return true;
    }
    return false; 
}

void AvmTextField::OnLinkEventEx(TextField::LinkEvent event, unsigned pos, unsigned controllerIndex)
{ 
    if (GetAVM()->ExtensionsEnabled)
    {
        TextField* ptf       = GetTextField();
        const Text::TextFormat* ptextFmt;
        if (ptf->GetTextAndParagraphFormat(&ptextFmt, NULL, pos))
        {
            if (ptextFmt->IsUrlSet())
            {
                const char* url = ptextFmt->GetUrl();

                const char* evtSyn = NULL;
                switch (event)
                {
                case TextField::Link_rollover:  evtSyn = "linkMouseOver";   break;
                case TextField::Link_rollout:   evtSyn = "linkMouseOut";    break;
                default: return;
                }

                // fire the link event
                const ASString& evtName = GetAS3Root()->GetStringManager()->CreateString(evtSyn);
                Instances::DisplayObject* as3obj = GetAS3Obj();
                if (as3obj/*add by zhaojun@snda, sometimes the as3obj is null*/ && as3obj->WillTrigger(evtName, false))
                {
                    SPtr<Instances::TextEventEx> evtEx;
                    Value params[] = { Value(evtName), Value(true), Value(true) };
                    ASVM* asvm = GetAS3Root()->GetAVM();
                    asvm->ConstructInstance(evtEx, asvm->TextEventExClass, 3, params);
                    SF_ASSERT(evtEx);
                    evtEx->Target = as3obj;
                    evtEx->SetText(GetAS3Root()->GetStringManager()->CreateString(url));
                    evtEx->SetControllerIdx(controllerIndex);

                    as3obj->Dispatch(evtEx, GetDispObj());
                }
            }
        }
    }
}

bool AvmTextField::OnCharEvent(wchar_t wcharCode, unsigned controllerIdx)
{
    SF_ASSERT(wcharCode);
    bool rv = true;

    const ASString& evtName = GetAS3Root()->GetBuiltinsMgr().GetBuiltin(AS3Builtin_textInput);
    Instances::DisplayObject* as3obj = GetAS3Obj();
    if (as3obj->WillTrigger(evtName, false))
    {
        SPtr<Instances::TextEvent> evt;
        Value params[] = { Value(evtName), Value(true), Value(true) };
        ASVM* asvm = GetAS3Root()->GetAVM();
        asvm->ConstructInstance(evt, asvm->ExtensionsEnabled ? asvm->TextEventExClass : asvm->TextEventClass, 3, params);
        SF_ASSERT(evt);
        evt->Target = as3obj;
        evt->SetText(wcharCode);

        if (asvm->ExtensionsEnabled)
        {
            Instances::TextEventEx* evtExt = static_cast<Instances::TextEventEx*>(evt.GetPtr());
            evtExt->SetControllerIdx(controllerIdx);
        }

        rv = as3obj->Dispatch(evt, GetDispObj());
    }
    return rv;
}

void AvmTextField::OnEventLoad()
{
    // should it be here still? For sprites it was moved in AS3Constructor

#ifdef _DEBUG

	GetAvmParent()->InsertChildToPlayList(GetIntObj());
	GetIntObj()->ModifyOptimizedPlayList();

#else
	if (GetAvmParent() != NULL && GetIntObj() != NULL)	// added by zhaojun@snda
	{
		GetAvmParent()->InsertChildToPlayList(GetIntObj());
		GetIntObj()->ModifyOptimizedPlayList();
	}
#endif

    AvmInteractiveObj::OnEventLoad();
//     // finalize the initialization. We need to initialize text here rather than in ctor
//     // since the name of instance is not set yet in the ctor and setting text might cause
//     // GFxTranslator to be invoked, which uses the instance name.
//     TextField* ptf = GetTextField();
//     if (GetTextFieldDef()->DefaultText.GetLength() > 0)
//     {
//         ptf->SetTextValue(GetTextFieldDef()->DefaultText.ToCStr(), ptf->IsHtml());
//     }
//     else
//     {
//         // This assigns both Text and HtmlText vars.
//         ptf->SetTextValue("", ptf->IsHtml(), false);
//     }
}

void AvmTextField::UpdateAutosizeSettings()
{
    TextField* ptf          = GetTextField();
    const bool  autoSizeByX = (ptf->IsAutoSize() && !ptf->IsWordWrap());
    const bool  autoSizeByY = (ptf->IsAutoSize());
    if (autoSizeByX)
        ptf->SetAutoSizeX();
    else
        ptf->ClearAutoSizeX();
    if (autoSizeByY)
        ptf->SetAutoSizeY();
    else
        ptf->ClearAutoSizeY();
    ptf->SetNeedUpdateGeomData();
}

bool    AvmTextField::IsTabable() const
{
    SF_ASSERT(pDispObj);

    if (!pDispObj->GetVisible()) 
        return false;
    if (GetIntObj()->IsTabEnabledFlagDefined())
        return GetIntObj()->IsTabEnabledFlagTrue();
    else if (GetIntObj()->GetTabIndex() > 0)
        return true;
    return !GetTextField()->IsReadOnly();
}

void AvmTextField::NotifyChanged()
{
    const ASString& evtName = GetAS3Root()->GetBuiltinsMgr().GetBuiltin(AS3Builtin_change);
    Instances::DisplayObject* as3obj = GetAS3Obj();
    if (as3obj && as3obj->HasEventHandler(evtName, false))
    {
        SPtr<Instances::Event> evt = as3obj->CreateEventObject(evtName, true, false);
        SF_ASSERT(evt);
        evt->Target = as3obj;
        as3obj->Dispatch(evt, GetDispObj());
    }
}

void AvmTextField::OnScroll()
{
    const ASString& evtName = GetAS3Root()->GetBuiltinsMgr().GetBuiltin(AS3Builtin_scroll);
    Instances::DisplayObject* as3obj = GetAS3Obj();
    if (as3obj && as3obj->HasEventHandler(evtName, false))
    {
        SPtr<Instances::Event> evt = as3obj->CreateEventObject(evtName, true, false);
        SF_ASSERT(evt);
        evt->Target = as3obj;
        as3obj->Dispatch(evt, GetDispObj());
    }
}

}}} // SF::GFx::AS3

