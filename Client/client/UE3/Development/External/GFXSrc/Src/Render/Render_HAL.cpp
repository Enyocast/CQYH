/**************************************************************************

Filename    :   Render_HAL.cpp
Content     :   
Created     :   
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Render_HAL.h"
#include "Kernel/SF_Debug.h"
#include "Render/Render_Bundle.h"
#include "Render/Render_Queue.h"

namespace Scaleform { namespace Render {

void MatrixState::SetUserMatrix(const Matrix2F& user)
{
    UVPOChanged = 1;
    User = user;
    UserView = View2D * (User * Orient2D);
    User3D = User;
    User3D.M[0][3] *= View2D.M[0][0] / User.M[0][0];
    User3D.M[1][3] *= View2D.M[1][1] / User.M[1][1];
}

void MatrixState::SetViewportMatrix(const Matrix2F& vp)
{
    View2D = vp;
    UserView = View2D * (User * Orient2D);
}

Viewport MatrixState::SetOrientation(const Viewport& vp)
{
    OrientationSet = 0;
    UVPOChanged = 1;

    switch (vp.Flags & Viewport::View_Orientation_Mask)
    {
    case Viewport::View_Orientation_Normal:
        Orient2D.SetIdentity();
        Orient3D.SetIdentity();
        break;

    case Viewport::View_Orientation_R90:
    case Viewport::View_Orientation_L90:
        {
            OrientationSet = 1;

            float flipm = ((vp.Flags & Viewport::View_Orientation_Mask) == Viewport::View_Orientation_L90 ? -1.0f : 1.0f);
            Orient2D.SetMatrix(0, -flipm, flipm < 0 ? 0 : (float)vp.BufferWidth,
                               flipm, 0,  flipm < 0 ? (float)vp.BufferHeight : 0);
            Orient3D.M[0][0] = 0;
            Orient3D.M[0][1] = flipm;
            Orient3D.M[1][1] = 0;
            Orient3D.M[1][0] = -flipm;
        }
        break;
    }

    UserView = View2D * (User * Orient2D);

    Viewport viewport;
    PointF tl = Orient2D.Transform(PointF((float)vp.Left, (float)vp.Top));
    PointF br = Orient2D.Transform(PointF(float(vp.Left+vp.Width), float(vp.Top+vp.Height)));
    viewport.Flags = vp.Flags;
    viewport.Left = (int)ceilf(Alg::Min(tl.x, br.x));
    viewport.Top = (int)ceilf(Alg::Min(tl.y, br.y));
    viewport.Width = (int)ceilf(fabsf(tl.x - br.x));
    viewport.Height = (int)ceilf(fabsf(tl.y - br.y));
    if (viewport.Flags & Viewport::View_UseScissorRect)
    {
        PointF sctl = Orient2D.Transform(PointF((float)vp.ScissorLeft, (float)vp.ScissorTop));
        PointF scbr = Orient2D.Transform(PointF(float(vp.ScissorLeft+vp.ScissorWidth),
                                                float(vp.ScissorTop+vp.ScissorHeight)));
        viewport.Flags = vp.Flags;
        viewport.ScissorLeft = (int)ceilf(Alg::Min(sctl.x, scbr.x));
        viewport.ScissorTop = (int)ceilf(Alg::Min(sctl.y, scbr.y));
        viewport.ScissorWidth = (int)ceilf(fabsf(sctl.x - scbr.x));
        viewport.ScissorHeight = (int)ceilf(fabsf(sctl.y - scbr.y));
    }
    viewport.BufferWidth = vp.BufferWidth;
    viewport.BufferHeight = vp.BufferHeight;

    return viewport;
}

#if !defined(SF_OS_3DS) && !defined(SF_OS_WII)
void MatrixState::recalculateUVPOC() const
{
    if (UVPOChanged)
    {
        // Recalculated the view compensation matrix.
        if ( ViewRect != ViewRectOriginal && !ViewRectOriginal.IsNull())
        {
            Point<int> dc = ViewRect.Center() - ViewRectOriginal.Center();
            float      dx = ((float)ViewRectOriginal.Width()) / ViewRect.Width();
            float      dy = ((float)ViewRectOriginal.Height()) / ViewRect.Height();
            float      ox = 2.0f * dc.x / ViewRect.Width();
            float      oy = 2.0f * dc.y / ViewRect.Height();
            ViewRectCompensated3D.MultiplyMatrix(Matrix4F::Translation(-ox, oy, 0), Matrix4F::Scaling(dx, dy, 1));
        }
        else
        {
            ViewRectCompensated3D = Matrix4F::Identity;
        }

        const Matrix4F& Projection = updateStereoProjection();
        Matrix4F UO(User3D, ViewRectCompensated3D);
        Matrix4F VRP(Orient3D, Projection);
        UVPO = Matrix4F(Matrix4F(UO, VRP), View3D);
        UVPOChanged = 0;
    }
}
#endif

const Matrix4F& MatrixState::updateStereoProjection(float factor) const
{
    if (S3DDisplay != StereoCenter)
    {
        float eyeZ = -View3D.M[2][3];
        if (S3DDisplay == StereoLeft)
        {
            getStereoProjectionMatrix(&Proj3DLeft, NULL, Proj3D, eyeZ, factor);
            return Proj3DLeft;
        }
        else if (S3DDisplay == StereoRight)
        {
            getStereoProjectionMatrix(NULL, &Proj3DRight, Proj3D, eyeZ, factor);
            return Proj3DRight;
        }
    }
    return Proj3D;
}

void Viewport::SetStereoViewport(unsigned display)
{
	switch (Flags & View_Stereo_AnySplit)
	{
	case View_Stereo_SplitV:
		Height = Height >> 1;
		Top = Top >> 1;
		if (display == StereoRight)
			Top += BufferHeight >> 1;
		break;

	case View_Stereo_SplitH:
		Width = Width >> 1;
		Left = Left >> 1;
		if (display == StereoRight)
			Left += BufferWidth >> 1;
		break;
	}
}

//
// Stereo projection matrix is a horizontally offset version of regular mono 
// projection matrix, shifted in X.
//
// Essentially, the camera separation  = interaxial / screen width;  (scaled 
// by a distortion scale factor)
//
void MatrixState::getStereoProjectionMatrix(
                                    Matrix4F *left, 		    // dest perspective matrix ptr for left eye
                                    Matrix4F *right, 	        // dest perspective matrix ptr for right eye
                                    const Matrix4F &original, 	// original (mono) perspective matrix
                                    float screenDist,           // eye distance to screen, eye Z 
                                    float factor)   const

{
    Matrix4F postProjectionMove;
    Matrix4F preProjectionMove;
    Matrix4F tmpMat;
    float postParam, preParam;

    postParam = S3DParams.Distortion * factor * S3DParams.EyeSeparationCm / S3DParams.DisplayWidthCm;
    preParam = - postParam * screenDist * original.M[3][2] / original.M[0][0];
    if (preParam < 0)
        preParam = -preParam;

    if (left)
    {
        postProjectionMove.M[0][3]  = -postParam;
        preProjectionMove.M[0][3] =  preParam;

        tmpMat = original * preProjectionMove;
        *left = postProjectionMove * tmpMat;
    }

    if (right)
    {
        postProjectionMove.M[0][3]  =  postParam;
        preProjectionMove.M[0][3] = -preParam;

        tmpMat = original * preProjectionMove;
        *right = postProjectionMove * tmpMat;
    }
}

//---------------------------------------------------------------------------------------
HAL::HAL(ThreadCommandQueue *commandQueue)  : 
    HALState(0),
    CurrentPass(Display_All),
    VMCFlags(0),
    pHeap(0),
    pRTCommandQueue(commandQueue),
    pRenderBufferManager(0),
    QueueProcessor(Queue, getThis()),
    MaskStackTop(0),
    CachedFilterIndex(-1),
	CachedFilterPrepIndex(-1),
    NextProfileMode(0)
{ 
    pHeap = Memory::GetGlobalHeap();
    Link_RenderStats(); 
}

bool HAL::initHAL(const HALInitParams& params)
{
    VMCFlags = params.ConfigFlags;
    return Queue.Initialize(params.RenderQueueSize);
}

bool HAL::shutdownHAL()
{
    if (!(HALState & HS_ModeSet))
        return true;
    notifyHandlers(HAL_Shutdown);

    Queue.Shutdown();

    // Remove ModeSet and other state flags.
    HALState = 0;    
    return true;
}

bool HAL::BeginFrame()
{
    if (!checkState(HS_ModeSet, __FUNCTION__))
        return false;

    if (HALState & HS_ReadyForReset)
        return false;

    HALState |= HS_InFrame;
    GetRQProcessor().BeginFrame();
    GetMeshCache().BeginFrame();
    GetTextureManager()->BeginFrame();

    return true;
}

void HAL::EndFrame()
{
    if (!checkState(HS_ModeSet|HS_InFrame, __FUNCTION__))
        return;

    RenderBufferManager* prbm = GetRenderBufferManager();
    if ( prbm )
        prbm->EndFrame();
    GetMeshCache().EndFrame();
    HALState &= ~HS_InFrame;
}

class HALBeginDisplayItem : public RenderQueueItem::Interface
{
public:
    static HALBeginDisplayItem Instance;
    virtual void EmitToHAL(RenderQueueItem&item, RenderQueueProcessor&qp) 
    {
        BeginDisplayData* data = (BeginDisplayData*)item.GetData();
        qp.GetHAL()->beginDisplay(data);
    }
};
class HALEndDisplayItem : public RenderQueueItem::Interface
{
public:
    static HALEndDisplayItem Instance;
    virtual void EmitToHAL(RenderQueueItem&, RenderQueueProcessor&qp) 
    {
        qp.GetHAL()->endDisplay();
    }
};
HALBeginDisplayItem HALBeginDisplayItem::Instance;
HALEndDisplayItem   HALEndDisplayItem::Instance;

void HAL::BeginDisplay(Color backgroundColor, const Viewport& vpin)
{
    if (!checkState(HS_InFrame, __FUNCTION__))
        return;

    BeginDisplayData entry(backgroundColor, vpin);
    BeginDisplayData* data = BeginDisplayDataList.Alloc(entry);

    // If BeginScene has not be called, BeginDisplay cannot be queued, because it is 
    // presumed that there is no matching EndScene call. This would not flush rendering
    // once it is completed, and thus Present would display no content. This is valid
    // in the case of a single movie rendering within a scene. Otherwise, Begin/EndScene
    // should be called.
    if ( !(HALState & HS_InScene) )
        beginDisplay(data);
    else
        Draw(&HALBeginDisplayItem::Instance, data);
}


void HAL::EndDisplay()
{
    // If BeginDisplay called BeginScene, we must call EndDisplay directly (not queued), because
    // otherwise rendering will not be flushed (because EndScene would not be called). This would
    // cause no display if Present were called.
    if (!(HALState & HS_SceneInDisplay))
        Draw(&HALEndDisplayItem::Instance);
    else
    {
        Flush();
        endDisplay();
    }
}


//---------------------------------------------------------------------------------------
void HAL::beginDisplay(BeginDisplayData* data)
{
    if (!checkState(HS_InFrame, __FUNCTION__))
        return;
    HALState |= HS_InDisplay;

    Color backgroundColor = data->BackgroundColor;
    const Viewport& vpin  = data->VP;
    BeginDisplayDataList.Free(data);

    // BeginScene automatically calls BeginScene if necessary.
    if (!(HALState & HS_InScene))
    {
        BeginScene();
        HALState |= HS_SceneInDisplay;
    }

    beginMaskDisplay();
    Profiler.SetDrawMode(0);

    VP = Matrices.SetOrientation(vpin);
    if (VP.GetClippedRect(&ViewRect))
        HALState |= HS_ViewValid;
    else
        HALState &= ~HS_ViewValid;

    updateViewport();

    // Clear the background with a solid quad, if background has alpha > 0.
    if (backgroundColor.GetAlpha() > 0)
        clearSolidRectangle(Rect<int>(vpin.Width, vpin.Height), backgroundColor);
}

void HAL::endDisplay()
{
    if (!checkState(HS_InDisplay, __FUNCTION__))
        return;    

    endMaskDisplay();
    SF_ASSERT(BlendModeStack.GetSize() == 0);

    if (HALState & HS_SceneInDisplay)
    {
        EndScene();
        HALState &= ~HS_SceneInDisplay;
    }

    // Must clear - but clear after EndScene, because it may do a Flush. Clearing this
    // flag beforehand would cause all the flushed items to fail, because we were not
    // currently in display.
    HALState &= ~HS_InDisplay;
}


void HAL::Flush()
{
    GetRQProcessor().Flush();
}

RenderTarget* HAL::GetDefaultRenderTarget()
{
    if (RenderTargetStack.GetSize() == 0 )
        return 0;
    return RenderTargetStack[0].pRenderTarget;
}

void HAL::destroyRenderBuffers()
{
    // Explicitly delete any targets which are 'default' as they are allocated either internally
    // by the HAL, or by the user and lifetime control has been passed to the HAL via SetRenderTarget.
    // They do not use the default ref-count implementation, so they are not auto-deleted.
    unsigned rtSize = (unsigned)RenderTargetStack.GetSize();
    for ( unsigned rt = 0; rt < rtSize; ++rt)
    {
        RenderTarget* pRT = 0;
        DepthStencilBuffer * pDS = 0;
        {
            RenderTargetEntry entry = RenderTargetStack.Pop();
            if ( entry.pRenderTarget && entry.pRenderTarget->GetType() == RBuffer_Default )
            {
                pRT = entry.pRenderTarget;
                RenderBuffer::HALData* phd = (RenderBuffer::HALData*)entry.pRenderTarget->GetHALData();
                if ( phd && phd->pDepthStencilBuffer )
                {
                    pDS = phd->pDepthStencilBuffer;
                    phd->pDepthStencilBuffer = 0;
                }
            }
        }
        delete pRT;
        delete pDS;
    }
    RenderTargetStack.Clear();
}

void HAL::checkState_EmitWarnings(unsigned stateFlags, const char* funcName)
{    
    SF_UNUSED2(stateFlags, funcName);
#ifdef SF_BUILD_DEBUG
    // Outputs debug warnings for missing states.
    struct WarnHelper
    {
        unsigned CheckFlags, HALState;
        WarnHelper(unsigned cf, unsigned hs) : CheckFlags(cf), HALState(hs) { }

        bool operator ()(unsigned checkBit, unsigned requiredBits) const
        {
            return (CheckFlags & checkBit) &&
                   ((HALState & (requiredBits | checkBit)) == requiredBits);
        }
    };

    WarnHelper needWarning(stateFlags, HALState);

    // TBD: WE need a better solution then secondary mask for when to NOT display warnings.
    //      Once BeginFrame fails, for example, there is no need to warn on all other calls.
    SF_DEBUG_WARNING1(needWarning(HS_ModeSet, 0),
                      "%s failed - Mode Not Set", funcName);
    SF_DEBUG_WARNING1(needWarning(HS_InFrame, 0),
                      "%s failed - Begin/EndFrame missing/failed.", funcName);
    SF_DEBUG_WARNING1(needWarning(HS_InDisplay, HS_InFrame|HS_ModeSet),
                      "%s failed - Begin/EndDisplay missing/failed.", funcName);
    SF_DEBUG_WARNING1(needWarning(HS_DeviceValid, 0),
                      "%s failed - Device Lost or not valid", funcName);

    SF_DEBUG_WARNING1(needWarning(HS_DrawingMask, HS_InFrame|HS_InDisplay),
                      "%s failed - PushMask_BeginSubmit call missing", funcName);
    SF_DEBUG_WARNING1(needWarning(HS_DrawingFilter, HS_InFrame|HS_InDisplay),
                      "%s failed - PushFilter call missing", funcName);
#endif
}

void HAL::DrawBundleEntries( BundleIterator ibundles, Renderer2DImpl* r2d )
{
    if ( CurrentPass == Display_All && IsPrepassRequired() )
    {
        SetDisplayPass(Display_Prepass);
        DrawBundleEntries(ibundles, r2d);
        SetDisplayPass(Display_Final);
        DrawBundleEntries(ibundles, r2d);
        SetDisplayPass(Display_All);
    }
    else
    {
        switch(CurrentPass)
        {
        case Display_All:
        case Display_Final:
			GetRQProcessor().SetQueueEmitFilter(RenderQueueProcessor::QPF_All);
			GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_All);
            break;
        case Display_Prepass:
			GetRQProcessor().SetQueueEmitFilter(RenderQueueProcessor::QPF_Filters);
            GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_Filters);
            break;
        }

        while(ibundles)
        {
            ibundles->DrawBundleEntry(r2d);
            ibundles++;
        }
    }
}

// Draws a RenderQueueItem by placing it into a queue.

void HAL::Draw(const RenderQueueItem& item)
{    
    SF_AMP_SCOPE_RENDER_TIMER(__FUNCTION__, Amp_Profile_Level_Medium);

    // Must be in display, unless this is a queued BeginDisplay render item.
    if (item.GetInterface() != &HALBeginDisplayItem::Instance && 
        !checkState(HS_InDisplay, __FUNCTION__))
        return;

    RenderQueueProcessor& qp = GetRQProcessor();
    RenderQueueItem* pitem = Queue.ReserveHead();
    if (!pitem)
    {
        qp.ProcessQueue(RenderQueueProcessor::QPM_One);
        pitem = Queue.ReserveHead();
        SF_ASSERT(pitem);
    }

    // We can add our primitive.
    // On Consoles, this may end up building up multiple primitives since cache
    // eviction will not rely on lock but will wait instead.
    *pitem = item;    
    Queue.AdvanceHead();

    // Process as many items as possible.
    qp.ProcessQueue(RenderQueueProcessor::QPM_Any);
}

void HAL::PushBlendMode(BlendMode mode)
{
    if (!checkState(HS_InDisplay, __FUNCTION__))
        return;

    BlendModeStack.PushBack(mode);
    applyBlendMode(mode, false, (HALState& HS_InRenderTarget) != 0 );
}

void HAL::PopBlendMode()
{
    if (!checkState(HS_InDisplay, __FUNCTION__))
        return;

    UPInt stackSize = BlendModeStack.GetSize();
    SF_ASSERT(stackSize != 0);
    BlendModeStack.PopBack();
    applyBlendMode((stackSize>1) ? BlendModeStack[stackSize-2] : Blend_Normal, 
        false, (HALState& HS_InRenderTarget) != 0 );
}

void HAL::PrepareFilters(FilterPrimitive* prim)
{
    if (!checkState(HS_InDisplay, __FUNCTION__))
        return;

    // We are drawing a profile mode, which will not use the cached results, and will 
    // not require a change in the queue filtering.
    if ( !Profiler.ShouldDrawMask() || !prim)
        return;

    // If the filter pointer is 0, then we are 'unpreparing'. This happens after the filter
    // and all its contents have been prepared.
    bool unprepare = (prim->GetFilters() == 0);

    // If we are cached in some way (or we are 'unpreparing').
    if ( prim->GetCacheState() != FilterPrimitive::Cache_Uncached || unprepare)
    {
        if ( !unprepare )
        {
            // The filter is being prepared, determine whether the results are cached.
            RenderTarget* results[FilterPrimitive::MaximumCachedResults];
            prim->GetCacheResults(results, FilterPrimitive::MaximumCachedResults);

            // Make sure that the first result (which is always required) is valid, and has the CacheID relating to
            // this FilterPrimitive. If other results exist, make sure that they are valid as well.
            bool validCache = true;
            for ( unsigned cr = 0; cr < FilterPrimitive::MaximumCachedResults; ++cr )
            {
                if ( !results[cr] )
                {
                    validCache = (cr != 0);
                    break;
                }

                if ( results[cr]->GetStatus() == RTS_Lost || results[cr]->GetStatus() == RTS_Unresolved ||
                    results[cr]->GetHALData()->CacheID != reinterpret_cast<UPInt>(prim) )
                {
                    validCache = false;
                    break;
                }
            }

            // Must increase the prep index always, so we know when to remove the prepare filter.
            CachedFilterPrepIndex++;

            // Cache isn't valid, uncache the results.
            if (!validCache)
            {
                prim->SetCacheResults(FilterPrimitive::Cache_Uncached, 0, 0);
                return;
            }

            // If there are valid cache results, then we must set the queue processor to skip
            // anything in the queue, except other filter prepares. Because the filter is cached,
            // we do not need to prepare any geometry inside it, as it will be contained within 
            // the cached results. 
            if (CachedFilterPrepIndex == 0 )
            {
                for ( unsigned cr = 0; cr < FilterPrimitive::MaximumCachedResults; ++cr )
                {
                    if ( results[cr] )
                        results[cr]->SetInUse(true);
                }
                GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_Filters);
            }
        }
        else if ( CachedFilterPrepIndex >= 0 )
        {
            // When filters are 'unprepared' we need to set the render queue to continue preparing
            // primitives from that point on. However, if we are in the prepass, make sure it is
            // still only processing filters.
            if (CachedFilterPrepIndex == 0 && CurrentPass != Display_Prepass)
                GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_All);
            else if (CachedFilterPrepIndex == 0 && CurrentPass == Display_Prepass )
                GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_Filters);
            --CachedFilterPrepIndex;
        }
    }
    else if (prim->GetCacheState() == FilterPrimitive::Cache_Uncached && CurrentPass == Display_Prepass)
    {
        // Uncached, and in the prepass, or 'both', need to prepare everything.
        GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_All);
    }
}

void HAL::GetStats(Stats* pstats, bool clear)
{
	// Cannot call GetStats within a scene - rendering may not be flushed, primitives
	// will not be drawn, and stats will be inaccurate.
	SF_ASSERT( (HALState & HS_InScene) == 0 );
	*pstats = AccumulatedStats;
	if (clear)
		AccumulatedStats.Clear();
}

void HAL::PopFilters()
{
    FilterStackEntry e;
    e = FilterStack.Pop();

    if ( !Profiler.ShouldDrawMask() )
    {
        if ( FilterStack.GetSize() == 0 )
            Profiler.SetDrawMode(0);
        return;
    }

    // If doing a cached filter, and haven't reached the level at which it will be displayed, ignore the pop.
    if ( (HALState & HS_CachedFilter) && (CachedFilterIndex < (int)FilterStack.GetSize()) )
        return;

    CachedFilterIndex = -1;
    if ( HALState & HS_CachedFilter )
    {
        drawCachedFilter(e.pPrimitive);
        GetRQProcessor().SetQueueEmitFilter(RenderQueueProcessor::QPF_All);
        HALState &= ~HS_CachedFilter;
    }
    else
    {
        drawUncachedFilter(e);
    }

    if ( FilterStack.GetSize() == 0 )
        HALState &= ~HS_DrawingFilter;
}


}} // Scaleform::Render
