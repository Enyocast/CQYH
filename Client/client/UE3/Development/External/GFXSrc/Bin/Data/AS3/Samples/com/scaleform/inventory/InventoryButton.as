package com.scaleform.inventory {
	
	import scaleform.clik.controls.Button
	
	public class InventoryButton extends Button {
        /** Override for setActualSize that doesn't change the size. Allows for Button's to be tweened on the timeline. */
		override public function setActualSize(newWidth:Number, newHeight:Number):void { 
        	//
		}
	}
	
}