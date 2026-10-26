//
// 玩家类
//
class MMOPlayer extends MMOActor implements(IMMOActorHUD, IInteractableActor)
	dependson(NPC)
	placeable
	config(MMOGame)
	native
	hidecategories(Object,Advanced,Attachment,Display,Debug,Camera,AI);

//------------------------------------------------------------
// 过场动画
//------------------------------------------------------------
//var Actor TargetMatineeActor;
//var EPhysics PhysicsBeforeMatinee;
//var AnimTree AnimTreeBeforeMatinee;
//var array<AnimSet> AnimsBeforMatinee;

var transient bool IsInMatinee;
//var transient Vector BeforMatineeLocation;
//var transient Rotator BeforMatineeRotation;
 

//---------------------------------------------------------------
// 网络协议相关变量
//---------------------------------------------------------------
var init string UserId;

//`define USE_CLOTHING_SET    true;   // macro that controls whether to use avatar pieces or not

//var SkeletalMeshComponent   HairMesh;
//var SkeletalMeshComponent   FaceMesh;

var	bool        ShowManteau;

var bool        SuitMode;
//var() string	ActorName      <DisplayName="玩家名字">;

var(MMOPlayer) bool    IsMale									<DisplayName="IsMale">;
var(MMOPlayer) bool  bShowAvatar								<DisplayName="ShowAvatar">;
var(MMOPlayer) int nShowAvatarClassID							<DisplayName="ShowAvatarClassID">;
//在连击中是否可以转向
var(MMOPlayer) bool CanRotWhenCombo								<DisplayName="CanRotWhenCombo">;


// 轻功最大距离
var(MMO) float MaxFlyDistance									<DisplayName="MaxFlyDistance">;

//自动检测随机动作时间
var transient float LeftTimeToCheckAboutRestAnim;
var transient float TimeToCheckAboutRestAnim;

//临时属性
//var(MMO) bool bMale <DisplayName="是男性么">;

//是否在安全区
var bool IsInSafeZone;
var bool IsInFreePkZone;

//var Vector AbilityDir;
var Vector TargetLocation;

// 缓冲的技能，只能缓冲一次
//var Ability BufferAbility;
var int BufferAbility;

// 连击计时
var float ComboCD;

// 连击数
var int ComboCount;



//队伍管理器
//var TeamManager TeamManager;
//战场管理器
//var BattleManager BattleMgr;

//好友聊天的管理器
//var MMOFriendChatManager    FriendChatManager;

//初始位置，角度
var vector OrignPos;
var rotator OrignRot;

// 在此时间内击中怪物算连击
var(MMOCombo) float MaxComboTime	<DisplayName="MaxComboTime">;


var bool DrawDebugRange;

// wind source strength
var config float PlayerWindStrength;

//var config float PlayerLightHeight;
//enum eLifeState{
//	eDoingNoting,
//	eApplyTradeP2P,
//	eReplyTradeP2P,
//	eDoTradeP2P,
//	eLockTradeP2P
//};
//var eLifeState LifeState;
var bool IsFighting;
var bool IsTrading;
var int PrisonTerm;

var int  VipType;

// 摆摊相关
var init string StallName;
var int StallLevel;
// 摊位等级不同，模型不同
var config string StallMeshName1;
var config string StallMeshName2;

var config string PlayerLevelUpEffect;  // 升级特效
var config string PlayerReviveEffect;   // 复活特效
var config string PlayerTeleportLeaveEffect; // 传出特效
var config string PlayerTeleportEnterEffect; // 传入特效
var config string PlayerSkillLearnedEffect; // 技能获得特效
var config string PlayerSkillLevelUpEffect; // 技能升级特效
var config string PlayerAchievementEffect;  // 成就达成特效
var config string SabacStatueEffect;  // 沙巴克雕像特效
var config string PlayerGainExtraExpEffect; //历练经验获得
//加个元宝
var int RealMoney;


var bool bRelevant;

// 任务 #21843
// 主角的武器升级点数是通过玩家武器道具属性计算的，但是其他玩家的是服务器单独发过来的
// 这里统一记在玩家身上
var int WeaponUpgradePoint;
var config int WeaponUpgradeTopLevel;

enum OperationMaterialAniState
{
	eOperationAnimationStateInvalid,
	eOperationAnimationStateStart,
	eOperationAnimationStateLoop,
	eOperationAnimationStateEnd,
};

