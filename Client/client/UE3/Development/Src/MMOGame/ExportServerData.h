#ifndef _EXPORT_SERVER_DATA_H_
#define _EXPORT_SERVER_DATA_H_

FString GetCurrentNPCPreLoadingListFile();

#if !SHIPPING_PC_GAME

void ExportBinaryServerScene();

void ConvertToNewNPCTemplate();
void FixNPCTemplateRef();
void ExtractEquipAppearence();

//
// Server scene data exporter interface
//
class IServerSceneExporter
{
public:

	virtual void PrePorcess(INT& GlobalAutoID) = 0;
	virtual void WriteHeader(FBufferArchive& ar ) = 0;
	virtual void WriteData(FBufferArchive& ar) = 0;

	// 返回每个导出插件需要导出多少种类型数据（一般一个插件只处理一种class）
	virtual	int GetBlockNumber() const = 0;
};

//
// 全局数据处理
//
class IGlobalDataExporter
{
public:

	virtual void ProcessData(INT& GlobalAutoID) = 0;
};

typedef TArray<IServerSceneExporter*> ServerSceneExporterList;
extern ServerSceneExporterList GServerSceneExporterList;

// 扩展插件，处理一些全局导出时的预处理
typedef TArray<IGlobalDataExporter*> GlobalDataExporterList;;
extern GlobalDataExporterList GGlobalDataExporterList;

#define REG_SERVER_EXPORTER(ExportClass) \
	ExportClass __##ExportClass##Instance; \
	GServerSceneExporterList.AddItem(&__##ExportClass##Instance);


#define REG_GLOBAL_EXPORTEREX(ExportClass) \
	ExportClass __##ExportClass##Instance; \
	GGlobalDataExporterList.AddItem(&__##ExportClass##Instance);

#endif // #if !SHIPPING_PC_GAME

#endif
