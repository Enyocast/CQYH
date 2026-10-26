#include "stdafx.h"
#include "Exporter_MapMapSizeVolume.h"
#include <sstream>
#include <fstream>
#include <ios>
#include "SourceControl.h"
#include "MMOFacade.h"

#if !SHIPPING_PC_GAME

Exporter_MapMapSizeVolume::Exporter_MapMapSizeVolume(void)
{
}
//------------------------------------------------------------------------
Exporter_MapMapSizeVolume::~Exporter_MapMapSizeVolume(void)
{
}
//------------------------------------------------------------------------
void Exporter_MapMapSizeVolume::ProcessData(INT& GlobalAutoID)
{
	UWorld*	World = GWorld;

	FString ExportDir;
	GConfig->GetString(TEXT("Configuration"), TEXT("GlobalMapInfoPath"), ExportDir, GGameIni);
	ExportDir = MMO::FormatTempleteDataLoadingDir(ExportDir);

	FString mapName = World->GetWorldInfo()->GetMapName() + TEXT(".volume");
	FString mapPath = ExportDir + mapName;

	const INT C_TMPBUF_SZ = 2048;
	wchar_t tmpBuf[C_TMPBUF_SZ];

	std::wstringstream ss;

	ss << TEXT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");

	FVector2D MapSize(100, 50);
	INT ServerMapType = E_est_Static;
	UMMOMapInfo* mapInfo = Cast<UMMOMapInfo>(World->GetWorldInfo()->GetMapInfo());
	if(mapInfo)
	{
		MapSize = mapInfo->Map2DExportSize;
		//ServerMapType = mapInfo->ServerMapType;
	}

	swprintf_s(tmpBuf, C_TMPBUF_SZ - 1,
		TEXT("<root CanvasDrawSize=\"%s\" ServerMapType=\"%d\">\n"),
		*MapSize.ToString(), ServerMapType);

	ss << tmpBuf;


	for( int i = 0; i < World->Levels.Num(); ++i ){
		ULevel* Level = World->Levels(i);

		for (INT j = 0; j < Level->Actors.Num(); ++j){
			AActor* actor = Level->Actors(j);

			if(actor && (actor->GetClass() == AMMOVolume_MapSize::StaticClass())){
				AMMOVolume_MapSize* volumeMapSize = Cast<AMMOVolume_MapSize>(actor);
				FBox volumeBox;
				volumeBox = volumeMapSize->GetComponentsBoundingBox(TRUE);

				memset(tmpBuf, 0, sizeof(wchar_t) * C_TMPBUF_SZ);

				swprintf_s( tmpBuf, C_TMPBUF_SZ - 1,
					TEXT("\t<VolumeMapSize Name=\"%s\" DisplayName=\"%s\" Priority=\"%d\" ReuseMapVolumeName=\"%s\" MinPos=\"%s\" MaxPos=\"%s\" "),
					*volumeMapSize->GetName(),
					*volumeMapSize->DisplayName,
					volumeMapSize->Priorrity,
					*volumeMapSize->ReuseMapVolumeName,
					*volumeBox.Min.ToString(),
					*volumeBox.Max.ToString() );
				ss << tmpBuf;

				memset(tmpBuf, 0, sizeof(wchar_t) * C_TMPBUF_SZ);
				swprintf_s( tmpBuf, C_TMPBUF_SZ - 1,
					TEXT("MiniMapTileRowNum=\"%d\" MiniMapTileColNum=\"%d\" MiniMapPixelSize=\"%f\" MiniMapScale=\"%f\" MiniMapOffsetX=\"%d\" MiniMapOffsetY=\"%d\" "),
					volumeMapSize->MiniMapTileRowNum,
					volumeMapSize->MiniMapTileColNum,
					volumeMapSize->MiniMapPixelSize,
					volumeMapSize->MiniMapScale,
					volumeMapSize->MiniMapOffsetX,
					volumeMapSize->MiniMapOffsetY );
				ss << tmpBuf;

				memset(tmpBuf, 0, sizeof(wchar_t) * C_TMPBUF_SZ);
				swprintf_s( tmpBuf, C_TMPBUF_SZ - 1,
					TEXT("WorldMapTileRowNum=\"%d\" WorldMapTileColNum=\"%d\" WorldMapPixelSize=\"%f\" WorldMapScale=\"%f\" WorldMapOffsetX=\"%d\" WorldMapOffsetY=\"%d\"/>\n"),
					volumeMapSize->WorldMapTileRowNum,
					volumeMapSize->WorldMapTileColNum,
					volumeMapSize->WorldMapPixelSize,
					volumeMapSize->WorldMapScale,
					volumeMapSize->WorldMapOffsetX,
					volumeMapSize->WorldMapOffsetY	);
				ss << tmpBuf;
			}
		} 
	}

	ss << TEXT("</root>\n");


	SET_WARN_COLOR(COLOR_GREEN);
	warnf(TEXT("=====[Export]===== Exported map Volume_MapSize info file:%s"), *mapPath);
	CLEAR_WARN_COLOR();

#if HAVE_SCC
	FCheckoutResult sccResult = FSourceControl::TryCheckOut(mapPath);
#endif

	std::string str(TCHAR_TO_ANSI(*mapPath));
	std::wfstream fs(str.c_str(), std::ios_base::out);
	if(fs.good())
	{
		fs << TCHAR_TO_UTF8(ss.str().c_str());
		fs.close();
	}

#if HAVE_SCC
	sccResult.TryAddToDefaultChangelist();
#endif
}
//------------------------------------------------------------------------
#endif