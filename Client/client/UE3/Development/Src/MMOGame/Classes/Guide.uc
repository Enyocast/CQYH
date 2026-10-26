class Guide extends Object implements(IExcelable,IReferenceID)
	native
	hidecategories(Object);

enum EGuideEventType
{
	EGUET_Null																				<DisplayName="EGUET_Null">,		                    // 无
	EGUET_LevelChange																		<DisplayName="EGUET_LevelChange">,		            // 等级变化（新系统开启）
	EGUET_GetItem																			<DisplayName="EGUET_GetItem">,		                // 获得道具
	EGUET_EnterZone																			<DisplayName="EGUET_EnterZone">,		            // 进入区域
	EGUET_EnterGame																			<DisplayName="EGUET_EnterGame">,		            // 进入游戏
	EGUET_EnterScene																		<DisplayName="EGUET_EnterScene">,		            // 进入地图
	EGUET_Move																				<DisplayName="EGUET_Move">,		                    // 移动教学
	EGUET_CloseGuidePanel																	<DisplayName="EGUET_CloseGuidePanel">,		        // 关闭教学面板
	EGUET_ClickNaviLink																		<DisplayName="EGUET_ClickNaviLink">,		        // 点击寻路超链接
	EGUET_OpenQuestDialogSinglePage															<DisplayName="EGUET_OpenQuestDialogSinglePage">,    // 任务对话(单页)
	EGUET_OpenQuestDialogMultiPage															<DisplayName="EGUET_OpenQuestDialogMultiPage">,	    // 任务对话(多页)
	EGUET_QuestPageDown																		<DisplayName="EGUET_QuestPageDown">,		        // 任务对话翻页
	EGUET_QuestPageUp																		<DisplayName="EGUET_QuestPageUp">,		            // 任务对话翻页
	EGUET_CloseDialog																		<DisplayName="EGUET_CloseDialog">,		            // 关闭对话框
	EGUET_DialogCompleteQuest																<DisplayName="EGUET_DialogCompleteQuest">,		    // 对话框点击完成任务
	EGUET_DialogAcceptQuest																	<DisplayName="EGUET_DialogAcceptQuest">,		    // 对话框点击接受任务
	EGUET_AcceptQuest																		<DisplayName="EGUET_AcceptQuest">,		            // 接受任务
	EGUET_CompleteQuest																		<DisplayName="EGUET_CompleteQuest">,		        // 完成任务
	EGUET_OpenNpcDialog																		<DisplayName="EGUET_OpenNpcDialog">,		        // NPC对话
	EGUET_NpcDialogServerOption																<DisplayName="EGUET_NpcDialogServerOption">,	    // 任务对话
	EGUET_ShowBagPanel																		<DisplayName="EGUET_ShowBagPanel">,		            // 打开背包
	EGUET_UseItem																			<DisplayName="EGUET_UseItem">,		                // 使用道具
	EGUET_DragItemToSkillBar																<DisplayName="EGUET_DragItemToSkillBar">,	        // 拖动道具到快捷栏
	EGUET_Emergency																			<DisplayName="EGUET_Emergency">,		            // 紧急事件
	EGUET_AddDrop																			<DisplayName="EGUET_AddDrop">,		                // 第一次掉落
	EGUET_ClickCompItem																		<DisplayName="EGUET_ClickCompItem">,		        // 单击合成道具
	EGUET_KillMonster																		<DisplayName="EGUET_KillMonster">,		            // 第一次杀怪
	EGUET_LearnSkill																		<DisplayName="EGUET_LearnSkill">,		            // 学会第一个技能
	EGUET_ClickFlyLink																		<DisplayName="EGUET_ClickFlyLink">,		            // 点击飞鞋超链接
	EGUET_SelectQuestAward																	<DisplayName="EGUET_SelectQuestAward">,		        // 选择任务奖励
	EGUET_ShowQuestPanel																	<DisplayName="EGUET_ShowQuestPanel">,		        // 开启任务面板
	EGUET_EquipWeapon																		<DisplayName="EGUET_EquipWeapon">,		            // 装备道具
	EGUET_KismetEnd																			<DisplayName="EGUET_KismetEnd">,		            // 过场动画结束
	EGUET_ShowCharacterPanel																<DisplayName="EGUET_ShowCharacterPanel">,	        // 打开角色属性
	EGUET_GetAchievement																	<DisplayName="EGUET_GetAchievement">,		        // 获得成就
	EGUET_ShowAchievementPanel																<DisplayName="EGUET_ShowAchievementPanel">,	        // 打开成就面板
	EGUET_ShowDungeonEnterPanel																<DisplayName="EGUET_ShowDungeonEnterPanel">,        // 打开副本进入面板
	EGUET_ChooseDungeonLvPanel																<DisplayName="EGUET_ChooseDungeonLvPanel">,	        // 选择副本难度
	EGUET_EnterDungeon																		<DisplayName="EGUET_EnterDungeon">,		            // 进入副本
	EGUET_ShowDungeonAward																	<DisplayName="EGUET_ShowDungeonAward">,		        // 副本奖励
	EGUET_ExitDungeonConfirm																<DisplayName="EGUET_ExitDungeonConfirm">,           // 离开副本
	EGUET_ExitDungeon																		<DisplayName="EGUET_ExitDungeon">,		            // 离开副本
	EGUET_Extendbag																			<DisplayName="EGUET_Extendbag">,		            // 扩展背包
	EGUET_ShowMasterPanel																	<DisplayName="EGUET_ShowMasterPanel">,		        // 打开师徒面板
	EGUET_ChooseChatChanel																	<DisplayName="EGUET_ChooseChatChanel">,		        // 选择聊天频道
	EGUET_SendChat																			<DisplayName="EGUET_SendChat">,		                // 聊天
	EGUET_ShowMailPanel																		<DisplayName="EGUET_ShowMailPanel">,		        // 打开邮件面板
	EGUET_StudentApply																		<DisplayName="EGUET_StudentApply">,		            // 拜师
	EGUET_ShowHeavenPanel																	<DisplayName="EGUET_ShowHeavenPanel">,		        // 打开境界面板
	EGUET_SoulToPoint																		<DisplayName="EGUET_SoulToPoint">,		            // 魂转修炼点
	EGUET_ShowSkillLevelUpPanel																<DisplayName="EGUET_ShowSkillLevelUpPanel">,        // 技能升级面板
	EGUET_SkillLevelUp																		<DisplayName="EGUET_SkillLevelUp">,		            // 技能升级
	EGUET_ShowSkillSettingPanel																<DisplayName="EGUET_ShowSkillSettingPanel">,        // 打开技能配置界面
	EGUET_SetSkillSetting																	<DisplayName="EGUET_SetSkillSetting">,		        // 技能进入技能配置界面
	EGUET_EquipSkill																		<DisplayName="EGUET_EquipSkill">,		            // 点选一个技能装配到快捷栏
	EGUET_ShowWeaponSkillPanel																<DisplayName="EGUET_ShowWeaponSkillPanel">,	        // 打开铭文界面
	EGUET_DropWeaponToWeaponSkill															<DisplayName="EGUET_DropWeaponToWeaponSkill">,      // 放置武器到铭文界面
	EGUET_DropWeaponSkill																	<DisplayName="EGUET_DropWeaponSkill">,		        // 放置铭文
	EGUET_EmbedWeaponSkill																	<DisplayName="EGUET_EmbedWeaponSkill">,		        // 镶嵌铭文
	EGUET_WeaponSkillLvUp																	<DisplayName="EGUET_WeaponSkillLvUp">,		        // 升级铭文	
	EGUET_ShowGuildPanel																	<DisplayName="EGUET_ShowGuildPanel">,		        // 打开公会面板
	EGUET_ShowGuildViewPanel																<DisplayName="EGUET_ShowGuildViewPanel">,	        // 打开公会查看面板
	EGUET_ShowTeamPanel																		<DisplayName="EGUET_ShowTeamPanel">,		        // 打开组队面板
	EGUET_CreateTeam																		<DisplayName="EGUET_CreateTeam">,		            // 创建队伍
	EGUET_ClickDecompEquip																	<DisplayName="EGUET_ClickDecompEquip">,		        // 点击分解装备
	EGUET_DecompEquip																		<DisplayName="EGUET_DecompEquip">,		            // 分解装备
	EGUET_CompEquip																			<DisplayName="EGUET_CompEquip">,		            // 合成装备
	EGUET_ShowGemPanel																		<DisplayName="EGUET_ShowGemPanel">,		            // 打开灵石镶嵌面板
	EGUET_GemPanelWithEquip																	<DisplayName="EGUET_GemPanelWithEquip">,	        // 灵石镶嵌面板拖入武器
	EGUET_GemPanelWithGem																	<DisplayName="EGUET_GemPanelWithGem">,		        // 灵石镶嵌面板拖入灵石
	EGUET_GemEmbed																			<DisplayName="EGUET_GemEmbed">,		                // 灵石镶嵌
	EGUET_ShowStrongPanel																	<DisplayName="EGUET_ShowStrongPanel">,		        // 打开体格强化面板
	EGUET_ChooseHeadPart																	<DisplayName="EGUET_ChooseHeadPart">,		        // 选中头部
	EGUET_Strong																			<DisplayName="EGUET_Strong">,		                // 强化
	EGUET_ShowGasPraPanel																	<DisplayName="EGUET_ShowGasPraPanel">,		        // 打开气息修炼面板
	EGUET_OpenGas																			<DisplayName="EGUET_OpenGas">,		                // 开辟气海
	EGUET_EquipGas																			<DisplayName="EGUET_EquipGas">,		                // 装备气海
	EGUET_OpenShopPanel																		<DisplayName="EGUET_OpenShopPanel">,		        // 开启商店面板
	EGUET_ShowShopPanel																		<DisplayName="EGUET_ShowShopPanel">,		        // 显示商店面板
	EGUET_CloseShopPanel																	<DisplayName="EGUET_CloseShopPanel">,		        // 关闭商店面板
	EGUET_BuyItem																			<DisplayName="EGUET_BuyItem">,		                // 购买道具
	EGUET_ShowActivityPanel																	<DisplayName="EGUET_ShowActivityPanel">,	        // 活动面板
	EGUET_SwitchLine																		<DisplayName="EGUET_SwitchLine">,		            // 切换分线
	EGUET_ShowWeaponLvUpPanel																<DisplayName="EGUET_ShowWeaponLvUpPanel">,	        // 武器升级
	EGUET_ActivateJourneyType																<DisplayName="EGUET_ActivateJourneyType">,	        // 激活玛法日志分类
	EGUET_OpenNpcMap																		<DisplayName="EGUET_OpenNpcMap">,		            // 打开玛法杀怪地图
	EGUET_ReputationFull																	<DisplayName="EGUET_ReputationFull">,		        // 声望满
	EGUET_OpenJourneyView																	<DisplayName="EGUET_OpenJourneyView">,	            // 打开玛法奖励界面
	EGUET_GetJourneyAwards                                                                  <DisplayName="EGUET_GetJourneyAwards">,             // 领取玛法奖励
	EGUET_GetTitle                                                                          <DisplayName="EGUET_GetTitle">,                     // 获取称号
	EGUET_ChooseTitle                                                                       <DisplayName="EGUET_ChooseTitle">,                  // 选择称号
	EGUET_EquipTitle                                                                        <DisplayName="EGUET_EquipTitle">,                   // 装备称号
	EGUET_BagFull                                                                           <DisplayName="EGUET_BagFull">,                      // 第一次背包满
};