var int NextOperationMaterialState;

native function string GetActorName();

native function vector GetInteractActorLocation();
native function float GetMaxInteractRadius();
native function DoInteract();
native function bool CanInteract() const;
native function SetSilhouette( bool show, Vector sc = vect( 1.f, 1.f, 0.f ) );

native function RefreshCollision();		//Bruce@snda


// 初始化函数
simulated event PostBeginPlay()
{
	//local LightingChannelContainer lcc;
	//local MMOActorMaterialController matCtrl;

	//`Log("[MMO]: MMOPlayer Init"@ name);

	
	ActorAttributes = new(self) class'ActorAttribute'(ActorAttributes);

	super.PostBeginPlay();
	
	//lcc.CompositeDynamic = true;
	//lcc.Dynamic = false;
	//Mesh.SetLightingChannels(lcc);

	HealthMax = ActorAttributes.GetMaxHp();
	Health = ActorAttributes.GetCurHp();


	//TeamManager = new class'TeamManager';
	//BattleMgr = new class'BattleManager';
	//FriendManager = new class'FriendManager';

	SuitMode = false;

	CylinderComponent.SetActorCollision(true, false);

	
//	Mesh.SetActorCollision( true, false );
///////////////////////////////////////////////////////////////
//	CylinderComponent.SetActorCollision( true, true );
//	CylinderComponent.SetBlockRigidBody( true );
//	//CollisionComponent = Mesh; // bug: ???
//	CollisionComponent.AddRadialForce( vect(0,0,0), 200, 50, 0 );
//	Mesh.SetActorCollision( true, false );
//	Mesh.SetTraceBlocking( true, true );
//	Mesh.PhysicsWeight = 0.5;
//	Mesh.ForceSkelUpdate();

//	Mesh.bEnableFullAnimWeightBodies = true;
//	if(Mesh.PhysicsAssetInstance != none)
//	{
//		//Mesh.PhysicsAssetInstance.SetAllBodiesFixed( false );
//		Mesh.PhysicsAssetInstance.SetFullAnimWeightBonesFixed(false, Mesh);
//	}

//	Mesh.SetNotifyRigidBodyCollision( true );
//	Mesh.WakeRigidBody();
/////////////////////////////////////////////////////////



	//OnBladeInOut();

	if(WorldInfo.IsPlayInEditor()
		|| WorldInfo.IsPlayInPreview()
		|| WorldInfo.IsPlayInMobilePreview())
	{
		CheckActorLight();
	}
	
	AddInteractiveWind( PlayerWindStrength );

	if( IsMainPlayer() || WorldInfo.IsPlayInEditor() )
	{
		// use full speed update for self
		//LightEnvironment.bRequiresNonLatentUpdates = true; // this method will cause visual blink
		LightEnvironment.MinTimeBetweenFullUpdates = 0.1;
	}
}


simulated event Destroyed()
{
	super.Destroyed();
	//class'MMOHUD'.static.RemoveDrawHUD(self);
}

simulated event OutsideWorldBounds()
{
	if(IsMainPlayer())
	{
		SetPhysics(PHYS_None);
	}
	else
	{
		super.OutsideWorldBounds();
	}
}

final native function SetInFighting( bool isNowFighting );
final native function bool IsInFighting();

final native function SetInTrading( bool isNowTrading );
final native function bool IsInTrading();

final native function SetPrisonTerm( int sec );
final native function int GetPrisonTerm();
final native function bool IsInPrison();

native function SetVip( int curVipType );
native function int GetVipType();

native function PlayRandomAnim();

native function ProcessDefaultDie(byte DieCause);

native function EPickPriority GetPickPriority();

event SetRevive()
{
	super.SetRevive();
	//直接调用 经常其他MMOActor挂了会跑到这里
	//MMOGame(WorldInfo.Game).EnableDeathEffects( false );

	if( ItemManager != none )
	{
		ItemManager.ApplySkinColor( ItemManager.CurrentSkinColorIdx );
		ItemManager.ApplyHairColor( ItemManager.CurrentHairColorIdx );
	}
}
event EndDeathEffect()
{
	MMOGame(WorldInfo.Game).EnableDeathEffects( false );
}

