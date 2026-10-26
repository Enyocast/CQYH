package ActionScript3
{
	import scaleform.clik.core.UIComponent;
	import flash.display.MovieClip;
	import flash.external.ExternalInterface;
	import ActionScript3.GravityObj;
	import fl.motion.Color;
	import flash.text.TextField;
	import UI_DamageLevel.DamageLevelAS3.TextMovieClip;
	

	public class MyEjectNumber extends UIComponent
	{

		public var bNeedUpdate:Boolean;
		//public var tf_number:TextField;
		public var MoneyTextMovieClip_mc:TextMovieClip;
		
		public var gObj:GravityObj = new GravityObj();
		
		public var removeEnable:Boolean = true;
		
		public var posX:Number;
		public var posY:Number;
		public var posZ:Number;

		public var dynamicX:Number = 0;
		public var dynamicY:Number = 0;
		

		override protected function configUI():void
		{
			super.configUI();
			this.mouseChildren=false;
			this.mouseEnabled=false;
			gObj.Init(this);
		}
		
		public function RemoveAll( Parent:UIComponent)
		{
			if (removeEnable)
			{
				if (gObj)
				{
					gObj.uiObj = null;
					gObj = null;
				}
				Parent.removeChild(this);
			}
			else
			{
				visible = false;
			}
		}
		
		public function UpdatePos(DeltaTime:Number):Boolean
		{
			if (visible==false)
			{
				return true;
			}
			
			if (gObj.isEnable == false)
			{
				return true;
			}

			if (gObj.isOver)
			{
				return false;
			}
			else
			{
				gObj.UpdateTween(DeltaTime);
			}

			if (visible)
			{
				scaleX = gObj.scaleCur;
				scaleY = gObj.scaleCur;
				alpha = gObj.alphaCur;

				var x1 = posX+gObj.sx;
				var y1 = posY+gObj.sy;
				var z1 = posZ+gObj.sz;
				
				ExternalInterface.call( "ASSetPos3DTo2D", this,x1,y1,z1 );
			}

			return true;
		}

		public function StartShow(Parent:UIComponent)
		{
			if (removeEnable)
			{
				Parent.addChild(this);
			}
			visible = true;
			bNeedUpdate = false;
			UpdatePos(0);
		}
	}
}