enum EGuideType
{
	EGDT_Null                                                                               <DisplayName="EGDT_Null">,
	EGDT_Illustrate                                                                         <DisplayName="EGDT_Illustrate">,
	EGDT_TipLT                                                                              <DisplayName="EGDT_TipLT">,
	EGDT_TipRT                                                                              <DisplayName="EGDT_TipRT">,
	EGDT_TipLB                                                                              <DisplayName="EGDT_TipLB">,
	EGDT_TipRB                                                                              <DisplayName="EGDT_TipRB">,
	EGDT_ArrowT                                                                             <DisplayName="EGDT_ArrowT">,
	EGDT_ArrowB                                                                             <DisplayName="EGDT_ArrowB">,
	EGDT_ArrowL                                                                             <DisplayName="EGDT_ArrowL">,
	EGDT_ArrowR                                                                             <DisplayName="EGDT_ArrowR">,
	EGDT_Dialog                                                                             <DisplayName="EGDT_Dialog">,
	EGDT_Sound                                                                              <DisplayName="EGDT_Sound">,
};

enum EGuideBoxType
{
	EGBT_Null                                                                               <DisplayName="EGBT_Null">,
	EGBT_Square                                                                             <DisplayName="EGBT_Square">,
	EGBT_Triangle                                                                           <DisplayName="EGBT_Triangle">,
	EGBT_Circle                                                                             <DisplayName="EGBT_Circle">,
	EGBT_SquareSmall                                                                        <DisplayName="EGBT_SquareSmall">,
};

