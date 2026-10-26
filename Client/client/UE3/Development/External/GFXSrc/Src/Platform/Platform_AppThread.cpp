/**************************************************************************

Filename    :   Platform_AppThread.cpp
Content     :   
Created     :   
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Platform_AppThread.h"
#include "Platform_SystemRenderHALThread.h"

namespace Scaleform { namespace Platform {


int AppThread::Run()
{
    SF_COMPILER_ASSERT(sizeof(GFx::KeyEvent) <= AppThread::EventSize);
    SF_COMPILER_ASSERT(sizeof(GFx::MouseEvent) <= AppThread::EventSize);
    SF_COMPILER_ASSERT(sizeof(GFx::TouchEvent) <= AppThread::EventSize);
    SF_COMPILER_ASSERT(sizeof(GFx::GestureEvent) <= AppThread::EventSize);

    char* argv[] = {"ScaleformApp"};
    pApp->AppMain(1, argv);

    AppInit.PulseEvent();

    while (!pApp->IsShuttingDown())
    {
        // process commands from input or render thread
        RTCommandBuffer cmd;

        while (PopCommand(&cmd, 0))
        {
            cmd.Execute(*this);
            if (cmd.NeedsWait())
                cmd.GetNotifier()->Notify();
        }

        pApp->GetAppRenderThread()->WaitForOutstandingDrawFrame();
        pApp->OnUpdateFrame(true);
    }

    pApp->OnShutdown();
    return 0;
}

void    AppThread::OnEvent(const GFx::Event& event)
{
    PushCall(&AppThread::onEvent, *((EventStorage*)&event));
}

void    AppThread::OnOrientation(int orientation, bool force)
{
    PushCall(&AppThread::onOrientation, orientation, force);
}

void    AppThread::OnSize(int width, int height)
{
    PushCall(&AppThread::onSize, width, height);
}

void    AppThread::OnDropFiles(const String& filename)
{
    PushCall(&AppThread::onDropFiles, filename);
}

void    AppThread::OnLifecycleEvent(int event)
{
    PushCall(&AppThread::onLifecycleEvent, event);
}

void    AppThread::onEvent(EventStorage event)
{
    const GFx::Event*        pevent = (const GFx::Event*)&event;
    const GFx::KeyEvent*     pkevent = (const GFx::KeyEvent*)&event;
    const GFx::MouseEvent*   pmevent = (const GFx::MouseEvent*)&event;
    const GFx::TouchEvent*   ptevent = (const GFx::TouchEvent*)&event;
    const GFx::GestureEvent* pgevent = (const GFx::GestureEvent*)&event;

    switch (pevent->Type)
    {
    case GFx::Event::MouseDown:
        pApp->OnMouseButton(pmevent->MouseIndex, pmevent->Button, 1, Point<int>(pmevent->x, pmevent->y), pmevent->Modifiers);
        return;
    case GFx::Event::MouseUp:
        pApp->OnMouseButton(pmevent->MouseIndex, pmevent->Button, 0, Point<int>(pmevent->x, pmevent->y), pmevent->Modifiers);
        return;
    case GFx::Event::MouseMove:
        pApp->OnMouseMove(pmevent->MouseIndex, Point<int>(pmevent->x, pmevent->y), pmevent->Modifiers);
        return;

    case GFx::Event::KeyDown:
        pApp->OnKey(pkevent->KeyboardIndex, pkevent->KeyCode, pkevent->WcharCode, 1, pkevent->Modifiers);
        return;
    case GFx::Event::KeyUp:
        pApp->OnKey(pkevent->KeyboardIndex, pkevent->KeyCode, pkevent->WcharCode, 0, pkevent->Modifiers);
        return;

    case GFx::Event::TouchBegin:
        pApp->OnTouchBegin(0, ptevent->TouchPointID, Point<int>(ptevent->x, ptevent->y), Point<int>(ptevent->WContact, ptevent->HContact),
            ptevent->PrimaryPoint);
        return;
    case GFx::Event::TouchMove:
        pApp->OnTouchMove(0, ptevent->TouchPointID, Point<int>(ptevent->x, ptevent->y), Point<int>(ptevent->WContact, ptevent->HContact),
            ptevent->PrimaryPoint);
        return;
    case GFx::Event::TouchEnd:
        pApp->OnTouchEnd(0, ptevent->TouchPointID, Point<int>(ptevent->x, ptevent->y), Point<int>(ptevent->WContact, ptevent->HContact),
            ptevent->PrimaryPoint);
        return;

    case GFx::Event::GestureBegin:
        pApp->OnGestureBegin(0, pgevent->GestureMask, Point<int>(pgevent->x, pgevent->y), PointF(pgevent->OffsetX, pgevent->OffsetY),
            PointF(pgevent->ScaleX, pgevent->ScaleY), pgevent->Rotation);
        return;
    case GFx::Event::Gesture:
        pApp->OnGesture(0, pgevent->GestureMask, Point<int>(pgevent->x, pgevent->y), PointF(pgevent->OffsetX, pgevent->OffsetY),
            PointF(pgevent->ScaleX, pgevent->ScaleY), pgevent->Rotation);
        return;
    case GFx::Event::GestureEnd:
        pApp->OnGestureEnd(0, pgevent->GestureMask, Point<int>(pgevent->x, pgevent->y));
        return;

    default:
        return;
    }
}

void    AppThread::onOrientation(int orientation, bool force)
{
    pApp->OnOrientation(orientation, force);
}

void    AppThread::onSize(int width, int height)
{
    pApp->OnSize(Size<unsigned>(width, height));
}

void    AppThread::onDropFiles(String filename)
{
    pApp->OnDropFiles(filename);
}

void    AppThread::onLifecycleEvent(int event)
{
    switch (event)
    {
	case GFx::AppLifecycleEvent::OnPause:
        pApp->OnPause();
        return;

    case GFx::AppLifecycleEvent::OnResume:
        pApp->OnResume();
        return;
    }
}

}}
