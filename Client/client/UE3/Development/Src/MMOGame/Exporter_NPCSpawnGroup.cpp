#include "stdafx.h"
#include "Exporter_NPCSpawnGroup.h"
#include "MMOGameClasses.h"

#if !SHIPPING_PC_GAME

Exporter_NPCSpawnGroup::Exporter_NPCSpawnGroup(void)
{
	//sbtNpcSpawnPoint,
	//sbtNpcSpawnGroup,
}
//------------------------------------------------------------------------
void Exporter_NPCSpawnGroup::CleanUp()
{
	SpawnPointList.clear();
	SpawnGroupList.clear();
}
//------------------------------------------------------------------------
Exporter_NPCSpawnGroup::~Exporter_NPCSpawnGroup(void)
{
	CleanUp();
}
//------------------------------------------------------------------------
void Exporter_NPCSpawnGroup::PrePorcess(INT& GlobalAutoID)
{
	////------------------------------------------------------------------------
	//// 分类对象
	////------------------------------------------------------------------------
	//for (INT i = 0; i < GWorld->Levels.Num(); ++i)
	//{
	//	ULevel* level = GWorld->Levels(i);
	//	for (INT j = 0; j < level->Actors.Num(); ++j)
	//	{
	//		AActor* actor = level->Actors(j);
	//		if(actor)
	//		{				
	//			if(actor->IsA(AMMONPCSpawnGroup::StaticClass()))
	//			{
	//				SpawnGroupList.push_back( Cast<AMMONPCSpawnGroup >(actor) );
	//			}
	//			else if(actor->IsA(ANPCSpawnPoint::StaticClass()))
	//			{
	//				SpawnPointList.push_back( Cast<ANPCSpawnPoint >(actor) );
	//			}
	//		}
	//	}
	//}

	//INT autoID = 0;

	//// 自动编号
	//for( vector< AMMONPCSpawnGroup * >::iterator it = SpawnGroupList.begin(); it != SpawnGroupList.end() ; ++it)
	//{
	//	AMMONPCSpawnGroup* SpawnGrp = *it;
	//	SpawnGrp->AutoServerID = autoID;
	//	++autoID;
	//}

	//IniData();

}
//------------------------------------------------------------------------
void Exporter_NPCSpawnGroup::IniData()
{
	//NPC_SPAWN_POINT_HEADER  *spntHdr = new NPC_SPAWN_POINT_HEADER;
	//NPC_SPAWN_GROUP_HEADER *grpHdr  = new NPC_SPAWN_GROUP_HEADER;

	//// =========================导出SpawnGroupList==================
	//grpHdr->nGroupCount = SpawnGroupList.size();
	////定长，统一申请
	//NPC_SPAWN_GROUP_DATA *grpList = new NPC_SPAWN_GROUP_DATA[ grpHdr->nGroupCount ];
	//memGroupAr.ByteOrderSerialize(grpHdr, sizeof(NPC_SPAWN_GROUP_HEADER));
	//for (INT i = 0; i < grpHdr->nGroupCount ; ++i)
	//{
	//	//AutoServerID 暂时不用
	//	grpList[i].nGroupID = SpawnGroupList[i]->AutoServerID;//NPCSpawnGroupId;
	//	if(SpawnGroupList[i]->MaxConcurrentPoint > SpawnGroupList[i]->NPCSpawnPoints.Num())
	//		grpList[i].nMaxConcurrentPoint = SpawnGroupList[i]->NPCSpawnPoints.Num();
	//	else
	//		grpList[i].nMaxConcurrentPoint = SpawnGroupList[i]->MaxConcurrentPoint;
	//	grpList[i].IsAutoSpawn = SpawnGroupList[i]->IsAutoSpawn;
	//	grpList[i].IsAutoReSpawn = SpawnGroupList[i]->IsAutoReSpawn;
	//	//先导出Grp的原因在这里，对SpawnPoint的Group完成赋值
	//	for( INT j = 0; j < SpawnGroupList[i]->NPCSpawnPoints.Num(); ++j )
	//	{
	//		if(!SpawnGroupList[i])
	//		{
	//			GWarn->MapCheck_Add(MCTYPE_ERROR, 0, 
	//				*FString::Printf(TEXT("SpawnGroupList[%d] is empty!"), i),
	//				NULL, MCGROUP_DEFAULT);
	//		}
	//		else if(!SpawnGroupList[i]->NPCSpawnPoints(j))
	//		{
	//			GWarn->MapCheck_Add(MCTYPE_ERROR, SpawnGroupList[i], 
	//				*FString::Printf(TEXT("SpawnPoints is empty:%s"), *SpawnGroupList[i]->GetName()),
	//				NULL, MCGROUP_DEFAULT);
	//		}
	//		else
	//		{
	//			SpawnGroupList[i]->NPCSpawnPoints( j )->GroupID = SpawnGroupList[i]->AutoServerID;
	//		}
	//	}
	//	memGroupAr.ByteOrderSerialize(&grpList[i], sizeof(NPC_SPAWN_GROUP_DATA));
	//}

	//// =========================导出ANPCSpawnPoint==================
	//spntHdr->nPointCount = SpawnPointList.size();
	////这里是变长 所以需要预先申请好内存
	//int SpawnPointDataSize= spntHdr->nPointCount*sizeof( NPC_SPAWN_POINT_DATA ) ;
	//for (INT i = 0; i < spntHdr->nPointCount ; ++i)
	//{
	//	SpawnPointDataSize+=SpawnPointList[i]->NPCTemplateList.Num() * sizeof( NPC_SPAWN_DATA );
	//}
	//char* pMem=new char[ SpawnPointDataSize ]; 
	//char* pSpawnPointData=pMem;
	//NPC_SPAWN_POINT_DATA *spntData;
	//NPC_SPAWN_DATA		*spntNpcData;
	//memPointAr.ByteOrderSerialize(spntHdr, sizeof(NPC_SPAWN_POINT_HEADER));
	//for (INT i = 0; i < spntHdr->nPointCount ; ++i)
	//{
	//	spntData = (NPC_SPAWN_POINT_DATA*)pSpawnPointData;
	//	pSpawnPointData += sizeof(NPC_SPAWN_POINT_DATA);
	//	spntData->nX = SpawnPointList[i]->Location.X * POINT_PER_CM;
	//	spntData->nY = SpawnPointList[i]->Location.Y * POINT_PER_CM;
	//	spntData->nZ = SpawnPointList[i]->Location.Z * POINT_PER_CM;
	//	spntData->shDirection = (UINT16)(SpawnPointList[i]->Rotation.Yaw);
	//	spntData->nGroupID = SpawnPointList[i]->GroupID; 
	//	spntData->nNpcCount = SpawnPointList[i]->NPCTemplateList.Num();
	//	//这里也可以用流 << 直接输入，但这样表现相对直观 而且便于调试 
	//	memPointAr.ByteOrderSerialize(spntData, sizeof(NPC_SPAWN_POINT_DATA));
	//	//SpawnNPCTableOffest 开始于所有的NPCSpawnPoint数据之后
	//	for( INT j = 0; j < spntData -> nNpcCount  ; ++j )
	//	{
	//		spntNpcData = (NPC_SPAWN_DATA*)pSpawnPointData;
	//		pSpawnPointData += sizeof(NPC_SPAWN_DATA);
	//		//配多了 可能配错 出现空值
	//		if(!SpawnPointList[i]->NPCTemplateList(j).NPCTemplateArchi )
	//		{
	//			spntNpcData->nTemplateID = 0 ;
	//			spntNpcData->nWeight = 0 ;
	//			GWarn->MapCheck_Add(MCTYPE_ERROR, SpawnPointList[i], 
	//				*FString::Printf(TEXT("SpawnPointList[%d] NPCTemplateList [%d]is empty!"), i,j ),
	//				NULL, MCGROUP_DEFAULT);
	//		}
	//		else
	//		{
	//			spntNpcData->nTemplateID = SpawnPointList[i]->NPCTemplateList(j).NPCTemplateArchi->NPCID;
	//			spntNpcData->nWeight = SpawnPointList[i]->NPCTemplateList(j).Weight;
	//		}
	//		memPointAr.ByteOrderSerialize(spntNpcData, sizeof(NPC_SPAWN_DATA));
	//	}
	//}

	//SAFEDELETE( spntHdr );
	//SAFEDELETE( grpHdr );
	//SAFEDELETEARRAY( grpList );
	//spntData=NULL;
	//spntNpcData=NULL;
	//SAFEDELETE( pMem );
}
//------------------------------------------------------------------------
void Exporter_NPCSpawnGroup::WriteHeader( FBufferArchive& ar)
{
	////Serialize
	////难看，将就下
	//SCENE_FILE_BLOCK_HEADER blkHdrs[2];
	//blkHdrs[0].eBlockType= sbtNpcSpawnPoint;
	//blkHdrs[0].nBlockSize = 0;
	//blkHdrs[0].nBlockOffset = sizeof(SCENE_FILE_BLOCK_HEADER);

	//blkHdrs[1].eBlockType=sbtNpcSpawnGroup;
	//blkHdrs[1].nBlockSize = 0;
	//blkHdrs[1].nBlockOffset = sizeof(SCENE_FILE_BLOCK_HEADER);

	//ar.ByteOrderSerialize(&blkHdrs[0], sizeof(SCENE_FILE_BLOCK_HEADER) );
	//// 先存储位置，后面再修改参数
	//arBlkHdrs[0] = (SCENE_FILE_BLOCK_HEADER*)( ar.GetData() + ar.Tell() - sizeof(SCENE_FILE_BLOCK_HEADER) );

	//ar.ByteOrderSerialize(&blkHdrs[1], sizeof(SCENE_FILE_BLOCK_HEADER));
	//arBlkHdrs[1] = (SCENE_FILE_BLOCK_HEADER*)( ar.GetData() + ar.Tell() - sizeof(SCENE_FILE_BLOCK_HEADER) );
}
//------------------------------------------------------------------------
void Exporter_NPCSpawnGroup::WriteData( FBufferArchive& ar )
{
	//// =====================SpawnPointList写到内存=====================
	//arBlkHdrs[0]->nBlockSize = memPointAr.TotalSize();
	////计算SpawnPointList  nBlockOffset 注：Offest 是指与 SCENE_FILE_HEADER的Global Offset
	//arBlkHdrs[0]->nBlockOffset = ar.Tell();
	////Srialize时很可能会ReAllocate 地址会发生改变，watch arBlkHdrs[0] 会看到异常
	//ar.ByteOrderSerialize(memPointAr.GetData(), memPointAr.TotalSize());

	////===================== SpawnGroup写到内存=======================
	//arBlkHdrs[1]->nBlockSize = memGroupAr.TotalSize();
	//arBlkHdrs[1]->nBlockOffset = ar.Tell();
	//ar.ByteOrderSerialize(memGroupAr.GetData(), memGroupAr.TotalSize());
}

#endif