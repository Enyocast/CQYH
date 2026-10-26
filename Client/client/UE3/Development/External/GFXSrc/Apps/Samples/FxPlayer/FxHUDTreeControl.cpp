/**************************************************************************

Filename    :   FxHUDTreeControl.cpp
Content     :   Statistics reporting base item for FxPlayer 
Created     :   February 2, 2009
Authors     :   Dmitry Polenur

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "FxHUDTreeControl.h"
#include "FxReportCollector.h"
#include "FxResourceStats.h"
// ***** FxPlayerStatHudControl

// Implementation FxReportOutput for Tree control
class FxArrayReportOutput : public FxReportOutput
{
    Array<String> StringArray;
public:
    inline const Array<String>& GetStringArray() {return StringArray;}
    const String& GetString(UPInt i) 
    {
        SF_ASSERT( i < StringArray.GetSize()); 
        return  StringArray[i];
    }
    virtual void Clear() { StringArray.Clear(); }
    virtual void AddLine(const char* pname, const char* ptext)
    {
        StringArray.PushBack(String(pname, ptext, "\n"));
    }

};


void FxTreeControl::PushBack( FxStatItem* pitem, bool includeRoot /*= false*/ )
{
    if (pitem->IsHidden())
        return;

    if (includeRoot)
    {
        TempListElement.pItem = pitem;
        DisplayList.PushBack(TempListElement);
        pitem->SetShown(true);
    }

    if(!pitem->IsExpanded())
        return;

    for (unsigned i = 0; i < pitem->GetChildCount(); i++)
    {
        FxStatItem* pchild = pitem->GetChild(i);
        PushBack(pchild, true);
    }
}

UPInt FxTreeControl::InsertAt( UPInt index, FxStatItem* pitem, bool includeRoot /*= false*/ )
{   
    unsigned nInserted = 0;

    if (pitem->IsHidden())
        return nInserted;

    if (includeRoot)
    {
        TempListElement.pItem = pitem; 
        DisplayList.InsertAt(index, TempListElement);
        pitem->SetShown(true);
        nInserted++;
    }

    if(!pitem->IsExpanded())
        return nInserted;

    UPInt currentIndex = index + nInserted;
    for (unsigned i = 0; i < pitem->GetChildCount(); i++)
    {
        FxStatItem* pchild = pitem->GetChild(i);
        currentIndex += InsertAt(currentIndex, pchild, true);
    }
    return currentIndex - index;
}

UPInt FxTreeControl::RemoveAt( UPInt index, bool includeRoot /*= false*/ )
{    
    UPInt nRemoved = GetLastDesendantPosition(index) - index;

    if(includeRoot)
        ++nRemoved;
    else
        ++index;
   
    for (UPInt i = index; i < index + nRemoved; i++)
        DisplayList[i].pItem->SetShown(false);

    DisplayList.RemoveMultipleAt(index, nRemoved);
    return nRemoved;
}


void FxTreeControl::OnItemCommand( const char* pcommand, int index )
{
    if (index >= 0 && index < (int)DisplayList.GetSize())
    {
        CurrentLine = index;
        FxStatItem* pitem = DisplayList[index].pItem;

        if (pitem->IsExpanded())
		{
			 if (SFstrcmp(pcommand, "click") == 0 || SFstrcmp(pcommand, "left") == 0)
				CollapseItem((UPInt)index);
		}
		else
		{
			if (SFstrcmp(pcommand, "click") == 0 || SFstrcmp(pcommand, "right") == 0)
				ExpandItem((UPInt)index);
		}
    }
}

