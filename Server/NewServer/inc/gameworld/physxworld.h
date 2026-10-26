// SHANDA GAMES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Shanda Games and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1999-2010 Shanda Games.
//      All Rights Reserved.
//
// Shanda Games Limited, Shanghai, China, 201203
// http://www.shandagames.com

#ifndef _PHYSXWORLD_H_
#define _PHYSXWORLD_H_

#include "physxscene.h"
#include "string_def.h"

#include "object_pool.h"
#include "scene_data.h"

class CPhysxWorld
{
public:
    CPhysxWorld();
    virtual ~CPhysxWorld();

    static CPhysxWorld& GetInstance(VOID);
public:
    BOOL Init(UINT32 nSceneCount);
    BOOL UnInit(VOID);

    CPhysxScene* CreatePhysxScene(INT32 nSceneID, const TCHAR* pszFileName);
    NxScene* CreateScenProp(const TCHAR* pszPath, const TCHAR* pszFileName);
    BOOL DestroyPhysxScene(CPhysxScene* poPhysxScene);
private:
    BOOL _DestroyScenProp(NxScene* poPhysxSceneProp);

    BOOL _CreatePhysxActor(EPhysxDataGroup eGroup, NxScene* poSceneProp, const TCHAR* pszPath, CSDXMLNode& oActorNode);

    NxVec3 _ConvertNxPos(const TCHAR* pszPos);
private:
    struct CTraversePhysxData
    {
        NxScene** m_poSceneProp;
        BOOL operator()(SCENE_DATA* pstSceneData);
    }m_TraversePhysxData;

    NxPhysicsSDK* m_poNxSDK;

    NxScene* m_poSceneProp[MAX_PHYSX_SCENE_COUNT];
    CObjectPool<CPhysxScene>    m_PhysxScenePool;
};

#endif  //_PHYSXWORLD_H_