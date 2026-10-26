/**************************************************************************

Filename    :   WiiApp.cpp
Content     :   Simple Wii Application class implemenation
Created     :   
Authors     :   Michael Antonov, Andrew Reisse

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "WiiApp.h"
#include "GRefCount.h"
#include "GAllocator.h"
#include "GMemory.h"
#include "GStd.h"

#include <revolution.h>
#include <revolution/kpad.h>

#include <stdlib.h>
#include <string.h>

#define  GX_FIFO_SIZE (256*1024)

static void *mem2alloc(unsigned long size)
{
    return GALLOC(size, GStat_Default_Mem);
}
static u8 mem2free(void *ptr)
{
    GFREE(ptr);
    return 1;
}

void     WiiApp::InitMain()
{
    void *arenaLo = OSGetMEM1ArenaLo();
    void *arenaHi = OSGetMEM1ArenaHi();
    arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
    OSSetMEM1ArenaLo(arenaLo);

    OSSetCurrentHeap(OSCreateHeap((void*)OSRoundUp32B(arenaLo), (void*)OSRoundDown32B(arenaHi)));
    OSSetMEM1ArenaLo(arenaHi);

    DVDInit();
    VIInit();
}

WiiApp::WiiApp()  : FxApp() 
{
    FullScreen  = 1;
    Console     = 1;

    for (int i = 0; i < 4; i++)
    {
        Controllers[i].MouseX      = 100;
        Controllers[i].MouseY      = 100;
    }

    CursorDisabled  = 0;
    CursorHidden    = 0;
    
    pRenderSync     = NULL;
}

WiiApp::~WiiApp()
{

    if (Created)
        KillWindow();
}

bool WiiApp::CreateRenderer()
{
    pRenderer = *GRendererWii::CreateRenderer();
    if (pRenderer)
    {
        if (!pRenderSync)
            pRenderSync = pRenderer->CreateRenderSync_DrawSync();
        pRenderer->SetDependentVideoMode(pRmode, pRenderSync);
        return true;
    }
    return false;
}

GRenderer* WiiApp::GetRenderer()
{
    return pRenderer.GetPtr();   
}

FxApp::DisplayStatus  WiiApp::CheckDisplayStatus() const
{
    if (!pRenderer)
        return FxApp::DisplayStatus_Unavailable;
    return (FxApp::DisplayStatus)pRenderer->CheckDisplayStatus();
}

static void WPADConnectFunc(SInt32 chan, SInt32 result)
{
    if (chan >= 0 && chan < 4)
        ((WiiApp*)FxApp::pApp)->Controllers[chan].Enabled = (result == WPAD_ERR_NONE);
}

// Create and show the window
bool WiiApp::SetupWindow(const char *pname, int width, int height,
                         const SetupWindowParams& extraParams )
{
    GUNUSED2(pname, extraParams);

    if (Created)
        return 0;

    pGXFifoBuf = OSAlloc(GX_FIFO_SIZE);
    pGXFifo = GXInit(pGXFifoBuf, GX_FIFO_SIZE);

    bool isdtv = VIGetDTVStatus();
    UInt32 tvf = VIGetTvFormat();
    UInt32 tvm = VIGetScanMode();

    switch (tvf)
    {
    case VI_NTSC:
        pRmode = isdtv ? &GXNtsc480Prog : &GXNtsc480IntDf;
        break;
    case VI_PAL:
        pRmode = &GXPal528IntDf;
        break;
    case VI_EURGB60:
        pRmode = isdtv ? &GXEurgb60Hz480Prog : &GXEurgb60Hz480IntDf;
        break;
    case VI_MPAL:
        pRmode = isdtv ? &GXMpal480Prog : &GXMpal480IntDf;
        break;
    default:
        OSHalt("unknown TV format\n");
        break;
    }

    GXAdjustForOverscan(pRmode, &Rmode, 0, 16);
    pRmode = &Rmode;

    FBSize = VIPadFrameBufferWidth(pRmode->fbWidth) * pRmode->xfbHeight * VI_DISPLAY_PIX_SZ;
    pFB[0] = OSAlloc(FBSize);
    pFB[1] = OSAlloc(FBSize);
    CurFb = 0;

    VIConfigure(pRmode);
    VISetBlack(1);
    VISetNextFrameBuffer(pFB[0]);
    VIFlush();
    VIWaitForRetrace();
    if (pRmode->viTVmode & 3 != tvm || tvm == VI_INTERLACE)
    {
        VIWaitForRetrace();
    }

    GXSetViewport(0, 0, pRmode->fbWidth, pRmode->efbHeight, 0, 1.0f);
    GXSetScissor(0, 0, pRmode->fbWidth, pRmode->efbHeight);

    Float yScale = GXGetYScaleFactor(pRmode->efbHeight, pRmode->xfbHeight);
    int xfbHeight = GXSetDispCopyYScale(yScale);
    GXSetDispCopySrc(0, 0, pRmode->fbWidth, pRmode->efbHeight);
    GXSetDispCopyDst(pRmode->fbWidth, xfbHeight);
    GXSetCopyFilter(pRmode->aa, pRmode->sample_pattern, GX_TRUE, pRmode->vfilter);
    GXSetDispCopyGamma(GX_GM_1_0);

    if (pRmode->aa)
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    else
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);

    GXCopyDisp(pFB[1], GX_TRUE);

    Width     = pRmode->fbWidth;
    Height    = pRmode->efbHeight;
    
    Created = 1;
    if (!InitRenderer())
    {       
        KillWindow();
        return 0;
    }

    // controller setup
    WPADRegisterAllocator(mem2alloc, mem2free);
    KPADInit();

    for (int i = 0; i < 4; i++)
    {
#if (__SDKVERNUMERIC__ <= 2006113006L)
        WPADSetConnectCallback(i, WPADConnectFunc);
#else
        KPADSetConnectCallback(i, WPADConnectFunc);
#endif

        UInt32 type;
        if (WPAD_ERR_NONE == WPADProbe(i, &type))
            Controllers[i].Enabled = 1;
    }

    return 1;
}


// Resets the direct3D, return 1 if successful.
// On successful reset, this function will call InitRenderer again.
bool    WiiApp::RecreateRenderer()
{   
//    if (!pDevice)
  //      return 0;

    GXAbortFrame();

    UPInt fbsize = VIPadFrameBufferWidth(pRmode->fbWidth) * pRmode->xfbHeight * VI_DISPLAY_PIX_SZ;
    if (fbsize > FBSize)
    {
        OSFree(pFB[0]);
        OSFree(pFB[1]);
        pFB[0] = OSAlloc(fbsize);
        pFB[1] = OSAlloc(fbsize);
    }
    CurFb = 0;
    GXSetViewport(0, 0, pRmode->fbWidth, pRmode->efbHeight, 0, 1.0f);
    GXSetScissor(0, 0, pRmode->fbWidth, pRmode->efbHeight);

    Float yScale = GXGetYScaleFactor(pRmode->efbHeight, pRmode->xfbHeight);
    int xfbHeight = GXSetDispCopyYScale(yScale);
    GXSetDispCopySrc(0, 0, pRmode->fbWidth, pRmode->efbHeight);
    GXSetDispCopyDst(pRmode->fbWidth, xfbHeight);
    GXSetCopyFilter(pRmode->aa, pRmode->sample_pattern, GX_TRUE, pRmode->vfilter);
    GXSetDispCopyGamma(GX_GM_1_0);

    if (pRmode->aa)
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    else
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);

    GXCopyDisp(pFB[1], GX_TRUE);

    return InitRenderer();
}

// Deletes the DC, RC, and Window, and restores the original display.
void WiiApp::KillWindow()
{
    if (!Created)
        return;

    Created = 0;
    return;
}

static void Color32ToFloat(float *prgba, UInt32 color)
{
    float scalar = 1.0f / 255.0f;
}

void    WiiApp::Clear(unsigned int color)
{   
    GXColor prgba;

    prgba.a =  (color >> 24);
    prgba.r =  ((color >> 16) & 0xFF);
    prgba.g =  ((color >> 8) & 0xFF);
    prgba.b =  (color & 0xFF);

    GXSetCopyClear(prgba, GX_MAX_Z24);
    GXCopyDisp(pFB[CurFb], GX_TRUE);
}

// Initialize and restore 2D rendering view.
void    WiiApp::Push2DRenderView()
{
    if (pRmode->field_rendering)
        GXSetViewportJitter(0,0, Width, Height, 0.0F, 1.0F, VIGetNextField());
    else
        GXSetViewport(0,0, Width, Height, 0.0F, 1.0F);

    Mtx idm;
    MTXIdentity(idm);
    GXLoadPosMtxImm(idm, GX_PNMTX2);
    GXSetCurrentMtx(GX_PNMTX2);

    Mtx44 oProjection;
    MTXOrtho( oProjection, 0,Height, 0,Width, 0.0f,255.0f);
    GXSetProjection(oProjection, GX_ORTHOGRAPHIC);

    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetClipMode(GX_CLIP_DISABLE);
    GXSetAlphaCompare( GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetCullMode( GX_CULL_NONE );
    GXSetScissor(0,0, Width, Height);
}


void    WiiApp::Pop2DRenderView()
{
}

// Draw a filled + blended rectangle.
void    WiiApp::FillRect(int l, int t, int r, int b, unsigned int color)
{
}


// API-independednt toggle for wireframe rendering.
void    WiiApp::SetWireframe(bool wireframeEnable)
{
}

void WiiApp::RedrawMouseCursor()
{
    ShowCursorInstantly(!CursorHidden);
}

static const GXColor CursorColors[4] = {{255,0,0,255}, {0,0,255,255}, {0,255,0,255}, {0,255,255,255}};

void WiiApp::ShowCursorInstantly(bool show)
{
    if(!show)
        return;

    Push2DRenderView();

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

    GXSetNumTexGens(0);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);

    for (int i = 0; i < 4; i++)
        if (Controllers[i].Enabled)
        {
            GXSetChanMatColor(GX_COLOR0A0, CursorColors[i]);

            GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
                GXPosition2f32(Controllers[i].MouseX, Controllers[i].MouseY);
                GXPosition2f32(Controllers[i].MouseX+6, Controllers[i].MouseY+24);
                GXPosition2f32(Controllers[i].MouseX+12, Controllers[i].MouseY+21);
                GXPosition2f32(Controllers[i].MouseX+18, Controllers[i].MouseY+24);
                GXPosition2f32(Controllers[i].MouseX, Controllers[i].MouseY);
            GXEnd();
        }

    Pop2DRenderView();
}


static int keymap[13][2] = {
    {KPAD_BUTTON_LEFT,  FxApp::Pad_Left},
    {KPAD_BUTTON_RIGHT, FxApp::Pad_Right},
    {KPAD_BUTTON_UP,    FxApp::Pad_Up},
    {KPAD_BUTTON_DOWN,  FxApp::Pad_Down},
    {KPAD_BUTTON_PLUS,  FxApp::Pad_Plus},
    {KPAD_BUTTON_MINUS, FxApp::Pad_Minus},
    {KPAD_BUTTON_A,     FxApp::Pad_A},
    {KPAD_BUTTON_B,     FxApp::Pad_B},
    {KPAD_BUTTON_1,     FxApp::Pad_1},
    {KPAD_BUTTON_2,     FxApp::Pad_2},
    {KPAD_BUTTON_HOME,  FxApp::Pad_Home},
    {KPAD_BUTTON_C,     FxApp::Pad_C},
    {KPAD_BUTTON_Z,     FxApp::Pad_Z}};

// Message processing function to be called in the 
// application loops until this returns 0.

bool    WiiApp::ProcessMessages()
{
    for (int i = 0; i < 4; i++)
    {
        if (!Controllers[i].Enabled)
            continue;

        KPADStatus kpad[KPAD_MAX_READ_BUFS];

        UInt n = KPADRead(i, kpad, KPAD_MAX_READ_BUFS);

        if (n > 0)
        {
            SInt mx = Width*0.5f + kpad[0].pos.x * Width*0.50f;
            SInt my = Height*0.5f + kpad[0].pos.y * Height*0.50f;

            if (Controllers[i].MouseX != mx ||
                Controllers[i].MouseY != my)
            {
                Controllers[i].MouseX = mx;
                Controllers[i].MouseY = my;

                OnMouseMove(i, mx, my, 0);
            }

            for (int i = 0; i < 13; i++)
                if (kpad[0].trig & keymap[i][0])
                    OnPad((FxApp::PadKeyCode)keymap[i][1], 1);
                else if (kpad[0].release & keymap[i][0])
                    OnPad((FxApp::PadKeyCode)keymap[i][1], 0);

            if (kpad[0].trig & KPAD_BUTTON_A)
                OnMouseButton(i, 0, 1, Controllers[i].MouseX, Controllers[i].MouseY, 0);
            else if (kpad[0].release & KPAD_BUTTON_A)
                OnMouseButton(i, 0, 0, Controllers[i].MouseX, Controllers[i].MouseY, 0);
        }
    }

    return 1;
}

void    WiiApp::SleepMilliSecs(unsigned int ms)
{
    OSSleepMicroseconds(ms);
}

bool    WiiApp::UpdateFiles(char* filename, bool prev)
{
    char    path[256];
    char*   pfilename=filename;
    SPInt len = strlen(pfilename);
    for (SPInt i=len; i>0; i--) 
    {
        if (pfilename[i]=='/' || pfilename[i]=='\\') {
            pfilename = pfilename+i+1;
                break;
            }
    }
    G_strcpy(path,sizeof(path),filename);
    unsigned int path_length =(unsigned int) strlen(filename)-strlen(pfilename);
    path[path_length]=0; //current directory

    if (Filenames.GetSize() == 0)
    {
        DVDDir fd;
        if (DVDOpenDir(path, &fd))
        {
            DVDDirEntry dir;
            UInt64      size = sizeof(dir);
            while (DVDReadDir(&fd, &dir))
            {
                GArray<char> fn;
                int ext = 0;
                for (int i = 0; dir.name[i]; i++)
                {
                    if (dir.name[i] == '.')
                        ext = i;
                    fn.PushBack(dir.name[i]);
                }
                fn.PushBack(0);
                if (strcmp(&fn[0], "fxplayer.swf") && (!strcmp(&fn[ext], ".swf") || !strcmp(&fn[ext], ".gfx")))
                Filenames.PushBack(fn);
            }
        }
        DVDCloseDir(&fd);
        CurFile = 0;
    }

    if (CurFile >= 0 && CurFile < SInt(Filenames.GetSize()))
    {
        CurFile += (prev ? -1 : 1);
        if (CurFile < 0)
            CurFile = SInt(Filenames.GetSize()-1);
        else if (CurFile >= SInt(Filenames.GetSize()))
            CurFile = 0;
        G_strcpy(&filename[path_length], 256-path_length, &Filenames[CurFile].Front());
        return 1;
    }
    else
    {
        Filenames.Clear();   
        return 0;
    }
}

// Changes/sets window title
void    WiiApp::SetWindowTitle(const char *ptitle)
{
    GUNUSED(ptitle);
}


// Presents the data (swaps the back and front buffers)
void    WiiApp::PresentFrame()
{
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXCopyDisp(pFB[CurFb], GX_TRUE);
    GXDrawDone();

    VISetNextFrameBuffer(pFB[CurFb]);
    VISetBlack(0);
    VIFlush();
    VIWaitForRetrace();
    CurFb = !CurFb;
}

// *** Overrides

bool    WiiApp::InitRenderer()
{
    return 1;
}
// Should/can be called every frame to prepare the render, user function
void    WiiApp::PrepareRendererForFrame()
{   
    if (pRmode->field_rendering)
        GXSetViewportJitter(
            0.0F, 0.0F, (float)pRmode->fbWidth, (float)pRmode->efbHeight, 
            0.0F, 1.0F, VIGetNextField());
    else
        GXSetViewport(
            0.0F, 0.0F, (float)pRmode->fbWidth, (float)pRmode->efbHeight, 
            0.0F, 1.0F);

    GXInvalidateVtxCache();
    GXInvalidateTexAll();
}
