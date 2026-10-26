#ifndef _EXPORTER_NPCINSTANCEINFOS_H_
#define _EXPORTER_NPCINSTANCEINFOS_H_

#if !SHIPPING_PC_GAME

#include "ExportServerData.h"

class Exporter_NPCInstanceInfos : public IGlobalDataExporter
{
public:
	Exporter_NPCInstanceInfos(void);
	virtual ~Exporter_NPCInstanceInfos(void);

	virtual void ProcessData(INT& GlobalAutoID);
};

#endif
#endif