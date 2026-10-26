/*
 * Params  format: dir1 dir2 ...
 * forexample ExportAllObjectMT ..\\..\\MMOGame\\Content\\MMOContent\\01_Scene
 * 
 */
class ExportAllObjectMTCommandlet extends Commandlet
	native;

var array<string> ConvertFileRootFolders;

defaultproperties
{
	//ConvertFileRootFolders(0)="..\\..\\MMOGame\\Content\\MMOContent\\01_Scene\\legend\\Login"
}
