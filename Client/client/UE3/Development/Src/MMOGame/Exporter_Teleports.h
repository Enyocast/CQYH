#ifndef _EXPORTER_TELEPORTS_H_
#define _EXPORTER_TELEPORTS_H_

#if !SHIPPING_PC_GAME

#include "ExportServerData.h"

class Exporter_Teleports : public IGlobalDataExporter
{
public:
	Exporter_Teleports(void);
	virtual ~Exporter_Teleports(void);

	virtual void ProcessData(INT& GlobalAutoID);
};

#endif
#endif