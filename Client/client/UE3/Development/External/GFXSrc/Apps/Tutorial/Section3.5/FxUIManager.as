class FxUIManager
{
	private var bLoseFocus:Boolean;
	
	public function FxUIManager()
	{
		bLoseFocus = false;
		Mouse.addListener(this);
	}
	
	public function onMouseDown()
	{
		//trace("FxUIManager::onMouseDown");
		bLoseFocus = true;
	}
	
	public function onUIElementMouseDown()
	{
		//trace("FxUIManager::onUIElementMouseDown");
		bLoseFocus = false;
	}
	
	public function onMouseUp()
	{
		//trace("FxUIManager::onMouseUp");
		if (bLoseFocus == true)
		{
			//trace("Removing focus!");
			Selection.setFocus(null);
		}
	}
	
	public function onUIElementMouseUp()
	{
		//trace("FxUIManager::onUIElementMouseUp");
		// nothing
	}	
}