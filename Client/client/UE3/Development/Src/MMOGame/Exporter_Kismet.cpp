#include "stdafx.h"
#include "Exporter_Kismet.h"

#if !SHIPPING_PC_GAME


Exporter_Kismet::Exporter_Kismet(void)
	: KismetHeader(0)
{
}
//------------------------------------------------------------------------
Exporter_Kismet::~Exporter_Kismet(void)
{
}
//------------------------------------------------------------------------
void Exporter_Kismet::PrePorcess(INT& GlobalAutoID)
{
	//TArray<USequenceObject*> ActionNodes;
	//// 对变量统一重新编号

	//for(INT i = 0; i < GWorld->Levels.Num(); ++i)
	//{
	//	USequence* seq = GWorld->GetGameSequence(GWorld->Levels(i));
	//	if(seq == NULL)
	//	{
	//		continue;
	//	}

	//	// 每个sequence的节点ID唯一
	//	INT id = 1;
	//	for(INT j = 0; j < seq->SequenceObjects.Num(); ++j)
	//	{
	//		USequenceObject* seqObj = seq->SequenceObjects(j);
	//		if(seqObj->IsA(USequenceVariable::StaticClass()))
	//		{
	//			if( (seqObj->GetKismetObjectServerType() >= kotSequenceVariableInt)
	//				&& (seqObj->GetKismetObjectServerType() <= kotSequenceVariableObject))
	//			{
	//				USeqVar_Object* objVar = Cast<USeqVar_Object>(seqObj);
	//				if(objVar)
	//				{
	//					// 只导出服务器要的变量
	//					if(objVar->ObjValue && objVar->ObjValue->GetObjectServerType() != -1)
	//					{
	//						SeqVars.AddItem(Cast<USequenceVariable>(seqObj));
	//					}
	//				}
	//				else
	//				{
	//					SeqVars.AddItem(Cast<USequenceVariable>(seqObj));
	//				}
	//			}
	//		}
	//		else if(seqObj->IsServerKismetObject())
	//		{
	//			ActionNodes.AddItem(seqObj);
	//			seqObj->GenAutoID(id);
	//		}
	//	}
	//}

	//
	////for(INT i = 0; i < ActionNodes.Num(); ++i)
	////{
	////	USequenceObject* seq = ActionNodes(i);
	////	seq->GenAutoID(id);
	////}
	////

	//INT id = 1;
	//for(INT i = 0; i < SeqVars.Num(); ++i)
	//{
	//	USequenceVariable* seq = SeqVars(i);
	//	seq->GenAutoID(id);
	//}
}
//------------------------------------------------------------------------
void Exporter_Kismet::WriteHeader( FBufferArchive& ar)
{
	//// 再写到文件
	//SCENE_FILE_BLOCK_HEADER blkHdr = {0};
	//blkHdr.eBlockType = sbtKismet;
	//blkHdr.nBlockSize = 0;
	//blkHdr.nBlockOffset = sizeof(SCENE_FILE_BLOCK_HEADER);
	//
	//ar.ByteOrderSerialize(&blkHdr, sizeof(SCENE_FILE_BLOCK_HEADER));

	//// 先存储位置，后面再修改参数
	//KismetHeader = (SCENE_FILE_BLOCK_HEADER*)(ar.GetData() + ar.Tell() - sizeof(SCENE_FILE_BLOCK_HEADER));
}
//------------------------------------------------------------------------
void Exporter_Kismet::WriteData( FBufferArchive& ar )
{
	//FBufferArchive memAr;

	//// 先导出变量到一个整表
	//INT val = (INT)kotSequenceVariableTable;	
	//memAr << val;

	//val = SeqVars.Num();
	//memAr << val;

	////if( SeqVars.Num() <= 0 )
	////	return;
	//for(INT i = 0; i < SeqVars.Num(); ++i)
	//{
	//	USequenceVariable* seq = SeqVars(i);

	//	seq->ExportServerData(memAr);
	//}

	//// 再导其它对象
	//for(INT i = 0; i < GWorld->Levels.Num(); ++i)
	//{
	//	USequence* seq = GWorld->GetGameSequence(GWorld->Levels(i));
	//	if( seq != NULL )
	//		seq->ExportServerData(memAr);
	//}

	//// 修改文件头
	//KismetHeader->nBlockSize = memAr.TotalSize();
	//KismetHeader->nBlockOffset = ar.Tell();

	//ar.ByteOrderSerialize(memAr.GetData(), memAr.TotalSize());
}

#endif