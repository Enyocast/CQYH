#include "stdafx.h"
#include "Exporter_NaviPoint.h"
#include <sstream>
#include <fstream>
#include <ios>
#include "SourceControl.h"
#include "MMOFacade.h"

#if !SHIPPING_PC_GAME

Exporter_NaviPoint::Exporter_NaviPoint(void)
{
}

Exporter_NaviPoint::~Exporter_NaviPoint(void)
{
}

void Exporter_NaviPoint::ProcessData(INT& GlobalAutoID)
{
	UWorld*	World = GWorld;
	FString ExportDir;
	GConfig->GetString(TEXT("Configuration"), TEXT("GlobalMapInfoPath"), ExportDir, GGameIni);

	ExportDir = MMO::FormatTempleteDataLoadingDir(ExportDir);

	FString mapName = World->GetWorldInfo()->GetMapName() + TEXT(".navipoints");
	FString mapPath = ExportDir + mapName;

	std::wstringstream ss;
	ss << TEXT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");

	const INT C_TMPBUF_SZ = 2048;
	wchar_t buffer[C_TMPBUF_SZ];
	INT mapType = E_est_Static;
	swprintf_s(buffer, C_TMPBUF_SZ - 1, TEXT("<root ServerMapName=\"%s\" ServerMapType=\"%d\">\n"), *(World->GetWorldInfo()->GetMapName()), mapType);
	ss << buffer;

	for (TObjectIterator<AMMONavPoint> iter; iter; ++ iter)
	{
		AMMONavPoint* point = *iter;
		if (point)
		{
			memset(buffer, 0, sizeof(wchar_t) * C_TMPBUF_SZ);

			swprintf_s(buffer, C_TMPBUF_SZ - 1,
				TEXT("\t<NaviPoint Name=\"%s\" DisplayName=\"%s\" Position=\"%s\" RedirectLoc=\"%s\" IsShow=%d/>\n"),
				*(point->ConfigName),
				*(point->DisplayName),
				*(point->Location.ToString()),
				*(point->RedirectLoc.ToString()),
				point->IsShowOnUI);

			ss << buffer;
		}
	}

	ss << TEXT("</root>\n");

	FCheckoutResult result = FSourceControl::TryCheckOut(mapPath);
	std::string mapPathTemp(TCHAR_TO_ANSI(*mapPath));
	std::wfstream fs(mapPathTemp.c_str(), std::ios_base::out);
	if (fs.good())
	{
		fs << TCHAR_TO_UTF8(ss.str().c_str());
		fs.close();
	}
	result.TryAddToDefaultChangelist();
}

#endif