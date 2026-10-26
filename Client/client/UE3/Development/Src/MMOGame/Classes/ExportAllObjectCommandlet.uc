/*
 * Params  format: dir1 dir2 ...
 * forexample ExportAllObject ..\\..\\MMOGame\\Content\\MMOContent\\01_Scene
 * 
 */
class ExportAllObjectCommandlet extends Commandlet
	native;

cpptext
{
	virtual INT Main(const FString& Params);
}

var array<string> ConvertFileRootFolders;

defaultproperties
{
	//ConvertFileRootFolders(0)="..\\..\\MMOGame\\Content\\MMOContent\\01_Scene\\legend\\Login"
}
