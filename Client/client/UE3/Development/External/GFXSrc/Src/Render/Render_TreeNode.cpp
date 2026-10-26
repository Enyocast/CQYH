/**************************************************************************

Filename    :   Render_TreeNode.cpp
Content     :   Rendering tree node classes implementation
Created     :   December 19, 2009
Authors     :   Michael Antonov

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Render_TreeNode.h"
#include "Render_TreeCacheNode.h"
#include "Render/Render_Twips.h"
#include "Render/Render_Viewport.h"
#include "Kernel/SF_Debug.h"
#include "Kernel/SF_HeapNew.h"

extern Scaleform::Render::TreeCacheNode* g_IMETreeCacheNode;
extern Scaleform::Render::TreeNode* g_IMETreeNode;

namespace Scaleform { namespace Render {


// ***** TreeNode

void TreeNode::NodeData::ReleaseNodes() const
{
    if (HasMask())
    {
        removeThisAsMaskOwner(this);
        // Clearing NF_HasMask Probably not needed since we are destroying node...
        // Could clearing it also affect data seen by another thread? Best be safe.
        //Flags &= ~NF_HasMask;
    }
    States.ReleaseNodes();
}

bool TreeNode::NodeData::expandByFilterBounds(RectF* bounds, bool boundsEmpty) const
{
    // Applying a filter will not increase empty bounds.
    if ( boundsEmpty )
        return boundsEmpty;

    const FilterState* filterState = GetState<FilterState>();
    const FilterSet* filters = filterState ? filterState->GetFilters() : 0;
    if ( !filters )
        return boundsEmpty;

    for (unsigned i = 0; i < filters->GetFilterCount(); ++i )
    {
        const Filter* filter = filters->GetFilter(i);
        switch( filter->GetFilterType() )
        {
            case Filter_Blur:
            case Filter_Shadow:
            case Filter_Glow:
            case Filter_Bevel:
            {
                const BlurFilter* blurFilter = (const BlurFilter*)filter;
                const BlurFilterParams& params = blurFilter->GetParams();

                // The filter area must be extended even for inner shadows as the blurred area outside is still read
                float count = params.Mode & BlurFilterParams::Mode_Highlight ? 2.0f : 1.0f;
                bounds->Expand( count * ceilf(params.BlurX * params.Passes), 
                                count * ceilf(params.BlurY * params.Passes) );

                if (filter->GetFilterType() == Filter_Shadow || filter->GetFilterType() == Filter_Bevel)
                {
                    PointF offset = params.Offset;
                    if (offset.x > 0)
                        bounds->HExpand(0, ceilf(count * fabsf(offset.x)));
                    else
                        bounds->HExpand(ceilf(count * fabsf(offset.x)), 0);
                    if (offset.y > 0 )
                        bounds->VExpand(0, ceilf(count * fabsf(offset.y)));
                    else
                        bounds->VExpand(ceilf(count * fabsf(offset.y)), 0);
                }
                break;
            }
            default:
                break;
        }
    }   
    return boundsEmpty;
}

void TreeNode::NodeData::contractByFilterBounds(RectF* bounds) const
{
    const FilterState* filterState = GetState<FilterState>();
    const FilterSet* filters = filterState ? filterState->GetFilters() : 0;
    if ( !filters )
        return;

    for (unsigned i = 0; i < filters->GetFilterCount(); ++i )
    {
        // Visit filters in reverse order.
        const Filter* filter = filters->GetFilter(filters->GetFilterCount()-i-1);
        switch( filter->GetFilterType() )
        {
        case Filter_Blur:
        case Filter_Shadow:
        case Filter_Glow:
        case Filter_Bevel:
            {
                const BlurFilter* blurFilter = (const BlurFilter*)filter;
                const BlurFilterParams& params = blurFilter->GetParams();

                // The filter area must be extended even for inner shadows as the blurred area outside is still read
                float count = params.Mode & BlurFilterParams::Mode_Highlight ? 2.0f : 1.0f;
                bounds->Contract( count * ceilf(params.BlurX * params.Passes), 
                    count * ceilf(params.BlurY * params.Passes) );

                if (filter->GetFilterType() == Filter_Shadow || filter->GetFilterType() == Filter_Bevel)
                {
                    PointF offset = params.Offset;
                    if (offset.x > 0)
                        bounds->HContract(0, ceilf(count * fabsf(offset.x)));
                    else
                        bounds->HContract(ceilf(count * fabsf(offset.x)), 0);
                    if (offset.y > 0 )
                        bounds->HContract(0, ceilf(count * fabsf(offset.y)));
                    else
                        bounds->HContract(ceilf(count * fabsf(offset.y)), 0);
                }
                break;
            }
        default:
            break;
        }
    }   
}

void TreeNode::NodeData::CopyGeomData(TreeNode* destNode, const TreeNode& srcNode)
{
    SF_ASSERT(destNode);
    SF_ASSERT(destNode->GetReadOnlyData() == this);
    if (destNode == &srcNode)
        return;

    const NodeData& srcData = *srcNode.GetReadOnlyData();

    if (IsVisible() != srcNode.IsVisible())
    {
        destNode->SetVisible(srcNode.IsVisible());
        // Invisible items retain their bounds, but parent doesn't
        // consider them in bounds computation. This means that
        // we require parent update in bound computation.
        if (destNode->Entry::GetParent())
            destNode->Entry::GetParent()->AddToPropagate();
    }
    // need to transfer matrix and color transform from old to new node;
    // old node should be set to Identity for both matrix and cxform.
    // Also, do this for other properties (visible, blendMode, s9g, 3d, etc)
    if (srcData.Is3D())
    {
        SetMatrix3D(srcData.M3D());

        Matrix4F m4;
        if (srcNode.GetProjectionMatrix3D(&m4))
            destNode->SetProjectionMatrix3D(m4);
        Matrix3F m3;
        if (srcNode.GetViewMatrix3D(&m3))
            destNode->SetViewMatrix3D(m3);
    }
    else
        SetMatrix(srcData.M2D());

    Cx = srcData.Cx;

    destNode->SetBlendMode(srcNode.GetBlendMode());

    Render::RectF s9g = srcNode.GetScale9Grid();
    if (!s9g.IsEmpty())
    {
        destNode->SetScale9Grid(s9g);
    }
}

void TreeNode::Clear3D()           
{  
    // If they are switching from 3D to 2D, we need to reflect those changes.
    unsigned flags = Change_Matrix;
    if ( GetReadOnlyData()->Is3D() )    // if was 3D (and now 2D), set change flag
        flags |= Change_3D;

    NodeData* pdata = GetWritableData(flags); // |Change_AproxBounds
    pdata->SetMatrix3D(Matrix3F::Identity);
    pdata->Clear3D();
}

void TreeNode::SetMatrix(const Matrix2F& m)
{
    // If they are switching from 3D to 2D, we need to reflect those changes.
    unsigned flags = Change_Matrix;
    NodeData* pdata = GetWritableData(flags); // |Change_AproxBounds
    pdata->SetMatrix(m);
    /*
    RectF r = m.EncloseTransform(pdata->AproxLocalBounds);
    if (r != pdata->AproxParentBounds)
    {
        pdata = GetWritableData(Change_AproxBounds);
        pdata->AproxParentBounds = r;
        if (pParent)
            pParent->AddToPropagate();
  
    } */
    
    // Update our own bounds, then parent if needed.
    AddToPropagate();
}

