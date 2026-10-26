//
// 动画通知扩展类
//
class AnimNotify_ScriptedEx extends AnimNotify_Scripted
	;

// 取得Socket位置
function vector GetSocketWorldPosition(SkeletalMeshComponent mesh, name socketName)
{
	local Vector pos;
	local rotator rot;

	mesh.GetSocketWorldLocationAndRotation(
		socketName, pos, rot, 0);// 0 == World, 1 == Local (Component)

	return pos;
}

// 取得Socket朝向
function rotator GetSocketWorldRotation(SkeletalMeshComponent mesh, name socketName)
{
	local Vector pos;
	local rotator rot;

	mesh.GetSocketWorldLocationAndRotation(
		socketName, pos, rot, 0);// 0 == World, 1 == Local (Component)

	return rot;
}

// 如果没有socket就取角色位置
function GetWorldPosRot(Actor Owner, name socketName, out Vector pos, out Rotator rot)
{
	local Pawn pawn;

	//`log("+++++++" @Owner);
	
	if(socketName != '')
	{
		pawn = Pawn(Owner);
		if(pawn != none)
		{		
			//`log("+++++++ Use socket position");
			if(!pawn.Mesh.GetSocketWorldLocationAndRotation(socketName, pos, rot, 0))
			{
				pos = Owner.Location;
				rot = Owner.Rotation;
			}
		}
		else
		{
			//`log("+++++++ User actor position instead of socket");
			pos = Owner.Location;
			rot = Owner.Rotation;
		}
	}
	else
	{
		//`log("+++++++ User actor position");
		pos = Owner.Location;
		rot = Owner.Rotation;
	}
}

DefaultProperties
{
	NotifyColor=(R=255,G=255,B=0,A=255)
}
