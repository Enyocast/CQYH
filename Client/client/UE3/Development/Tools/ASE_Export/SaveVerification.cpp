//************************************************************************** 
//* SaveVerification.cpp -	A callback mechanism to validate that scene
//*							files are saved correctly.
//*
//* This plug-in works by subscribing to a 'post save' callback, and as soon
//* as a file is saved, the file will be reopened and validated. If the
//* validation fails,it will prompt the user to resave the file.
//* The validation is simply verifying that the file is a valid OLE structured
//* storage file and that the steams required by max is present - as such the
//* format is validated, but not the actual contents.
//* 
//* Christer Janson
//* Discreet, A division of Autodesk, Inc.
//*
//* October 28, 2002, CCJ - Initial coding.
//*
//* Copyright (c) 2002, All Rights Reserved. 
//***************************************************************************

#include "SaveVerification.h"
#include "asciiexp.h"
#include "impapi.h"
#include "simpobj.h"
#include "direct.h"
#include "object.h"
#include "maxsdk/include/maxscrpt/maxscrpt.h"

HWND hToolbarWnd = NULL; 
//#define TB_BUT_WIDTH 50
//#define TB_BUT_HEIGHT 50
SaveVerificationGUP::SaveVerificationGUP()
{
}

SaveVerificationGUP::~SaveVerificationGUP()
{
}

TSTR ReturnCurrentFileName()
{
	Interface *maxT = GetCOREInterface();
	TSTR filenameT = maxT->GetCurFileName();	 
	INT NumT = filenameT.length();
	TSTR FinalNameT = filenameT.Substr(0, NumT - 4);
	return FinalNameT;
}

TSTR ReturnCurrentFilePath()
{
	Interface *maxT = GetCOREInterface();
	TSTR filenameT = maxT->GetCurFilePath();
	INT NumT = filenameT.length();
	TSTR FinalNameT = filenameT.Substr(0, NumT - 4);
	_mkdir( FinalNameT );
	return FinalNameT;
}

TSTR ReturnCurrentPath()
{
	Interface *maxT = GetCOREInterface();
	TSTR PathFileName = maxT->GetCurFileName();	 
	TSTR filenamePath = maxT->GetCurFilePath();
	INT NumPathFileName = PathFileName.length();
	INT NumfilenamePath = filenamePath.length();
	TSTR FinalNameT = filenamePath.Substr( 0, NumfilenamePath - NumPathFileName - 1 );
	return FinalNameT;
}

void ChangeObjectAndCollisionName()
{
	char ModelNameStr[MAX_PATH], CollisonNameStr[MAX_PATH];

	_tcscpy( ModelNameStr, ReturnCurrentFileName() );	
	sprintf( CollisonNameStr, _T("%s_UCX"), ReturnCurrentFileName() );

	Interface *ip = GetCOREInterface();

	INode *pRoot =ip->GetRootNode();
	INT FirstObjFaceCount = 0;
	INT SecondObjFaceCount = 0;
	TimeValue t = ip->GetTime();
	int numFaces, numVerts;

	INode *pFirstObj = pRoot->GetChildNode(0);
	INode *pSecondObj = pRoot->GetChildNode(1);

	const ObjectState& osFirst = pFirstObj->EvalWorldState(t);
	Object* obFirst = osFirst.obj;
	GetTriMeshFaceCount(t, obFirst, numFaces, numVerts);
	FirstObjFaceCount = numFaces;

	const ObjectState& osSecond = pSecondObj->EvalWorldState(t);
	Object* obSecond = osSecond.obj;
	GetTriMeshFaceCount(t, obSecond, numFaces, numVerts);
	SecondObjFaceCount = numFaces;

	if ( FirstObjFaceCount > SecondObjFaceCount )
	{
		(*pFirstObj).SetName( (char*)ModelNameStr );
		(*pSecondObj).SetName( (char*)CollisonNameStr );
	}
	else
	{
		(*pSecondObj).SetName( (char*)CollisonNameStr );
		(*pFirstObj).SetName( (char*)ModelNameStr );
	}
}

void ChangeAllObjectName()
{
	char ModelNameStr[MAX_PATH];
	Interface *ip = GetCOREInterface();
	INode *pRoot =ip->GetRootNode();
	int numNodes = pRoot->NumberOfChildren();
	INT T = 0;
	TSTR CurSceFileName = ReturnCurrentFileName();
	for (INT i = 0; i < numNodes; i++ )
	{
	    INode *TempNode = pRoot->GetChildNode(i);
		if ( TempNode->GetObjectRef()->SuperClassID() != HELPER_CLASS_ID )
		{
			sprintf( ModelNameStr, _T("S_%s_0%d"), CurSceFileName, T );
			(*TempNode).SetName( (char*)ModelNameStr );
			++T;
		}
	}
}

void ChangeAllObjectNameBySpecific()
{
	char ModelNameStr[MAX_PATH];
	Interface *ip = GetCOREInterface();
	int numNodes = ip->GetSelNodeCount();
	INT T = 1;
	for (INT i = 0; i < numNodes; i++ )
	{	
		INode *TempNode = ip->GetSelNode(i);
		sprintf( ModelNameStr, _T("Explode0%d"), T );
		(*TempNode).SetName( (char*)ModelNameStr );
		++T;
	}
}

