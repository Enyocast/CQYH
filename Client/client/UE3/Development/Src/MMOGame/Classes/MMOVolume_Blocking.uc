
class MMOVolume_Blocking extends Volume
	placeable
	native
	hidecategories(Object, Attachment, Physics, Advanced, Debug, Mobile, Volume);

var(MMOBlock) bool BlockMove;
var(MMOBlock) bool BlockLeap;
var(MMOBlock) bool BlockMissile;
var(MMOBlock) bool BlockBullet;
var(MMOBlock) bool RoleBlock;

DefaultProperties
{
	BlockMove=true
	bColored=true
	BrushColor=(R=255,G=0,B=0,A=255)
}
