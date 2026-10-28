function DefaultAdcolumnBarOnResize(Sender){
	// Receive notification after resize
	btnPageDown.top = Sender.height - 14;
	
	//btnPageUp.visible = true;
	//btnPageUp.caption = DefaultAdcolumnBar.ActiveWidgetItem.WidgetNameSpace;
	
	// DefaultAdcolumnBar.ActiveWidgetItem gets the current ad sidebar widget item
	// DefaultAdcolumnBar.ActiveWindows gets the currently displayed widget window
	
}


DefaultAdcolumnBar.onresize="DefaultAdcolumnBarOnResize(Self);"; 
