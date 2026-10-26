
class MMOVolume_Trigger extends TriggerVolume implements(IUniqueID)//implements(IServerArea)
	placeable
	native
	hidecategories(Object, Attachment, Physics, Advanced, Debug, Mobile, Volume);

enum EVolumeTriggerType
{
	EVTT_Trigger <DisplayName="EVTT_Trigger">,				//Trigger区
	EVVT_PKType <DisplayName="EVVT_PKType">,				//Pk区类型
	EVVT_StallZone <DisplayName="EVVT_StallZone">,			//摆摊区
	EVVT_Surface <DisplayName="EVVT_Surface">,				//地表类型
	EVVT_QuestZone <DisplayName="EVVT_QuestZone">,			//区域触发任务
	EVVT_Door <DisplayName="EVVT_Door">,					//Door
	EVVT_Guide <DisplayName="EVVT_Guide">,					//区域触发引导
	EVVT_Mine <DisplayName="EVVT_Mine">,					//可以挖矿
	EVVT_CannotTeleport <DisplayName="EVVT_CannotTeleport">,//禁止传送
	EVVT_CannotLoseItem <DisplayName="EVVT_RoleCannotLoseItem">,//玩家爆装备
	EVVT_CannotDropItem <DisplayName="EVVT_RoleCannotDropItem">,//玩家扔装备
	EVVT_NpcCannotDropItem <DisplayName="EVVT_CannotDropItem">,//Npc扔装备
	EVVT_SlayerArea <DisplayName="EVVT_SlayerArea">,		//屠杀区域
};

var(MMOServer) const EVolumeTriggerType	 VolumeType;
// 区域ID，和服务器配置一致
//var(MMOTrigger) editconst int AreaID;//TODO: 当前使用 ServerUniqueID 代替之

var bool EditTriggerProperty;
var(MMOTrigger) int Priority <editcondition=EditTriggerProperty>;
var(MMOTrigger) int MaxTriggerCount <editcondition=EditTriggerProperty>;
var(MMOTrigger) string BehaviorTreeName <editcondition=EditTriggerProperty>;


enum EPKType
{
	EPKT_Normal <DisplayName="EPKT_Normal">,
	EPKT_Free <DisplayName="EPKT_Free">,
	EPKT_Safe <DisplayName="EPKT_Safe">
};

var bool EditPKType;
var(MMOPK) EPKType PKType <editcondition=EditPKType>;

var bool EditStall;
// 摊位税率等级
var(MMOStall) int StallLevel <editcondition=EditStall>;

// add by zhangrui05@snda.com >
enum EQuestTriggerType
{
	EQTT_Explore <DisplayName="EQTT_Explore">,
	EQTT_Accept <DisplayName="EQTT_Accept">,
	EQTT_Complete <DisplayName="EQTT_Complete">
};

var bool EditQuestTriggerType;
var(MMOQuest) EQuestTriggerType QuestTriggerType <editcondition=EditQuestTriggerType>;
var(MMOQuest) array<int> Quests;
// < add by zhangrui05@snda.com

var bool EditGuideTriggerType;
var(MMOGuide) int GuideId <editcondition=EditGuideTriggerType>;
// < add by zhangrui05@snda.com

var bool EditBlock;
var(MMOBlock) bool BlockMove <editcondition=EditBlock>;
var(MMOBlock) bool BlockLeap <editcondition=EditBlock>;
var(MMOBlock) bool BlockMissile <editcondition=EditBlock>;
var(MMOBlock) bool BlockBullet <editcondition=EditBlock>;

var bool EditDoor;
var(MMODoor) int DoorID <editcondition=EditDoor>;

var bool EditMine;
var(MMOMine) int nMineLevel <editcondition=EditMine>;

var bool EditTeleport;
var(MMOTeleport) bool CannotTeleport <editcondition=EditTeleport>;

var bool EditLoseItem;
var(MMORoleLoseItem) bool CannotLoseItem <editcondition=EditLoseItem>;

var bool EditDropItem;
var(MMORoleDropItem) bool CannotDropItem <editcondition=EditDropItem>;

var bool EditNpcDropItem;
var(MMODropItem) bool NpcCannotDropItem <editcondition=EditNpcDropItem>;

var (MMOServer)editinline int ServerUniqueID;			//song@snda.com

cpptext
{
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	virtual void PostDuplicate() { Super::PostDuplicate(); SetUniqueID(-1); InitUniqueID(); }

	#if WITH_EDITOR
	virtual void CheckForErrors()
	{
		AVolume::CheckForErrors();
	}
	#endif
}

