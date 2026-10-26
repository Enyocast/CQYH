
package ActionScript3{

import flash.display.MovieClip;
import flash.external.ExternalInterface;
import flash.events.Event;
import flash.events.MouseEvent;

import flash.text.TextField;

import scaleform.clik.events.ButtonEvent;
import scaleform.clik.core.UIComponent;
import scaleform.clik.controls.Label;
import scaleform.clik.controls.Button;

	public class MyMenuSlot extends Button
{
	public var icon_mc:MovieClip;
	public var skillicon_mc:MovieClip;
	public var ItemButton_mc:Button;
	public var ItemText:Label;
	public var BG_mc:MovieClip;
	public var tF_Key:TextField;
	public var tF_SlotName:TextField;
	
	[Inspectable(type="Number", name="_SlotType")]
	var SlotType = 0;//
	

	[Inspectable(type="Boolean", name="_bDisableDrag")] 
	var bDisableDrag = false; //
	
	
	
	public var icon:MovieClip;
	//var tempItemData:ItemSlotData;
	
	var Mode = 0;
	var bDrag = false;
	var bOver = false;
	var bPressed = false;
	var _MenuId:Number = 0;
	

	public function set MenuId( id)
	{ 
		_MenuId = id;
		//trace(_MenuId);
		UpdateData();
	}
	public function get MenuId():Number
	{
		return _MenuId;
	}
	public function set _SlotType(nType){
		SlotType = nType;
	}
	
	public function MyMenuSlot() {
		super();
		visible = true;
		
		

	}
	
	
	//configUI()这个调用非常晚啊，比外部的初始化赋值都晚
	override protected  function configUI():void {
		super.configUI();
		this.addEventListener(ButtonEvent.PRESS ,DragIn);
		this.addEventListener(ButtonEvent.RELEASE_OUTSIDE,DragRelease);
		this.addEventListener( ButtonEvent.CLICK ,DragOutInsize);
		
		this.addEventListener("rollOver",ShowTips);
		this.addEventListener("rollOut",RollOut);
		this.addEventListener( ButtonEvent.DRAG_OVER, DragOver);
		this.addEventListener( ButtonEvent.DRAG_OUT , DragOut );
		
		MenuId = 2;
		
		//disableFocus = true;

		//this.addEventListener( Event.ENTER_FRAME,UpdateFrame );
	}
	

	
	function DragOver()
	{
		
		//trace("DragOver");
	}
	
	function DClick()
	{
		//ExternalInterface.call("ASDoubleClickSlot",this );
	}

	function DragOut()
	{
		//trace("DragOut "+ bPressed + _MenuId);
		if( bPressed && _MenuId > 0 )
		{

			
			if(this["root"].MenuIcon != null && this["root"].MenuIcon != undefined )
			{
				//trace("goto"+_MenuId );
				//trace("goto"+ this["root"].MenuIcon.bNeedVisible );
				this["root"].MenuIcon.gotoAndStop( _MenuId+1 ) ;
				
				this["root"].MenuIcon.bNeedVisible = true;
			}
			//if( _global.gfxProcessSound )
			//{
			//	_global.gfxProcessSound(this, "default", "MoveItem" );		
			//}
			
			bDrag = true;
			//HideTips();
		}
	}
	
	function HideTips()
	{
		//trace(this["root"].tooltips_mc);
		if( this["root"].tooltips_mc != null  && this["root"].tooltips_mc != undefined )
		this["root"].tooltips_mc.visible =false;
		bOver = false;
	}
	
	function RollOut()
	{
		bOver = true;
		HideTips();
		//ExternalInterface.call("ASTrace", bPressed );

	}

	function ShowTips()
	{
		
		
		if( _MenuId >= 0 && SlotType == 1 )//
		{
			ExternalInterface.call("ShowTips",2, _MenuId ,this );
			this["root"].ChangeTips();	
		}
	}
	
	function DragIn()
	{
		//trace(DragIn);

		if( bDisableDrag )
		 return;
		
		bPressed = true;
		/*if(_ItemData.itemIndex >=0 && _ItemData.iconIndex != "")
		{
					
			HideTips();
		}*/
		HideTips();
		
	}
	
	function DragOutInsize()//
	{
		
		if(!bDrag)
		{
			ExternalInterface.call("ASClickMenu", this );
		}
		
		
		//DragRelease();
		
	}
	
	
	function DragRelease()
	{
		
		//trace( "DT: "+this.dropTarget );
		bPressed = false;
		
		if(!bDrag)
		{ return;}
		
		//旧方法不行了
		
		bDrag = false;
		return;
				
				
		var  dropMc:MovieClip = this["root"].MenuIcon.dropTarget as MovieClip;//_root.mouse_mc._droptarget;
		this["root"].MenuIcon.visible = false; //
		//trace(dropMc);
		
		if(dropMc == null)
		{
			ExternalInterface.call("ASThrowMenu", this );
			bDrag = false;
			return;
		}
		
		if( dropMc is MyMenuSlot && dropMc != this )
		{
			var dropMenu:MyMenuSlot = dropMc as MyMenuSlot;
			ExternalInterface.call("ASChangeMenu", this, dropMenu);
		}
	
/*				
		var  dropMenu:MyMenuSlot = MyMenuSlot( eval(dropDir));//
		if( dropMenu == null)
		{
			dropMenu = MyMenuSlot( eval(dropDir)._parent);
		}
		if( dropMenu == null)
		{
			dropMenu = MyMenuSlot( eval(dropDir)._parent._parent);
		}
		
		
		if( dropMenu == null || dropMenu.bDisableDrag  )
			return;
		
		if( dropMenu != this)
		ExternalInterface.call("ASChangeMenu", this, dropMenu);
		*/
		
	
	}
	


	
	function UpdateData()
	{
		//trace("menu "+MenuId);
		if( _MenuId >= 0)
		{
			icon.gotoAndStop( _MenuId+1 ) ;
		}

	}
}

}