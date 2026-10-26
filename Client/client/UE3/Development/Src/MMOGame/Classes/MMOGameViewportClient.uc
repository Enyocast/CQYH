class MMOGameViewportClient extends GameViewportClient;



event PostRender(Canvas Canvas)
{
	super.PostRender(Canvas);
}

DefaultProperties
{
	//UIControllerClass=class'UDKBase.UDKInteraction'
	bShowSystemMouseCursor=true
}
