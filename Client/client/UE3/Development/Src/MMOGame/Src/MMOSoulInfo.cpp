#include "MMOFacade.h"
#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "net/message_handler.h"
#include "UITextParser.h"


IMPLEMENT_CLASS(UMMOSoulInfo)

void UMMOSoulInfo::ExportExcelHeaders(TArray<FString>& Header,TArray<FString>& DefaultValues)
{
	Header.AddItem(TEXT("TemplateID"));
	DefaultValues.AddItem(TEXT("0"));

	Header.AddItem(TEXT("AttrType"));
	DefaultValues.AddItem(TEXT("0"));

	Header.AddItem(TEXT("Param"));
	DefaultValues.AddItem(TEXT("0"));

	Header.AddItem(TEXT("MatchSocket"));
	DefaultValues.AddItem(TEXT("0"));

	Header.AddItem(TEXT("SoulLevel"));
	DefaultValues.AddItem(TEXT("0"));

	Header.AddItem(TEXT("PriceValue"));
	DefaultValues.AddItem(TEXT("0"));

	Header.AddItem(TEXT("UpgradeSoulID"));
	DefaultValues.AddItem(TEXT("0"));

	Header.AddItem(TEXT("DetouchPrice"));
	DefaultValues.AddItem(TEXT("0"));

}
void UMMOSoulInfo::DataToExcel(TArray<FString>& Row)
{
}
void UMMOSoulInfo::ImportFromExcel(const TArray<FString>& values)
{
}
void UMMOSoulInfo::InitDataToExcel()
{
}
INT UMMOSoulInfo::GetTemplateID() const
{
	return TemplateID;
}