//
// MMOCrowdDebugComponent
//
class MMOCrowdDebugComponent extends PrimitiveComponent
	native
	hidecategories(Object)
	editinlinenew;

cpptext
{
	/**
	 * Creates a new scene proxy for the path rendering component.
	 * @return	Pointer to the ServerTriggerSceneProxy
	 */
	virtual FPrimitiveSceneProxy* CreateSceneProxy();

	virtual void UpdateBounds();
};

defaultproperties
{
	//HiddenGame=true
	//AlwaysLoadOnClient=false
	//AlwaysLoadOnServer=false
	//bSelectable=false
}