// 注册到Facade中以便查找
//native function RegisterToFacade();

simulated function PreBeginPlay()
{	
	Super.PreBeginPlay();

	// 编辑器中打开碰撞，平时关掉碰撞，由服务器通知
// 	if(!WorldInfo.IsPlayInEditor())
// 	{
// 		SetCollision(false, false, true);
// 	}

	//RegisterToFacade();
}

//native function int GetAreaID();

//native function SetAutoID(int id);

// 取得物体大小
//native function Box GetObjectServerBounds();

// 取得物体位置
//native function vector GetObjectServerPosition();

//event OnServerNotify(bool on)
//{
//	`log("OSCAR:!!!!_______ MMOVolume_Trigger OnServerNotify:" @on);

//	if(on)
//	{
//		// enter
//		TriggerEvent(0);
//	}
//	else
//	{
//		// exit
//		TriggerEvent(1);
//	}
//}

// function TriggerEvent(int outputIndex)
// {
// 	local Sequence GameSeq;
// 	local array<SequenceObject> AllSeqEvents;
// 	local array<int> ActivateIndices;
// 	local int i;
// 	local SeqEvent_Server_AreaChange eventObj;
// 
// 	GameSeq = WorldInfo.GetGameSequence();
// 	if (GameSeq != None)
// 	{
// 		// find any Level Loaded events that exist
// 		GameSeq.FindSeqObjectsByClass(class'SeqEvent_Server_AreaChange', true, AllSeqEvents);
// 
// 		// activate them
// 		ActivateIndices[0] = outputIndex;
// 		for (i = 0; i < AllSeqEvents.Length; i++)
// 		{
// 			eventObj = SeqEvent_Server_AreaChange(AllSeqEvents[i]);
// 			
// 			if(eventObj.IsDesiredInstigator(self))
// 			{
// 				`log("OSCAR:!!!!_______ MMOVolume_Trigger Trigger Event Index:" @outputIndex);
// 				eventObj.CheckActivate(WorldInfo, self, false, ActivateIndices);
// 			}
// 		}
// 	}
// }

//native function array<DynamicBlockingVolume> GetBlockingVolumes();
//native function array<NPCSpawnPoint> GetNPCSpawnPoints();
// 返回一个调试用的标识名
//native function string GetClientName();

// native function array<IServerTrigger> GetLinkedTrigger();
// 
// native function ETrapEventType GetTrapEventType();
native function InitUniqueID();			//song@snda.com
native function INT GetUniqueID();
native function SetUniqueID(int id);

// add by zhangrui05@snda.com
native final function OnEnterQuestZone(MMOPlayer Other);
native final function OnLeaveQuestZone(MMOPlayer Other);

// add by zhangrui05@snda.com
native final function OnTriggerGuide(MMOPlayer Other);

//add by JimZhang@snda.com
native final function OnEnterSafe(MMOPlayer Other);
native final function OnLeaveSafe(MMOPlayer Other);
native final function OnEnterFree(MMOPlayer Other);


simulated event Touch( Actor Other, PrimitiveComponent OtherComp, vector HitLocation, vector HitNormal )
{
	Super.Touch(Other, OtherComp, HitLocation, HitNormal);
	
	if (VolumeType == EVVT_QuestZone)
	{
		OnEnterQuestZone(MMOPlayer(Other));
	}
	else if (VolumeType == EVVT_Guide)
	{
		OnTriggerGuide(MMOPlayer(Other));
	}
	else if (VolumeType == EVVT_PKType)
	{
		switch(PKType)
		{
		case EPKT_Safe:
			OnEnterSafe(MMOPlayer(Other));
			break;
		//case EPKT_Free:
		//	OnEnterFree(MMOPlayer(Other));
		//	break;
		}
	}
}

event UnTouch(Actor Other)
{
	super.UnTouch(Other);

	if (Pawn(Other) != none)
	{
		if (VolumeType == EVVT_QuestZone)
		{
			 OnLeaveQuestZone(MMOPlayer(Other));
		}
		else if(VolumeType == EVVT_PKType)
		{
			switch(PKType)
			{
			case EPKT_Safe:
				OnLeaveSafe(MMOPlayer(Other));
				break;
			}
		}
	}
}

// < add by zhangrui05@snda.com

DefaultProperties
{	
	ServerUniqueID=0
	//SupportedEvents(2)=class'SeqEvent_Server_AreaChange'

	Quests(0)=0
	Quests(1)=0
	Quests(2)=0
	Quests(3)=0
}
