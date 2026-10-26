/**************************************************************************

Filename    :   ListRow.as
Content     :   
Created     :   
Authors     :   Ankur 

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

package
{
import flash.display.*
import flash.geom.*;
import flash.events.MouseEvent
import flash.text.*

public class ListRow extends MovieClip
{
	public var bkGround_mc:MovieClip;
	//public var RowNumberBackground_mc:MovieClip;
	public var currentState:String = "UnSelected";
	public var Value:TextField;
	public var ID:TextField;
	public var controller:Object;
	
	function ListRow(_controller:Object)
	{
		// constructor
		controller = _controller;
		addEventListener(MouseEvent.MOUSE_DOWN, pressHandler);
		addEventListener(MouseEvent.MOUSE_UP, releaseHandler);
	}
	
	function pressHandler(event:MouseEvent)
	{
		MovieClip(parent).ClickedOnCandidateList = true;
		controller.SelectItem(this.name);
	}

	function releaseHandler(event:MouseEvent)
	{
	//	_root.characterList.SelectItem(this._parent._name);
	}


	// This class is a good place to keep these functions because they are loaded up when the listrow movie 
	// is instantiated during attachMovie and they are available for execution before the first advance on this movie
	// is called. If these functions are put on the first frame of the listrow movie, they will not be available
	// until the first advance.
	public function GotoOffState()
	{
		if(bkGround_mc != null)
		{
			controller.DisplayInfo(name);
			var myroot:MovieClip = MovieClip(parent.parent);
			var oldTextFormat:TextFormat = Value.getTextFormat();		
			oldTextFormat.color = 0xFFFFFF;		
			oldTextFormat.size 	= 16;
			oldTextFormat.font="Source Han Sans CN Medium";
/*			var bkC:uint = myroot.candidateList.BackgroundColor;
			bkGround_mc.transform.colorTransform = 
			new ColorTransform(0,0,0,1,(bkC&0xff0000)>>16,(bkC&0x00ff00)>>8, (bkC&0x0000ff), 0);
			var inC:uint = myroot.candidateList.IndexBackgroundColor;
			RowNumberBackground_mc.transform.colorTransform = 
			new ColorTransform(0,0,0,1,(inC&0xff0000)>>16,(inC&0x00ff00)>>8, (inC&0x0000ff), 0);*/
			Value.setTextFormat(oldTextFormat);
			ID.setTextFormat(oldTextFormat);
		}
		currentState = "UnSelected";  
		
	}
	
	public function GotoOnState()
	{
		if(bkGround_mc != null)
		{
			controller.DisplayInfo(name);
			var oldTextFormat:TextFormat = Value.getTextFormat();
			var myroot:MovieClip = MovieClip(parent.parent);
			oldTextFormat.color = 0x71dfff;		
			oldTextFormat.size 	= 16;
			oldTextFormat.font="Source Han Sans CN Medium";
			Value.setTextFormat(oldTextFormat);
			ID.setTextFormat(oldTextFormat);
		}
		currentState = "Selected"; 		
	}
 }
}