INT GetMtlIDCount( INode *node )
{
	TimeValue t = GetCOREInterface()->GetTime();


	Object *obj = node->EvalWorldState(t).obj;

	TriObject *tri= static_cast<TriObject *>( obj->ConvertToType(t, Class_ID(TRIOBJ_CLASS_ID, 0)))	;


	Mesh mesh = tri->GetMesh();

	INT Num = mesh.numFaces;

	int nmtl, numMtls=0,
		ZeroNum = 0,
		SecondNum = 0,
		ThirdNum = 0,
		FouthNum = 0,
		FifthNum = 0,
		SixthNum = 0,
		SeventhNum = 0,
		EighthNum = 0,
		NinthNum = 0,
		TenthNum = 0;		
	for ( INT i = 0; i < Num; i++ ) 
	{
		nmtl = mesh.faces[i].getMatID();
		switch(nmtl)
		{
			case 0:
				ZeroNum++;
				break;
			case 1:
				SecondNum++;
				break;
			case 2:
				ThirdNum++;
				break;
			case 3:
				FouthNum++;
				break;
			case 4:
				FifthNum++;
				break;
			case 5:
				SixthNum++;
				break;
			case 6:
				SeventhNum++;
				break;
			case 7:
				EighthNum++;
				break;
			case 8:
				NinthNum++;
				break;
			default:
				TenthNum++;
				break;
		}


		if ( nmtl != 0 ) 
		{
			numMtls++;
		}
	}
    return numMtls;
}

void AssignMtl( INode *node )
{
	char ModelNameStr[MAX_PATH];
	Interface *ip = GetCOREInterface();
	MultiMtl *newmat = NewDefaultMultiMtl();
	INT numMtls = GetMtlIDCount( node );
	newmat->SetNumSubMtls( numMtls );
	StdMat *m = NewDefaultStdMat();
	for ( int i = 0; i < numMtls; i++ ) 
	{
		sprintf( ModelNameStr, _T("%s_0%d"), node->GetName(), i+1 );
		m->SetName( ModelNameStr );
		newmat->SetSubMtl( i, m );
		ip->RedrawViews(ip->GetTime());
	}
	newmat->SetName( node->GetName() );
	node->SetMtl( newmat );
	ip->RedrawViews(ip->GetTime());
}

//SetParams(float width, float height, float length, int wsegs=1,int lsegs=1, 
//		  int hsegs=1, BOOL genUV=TRUE)=0; 

void ChangeSelectionObjectsName()
{
	char ModelNameStr[MAX_PATH];
	Interface *ip = GetCOREInterface();
	int numNodes = ip->GetSelNodeCount();
	TSTR CurSceFileName = ReturnCurrentFileName();
	for (INT i = 0; i < numNodes; i++ )
	{	
		INode *TempNode = ip->GetSelNode(i);
		sprintf( ModelNameStr, _T("S_%s_0%d"), CurSceFileName, i );
		(*TempNode).SetName( (char*)ModelNameStr );
		AssignMtl( TempNode );
	}
}

Point3 GetObjectCenterValue( INode *TNode )
{
	TimeValue N = GetCOREInterface()->GetTime();
	Box3 bbox;
	ViewExp* view = GetCOREInterface()->GetActiveViewport();
	TNode->GetObjectRef()->GetWorldBoundBox(N, TNode, view, bbox);
	GetCOREInterface()->ReleaseViewport(view);
	Point3 ObjCenter = bbox.Center();
	return ObjCenter;
}

FLOAT GetDistanceBetweenTwoNodes( Point3 SelCenter, Point3 ChildCenter )
{
   FLOAT DistanceVal = sqrt( pow( (SelCenter.x - ChildCenter.x), 2 ) + pow( (SelCenter.y - ChildCenter.y), 2 ) + pow( (SelCenter.z - ChildCenter.z), 2 ) );
   return DistanceVal;
}

void CreateCollisionObjects()
{
	Interface *ip = GetCOREInterface();
	int numNodes = ip->GetSelNodeCount();
	TimeValue N = GetCOREInterface()->GetTime();
	Box3 bbox;
	for (INT i = 0; i < numNodes; i++ )
	{	
		INode *TempNode = ip->GetSelNode(i);
		ViewExp* view = GetCOREInterface()->GetActiveViewport();
		TempNode->GetObjectRef()->GetWorldBoundBox(N, TempNode, view, bbox);
		GetCOREInterface()->ReleaseViewport(view);
		Point3 ObjCenter = bbox.Center();
		Point3 PointMin = bbox.Min();
		Point3 PointMax = bbox.Max();
		FLOAT XWidth = fabs( PointMax.x - PointMin.x );
		FLOAT ZHeight = fabs( PointMax.z - PointMin.z );
		FLOAT YLength = fabs( PointMax.y - PointMin.y );
		GenBoxObject *gb = (GenBoxObject *)CreateInstance(GEOMOBJECT_CLASS_ID, Class_ID(BOXOBJ_CLASS_ID, 0));
		gb->SetParams( XWidth, ZHeight, YLength );
		INode *node = ip->CreateObjectNode( gb );
		char ModelNameStr[MAX_PATH];
		sprintf( ModelNameStr, _T("%s_UCX"), TempNode->GetName() );
		node->SetName( ModelNameStr );
		node->XRayMtl(TRUE);
        node->CenterPivot( N , FALSE );
		Control *Ctr = node->GetTMController()->GetPositionController();
		Ctr->SetValue( N, ObjCenter );
	}
	ip->RedrawViews( N );
}

void ProcessSelectionCollisions()
{
	char ModelNameStr[MAX_PATH];
	Interface *ip = GetCOREInterface();
	int numNodes = ip->GetSelNodeCount();
	INode *pRoot =ip->GetRootNode();
	int numAllNodes = pRoot->NumberOfChildren();
    FLOAT DistanceValue[200];
	INode *AllNode[200];
	TimeValue N = ip->GetTime();
	for (INT i = 0; i < numNodes; i++ )
	{	
		INode *TempNode = ip->GetSelNode(i);
        INT T = 0;
		for (INT i = 0; i < numAllNodes; i++ )
		{
			INode *TNode = pRoot->GetChildNode(i);
			if ( TNode->GetObjectRef()->SuperClassID() != HELPER_CLASS_ID && TNode != TempNode )
			{
				Point3 TempPos;
				Interval Inter;
                AllNode[T] = TNode;
				DistanceValue[T] = GetDistanceBetweenTwoNodes( GetObjectCenterValue(TempNode), GetObjectCenterValue(TNode) ); 
                ++T;
			}
		}

		FLOAT Temp = DistanceValue[0];
		INT S = 0;
		for ( INT b = 1; b < T; b++ )
		{
            if ( DistanceValue[b] < Temp )
			{
                Temp = DistanceValue[b];
				S = b;
			}
		}

		sprintf( ModelNameStr, _T("%s_UCX"), AllNode[S]->GetName() );
		(*TempNode).SetName( (char*)ModelNameStr );
        TempNode->XRayMtl(TRUE);
	}
}

