package UI_WeaponSkill.WeaponSkillAS3
{
	import ActionScript3.MyPanel;
	import ActionScript3.ItemSlot.MyItemSlot;
	import scaleform.clik.controls.Button;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;

	import flash.display.MovieClip;
	import ActionScript3.Common.Utils.StyleType;
	import scaleform.clik.core.UIComponent;
	import UI_WeaponSkill.WeaponSkillAS3.WeaponSkillData;
	import ActionScript3.Common.TimerManager;
	import scaleform.clik.motion.Tween;
	import flash.text.TextFieldAutoSize;
	
	
	public class WeaponSkillPanel extends MyPanel
	{
		public var WeaponSlotMc:MyItemSlot;//武器 
		public var btn_baptize:Button;
		public var txt_gold:TextField;//显示金币数量
		public var ItemslotMc:MyItemSlot;
		public var skillitem0:SkillItem;
		public var skillitem1:SkillItem;
		public var mc_effect:MovieClip;
        public var effectId:int=-1;
		private var tt:int;
		private var _myItemNum:int;
		private var _minItemNum:int;
		public var mc_gif:MovieClip;
		public var _Titlebg:MovieClip;
		public var txt_num:TextField;
		override protected function configUI():void
		{
			super.configUI();
			clear();
			UCSetIsGuildEdition(false);
			btn_baptize.addEventListener(MouseEvent.CLICK,clickHandler);
			ItemslotMc.itemSlotBg.visible = false;
			UCSetWeaponSkillTotalCount(1);
			//UCSetMoneyNeed("124");
			//UCSetGuildNeeds("9990");
			//testData();
			//ExternalInterface.call( "RegisterWeaponSkill", this );
			//UCSetItemData(1101,"1.TGA",1,28);
			//UCUpdateItemNum(10,10);
			//TimerManager.getInstance().add(5000,testData);
		}
		
/*		private function testData():void
		{
			var arr:Array=[];
			var obj:Object=new WeaponSkillData();
			obj.skillName="技能名称";
			obj.skillDec="技能描述技能描述技能描述技能描述技能描述技能描述技能描述技能描述技能描述";
			obj.iconName="1.TGA";
			obj.skillID=10010;
			obj.tipsType=12;
			arr.push(obj);
			UCUpdateSkillInfoOfWeapon(arr);
		}*/
		
		public function UCSetItemData(ItemTemplateID:int,iconName:String,itemColor:int,slotType:int):void
		{
			//ItemslotMc.SetSlotType( slotType );
			ItemslotMc.SetData(0,iconName,ItemTemplateID,"",itemColor,-1,-1);
			if( iconName == "" )
			{
				ItemslotMc.itemSlotBg.visible = false;
			}
			else
			{
				ItemslotMc.itemSlotBg.visible = true;
				updateItemNum();
			}
		}
		
		public function UCUpdateItemNum(minItemNum:int,myItemNum:int):void
		{
			_myItemNum=myItemNum;
			_minItemNum=minItemNum;
			updateItemNum();
			//ItemslotMc.updateItemData(minItemNum,myItemNum);
		}
		
		private function updateItemNum():void
		{
			if(ItemslotMc.valueAmount)
			{
				ItemslotMc.valueAmount.visible=true;
				ItemslotMc.valueAmount.text=_minItemNum+"/"+_myItemNum;
				if(_minItemNum>_myItemNum)
				{
					ItemslotMc.valueAmount.textColor=0xFF0000;
				}
				else
				{
					ItemslotMc.valueAmount.textColor=0xFFFFFF;
				}
				if(_myItemNum==0 && ItemslotMc.itemSlotIcon)
				{
					ItemslotMc.filters=[StyleType.getInstance().getBlackFilter()];
				}
				else
				{
					ItemslotMc.filters=null;
				}
			}
		}
		
		public function UCSetWeaponSkillTotalCount(cnt:int):void
		{
			if(cnt==1)
			{
				mc_gif.visible=true;
			}
			else
			{
				mc_gif.visible=false;
			}
		}
		
				//控制特效哪一条播放
		public function UCUpdateEffect(dat:int):void
		{
			mc_effect.gotoAndStop(1);
			mc_effect.visible=false;
			effectId=dat;//特效
		    ExternalInterface.call( "ASTrace", "UCUpdateEffect"+dat);
			mc_effect.y=188+(dat*97);
			mc_effect.visible=true;
			mc_effect.gotoAndPlay(1);
			var item:SkillItem=this.getChildByName("skillitem"+dat) as SkillItem;
			if(item){
				item.alpha=0.2;
				var tween:Tween=new Tween(1000,item,{alpha:1},{onComplete:onComplete});
			}
			//sound
			playSound("Update_WeaponSkill_FX");
		}
		
	    private function onComplete():void
		{
			//item.alpha=1;
		}
		
		
		private function clickHandler(evt:MouseEvent):void
		{
			ExternalInterface.call( "ASClickToTryGetWeaponSkill");
		}
		
		//更新铭文数据
		public function UCUpdateSkillInfoOfWeapon(dat:Array):void
		{
			clear();
			if(dat){
				var i:int=0;
				for(i=0;i<2;i++){
					var obj:WeaponSkillData=dat[i];
					var item:SkillItem=this.getChildByName("skillitem"+i) as SkillItem;
					if(obj){
						ExternalInterface.call( "ASTrace", "UCUpdateSkillInfoOfWeapon"+obj.skillName);
						item.setData(obj);
						item.visible=true;
					}else{
						item.visible=false;
					}
				}
			}
		}
		//更新公会贡献
		public function UCSetGuildNeeds(dat:String):void
		{
			txt_num.htmlText="<font color='#fbd671'>公会贡献: </font>"+dat;
		}
		public function clear():void
		{
			mc_effect.visible=false;
			mc_effect.gotoAndStop(1);
			skillitem0.visible=false;
			skillitem1.visible=false;
		}
		
		//显示隐藏公会贡献UI
		public function UCSetIsGuildEdition(bl:Boolean):void
		{
			if(bl==true)
			{
				txt_gold.x=90;
				txt_gold.y=453;
				txt_gold.autoSize=TextFieldAutoSize.LEFT;
			}
			else
			{
				txt_gold.x=144;
				txt_gold.y=455;
				txt_gold.autoSize=TextFieldAutoSize.CENTER;
				txt_num.htmlText="";
			}
			_Titlebg.visible=bl;
			txt_num.visible=bl;
		}
		
		//设置更新金币数量
		public function UCSetMoneyNeed(dat:String):void
		{
			txt_gold.htmlText="<font color='#fbd671'>金币: </font>"+dat;
		}

		//设置武器变灰
		public function GraySlot(isGray:Boolean ):void
		{
			if (isGray)
			{
				WeaponSlotMc.filters = [StyleType.getInstance().getBlackFilter()];
			}
			else
			{
				WeaponSlotMc.filters = null;
			}
		}
	}
}