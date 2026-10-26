#ifndef _EXPORTER_TRIGGER_VOLUME_H_
#define _EXPORTER_TRIGGER_VOLUME_H_

#if !SHIPPING_PC_GAME

#include "ExportServerData.h"

class Exporter_TriggerVolume : public IGlobalDataExporter
{
public:
	Exporter_TriggerVolume(void);
	virtual ~Exporter_TriggerVolume(void);

	virtual void ProcessData(INT& GlobalAutoID);
};

#endif
#endif