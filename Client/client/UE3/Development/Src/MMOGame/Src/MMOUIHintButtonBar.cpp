#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOHintButtonManager.h"

IMPLEMENT_CLASS(UMMOUIHintButtonBar)

INT UMMOUIHintButtonBar::AddNewButton(const FString& iconResouce,INT time,UBOOL add)
{
	TArray<struct FASValue> Arguments;
	FASValue Asvalue( EC_EventParm );

	Asvalue.S = iconResouce;
	Asvalue.Type = AS_String;
	Arguments.AddItem( Asvalue );

	Asvalue.I = time;
	Asvalue.Type = AS_Int;
	Arguments.AddItem( Asvalue );

	Asvalue.B = add;
	Asvalue.Type = AS_Boolean;
	Arguments.AddItem( Asvalue );

	FASValue retVal = this->Invoke( TEXT("addNewButton") , Arguments );
	return retVal.I;

}


void UMMOUIHintButtonBar::RemoveButton(INT pos)
{
	TArray<struct FASValue> Arguments;
	FASValue Asvalue( EC_EventParm );
	Asvalue.I = pos;
	Asvalue.Type = AS_Int;
	Arguments.AddItem( Asvalue );

	this->Invoke( TEXT("removeButton") , Arguments );

}

void UMMOUIHintButtonBar::ASHintButtonClick(INT id)
{
	MMOHintButtonManager::getSingleton().ClickButton(id);
}