//------------------------------------------------------------------------
// oscar@snda
//------------------------------------------------------------------------

#ifndef __MSERVERMAPCFGEXPORT_H__
#define __MSERVERMAPCFGEXPORT_H__

#if WITH_EDITOR
class MServerMapCfgExport
{
public:

	static void ExportToExcel(const TArray< TArray<FString> >& CfgData, const FString& ExcelFile, const FString& ExportFile);

	static void ImportSceneConfigFromExcel(const FString& sceneFile, TArray< TArray<FString> >& sceneDat,
		const FString& dunFile, TArray< TArray<FString> >& dungeonDat);

};
#endif // WITH_EDITOR

#endif