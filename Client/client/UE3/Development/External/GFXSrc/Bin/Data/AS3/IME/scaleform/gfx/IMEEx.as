/**************************************************************************

Filename    :   IMEEx.as

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

package scaleform.gfx
{
   import flash.events.*;
   import flash.display.Sprite;
	public final class IMEEx extends EventDispatcher 
   {
		static public function getIMECandidateListStyle():IMECandidateListStyle{return null;}
		static public function setIMECandidateListStyle(style:IMECandidateListStyle):void{}
		static public function SendLangBarMessage(mc:Sprite, command:String, message:String):void{}
		static public function GetOSVersion():String{return null;}
   }
}