enum EGuideArrowTipsType
{
	EGATT_Null                                                                              <DisplayName="EGATT_Null">,
	EGATT_1                                                                                 <DisplayName="EGATT_1">,
	EGATT_2                                                                                 <DisplayName="EGATT_2">,
	EGATT_3                                                                                 <DisplayName="EGATT_3">,
	EGATT_4                                                                                 <DisplayName="EGATT_4">,
	EGATT_5                                                                                 <DisplayName="EGATT_5">,
	EGATT_6                                                                                 <DisplayName="EGATT_6">,
	EGATT_7                                                                                 <DisplayName="EGATT_7">,
	EGATT_8                                                                                 <DisplayName="EGATT_8">,
	EGATT_9                                                                                 <DisplayName="EGATT_9">,
	EGATT_10                                                                                <DisplayName="EGATT_10">,
};

enum ETraceMenuBarType
{
	ETMBT_Left                                                                              <DisplayName="ETMBT_Left">,
	ETMBT_Right                                                                             <DisplayName="ETMBT_Right">,
};

struct native GuidePicture
{
	var() Texture2D Picture                                                                 <DisplayName="Picture" | ExportExcel="Client">;
};

struct native GuideItem
{
	var() int ItemId                                                                        <DisplayName="ItemId" | ExportExcel="Client">;
};

