#ifndef _EXPORTER_SEARCHPOINT_H_
#define _EXPORTER_SEARCHPOINT_H_

#if !SHIPPING_PC_GAME

#include "ExportServerData.h"

class Exporter_SearchPoint : public IGlobalDataExporter
{
public:
	Exporter_SearchPoint(void);
	virtual ~Exporter_SearchPoint(void);

	virtual void ProcessData(INT& GlobalAutoID);
};

#endif
#endif