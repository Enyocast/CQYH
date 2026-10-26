#include "ExportArchetypeToXMLUtils.h"



UBOOL ExportArchetypeUtils::ShouldSerializeValue( QWORD PropertyFlags)
{
	UBOOL Skip = FALSE;
	if( (PropertyFlags & (CPF_Native|CPF_Transient|CPF_DuplicateTransient|CPF_ArchetypeProperty|CPF_NonTransactional|CPF_Deprecated)) != 0 )
	{
		Skip =	((PropertyFlags & CPF_Native) != 0)
			||	((PropertyFlags & CPF_Transient) != 0 )
			||	((PropertyFlags & CPF_DuplicateTransient) != 0 )
			||	((PropertyFlags & CPF_ArchetypeProperty) != 0)
			||	((PropertyFlags & CPF_Deprecated) != 0 );
	}
	return !Skip;
}

void ExportArchetypeUtils::PropertyToXML(BYTE*Data, UProperty* Property, TiXmlElement* super)
{
	UPropertyValue pv;
	Property->GetPropertyValue(Data, pv);
	//Property->SerializeItem( Ar, Data + Property->Offset + Idx * Property->ElementSize, 0 );
	if (Property->IsA(UBoolProperty::StaticClass()))
	{
		UBOOL ret = pv.BoolValue;
		TiXmlElement* newEle = new TiXmlElement(TCHAR_TO_UTF8(*(Property->GetName())));
		newEle->SetAttribute("type", "bool");
		newEle->SetAttribute("value", ret);
		super->LinkEndChild(newEle);
	}
	else if (Property->IsA(UByteProperty::StaticClass()))
	{
		BYTE ret = pv.ByteValue;
		TiXmlElement* newEle = new TiXmlElement(TCHAR_TO_UTF8(*(Property->GetName())));
		newEle->SetAttribute("type", "byte");
		newEle->SetAttribute("value", ret);
		super->LinkEndChild(newEle);
	}
	else if (Property->IsA(UFloatProperty::StaticClass()))
	{
		FLOAT ret = pv.FloatValue;
		TiXmlElement* newEle = new TiXmlElement(TCHAR_TO_UTF8(*(Property->GetName())));
		newEle->SetAttribute("type", "float");
		newEle->SetDoubleAttribute("value", ret);
		super->LinkEndChild(newEle);
	}
	else if (Property->IsA(UIntProperty::StaticClass()))
	{
		INT ret = pv.IntValue;
		TiXmlElement* newEle = new TiXmlElement(TCHAR_TO_UTF8(*(Property->GetName())));
		newEle->SetAttribute("type", "int");
		newEle->SetAttribute("value", ret);
		super->LinkEndChild(newEle);
	}
	else if (Property->IsA(UNameProperty::StaticClass()))
	{
		FName* ret = pv.NameValue;
		TiXmlElement* newEle = new TiXmlElement(TCHAR_TO_UTF8(*(Property->GetName())));
		newEle->SetAttribute("type", "string");
		newEle->SetAttribute("value", TCHAR_TO_UTF8(*(ret->GetNameString())));
		super->LinkEndChild(newEle);
	}
	else if (Property->IsA(UArrayProperty::StaticClass()))
	{
		TiXmlElement* current = new TiXmlElement(TCHAR_TO_UTF8(*(Property->GetName())));
		current->SetAttribute("type", "array");
		super->LinkEndChild(current);

		for (INT ArrayIndex = 0; ArrayIndex < pv.ArrayValue->Num(); ArrayIndex++)
		{
			UArrayProperty* ArrayProp = (UArrayProperty*)Property;
				if (!ShouldSerializeValue(ArrayProp->Inner->GetPropertyFlags()))
				{
					continue;
				}
				PropertyToXML(((BYTE*)pv.ArrayValue->GetData())+ArrayIndex*ArrayProp->Inner->ElementSize, ArrayProp->Inner, current);
		}
	}
	else if (Property->IsA(UObjectProperty::StaticClass()))
	{
		UObject* ret = pv.ObjectValue;
		if(ret == NULL)
		{
			return;
		}
		if(ret->HasAnyFlags(RF_ArchetypeObject) == FALSE)
		{
			return;
		}
		TiXmlElement* current = new TiXmlElement(TCHAR_TO_UTF8(*(ret->GetName())));
		current->SetAttribute("type", "object");
		super->LinkEndChild(current);
		ExportArchetypeUtils::ExportOjbectToXML(ret, current);

	}
	else if (Property->IsA(UStrProperty::StaticClass()))
	{
		FString* ret = pv.StringValue;
		TiXmlElement* newEle = new TiXmlElement(TCHAR_TO_UTF8(*(Property->GetName())));
		newEle->SetAttribute("type", "string");
		newEle->SetAttribute("value", TCHAR_TO_UTF8(**ret));
		super->LinkEndChild(newEle);
	}
	else if (Property->IsA(UStructProperty::StaticClass()))
	{
		TiXmlElement* current = new TiXmlElement(TCHAR_TO_UTF8(*(Property->GetName())));
		current->SetAttribute("type", "struct");
		super->LinkEndChild(current);

		if (((UStructProperty*)Property)->Struct == NULL)
		{
			return;
		}

		UProperty* NextProperty = ((UStructProperty*)Property)->Struct->PropertyLink;

		for (; NextProperty != NULL; NextProperty = NextProperty->PropertyLinkNext)
		{
			for(INT i = 0; i < NextProperty->ArrayDim; ++i)
			{
				if (!ShouldSerializeValue(NextProperty->GetPropertyFlags()))
				{
					continue;
				}
				PropertyToXML(Data+NextProperty->Offset + NextProperty->ElementSize*i, NextProperty, current);
			}
		}
	}
}