struct native GuideSkill
{
	var() int SkillId                                                                       <DisplayName="SkillId" | ExportExcel="Client">;
};

struct native GuideOffset
{
	var() int X                                                                             <DisplayName="X" | ExportExcel="Client">;
	var() int Y                                                                             <DisplayName="Y" | ExportExcel="Client">;
};

struct native GuideSize
{
	var() int Width                                                                         <DisplayName="Width" | ExportExcel="Client">;
	var() int Height                                                                        <DisplayName="Height" | ExportExcel="Client">;
};

struct native GuideTargetComponent
{
	var() init string TargetComponentName                                                   <DisplayName="TargetComponentName" | ExportExcel="Client">;
};

var() editconst int GuideId                                                                 <DisplayName="GuideId" | ExportExcel="Client">;
var() EGuideType GuideType                                                                  <DisplayName="GuideType" | ExportExcel="Client">;
var() init string GuideDesc         				                                        <DisplayName="GuideDesc" | ExportExcel="Client">;
var() bool Enable                                                                           <DisplayName="Enable" | ExportExcel="Client">;
var() EGuideEventType ActivateGuideType                                                     <DisplayName="ActivateGuideType" | ExportExcel="Client">;
var() EGuideEventType DeactiveGuideType                                                     <DisplayName="DeactiveGuideType" | ExportExcel="Client">;

var(Condition) int LevelReq				                                                    <DisplayName="LevelReq" | ExportExcel="Client">;
var(Condition) int GuideReq				                                                    <DisplayName="GuideReq" | ExportExcel="Client">;
var(Condition) int QuestReq				                                                    <DisplayName="QuestReq" | ExportExcel="Client">;
var(Condition) editfixedsize array<GuideItem> ItemReqNew      	                            <DisplayName="ItemReqNew" | ExportExcel="Client">;
var(Condition) editfixedsize array<GuideSkill> SkillReq      	                            <DisplayName="SkillReq" | ExportExcel="Client">;
var(Condition) int ItemQuaReq				                                                <DisplayName="ItemQuaReq" | ExportExcel="Client">;
var(Condition) int NpcReq				                                                    <DisplayName="NpcReq" | ExportExcel="Client">;
var(Condition) EDOODAD_TYPE DoodadTypeReq		                                            <DisplayName="DoodadTypeReq" | ExportExcel="Client">;
var(Condition) EPlayerClass ClassReq			                                            <DisplayName="ClassReq" | ExportExcel="Client">;