event SetPlayerRBChannels()
{
	if(IsMainPlayer())
	{
		Mesh.SetRBChannel(RBCC_Untitled1);
// 		Mesh.SetRBCollidesWithChannel(RBCC_Default,TRUE);
// 		Mesh.SetRBCollidesWithChannel(RBCC_Pawn,TRUE);
// 		Mesh.SetRBCollidesWithChannel(RBCC_Vehicle,TRUE);
// 		Mesh.SetRBCollidesWithChannel(RBCC_Untitled3,FALSE);
// 		Mesh.SetRBCollidesWithChannel(RBCC_BlockingVolume,TRUE);
//		Mesh.SetRBCollidesWithChannel(RBCC_Untitled2,TRUE);
	}
	else
	{
		Mesh.SetRBChannel(RBCC_Untitled2);
		//Mesh.SetRBCollidesWithChannel(RBCC_Default,TRUE);
		//Mesh.SetRBCollidesWithChannel(RBCC_Pawn,TRUE);
		//Mesh.SetRBCollidesWithChannel(RBCC_Vehicle,TRUE);
		//Mesh.SetRBCollidesWithChannel(RBCC_Untitled3,FALSE);
		//Mesh.SetRBCollidesWithChannel(RBCC_BlockingVolume,TRUE);
//		Mesh.SetRBCollidesWithChannel(RBCC_Untitled1,TRUE);
	}
}

function CheckActorLight()
{
	local MMOMapInfo mapInfo;
	local Vector lightPos;

	SetPlayerRBChannels();

	if(IsMainPlayer())
	{	
		mapInfo = MMOMapInfo(WorldInfo.GetMapInfo());
		if(mapInfo != none)
		{
			if(mapInfo.ActorPointLight != none)
			{
				lightPos = GetSocketWorldPosition('PlayerLight');
				//lightHight.Z = PlayerLightHeight;
				mapInfo.ActorPointLight.SetLocation(lightPos);
				mapInfo.ActorPointLight.SetBase(self);
			}
		}
	}
}



event RigidBodyCollision( PrimitiveComponent HitComponent,
	PrimitiveComponent OtherComponent,
	const out CollisionImpactData RigidCollisionData,
	int ContactIndex )
{
	super.RigidBodyCollision(HitComponent, OtherComponent, RigidCollisionData, ContactIndex);
	//`log("________XXXXXXXXXXXXXXX Player RigidBodyCollision");
}


function DetachFromController( optional bool bDestroyController )
{
	//`log("________XXXXXXXXXXXXXXX Player DetachFromController");
	
	//ScriptTrace();
	super.DetachFromController(bDestroyController);
}


event EncroachedBy( actor Other )
{
	//// Allow encroachment by Vehicles so they can push the pawn out of the way
	//if ( Pawn(Other) != None && Vehicle(Other) == None )
	//	gibbedBy(Other);
}

// 设置默认相机模式为Isometric
simulated function name GetDefaultCameraMode( PlayerController RequestedBy )
{
	`Log("[MMO]: Default camera mode Isometric");
	return 'Isometric';
}

// 玩家死亡时不要丢出武器
function ThrowWeaponOnDeath()
{
}

/**
 */
function ShowNormalClothes( bool bShow )
{
}

/**
 */
function ShowSuit( bool bShow )
{
}

/**
 */
function ToggleSuitMode( )
{
	if( SuitMode )
	{   // switch to normal mode
		ShowNormalClothes( true );
		ShowSuit( false );
		SuitMode = false;
	}
	else
	{   // switch to suit mode
		ShowNormalClothes( false );
		ShowSuit( true );
		SuitMode = true;
	}
}

/**
 * the weapon effects would be better follow the weapons
 */
//function AttachParticles( EWeaponHoldingType eHoldingType, ParticleSystem particles )
//{
//	local ParticleSystemComponent pc;
//	switch( eHoldingType )
//	{
//	case EWHT_SINGLE:
//		pc = new( self ) class'ParticleSystemComponent';
//		//WeaponSlot[1] = pc;
//		pc.SetTemplate(particles);
//		pc.ActivateSystem(true);				
//		Mesh.AttachComponentToSocket( pc, 'SFX_WeaponR' );
//		break;
//	case EWHT_DOUBLE:
//		break;
//	default:
//		break;
//	}
//}
// 
// event HoldUpStone()
// {
// 	MMOPlayerController( controller ).HoldUpStone();
// }
// 
// event ThrowStone()
// {
// 	MMOPlayerController( controller ).ThrowStone();
// }
// 
// event DropStone()
// {
// 	MMOPlayerController( controller ).DropStone();
// }

function ClimbLadder(LadderVolume L)
{
	// `log("!@@@@@@@@@@@ Climb Ladder");
	//super.ClimbLadder(L);

	OnLadder = L;
	Controller.ClientSetRotation(OnLadder.WallDir);

	SetPhysics(PHYS_Ladder);
	
	Controller.PushState('Climbing');
}

