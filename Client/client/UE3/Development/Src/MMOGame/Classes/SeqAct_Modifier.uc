/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
class SeqAct_Modifier extends SequenceOp
	native
	hidecategories(SequenceObject);

cpptext
{
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	virtual void Activated();
	virtual UBOOL UpdateOp(FLOAT DeltaTime);
	virtual void DeActivated();

	virtual void Spawned(UObject *NewSpawn);

	virtual FString GetDetailedDescription( INT InIndex );

	INT GetId(){ return Id; }

	UBOOL _NeedMark(USeqAct_Modifier* pNode);
	virtual void PostLoad();

	#if WITH_EDITOR
	virtual void CheckForErrors();
	#endif
};


enum EModifierTargetType
{
	EModifer_Type1 <DisplayName="MT_Type1">,
	EModifer_Type2 <DisplayName="MT_Type2">,
	EModifer_Type3 <DisplayName="MT_Type3">,
	EModifer_Type4 <DisplayName="MT_Type4">,
};

struct native ModifierParam
{
	var() init string       ValueStr	<DisplayName="ValueStr">;
//	var() init string       ValueX		<DisplayName="ValueX">;
//	var() int               Value1		<DisplayName="Value1">;
	var() SeqAct_Modifier   Value2		<DisplayName="Value2">;
};

var(ModifierNode)	editconst	int Id						<DisplayName="Id">;
var(ModifierNode)	string NodeName							<DisplayName="NodeName">;
var(ModifierNode)	editconst	EModifierTargetType Type	<DisplayName="Type">;
var(ModifierNode)	SeqAct_Modifier ParentNode				<DisplayName="ParentNode">;
var(ModifierNode)	SeqAct_Modifier TrueRetNode				<DisplayName="TrueRetNode">;	 
var(ModifierNode)	SeqAct_Modifier FalseRetNode			<DisplayName="FalseRetNode">;	 
var(ModifierNode)	SeqAct_Modifier NextNode				<DisplayName="NextNode">; 
var(ModifierNode)	int Key									<DisplayName="Key">;
var(ModifierNode)	ModifierParam Param1					<DisplayName="Param1">;
var(ModifierNode)	ModifierParam Param2					<DisplayName="Param2">;
var(ModifierNode)	ModifierParam Param3					<DisplayName="Param3">;


var(Debug) editconst bool bRoot;
var(Debug) editconst array<SeqAct_Modifier> Modifiers;
var bool bInit;
var(Debug) editconst SeqAct_Modifier Parent;
var(Debug) transient bool BreakOnExport;

static event int GetObjClassVersion()
{
	return Super.GetObjClassVersion() + 0;
}

defaultproperties
{
	ObjName="Modifier"
	ObjCategory="Actor"

	InputLinks(0)=(LinkDesc="In")

	OutputLinks(0)=(LinkDesc="TrueRetNode")
	OutputLinks(1)=(LinkDesc="NextNode")
	OutputLinks(2)=(LinkDesc="FalseRetNode")
	bRoot = false
	bInit = false 
	Parent= None
}
