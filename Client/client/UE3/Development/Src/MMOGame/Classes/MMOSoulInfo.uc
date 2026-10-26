class MMOSoulInfo extends Object implements(IExcelable,IReferenceID)
	native;

/*
struct SOUL_DATA
{
    INT32 m_nTemplateID;
    INT32 m_nAttrType;
    INT32 m_nParam;
    INT32 m_nMatchSocket;
    INT32 m_nSoulLevel;
    INT32 m_nPriceValue;
    INT32 m_nUpgradeSoulID;
};
*/

struct native SoulAddParam
{
	var init string			paramName;
	var init int			value;
};

struct native SoulLevelUpInfo
{
	var init int			SoulWaitForLevelUpID;
	var init array<int>		SoulIDToSacrifyForLevelUp;
	var init float			SuccessRate;
	var init float			RequiredMoney;
	var init array<SoulAddParam>	ParamList;
};

struct native ItemPosInfo
{
	var int ContainerID;
	var int	ItemSlotID;
};

var(MMOServer) int   TemplateID <DisplayName="TemplateID"|ExportExcel="0">;
var(MMOServer) int   AttrType <DisplayName="AttrType"|ExportExcel="1">;
var(MMOServer) int	 Param   <DisplayName="Param"|ExportExcel="2">;
var(MMOServer) int   MatchSocket <DisplayName="MatchSocket"|ExportExcel="3">;
var(MMOServer) int	 SoulLevel <DisplayName="SoulLevel"|ExportExcel="4">;
var(MMOServer) int	 PriceValue <DisplayName="PriceValue"|ExportExcel="5">;
var(MMOServer) int	 UpgradeSoulID <DisplayName="UpgradeSoulID"|ExportExcel="6">;
var(MMOServer) int	 DetouchPrice <DisplayName="DetouchPrice"|ExportExcel="7">;


// 导出表头,先调用脚本函数，再调用native函数
event ScriptExportExcelHeaders(out array<string> Header, out array<string> DefaultValues)
{	
	// 继承自ACTOR的类只能用native函数导出
}


// 导出每行数据,先调用脚本函数，再调用native函数
event ScriptDataToExcel(out array<string> Row)
{
	// 继承自ACTOR的类只能用native函数导出
}

native function ExportExcelHeaders(out array<string> Header, out array<string> DefaultValues);
native function DataToExcel(out array<string> Row);
native function ImportFromExcel(array<string> values);
event ScriptImportFromExcel(array<string> Values)
{	
	// 继承自ACTOR的类只能用native函数导出
}

native function InitDataToExcel();
native function int GetTemplateID() const;

DefaultProperties
{	
	TemplateID=-1
}