// 进入安全区
//native function OnEnterSafeZone();
//{
//	 `log("Debug: +++++++++++++++++ Enter MMOVolume_SafeZone" @self);
//	IsInSafeZone = true;
//	if(bHoldWeapon)
//	{
//		//BladeInOutNode.PlayAnim(false, 1, 0);
//		PlayAnimation( 'blade_in_out');
//	}
//}

// 离开安全区
//native function  OnLeavingSafeZone();
//{
//	 `log("Debug: ----------------- Leave MMOVolume_SafeZone" @self);
//	IsInSafeZone = false;
//	MakeBladeInAfterIdle = 0.0f;


//	if(!bHoldWeapon)
//	{
//		//BladeInOutNode.PlayAnim(false, 1, 0);
//		PlayAnimation( 'blade_in_out');
//	}
//}

//刷新武器绑定骨骼
native function ReflashWeaponSocket();

native function RefreshCombatPose();

//// 抽刀/拔刀
//event OnBladeInOut()
//{
//	if(IsInSafeZone)
//	{
//		if(ItemManager != none)
//		{
//			ItemManager.RequestHoldWeapon(false);
//		}
//	}
//	else
//	{
//		if(ItemManager != none)
//		{
//			ItemManager.RequestHoldWeapon(true);
//		}
//	}
//	IsBladeIn = !bHoldWeapon;
//}


simulated event Tick( float deltaTime )
{
	// local int idx;
	super.Tick(deltaTime);


	if(ComboCD > 0)
	{
		ComboCD -= deltaTime;

		if(ComboCD <= 0)
		{
			OnComboEnd();
		}
	}
	

	//// 如果有缓冲技能并且当前技能可以接下招就
	//if(HasBufferAbility()
	//	&& ActiveAbility.CanComboNext())
	//{
	//	ActiveAbility.OnEnd();
	//	//UseAbility(BufferAbility);
	//	//ClearBufferAbility();
	//}
}

//event TakeDamages(DamageResult dmg, Controller EventInstigator, vector HitLocation, vector Momentum, class<DamageType> DamageType, optional TraceHitInfo HitInfo, optional Actor DamageCauser)
//{
//	//// `log("[MMO] Player take damage!");

//	super.NotifyTakeHitEx( EventInstigator, HitLocation, abs(dmg.HPChange), DamageType, Momentum, dmg );
//	//let add 
//	if(MMOHud(MMOPlayerController(Controller).myHUD).HudMovie != none && Abs(dmg.HPChange)>0 )
//	{
//		//`log("@@@@HP"@dmg.HPChange);
//		MMOHud(MMOPlayerController(Controller).myHUD).HudMovie.CallShotText( string(dmg.HPChange),0xff0000,0xffff00,580,310,15,0,-5,0,-100);
//		//HudMovie.CallShotText( "未击中",0xff0000,0xffff00,screenPos.X, screenPos.y,15,0,-5,0,-100 ); 
//	}
//}

function Vector GetAbilityTargetDirection( )
{
	local Vector actorDir;
	
	actorDir = Normal(MMOPlayerController(Controller).MouseHitWorldLocation - Location);

	actorDir.Z = 0; // 不要在高度上变化

	return actorDir;
}

function Vector GetAbilityTargetLocation( )
{
	return TargetLocation;
}


//replication
//{
//	if (Role == ROLE_Authority)
//		bEnabled;
//}

//simulated event ReplicatedEvent(name VarName)
//{
//	// `log("MMO Player ReplicatedEvent:" @VarName);

//	if (VarName == 'bEnabled')
//	{
//		ActorLight.SetEnabled(bEnabled);
//	}
//	else
//	{
//		Super.ReplicatedEvent(VarName);
//	}
//}

function bool HasBufferAbility()
{
	return BufferAbility != -1;
}

function ClearBufferAbility()
{
	BufferAbility = -1;
}

