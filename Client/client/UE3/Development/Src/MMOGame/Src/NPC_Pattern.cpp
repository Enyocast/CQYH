#include "stdafx.h"

IMPLEMENT_CLASS(UNPC_Pattern);


//------------------------------------------------------------------------
void UNPC_Pattern::DataToExcel(TArray<FString>& Row)
{

}
//------------------------------------------------------------------------
void UNPC_Pattern::ExportExcelHeaders(TArray<FString>& Header,TArray<FString>& DefaultValues)
{
}
void UNPC_Pattern::InitDataToExcel()
{

}

//------------------------------------------------------------------------
void UNPC_Pattern::ImportFromExcel(const TArray<FString>& Values)
{	
}
//------------------------------------------------------------------------
int UNPC_Pattern::GetTemplateID() const
{
	return TemplateID;
}