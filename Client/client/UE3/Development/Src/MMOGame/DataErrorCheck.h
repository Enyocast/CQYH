#ifndef __DATAERRORCHECK_H__
#define __DATAERRORCHECK_H__

#if !SHIPPING_PC_GAME

void AddDataError(const FString& tabFile, const FString& msg);
void ReportAllDataError();

void EnableErrorToConsole(bool on);

void BeginLoadData(const FString& loadingContex);

#define M_BeginLoadData BeginLoadData
#define M_AddDataError AddDataError
#define M_ReportError ReportAllDataError
#define M_EnableErrorToConsole EnableErrorToConsole
#else

#define M_BeginLoadData(...)
#define M_AddDataError(...)
#define M_ReportError(...)
#define M_EnableErrorToConsole(...)
#endif


#endif