void TreeNode::SetMatrix3D(const Matrix3F& m)
{
    // If they are switching from 2D to 3D, we need to reflect those changes.
    unsigned flags = Change_Matrix;
    if ( !GetReadOnlyData()->Is3D() )   // if was 2D (and now 3D), set change flag
        flags |= Change_3D;

    NodeData* pdata = GetWritableData(flags); // |Change_AproxBounds
    pdata->SetMatrix3D(m);
    /*
    RectF r = m.EncloseTransform(pdata->AproxLocalBounds);
    if (r != pdata->AproxParentBounds)
    {
        pdata = GetWritableData(Change_AproxBounds);
        pdata->AproxParentBounds = r;
        if (pParent)
            pParent->AddToPropagate();
  
    } */
    
    // Update our own bounds, then parent if needed.
    AddToPropagate();
}

void TreeNode::CalcViewMatrix(Matrix2F *m) const
{    
    *m = GetReadOnlyData()->M2D();
    appendAncestorMatrices(m);
}

void TreeNode::appendAncestorMatrices(Matrix2F *m) const
{
    const TreeNode* p = this;
    while(p->GetParent())
    {
        p = p->GetParent();
        m->Append(p->GetReadOnlyData()->M2D());
    }
}


void TreeNode::SetVisible(bool visible)
{
    if (IsVisible() != visible)
    {
        NodeData* pdata = GetWritableData(Change_Visible);
        pdata->SetVisible(visible);

        // Invisible items retain their bounds, but parent doesn't
        // consider them in bounds computation. This means that
        // we require parent update in bound computation.
        if (Entry::GetParent())
            Entry::GetParent()->AddToPropagate();
    }
}