// 连击数变化，一般就是连中时更新
event OnComboChanged(int currentHit)
{
	//++ComboCount;
	// `log("______Combo:" @currentHit);
	if(MMOHud(MMOPlayerController(Controller).myHUD).HudMovie != none)
	{
		MMOHud(MMOPlayerController(Controller).myHUD).HudMovie.CallSetCombo( currentHit );
	}
}

// 连击结束，隐藏显示界面
event OnComboEnd()
{
	ComboCount = 0;
}

// 增加连击数
event IncrementCombo()
{
	// 连中之后延长时间
	ComboCD = MaxComboTime;
	++ComboCount;

	if(ComboCount > 0)
	{
		OnComboChanged(ComboCount);
	}
}

event Falling()
{
	//`log("MMOPlayer::Falling");
	super.Falling();

	//Controller.GotoState('FallingEx');
}


function bool OnlyDrawHUDForOwner(){return false;}

native function DrawHUDPostGFx( HUD H );

native function bool DrawMyHUD( MMOHud H );
//{
//	local Vector screenPos;
//	//local float healthPercent;
//	//local LinearColor healthColor;
//	//local Vector healthColorVec;
//	local Vector objectIconWorldPos;
//	//local float cameraDistFromPos;
//	//local float iconWidth, iconHeight;
//	//local float IconDistanceScale;
//	local int drawX, drawY;
//	local int i, j;
//	local Vector drawStart, drawEnd;
//	local float radius;


//	if(bHidden)
//	{
//		return true;
//	}

//	if(DrawDebugRange)
//	{
//		for(i = 0; i < 6; ++i)
//		{
//			radius = (i + 1) * 500;
//			for(j = 1; j < 16; ++j)
//			{
//				drawStart.X = Location.X + Cos(DegToRad * (j - 1) / 360) * radius;
//				drawStart.Y = Location.X + Sin(DegToRad * (j - 1) / 360) * radius;
//				drawStart.Z = Location.Z;

//				drawEnd.X = Location.X + Cos(DegToRad * j / 360) * radius;
//				drawEnd.Y = Location.X + Sin(DegToRad * j / 360) * radius;
//				drawEnd.Z = Location.Z;

//				H.Draw3DLine(drawStart,  drawEnd, MakeColor(255, 0, 0, 255));
//			}
//		}
//	}

//	objectIconWorldPos = Location;//(HealthBarPositionOffset>>Rotation);//实际位置
//	objectIconWorldPos.Z += 120;
//	screenPos = H.Canvas.Project(objectIconWorldPos);

//	if(MMOGame(WorldInfo.Game).DrawDebugActorState)
//	{
//		H.Canvas.SetDrawColor(255, 0, 0, 255);

//		//drawY = screenPos.y - iconHeight/2;
//		//drawX = screenPos.x - iconWidth/2;
//		drawX = screenPos.X;
//		drawY = screenPos.Y;

//		H.Canvas.SetPos(drawX, drawY);
//		H.Canvas.DrawText("[" $ ServerID $ "]" $ " RoleName:[" $ RoleName $ "]UserID:["
//			$ UserID $ "] " $ Controller.GetStateName()
//			 $ "]");

//		//drawY -= 20;
//		//H.Canvas.SetPos(drawX, drawY);
//		//H.Canvas.DrawText("[" $ GetPhysicsName() $ "]" $ "[" $ CollisionType $ "]" $ "[" $ Mesh.RBChannel $ "]");

//		//drawY -= 20;
//		//H.Canvas.SetPos(drawX, drawY);
//		//H.Canvas.DrawText("BlockingVolume = [" $ Mesh.RBCollideWithChannels.BlockingVolume $ "] Cloth = [" $ Mesh.RBCollideWithChannels.Cloth $ "]");

//		//drawY -= 20;
//		//H.Canvas.SetPos(drawX, drawY);
//		//H.Canvas.DrawText("Clothing = [" $ Mesh.RBCollideWithChannels.Clothing $ "] ClothingCollision = [" $ Mesh.RBCollideWithChannels.ClothingCollision $ "]");

//		//drawY -= 20;
//		//H.Canvas.SetPos(drawX, drawY);
//		//H.Canvas.DrawText("DeadPawn = [" $ Mesh.RBCollideWithChannels.DeadPawn $ "] Default = [" $ Mesh.RBCollideWithChannels.Default $ "]");

//		//drawY -= 20;
//		//H.Canvas.SetPos(drawX, drawY);
//		//H.Canvas.DrawText("EffectPhysics = [" $ Mesh.RBCollideWithChannels.EffectPhysics $ "] FluidDrain = [" $ Mesh.RBCollideWithChannels.FluidDrain $ "]");

