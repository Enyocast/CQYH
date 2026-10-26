
#include "stdafx.h"
#include "ExportServerData.h"
#include "MMOFacade.h"

#if WITH_EDITOR

FString NPCTemplateSrcPath = TEXT("..\\..\\MMOGame\\Content\\MMOContent\\07_NPC");
FString NPCTemplateDestPath = TEXT("..\\..\\MMOGame\\Content\\MMOContent\\08_NPCTemplate");
FString QuestTemplatePath = TEXT("..\\..\\MMOGame\\Content\\MMOContent\\07_Quest");

void ConvertNPC(const FString& SrcPkgPath);
void ConvertNPC(ANPC* OldTemplate, UNPCTemplate* NewTemplate);

void RecuriveFindDirs(TArray<FString>& OutPkgs, const FString& FindDir);
void RecuriveFindPkgs(TArray<FString>& OutPkgs, const FString& FindDir);
void ChangeQuestNPCTemplateRef();

UNPCTemplate* FindNewNPCTemplate(ANPC* OldNPC);

FFilename GetDestNPCTemplatePackageName(const FString& SrcPkgName)
{
	FString DestPkg = NPCTemplateDestPath + SrcPkgName.Right(SrcPkgName.Len() - NPCTemplateSrcPath.Len());
	FFilename DestPkgName(DestPkg);

 	FString DestRealName = DestPkgName.GetPath() + TEXT("\\") + DestPkgName.GetBaseFilename() + TEXT("_New.") + DestPkgName.GetExtension();
 	return FFilename(DestRealName);
}

void ConvertToNewNPCTemplate()
{
	NPCTemplateSrcPath = GFileManager->ConvertToAbsolutePath(*NPCTemplateSrcPath);
	NPCTemplateDestPath = GFileManager->ConvertToAbsolutePath(*NPCTemplateDestPath);

	TArray<FString> SrcPackages;
	RecuriveFindDirs(SrcPackages, NPCTemplateSrcPath);

	for (INT i = 0; i < SrcPackages.Num(); ++i)
	{
		const FString& SrcPkg = SrcPackages(i);
		ConvertNPC(SrcPkg);
	}

	ChangeQuestNPCTemplateRef();
}

void RecuriveFindDirs(TArray<FString>& OutPkgs, const FString& FindDir)
{
	TArray<FString> SrcDirs;
	GFileManager->FindFiles(SrcDirs, *(FindDir + TEXT("\\*.*")), FALSE, TRUE);

	for (INT i = 0; i < SrcDirs.Num(); ++i)
	{
		const FString& SrcDir = SrcDirs(i);		
		FString SrcSubDir = FindDir + TEXT("\\") + SrcDir;
		RecuriveFindPkgs(OutPkgs, SrcSubDir);
	}
}

void RecuriveFindPkgs(TArray<FString>& OutPkgs, const FString& FindDir)
{
	TArray<FString> SrcPackages;
	GFileManager->FindFiles(SrcPackages, *(FindDir + TEXT("\\*.upk")), TRUE, FALSE);

	for(INT i = 0; i < SrcPackages.Num(); ++i)
	{
		OutPkgs.AddItem(FindDir + TEXT("\\") + SrcPackages(i));
	}

	RecuriveFindDirs(OutPkgs, FindDir);
}

extern UBOOL SavePackageHelper(UPackage* Package, FString Filename,  EObjectFlags KeepObjectFlags = RF_Standalone, FOutputDevice* ErrorDevice=GWarn, ULinkerLoad* LinkerToConformAgainst=NULL);

void ConvertNPC(const FString& SrcPkgPath)
{
	FFilename SrcPkgName(SrcPkgPath);
	FFilename DestPkgName = GetDestNPCTemplatePackageName(SrcPkgPath);
	GFileManager->MakeDirectory(*DestPkgName.GetPath(), TRUE);
	UPackage* SrcUpk = UObject::LoadPackage(NULL, *SrcPkgName.GetBaseFilename(), LOAD_NoWarn | LOAD_Quiet);
	UPackage* DestUpk = UObject::CreatePackage(NULL, *DestPkgName.GetBaseFilename());

	if(!SrcUpk->IsFullyLoaded())
	{
		SrcUpk->FullyLoad();
	}

	for (INT j = 0; j < SrcUpk->GetNetObjectCount(0); ++j)
	{
		ANPC* item = Cast<ANPC>(SrcUpk->GetNetObjectAtIndex(j));
		if(item)
		{
			FString SrcObjName = item->GetName();
			UNPCTemplate* newNpc = ConstructObject<UNPCTemplate>(UNPCTemplate::StaticClass(),
				DestUpk, *SrcObjName, item->GetFlags());
			ConvertNPC(item, newNpc);
		}
	}

	SavePackageHelper(DestUpk, DestPkgName);
}


