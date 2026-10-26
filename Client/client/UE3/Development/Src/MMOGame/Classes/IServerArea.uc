//
// IServerArea接口
//
interface IServerArea
	native;

// 注册到Facade中以便查找
native function RegisterToFacade();

// 取得相应ID
native function int GetAreaID();
native function SetAutoID(int id);

// 服务器通知协议
event OnServerNotify(bool on);

// 取得物体大小
native function Box GetObjectServerBounds();

// 取得物体位置
native function vector GetObjectServerPosition();

// 取得关联的阻挡框
//native function array<DynamicBlockingVolume> GetBlockingVolumes();

// 取得关联的NPC出生点
//native function array<NPCSpawnPoint> GetNPCSpawnPoints();

// 返回一个调试用的标识名
native function string GetClientName();

// 取得关联的机关，以便在当前事件区域完成后，激活这些机关
//native function array<IServerTrigger> GetLinkedTrigger();
