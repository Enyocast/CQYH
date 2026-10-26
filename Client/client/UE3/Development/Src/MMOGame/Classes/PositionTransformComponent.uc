class PositionTransformComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;


enum TransformType
{
	TransformType_Location,
	TransformType_Rotator,
};

enum EEndPositionType
{
	EndPositionType_StartPoint,
	EndPositionType_CurrentPoint,
	EndPositionType_EndPoint,
};

struct native PointNode
{
	var() float Time <ClampMin=0.0 | ClampMax=1.0>;
	var() Vector Point;
};

var() TransformType Type;
var() InterpCurveVector Values;
var() bool bResizePointTimeToComponentLifespan;
var() bool bNeedRotatorToDes;
var() EEndPositionType EndPositionType;


cpptext
{
	virtual FString GetResName() { return TitleString; }
	virtual struct BaseComponent* CreateCplusplusNode();
}



DefaultProperties
{
	LineColor=(R=0.86,G=1.0,B=0.5,A=1.0)
	TitleString="PositionTransform"
	bHaveTrail=true
	bNeedRotatorToDes=false
	bResizePointTimeToComponentLifespan=true
}

