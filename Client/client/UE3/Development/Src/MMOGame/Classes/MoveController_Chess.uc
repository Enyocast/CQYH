/*
 * 
 * 棋类npc的特殊controller,
 * 
 */
class MoveController_Chess extends MoveController
	native
	hidecategories(Object,Physics,Collision,MMO,Mobile,Advanced,Attachment,Display,Movement,Debug);

	
	//接口
	native function OnLeftMouseKey(Actor srcActor,bool bRelease,Vector StartTrace,Vector EndTrace);


DefaultProperties
{

}