void  TreeNode::SetEdgeAAMode(EdgeAAMode edgeAA)
{
    if (GetEdgeAAMode() != edgeAA)
    {
        NodeData* pdata = GetWritableData(Change_EdgeAAMode);
        pdata->SetEdgeAAMode(edgeAA);
    }
}


const State* TreeNode::GetState(StateType state) const
{
    return GetReadOnlyData()->States.GetState(state);
}

void TreeNode::SetScale9Grid(const RectF& rect)
{
    NodeData* pdata = GetWritableData(Change_State_Scale9);
    if (rect.x1 < rect.x2 && rect.y1 < rect.y2)
    {
        Ptr<Scale9GridRect> s9gr = *SF_HEAP_AUTO_NEW(this) Scale9GridRect;
        if (s9gr)
        {
            s9gr->Scale9 = rect;
            pdata->States.SetState(&Scale9State::InterfaceImpl, s9gr.GetPtr());
        }
    }
    else
    {
        pdata->States.RemoveState(State_Scale9);
    }
}

void TreeNode::SetViewMatrix3D(const Matrix3F& mat3D)
{
    // allocate space and copy
    NodeData* pdata = GetWritableData(Change_State_ViewMatrix3D);
    Ptr<Matrix3FRef> pmat3D = *SF_HEAP_AUTO_NEW(this) Matrix3FRef;
    *pmat3D = mat3D;    
    pdata->States.SetState(&ViewMatrix3DState::InterfaceImpl, pmat3D.GetPtr());
    pdata->Flags |= NF_HasViewMatrix3D;
}

void TreeNode::SetProjectionMatrix3D(const Matrix4F& mat3D)
{
    // allocate space and copy
    NodeData* pdata = GetWritableData(Change_State_ProjectionMatrix3D);
    Ptr<Matrix4FRef> pmat3D = *SF_HEAP_AUTO_NEW(this) Matrix4FRef;
    *pmat3D = mat3D;    
    pdata->States.SetState(&ProjectionMatrix3DState::InterfaceImpl, pmat3D.GetPtr());
    pdata->Flags |= NF_HasProjectionMatrix3D;
}

void TreeNode::SetBlendMode(BlendMode mode)
{
    NodeData* pdata = GetWritableData(Change_State_BlendMode);
    if (mode != Blend_None)
        pdata->States.SetStateVoid(&BlendState::InterfaceImpl, (void*)mode);
    else
        pdata->States.RemoveState(State_BlendMode);
}

void TreeNode::SetMaskNode(TreeNode* node)
{
    NodeData* pdata = GetWritableData(Change_State_MaskNode);
    if (node)
    {
        if (setThisAsMaskOwner(pdata, node))
            pdata->States.SetStateVoid(&MaskNodeState::InterfaceImpl, (void*)node);
    }
    else
    {
        if (removeThisAsMaskOwner(pdata))
        {
            pdata->States.RemoveState(State_MaskNode);
            pdata->Flags &= ~NF_HasMask;
        }
    }
    AddToPropagate();
}

void TreeNode::SetFilters(const FilterSet* filters)
{
    if ( filters && filters->GetFilterCount() > 0 )
    {
        // allocate space and copy
        Ptr<FilterSet> set = *filters->Clone();
        NodeData* pdata = GetWritableData(Change_State_Filter);
        pdata->States.SetState(&FilterState::InterfaceImpl, set);
        pdata->Flags |= NF_HasFilter;
    }
    else if ( GetReadOnlyData()->HasFilter() )
    {
        NodeData* pdata = GetWritableData(Change_State_Filter);
        pdata->States.RemoveState(State_Filter);
        pdata->Flags &= ~NF_HasFilter;
    }
    else
    {
        // Do not add to propagation, unless something actually changed.
        return;
    }

    // Update our own bounds, then parent if needed.
    AddToPropagate();
}

