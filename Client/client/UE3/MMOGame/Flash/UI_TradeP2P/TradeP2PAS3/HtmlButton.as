package UI_TradeP2P.TradeP2PAS3
{
	import scaleform.clik.controls.Button;

	public class HtmlButton extends Button
	{
		override protected function updateText():void {
			if (_label != null && textField != null) {
                textField.htmlText = _label;
            }
        }
	}
}