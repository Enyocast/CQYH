//
// IExcelable接口，能输出Excel的对象可实现此接口
//
interface IExcelable
	native;

//
// 重要：如果实现了脚本版本的函数，就不要实现native版本的，两个都实现会造成数据冲突
//

// 导出表头,先调用脚本函数，再调用native函数
event ScriptExportExcelHeaders(out array<string> Header, out array<string> DefaultValues);


// 导出每行数据,先调用脚本函数，再调用native函数
event ScriptDataToExcel(out array<string> Row);

native function ExportExcelHeaders(out array<string> Header, out array<string> DefaultValues);
native function DataToExcel(out array<string> Row);
native function InitDataToExcel();

// 从EXCEL导入数据
native function ImportFromExcel(array<string> values);
event ScriptImportFromExcel(array<string> Values);
//// 输出数据到Excel
//cpptext
//{
//	bool DataToExcel(TArray<FString>& Row);
//}