/*
*	export archtype to xml to ... (wait 
*/

void ExportArchetypeUtils::ExportOjbectToXML(UObject* Obj, TiXmlElement* super)
{
	TiXmlElement* current = new TiXmlElement(TCHAR_TO_UTF8((*(Obj->GetName()))));
	current->SetAttribute("type", "object");

	super->LinkEndChild(current);


	for (UProperty* Property = Obj->GetClass()->PropertyLink; Property != NULL; Property = Property->PropertyLinkNext)
	{
		for( INT Idx=0; Idx<Property->ArrayDim; Idx++ )
		{
			if (!ShouldSerializeValue(Property->GetPropertyFlags()))
			{
				continue;
			}
			PropertyToXML((BYTE*)Obj+Property->Offset+Property->ElementSize*Idx, Property, current);
		}
	}
}

UBOOL ExportArchetypeUtils::ExportToXML(const TCHAR* Str)
{
	FString temName;
	//if (ParseCommand(&Str, TEXT("ABILITY")))
	//{

		TArray<FString> list, list1,list2;
		FString dir = TEXT("..\\..\\MMOGame\\Content\\MMOContent\\06_Ability");
		
		appFindFilesInDirectory(list1, *dir, TRUE, FALSE);

		dir = TEXT("..\\..\\MMOGame\\Content\\MMOContent\\05_Items");
		appFindFilesInDirectory(list2, *dir, TRUE, FALSE);

		list.Append(list1);
		list.Append(list2);

		FString fileName = FString(TEXT("..\\..\\MMOGame\\ExportData\\")) + FString(Str) + FString(TEXT("Data")) + FString(TEXT(".xml"));

		TiXmlDocument* myDoc = new TiXmlDocument(TCHAR_TO_ANSI(*fileName));

		TiXmlDeclaration* myDec = new TiXmlDeclaration("1.0", "utf-8", "yes");

		myDoc->LinkEndChild(myDec);

		FString RootName = FString(Str) + FString(TEXT("List"));
		TiXmlElement* EleList = new TiXmlElement(TCHAR_TO_ANSI(*RootName));
		myDoc->LinkEndChild(EleList);


		for (int i = 0; i < list.Num(); ++i)
		{
			const FString& PackageName = FPackageFileCache::PackageFromPath(*list(i));
			UPackage* Package = FindObject<UPackage>(NULL, *PackageName, TRUE);
			if ( Package != NULL )
			{
				Package->FullyLoad();
			}
			else
			{
				Package = UObject::LoadPackage( NULL, *list(i), LOAD_None );
			}

			if( Package == NULL )
			{
				continue;
			}

			for (INT i = 0; i < Package->NetObjects.Num(); ++i)
			{
				UObject* obj = Package->NetObjects(i);
				if(obj && obj->GetClass() && obj->GetClass()->GetName() == FString(Str))
				{
					ExportArchetypeUtils::ExportOjbectToXML(obj, EleList);
				}
			}
		}

		myDoc->SaveFile();
		delete myDoc;
	//}

	return TRUE;
}