void ExportSelection()
{
	Interface *ip = GetCOREInterface();
	int numNodes = ip->GetSelNodeCount();
	TimeValue N = GetCOREInterface()->GetTime();
	Box3 bbox;
	Interval Inter;

	Point3 OrignalObjPos, OrignalCollisionPos;
     char DestPath[MAX_PATH];
	char *ModelNameStr;
	if ( numNodes == 2 )
	{
		char *NameOne = ip->GetSelNode(0)->GetName();
		char *NameTwo = ip->GetSelNode(1)->GetName();
		if ( strlen( NameOne ) > strlen( NameTwo ) )
			ModelNameStr = NameTwo;
		else
			ModelNameStr = NameOne;	
	}
	else
	{
	     ModelNameStr = ip->GetSelNode(0)->GetName();
	}

	for (INT i = 0; i < numNodes; i++ )
	{	
		switch(i)
		{
			case 0:
				{
					INode *TempNode = ip->GetSelNode(i);
					Control *Ctr = TempNode->GetTMController()->GetPositionController();
					Ctr->GetValue( N, OrignalObjPos, Inter );
				}
			break;
			case 1:
				{
					INode *TempNode = ip->GetSelNode(i);
					Control *Ctr = TempNode->GetTMController()->GetPositionController();
					Ctr->GetValue( N, OrignalCollisionPos, Inter );
				}
			break;
		}
	}

	for (INT i = 0; i < numNodes; i++ )
	{	
		INode *TempNode = ip->GetSelNode(i);
		Control *Ctr = TempNode->GetTMController()->GetPositionController();
		Ctr->SetValue( N, Point3(0,0,0) ); 
	}

	char PathStr[MAX_PATH];
	_tcscpy( PathStr, ReturnCurrentFilePath() );	

	sprintf (DestPath, "%s\\%s.ASE", (char*)PathStr, ModelNameStr );   
	AsciiExp s;			
	s.DoExport( DestPath, NULL, ip, TRUE, 1 ); 

	for (INT i = 0; i < numNodes; i++ )
	{	
		switch(i)
		{
		case 0:
			{
				INode *TempNode = ip->GetSelNode(i);
				Control *Ctr = TempNode->GetTMController()->GetPositionController();
				Ctr->SetValue( N, OrignalObjPos ); 
			}
			break;
		case 1:
			{
				INode *TempNode = ip->GetSelNode(i);
				Control *Ctr = TempNode->GetTMController()->GetPositionController();
				Ctr->SetValue( N, OrignalCollisionPos ); 
			}
			break;
		}
	}
}

void ExportSelectionToCurrentDir()
{
	Interface *ip = GetCOREInterface();
	int numNodes = ip->GetSelNodeCount();
	TimeValue N = GetCOREInterface()->GetTime();
	Box3 bbox;
	Interval Inter;

	Point3 OrignalObjPos, OrignalCollisionPos;
     char DestPath[MAX_PATH];
	char *ModelNameStr;
	if ( numNodes == 2 )
	{
		char *NameOne = ip->GetSelNode(0)->GetName();
		char *NameTwo = ip->GetSelNode(1)->GetName();
		if ( strlen( NameOne ) > strlen( NameTwo ) )
			ModelNameStr = NameTwo;
		else
			ModelNameStr = NameOne;	
	}
	else
	{
	     ModelNameStr = ip->GetSelNode(0)->GetName();
	}

	for (INT i = 0; i < numNodes; i++ )
	{	
		switch(i)
		{
			case 0:
				{
					INode *TempNode = ip->GetSelNode(i);
					Control *Ctr = TempNode->GetTMController()->GetPositionController();
					Ctr->GetValue( N, OrignalObjPos, Inter );
				}
			break;
			case 1:
				{
					INode *TempNode = ip->GetSelNode(i);
					Control *Ctr = TempNode->GetTMController()->GetPositionController();
					Ctr->GetValue( N, OrignalCollisionPos, Inter );
				}
			break;
		}
	}

	for (INT i = 0; i < numNodes; i++ )
	{	
		INode *TempNode = ip->GetSelNode(i);
		Control *Ctr = TempNode->GetTMController()->GetPositionController();
		Ctr->SetValue( N, Point3(0,0,0) ); 
	}

	char PathStr[MAX_PATH];
	_tcscpy( PathStr, ReturnCurrentPath() );	

	sprintf (DestPath, "%s\\%s.ASE", (char*)PathStr, ModelNameStr );   
	AsciiExp s;			
	s.DoExport( DestPath, NULL, ip, TRUE, 1 ); 

	for (INT i = 0; i < numNodes; i++ )
	{	
		switch(i)
		{
		case 0:
			{
				INode *TempNode = ip->GetSelNode(i);
				Control *Ctr = TempNode->GetTMController()->GetPositionController();
				Ctr->SetValue( N, OrignalObjPos ); 
			}
			break;
		case 1:
			{
				INode *TempNode = ip->GetSelNode(i);
				Control *Ctr = TempNode->GetTMController()->GetPositionController();
				Ctr->SetValue( N, OrignalCollisionPos ); 
			}
			break;
		}
	}
}


