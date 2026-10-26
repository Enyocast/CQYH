//
// NPC 出生点
//
// implements(IMMOActorHUD) Editor 中没有Player
class NPCSpawnPoint extends Actor
	placeable
	dependson(NPC)
	native
	hidecategories(Object,Debug,Display,Attachment,Collision,Physics,Advanced)
	ClassGroup(__Server_Old__);

//具体NPC模板信息
struct native SpawnNpcData
{
	var() NPC  NPCTemplateArchi;
	var() int     Weight;
};
// NPC模板引用
var(MMOServer) editoronly editinline  array<SpawnNpcData> NPCTemplateList;

//@todo ------------Start---------------- 慢慢删除这块内容

// 出生群组ID,NPCSpawnGroupId,目前导出后才会自动赋值，手动配置 
var(MMOServerOld) editoronly int GroupID;

// NPC类型ID（以后改为引用Archetype)
var(MMOServerOld) editoronly int KindID;

// 出生数量
var(MMOServerOld) editoronly int SpawnCount;

// 如果是Manual方式，需要服务器在收到特定协议后进行刷怪处理（如过场电影看完之后）
var(MMOServerOld) editoronly bool ManualSpawn;

// AI的脚本函数名
var(MMOServerOld) editoronly init string AIScriptFunctionID;

// 由哪个区域出生，需要自动根据AreaID设定
var editoronly int SpawnByAreaID;

var editoronly ArrowComponent EditorArrow;
var editoronly SpriteComponent EditorSprite;

//@todo ------------End---------------- 慢慢删除这块内容

native function vector GetServerPosition();

cpptext
{
	//virtual INT GetServerID(){ return AutoServerID; }
	//virtual INT GetObjectServerType() const { return (INT)sbtNpcSpawnPoint; }
	virtual void CheckForErrors();
}
event Tick(  float deltaTime  )
{
	super.Tick( deltaTime );
	//绘制会缓冲
	//if ( !class'Engine'.static.IsGame() )
	//	DrawMyHUD( HUD( class'HUD'.static ) );
}
function bool OnlyDrawHUDForOwner(){return false;}

//在HUD上显示SpawnPoint 信息
function bool DrawMyHUD( MMOHud H )
{
// 	local Vector screenPos;
// 	local Vector objectIconWorldPos;
// 	local float cameraDistFromPos;
// 	local float iconWidth, iconHeight;
// 	local float IconDistanceScale;
// 	local int drawX, drawY;
// 	local int nNPCCount;
// 
// 
// 	objectIconWorldPos = Location;//实际位置
// 	objectIconWorldPos.Z += 120;
// 	screenPos = H.Canvas.Project(objectIconWorldPos);
// 
// 	cameraDistFromPos = VSize(objectIconWorldPos - H.PlayerOwner.PlayerCamera.ViewTarget.POV.Location);
// 	IconDistanceScale = FClamp(1.0 - cameraDistFromPos/4000,0.25,1)*(H.Canvas.ClipY / 768.0f);
// 
// 	iconWidth = 166*IconDistanceScale;
// 	iconHeight = 18*IconDistanceScale;
// 
// 	H.Canvas.SetDrawColor(255, 0, 0, 255);
// 
// 	drawY = screenPos.y - iconHeight/2;
// 	drawX = screenPos.x - iconWidth/2;
// 
// 	H.Canvas.SetPos(drawX, drawY);
// 	nNPCCount =  NPCTemplateList.Length;
// 	H.Canvas.DrawText("NPCSpawnPoint  Group ID:" @ GroupID @ "NPC Count:"@ nNPCCount );
// 
// 	`log("NPCSpawnPoint::DrawMyHUD"@name @"Location:" @screenPos @"DrawPos:" @drawX @drawY);
	return true;
}

DefaultProperties
{
	Begin Object Class=SpriteComponent Name=Sprite
		Sprite=Texture2D'MMOEditor.MonsterSpawnPoint'
		HiddenGame=True
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
		SpriteCategoryName="Server"		
	End Object
	EditorSprite=Sprite
	Components.Add(Sprite);
	//DrawScale=0.2

	Begin Object Class=ArrowComponent Name=Arrow
		ArrowColor=(R=150,G=200,B=255)
		ArrowSize=3
		bTreatAsASprite=True
		HiddenGame=true
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
		SpriteCategoryName="Navigation"
	End Object
	EditorArrow=Arrow
	Components.Add(Arrow)


	ManualSpawn=false
}
