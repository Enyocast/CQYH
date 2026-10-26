class MMOUITransducerInfo extends MMOUIBase
	native(UI);

var int Progress;
var float ProgressLenth;
var int UIBarLength;
var GFxObject ShineObj;
var GFxObject FillObj;
var float ShineHalfLegth;
var float ShineHalfHeight;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
	Progress = 0;
	ProgressLenth = 1000.0f;
	UIBarLength =  GetObject("tf_Name").GetFloat("width");
	`log("MMOUITransducerInfo::InitLoad:ProgressLenth"@ProgressLenth);
	ShineObj = GetObject("shine");
	FillObj = GetObject("mask");
	ShineHalfLegth = ShineObj.GetFloat("width") / 2;

	/*************
		   |
		== | ===> 1/6 Y offset
		   |
	***************/
	ShineHalfHeight = ShineObj.GetFloat("height") / 6;
}

event UpdateInfo( bool bShow ,int inProgress)
{
	local float Percent;
	local float Length;
	local float ShineX,ShineY;
	if(bShow)
	{		
		Progress = inProgress;
		Percent = float( Progress ) / ProgressLenth ;

		if(Percent<0.001)
			Percent = 0.001;
		
		SetVisible(true);
		
		Length = clamp(UIBarLength*Percent,1,UIBarLength );
		`log("MMOUITransducerInfo::UpdateInfo,inProgress:"@inProgress @"Percent:"@Percent @"Length"@Length);
		//
		FillObj.GetPosition( ShineX, ShineY );
		ShineX += Length ;//- ShineHalfLegth;
		ShineY += ShineHalfHeight;
		ShineObj.SetPosition( ShineX,ShineY);
		FillObj.SetFloat("width", Length );
		SetBool("bNeedUpdate",true);
	}
	else
	{
		SetVisible(false);
	}
}

DefaultProperties
{
	DefaultVisible=true
	CloseOnEsc=false
}