void BatchExportASEInCurrentScene()
{
	Interface *ip = GetCOREInterface();
	INode *pRoot =ip->GetRootNode();
	int numAllNodes = pRoot->NumberOfChildren();
	INode *AllNode[200],  *AllCollisionNodes[200];
	TimeValue N = ip->GetTime();
	INT T = 0;
	for (INT i = 0; i < numAllNodes; i++ )
	{
		INode *TNode = pRoot->GetChildNode(i);
		TSTR ObjectNameStr = TNode->GetName();
		INT NumT = ObjectNameStr.length();
		TSTR FinalNameT = ObjectNameStr.Substr( NumT - 3, 3 );
		TSTR DefStr = _T("UCX");
		if ( (TNode->GetObjectRef()->SuperClassID() != HELPER_CLASS_ID) && (DefStr != FinalNameT) )
		{
			AllNode[T] = TNode;
			++T;
		}
	}
	FLOAT DistanceValue[200];
	INode *AllNodes[200];
	for (INT i = 0; i < T; i++ )
	{	
		INT T = 0;
		for (INT m = 0; m < numAllNodes; m++ )
		{
			INode *TNode = pRoot->GetChildNode(m);
			if ( TNode->GetObjectRef()->SuperClassID() != HELPER_CLASS_ID && TNode != AllNode[i] )
			{
				Point3 TempPos;
				Interval Inter;
				AllNodes[T] = TNode;
				DistanceValue[T] = GetDistanceBetweenTwoNodes( GetObjectCenterValue(AllNode[i]), GetObjectCenterValue(TNode) ); 
				++T;
			}
		}
		FLOAT Temp = DistanceValue[0];
		INT S = 0;
		for ( INT b = 1; b < T; b++ )
		{
			if ( DistanceValue[b] < Temp )
			{
				Temp = DistanceValue[b];
				S = b;
			}
		}
		AllCollisionNodes[i] = AllNodes[S];
	}

	for ( INT V = 0; V < T; V++ )
	{
		ip->SelectNode( AllNode[V], 0 );
		ip->SelectNode( AllCollisionNodes[V], 0 );		
		ExportSelection();
		ip->DeSelectNode( AllNode[V] );
		ip->DeSelectNode( AllCollisionNodes[V] );
	}
}

void BatchExportASEFileInSceneByName()
{
	Interface *ip = GetCOREInterface();
	INode *pRoot =ip->GetRootNode();
	int numAllNodes = pRoot->NumberOfChildren();
	INode *AllNode[200],  *AllCollisionNodes[200];
	char WholeNameStr[MAX_PATH];
	TimeValue N = ip->GetTime();
	INT T = 0;
	for (INT i = 0; i < numAllNodes; i++ )
	{
		INode *TNode = pRoot->GetChildNode(i);
		TSTR ObjectNameStr = TNode->GetName();
		INT NumT = ObjectNameStr.length();
		TSTR FinalNameT = ObjectNameStr.Substr( NumT - 3, 3 );
		TSTR DefStr = _T("UCX");
		if ( (TNode->GetObjectRef()->SuperClassID() != HELPER_CLASS_ID) && (DefStr != FinalNameT) )
		{
			AllNode[T] = TNode;
			++T;
		}
	}

	for ( INT g = 0; g < T; g++ )
	{
		sprintf ( WholeNameStr, "%s_UCX", AllNode[g]->GetName() );   
		AllCollisionNodes[g] = ip->GetINodeByName( WholeNameStr );	
	} 

	for ( INT V = 0; V < T; V++ )
	{
		ip->SelectNode( AllNode[V], 0 );
		ip->SelectNode( AllCollisionNodes[V], 0 );		
		ExportSelection();
		ip->DeSelectNode( AllNode[V] );
		ip->DeSelectNode( AllCollisionNodes[V] );
	}
}

void BatchExportASEFileInCurrentSceneByName()
{
	Interface *ip = GetCOREInterface();
	int numAllNodes = ip->GetSelNodeCount();
	INode *AllNode[200],  *AllCollisionNodes[200];
	char WholeNameStr[MAX_PATH];
	TimeValue N = ip->GetTime();
	INT T = 0;
	for (INT i = 0; i < numAllNodes; i++ )
	{
		INode *TNode = ip->GetSelNode( i );
		TSTR ObjectNameStr = TNode->GetName();
		INT NumT = ObjectNameStr.length();
		TSTR FinalNameT = ObjectNameStr.Substr( NumT - 3, 3 );
		TSTR DefStr = _T("UCX");
		if ( (TNode->GetObjectRef()->SuperClassID() != HELPER_CLASS_ID) && (DefStr != FinalNameT) )
		{
			AllNode[T] = TNode;
			++T;
		}
	}
	for (INT i = 0; i < numAllNodes; i++ )
	{
		INode *TNode = ip->GetSelNode( numAllNodes - i - 1 );
		ip->DeSelectNode( TNode );
	}

	for ( INT g = 0; g < T; g++ )
	{
		sprintf ( WholeNameStr, "%s_UCX", AllNode[g]->GetName() );   
		AllCollisionNodes[g] = ip->GetINodeByName( WholeNameStr );	
	} 

	for ( INT V = 0; V < T; V++ )
	{
		ip->SelectNode( AllNode[V], 0 );
		ip->SelectNode( AllCollisionNodes[V], 0 );		
		ExportSelectionToCurrentDir();
		ip->DeSelectNode( AllNode[V] );
		ip->DeSelectNode( AllCollisionNodes[V] );
	}
}

void BatchExportSingleObjectInScene()
{
	Interface *ip = GetCOREInterface();
	INode *pRoot =ip->GetRootNode();
	int numAllNodes = pRoot->NumberOfChildren();
	INode *AllNode[200];
	INT T = 0;
	for (INT i = 0; i < numAllNodes; i++ )
	{
		INode *TNode = pRoot->GetChildNode(i);

		if ( TNode->GetObjectRef()->SuperClassID() != HELPER_CLASS_ID )
		{
			AllNode[T] = TNode;
			++T;
		}
	}

	for ( INT V = 0; V < T; V++ )
	{
		ip->SelectNode( AllNode[V], 1 );
		ExportSelection();
	}
}

class TBMsgHandler : public CUIFrameMsgHandler {
	SaveVerificationGUP *ct;
public:
	TBMsgHandler(SaveVerificationGUP *ctst)	{ this->ct = ctst; }
	int ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
};	