void ExportArchetypeUtils::ConvertAbilityData()
{
#if 1

	for ( TObjectIterator<UAbilityEmitterComponent> It ; It ; ++It )
	{
		UAbilityEmitterComponent* EmitComp = *It;
		ExportArchetypeUtils::ConvertAbilityComponent(EmitComp);
	}


	/*
	FString temName;

	TArray<FString> list, list1,list2;
	FString dir = TEXT("..\\..\\MMOGame\\Content\\MMOContent\\06_Ability");

	appFindFilesInDirectory(list1, *dir, TRUE, FALSE);

	list.Append(list1);


	for (int i = 0; i < list.Num(); ++i)
	{
		const FString& PackageName = FPackageFileCache::PackageFromPath(*list(i));
		UPackage* Package = FindObject<UPackage>(NULL, *PackageName, TRUE);
		if ( Package != NULL )
		{
			Package->FullyLoad();
		}
		else
		{
			Package = UObject::LoadPackage( NULL, *list(i), LOAD_None );
		}

		if( Package == NULL )
		{
			continue;
		}

		for (INT i = 0; i < Package->NetObjects.Num(); ++i)
		{
			UObject* obj = Package->NetObjects(i);
			UMMOAbility* AbilityData = Cast<UMMOAbility>(obj);
			if (AbilityData)
			{
				AbilityData->MarkPackageDirty();
				for (INT i = 0; i < AbilityData->SpellComponentList.Num(); ++i)
				{
					ExportArchetypeUtils::ConvertAbilityComponent(AbilityData->SpellComponentList(i));
				}

				for (INT i = 0; i < AbilityData->CastComponentList.Num(); ++i)
				{
					ExportArchetypeUtils::ConvertAbilityComponent(AbilityData->CastComponentList(i));
				}

				for (INT i = 0; i < AbilityData->OverrideComponentList.Num(); ++i)
				{
					for (INT j = 0; j < AbilityData->OverrideComponentList(i).OverrideSpellComponentList.Num(); ++j)
					{
						ExportArchetypeUtils::ConvertAbilityComponent(AbilityData->OverrideComponentList(i).OverrideSpellComponentList(j));
					}

					for (INT j = 0; j < AbilityData->OverrideComponentList(i).OverrideCastComponentList.Num(); ++j)
					{
						ExportArchetypeUtils::ConvertAbilityComponent(AbilityData->OverrideComponentList(i).OverrideCastComponentList(j));
					}
				}
			}
		}
	}
	*/

#endif
}

UBOOL ExportArchetypeUtils::ConvertAbilityComponent(UAbilityComponent* InComponent)
{
	if (InComponent->IsA(UAbilityEmitterComponent::StaticClass()))
	{
		UAbilityEmitterComponent* EmitComp = Cast<UAbilityEmitterComponent>(InComponent);
		if (!EmitComp)
		{
			return FALSE;
		}

		//EmitComp->BezierControlPointList.AddZeroed();
		//EmitComp->BezierControlPointList(0).v1 = EmitComp->BezierControlPoint1;
		//EmitComp->BezierControlPointList(0).v2 = EmitComp->BezierControlPoint2;
		//InComponent->MarkPackageDirty();

		

		//if (EmitComp->AttachType == EAT_SetToTargetPoint)
		//{
		//	EmitComp->SourceType = EST_TargetPoint;
		//	EmitComp->bAttach = FALSE;
		//	EmitComp->MarkPackageDirty();
		//}
	}


	return TRUE;

}
