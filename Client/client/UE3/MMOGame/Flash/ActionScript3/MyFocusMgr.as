

//似乎不能这么搞
import gfx.managers.FocusHandler

class ActionScript.MyFocusMgr extends FocusHandler 
{
	private static var _instance:MyFocusMgr = instance;
	
	//单体类，用static取值函数获得，静态调用FocusHandler.instance。	
	public static function get instance():MyFocusMgr {
		if (_instance == null) { _instance = new MyFocusMgr(); }
		return _instance;
	}
	
	
	
	

}