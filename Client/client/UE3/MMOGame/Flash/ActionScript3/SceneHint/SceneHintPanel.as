package ActionScript3.SceneHint {
	
	import flash.display.MovieClip;
	import ActionScript3.MyPanel;
	import flash.external.ExternalInterface;
	
	public class SceneHintPanel extends MyPanel {
		
		
		override protected  function configUI():void
		{
			super.configUI();
			//ExternalInterface.call( "RegisterSceneHint" , this );
		}
	}
	
}
