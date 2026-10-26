class AbilityMeshChangeComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;

var() AvatarData MeshData;


cpptext
{
	virtual FString GetResName() { return TitleString; }
	virtual struct BaseComponent* CreateCplusplusNode();
}



DefaultProperties
{
	LineColor=(R=1.0,G=1.0,B=0.5,A=1.0)
	TitleString="MeshChange"
	bHaveTrail=true
}