bool TreeNode::setThisAsMaskOwner(NodeData* thisData, TreeNode* node)
{
    NodeData* pmaskData = node->GetWritableData(Change_IsMask);
#ifdef SF_BUILD_DEBUG
    // Error / warn if mask already has a different owner.
    if (pmaskData->IsMaskNode() && (pmaskData->GetMaskOwner() != this))
    {
        SF_DEBUG_WARNING1(1, "TreeNode::SetMaskNode failed - node %p already has owner", node);
        return false;
    }
    if (node->GetParent() && (node->GetParent() != this))
    {
        SF_DEBUG_WARNING1(1, "TreeNode::SetMaskNode failed - node %p already has parent", node);
        return false;
    }
#endif
    // Record the us as owner in mask state.
    node->SetParent(this);
    pmaskData->Flags |= NF_MaskNode;
    pmaskData->States.SetStateVoid(&Internal_MaskOwnerState::InterfaceImpl, (void*)this);
    thisData->Flags |= NF_HasMask;    
    // TBD: Mask node's parent shouldn't include it in bounds?
    //if (node->pParent)
    //    node->GetParent()->AddToPropagate();
    return true;
}

bool TreeNode::removeThisAsMaskOwner(const NodeData* thisData)
{
    const MaskNodeState* mns = thisData->States.GetState<MaskNodeState>();
    if (mns)
    {
        NodeData* pmaskData = mns->GetNode()->GetWritableData(Change_IsMask);
        mns->GetNode()->SetParent(0);
        SF_ASSERT(pmaskData->IsMaskNode());
        // TBD: Check owner match for debug?
        pmaskData->Flags &= ~NF_MaskNode;
        pmaskData->States.RemoveState(State_Internal_MaskOwner);
        return true;
    }
    return false;
}

// copies all matrices, cxform, visibility from src to 'this' node.
void TreeNode::CopyGeomData(const TreeNode& src)
{
    GetWritableData(Change_Matrix|Change_CxForm)->CopyGeomData(this, src);
}


//--------------------------------------------------------------------
// ***** TreeNodeArray implementation


TreeNodeArray::ArrayData* TreeNodeArray::allocByCapacity(UPInt capacity, UPInt size)
{    
    UPInt       allocSize = sizeof(ArrayData) + sizeof(TreeNode*) * (capacity - FirstNodeSize);
    ArrayData*  pdata = (ArrayData*)SF_HEAP_AUTO_ALLOC(this, allocSize);
    if (pdata)
    {
        pdata->RefCount = 1;
        pdata->Size = size;
    }
    return pdata;
}

TreeNodeArray::TreeNodeArray(const TreeNodeArray& src)
{
    SF_COMPILER_ASSERT(FixedStoreSize == 2);
    pNodes[0] = src.pNodes[0];
    pNodes[1] = src.pNodes[1];

    if (src.hasArrayData())
    {
        src.getArrayData()->AddRef();
        pNodes[1] = 0; // Clear capacity.
    }
}

void TreeNodeArray::operator = (const TreeNodeArray& src)
{
    SF_COMPILER_ASSERT(FixedStoreSize == 2);
    UPInt destData0 = pData[0];
    UPInt srcData1  = src.pData[1];

    if (src.hasArrayData())
    {
        src.getArrayData()->AddRef();
        // Clear capacity to signal mutation.
        srcData1 = 0; 
    }
    if (hasArrayDataBit(destData0))
        toArrayData(destData0)->Release();

    pData[0] = src.pData[0];
    pData[1] = srcData1;
}

TreeNode*const* TreeNodeArray::GetMultipleAt(UPInt index) const
{
    TreeNode*const* nodes;
    
    if (!pNodes[0])
    {
        if (index == 0)
            return 0;
        // Empty array can't be indexed.
        SF_ASSERT(1);
    }    

    if (hasArrayData())
    {
        ArrayData* data = getArrayData();
        SF_ASSERT(index < data->Size);
        nodes = data->pNodes;
    }
    else
    {
        SF_ASSERT(index < FixedStoreSize);
        nodes = pNodes;
    }
    return nodes + index;
}


