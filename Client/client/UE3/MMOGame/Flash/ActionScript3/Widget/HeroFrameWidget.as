package ActionScript3.Widget
{
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	import flash.utils.getTimer;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import flash.events.Event;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.controls.Button;

	public class HeroFrameWidget extends MyPanel
	{
		public var heroLevelText:TextField;
		public var HeroName_mc:TextField;
		public var heroHpFill_mc:MovieClip;
		public var heroProIcon:MovieClip;
		public var uncall_btn:Button;
		public var bag_btn:Button;
		public var mode1_btn:Button;
		public var mode2_btn:Button;
		public var mode3_btn:Button;
		public var mode4_btn:Button;

		override protected function configUI():void
		{
			super.configUI();

			bag_btn.enabled = false;

			mode1_btn.addEventListener( "click",FunMode1 );
			mode1_btn.addEventListener("rollOver" ,function _showTips(e:Event){ ShowTips(e,1);});
			mode1_btn.addEventListener("rollOut" ,RollOut);

			mode2_btn.addEventListener( "click",FunMode2 );
			mode2_btn.addEventListener("rollOver" ,function _showTips(e:Event){ ShowTips(e,2);});
			mode2_btn.addEventListener("rollOut" ,RollOut);

			mode3_btn.addEventListener( "click",FunMode3 );
			mode3_btn.addEventListener("rollOver" ,function _showTips(e:Event){ ShowTips(e,3);});
			mode3_btn.addEventListener("rollOut" ,RollOut);

			mode4_btn.addEventListener( "click",FunMode4 );
			mode4_btn.addEventListener("rollOver" ,function _showTips(e:Event){ ShowTips(e,4);});
			mode4_btn.addEventListener("rollOut" ,RollOut);

			bag_btn.addEventListener( "click",FunBug );
			bag_btn.addEventListener("rollOver" ,function _showTips(e:Event){ ShowTips(e,5);});
			bag_btn.addEventListener("rollOut" ,RollOut);

			uncall_btn.addEventListener( "click",FunUnCall );
			uncall_btn.addEventListener("rollOver" ,function _showTips(e:Event){ ShowTips(e,6);});
			uncall_btn.addEventListener("rollOut" ,RollOut);


			///ExternalInterface.call( "RegisterHeroInfo", this);

			//this.visible = false;
			//var HeroObj:Object = {HasHero:true,Level:12,Name:"草上飞",ClassID:2,IsSummon:true};

			//SetHeroInfo(HeroObj);
		}

		public function SetHeroInfo(data:Object)
		{
			this.visible = data.HasHero;
			heroLevelText.text = data.Level;
			HeroName_mc.text = data.Name;
			SetHp(data.curHp,data.maxHp);
			heroProIcon.roleIcon.source = data.IconName;
			//heroProIcon.gotoAndStop(data.ClassID);
			uncall_btn.enabled = data.IsSummon;
			mode1_btn.enabled = data.IsSummon;
			mode2_btn.enabled = data.IsSummon;
			mode3_btn.enabled = data.IsSummon;
			mode4_btn.enabled = data.IsSummon;
			if (data.HeroAi == 1)
			{
				mode1_btn.selected = true;
				mode2_btn.selected = false;
				mode3_btn.selected = false;
				mode4_btn.selected = false;
			}
			else if (data.HeroAi==2)
			{
				mode1_btn.selected = false;
				mode2_btn.selected = true;
				mode3_btn.selected = false;
				mode4_btn.selected = false;
			}
			else if (data.HeroAi==3)
			{
				mode1_btn.selected = false;
				mode2_btn.selected = false;
				mode3_btn.selected = true;
				mode4_btn.selected = false;
			}
			else if (data.HeroAi==4)
			{
				mode1_btn.selected = false;
				mode2_btn.selected = false;
				mode3_btn.selected = false;
				mode4_btn.selected = true;
			}
		}

		public function FunMode1()
		{
			ExternalInterface.call("FunMode",1);
		}
		public function FunMode2()
		{
			ExternalInterface.call("FunMode",2);
		}
		public function FunMode3()
		{
			ExternalInterface.call("FunMode",3);
		}
		public function FunMode4()
		{
			ExternalInterface.call("FunMode",4);
		}
		public function FunBug()
		{
			ExternalInterface.call( "ASHeroBag");
		}
		public function FunUnCall()
		{
			ExternalInterface.call( "ASHeroUncall");
		}

		function SetHp(curHp:Number, maxHp:Number)
		{
			if (maxHp>=curHp && maxHp>0)
			{
				(heroHpFill_mc.hpMask as MovieClip ).scaleX = curHp/maxHp;
			}
			else
			{
				(heroHpFill_mc.hpMask as MovieClip ).scaleX = 1.0;
			}
		}


		function ShowTips(e:Event,index:Number)
		{
			ExternalInterface.call("ASGetStringByID",this,"tipsHtml","MMOGame.HeroFrame.Tips"+index );
			ExternalInterface.call("ASShowTips_PlainText",this );
		}

		function HideTips()
		{
			ExternalInterface.call("ASHideTips_PlainText",this );
		}
		
		function RollOut( e:Event  )
		{
			HideTips();
		}
	}
}