/**************************************************************************

Filename    :   IMEEventEx.as

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

package scaleform.gfx
{
	import flash.events.*;
    public final class IMEEventEx extends Event
    {
		public var message: String;
		public static const SET_CURRENT_INPUT_LANGUAGE:String 	= "SetCurrentInputLanguage"; 
		public static const SET_SUPPORTED_LANGUAGES:String 		= "SetSupportedLanguages";
		public static const SET_SUPPORTED_IMENAMES:String 		= "SetSupportedIMENames";
		public static const SET_IMENAME:String					= "SetIMEName";
		public static const SET_CURRENT_LANGUAGE:String 		= "SetCurrentLanguage"; 
		public static const REMOVE_STATUS_WINDOW:String			= "RemoveStatusWindow";
		public static const DISPLAY_STATUS_WINDOW:String 		= "DisplayStatusWindow";
		public static const SET_CONVERSION_STATUS:String		= "SetConversionStatus";
		
		public function IMEEventEx(type:String) { super(type); }
    }
}