bool TreeNodeArray::Insert(UPInt index, TreeNode* node)
{
    // Due to the way array is designed, we don't allow null nodes.
    SF_ASSERT(node != 0);

    if (!pNodes[0])
    {
        SF_ASSERT(index == 0);
        pNodes[0] = node;
        return true;
    }
    if (!hasArrayData())
    {
        SF_COMPILER_ASSERT(FixedStoreSize == 2);

        if (pNodes[1] == 0)
        {
            SF_ASSERT(index < 2);
            if (index == 0)
                pNodes[1] = pNodes[0];
            pNodes[index] = node;
        }
        else
        {
            SF_ASSERT(index < 3);

            // Need to allocate .
            UPInt      capacity = calcIncreasedCapacity(2);
            ArrayData* data = allocByCapacity(capacity, 3);
            if (!data)
                return false;

            switch(index)
            {
            case 0:
                data->pNodes[1] = pNodes[0];
                ((TreeNode**)data->pNodes)[2] = pNodes[1];
                break;
            case 1:                
                data->pNodes[0] = pNodes[0];
                ((TreeNode**)data->pNodes)[2] = pNodes[1];
                break;
            case 2:
                data->pNodes[0] = pNodes[0];
                data->pNodes[1] = pNodes[1];
            default:
                break;
            }
            data->pNodes[index] = node;
            setArrayData(data, capacity);
        }
        return true;
    }

    // Handle inserting into allocated array data.
    ArrayData* data = getArrayData();
    SF_ASSERT(index <= data->Size);

    if (((data->Size + 1) <= getCapacity())) //&& (data->RefCount == 1))
    {
        // RefCount != 1 would imply that SignalFrameCapture wasn't called properly.
        SF_ASSERT(data->RefCount == 1);
        // Ok to insert up to capacity; do so after making space.
        for(UPInt j = data->Size; j > index; j--)
            data->pNodes[j] = data->pNodes[j-1];
        data->pNodes[index] = node;
        data->Size++;
    }
    else
    {
        // Reallocate unconditionally.
        UPInt      newCapacity = calcIncreasedCapacity(data->Size);
        ArrayData* newData     = allocByCapacity(newCapacity, data->Size + 1);
        if (!newData)
            return false;

        if (index > 0)
            memcpy(newData->pNodes, data->pNodes, index * sizeof(TreeNode*));
        newData->pNodes[index] = node;
        if (index < data->Size)
            memcpy(newData->pNodes + index + 1, data->pNodes + index,
                   (data->Size - index) * sizeof(TreeNode*));

        data->Release();
        setArrayData(newData, newCapacity);
    }

    return true;
}

bool TreeNodeArray::Remove(UPInt index, UPInt count)
{
    SF_ASSERT(index <= GetSize());
    SF_ASSERT(pNodes[0] || (count == 0));
       
    if (count == 0)
        return true;

    // Handle removal in two-slot fixed case.
    // This simple if logic is easier and likely more efficient
    // then implementing a general case.
    if (!hasArrayData())
    {
        SF_COMPILER_ASSERT(FixedStoreSize == 2);

        if (pNodes[1] == 0)
        {
            SF_ASSERT((index == 0) && (count == 1));
            pNodes[0] = 0;
        }
        else
        {
            if (count == 2)
            {
                SF_ASSERT(index == 0);
                pNodes[0] = 0;
                pNodes[1] = 0;
            }
            else
            {
                SF_ASSERT(count == 1);
                if (index == 0)
                {
                    pNodes[0] = pNodes[1];
                    pNodes[1] = 0;
                }
                else
                {
                    pNodes[1] = 0;
                }
            }
        }
        return true;
    }

    // Handle removal from allocated array.
    ArrayData* data = getArrayData();
    UPInt      newSize = data->Size - count;
    SF_ASSERT((index+count) <= data->Size);

    // Free buffer only if fall to 0,1; 2 items is left as array
    // for minimal hysteresis.
    if (newSize <= 1)
    {
        if (newSize == 1)
        {
            if (index != 0)
                pNodes[0] = data->pNodes[0];
            else
                pNodes[0] = data->pNodes[index+count];
        }
        else
        {
            pNodes[0] = 0;
        }
        pNodes[1] = 0;
        data->Release();
        return true;
    }

    UPInt newCapacity;

    // Capacity non-zero check verifies that modify-in-place is
    // allowed, since SignalFrameCapture sets it to 0.
    if (getCapacity())
    {
        // RefCount != 1 would imply that SignalFrameCapture wasn't
        // called properly.
        SF_ASSERT(data->RefCount == 1);
        newCapacity = calcRemoveCapacity(getCapacity(), newSize);
    }
    else
    {
        newCapacity = roundUpSize(newSize);
    }

    if (newCapacity != getCapacity())
    {
        // Realloc.
        ArrayData* newData = allocByCapacity(newCapacity, newSize);
        if (!newData)
            return false;

        if (index > 0)
            memcpy(newData->pNodes, data->pNodes, index * sizeof(TreeNode*));
        if ((index+count) < data->Size)
            memcpy(newData->pNodes + index, data->pNodes + index + count,
                   (data->Size - index - count) * sizeof(TreeNode*));
        data->Release();
        setArrayData(newData, newCapacity);
    }
    else
    {
        // Move memory.
        for(UPInt j = index; j < newSize; j++)
            data->pNodes[j] = data->pNodes[j+count];
        data->Size = newSize;
        setCapacity(newCapacity);
    }

    return true;
}



