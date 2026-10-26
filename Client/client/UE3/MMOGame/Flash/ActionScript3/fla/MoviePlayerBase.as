package ActionScript3.fla
{
	import scaleform.clik.core.UIComponent;
	import flash.external.ExternalInterface;
	import ActionScript3.ItemSlot.MyItemSlot;
	import ActionScript3.MyItemSlotShow;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import scaleform.clik.controls.Label;
	import ActionScript3.Widget.CharactorPanel;
	import ActionScript3.MyPanel;
	import scaleform.gfx.Extensions;

	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.ui.Mouse;
	import ActionScript3.DropIcon;
	import flash.utils.getDefinitionByName;
	import ActionScript3.MyActivePanel;
	import ActionScript3.Widget.MyRClickMenu;
	import ActionScript3.MyIconConponent;
	import ActionScript3.Widget.MyDamageLevel;
	import scaleform.clik.controls.Button;
	import flash.display.DisplayObject;
	import flash.display.StageScaleMode;
	import flash.utils.getQualifiedClassName;
	import flash.display.StageAlign;
	import ActionScript3.GameDispathcher;
	import ActionScript3.Common.Events.ParamEvent;
	import scaleform.clik.core.CLIK;

	public class MoviePlayerBase extends UIComponent
	{
		override protected function draw():void
		{
			super.draw();
			root.stage.scaleMode = StageScaleMode.NO_SCALE;
			root.stage.align = StageAlign.TOP_LEFT;
			ReSizeStage();
		}

		public function _ReSizeStage(evt:Event):void
		{
			GameDispathcher.getInstance().StageWidth = root.stage.stageWidth;
			GameDispathcher.getInstance().StageHeight = root.stage.stageHeight;
			GameDispathcher.getInstance().dispatchEvent(new ParamEvent(ParamEvent.STAGECHANGE,null));
			ReSizeStage();
		}
		
		public function ReSizeStage():void
		{
			var i:int;
			for (i = 0; i< this.numChildren; i++)
			{
				var obj:DisplayObject = this.getChildAt(i);
				var Panel:MyPanel = obj as MyPanel;
				trace("MoviePlayerBase::ReSizeStage panel:", Panel,  obj, flash.utils.getQualifiedClassName(obj), obj.parent, flash.utils.getQualifiedClassName(obj.parent));
				if (Panel)
				{
					trace("-------ReSizeStage Panel:", Panel);
					Panel.UpdatePos(root.stage.stageWidth,root.stage.stageHeight);
				}
			}
		}

		override protected function configUI():void
		{
			super.configUI();
			root.stage.removeEventListener(Event.RESIZE,_ReSizeStage);
			root.stage.addEventListener( Event.RESIZE , _ReSizeStage );//只监听父容器的舞台大小改变
		}
		
		public function GetMouseTopMostEntity()
		{
			var topMostObject:DisplayObject = Extensions.getMouseTopMostEntity();
			ExternalInterface.call( "ASGetMouseTopMostEntity", topMostObject );
		}

		public function WidgetDispatchEvent( mc:MovieClip ,mouseevent:String )
		{
			mc.dispatchEvent( new MouseEvent(mouseevent) );
		}


		public function RemoveChildWidget( ParentMc:MovieClip , ChildMc:DisplayObject )
		{
			if ( ParentMc && ChildMc )
			{
				trace("MoviePlayerBase::RemoveChildWidget ",ParentMc, ChildMc );
				ParentMc.removeChild( ChildMc );
			}
		}

		public function SetItemData( mc:MyItemSlot, quantity:int, iconname:String, itemindex:int, slotType:int, type:String, itemColor:int, containerID:int, slotID:int )
		{
			//ExternalInterface.call( "ASTrace", "MoviePlayer::SetItemData type:" + type + " SlotType:" + slotType + " ContainerID:" + containerID + " SlotID:" + slotID + " Icon:" + iconname );
			if (mc)
			{
				mc.SetSlotType(slotType);
				
				//ExternalInterface.call( "ASTrace", "MoviePlayer::SetData type:" + type + " SlotType:" + slotType + " ContainerID:" + containerID + " SlotID:" + slotID + " Icon:" + iconname );
				mc.SetData(quantity, iconname, itemindex, type, itemColor, containerID, slotID);				
			}
		}

		public function SetItemShowData( mc:MyItemSlotShow, quantity:int, iconname:String, itemID:int, itemColor:int, containerID:int, slotID:int )
		{
			if (mc)
			{
				mc.SetData(quantity, iconname, itemID, itemColor, containerID, slotID);
			}
		}

		public function FindChild( obj:Object )
		{
			if ( obj is TextField )
			{
				var FontString:String = (obj as TextField).defaultTextFormat.font.toString();
				if( FontString != "FZCuYuan-M03" && FontString != "Microsoft YaHei" )
				{
					if( (obj as TextField).parent )
					{
						trace( FontString +":"+ (obj as TextField).parent.name + "/" + (obj as TextField).name  );
					}
					else
					{
						trace( FontString +":"+ (obj as TextField).name  );
					}
					
				}

			}
			else if ( obj is MovieClip )
			{
				var i:int;

				for (i = 0; i< (  obj as MovieClip ).numChildren; i++)
				{
					FindChild( (  obj as MovieClip ).getChildAt( i ) );
				}
			}
		}

		function GetLastTopUIComponent( mc:DisplayObject ):UIComponent
		{
			if ( mc is UIComponent )
			{
				return ( mc as UIComponent);
			}
			else if ( mc.parent )
			{
				return GetLastTopUIComponent( mc.parent );
			}

			return null;

		}
	}
}