static TBMsgHandler *tbMsgHandler;

int TBMsgHandler::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message) 
	{
		case WM_COMMAND:
			switch (LOWORD(wParam)) 
			{
				case ID_TB_00: 
					{
						BatchExportASEFileInCurrentSceneByName();
					}
					break;
				case ID_TB_0: 
					{
						Interface *TheMaxInterface = GetCOREInterface();
						TCHAR dir[300];
						TCHAR desc[300];
						_tcscpy(desc, _T("Maxfiles source folder"));
						char batchfoldername[MAX_PATH];
						TheMaxInterface->ChooseDirectory( TheMaxInterface->GetMAXHWnd(),_T("Choose Folder"), dir, desc );					
						_tcscpy(batchfoldername, dir); 

						WIN32_FIND_DATA data;
						TSTR search;
						search.printf("%s%s", _T( (char*) batchfoldername ), _T("\\*.max"));
						HANDLE h = FindFirstFile( search.data(), &data);
						BOOL FoundFile = ( h != INVALID_HANDLE_VALUE);		 
						while( FoundFile )
						{		
							TSTR fname;
							fname.printf("%s%s%s",batchfoldername,_T("\\"),_T(data.cFileName)); 
							TheMaxInterface->LoadFromFile( fname );
							BatchExportASEInCurrentScene();
							FoundFile = FindNextFile(h, &data);
						}
					}
					break;
				case ID_TB_1: 
					{
						Interface *TheMaxInterface = GetCOREInterface();
						TCHAR dir[300];
						TCHAR desc[300];
						_tcscpy(desc, _T("Maxfiles source folder"));
						char batchfoldername[MAX_PATH];
						TheMaxInterface->ChooseDirectory( TheMaxInterface->GetMAXHWnd(),_T("Choose Folder"), dir, desc );					
						_tcscpy(batchfoldername, dir); 

						WIN32_FIND_DATA data;
						TSTR search;
						search.printf("%s%s", _T( (char*) batchfoldername ), _T("\\*.max"));
						HANDLE h = FindFirstFile( search.data(), &data);
						BOOL FoundFile = ( h != INVALID_HANDLE_VALUE);		 
						while( FoundFile )
						{		
							TSTR fname;
							fname.printf("%s%s%s",batchfoldername,_T("\\"),_T(data.cFileName)); 
							TheMaxInterface->LoadFromFile( fname );
							BatchExportASEFileInSceneByName();
							FoundFile = FindNextFile(h, &data);
						}
					}
					break;
				case ID_TB_2:
					{
						ChangeObjectAndCollisionName();
						char ModelNameStr[MAX_PATH], DestPath[MAX_PATH];
						Interface *ip = GetCOREInterface();
						_tcscpy( ModelNameStr, ReturnCurrentFileName() );		

						sprintf (DestPath, "d:\\%s.ASE", (char*)ModelNameStr );
						AsciiExp s;			
						s.DoExport( DestPath, NULL, ip, TRUE, 0 ); 
					}
					break;
				case ID_TB_3: 
					{
						 ChangeObjectAndCollisionName();
					}
					break;
				case ID_TB_4: 
					{
						ChangeAllObjectName();
					}
					break;
				case ID_TB_5: 
					{
						ChangeSelectionObjectsName();
					}
					break;
				case ID_TB_6: 
					{
						CreateCollisionObjects();
					}
					break;
				case ID_TB_7: 
					{
                        ProcessSelectionCollisions();
					}
					break;
				case ID_TB_8: 
					{
                        ExportSelection();
					}
					break;
				case ID_TB_9: 
					{
						Interface *TheMaxInterface = GetCOREInterface();
						TCHAR dir[300];
						TCHAR desc[300];
						_tcscpy(desc, _T("Maxfiles source folder"));
						char batchfoldername[MAX_PATH];
						TheMaxInterface->ChooseDirectory( TheMaxInterface->GetMAXHWnd(),_T("Choose Folder"), dir, desc );					
						_tcscpy(batchfoldername, dir); 

						WIN32_FIND_DATA data;
						TSTR search;
						search.printf("%s%s", _T( (char*) batchfoldername ), _T("\\*.max"));
						HANDLE h = FindFirstFile( search.data(), &data);
						BOOL FoundFile = ( h != INVALID_HANDLE_VALUE);		 
						while( FoundFile )
						{		
							TSTR fname;
							fname.printf("%s%s%s",batchfoldername,_T("\\"),_T(data.cFileName)); 
							TheMaxInterface->LoadFromFile( fname );
							BatchExportSingleObjectInScene();
							FoundFile = FindNextFile(h, &data);
						}
					}
					break;
     				case ID_TB_10: 
					{
						char ModelNameStr[MAX_PATH];
						Interface *ip = GetCOREInterface();
						int numNodes = ip->GetSelNodeCount();
						INT T = 0;
						for (INT i = 0; i < numNodes; i++ )
						{
							INode *TempNode = ip->GetSelNode(i);
							sprintf( ModelNameStr, _T("Monster_Extra_0%d"), T );
							(*TempNode).SetName( (char*)ModelNameStr );
							++T;
						}		
						if ( T > 21 )
						{
							//TCHAR TempStr[4096]=TEXT("");
							//MessageBox(NULL, TempStr, TEXT("appDebugMessagef"),MB_OK|MB_SYSTEMMODAL);
							TSTR str;
							str.printf("%s", _T("骨骼数量超过了21根，请删除多余的！"));
							MessageBox(NULL, str, TEXT("错误"), MB_OK | MB_ICONERROR);
						}
						else if ( T < 21 )
						{
							TSTR str;
							str.printf("%s", _T("请将骨骼数量补足21根！"));
							MessageBox(NULL, str, TEXT("错误"), MB_OK | MB_ICONERROR);
						}
					}
					break;
     				case ID_TB_11: 
					{
						ChangeAllObjectNameBySpecific();
					}
					break;

					case ID_TB_12: 
					{
							ExecuteMAXScriptScript(_T("SelectedVerts = #() \n SelectedVerts = $.unwrap_uvw.getSelectedGeomVerts() \n	convertToPoly($) \n polyOp.setVertSelection $ SelectedVerts \n subObjectLevel = 1 "), TRUE);	

/*							Interface *ip = GetCOREInterface();
							INode *TempNode = ip->GetSelNode(0);
							TempNode->mo
							TimeValue t = ip->GetTime();

							BitArray sel;

							ObjectState os  = TempNode->EvalWorldState(t);
							Object *obj = os.obj;
							PolyObject *polyObj = dynamic_cast<PolyObject *>(obj);
							MNMesh *pSelectMesh = &(polyObj->GetMesh());
						    pSelectMesh->getVertexSel(sel);

							ip->CollapseNode(TempNode, TRUE);

							pSelectMesh->setNumVerts(100);
							pSelectMesh->VertexSelect(sel);		*/	


							//BitArray sel = NULL;
							//Object *obj = TempNode->EvalWorldState(t).obj;
							//if (obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0))) 
							//{ 
							//	TriObject *tri = (TriObject *) obj->ConvertToType(t, Class_ID(TRIOBJ_CLASS_ID, 0));
							//	Mesh* mesh = &tri->GetMesh();
							//	sel = mesh->vertSel;
							//	sel.SetSize(mesh->getNumVerts(), TRUE);

							//	ip->CollapseNode(TempNode, TRUE);

							//	ObjectState os  = TempNode->EvalWorldState(t);
							//	Object *obj = os.obj;
							//	PolyObject *polyObj = dynamic_cast<PolyObject *>(os.obj);
							//	//PolyObject *polyObj = (PolyObject *) os->obj->ConvertToType (t, polyObjectClassID);
							//	MNMesh *pSelectMesh = &(polyObj->GetMesh());
							//	pSelectMesh->VertexSelect(sel);								
							//}

					}
					break;

				default: 
					return FALSE;
		}

	case WM_NOTIFY: 
		{
			LPNMHDR hdr = (LPNMHDR)lParam;
			if (hdr->code == TTN_NEEDTEXT) 
			{
				LPTOOLTIPTEXT lpttt;
				lpttt = (LPTOOLTIPTEXT)hdr;            
				switch (lpttt->hdr.idFrom) 
				{
					case ID_TB_00:
						lpttt->lpszText = _T("一键批处理导出所有选中的物体和碰撞体到当前 Max 文件目录 ( 坐标自动归(0,0,0)操作。(命名必须提前命好)___按名称 )");							
						break;
					case ID_TB_0:
						lpttt->lpszText = _T("一键批处理导出同一目录下的所有 MAX 文件中的物体和碰撞体。会自动做规(0,0,0)操作。(命名必须提前命好)___按距离");							
						break;
					case ID_TB_1:
						lpttt->lpszText = _T("一键批处理导出同一目录下的所有 MAX 文件中的物体和碰撞体。会自动做规(0,0,0)操作。(命名必须提前命好)___按名称");		
						break;
					case ID_TB_2:
						lpttt->lpszText = _T("一键导出 ASE 文件到 D: 盘根目录 (包括自动重命名)");
						break;
					case ID_TB_3:
						lpttt->lpszText = _T("命名物体和碰撞体");
						break;
					case ID_TB_4:
						lpttt->lpszText = _T("一键命名场景中所有物体 (以当前MAX文件名前辍为依据) ");
						break;
					case ID_TB_5:
						lpttt->lpszText = _T("一键命名场景中所有选中的物体并自动赋予材质 (命名以当前MAX文件名前辍为依据)");
							break;
					case ID_TB_6:
						lpttt->lpszText = _T("一键生成所有物体的碰撞体 ( 命名, 半透明 )");
						break;
					case ID_TB_7:
						lpttt->lpszText = _T("一键处理所有选中的碰撞体 (透明，命名以最临近的物体命名+_UCX)");
						break;
					case ID_TB_8:
						lpttt->lpszText = _T("一键导出选中的物体和碰撞体到当前 Max 文件目录 ( 坐标自动归(0,0,0) )");
						break;
					case ID_TB_9:
						lpttt->lpszText = _T("一键批处理导出同一目录下的所有 MAX 文件中的所有物体。会自动做规(0,0,0)操作。导出的 ASE 文件名与物体名同名。");	
						break;
					case ID_TB_10:
						lpttt->lpszText = _T("一键批处理命名场景中所有选中的骨骼物体 (以 Monster_Extra_ 为前辍) . 骨骼数量限制为 21 根");	
						break;
					case ID_TB_11:
						lpttt->lpszText = _T("一键批处理命名场景中所有选中的尸体爆炸后的碎块 (以 Explode 为前辍) ");	
						break;
					case ID_TB_12:
						lpttt->lpszText = _T("一键选中 UV 点 (在 Unwrap_UVW 模式下选中的顶点，自动塌陷成 Editable_Poly 后会自动选中) ");	
						break;
				};
			};
			break;
		}
	}
	return FALSE;
}