void FxTreeControl::ExpandItem(UPInt index )
{
    FxStatItem* pitem = DisplayList[index].pItem;
    DisplayList[index].pItem->SetExpanded(true);
    UPInt nInserted = InsertAt(index + 1, pitem, false);

    //Expanding/collapsing item may change formating for other lines 
    FxArrayReportOutput report;
    FxReportCollector rc(&report);
    rc.ReportItems(pTree);
    SF_ASSERT(report.GetStringArray().GetSize() == DisplayList.GetSize());
    UpdateStrings(0, index, report.GetStringArray());
    if (pDisplayUpdate)
        pDisplayUpdate->Insert(index + 1, report.GetStringArray(), index + 1, index +  nInserted);
    UpdateStrings(index + nInserted + 1, report.GetStringArray().GetSize() - 1, report.GetStringArray());
}


void FxTreeControl::CollapseItem(UPInt index )
{   
    DisplayList[index].pItem->SetExpanded(false);
    UPInt nRemoved =  RemoveAt(index,  false);

    //Expanding/collapsing item may change formating for other lines 
    FxArrayReportOutput report;
    FxReportCollector rc(&report);
    rc.ReportItems(pTree);
    if (pDisplayUpdate)
        pDisplayUpdate->Remove(index + 1, nRemoved);
    SF_ASSERT(report.GetStringArray().GetSize() == DisplayList.GetSize());
    UpdateStrings(0, report.GetStringArray().GetSize() -1, report.GetStringArray());
}


void FxTreeControl::UpdateData()
{
    FxArrayReportOutput report;
    FxReportCollector rc(&report);
    rc.ReportItems(pTree);
    if (DisplayList.GetSize() > 0)
        UpdateStrings(0, DisplayList.GetSize() - 1, report.GetStringArray());
}


void FxTreeControl::UpdateStrings( UPInt start, UPInt end, const Array<String>& strList )
{
 //   PrintDisplayList();
 //   PrintReport();
    bool isTreeChanged = false;
    int  replaceStart = -1;
    int  replaceEnd = -1;
    for (UPInt i = start; i <= end; i++)
    {
        String str;
        //Update only items with changed strings
        if (DisplayList[i].CurrentStr != strList[i])
        {
            if (replaceStart < 0)
            {
                replaceStart = replaceEnd = (int)i;
            }
            else
            {
                replaceEnd = (int)i;
            }
            DisplayList[i].CurrentStr = strList[i];       
        }
        else
        {
            SF_ASSERT(replaceEnd >= replaceStart);
            if (pDisplayUpdate && replaceStart >=0)
            {
                pDisplayUpdate->Replace(replaceStart, strList, replaceStart, replaceEnd);
                replaceStart = replaceEnd = -1;
            }
        }
        //If NeedsRefresh is true,  then pDisplayUpdate had bee notified before 
        if (!NeedsRefresh && !isTreeChanged && DisplayList[i].pItem->IsChanged())
            isTreeChanged = true; 
    }

    if (pDisplayUpdate && replaceStart >=0)
        pDisplayUpdate->Replace(replaceStart, strList, replaceStart, replaceEnd);

    if (isTreeChanged)
    {
        pDisplayUpdate->SetRefreshButton(true);
        NeedsRefresh = true;
    }
}


FxTreeControl::FxTreeControl( FxStatItem* ptree ) 
: pDisplayUpdate(NULL), CurrentLine(-1), IsActive(false), NeedsRefresh(false)
{
    SetTree(ptree);
}


void FxTreeControl::SetTree( FxStatItem* ptree )
{
    SF_ASSERT(ptree);
    pTree = ptree;
    //Reset();
}


void FxTreeControl::Reset()
{
    DisplayList.Clear(); 
    pTree->SetExpanded(true);
    pTree->SetHidden(false);
    //if (pTree->GetChildCount() > 0)
    //{
    //    FxStatItem* pchild = pTree->GetChild(0);
    //    pchild->SetExpanded(true);
    //    pchild->SetHidden(false);        
    //}
    PushBack(pTree, true);
    

    if (pDisplayUpdate)
    {
        pDisplayUpdate->Clear();
        FxArrayReportOutput report;
        FxReportCollector rc(&report);
        rc.ReportItems(pTree);
        if (report.GetStringArray().GetSize() > 0)
            pDisplayUpdate->Insert(0, report.GetStringArray(), 0, report.GetStringArray().GetSize()-1);

        for (unsigned i = 0; i < DisplayList.GetSize(); i++)
        {
            DisplayList[i].CurrentStr = report.GetString(i);      
        }
    }
}