//		//drawY -= 20;
//		//H.Canvas.SetPos(drawX, drawY);
//		//H.Canvas.DrawText("FracturedMeshPart = [" $ Mesh.RBCollideWithChannels.FracturedMeshPart $ "] FluidDrain = [" $ Mesh.RBCollideWithChannels.GameplayPhysics $ "]");

//		//drawY -= 20;
//		//H.Canvas.SetPos(drawX, drawY);
//		//H.Canvas.DrawText("Nothing = [" $ Mesh.RBCollideWithChannels.Nothing $ "] Pawn = [" $ Mesh.RBCollideWithChannels.Pawn $ "]");

//		//drawY -= 20;
//		//H.Canvas.SetPos(drawX, drawY);
//		//H.Canvas.DrawText("Untitled1 = [" $ Mesh.RBCollideWithChannels.Untitled1 $ "] Untitled2 = [" $ Mesh.RBCollideWithChannels.Untitled2 $ "]");

//		//drawY -= 20;
//		//H.Canvas.SetPos(drawX, drawY);
//		//H.Canvas.DrawText("Untitled3 = [" $ Mesh.RBCollideWithChannels.Untitled3 $ "] Untitled4 = [" $ Mesh.RBCollideWithChannels.Untitled4 $ "]");

//		//drawY -= 20;
//		//H.Canvas.SetPos(drawX, drawY);
//		//H.Canvas.DrawText("Vehicle = [" $ Mesh.RBCollideWithChannels.Vehicle $ "] Water = [" $ Mesh.RBCollideWithChannels.Water $ "]");

//	}

//	return true;
//}


native function OnAnimEndNative(AnimNodeSequence SeqNode, float PlayedTime, float ExcessTime);

event OnAnimEnd(AnimNodeSequence SeqNode, float PlayedTime, float ExcessTime)
{
	super.OnAnimEnd(SeqNode,PlayedTime,ExcessTime );

}

state ShowAvatar
{
	
	event BeginState( name PreviousStateName )
	{
		super.BeginState( PreviousStateName );		
		if(ItemManager != none)
		{
			ItemManager.RequestHoldWeapon(true);
		}
		Mesh.RootMotionMode=RMM_Ignore;
		OrignPos = Location;
		OrignRot = Rotation;
	}

	event EndState( name NextStateName )
	{
		super.EndState( NextStateName );
	}
}

native final function PlayLevelUpEffect(Vector inLoc, Rotator inRot);
native final function PlayAchievementEffect(Vector inLoc, Rotator inRot);
native final function PlaySkillLearnedEffect(Vector inLoc, Rotator inRot);
native final function PlaySkillLevelUpEffect(Vector inLoc, Rotator inRot);
native final function PlayTeleportLeaveEffect(Vector inLoc, Rotator inRot);
native final function PlayTeleportEnterEffect(Vector inLoc, Rotator inRot);
native final function PlayReviveEffect(Vector inLoc, Rotator inRot);
native final function PlaySabacStatueEffect(Vector inLoc, Rotator inRot);
native final function PlayGainExtraExpEffect(Vector inLoc, Rotator inRot);

native final function int GetMoney(EMONEY_TYPE MoneyType);

//重新登录后，重置数据
native final function ResetData();

// modified by zhangrui05
native final function OpenStall();
native final function CloseStall();

