
interface IPickableActor
	native;

// 物品捡选优先级
enum EPickPriority
{
	//EPP_Trigger	    <DisplayName="Trigger">,
	//EPP_DropItem	<DisplayName="DropItem">,
	//EPP_NPC         <DisplayName="NPC">,
	//EPP_Totem       <DisplayName="Totem">,		
	//EPP_Retinue     <DisplayName="Retinue">,
	//EPP_Pet         <DisplayName="Pet">,
	//EPP_OtherPlayer	<DisplayName="OtherPlayer">,
	//EPP_InterpActor <DisplayName="StaticMeshActor">,
	//EPP_TeleportOrig <DisplayName="TeleportOrig">,
	//EPP_WorldGeometry,
	////EPP_StaticMeshActor <DisplayName="StaticMeshActor">,
	////EPP_Terrain     <DisplayName="Terrain">,
	////EPP_Landscape	<DisplayName="Landscape">,
	//EPP_Body	    <DisplayName="Body">,
	//EPP_Player      <DisplayName="Player">,
	//EPP_ObstacleMesh      <DisplayName="ObstacleMesh">,
	//EPP_UnTouchBody  <DisplayName="EPP_UnTouchBody">,
	//EPP_PickMax      <DisplayName="PickMax">,

	EPP_High,		// 场景触发物,交互类NPC，所有doodad
	EPP_Normal,		// 非交互类ＮＰＣ，非自己玩家，宠物，掉落物
	EPP_Low,		 // 玩家自己
	EPP_Floor,      // 场景
	EPP_PickMax,
};

// 鼠标状态定义,根据UE3的EMouseCursor做扩展
// 通过DefaultGame.ini中的Cursor段映射光标文件
enum EMMOCursorType
{
	EMC_None,
	EMC_NoChange,		// Keeps the platform client from calling setcursor so a cursor can be set elsewhere (ie using wxSetCursor).
	EMC_Arrow,
	EMC_Cross,
	EMC_SizeAll,
	EMC_SizeUpRightDownLeft,
	EMC_SizeUpLeftDownRight,
	EMC_SizeLeftRight,
	EMC_SizeUpDown,
	EMC_Hand,
	EMC_GrabHand,
	//Custom cursors for game-specific usage
	EMC_IBEAM,
	EMC_Sell,
	EMC_Buy,
	EMC_Attack,
	EMC_Pick,
	EMC_Talk,
	EMC_Dialog,
	EMC_Task,
	EMC_Repair,
	EMC_Identify,
	EMC_Signature,
	EMC_Aim,
    EMC_PickWithLock,
	EMC_Split,
	EMC_Busy,
};

native function EPickPriority GetPickPriority();
native function EMMOCursorType GetMouseCursor();
