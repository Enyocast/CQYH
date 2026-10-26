//MMOServerToggleDoorActor
//hemu@snda
//用于场景交互中的门
//涉及到碰撞相关 服务需要填入Grid 这里单独处理

class MMOServerToggleDoorActor extends MMOServerToggleActor 
	native
	ClassGroup(__Server_Old__);

//DoorId 标记
var(MMOServerToggleActor)  int                   DoorId           <DisplayName="ID">;

cpptext
{
	virtual INT GetServerID(){ return DoorId; }
	virtual INT GetObjectServerType() const { return (INT)kotDoor; }
}

DefaultProperties
{
	DoorId=1
}
