// JavaScript Document


var TestCase = {
	selectFile : function()
	{
		alert ( NSISBrowser.selectFile() );
	},
	selectFolder : function()
	{
		alert ( NSISBrowser.selectFolder() );
	},
	isFileExists : function()
	{
		var files = NSISBrowser.selectFile();
		if ( files.length == 0 )
		{
			alert ( "未选择文件" );
		}
		else
		{
			alert ( "文件："+files[0]+"\n是否存在："+NSISBrowser.isFileExists( files[0] ) );
		}
		
	},
	isDirExists : function()
	{
		var folder = NSISBrowser.selectFolder();
		if ( folder == "" )
		{
			alert ( "未选择文件夹" );
		}
		else
		{
			alert ( "文件夹："+folder+"\n是否存在："+NSISBrowser.isDirExists( folder ) );
		}
		
	},
	getFilelist : function()
	{
		/*
		var folder = NSIS.selectFolder();
		if ( folder == "" )
		{
			alert ( "未选择文件夹" );
		}
		else
		{
			var arrFilelist = NSIS.getFilelist(folder);
			alert ( "文件夹："+folder+"是否存在：" );
		}
		*/
		var arrFilelist = NSISBrowser.getFilelist("c:\\test1\\");
		var i,arrItem,strRet="";
		for ( i=0;i<arrFilelist.length;i++)
		{
			arrItem = arrFilelist[i].parseJSON();
			if ( arrItem[1] == 0 )
			{
				strRet += ("文件夹："+arrItem[0]+"\n");
			}
			else
			{
				strRet += ("文件："+arrItem[0]+"\n");
			}
		}
		alert (strRet);
	},
	//读取文件
	readfile : function()
	{
		var files = NSISBrowser.selectFile();
		if ( files.length > 0 )
		{
			alert ( NSISBrowser.readFile(files[0]) );
		}
	},
	//写文件
	writefile : function()
	{
		var files = NSISBrowser.selectFile();
		if ( files.length > 0 )
		{
			var path = "f:\\热血传奇.txt";
			var content = NSISBrowser.readFile(files[0]);
			NSISBrowser.writeFile(path,content);
			//NSIS.writeFile(path,'123');
		}
		
	},
	other : function()
	{
		//window.external.about(  );
		NSISBrowser.writeFile("test.txt","\'\"");
	},
	fillblank : function( form )
	{
		form.nameCn.value = "热血传奇";
		form.nameEn.value = "mir2";
		form.gameId.value = "1";
		form.productMP.value = "1";
		form.programName.value = "mir2.exe";
			
			
		form.programGameName.value = "mir2.exe";
		form.version.value = "1.0.0.1";
		form.versionEx.value = "1.0.0.2";
		form.website.value = "http://mir2.sdo.com";
		
		$("license").value = NSISLicenseTemplate.getLicense(form.nameCn.value,form.nameEn.value,form.website.value);

/*	
		form.isPopularize.value = "false";
		form.compressType.value = "zlib";
		form.isSplitCompress.value = "false";
		form.splitCompressPassword.value = "";
		*/
	},
	copyfile : function()
	{
		var files = NSISBrowser.selectFile();
		
		if ( files.length > 0 )
		{
			var folder = NSISBrowser.selectFolder();
			
			if ( folder != "" )
			{
				var i;
				var from,to;
				for ( i=0;i<files.length;i++ )
				{
					from = files[i];
					to = folder + "\\" + getFilename(files[i]);
					alert ( "copy file:\nfrom:"+from+"\nto:"+to );
					NSISBrowser.copyFile( from , to );
				}
				
			}
		}
	},
	runJS : function()
	{

	},
	viewSkin : function()
	{
		var str = "";
		str = str + $("skinHeaderPath").value + "\n";
		str = str + $("skinLeftPath").value + "\n";
		str = str + $("skinPTPath").value + "\n";
		str = str + $("skinBottomPath").value + "\n";
		str = str + $("skinSplashPath").value + "\n";
		str = str + $("skinSetupPath").value + "\n";
		str = str + $("skinUninstallPath").value + "\n";
		alert (str);
	},
	CurrInfo : function()
	{
		var str = "";
		str = str + "currentdir:" + NSISBrowser.getPath() + "\n";
		str = str + "currentprocess:" + NSISBrowser.getProcessId() + "\n";
		alert (str);
	},
	UICtrl : function()
	{
		//alert ("SetWindowSize:800*600");
		//NSISBrowser.setWindowSize(800,600);
		//alert ("moveWindow:-5,-5\n");
		NSISBrowser.moveWindow(-5,5);
		//alert ("Hide Border");
		NSISBrowser.showBorder(false);

		//alert ("Enable Drag");
		NSISBrowser.dragEnable(true);
	},
	showBorder : function()
	{
		NSISBrowser.showBorder(true);
	},
	setWebSize : function()
	{
		NSISBrowser.setWebSize( 200 , 100 );
	},
	makeNSIS : function()
	{
		NSISBrowser.makeNSIS();
	},
	getLicense : function()
	{
		NSISLicenseTemplate.getTemplate("热血传奇","mir2","http://mir2.sdo.com");
	},
	exit : function()
	{
		NSISBrowser.exit();
	}
};