void FxTreeControl::Insert( FxStatItem* pitem)
{
    FxStatItem* pparent = pitem->GetParent();
    SF_ASSERT(pparent);

    int  parentIndex = GetItemPosition(pparent);
    if (parentIndex >= 0 && pparent->IsExpanded())
    {   
        CollapseItem(parentIndex);
        ExpandItem(parentIndex);
        //SF_ASSERT(!pitem->IsShown());

        ////Since other children could be open, we must find the right position - find next sibling and insert before it
        //unsigned nextSiblingIndex =  pitem->GetIndexInParent() + 1;
        //int  itemIndex;
        //if (pparent->GetChildCount() > nextSiblingIndex )
        //{
        //    FxStatItem* pnextSibling = pparent->GetChild(nextSiblingIndex);
        //    itemIndex = GetItemPosition(pnextSibling);
        //    if (itemIndex < 0)
        //        itemIndex = (int)GetLastDesendantPosition(parentIndex)+1;
        //}
        //else // Last child
        //{
        //    itemIndex = (int)GetLastDesendantPosition(parentIndex)+1;
        //}

        //UPInt nInserted = InsertAt(itemIndex, pitem, true); //Inserted items should not be expanded (?)
        //SF_ASSERT(nInserted == 1);
        //if (pDisplayUpdate)
        //    pDisplayUpdate->Insert(itemIndex, "\n");
    }
}


void FxTreeControl::Remove( FxStatItem* pitem)
{
    int  itemIndex = GetItemPosition(pitem);
    if (itemIndex > 0)
    {
        if (pitem->IsExpanded())
            CollapseItem(itemIndex);
        RemoveAt(itemIndex, true);
        if (pDisplayUpdate)
            pDisplayUpdate->Remove(itemIndex, 1);
    }
}


int  FxTreeControl::GetItemPosition( FxStatItem* pitem ) const
{
    int  position = -1;
    for (unsigned i = 0; i < DisplayList.GetSize(); i++ )
        if(DisplayList[i].pItem == pitem)
        {
            position = i;
            break;
        }
        return position;

}


UPInt FxTreeControl::GetLastDesendantPosition( UPInt index ) const
{
    FxStatItem* pitem = DisplayList[index].pItem;
    UPInt currentIndex = index + 1;

    //Calculate number of descendants in Displaylist
    while (currentIndex < DisplayList.GetSize())
    {
        bool isDescendant = false;
        FxStatItem* pprarent = DisplayList[currentIndex].pItem->GetParent();
        while (pprarent)
        {
            if (pprarent == pitem)
            {
                isDescendant = true;
                break;
            }
            else
                pprarent = pprarent->GetParent();
        }
        if (isDescendant)
            currentIndex++;
        else
            break;
    }
    return currentIndex - 1;
}

void FxTreeControl::RefreshItem( FxStatItem* pitem )
{
    pitem->SetChanged(false);
    if (pitem->IsDead() && pitem->IsExpired())
    {
        if (pitem->IsShown())
        {
            //Remove(pitem);
            pitem->SetShown(false);
        }
        // Need this so item will not appear after parent expansion before removal
        pitem->SetHidden(true); 
        return;
    }

    if (!pitem->IsShown())
    {
        pitem->SetHidden(false);
        //Insert(pitem);
    }

    for (unsigned i = 0; i < pitem->GetChildCount(); i++)
    {
        RefreshItem (pitem->GetChild(i));
    }
}

void FxTreeControl::Refresh()
{
    RefreshItem(pTree);
    NeedsRefresh = false;
    pDisplayUpdate->SetRefreshButton(false);
    Reset();
}
