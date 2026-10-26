#ifndef _EXPORTER_KISMET_H_
#define _EXPORTER_KISMET_H_

#if !SHIPPING_PC_GAME

#include "ExportServerData.h"

class Exporter_Kismet : public IServerSceneExporter
{
public:
	Exporter_Kismet(void);
	virtual ~Exporter_Kismet(void);

	virtual void PrePorcess(INT& GlobalAutoID);
	virtual void WriteHeader(FBufferArchive& ar );
	virtual void WriteData(FBufferArchive& ar);

	virtual	int GetBlockNumber() const { return 1; }

	struct SCENE_FILE_BLOCK_HEADER* KismetHeader;
	TArray<USequenceVariable*> SeqVars;
};

#endif

#endif