var sourceFolder="file:///H|P4/08.Prog_CQ/Client/UE3/MMOGame/Flash/UI_MyComponent";
fl.trace(sourceFolder);
var fileMask="*.fla";
var list=FLfile.listFolder(sourceFolder+"/"+fileMask,"files");
for(var i=0;i<list.length;i++){
	var doc=fl.openDocument(sourceFolder+"/"+list[i]);
	doc.publish();
	doc.close();
}