DWORD SaveVerificationGUP::Start()
{
    ip = GetCOREInterface();
	ICUIFrame* iFrame = GetICUIFrame();
	if (iFrame) {
		// We have the toolbar already, just show it...(EndEditParams() hid it)
		iFrame->Hide(FALSE);
		// If the frame is floating there is no reason to 
		// recalc the layout, but if it's docked we need to do so
		if (!iFrame->IsFloating()) {
			GetCUIFrameMgr()->RecalcLayout(TRUE);
		}
	}
	else {
		HWND hParent = ip->GetMAXHWnd();
		HWND hWnd = CreateCUIFrameWindow(hParent, _T("ShanDa Games--AGE OF DAWN"), 0, 0, 250, 100);
		ICUIFrame* iFrame = ::GetICUIFrame(hWnd);
		iFrame->SetContentType(CUI_TOOLBAR);
		iFrame->SetPosType(CUI_HORIZ_DOCK | CUI_VERT_DOCK | CUI_FLOATABLE | CUI_SM_HANDLES);

		// -- Now create the toolbar window
		HWND hToolbar = CreateWindow(
			CUSTTOOLBARWINDOWCLASS,
			NULL,
			WS_CHILD | WS_VISIBLE,
			0, 0, 2250, 100,
			hWnd,
			NULL,
			hInstance,
			NULL);
		hToolbarWnd = hToolbar;

		// -- Now link the toolbar to the CUI frame
		ICustToolbar *iToolBar = GetICustToolbar(hToolbar);
		iToolBar->LinkToCUIFrame(hWnd, NULL);
		iToolBar->SetBottomBorder(TRUE);
		iToolBar->SetTopBorder(TRUE);

		//hImageTB = ImageList_Create(16, 15, TRUE, 8, 0);
		//HBITMAP hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_TB));
		//HBITMAP hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_TBMASK));
		//ImageList_Add(hImageTB, hBitmap, hMask);
		//DeleteObject(hBitmap);
		//DeleteObject(hMask);
		//iToolBar->SetImage(hImageTB);

		// Install the message handler to process the controls we'll add...
		tbMsgHandler = new TBMsgHandler(this);
		iFrame->InstallMsgHandler(tbMsgHandler);

		//   iToolBar->AddTool(ToolSeparatorItem(3));

		//iToolBar->AddTool(
		//	ToolButtonItem(CTB_PUSHBUTTON,  0,0,2,2,  16,15,
		//	TB_BUT_WIDTH,TB_BUT_HEIGHT,ID_TB_0));  

		//iToolBar->AddTool(
		//	ToolButtonItem(CTB_PUSHBUTTON,  1,1,3,3,  16,15,
		//	TB_BUT_WIDTH,TB_BUT_HEIGHT,ID_TB_1));  

	 //  iToolBar->AddTool(ToolSeparatorItem(6));

		//iToolBar->AddTool(
		//	ToolButtonItem(CTB_PUSHBUTTON,  4,5,6,7,  16,15,
		//	TB_BUT_WIDTH,TB_BUT_HEIGHT,ID_TB_2));  

		MaxBmpFileIcon* pIcon = new MaxBmpFileIcon(_T("AnimLayerToolbar"), 1);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_00));

		iToolBar->AddTool(ToolSeparatorItem(3));
	    	pIcon = new MaxBmpFileIcon(_T("brush_preset_manager"), 1);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_0));

		iToolBar->AddTool(ToolSeparatorItem(3));
		pIcon = new MaxBmpFileIcon(_T("brush_preset_manager"), 2);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_1));

		iToolBar->AddTool(ToolSeparatorItem(6));
		pIcon = new MaxBmpFileIcon(_T("brush_preset_manager"), 3);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_2));

		iToolBar->AddTool(ToolSeparatorItem(8));
		pIcon = new MaxBmpFileIcon(_T("brush_preset_manager"), 4);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_3));

		iToolBar->AddTool(ToolSeparatorItem(8));
		pIcon = new MaxBmpFileIcon(_T("brush_preset_manager"), 5);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_4));

		iToolBar->AddTool(ToolSeparatorItem(8));
		pIcon = new MaxBmpFileIcon(_T("AnimLayerToolbar"), 6);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_5));

		iToolBar->AddTool(ToolSeparatorItem(8));
		pIcon = new MaxBmpFileIcon(_T("AnimLayerToolbar"), 7);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_6));

		iToolBar->AddTool(ToolSeparatorItem(8));
		pIcon = new MaxBmpFileIcon(_T("AnimLayerToolbar"), 8);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_7));

		iToolBar->AddTool(ToolSeparatorItem(8));
		pIcon = new MaxBmpFileIcon(_T("AnimLayerToolbar"), 9);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_8));

		iToolBar->AddTool(ToolSeparatorItem(8));
		pIcon = new MaxBmpFileIcon(_T("brush_preset_manager"), 10);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_9));

		iToolBar->AddTool(ToolSeparatorItem(5));
		pIcon = new MaxBmpFileIcon(_T("brush_preset_manager"), 5);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_10));

		iToolBar->AddTool(ToolSeparatorItem(5));
		pIcon = new MaxBmpFileIcon(_T("brush_preset_manager"), 2);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_11));

		iToolBar->AddTool(ToolSeparatorItem(5));
		pIcon = new MaxBmpFileIcon(_T("brush_preset_manager"), 7);
		iToolBar->AddTool(TBITEM(CTB_PUSHBUTTON, pIcon, ID_TB_12));

	    //iToolBar->AddTool(ToolSeparatorItem(8));
		// Add a separator
		//iToolBar->AddTool(ToolSeparatorItem(8));

		// Add a keyboard macro command.  In this case the Time Configuration dialog
		// is presented as an example.  In order to get the proper command ID to use
		// we must search through the names in the MAX UI action table and find
		// a match.  The list of names can be reviewed in the MAX UI when setting up
		// a keyboard shortcut.
		//TSTR findName = _T("Time Configuration");
		//ActionTable *pTable = ip->GetActionManager()->FindTable(kActionMainUI);
		//assert(pTable);
		//for(int i = 0; i < pTable->Count(); i++) {
		//	ActionItem* pAction = (*pTable)[i];
		//	TSTR desc;
		//	pAction->GetDescriptionText(desc);
		//	if (_tcscmp(findName.data(), desc.data()) == 0) {
		//		int cmdID = pAction->GetId();
		//		MacroButtonData md1(kActionMainUI, cmdID, _T("KBD Cmd"), _T("Key Macro Tooltip"));
		//		iToolBar->AddTool(TBMACRO(&md1));
		//		break;
		//	}
		//}

		// Add a macro script button to the toolbar.  This is a custom macro script
		// which is loaded, then located, then added.
		//TSTR ui = ip->GetDir(APP_UI_DIR);
		//TSTR path = ui + _T("\\CUITEST.MCR");
		//GetMacroScriptDir().LoadMacroScripts(path.data(), FALSE);
		//// Find it based on the category and name defined in the CUITest.mcr file.
		//MacroEntry *me = GetMacroScriptDir().FindMacro(_T("CUITestCategory"), _T("CUITestName"));
		//if (me) {
		//	MacroID mID = me->GetID();
		//	MacroButtonData md2(mID, _T("Macro Scr"), _T("Macro Script Tooltip"));
		//	iToolBar->AddTool(TBMACRO(&md2));
		//}

		// This button is processed by our message handler (ID_TB_2)

		// -- Set the initial floating position
		SIZE sz; RECT rect;
		iToolBar->GetFloatingCUIFrameSize(&sz);
		rect.top = 200; rect.left = 200;
		rect.right = rect.left+sz.cx; rect.bottom = rect.top+sz.cy;
		GetCUIFrameMgr()->FloatCUIWindow(hWnd, &rect);
		MoveWindow(hWnd, rect.left, rect.right, sz.cx, sz.cy, TRUE);

		// We are done, release the toolbar and frame handles
		ReleaseICustToolbar(iToolBar);
		iToolBar = NULL;
		ReleaseICUIFrame(iFrame);

		ICUIFrame* pFrame = theCUITest.GetICUIFrame();
		// Don't do anything of it's on the tab panel
		if (pFrame && !pFrame->GetTabbedToolbar()) {
			if (pFrame->IsFloating()) {
				GetCUIFrameMgr()->DockCUIWindow(GetParent(pFrame->GetContentHandle()), CUI_LEFT_DOCK, NULL);
				GetCUIFrameMgr()->RecalcLayout(TRUE);
			}
			else {
				GetCUIFrameMgr()->FloatCUIWindow(GetParent(pFrame->GetContentHandle()), NULL);
				GetCUIFrameMgr()->RecalcLayout(TRUE);
			}
		}
	}
     return TRUE;
	//return GUPRESULT_KEEP;
}