//--------------------------------------------------------------------
// ***** TreeContainer implementation

bool TreeContainer::Insert(UPInt index, TreeNode* pnode)
{
    SF_ASSERT(pnode);
    NodeData* pdata  = GetWritableData(Change_ChildInsert);
    bool      result = pdata->Children.Insert(index, pnode);

   // printf(" i%p", pdata);

    if (result)
    {
        SF_ASSERT(pnode->GetParent() == 0);
        pnode->SetParent(this);
        pnode->AddRef();
        AddToPropagate();
    }
    return result;
}

void TreeContainer::Remove(UPInt index, UPInt count)
{
    if (count == 0)
        return;
    NodeData* pdata = GetWritableData(Change_ChildRemove);

  //  printf(" r%p", pdata);

    // TBD: Need to check return code!
    TreeNode*const* pn = pdata->Children.GetMultipleAt(index);
    UPInt           c  = count;
    while(c--)
    {
        SF_ASSERT((*pn)->GetParent() == this);
        (*pn)->SetParent(0);
        (*pn)->Release();
        pn++;
    }
    AddToPropagate();
    //Release_Multiple(pdata->Children.GetMultipleAt(index), count);
    bool  result = pdata->Children.Remove(index, count);
    SF_ASSERT(result != false);
    SF_UNUSED(result);
}


void TreeContainer::NodeData::ReleaseNodes() const
{
    UPInt c = Children.GetSize();
    if (c != 0)
    {
        TreeNode*const* pn = Children.GetMultipleAt(0);
        while(c--)
        {
            SF_ASSERT((*pn)->GetParent());
            (*pn)->SetParent(0);
            (*pn)->Release();
            pn++;
        }
    }
    BaseClass::ReleaseNodes();
}

bool TreeContainer::NodeData::PropagateUp(Context::Entry* entry) const
{
    TreeContainer* pc = (TreeContainer*)entry;

    UPInt           count = Children.GetSize();
    TreeNode*const* nodes = Children.GetMultipleAt(0);

    RectF   bounds, parentBounds;
    bool    boundsEmpty = true;

    for (UPInt i = 0; i< count; i++)
    {
        TreeNode* child = nodes[i];
        const TreeNode::NodeData* childData = child->GetReadOnlyData();

        if (childData->IsVisible() && !childData->AproxParentBounds.IsEmpty())
        {
            if (boundsEmpty)
            {
                bounds = childData->AproxParentBounds;
                boundsEmpty = false;
            }
            else
            {
                bounds.UnionRect(&bounds, childData->AproxParentBounds);
            }
        }
    }

    // Doesn't work because  
    //if (HasMask())
    //    boundsEmpty = expandByMaskBounds(pc, &bounds, boundsEmpty);

    if (!boundsEmpty)
    {
        // Must apply any filters to the bounds before it is transformed into parent space.
        boundsEmpty = expandByFilterBounds(&bounds, false );
        if ( !Is3D() )
        {
            parentBounds = M2D().EncloseTransform(bounds);
        }
        else
        {
            parentBounds = M3D().EncloseTransform(bounds);
        }
    }


    if ((bounds != AproxLocalBounds) || (parentBounds != AproxParentBounds))
    {
        // Bounds change should cause Matrix change (for now)
        //  - needed for culling on this object to be recomputed.
        //  - TBD: May be this can be partial update.... such as parent cull check and done.
        NodeData* wdata = pc->GetWritableData(Change_AproxBounds | Change_Matrix);
        wdata->AproxLocalBounds = bounds;
        wdata->AproxParentBounds= parentBounds;

        // Call SignalFrameCapture to ensure that child arrays are "frozen" to
        // ensure thread safety for their content.
        if (pc->GetChange())
            wdata->Children.SignalFrameCapture();

        // Mark mask parent as having changed bounds+matrix update, as it is
        // needed since currently mask is not apart of computed bounds.
        // Matrix update ensures mask bounds/bounds matrix is updated too.
        // TBD: Is this not enough? What about parent matrix change?
        // Doesn't work well, since mask node bounds don't necessarily change above
        // when child mask moves.
        //if (IsMaskNode())
        //    pc->GetParent()->GetWritableData(Change_AproxBounds | Change_Matrix);

        return IsVisible();
    }
    else
    {
        if (pc->GetChange())
            pc->GetWritableData(0)->Children.SignalFrameCapture();
    }
    return false;
}