DefaultProperties
{
	ActorAttributes=ActorAttribute'Player.Player_Attribute'


	FriendlyMask=2
	LeftTimeToCheckAboutRestAnim = 0;
	TimeToCheckAboutRestAnim = 9.0;

	////删除场景内原有的元素
	//Components.Remove(Sprite)
	////创建动态环境光照对象--用于InitialSkeletalMesh对象(使用LightEnvironment成员赋值)
	//Begin Object Class=DynamicLightEnvironmentComponent Name=InitLightEnvironment
	//  ModShadowFadeoutTime=0.25
	//  MinTimeBetweenFullUpdates=0.2
	//  AmbientGlow=(R=.01,G=.01,B=.01,A=1)
	//  AmbientShadowColor=(R=0.15,G=0.15,B=0.15)
	//  LightShadowMode=LightShadow_ModulateBetter
	//  ShadowFilterQuality=SFQ_High
	//  bSynthesizeSHLight=TRUE
	//End Object

	////添加进组件库
	//Components.Add(InitLightEnvironment)

	//Begin Object Class=SpriteComponent Name=Sprite2
	//	Sprite=Texture2D'EditorResources.S_Emitter'
	//	HiddenGame=False
	//	Translation=(X=50,Z=0)
	//	AlwaysLoadOnClient=False
	//	AlwaysLoadOnServer=False
	//	bIsScreenSizeScaled=True
	//	ScreenSize=0.0025
	//End Object
	//Components.Add(Sprite2)

	//clothing system
	Begin Object Class=SkeletalMeshComponent   Name=MasterMesh     // master piece pour caching animations
		//SkeletalMesh=SkeletalMesh'MMO_Player_Body.man_body'
		//AnimSets.Add(AnimSet'Demo_Characters.Anim.Man_Run')
		////AnimSets.Add(AnimSet'Demo_Characters_ManAnim.man_melee01')
		//AnimSets.Add(AnimSet'man_fight.amin.man_fight');
		//AnimSets.Add(AnimSet'man_fight.Melee_Normal');
		//AnimSets.Add(AnimSet'man_fight.Melee_Round');
		//Animations=none
		//AnimTreeTemplate=AnimTree'MMO_PlayerAnim.Anim.Man_AnimTree'
		//PhysicsAsset=PhysicsAsset'MMO_PlayerAnim.Anim.SK_MMO_Player_Physics'
		bUpdateSkelWhenNotRendered=false
		
		//LightingChannels=(BSP=TRUE,Static=FALSE,Dynamic=FALSE,CompositeDynamic=TRUE,bInitialized=TRUE)
		LightingChannels=(Gameplay_1=TRUE)
		bNotifyRigidBodyCollision=true
		ScriptRigidBodyCollisionThreshold=0.001

		bCacheAnimSequenceNodes=FALSE
		AlwaysLoadOnClient=true
		AlwaysLoadOnServer=true
		//bOwnerNoSee=true
		CastShadow=false
		BlockRigidBody=TRUE
		//bUpdateSkelWhenNotRendered=false
		bIgnoreControllersWhenNotRendered=TRUE
		bUpdateKinematicBonesFromAnimation=true
		bCastDynamicShadow=true
		//LightEnvironment=LightEnvironment
		bOverrideAttachmentOwnerVisibility=true
		bAcceptsDynamicDecals=FALSE
		//AnimTreeTemplate=AnimTree'CH_AnimHuman_Tree.AT_CH_Human'
		bHasPhysicsAssetInstance=false
		TickGroup=TG_PreAsyncWork
		RootMotionMode=RMM_Ignore
		//MinDistFactorForKinematicUpdate=0.0
		//bChartDistanceFactor=true
		//bSkipAllUpdateWhenPhysicsAsleep=TRUE
		//RBDominanceGroup=20
		//MotionBlurScale=0.0
		//bAllowAmbientOcclusion=FALSE
		// Nice lighting for hair
		//bUseOnePassLightingOnTranslucency=TRUE
		//bEnableFullAnimWeightBodies=true
	End Object
	Mesh=MasterMesh
	//CollisionComponent=MasterMesh
	Components.Add( MasterMesh )

	// has a bug that makes the player too bright in shadow
	Begin Object Name=MyLightEnvironment
		bSynthesizeSHLight=TRUE	// ENABLED FOR PLAYER
	End Object

	bCanPickupInventory=true
	bCanClimbLadders=true

	// 轻功默认10米
	MaxFlyDistance=1000.0f

	BlockRigidBody=true
	//_Exp=0

	IsInSafeZone=false
	IsInFreePkZone=false
	IsFighting=false
	IsTrading=false
	BufferAbility=-1

	MaxComboTime=2

	IsMale=false

	isDivideBody=true
	bShowAvatar=false
	nShowAvatarClassID=0
	bPushedByEncroachers=false
	CanRotWhenCombo=false

	PickPriority=EPP_Normal

	bMovable=TRUE
	bStatic=FALSE
	bHardAttach=TRUE
	//TeamManager=none
	//FriendManager=none
	//BattleMgr=none
	StallLevel=0
	ActorType=EACT_NONE

	RealMoney = 0
	bRelevant=false
	WeaponUpgradePoint=0
	CurBlockType=1

	NextOperationMaterialState=eOperationAnimationStateInvalid
}
