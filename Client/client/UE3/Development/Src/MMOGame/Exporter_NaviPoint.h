#ifndef _EXPORTER_NAVIPOINT_H_
#define _EXPORTER_NAVIPOINT_H_

#if !SHIPPING_PC_GAME

#include "ExportServerData.h"

class Exporter_NaviPoint : public IGlobalDataExporter
{
public:
	Exporter_NaviPoint(void);
	virtual ~Exporter_NaviPoint(void);

	virtual void ProcessData(INT& GlobalAutoID);
};

#endif
#endif