/*
// Computes mask bounds and expands bounds by it; returns the
// new boundsEmpty flag.
bool TreeContainer::NodeData::expandByMaskBounds(const TreeNode *thisNode,
                                                 RectF* bounds, bool boundsEmpty) const
{
    TreeNode*                 maskNode = GetState<MaskNodeState>()->GetNode();
    const TreeNode::NodeData* maskNodeData = maskNode->GetReadOnlyData();

    if (!maskNodeData->IsVisible() || maskNodeData->AproxParentBounds.IsEmpty())
        return boundsEmpty;

    // Transform mask into our coordinate system. Transform logic has
    // optimized special cases for direct child/sibling masks.
    Matrix2F m(maskNodeData->M);

    if (maskNode->GetParent() != thisNode)
    {
        Matrix2F m2;
        if (maskNode->GetParent() == thisNode->GetParent())
            m2.SetInverse(M);
        else
        {
            Matrix2F m3;
            maskNode->appendAncestorMatrices(&m);
            thisNode->CalcViewMatrix(&m3);
            m2.SetInverse(m3);
        }
        m.Append(m2);
    }

    RectF maskBounds = m.EncloseTransform(maskNodeData->AproxLocalBounds);

    if (!boundsEmpty)
        bounds->UnionRect(bounds, maskBounds);
    else
        *bounds = maskBounds;

    return true;
}
*/

TreeCacheNode*  TreeContainer::NodeData::updateCache(TreeCacheNode* pparent,
                                                     TreeCacheNode* pinsert,
                                                     TreeNode* pnode, UInt16 depth) const
{
    // Create & insert node if it doesn't already exist.
    TreeContainer*      pcontainer = (TreeContainer*)pnode;
    TreeCacheContainer* pcache = (TreeCacheContainer*)pnode->GetRenderData();
    if (!pcache)
    {        
        // Pass NF_MaskNode|NF_PartOfMask in constructor for consistency with Shape,
        // which needs it to create proper SortKey.
        unsigned cnodeFlags = (GetFlags() & NF_Visible) |
                              TreeCacheNode::CalcEdgeAAMode(this, pparent);
        if (IsMaskNode())
            cnodeFlags |= NF_MaskNode|NF_PartOfMask;
        if (Is3D())
            cnodeFlags |= NF_3D;

        pcache = SF_HEAP_AUTO_NEW(pparent)
                 TreeCacheContainer(pcontainer, pparent->pRenderer2D, cnodeFlags);
        pnode->SetRenderData(pcache);

		if (pnode == g_IMETreeNode)
		{
			g_IMETreeCacheNode = pcache;
		}

        if (!pcache)
            return 0;
    }

    // Insert node if not yet in parent. Update pRoot, Depth, pParent and child subtree. 
    pcache->UpdateInsertIntoParent(pparent, pinsert, this, depth);
    return pcache;    
}

//--------------------------------------------------------------------
// ***** TreeRoot implementation

void TreeRoot::SetViewport(const Viewport& vp)
{
    if (GetReadOnlyData()->VP != vp)
    {
        NodeData* data = GetWritableData(Change_Viewport);
        data->VP = vp;
    }
}

//shan@snda[
void TreeRoot::SetFilterCacheDisable()
{
	TreeCacheRoot  *prootCache = (TreeCacheRoot*)GetRenderData();
	prootCache->SetFilterCacheDisable();
}
//shan@snda]


}} // Scaleform::Render

