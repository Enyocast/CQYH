#include "stdafx.h"
//#include "MMOGameClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UDoodad)

BYTE UDoodad::GetActorType() const
{
	return EACT_Doodad;
}

int UDoodad::GetTemplateID() const
{
	return ID;
}

void UDoodad::ExportExcelHeaders(TArray<FString>& Header, TArray<FString>& DefaultValues)
{

}
void UDoodad::DataToExcel(TArray<FString>& Row)
{

}
void UDoodad::ImportFromExcel(const TArray<FString>& values)
{

}
void UDoodad::InitDataToExcel()
{

}

/*
void UDoodad::GetDynamicListValues(const DynamicListInfo& ListInfo, TArray<FString>& Values)
{
    if(ListInfo.ListName == TEXT("Doodad_RoleAnimGroup"))
    {
        for( TObjectIterator<UDoodad_RoleAnimGroup> It ; It ; ++It )
        {
            UDoodad_RoleAnimGroup* item = *It;
            Values.AddItem(item->GetName());
        }
    }
    else
    {
        Super::GetDynamicListValues(ListInfo, Values);
    }
}
*/
