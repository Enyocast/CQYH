//
// IServerTrigger接口，发协议时，根据对象转换出接口，取得协议需要的数据，再发送给服务器。
//
interface IServerTrigger
	native;

enum ETrapEventType
{
    // 触发NPC产生事件。
    eTET_TRAPEVENT_NPC_SPAWN <DisplayName="NPC Spawn">,
    // 阻挡区域控制。
    eTET_TRAPEVENT_BLOCK <DisplayName="Change Block">,
    // 技能释放器事件。
    eTET_TRAPEVENT_SKILL <DisplayName="Use Skill">,
    // 传送事件。
    eTET_TRAPEVENT_TELEPORT <DisplayName="Teleport">,
	// 传送门开启/关闭事件。
	eTET_TRAPEVENT_TRANSMI <DisplayName="Teleport Gate">
};


enum ETriggerType
{
	eTT_TRAPTYPE_INVALID <DisplayName="Invalid">,
	// 进入区域触发。
	eTT_TRAPTYPE_ENTER_AREA <DisplayName="EnterArea">,
	// NPC 死亡触发。
	eTT_TRAPTYPE_NPC_DEAD <DisplayName="NPC Dead">,
	// 手动触发。
	eTT_TRAPTYPE_MANUAL <DisplayName="Manual">,
	// 进度类型的机关。
	eTT_TRAPTYPE_LOADING <DisplayName="Loading">,
    // 技能发动触发。
    eTT_TRAPTYPE_SKILL <DisplayName="Skill">,
    // 道具触发。
    eTT_TRAPTYPE_PROP <DisplayName="Item">,
    // 多人(被动)机关。
    eTT_TRAPTYPE_MULTI <DisplayName="Multi">,
    // 多人进度触发。
    eTT_TRAPTYPE_MULTI_LOADING <DisplayName="Multi-Loading">,
};

enum ETriggerInitState
{
	eTIS_Invisible <DisplaName="Invisible">,
	eTIS_Off         <DisplaName="Off">,
	eTIS_On          <DisplaName="On">,
	eTIS_Loading <DisplaName="Loading">,
	eTIS_NA          <DisplaName="N/A">
};

struct native AbilityEvent
{
	var() array<MMOAbility> Ability;
	// TODO: 添加需要的参数
};

struct native TeleportEvent
{
	var() string TargetScene;
	var() Vector TargetPosition;
	// TODO: 添加需要的参数
};

struct native NPCDeadEvent
{
	var() int GroupID;
	var() array<IServerArea> TargetEventArea;
};

// 注册到Facade中以便查找
native function RegisterToFacade();

native function ETriggerType GetTriggerType();
native function int GetTriggerID();
native function SetAutoID(int id);

// 取得物体大小
native function Box GetObjectServerBounds();

// 取得物体位置
native function vector GetObjectServerPosition();

// 取得关联的阻挡框
native function array<DynamicBlockingVolume> GetBlockingVolumes();

// 开始状态是否是，开启、关闭、不可用
native function ETriggerInitState GetServerInitState();

// 返回一个调试用的标识名
native function string GetClientName();

// 取得关联的NPC出生点
native function array<NPCSpawnPoint> GetNPCSpawnPoints();

// 取得关联的机关，以便在当前事件区域完成后，激活这些机关
native function array<IServerTrigger> GetLinkedTrigger();

// 机关延迟启动时间
native function int GetDelayTime();

// 触发技能列表
native function array<AbilityEvent> GetAbilityList();

// 触发技能列表
native function TeleportEvent GetTeleportEvent();

// 取得陷阱类型
native function ETrapEventType GetTrapEventType();

native function array<IServerArea> GetLinkedEventArea();

// 触发时间
native function int GetLoadingTime(); 

// NPC死亡时触发的事件数据
native function NPCDeadEvent GetNPCDeadEvent();

// 打开传送门的列表
native function array<TeleportOrig> GetLinkedTeleportList();