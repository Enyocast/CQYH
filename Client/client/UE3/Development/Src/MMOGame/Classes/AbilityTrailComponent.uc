class AbilityTrailComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;

/** The Particle system to play */
var(Trails) ParticleSystem PSTemplate;

/** The first edge socket - with the second edge defines the edges of the trail */
var(Trails) name FirstEdgeSocketName <DynamicList="SocketList">;

/**
 *	The control point socket - controls the UV tiling as well as
 *	tapering the two edges to this point.
 */
var(Trails) name ControlPointSocketName <DynamicList="SocketList">;

/** The second edge socket - with the first edge defines the edges of the trail */
var(Trails) name SecondEdgeSocketName <DynamicList="SocketList">;

struct native TrailNode
{
	var string KeyString;
	var AnimNotify_Trails TrailData;
};

var transient array<TrailNode> TrailList;


///** If TRUE, the particle system will play in the viewer as well as in game */
//var() editoronly bool bPreview;

// @todo ib2merge: Chair added this fields, with this comment: added to make editor life easier with our dynamic system
/** If TRUE, this will be previewed as a big attack (using the AnimNotify_FX_Preview section in ini based on pawn's FXSwordTrailBig variable) */
//var() editoronly bool bPreviewBigAttack;

///** If TRUE, this will preview with listed PS and ignore AnimNotify_FX_Preview section in ini for pawn specific data */
//var() editoronly bool bPreviewForceExplicit;


///** If Owner is hidden, skip particle effect */
//var() bool bSkipIfOwnerIsHidden;

///** Locally store 'start' time to determine when regenerating the curve data is required. */
//var float LastStartTime;

///** The end time (will auto-adjust Duration setting, and vice-versa) */
//var float EndTime;

///** The timestep at which to sample the animation for trail points */
//var deprecated float SampleTimeStep;

cpptext
{
	virtual FString GetResName();
	virtual struct BaseComponent* CreateCplusplusNode();
	UAnimNotify_Trails* GetTrailData(UAnimNodeSequence* Seq);
	UAnimNotify_Trails* AddNewTrail(UAnimNodeSequence* Seq, FLOAT StartTime, FLOAT EndTime);
	void RebuildTrail(UAnimNodeSequence* Seq, FLOAT StartTime, FLOAT EndTime);
}


DefaultProperties
{
	LineColor=(R=1.0,G=0.7882,B=0.0549,A=1.0)
	TitleString="Trails"
	bHaveTrail=true
	//bScaleByStandardCollision=false
}