var(Picture) editfixedsize array<GuidePicture> Picture				                        <DisplayName="Picture" | ExportExcel="Client">;

var(Sound) SoundCue GuideSound                                                              <DisplayName="GuideSound" | ExportExcel="Client">;
var(Sound) Texture2D GuideSoundIcon                                                         <DisplayName="GuideSoundIcon" | ExportExcel="Client">;

var(Display) init string TargetWindowName				                                    <DisplayName="TargetWindowName" | ExportExcel="Client">;
var(Display) editfixedsize array<GuideTargetComponent> TargetComponent	                    <DisplayName="TargetComponent" | ExportExcel="Client">;
var(Display) GuideOffset TargetComponentOffset 				                                <DisplayName="TargetComponentOffset" | ExportExcel="Client">;
var(Display) bool WithBox 				                                                    <DisplayName="WithBox" | ExportExcel="Client">;
var(Display) GuideOffset BoxOffset 				                                            <DisplayName="BoxOffset" | ExportExcel="Client">;
var(Display) GuideSize BoxSize 				                                                <DisplayName="BoxSize" | ExportExcel="Client">;
var(Display) EGuideBoxType BoxType				                                            <DisplayName="BoxType" | ExportExcel="Client">;
var(Display) EGuideArrowTipsType ArrowTipsType				                                <DisplayName="ArrowTipsType" | ExportExcel="Client">;
var(Display) bool TraceBagSlot              				                                <DisplayName="TraceBagSlot" | ExportExcel="Client">;
var(Display) bool TraceMenuBar				                                                <DisplayName="TraceMenuBar" | ExportExcel="Client">;
var(Display) ETraceMenuBarType TraceMenuBarType			                                    <DisplayName="TraceMenuBarType" | ExportExcel="Client">;
var(Display) int TraceMenuType				                                                <DisplayName="TraceMenuType" | ExportExcel="Client">;
var(Display) int TraceMenuChildType				                                            <DisplayName="TraceMenuChildType" | ExportExcel="Client">;
var(Display) bool TraceJourney				                                                <DisplayName="TraceJourney" | ExportExcel="Client">;
var(Display) int TraceJourneyType     			                                            <DisplayName="TraceJourneyType" | ExportExcel="Client">;
var(Display) bool TraceSkillBar                                                             <DisplayName="TraceSkillBar" | ExportExcel="Client">;
var(Display) int TraceSkillIndex                                                            <DisplayName="TraceSkillIndex" | ExportExcel="Client">;


event ScriptExportExcelHeaders(out array<string> Header, out array<string> DefaultValues)
{
}

event ScriptDataToExcel(out array<string> Row)
{
}

event ScriptImportFromExcel(array<string> Values)
{
// 	local string val;
// 	val = values[0];
// 	QuestTempID = int(val);
}

native function ExportExcelHeaders(out array<string> Header, out array<string> DefaultValues);
native function DataToExcel(out array<string> Row);
native function bool IsNeedArchetype();
native function ImportFromExcel(array<string> values);
native function InitDataToExcel();
native function int GetTemplateID() const;

DefaultProperties
{
	Picture(0)=()
	Picture(1)=()
	Picture(2)=()
	Picture(3)=()
	Picture(4)=()

	TargetComponent(0)=()
	TargetComponent(1)=()
	TargetComponent(2)=()
	TargetComponent(3)=()
	TargetComponent(4)=()

	ItemReqNew(0)=()
	ItemReqNew(1)=()
	ItemReqNew(2)=()
	ItemReqNew(3)=()
	ItemReqNew(4)=()

	SkillReq(0)=()
	SkillReq(1)=()
	SkillReq(2)=()
	SkillReq(3)=()
	SkillReq(4)=()

	ClassReq=EPCT_None
}
