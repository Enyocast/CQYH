#ifndef _EXPORTER_MAPMAPSIZEVOLUME_H_
#define _EXPORTER_MAPMAPSIZEVOLUME_H_

#if !SHIPPING_PC_GAME

#include "ExportServerData.h"

class Exporter_MapMapSizeVolume : public IGlobalDataExporter
{
public:
	Exporter_MapMapSizeVolume(void);
	virtual ~Exporter_MapMapSizeVolume(void);

	virtual void ProcessData(INT& GlobalAutoID);
};

#endif
#endif