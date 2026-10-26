#ifndef _SINGLENPCSPAWNPOINT_H_
#define _SINGLENPCSPAWNPOINT_H_

#if !SHIPPING_PC_GAME

#include "ExportServerData.h"
#include <vector>

//illegal zero-sized array 服务端数据结构需要
#pragma warning(disable:4200)

class Exporter_SingleNPCSpawnPoint : public IServerSceneExporter
{
public:
	Exporter_SingleNPCSpawnPoint(void);
	virtual ~Exporter_SingleNPCSpawnPoint(void);

	virtual void PrePorcess(INT& GlobalAutoID);
	virtual void WriteHeader(FBufferArchive& ar  );
	virtual void WriteData(FBufferArchive& ar);
	
	virtual	int GetBlockNumber() const { return 1; }

private:
	SCENE_FILE_BLOCK_HEADER* arBlkHdrs;

	std::vector< ANPCServerInstance * >	NPCSpawnPointList; 
	FBufferArchive			memPointAr;

};

#endif

#endif