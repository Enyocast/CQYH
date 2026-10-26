/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
class SeqVar_Bool extends SequenceVariable
	native(Sequence);

cpptext
{
	// oscar@snda
	virtual UBOOL IsServerKismetObject() const { return TRUE; }
	virtual int GetKismetObjectServerType() const;
	virtual void ExportServerData(FArchive& inStream);
	// oscar@snda

	virtual UBOOL* GetRef()
	{
		return (UBOOL*)&bValue;
	}

	FString GetValueStr()
	{
		return bValue ? GTrue : GFalse;
	}

	virtual UBOOL SupportsProperty(UProperty *Property)
	{
		return (Property->IsA(UBoolProperty::StaticClass()));
	}

	virtual void PublishValue(USequenceOp *Op, UProperty *Property, FSeqVarLink &VarLink);
	virtual void PopulateValue(USequenceOp *Op, UProperty *Property, FSeqVarLink &VarLink);
}

var() int			bValue;

// Red bool - gives you wings!
defaultproperties
{
	ObjName="Bool"
	ObjColor=(R=255,G=0,B=0,A=255)		// red
}
