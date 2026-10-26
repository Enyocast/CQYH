
class MMOVolume_ChangeMoveSpeed extends TriggerVolume
	placeable
	native;

// 区域ID，和服务器配置一致
var(MMOServer) int ServerID;

// 玩家移动速度改变为多少倍速
var(MMOServer) float SpeedChange;

// 注册到Facade中以便查找
native function RegisterToFacade();
// 取得物体大小
native function Box GetObjectServerBounds();

// 取得物体位置
native function vector GetObjectServerPosition();

simulated function PreBeginPlay()
{	
	Super.PreBeginPlay();

	// 编辑器中打开碰撞，平时关掉碰撞，由服务器通知
	//if(!WorldInfo.IsPlayInEditor())
	//{
	//	SetCollision(false, false, true);
	//}

	SetCollision(false, false, false);

	RegisterToFacade();
}

DefaultProperties
{	
	SpeedChange=1.0
}