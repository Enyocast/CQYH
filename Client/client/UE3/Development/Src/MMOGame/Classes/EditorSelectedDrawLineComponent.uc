//
// For selected actor draw linked lines in editor  
//
class EditorSelectedDrawLineComponent extends PrimitiveComponent
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

	#if WITH_EDITOR
	virtual void CheckForErrors()
	{
	}
	#endif
};

defaultproperties
{
	HiddenGame=true
	AlwaysLoadOnClient=false
	AlwaysLoadOnServer=false
	bSelectable=false
	DepthPriorityGroup=SDPG_Foreground
}