void ConvertNPC(ANPC* OldTemplate, UNPCTemplate* NewTemplate)
{
#define CVT_NPC(prop) NewTemplate->prop = OldTemplate->prop;

	NewTemplate->TemplateID = OldTemplate->NPCID;

	NewTemplate->NameID = OldTemplate->NameID.ToString();
	//CVT_NPC(DisplayName);
	CVT_NPC(Radius);
	CVT_NPC(ServerSpawnTime);
	CVT_NPC(ReviveTime);
	CVT_NPC(CorpseTime);
	//CVT_NPC(RespawnTime);
	//CVT_NPC(AIData);
	CVT_NPC(ForceID);
	CVT_NPC(NPCScriptName);
	CVT_NPC(ShopID);
	CVT_NPC(ImmunePassiveMove);
	CVT_NPC(Invincible);
	CVT_NPC(AllwaysRun);
	CVT_NPC(Pattern);
	CVT_NPC(SpeciesType);
	NewTemplate->AvatarTemplate = OldTemplate->UseingAvatar;
	CVT_NPC(DefaultDialogText);
	CVT_NPC(IdentityName);
	CVT_NPC(IdentityIcon);
	CVT_NPC(NPCIcon);
	CVT_NPC(HUDDisplayIcon);
	CVT_NPC(SpawnProcList);
	CVT_NPC(TeleportProcList);
	CVT_NPC(RebirthProcList);
	CVT_NPC(ActionProcList);
	CVT_NPC(TickProcList);

	CVT_NPC(ActorName);
	CVT_NPC(PawnAnimInfo);
}

void ChangeQuestNPCTemplateRef()
{
#if 0
	TArray<FString> QuestPkgs;
	
	QuestTemplatePath = GFileManager->ConvertToAbsolutePath(*QuestTemplatePath);

	appFindFilesInDirectory(QuestPkgs, *QuestTemplatePath, TRUE, FALSE);
	for (INT i = 0; i < QuestPkgs.Num(); ++i)
	{
		UPackage* Package = UObject::LoadPackage( NULL, *QuestPkgs(i), LOAD_Verify );
		if( !Package )
		{
			warnf( NAME_Error, TEXT("Unable to load %s"), *QuestPkgs(i) );
			continue;
		}

		if(!Package->IsFullyLoaded())
		{
			Package->FullyLoad();
		}

		for (INT j = 0; j < Package->GetNetObjectCount(0); ++j)
		{
			UQuest* item = Cast<UQuest>(Package->GetNetObjectAtIndex(j));
			if(item)
			{								
				if(item->StartNPC)
				{
					item->StartNPCNew = FindNewNPCTemplate(item->StartNPC);
				}

				if(item->FinishNpc)
				{
					item->FinishNpcNew = FindNewNPCTemplate(item->FinishNpc);
				}

				for (INT k = 0; k < item->CheckKillNpc.Num(); ++k)
				{
					if(item->CheckKillNpc(k).CheckKillNpc)
					{
						item->CheckKillNpc(k).CheckKillNpcNew = FindNewNPCTemplate(item->CheckKillNpc(k).CheckKillNpc);
					}
				}
			}
		}
	}
#endif
}
//------------------------------------------------------------------------
UNPCTemplate* FindNewNPCTemplate(ANPC* OldNPC)
{
	FString oldName = OldNPC->GetPathName();
	
	FString newName;
	INT Pos = oldName.InStr(TEXT("."));
	if ( Pos != INDEX_NONE )
	{
		newName = oldName.Left(Pos) + TEXT("_New") + oldName.Right(oldName.Len() - Pos);
	}

	return (UNPCTemplate*)UObject::StaticLoadObject( UNPCTemplate::StaticClass(), NULL,
		*newName, NULL, LOAD_None, NULL );
}
//------------------------------------------------------------------------

void FixNPCTemplateRef()
{
	if(!GWorld)
	{
		return;
	}

	TArray<FString> DirArray;
	GConfig->GetArray( TEXT("NPCTemplates"), TEXT("TemplateDir"), DirArray, GGameIni );

	MMO::FormatTempleteDataLoadingDir(DirArray);

	for (INT k = 0; k < DirArray.Num(); ++k)
	{
		const FString& cfgDir = DirArray(k);

		TArray<FString> pkgs;
		appFindFilesInDirectory(pkgs, *cfgDir, TRUE, FALSE);
		for (INT i = 0; i < pkgs.Num(); ++i)
		{
			UPackage* Package = UObject::LoadPackage( NULL, *pkgs(i), LOAD_Verify );
			if( !Package )
			{
				warnf( NAME_Error, TEXT("Unable to load %s"), *pkgs(i) );
				continue;;
			}

			if(!Package->IsFullyLoaded())
			{
				Package->FullyLoad();
			}
		}
	}

// 	for(TObjectIterator<ANPCNewSpawnPoint> It; It; ++It)
// 	{
// 		ANPCNewSpawnPoint* pt = *It;
// 
// 		for (INT i = 0; i < pt->NPCTemplateList.Num(); ++i)
// 		{
// 			if(pt->NPCTemplateList(i).NPCTemplate)
// 			{
// 				pt->NPCTemplateList(i).NPCTemplateNew = FindNewNPCTemplate(pt->NPCTemplateList(i).NPCTemplate);
// 				pt->GetOutermost()->MarkPackageDirty();
// 			}
// 		}
// 	}

// 	for(TObjectIterator<ANPCServerInstance> It; It; ++It)
// 	{
// 		ANPCServerInstance* pt = *It;
// 
// 		if(pt->Template)
// 		{ 
// 			pt->TemplateNew = FindNewNPCTemplate(pt->Template);
// 			pt->GetOutermost()->MarkPackageDirty();
// 		}
// 	}	
}

#endif