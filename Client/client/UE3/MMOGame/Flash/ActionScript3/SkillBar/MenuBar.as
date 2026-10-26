package ActionScript3.SkillBar
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.utils.Dictionary;
	import flash.utils.Timer;

	import ActionScript3.MyMenuSlot;
	import ActionScript3.MyPanel;
	import ActionScript3.MyTipButton;
	import ActionScript3.ItemSlot.MyItemSlot;

	import UI_SkillbarWidget.AS3.MenuSlotBtn;

	import scaleform.clik.controls.Button;
	import scaleform.clik.controls.UILoader;
	import scaleform.clik.core.UIComponent;
	import scaleform.clik.events.ButtonEvent;
	import flash.display.Sprite;
	import flash.display.DisplayObject;
	import flash.geom.Point;
	import ActionScript3.Common.Events.ParamEvent;

	public class MenuBar extends MyPanel
	{
		public var MenuList:MovieClip;
		public var MenuListChild:MovieClip;
		public var MenuList2:MovieClip;
		private const MAXMAILS:int = 50;
		private const TOOMUCH:int = 100;

		private const MenuNum:int = 11;
		private const ChildMenuNum:int = 4;
		public const RightMenuStartIdx:int = 1000;
		//右边菜单
		private var RightMenuArr:Array;
		private var RightUnionList:Array;
		private var RightMenuButtonList:Array;
		private var SHowRightMenu:int = 0;

		//左边菜单
		private var LeftMenuArr:Array;
		private var LeftUnionList:Array;
		private var LeftMenuButtonList:Array;

		private var curChildMenuIdx = 0;
		private var curChildMenuType = 0;
		/*
		获得新物品 飞入背包效果
		*/
		private var newBagItemList:Array;
		public var bagNewItem0_mc:MyItemSlot;
		public var bagNewItem1_mc:MyItemSlot;
		private var bagPosX:int;
		private var bagPosY:int;
		private var itemPosX:int;
		private var itemPosY:int;
		private var bShowNewItem:Boolean = false;
		private var speedSeed:Number = 0;
		var newItemTimer:Timer = new Timer(33,0);
		var newItemTimer_DelayStart:Timer = new Timer(50,0);
		var newItemTimer_DelayStart_ing:Boolean = false;

		// 新功能开启效果
		public var new_system_mc:MovieClip;
		public var ok_mc:Button;
		private var new_system_dest_x:int;
		private var new_system_dest_y:int;
		private var new_system_dist_x:int;
		private var new_system_dist_y:int;
		private var new_system_speed:Number = 0.1;
		private var new_system_id:int = 0;
		private var effectDic:Dictionary;
		var new_system_timer:Timer = new Timer(33,0);

		public var guide_left_mc:Sprite=new Sprite();
		public var guide_right_mc:Sprite=new Sprite();
		public var _leftbg:MovieClip;
		public var _rightbg:MovieClip;
		public var txt_dec:TextField;
		override protected function configUI():void
		{
			super.configUI();
			guide_left_mc.mouseChildren = false;
			guide_left_mc.mouseEnabled = false;
			guide_right_mc.mouseChildren = false;
			guide_right_mc.mouseEnabled = false;
			_leftbg.mouseChildren = false;
			_leftbg.mouseEnabled = false;
			_rightbg.mouseChildren = false;
			_rightbg.mouseEnabled = false;
			this.setChildIndex(_leftbg,0);
			this.setChildIndex(_rightbg,1);
			this.addChildAt(guide_left_mc,2);
			this.addChildAt(guide_right_mc,3);
			if (MenuListChild)
			{
				MenuListChild.visible = false;
			}
			effectDic=new Dictionary();
			RightMenuArr = [];
			RightUnionList = [];
			RightMenuButtonList = [];

			LeftMenuArr = [];
			LeftUnionList = [];
			LeftMenuButtonList = [];
			newBagItemList = [];
			for (var j:int = 0; j < ChildMenuNum; j++)
			{
				if (MenuListChild)
				{
					var menuChildBtn:Button = MenuListChild.getChildByName("MenuSlot"+j) as Button;
					menuChildBtn.addEventListener( ButtonEvent.CLICK , clickChildMenuButton );
					menuChildBtn.itemid = j;
				}
			}

			/*           var a:Object = {iconName:"mall",MenuVisible:true, menuType:5 , componentList:[],childMenuList:[{menuName:"包裹",menuType:1,MenuVisible:true ,iconName:"mail",keyName:"B",panelName:"Bag"},{menuName:"英雄",MenuVisible:true,menuType:10 ,iconName:"hero",keyName:"Y",panelName:"Hero"}]};
			var b:Object = {iconName:"mail",MenuVisible:false, menuType:4 ,componentList:["mail_num","envelop"], childMenuList:[{menuName:"包裹",MenuVisible:true,menuType:11 ,iconName:"hero",keyName:"B",panelName:"Bag"}]};
			SetLeftMenuData( [ a ,b,a,a,a,a] );
			SetRightMenuData([ a,a ,b,a,a,a]);*/

			//updateMenuEffect(0,11,true,true);
			//UCGuideMenuEffect(2,11,true,true,"test");

			//UCSetNewMailCount( 1 , 0 ,true );
			//UCUpdateMaxMailCount( 0 , 141 , true );

			newItemTimer.addEventListener(TimerEvent.TIMER,newItemTimerHandle);
			newItemTimer_DelayStart.addEventListener(TimerEvent.TIMER,newItemTimerHandle_DelayStart);

			bagNewItem0_mc.visible = false;
			bagNewItem1_mc.visible = false;
			bagNewItem0_mc.itemSlotBg.visible=false;
			bagNewItem0_mc.itemSlotIcon.slotIcon_bg_mc.visible=false;
			bagNewItem1_mc.itemSlotBg.visible = false;
			bagNewItem1_mc.itemSlotIcon.slotIcon_bg_mc.visible=false;
			bagNewItem0_mc.mouseEnabled = false;
			bagNewItem1_mc.mouseEnabled = false;


			// 新功能开启效果
			new_system_mc.visible = false;
			ok_mc.visible = false;
			ok_mc.addEventListener(MouseEvent.CLICK, onBtClickOk);
			new_system_timer.addEventListener(TimerEvent.TIMER, onNewSystemTimer);
			stageChangeHandler(null);
			/*
			// test
			var new_system_data:Object = new Object();
			new_system_data.src_x = 640;
			new_system_data.src_y = 360;
			new_system_data.new_system_id = 0;
			new_system_data.new_system_icon = "Test.TGA";
			new_system_data.new_system_name = "AAAAA";
			UCShowNewSystem(new_system_data);
			*/
		}

		public function newItemTimerHandle_DelayStart(evt:TimerEvent)
		{
			updateNewItemShow();
			newItemTimer_DelayStart_ing = false;
			newItemTimer_DelayStart.stop();
		}

		public function newItemTimerHandle(evt:TimerEvent)
		{
			if (bShowNewItem)
			{
				if (bagNewItem0_mc.x + 5 >= bagPosX)
				{
					bagNewItem0_mc.alpha -=  0.07;
					if (bagNewItem0_mc.alpha <= 0)
					{
						bagNewItem0_mc.visible = false;
						updateNewItemShow();
						speedSeed = 0;
					}
				}
				else
				{
					speedSeed +=  0.05;
					bagNewItem0_mc.y = itemPosY + 200 * speedSeed * speedSeed;
					bagNewItem0_mc.x +=  5;
				}
			}
		}
		public function updateNewItemShow():void
		{
			newItemTimer_DelayStart_ing = false;
			var nLength:int = newBagItemList.length;

			bagNewItem0_mc.alpha = 1;
			bagNewItem0_mc.x = itemPosX;
			bagNewItem0_mc.y = itemPosY;
			bagNewItem1_mc.x = itemPosX;
			bagNewItem1_mc.y = itemPosY;
			if ( nLength > 1)
			{
				bagNewItem1_mc.SetDataObj(newBagItemList[1]);
				bagNewItem0_mc.SetDataObj(newBagItemList[0]);
				bagNewItem0_mc.visible = true;
				bagNewItem1_mc.visible = true;
				bShowNewItem = true;
				newBagItemList.shift();
			}
			else if (nLength == 1)
			{
				bagNewItem0_mc.SetDataObj(newBagItemList[0]);
				bagNewItem0_mc.visible = true;
				bagNewItem1_mc.visible = false;
				bShowNewItem = true;
				newBagItemList.shift();
			}
			else
			{
				bShowNewItem = false;
				bagNewItem0_mc.visible = false;
				bagNewItem1_mc.visible = false;
			}

			if (bShowNewItem)
			{
				newItemTimer.start();
			}
			else
			{
				newItemTimer.stop();
			}
		}
		public function UCAddNewItemHint(data:Object):void
		{
			newBagItemList.push(data);

			if (newItemTimer_DelayStart_ing==false)
			{
				if (! bShowNewItem)
				{
					newItemTimer_DelayStart_ing = true;
					newItemTimer_DelayStart.start();
				}
				else
				{
					var nLength:int = newBagItemList.length;
					if (nLength == 1)
					{
						bagNewItem1_mc.visible = true;
						bagNewItem1_mc.SetDataObj(newBagItemList[0]);
					}
				}
			}
		}

		override protected function stageChangeHandler(evt:ParamEvent):void
		{
			super.stageChangeHandler(evt);
			RePos();
		}

		private function RePos():void
		{
			MenuList2.x = cavasWidth - (32 * this.SHowRightMenu);
			MenuList2.y = (cavasHeight - 34);

			bagPosX = MenuList2.x + 26;
			bagPosY = MenuList2.y;

			itemPosX = bagPosX - 100;
			itemPosY = bagPosY - 200;
			_leftbg.width = MenuList.width;
			_rightbg.width = MenuList2.width;
			_rightbg.x = MenuList2.x + 5;
			_rightbg.y = MenuList2.y + 6;
			guide_left_mc.x = MenuList.x;
			guide_left_mc.y = MenuList.y;
			guide_right_mc.x = cavasWidth - 400;
			guide_right_mc.y = cavasHeight - 200;
			this.new_system_mc.x=(cavasWidth-463>>1)+247;
			this.new_system_mc.y=(cavasHeight - 296>>1)+150;
			ok_mc.x = this.new_system_mc.x - 13;
			ok_mc.y = this.new_system_mc.y + 46;
		}

		/*public function DelMenuUnion( startIdx:int , count:int , right:Boolean ):void
		{
		var bar:MovieClip;
		if (right)
		{
		bar = MenuList2;
		}
		else
		{
		bar = MenuList;
		}
		for (var i:int = startIdx; i < startIdx+count; i++)
		{
		var butt:MyMenuButton;
		var union:MovieClip;
		if (right)
		{
		butt = RightMenuButtonList[i];
		union = RightUnionList[i];
		}
		else
		{
		butt = LeftMenuButtonList[i];
		union = LeftUnionList[i];
		}
		
		if (butt)
		{
		butt.removeEventListener( ButtonEvent.CLICK , clickMenuButton );
		}
		
		if ( union && butt )
		{
		union.removeEventListener( MouseEvent.MOUSE_OVER , overMenuButton );
		union.removeEventListener( MouseEvent.MOUSE_OUT , outMenuButton );
		union.removeChild( butt );
		}
		//trace( "del:" + butt );
		bar.removeChild( union );
		}
		
		if (right)
		{
		RightMenuButtonList.splice( startIdx , count );
		RightUnionList.splice( startIdx , count );
		}
		else
		{
		LeftMenuButtonList.splice( startIdx , count );
		LeftUnionList.splice( startIdx , count );
		}
		
		}*/

		public function UCGuideMenuEffect(idx:int,childType:int ,left:Boolean,pl:Boolean,_display:String):void
		{
			if (pl == true)
			{
				var butt:MyMenuButton = GetMenuButton(idx,left);
				var buttPos:Point = butt.localToGlobal(new Point(butt.x,butt.y));
				if (left==true)
				{
					var guide_mc:MovieClip = guide_left_mc.getChildByName(_display) as MovieClip;
					if (guide_mc)
					{
						var guide_panel_mc:MovieClip = guide_mc.getChildByName("guide_panel_mc") as MovieClip;
						if (guide_panel_mc)
						{
							guide_panel_mc.x = buttPos.x - guide_left_mc.x;
							guide_panel_mc.y = buttPos.y - guide_left_mc.y + butt.height;
						}
					}
				}
				else
				{

					guide_mc = guide_right_mc.getChildByName(_display) as MovieClip;
					if (guide_mc)
					{
						guide_panel_mc = guide_mc.getChildByName("guide_panel_mc") as MovieClip;
						if (guide_panel_mc)
						{
							guide_panel_mc.x = buttPos.x - guide_right_mc.x + butt.width;
							guide_panel_mc.y = buttPos.y - guide_right_mc.y;
						}
					}
				}

				updateChildMeunEffect(childType);
			}
			else
			{
				if (left==true)
				{
					guide_mc = guide_left_mc.getChildByName(_display) as MovieClip;
					if (guide_mc)
					{
						guide_left_mc.removeChild(guide_mc);
					}
				}
				else
				{
					guide_mc = guide_right_mc.getChildByName(_display) as MovieClip;
					if (guide_mc)
					{
						guide_right_mc.removeChild(guide_mc);
					}
				}
				delectChildMenuEffect(childType);
			}
		}

		public function clearGuide():void
		{
			for (var i:* in effectDic)
			{
				delete effectDic[i];
			}
			effectDic = null;
			effectDic=new Dictionary();
			while (guide_left_mc.numChildren > 0)
			{
				guide_left_mc.removeChildAt(0);
			}
			while (guide_right_mc.numChildren>0)
			{
				guide_right_mc.removeChildAt(0);
			}
		}

		public function updateMenuEffect( idx:int,childType:int ,left:Boolean,pl:Boolean):void
		{
			var butt:MyMenuButton = GetMenuButton(idx,left);
			butt.effect(pl);
			if (pl==true)
			{
				updateChildMeunEffect(childType);
			}
			else
			{
				delectChildMenuEffect(childType);
			}
		}

		public function updateChildMeunEffect(childType:int):void
		{
			if (childType>-1)
			{
				effectDic[childType] = childType;
			}
		}

		public function delectChildMenuEffect(childType:int):void
		{
			if (childType>-1)
			{
				delete effectDic[childType];
			}
		}

		private function SetMenuData(MenuArr:Array,Menuunion:Array,right:Boolean):void
		{
			var l:int = MenuArr.length;
			var i:int = 0;
			var k:int = 0;
			var menuBtn:MyMenuButton;
			for (i=0; i<l; i++)
			{
				if (Menuunion[i])
				{
					menuBtn = Menuunion[i].getChildByName("MenuButton"+i) as MyMenuButton;
				}
				if (menuBtn==null)
				{
					menuBtn = this.NewMenuUnion(i,right);
				}
				var bl:Boolean = MenuArr[i].MenuVisible;
				//menuBtn.visible = bl;
				Menuunion[i].visible = bl;
				if (bl==true)
				{
					Menuunion[i].x = k * menuBtn.width;
					menuBtn.itemdataid = MenuArr[i].menuType;
					k++;
					if (right)
					{
						SHowRightMenu = k;
					}
					var componentList:Array = MenuArr[i].componentList as Array;
					if (componentList)
					{
						if (menuBtn.componentList == null)
						{
							for (var j:int = 0; j < componentList.length; j++)
							{
								menuBtn.AddComponent( componentList[j] );
							}
						}
					}
					var icon:MovieClip = menuBtn.getChildByName("icon") as MovieClip;
					if (icon)
					{
						icon.gotoAndStop( MenuArr[i].iconName );
						(icon._item as MovieClip).gotoAndStop(1);
					}
				}
				menuBtn = null;
			}
		}

		public function SetRightMenuData( dat:Array ):void
		{
			if (dat==null && dat.length==0)
			{
				return;
			}
			RightMenuArr = dat;
			if (RightUnionList)
			{
				SetMenuData(RightMenuArr,RightUnionList,true);
			}
			stageChangeHandler(null);
		}

		/*public function SetMenuButtonNum( num:int , right:Boolean ):void
		{
		if(RightUnionList==null && LeftUnionList==null)
		{
		return;
		}
		var curNum:int = 0;
		if( right )
		{
		    curNum = RightUnionList.length;
		}
		else
		{
		curNum = LeftUnionList.length;
		}
		var i:int = 0;
		if ( num < curNum )
		{
		DelMenuUnion( num , curNum - num , right );
		}
		else 
		if ( num > curNum )
		{
		for (i = curNum; i < num; i++)
		{
		NewMenuUnion( i , right );
		}
		}
		if (right)
		{
		stageChangeHandler(null);
		}
		}*/

		private function NewMenuUnion( idx:int , right:Boolean ):MyMenuButton
		{
			var bar:MovieClip;
			if (right)
			{
				bar = MenuList2;
			}
			else
			{
				bar = MenuList;
			}
			var menuBtn:MyMenuButton = new MenuSlot();
			if (menuBtn)
			{
				var union:MovieClip = new MovieClip();
				union.x = menuBtn.width * idx;
				union.y = 0;
				union.name = "MenuUnion" + idx;
				union.addChild( menuBtn );
				bar.addChild( union );
				menuBtn.name = "MenuButton" + idx;
				menuBtn.itemid = idx + ( right ? RightMenuStartIdx:0 );
				menuBtn.x = 2;
				if (right==true)
				{
					menuBtn.y = 2;
				}
				else
				{
					menuBtn.y = -1;
				}
				if (right)
				{
					if (RightUnionList && RightMenuButtonList)
					{
						RightUnionList.push( union );
						RightMenuButtonList.push( menuBtn );
					}
				}
				else
				{
					if (LeftUnionList && LeftMenuButtonList)
					{
						LeftUnionList.push( union );
						LeftMenuButtonList.push( menuBtn );
					}
				}
				menuBtn.addEventListener( ButtonEvent.CLICK , clickMenuButton );
				union.addEventListener(MouseEvent.MOUSE_OVER , overMenuButton );
				union.addEventListener(MouseEvent.MOUSE_OUT , outMenuButton );

			}
			return menuBtn;
		}

		public function SetLeftMenuData( dat:Array ):void
		{
			if (dat==null)
			{
				return;
			}
			LeftMenuArr = dat;
			if (LeftUnionList)
			{
				SetMenuData(LeftMenuArr,LeftUnionList,false);
				_leftbg.width = MenuList.width;
			}
			/*updateMenuEffect(0,true,true);
			updateMenuEffect(2,true,true);
			updateMenuEffect(4,true,true);*/
		}

		private function clickChildMenuButton(e:Event):void
		{
			if (e.target is Button)
			{
				ExternalInterface.call( "ASMenuChildClick" , curChildMenuIdx , curChildMenuType , ( e.target as Button ).itemid , ( e.target as Button ).itemdataid );
			}
		}

		private function clickMenuButton(e:Event):void
		{
			if (e.target is Button)
			{
				ExternalInterface.call( "ASMenuClick" ,  ( e.target as Button ).itemid , ( e.target as Button ).itemdataid );
			}
		}

		private function overMenuButton(e:MouseEvent):void
		{
			if (MenuListChild)
			{
				MenuListChild.visible = true;
			}
			var targetButton:Button = e.target as Button;
			if (! targetButton)
			{
				targetButton = e.target.parent as Button;
			}
			if (! targetButton)
			{
				return;
			}
			if (targetButton.parent == MenuListChild)
			{
				return;
			}

			if (MenuListChild&&targetButton)
			{
				curChildMenuIdx = targetButton.itemid;
				curChildMenuType = targetButton.itemdataid;
				targetButton.parent.addChild( MenuListChild );

				MenuListChild.x = targetButton.x;
				MenuListChild.y = targetButton.y + targetButton.height;

				var realIdx:int;
				var right:Boolean;
				var left:Boolean;
				var childMenuList:Array;

				if (targetButton.itemid >= RightMenuStartIdx)
				{
					realIdx = targetButton.itemid - RightMenuStartIdx;
					right = true;
					childMenuList = RightMenuArr[realIdx].childMenuList as Array;
				}
				else
				{
					realIdx = targetButton.itemid;
					right = false;
					childMenuList = LeftMenuArr[realIdx].childMenuList as Array;
				}
				left = ! right;
				if (childMenuList)
				{
					var j:int = 0;
					var l:int = childMenuList.length;
					var k:int;
					var childMenu:MenuSlotBtn;
					var bg:MovieClip = MenuListChild.getChildByName("bg") as MovieClip;
					if (bg==null)
					{
						return;
					}
					bg.height = 5;
					for (j = 0; j < l; j++)
					{
						childMenu = MenuListChild.getChildByName( "MenuSlot"+j ) as MenuSlotBtn;
						if (childMenu)
						{
							var bl:Boolean = childMenuList[j].MenuVisible;
							childMenu.visible = bl;
							if (bl)
							{
								childMenu.y = 5 + (k * 26);
								bg.height = childMenu.y + childMenu.height + 5;
								k++;
							}
							childMenu.label = childMenuList[j].menuName;
							childMenu.itemdataid = childMenuList[j].menuType;
							var key:TextField = childMenu.getChildByName("tF_Key") as TextField;
							if (key)
							{
								key.text = childMenuList[j].keyName;
							}
							var icon:MovieClip = childMenu.getChildByName("icon") as MovieClip;
							if (icon)
							{
								icon.gotoAndStop(  childMenuList[j].iconName );
							}
							var item:MovieClip = childMenu.getChildByName("_item") as MovieClip;
							if (item)
							{
								item.gotoAndStop(1);
								if (effectDic[childMenu.itemdataid] != undefined)
								{
									item.gotoAndPlay(1);
								}
							}
						}
					}
					//把不用的给隐藏掉
					for (j = l; j < ChildMenuNum; j++)
					{
						childMenu = MenuListChild.getChildByName( "MenuSlot"+j ) as MenuSlotBtn;
						if (childMenu)
						{
							childMenu.visible = false;
						}
					}
				}
				if (e.stageY + bg.height >= this.cavasHeight)
				{
					MenuListChild.y = targetButton.y - bg.height;
					if (e.stageX + MenuListChild.width > cavasWidth)
					{
						MenuListChild.x = targetButton.x-(e.stageX+MenuListChild.width-cavasWidth);
					}
				}
			}
		}

		private function outMenuButton(e:Event):void
		{
			if (MenuListChild)
			{
				MenuListChild.visible = false;
			}
		}

		private function GetMenuButton( idx:int , left:Boolean ):MyMenuButton
		{
			var butt:MyMenuButton;
			if (left)
			{
				butt = LeftMenuButtonList[idx];
			}
			else
			{
				butt = RightMenuButtonList[idx];
			}
			return butt;
		}

		public function UCSetNewMailCount( idx:int , count:int , left:Boolean ):void
		{
			var butt:MyMenuButton = GetMenuButton(idx,left);

			if (! butt)
			{
				return;
			}
			var compo:MovieClip = butt.getChildByName("mail_num") as MovieClip;

			if (! compo)
			{
				return;
			}
			var txt:TextField = compo.getChildByName("new_mail_count_txt") as TextField;

			if (! txt)
			{
				return;
			}

			if (0 <= count && count < TOOMUCH)
			{
				txt.text = count.toString();
			}
			else if (count >= TOOMUCH)
			{
				txt.text = "*";
			}

			if (count == 0)
			{
				compo.visible = false;
				txt.visible = false;
			}
			else
			{
				compo.visible = true;
				txt.visible = true;
			}
		}

		public function UCUpdateMaxMailCount( idx:int , count:int , left:Boolean ):void
		{
			var butt:MyMenuButton = GetMenuButton(idx,left);
			if (! butt)
			{
				return;
			}

			var envelop_mc:MovieClip = butt.getChildByName("envelop") as MovieClip;
			if (MAXMAILS <= count)
			{
				if (null != envelop_mc)
				{
					envelop_mc.gotoAndStop("full");
				}
			}
			else if (0 <= count && count < MAXMAILS)
			{
				if (null != envelop_mc)
				{
					envelop_mc.gotoAndStop("normal");
				}
			}
		}

		public function UCShowNewSystem(data:Object):void
		{
			new_system_mc.visible = true;
			new_system_mc.x = data.src_x;
			new_system_mc.y = data.src_y;

			new_system_mc.alpha = 1.0;
			new_system_mc.scaleX = 1.0;
			new_system_mc.scaleY = 1.0;
			ok_mc.x = this.new_system_mc.x - 13;
			ok_mc.y = this.new_system_mc.y + 46;
			var icon_mc:UILoader = new_system_mc.getChildByName("loader_mc") as UILoader;
			icon_mc.source = data.new_system_icon;
			var name_tf:TextField = new_system_mc.getChildByName("name_tf") as TextField;
			name_tf.text = data.new_system_name;

			new_system_id = data.new_system_id;
			new_system_mc.startEffect();
		}

		public function UCActivateNewSystem(data:Object):void
		{
			if (new_system_mc.visible)
			{
				var name_tf:TextField = new_system_mc.getChildByName("name_tf") as TextField;
				name_tf.visible = false;
				//var ok_mc:Button = new_system_mc.getChildByName("ok_mc") as Button;
				ok_mc.visible = false;

				new_system_dest_x = data.dest_x;
				new_system_dest_y = data.dest_y;

				new_system_dist_x = Math.abs(new_system_dest_x - new_system_mc.x);
				new_system_dist_y = Math.abs(new_system_dest_y - new_system_mc.y);

				new_system_timer.start();
			}
		}

		public function onBtClickOk():void
		{
			/*
			// test
			var new_system_data:Object = new Object();
			new_system_data.dest_x = 32;
			new_system_data.dest_y = 32;
			UCActivateNewSystem(new_system_data);
			*/
			ExternalInterface.call("ASActivateNewSystem", new_system_id);
		}

		public function onNewSystemTimer(e:TimerEvent)
		{
			if (new_system_mc.visible)
			{
				new_system_mc.alpha = Math.abs(new_system_dest_x - new_system_mc.x) / new_system_dist_x;
				new_system_mc.scaleX = Math.abs(new_system_dest_x - new_system_mc.x) / new_system_dist_x;
				new_system_mc.scaleY = Math.abs(new_system_dest_x - new_system_mc.x) / new_system_dist_x;

				new_system_mc.x +=  (new_system_dest_x - new_system_mc.x) * new_system_speed;
				new_system_mc.y +=  (new_system_dest_y - new_system_mc.y) * new_system_speed;

				if (new_system_mc.alpha <= 0.1)
				{
					new_system_mc.visible = false;
					new_system_id = 0;
					new_system_timer.stop();
					/*
					// test
					var new_system_data:Object = new Object();
					new_system_data.src_x = 640;
					new_system_data.src_y = 360;
					new_system_data.new_system_id = 0;
					new_system_data.new_system_icon = "Test.TGA";
					new_system_data.new_system_name = "AAAAA";
					UCShowNewSystem(new_system_data);
					*/
					ExternalInterface.call("ASShowNextNewSystem");
				}
			}
		}
	}
}