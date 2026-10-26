//INT         GetTextColor(INT Val, INT OriVal);
//UGFxObject* CreateAttributeTab(FString NodeName);
//UGFxObject* CreateAttributeValue(FString NodeName, INT Val, INT OriVal,BOOL PercentageFlag=FALSE);
//UGFxObject* CreateAttributeRange(FString NodeName, INT Val, INT OriVal,INT Val2, INT OriVal2,BOOL PercentageFlag=FALSE);
//void	    CreateAttributeNull(INT enum1, INT& index, UGFxObject *DataProvider, UEnum* Enum);
//void	    AddAttributeList(INT enum1,INT enum2, INT& index, UGFxObject *DataProvider,UActorAttribute* Attributes,UEnum* Enum ,INT level,INT classId,BOOL floatFormat = FALSE);
//
//// virtual void PreOnShow(UBOOL v);
virtual void Init();
virtual void UnInit();
virtual void PostOnShow(UBOOL v);