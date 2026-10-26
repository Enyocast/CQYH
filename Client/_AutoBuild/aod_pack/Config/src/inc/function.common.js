//包含了公共的函数


Function.prototype.getMultiLine = function() 
{
	var lines = new String(this); 
	lines = lines.substring( lines.indexOf("/*\r\n")+4 , lines.lastIndexOf("*/") );  
	return lines; 
};


var $ = function( str )
{
	return document.getElementById( str );
};


var getFilename = function( path )
{
	var pos = path.lastIndexOf( "\\" );
	if ( pos >= 0 )
	{
		return path.substring( pos+1 );
	}
	else
	{
		pos = path.lastIndexOf( "\/" );
	}
	return path.substring( pos+1 );
};



function getAbsolutePosition(obj) 
{ 
    position = new Object(); 
    position.x = 0; 
    position.y = 0; 
    var tempobj = obj; 
    while(tempobj!=null && tempobj!=document.body) 
    { 
		if(window.navigator.userAgent.indexOf("MSIE")!=-1) 
		{ 
			position.x += tempobj.offsetLeft; 
			position.y += tempobj.offsetTop; 
		} 
		else if(window.navigator.userAgent.indexOf("Firefox")!=-1) 
		{ 
			position.x += tempobj.offsetLeft; 
			position.y += tempobj.offsetTop; 
		} 
		tempobj = tempobj.offsetParent 
    } 
    return position; 
} 


