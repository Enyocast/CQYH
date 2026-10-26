使用命令行 ver %1 %2 %3 %4

const char* pNewVersionPath/*新版本路径*/, const char* pDestDir/*全包存放目录*/,
	const char* pRefVersionPath = NULL/*比对版本路径*/, const char* pDestPatchDir = NULL/*更新包存放目录*/

路径以\结尾， 若pDestDir为空，则不生成全包，后两个参数若为空，则不生成补丁