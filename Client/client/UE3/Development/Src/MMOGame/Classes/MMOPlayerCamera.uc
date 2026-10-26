//
// 主要的相机类
//
class MMOPlayerCamera extends Camera
	native
	dependson(MMOCameraActor)
	config(MMOPlayerCamera)
	;

var config vector TraceExtend;
// 最大的相机距离与最近距离
var config float FarCameraDistance;
var config float NearCameraDistance;

// Yaw偏移值
var config float CameraYawOffset;

// Pitch偏移值
var config float FarCameraPitch;
var config float NearCameraPitch;

// 目标点位置偏移,屏幕上下值
var config float FarCameraLookAtOffset;
var config float NearCameraLookAtOffset;

// 最远距离时的FOV
var config float FarFov;
var config float NearFov;

// 当前距离的比例
var config float DistanceRatio;

// 拉近到多少比例
var float TargetDistancePullPercent;

// 拉近速度
var float TargetDistancePullSpeed;
// 当前相机导航的参考点
var MMOVolume_CammeraNavigator CamNavVolume;
// 目标Yaw值
var float TargetYaw;
var float TargetPitch;
var float CachedPitch;
var bool PitchDirty;

// 默认的转动速度
var float DefaultYawSpeed;
var float DefaultPitchSpeed;

// 默认的跟随速度  
var config bool DefaultSmoothMove;
var config float DefaultMoveSpeed;
var config float DefaultMoveScale;
var config bool EnableDebugMode;

// 缓存一下上次的
var TViewTarget LastViewTarget;
var bool IsMapJustLoaded;
var bool EnableSmoothCameraPos;
var bool EnableSmoothCameraRot;

struct native AutoHideBlockActor
{
	var() Actor HideActor;
	var() MMOActorMaterialController MaterialCtrl;
};

var transient array<AutoHideBlockActor>  HiddenActorList;
var transient array<AutoHideBlockActor>  UnHiddenActorList;
var() float CheckHiddenActorTime;
var vector vLastTargetPos;

var MMOCameraActor PlayerCameraActor[6];
var MMOCameraActor CurrentCameraActor;
var bool isCameraActorImmediatly;
var TViewTarget curVT;

var config float BlockObjectFadeInOutSpeed;

var config bool EnableNearDof;
var config float NearDofFocusDistance;
var transient float FarDofFocusDistance;
var config float NearDofFocusRadius;
var transient float FarDofFocusRadius;
var config float NearDofFalloffExponent;
var transient float FarDofFalloffExponent;
var config float NearDofMaxFarBlurAmount;
var transient float FarDofMaxFarBlurAmount;
var config float NearDofFarBlurKernelSize;
var transient float FarDofFarBlurKernelSize;


var array<Material> MeshTranslucencyMaterials;

final native function CreateMaterial( MeshComponent MeshComp );


//Pow函数，放在native中计算提高速度，a为基数，b为指数
//也可以使用(**)运算符
final native function float Pow( float a, float b);

native function UpdateDebug();


