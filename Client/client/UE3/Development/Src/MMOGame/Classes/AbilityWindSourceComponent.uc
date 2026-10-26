class AbilityWindSourceComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;


var() editinline WindPointSourceComponent WindComponentTemplate;
var() ESourceType   SourceType;
var() bool          bAttach;
var() name AttachSocketName <DynamicList="SocketList">;
var() Vector RelativeLocation;
var() Rotator RelativeRotation;

cpptext
{
	virtual FString GetResName();
	virtual struct BaseComponent* CreateCplusplusNode();
}



DefaultProperties
{
	LineColor=(R=0.6,G=0.851,B=0.9176,A=1.0)
	TitleString="WindSource"
	bHaveTrail=true

}