void SaveVerificationGUP::Stop()
{
	// unregister the callback.
	UnRegisterNotification(PostSaveCallback, this, NOTIFY_FILE_POST_SAVE);
}

DWORD_PTR SaveVerificationGUP::Control(DWORD parameter)
{
	return 0;
}

void SaveVerificationGUP::DeleteThis()
{
	delete this;
}

// This method gets called when the user saves a file.
void SaveVerificationGUP::PostSaveCallback(void* param, NotifyInfo* info)
{
	SaveVerificationGUP* pThis = (SaveVerificationGUP*)param;
	pThis->ValidateFile((TCHAR*)info->callParam);
}	

void SaveVerificationGUP::ValidateFile(const TSTR& filename)
{
	TSTR tmpFileName = filename;
	if (tmpFileName.isNull()) 
	{
		tmpFileName = Max()->GetCurFilePath();
	}
	if (!tmpFileName.isNull())
	{
		// Does the path exist?
		TCHAR drive[_MAX_DRIVE], dir[_MAX_DIR], fullpath[_MAX_PATH];
		_splitpath(tmpFileName, drive, dir, NULL, NULL);
		_tmakepath(fullpath, drive, dir, NULL, NULL);
		if (!DoesFileExist(fullpath))
		{
			TSTR str;
			str.printf(GetStrings(IDS_ERROR_PATH_MISSING), fullpath);

			// The file was possibly corrupt! Prompt the user to resave.
			MessageBox(MaxWnd(), str, GetStrings(IDS_ATTENTION), MB_OK | MB_ICONERROR);
		}
		// Validate that the file is a valid STG file and that the proper streams are present.
		else if (!ValidateStreams(tmpFileName))
		{
			TSTR str;
			str.printf(GetStrings(IDS_ERROR_FILE_CORRUPT), tmpFileName);

			// The file was possibly corrupt! Prompt the user to resave.
			if (MessageBox(MaxWnd(), str, GetStrings(IDS_ATTENTION), MB_YESNO | MB_ICONERROR) == IDYES)
			{
				Max()->FileSaveAs();
			}
		}
	}
}

