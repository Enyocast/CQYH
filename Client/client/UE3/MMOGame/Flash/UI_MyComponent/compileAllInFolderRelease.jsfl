var bSilent = confirm("使用静默模式发布所有swf？")//静默模式下不打开fla文件
var JSFL_PATH = fl.scriptURI.substr(0, fl.scriptURI.lastIndexOf("/") + 1);

fl.trace(bSilent + "|" + JSFL_PATH);

var fileMask="*.fla";
var list=FLfile.listFolder(JSFL_PATH + "/" + fileMask, "files");
var filePath;
for(var i=0;i<list.length;i++)
{
	filePath = JSFL_PATH + "/" + list[i];
	if(bSilent)
	{
		fl.publishDocument(filePath);
	}
	else
	{
		var doc = fl.openDocument(filePath);
		doc.publish();
		doc.close();
	}
}
