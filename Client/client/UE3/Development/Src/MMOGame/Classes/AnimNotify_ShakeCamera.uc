//
// 动画通知震屏
//
class AnimNotify_ShakeCamera extends AnimNotify_Scripted
	;

// 震屏动画，预先编辑好的CameraAnim资源
var(MMO) CameraAnim ShakeCameraTemplate;

// 震屏时间速度倍，实际播放震屏时间为ShakeCameraTemplate的时间乘上这个值
var(MMO) float ShakeCameraTimeScale;

event Notify( Actor Owner, AnimNodeSequence AnimSeqInstigator )
{
	local Controller C;

	// TODO:检查多个玩家的情况？
	foreach Owner.WorldInfo.AllControllers(class'Controller', C)
	{
		if ( PlayerController(C) != None )
		{
			PlayerController(C).ClientPlayCameraAnim(ShakeCameraTemplate, ShakeCameraTimeScale);
			return;
		}
	}
}

event NotifyEnd( Actor Owner, AnimNodeSequence AnimSeqInstigator )
{
	
}


DefaultProperties
{
	ShakeCameraTemplate=CameraAnim'Shake.HeavyHitShake'
	ShakeCameraTimeScale=1

	NotifyColor=(R=255,G=255,B=0,A=255)
}