bool SaveVerificationGUP::ValidateStreams(const TSTR& filename)
{
	bool		validFile = true;
	HRESULT		res;
	IStorage*	pIStorage = NULL;

	// This opens the file as an OLE structured storage file.
	Interface11* pInterface11 = static_cast<Interface11*>(Max()->GetInterface(Interface11::kInterface11InterfaceID));
	DbgAssert(pInterface11);
	if (!pInterface11)
		return validFile;

	res = pInterface11->OpenMAXStorageFile(WStr(filename.data()), &pIStorage);
	if (res == S_OK)
	{
		if (!HasStream(pIStorage, "AutodeskDataPackage"))
		{
			// Verify that the Scene stream is present.
			if (!HasStream(pIStorage, "Scene"))
				validFile = false;

			// Verify that the Config stream is present.
			if (!HasStream(pIStorage, "Config"))
				validFile = false;

			// Verify that the ClassData stream is present.
			if (!HasStream(pIStorage, "ClassData"))
				validFile = false;

			// Verify that the DllDirectory stream is present.
			if (!HasStream(pIStorage, "DllDirectory"))
				validFile = false;
		}

		// It's twelve o'clock and all is well...
		pIStorage->Release();
		pIStorage = NULL;
	}
	else
	{
		validFile = false;
	}

	return validFile;
}

bool SaveVerificationGUP::HasStream(IStorage* storage, TSTR stream)
{
	bool		hasStream;
	IStream*	pIStream = NULL;

	// Verify that the given stream is present.
	HRESULT res = storage->OpenStream (WStr(stream), NULL,  STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pIStream);
	if (res == S_OK)  
	{
		pIStream->Release();
		pIStream = NULL;
		hasStream = true;
	}
	else {
		hasStream = false;
	}

	return hasStream;
}

ICUIFrame* SaveVerificationGUP::GetICUIFrame()
{
	HWND hFrameWnd = GetParent(hToolbarWnd);
	return  ::GetICUIFrame(hFrameWnd);
}