// 初始化函数
simulated event PostBeginPlay()
{
	local MMOCameraActor A;
	super.PostBeginPlay();
	IsMapJustLoaded = true;
	//默认情况下，加载地图后直接将相机就位
	EnableSmoothCameraPos = false;
	EnableSmoothCameraRot = false;
	if(EnableDebugMode)
		`log("[MMOPlayerCamera]PostBeginPlay():EnableSmoothCameraPos" @EnableSmoothCameraPos);
	foreach  AllActors(class'MMOCameraActor', A)
	{
		//if( A.isOnStart )
		//{
			switch( A.CameraType )
			{
			case ECSC_Girl:
			case ECSC_Female:
			case ECSC_Male:
			case ECSC_Base:
			case ECSC_Start:
			case ECSC_Selected:
					PlayerCameraActor[int(A.CameraType)] = A;
				break;
			default:
				break;
			}

		//}
		
	}

	if( PlayerCameraActor[ECSC_Start] != none )
	{
		CurrentCameraActor = PlayerCameraActor[ECSC_Start];
	}
	FarDofFocusDistance = WorldInfo.DefaultPostProcessSettings.DOF_FocusDistance;
	FarDofFocusRadius   = WorldInfo.DefaultPostProcessSettings.DOF_FocusInnerRadius;
	FarDofFalloffExponent = WorldInfo.DefaultPostProcessSettings.DOF_FalloffExponent;
	FarDofMaxFarBlurAmount  = WorldInfo.DefaultPostProcessSettings.DOF_MaxFarBlurAmount;
	FarDofFarBlurKernelSize  = WorldInfo.DefaultPostProcessSettings.DOF_BlurKernelSize;
}



function ChangeStartCameraActor( ECharactorSelectCamera CameraType,bool isImmediatly )
{
		isCameraActorImmediatly = isImmediatly;
		CurrentCameraActor = PlayerCameraActor[CameraType];
		CurrentCameraActor.Start();
	
}

function ChangeShotCameraMode(ECharactorSelectCamera CameraType,float h)
{
	local vector loc;
	loc = CurrentCameraActor.Location;
	loc.Z = h;
			isCameraActorImmediatly = true;
		CurrentCameraActor = PlayerCameraActor[CameraType];
		if( h>0)
			CurrentCameraActor.SetLocation(loc);
}



//---------------------------------------------------------------
// UpdateViewTarget()方法说明
// 这个类继承了基类的Camera摄像机类.
// 当这个类创建的时候，则会自动调用基类GamePawn的虚方法GetDefaultCameraMode(需要重载)(ps.其实UE3里,没有虚函数,他们extends后,都属于重写,本身他就有这方法,可以进基类的uc文件看他怎么写的).
// 如果想自己创建新的摄像机模式，则需要重载GamePawn的GetDefaultCameraMode的方法.
// Camera Mode var  Name  CameraStyle;
// Camera类里的CameraStyle成员变量，就是通过GamePawn的GetDefaultCameraMode实现的。(ps.我觉得这个方法名用Set更合适，不过他不是方法，是需要继承的，所以Get也没错)
// 我在继承的GamePawn类(KWPawn)里返回了Isometric,那么,我们在Camera.uc里，找到UpdateViewTarget方法，将其复制过来(其实也可以不复制，复制的好处是原始的摄像机模式保留)
// 在switch( CameraStyle )的地方添加对Isometric的处理（Isometric随便定义，不过你怎么case的就在你定义的Pawn里怎么Get
// 在这个类里可以设置
// 这是一个可以简单使用且有品质保证的摄像机类上的基本功能，增加或者说是扩展了另一款同等级GameCamera的功能
//---------------------------------------------------------------

native final function BeforeUpdateTick(float DeltaTime);
native final function AfterUpdateTick(float DeltaTime);

native final function EnableUpdatePlayerHUD(bool on);
/**
 * Query ViewTarget and outputs Point Of View.
 *
 * @param	OutVT		ViewTarget to use.
 * @param	DeltaTime	Delta Time since last camera update (in seconds).
 */
function UpdateViewTarget(out TViewTarget OutVT, float DeltaTime)
{
	local vector		        Loc, Pos, HitLocation, HitNormal;
	local rotator		        Rot;
	local Actor			    HitActor;
	local CameraActor  CamActor;
	local TPOV			    OrigPOV;
	//local bool                bSmooth;

	// Don't update outgoing viewtarget during an interpolation 
	//if( PendingViewTarget.Target != None && OutVT == ViewTarget && BlendParams.bLockOutgoing )
	//{
	//	super.UpdateViewTarget(OutVT, DeltaTime);
	//	return;
	//}
	// store previous POV, in case we need it later
	BeforeUpdateTick(DeltaTime);

	UpdateDebug();
	OrigPOV = OutVT.POV;

	// Default FOV on viewtarget
	OutVT.POV.FOV = DefaultFOV;

	// Viewing through a camera actor.
	CamActor = CameraActor(OutVT.Target);

	if(CurrentCameraActor != none)
		CamActor = CurrentCameraActor;
	//如果当前指定了相机Actor，则直接跳过本地的计算
	if( CamActor != None )
	{
		if( isCameraActorImmediatly )
		{
			OutVT.POV.Rotation = CamActor.Rotation;
			OutVT.POV.Location = CamActor.Location;
			OutVT.POV.FOV =CamActor.FOVAngle;
		}
		else
				CamActor.GetCameraView(DeltaTime, OutVT.POV);

		//`log("[MMOPlayerCamera]UseAcotr2UpdateViewTarget():" @CamActor.Name);
		// Grab aspect ratio from the CameraActor.
		bConstrainAspectRatio	= bConstrainAspectRatio || CamActor.bConstrainAspectRatio;
		OutVT.AspectRatio		= CamActor.AspectRatio;

		// See if the CameraActor wants to override the PostProcess settings used.
		CamOverridePostProcessAlpha = CamActor.CamOverridePostProcessAlpha;
		CamPostProcessSettings = CamActor.CamOverridePostProcess;
	}
	else
	{
		// Give Pawn Viewtarget a chance to dictate the camera position.
		// If Pawn doesn't override the camera view, then we proceed with our own defaults
		if( Pawn(OutVT.Target) == None ||
			!Pawn(OutVT.Target).CalcCamera(DeltaTime, OutVT.POV.Location, OutVT.POV.Rotation, OutVT.POV.FOV) )
		{
			if(TargetDistancePullPercent != DistanceRatio)
			{
				EnableUpdatePlayerHUD(true);
				if(TargetDistancePullPercent > DistanceRatio)
				{
					if(TargetDistancePullPercent - DistanceRatio < TargetDistancePullSpeed * DeltaTime)
					{
						TargetDistancePullPercent = DistanceRatio;
					}
					else
					{
						TargetDistancePullPercent -= TargetDistancePullSpeed * DeltaTime;
					}
				}
				else if(TargetDistancePullPercent < DistanceRatio)
				{
					if(DistanceRatio - TargetDistancePullPercent < TargetDistancePullSpeed * DeltaTime)
					{
						TargetDistancePullPercent = DistanceRatio;
					}
					else
					{
						TargetDistancePullPercent += TargetDistancePullSpeed * DeltaTime;
					}
				}
			}
			// don't apply modifiers when using these debug camera modes.
				
			switch( CameraStyle )
			{
			case 'Fixed'		:	// do not update, keep previous camera position by restoring
				// saved POV, in case CalcCamera changes it but still returns false
				OutVT.POV = OrigPOV;
				break;

			case 'ThirdPerson'	: // Simple third person view implementation
			case 'FreeCam'		:
			case 'FreeCam_Default':
				Loc = OutVT.Target.Location;
				Rot = OutVT.Target.Rotation;

				//OutVT.Target.GetActorEyesViewPoint(Loc, Rot);
				if( CameraStyle == 'FreeCam' || CameraStyle == 'FreeCam_Default' )
				{
					Rot = PCOwner.Rotation;
				}
				Loc += FreeCamOffset >> Rot;


				Pos = Loc - Vector(Rot) * TargetDistancePullPercent;
				// @fixme, respect BlockingVolume.bBlockCamera=false
				HitActor = Trace(HitLocation, HitNormal, Pos, Loc, FALSE, vect(12,12,12));
				OutVT.POV.Location = (HitActor == None) ? Pos : HitLocation;
				OutVT.POV.Rotation = Rot;

				break;

				//---------------------------------------------------------------
				// 自定义摄像机模式开始
				//---------------------------------------------------------------

				//从自定义的Pawn类(MMOPlayer)的GetDefaultCameraMode传来
			case 'Isometric':
				//如果当前正在释放技能，则可能带上相关的镜头动画，则暂时关闭平滑移动跟随
				if( ActiveAnims.Length > 0 && EnableSmoothCameraPos )
				{
					if(EnableDebugMode)
						`log("[MMOPlayerCamera]:PlayingAinm,Follow immediately" @ActiveAnims.Length  );
					//bSmooth=EnableSmoothCameraPos;
					EnableSmoothCameraPos=false;
				}
				//如果技能释放完毕，则恢复默认的镜头跟随状态
				else if( EnableSmoothCameraPos != DefaultSmoothMove )
				{
					EnableSmoothCameraPos = DefaultSmoothMove;
				}
				//修改摄像机朝向
				Rot = CalcRotation( DeltaTime );

				//修改摄像机的位置
				Pos = CalcPosition( Rot, CalcLookAtOffset( Rot ), DeltaTime );

				OutVT.POV.Location = Pos;
				OutVT.POV.Rotation = Rot;
				OutVT.POV.FOV = GetCurrentFOV();

				WorldInfo.DefaultPostProcessSettings.DOF_FocusDistance    = GetDofFocusDistance();
				WorldInfo.DefaultPostProcessSettings.DOF_FocusInnerRadius = GetDofFocusRadius();
				WorldInfo.DefaultPostProcessSettings.DOF_FalloffExponent  = GetDofFalloffExponent();
				WorldInfo.DefaultPostProcessSettings.DOF_MaxFarBlurAmount = GetDofFarMaxFarBlurAmount();
				WorldInfo.DefaultPostProcessSettings.DOF_BlurKernelSize   = GetDofFarBlurKernelSize();
/*
				if( ActiveAnims.Length > 0 )
				{
					EnableSmoothCameraPos=bSmooth;
				}
*/

				break;

				//---------------------------------------------------------------
				// 自定义摄像机模式结束
				//---------------------------------------------------------------

			case 'FirstPerson'	: // Simple first person, view through viewtarget's 'eyes'
			default				:	
				OutVT.Target.GetActorEyesViewPoint(OutVT.POV.Location, OutVT.POV.Rotation);
				break;

			}
		}
	}
	curVT = OutVT;

	//地图读取之后就采取平滑拉近的相机
	if(IsMapJustLoaded)
	{   
		IsMapJustLoaded=false;
		//是否开启区别较大，放在Ini中配置
		EnableSmoothCameraPos=DefaultSmoothMove;
		EnableSmoothCameraRot=true;
		if(EnableDebugMode)
			`log("[MMOPlayerCamera]UpdateViewTarget():EnableSmoothCameraPos" @EnableSmoothCameraPos);
	}
	ApplyCameraModifiers(DeltaTime, OutVT.POV);

	if(PCOwner != none)
	{
		PCOwner.SetLocation(OutVT.POV.Location);
		PCOwner.SetRotation(OutVT.POV.Rotation);
	}

	AfterUpdateTick(DeltaTime);
}

// 拉近镜头
native final function ZoomIn();
// 拉远镜头
native final function ZoomOut();


// 取得当前Dof焦点距离
function float  GetDofLerpParameter()
{
	local bool inMatinee;
	local float par;
	inMatinee = IsInMatinee();
	par       = ( !EnableNearDof && inMatinee ) ? 1.0f : TargetDistancePullPercent;
	return par;
}

function float GetDofFarBlurKernelSize()
{
	local float par;
	par  = GetDofLerpParameter();
	return NearDofFarBlurKernelSize + ( FarDofFarBlurKernelSize - NearDofFarBlurKernelSize )  * par;
}

function float GetDofFarMaxFarBlurAmount()
{
	local float par;
	par  = GetDofLerpParameter();
	return NearDofMaxFarBlurAmount + ( FarDofMaxFarBlurAmount - NearDofMaxFarBlurAmount )  * par;
}

function float GetDofFocusDistance()
{
	local float par;
	par  = GetDofLerpParameter();
	return NearDofFocusDistance + ( FarDofFocusDistance - NearDofFocusDistance )  * par;
}

// 取得当前Dof焦点半径
function float GetDofFocusRadius()
{
	local float par;
	par  = GetDofLerpParameter();
	return NearDofFocusRadius + ( FarDofFocusRadius - NearDofFocusRadius )  * par;
}

// 取得当前dof衰减系数
function float GetDofFalloffExponent()
{
	local float par;
	par  = GetDofLerpParameter();
	return NearDofFalloffExponent + ( FarDofFalloffExponent - NearDofFalloffExponent )  * par;
}

// 取得当前的FOV，根据远近参数线性插值
function float GetCurrentFOV()
{
	return NearFov + (FarFOV - NearFov) * TargetDistancePullPercent;
}

// 取得当前的距离偏移
native final function float GetCurrentDistance();
// {
// 	return TargetDistancePullPercent * (FarCameraDistance -NearCameraDistance) + NearCameraDistance;
// }

// 取得当前的上下look at偏移值
function float GetCurrentLookAtOffset()
{
	return -(NearCameraLookAtOffset + (FarCameraLookAtOffset - NearCameraLookAtOffset) * TargetDistancePullPercent);
}

// 取得当前的PITCH，根据远近参数线性插值
function int GetTargetPitch()
{
	//if(PitchDirty)
	//{
		if( CamNavVolume != none && CamNavVolume.LookAtFrom != none )
		{
			CachedPitch = CamNavVolume.LookAtFrom.Rotation.Pitch;
		}
		else
		{
			CachedPitch = -(NearCameraPitch + (FarCameraPitch - NearCameraPitch) * TargetDistancePullPercent) * DegToUnrRot;
		}

		if(TargetDistancePullPercent == DistanceRatio)
		{
			//PitchDirty = false;
		}
	//}

	return CachedPitch;
}

// 取得当前的YAW，根据远近参数线性插值
function int GetTargetYaw()
{
	local int curYaw;

	if( CamNavVolume != none && CamNavVolume.LookAtFrom != none )
	{
		curYaw = CamNavVolume.LookAtFrom.Rotation.Yaw;
	}
	else
	{
		curYaw = CameraYawOffset * DegToUnrRot;
	}

	return curYaw;
}

function float GetPitchSpeed()
{
	if( CamNavVolume != none )
		return CamNavVolume.PitchSpeed;
	return DefaultPitchSpeed;
}

function float GetYawSpeed()
{
	if( CamNavVolume != none )
		return CamNavVolume.YawSpeed;
	return DefaultYawSpeed;
}

function Rotator CalcRotation( float DeltaTime )
{
	local bool  dirty;
	local Rotator Rot;
	local float deltaPitch, deltaYaw, accuPitch, accuYaw;

	Rot.Roll  = 0.f;
	Rot.Yaw = GetTargetYaw()&0xFFFF; 
	if(Rot.Yaw < 0) 
		Rot.Yaw += 65536;
	Rot.Pitch = GetTargetPitch() & 0xFFFF; 
	if(Rot.Pitch < 0) 
		Rot.Pitch += 65536;

	if( EnableSmoothCameraRot )
	{
		dirty = false;

		if(CameraCache.POV.Rotation.Yaw < 0 || CameraCache.POV.Rotation.Yaw > 65536)
		{
			CameraCache.POV.Rotation.Yaw = CameraCache.POV.Rotation.Yaw%0xFFFF;
			if(CameraCache.POV.Rotation.Yaw < 0)
			{
				CameraCache.POV.Rotation.Yaw += 65536;
			}
		}

		if(CameraCache.POV.Rotation.Pitch < 0 || CameraCache.POV.Rotation.Pitch > 65536)
		{
			CameraCache.POV.Rotation.Pitch = CameraCache.POV.Rotation.Pitch%0xFFFF;
			if(CameraCache.POV.Rotation.Pitch < 0)
			{
				CameraCache.POV.Rotation.Pitch += 65536;
			}
		}

		deltaPitch = Rot.Pitch - CameraCache.POV.Rotation.Pitch;
		deltaYaw = Rot.Yaw - CameraCache.POV.Rotation.Yaw;


		if(deltaPitch > 32768)
		{
			deltaPitch -= 65536;
		}
		else if(deltaPitch < -32768)
		{
			deltaPitch += 65536;
		}
		if(deltaYaw > 32768)
		{
			deltaYaw -= 65536;
		}
		else if(deltaYaw < -32768)
		{
			deltaYaw += 65536;
		}

		accuPitch = GetPitchSpeed() * DeltaTime;
		if( abs( deltaPitch ) > accuPitch )
		{
			if( deltaPitch < 0 )
			{
				Rot.Pitch = CameraCache.POV.Rotation.Pitch - accuPitch;
			}
			else
			{
				Rot.Pitch = CameraCache.POV.Rotation.Pitch + accuPitch;
			}
			dirty = true;
		}
		accuYaw = GetYawSpeed() * DeltaTime;
		if( abs( deltaYaw ) > accuYaw )
		{
			if( deltaYaw < 0 )
				Rot.Yaw = CameraCache.POV.Rotation.Yaw - accuYaw;
			else
				Rot.Yaw = CameraCache.POV.Rotation.Yaw + accuYaw;
			dirty = true;
		}

		if( !dirty )
		{
			PitchDirty = false;
		}
	}
	return Rot;
}

function Vector CalcLookAtOffset( Rotator CurrRot )
{
	local Rotator offsetRot;
	local Vector lookat;

	if( CamNavVolume != none && CamNavVolume.FixCamera )
	{
		lookat = CamNavVolume.GetLookAtPosition( PCOwner.Pawn.Location );
	}
	else
	{
		offsetRot.Yaw = CurrRot.Yaw;
		offsetRot.Pitch = 0;
		offsetRot.Roll = 0;

		if(PCOwner.Pawn != none)
		{
			lookat = PCOwner.Pawn.Location 
				+ Vector(offsetRot) * GetCurrentLookAtOffset();
		}
		//`Log("[CalcLookAtOffset]"@offsetRot.Yaw @GetCurrentLookAtOffset());
	}

	return lookat;
}

function Vector CalcPosition( Rotator CurrRot, Vector LookAt, float DeltaTime )
{
	local Vector Pos, Diff,nDiff,RotPos;
	local float fDiffLength;
	local float accuMove;
	local float fRealMoveSpeed;
	local LinearColor LColor;
	local Color C;
	//LooAt为当前相机观察目标的位置 Pos为期望相机所处位置
	Pos = LookAt - Vector(CurrRot) * GetCurrentDistance();

	//`log("_______ CalcPosition");
	// 只有在不拉镜头时才进行平滑跟随
	if( EnableSmoothCameraPos && (DistanceRatio == self.TargetDistancePullPercent))
	{
		//`log("_______ EnableSmoothCameraPos");

		Diff = Pos - CameraCache.POV.Location;
		fDiffLength=vsize( Diff );
		if( fDiffLength < 1.0f )
			return Pos;

		if(fDiffLength > 256.0f)		
		{
			return Pos;
		}

		fRealMoveSpeed = fDiffLength*DefaultMoveScale+DefaultMoveSpeed;
		accuMove = DeltaTime * fRealMoveSpeed;
		if( ( accuMove < fDiffLength ) && ( accuMove > 1.0f ) && ( fRealMoveSpeed > 0.0f ) )
		{
			if( EnableDebugMode && vLastTargetPos != Pos )
			{
				LColor.A = 1.0;
				LColor.R = 1.0;
				LColor.G = 0;
				LColor.B = 0;
				DrawDebugPoint(LookAt, 5, LColor, true);
				LColor.A = accuMove/fDiffLength;
				LColor.R = 0.0;
				LColor.G = 1.0;
				//期望移动到的位置
				RotPos = Pos+Normal( Vector( CurrRot ) )*1400;
				DrawDebugLine (Pos,RotPos,0,255,0,true);
				DrawDebugPoint(Pos, 10, LColor, true);
				C.R = 255;
				C.G = 0;
				C.B = 255;
				DrawDebugCone(Pos, Normal( Vector( CurrRot ) ), 60, 3.0, 3.0,32,C, true);
			}
			nDiff = normal(Diff);
			Pos=CameraCache.POV.Location+accuMove*nDiff;
			if( EnableDebugMode )
			{
				//LColor.R =RandRange(0,1);
				LColor.G=0;
				LColor.B = 1.0;
				//实际移动到的位置
				C.R = 255;
				C.G = 255;
				C.B = 0;
				C.A = 255;
				DrawDebugCone(Pos, nDiff,10, 3.0, 3.0,32,C, true);
				DrawDebugPoint(Pos, 5, LColor, true);
			}
			if( EnableDebugMode )
			{   		
				`Log("[MMOPlayerCamera]DiffLen_RealSpeed_AccuMove:"@fDiffLength@fRealMoveSpeed@accuMove@"Pos_Dir:"@Pos@nDiff);
				`Log("[BeginPos：]"@CameraCache.POV.Location);
			}
		}
		else
		{
			//如果速度过大，则放弃平滑计算，直接移动到目标位置
			if( EnableDebugMode )
				`Log("[MMOPlayerCameraJump] fDiffLength fRealMoveSpeed accuMove" @accuMove@fDiffLength@fRealMoveSpeed);
		}
	}
	vLastTargetPos=Pos;

	return Pos;
}

unreliable client event ClientPlayCameraAnim( CameraAnim AnimToPlay, optional float Scale=1.f, optional float Rate=1.f,
						optional float BlendInTime, optional float BlendOutTime, optional bool bLoop,
						optional bool bRandomStartTime, optional ECameraAnimPlaySpace Space=CAPS_CameraLocal, optional rotator CustomPlaySpace )
{
	local CameraAnimInst AnimInst;
/*
	`Log("[MMOPlayer]:Stop play Anim!");
	return;*/
	AnimInst = PlayCameraAnim(AnimToPlay, Rate, Scale, BlendInTime, BlendOutTime, bLoop, bRandomStartTime);
	if (AnimInst != None && Space != CAPS_CameraLocal)
	{
		AnimInst.SetPlaySpace(Space, CustomPlaySpace);
	}
}

//function ClearHiddenList()
//{
//	local int i;
//	for(i = 0; i < HiddenActorList.Length; ++i)
//	{
//// 		HiddenActorList[i].SetHidden(false);
//// 		HiddenActorList[i].SetCollision(true, true, true);
//	}
//}

native final function bool HasHidden(Actor actor);
native final function bool IsUnHiding(Actor actor, out int idx);
native final function CheckStaticMeshToHide(float deltaTime);
native final function NativeTick(float deltaTime);
native final function UnHiddenAll();
native final function bool IsInMatinee();

event Tick(float deltaTime)
{
	super.Tick(deltaTime);
	NativeTick(deltaTime);
}

DefaultProperties
{
	DefaultYawSpeed=16384
	DefaultPitchSpeed=16384
	PitchDirty=true
	CheckHiddenActorTime=0.2f

	//DefaultCameraActor=none
	isCameraActorImmediatly=true
	TargetDistancePullSpeed=0.5
	EnableSmoothCameraPos=true
	EnableSmoothCameraRot=true

	CameraStyle=Isometric

	//NearDofFocusDistance = 700
	//NearDofFocusRadius    = 1200
}
