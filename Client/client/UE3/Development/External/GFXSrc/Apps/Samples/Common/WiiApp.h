/**************************************************************************

Filename    :   WiiApp.h
Content     :   Simple PS3 Application class
Created     :   
Authors     :   Michael Antonov

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_WIIAPP_H
#define INC_WIIAPP_H

// GFx Includes
#include "GTypes.h"
#include "FxApp.h"
#include "GRendererWii.h"

#include <revolution.h>

// ***** Application class

class WiiApp : public FxApp
{
public:

    // **** Public Interface

    WiiApp();
    virtual ~WiiApp();

    virtual bool    CreateRenderer();

    // Initialization
    static void             InitMain();

   // **** Public Interface
    // Returns 0 if window creation/initialization failed (the app should quit).
    virtual bool            SetupWindow(const char *pname, int width, int height, 
                                        const SetupWindowParams& extraParams = SetupWindowParams());

    // Message processing function to be called in the
    // application loops until it returns 0, to indicate application being closed.
    virtual bool            ProcessMessages();

    // Sleeps for the specified number of milliseconds or till message.
    //virtual void            SleepTillMessage(unsigned int /*ms*/) {}

    virtual void            SleepMilliSecs(unsigned int ms);

    // This call cleans up the application and kills the window.
    // If not called explicitly, it will be called from the destructor.
    virtual void            KillWindow();

    // Changes/sets window title
    virtual void            SetWindowTitle(const char *ptitle);

    // Number of mice or similar controllers available
    virtual int             GetMouseCount() { return 4; }

    // Presents the data (swaps the back and front buffers)
    virtual void            PresentFrame();

    // On successful reset, this function will call InitRenderer again.
    virtual bool            RecreateRenderer();

    // This override is called from SetupWindow to initialize OpenGL/Direct3D view
    virtual bool            InitRenderer();
    // Should/can be called every frame to prepare the render, user function
    virtual void            PrepareRendererForFrame();

    virtual void            Clear(unsigned int color);

    // Initialize and restore 2D rendering view.
    // Push2DRenderView must be called before using 2D functions below,
    // while Pop2DRenderView MUST be called after it is finished.
    virtual void            Push2DRenderView();
    virtual void            Pop2DRenderView();
    // Draw a filled + blended rectangle.
    virtual void            FillRect(int l, int t, int r, int b, unsigned int color);
    
    //Cycle through files
    virtual bool            UpdateFiles(char* filename, bool  prev);
    // API-independednt toggle for wireframe rendering.
    virtual void            SetWireframe(bool wireframeEnable);

    virtual GRenderer*      GetRenderer();

    virtual DisplayStatus   CheckDisplayStatus() const;

    virtual void    RedrawMouseCursor();
    virtual void    ShowCursorInstantly(bool show);

    // *** Implementation

    GXRenderModeObj*        pRmode;
    GXRenderModeObj         Rmode;
    GXFifoObj*              pGXFifo;
    void*                   pGXFifoBuf;
    UPInt                   FBSize;
    void*                   pFB[2];
    int                     CurFb;

    struct Controller
    {
        bool                Enabled;
        SInt                MouseX, MouseY;

        Controller() { Enabled = 0; }
    };
    Controller              Controllers[4];

    GPtr<GRendererWii>      pRenderer;
    GRenderSyncWii*         pRenderSync;
    
    int CurFile;
    GArray<GArray<char> >   Filenames;

};


#endif // INC_WIIAPP_H
