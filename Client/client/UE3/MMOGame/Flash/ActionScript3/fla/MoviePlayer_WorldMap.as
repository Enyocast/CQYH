package ActionScript3.fla
{
	import scaleform.clik.core.UIComponent;
	import flash.external.ExternalInterface;

	import flash.display.MovieClip;
	import scaleform.clik.controls.Label;
	import flash.text.TextField;
	
	import ActionScript3.MyPanel;  
	import ActionScript3.MyTooltips;
	import UI_WorldMap.WorldMapAS3.WorldMapPanel;
	
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.ui.Mouse;
	import flash.display.DisplayObject;
	import flash.display.StageScaleMode;
	
	import ActionScript3.fla.MoviePlayerBase;
	
	public class MoviePlayer_WorldMap extends MoviePlayerBase
	{
		public var MapPanel_mc:WorldMapPanel;		
	}
}