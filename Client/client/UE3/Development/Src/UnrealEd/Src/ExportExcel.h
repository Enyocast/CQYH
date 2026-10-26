#ifndef __EXPORTEXCEL_H__
#define __EXPORTEXCEL_H__

#if WITH_EDITOR


struct PropertyNode
{
	PropertyNode()
	{
		ObjPro	= NULL;
		Data	= NULL;
		DebugIndex = -1;	
	}

	FString StringValue;
	TArray<PropertyNode> ChildNode;
	UProperty*	ObjPro;
	BYTE*		Data;
	FString DebugString;
	int DebugIndex;
};

class UObject* FindReferenceObjectByID(class UClass* classType, INT templateID);

typedef bool (*FindReferenceObjectByIDPtr)( class UClass* classType, INT templateID, class UObject*& outPtr );

bool _FindReferenceObjectByID(class UClass* classType, INT templateID, class UObject*& outPtr);
// bool FindReferenceObjectByID_Ability(class UClass* classType, INT templateID, class UObject*& outPtr);
// bool FindReferenceObjectByID_Item(class UClass* classType, INT templateID, class UObject*& outPtr);
// bool FindReferenceObjectByID_Equip(class UClass* classType, INT templateID, class UObject*& outPtr);
// bool FindReferenceObjectByID_NPCTemplate(class UClass* classType, INT templateID, class UObject*& outPtr);
// bool FindReferenceObjectByID_Quest(class UClass* classType, INT templateID, class UObject*& outPtr);

#if !SHIPPING_PC_GAME

void CheckIDError(class UClass* classType, const TArray<UPackage*>& pkgs);
void RecursiveCheckForError(UProperty* ObjPro, UObject* obj);

#endif

#endif // WITH_EDITOR

#endif