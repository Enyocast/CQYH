package ActionScript3
{
	import flash.display.Bitmap;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.getDefinitionByName;
	import flash.utils.getTimer;
	
	import ActionScript3.GravityObj;
	import ActionScript3.Common.DynamicComponent.DynamicComponentFactory;
	
	import fl.motion.Color;
	
	import scaleform.clik.core.UIComponent;
	
	public class MyDamageNumber extends UIComponent
	{
		public var count:int;
		public var NumType:int=0;//数字类型
		public var TxtType:int=0;
		public var bNeedUpdate:Boolean;
		
		public var attack_mc:MovieClip;
		public var origWidth:Number;
		public var origHeight:Number;
		
		public var posX:Number;
		public var posY:Number;
		public var posZ:Number;
		
		public var dynamicX:Number = 0;
		public var dynamicY:Number = 0;
		//		public var yellow_mc:Class;//金色数字
		//		public var red_mc:Class;//黄色数字
		//		public var white_mc:MovieClip=new MovieClip();//白色数字
		//		public var blue_mc:Class;//黄色数字
		//        public var green_mc:Class;//绿色数字
		//		public var xpClass:Class;
		//		public var goldClass:Class;
		//		public var AchieveClass:Class;//成就 
		//		public var MoralClass:Class;//道义值
		//		public var DodgeClass:Class;//闪避
		
		public var gObj:GravityObj = new GravityObj();
		public var removeEnable:Boolean = true;
		protected var isVisible:Boolean=false;
		
		private var _compFactory:DynamicComponentFactory;
		
		override protected function configUI():void
		{
			super.configUI();
			//initConfig();
			Init();
		}
		
		//		protected function initConfig():void
		//		{
		//			yellow_mc=getDefinitionByName("CriticalChar") as Class;
		//			red_mc=getDefinitionByName("AttackedChar") as Class;
		//			blue_mc=getDefinitionByName("BlockChar") as Class;
		//			green_mc=getDefinitionByName("HpGetChar") as Class;//加血
		//			xpClass=getDefinitionByName("XpTxt") as Class;
		//			goldClass=getDefinitionByName("GoldTxt") as Class;
		//			AchieveClass=getDefinitionByName("AchieveTxt") as Class;
		//			MoralClass=getDefinitionByName("MoralTxt") as Class;
		//			DodgeClass=getDefinitionByName("DodgeChar") as Class;
		//			
		//		}
		
		public function Init():void
		{
			gObj.Init(this);
		}
		
		private function getTxt():MovieClip
		{
			_compFactory = DynamicComponentFactory.getInstance();
			var mc:MovieClip = null;
			switch(TxtType)
			{
				case 1:
				{
					mc = _compFactory.getComponentByClassName("XpTxt") as MovieClip;
					break;
				}
				case 3:
				{
					mc = _compFactory.getComponentByClassName("AchieveTxt") as MovieClip;
					break;
				}
				case 4:
				{
					mc = _compFactory.getComponentByClassName("MoralTxt") as MovieClip;
					break;
				}
				case 5:
				{
					mc = _compFactory.getComponentByClassName("DodgeChar") as MovieClip;
					mc.gotoAndStop(count+1);
					break;
				}
				case 8:
				{
					mc = _compFactory.getComponentByClassName("TeachTxt") as MovieClip;
					break;
				}
				case 9:
				{
					mc = _compFactory.getComponentByClassName("GuildTxt") as MovieClip;
					break;
				}
				default:
				{
					mc = _compFactory.getComponentByClassName("GoldTxt") as MovieClip;
					break;
				}
			}
			return mc;
		}
		
		private function getNumber():MovieClip
		{
			_compFactory = DynamicComponentFactory.getInstance();
			var mc:MovieClip = null;
			switch(NumType)
			{
				case 2:
				{
					mc = _compFactory.getComponentByClassName("AttackedChar") as MovieClip;
					break;
				}
				case 3:
				{
					mc = _compFactory.getComponentByClassName("CriticalChar") as MovieClip;
					break;
				}
				case 4:
				{
					mc = _compFactory.getComponentByClassName("BlockChar") as MovieClip;
					break;
				}
				case 5:
				{
					mc = _compFactory.getComponentByClassName("HpGetChar") as MovieClip;
					break;
				}
			}
			return mc;
		}
		
		public function RemoveAll( Parent:UIComponent):void
		{
			if (removeEnable)
			{
				if (gObj)
				{
					gObj.uiObj = null;
				}
				clearNumber();
				NumType=0;
				TxtType=0;
				gObj = null;
				_compFactory = null;//remove reference
				Parent.removeChild(this);
			}
			else
			{
				visible = false;
				isVisible=false;
			}
		}
		
		public function UpdatePos(DeltaTime:Number):Boolean
		{
			if(isVisible == false)
			{
				return true;
			}
			if (gObj.isOver)
			{
				return false;
			}
			if (gObj.isEnable == false)
			{
				return true;
			}
			gObj.UpdateTween(DeltaTime);
			setActualSize( origWidth*gObj.scaleCur, origHeight*gObj.scaleCur );
			alpha = gObj.alphaCur;
			
			var x1 = posX+gObj.sx;
			var y1 = posY+gObj.sy;
			var z1 = posZ+gObj.sz;
			
			ExternalInterface.call( "ASSetPos3DTo2D", this,x1,y1,z1 );
			return true;
		}
		
		public function clearNumber():void
		{
			if(attack_mc)
			{
				attack_mc.x = 0;
				while(attack_mc.numChildren > 0)
				{
					_compFactory.releaseUsedComponent(attack_mc.removeChildAt(0));
				}
			}
		}
		
		public function StartShow(Parent:UIComponent):void
		{ 
			if (removeEnable)
			{
				Parent.addChild(this);
			}
			
			if ( attack_mc != null )
			{
				clearNumber();
				//				if(yellow_mc==null)
				//			    {
				//				   initConfig();
				//			    }
				visible = true;
				isVisible=true;
				bNeedUpdate = false;
				if(NumType>0)
				{
					var i:int=0;
					var arr:Array=count.toString().split("");
					var l:int=arr.length;
					for(i=0;i<l;i++)
					{
						var num:int=arr[i];
						if(NumType==1)
						{
							var mc:MovieClip = attack_mc["num_"+i] as MovieClip;
							mc.gotoAndStop(num+1);
							mc.visible=true;
						}
						else
						{
							var bit:MovieClip = getNumber();
							if(bit != null)
							{
								bit.x = i*25;
								bit.gotoAndStop(num+1);
								attack_mc.addChild(bit);
							}
						}
					}
				}
				if(TxtType>0)
				{
					var txt_mc:MovieClip = getTxt();
					if(txt_mc != null)
					{
						txt_mc.x=attack_mc.width;
						txt_mc.y=-6;
						attack_mc.addChild(txt_mc);
					}
				}
				if(NumType==1)
				{
					attack_mc.x=-((i*25)>>1);//让伤害数字居中
				}
				else
				{
					attack_mc.x=-(attack_mc.width>>1);//让伤害数字居中
				}
				origWidth = attack_mc.width;
				origHeight = attack_mc.height;
				
			}
			else{
				origWidth = width;
				origHeight = height;
			}
			visible = true;
			isVisible=true;
			UpdatePos(0);
		}
		
	}
}