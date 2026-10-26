

var C_NSISViewer = function(){
	var objConfig = null;
	
	var _divStatus;
	var _hTimerHideStatus = null;		//隐藏状态条的定时器
	
	var _pathMakeNSIS = "D:\\Project\\NSIS\\NSIS\\NSIS\\makensisw.exe";
	
	this.stepControl = {
		step : ["tab1","tab2","tab3","tab4","tab5" ],	//一步的div的id
		menu : ["menu1" , "menu2" , "menu3" , "menu4" , "menu5" ],
		currentStep : 0,	//当前所在的div的id

		gotoNext : function(){
			if ( this.currentStep < this.step.length-1 )
			{
				this.currentStep++;
				this.show();
			}
			else
			{
				//提交了
				NSISViewer.submit();
			}
		},
		gotoPrevious : function(){
			if ( this.currentStep >0 )
			{
				this.currentStep--;
				this.show();
			}
		},
		goto : function( pos ){
			if ( pos >= 0 && pos < this.step.length )
			{
				this.currentStep = pos;
				this.show();
			}
		},
		show : function(){
			//隐藏所有tab
			var divOther;
			var i=0;
			for ( i=0 ; i<this.step.length;i++){
				divOther = document.getElementById(this.step[i]);
				if ( divOther )
				{
					divOther.style.display = "none";
				}
			}
			//显示自己
			var div = document.getElementById(this.step[this.currentStep]);
			if ( div ){
				div.style.display = "";
			}
			
			//控制按钮
			var btnPrevious = document.getElementById("btnPrevious");
			if ( btnPrevious )
			{
				if ( this.currentStep == 0 )
				{
					btnPrevious.style.display = "none";
				}
				else
				{
					btnPrevious.style.display = "";
				}
			}
			var btnNext = document.getElementById("btnNext");
			var btnFinish = document.getElementById("btnFinish");
			if ( btnNext )
			{
				if ( this.currentStep >= this.step.length-1 )
				{
					btnNext.style.display = "none";
					btnFinish.style.display = "";
				}
				else
				{
					btnNext.style.display = "";
					btnFinish.style.display = "none";
				}
			}
			
			//设置菜单
			for ( i=0 ; i<this.menu.length;i++){
				divOther = document.getElementById(this.menu[i]);
				if ( divOther )
				{
					divOther.style.color = "#FFFFFF";
					divOther.style.backgroundImage = "";
				}
			}
			div = document.getElementById(this.menu[this.currentStep]);
			if ( div ){
				div.style.color = "#FFFF00";
				div.style.backgroundImage = "url(images/menu_bg.jpg)";
			}
		},
		init : function(){
			this.show();
		}
	};
	
	
	this.init = function()
	{
		//屏蔽F5刷新
		document.onkeydown=function()
		{
			//屏蔽F5
			with(window.event)
			{
				if(keyCode == 116)
				{
					keyCode         =   0;
					cancelBubble    =   true;
					return              false;
				}
			};
		};
		
		$("gameId").onkeydown = function()
		{
			with(window.event)
			{
				if ( keyCode >= 48 && keyCode <= 57 || keyCode == 8 || keyCode == 9 || keyCode == 16 || keyCode == 17 || keyCode >= 96 && keyCode <= 105)
				{
					
				}
				else
				{
					keyCode         =   0;
					cancelBubble    =   true;
					return              false;
				}
			};
		};
		if ( NSISBrowser.getVersion() == '' )
		{
			//调用没成功
			$("cover").style.display = "block";
			return;
		}

		
		
		//初始化数据
		_init();

		var filepath;
		var content;
		filepath =  NSISBrowser.getPath()+"Config\\save.conf";
		if ( NSISBrowser.isFileExists( filepath ) )
		{
			content = NSISBrowser.readFile(filepath);
			var objConf = content.parseJSON();
			this.loadConfigObject( objConf );
		}


		//设置皮肤
		var img;
		filepath =  NSISBrowser.getPath()+"Resources\\header.bmp";

		img = $("skinHeader");
		if ( NSISBrowser.isFileExists( filepath ) )
		{
			NSISViewer.selectSkin( 'header' , img , filepath );
		}
		else
		{
			img.src = "images/noskin/header.jpg";
		}


		filepath =  NSISBrowser.getPath()+"Resources\\left.bmp";
		img = $("skinLeft");
		if ( NSISBrowser.isFileExists( filepath ) )
		{
			NSISViewer.selectSkin( 'left' , img , filepath );
		}
		else
		{
			img.src = "images/noskin/left.jpg";
		}


		filepath =  NSISBrowser.getPath()+"Resources\\pt.bmp";
		img = $("skinPT");
		if ( NSISBrowser.isFileExists( filepath ) )
		{
			NSISViewer.selectSkin( 'pt' , img , filepath );
		}
		else
		{
			img.src = "images/noskin/pt.jpg";
		}



		filepath =  NSISBrowser.getPath()+"Resources\\bottom.bmp";
		img = $("skinBottom");
		if ( NSISBrowser.isFileExists( filepath ) )
		{
			NSISViewer.selectSkin( 'bottom' , img , filepath );
		}
		else
		{
			img.src = "images/noskin/bottom.jpg";
		}



		filepath =  NSISBrowser.getPath()+"Resources\\splash.bmp";
		img = $("skinSplash");
		if ( NSISBrowser.isFileExists( filepath ) )
		{
			NSISViewer.selectSkin( 'splash' , img , filepath );
		}
		else
		{
			img.src = "images/noskin/splash.jpg";
		}


		//初始化页面控制
		this.stepControl.init();
		this.refreshLicense();
		$("isSplitCompressFalse").onclick = function(){	//不开启分卷压缩
			$("sub_isSplitCompress").style.display = "none";	//文件压缩方式显示
			$("compressFileTab").style.display = "none";	//压缩文件名显示
			/* update
			$("compressFileZip").setAttribute("checked" , "checked");
			$("compressFile7z").setAttribute("checked" , "");
			*/
		};
		$("isSplitCompressDefault").onclick = function(){	//开启默认自动分卷压缩
			$("sub_isSplitCompress").style.display = "none";	//文件压缩方式显示
			$("compressFileTab").style.display = "none";	//压缩文件名显示
			/* update
			$("compressFileZip").setAttribute("checked" , "checked");
			$("compressFile7z").setAttribute("checked" , "");
			*/
		};
		$("isSplitCompressCustom").onclick = function(){	//开启自定义分卷压缩
			$("sub_isSplitCompress").style.display = "";	//文件压缩方式显示
			$("compressFileTab").style.display = "";	//压缩文件名显示
			/* update
			$("compressFileZip").setAttribute("checked" , "checked");
			$("compressFile7z").setAttribute("checked" , "");
			*/
		};
		


		//读取版权信息
		filepath =  NSISBrowser.getPath()+"Resources\\license.txt";
		if ( NSISBrowser.isFileExists( filepath ) )
		{
			content = NSISBrowser.readFile(filepath);
			$("license").value = content;
		}
	};
	
	this.writeNode = function (xmlfile, nodeTage, nodeText)
	{
		schar = '\r'; 
		xmlfile.WriteLine('<'+nodeTage+'>'+nodeText+'</'+nodeTage+'>'+schar);
		
	};
	this.getCurPat = function()
	{
		var str = location.href;

		var arr = str.split("/");

		delete arr[arr.length-1];

		var dir = arr.join("/");

		alert(dir);
	};
	
	
	this.showError = function ( msg )
	{
		_divStatus = $('status');
		_divStatus.style.backgroundColor = 'red';
		_divStatus.style.color = 'yellow';
		_showStatus( msg );
	};
	
	
	this.showMessage = function ( msg )
	{
		_divStatus = $('status');
		_divStatus.style.backgroundColor = '#FFFF00';
		_divStatus.style.color = '#FF0000';

		_showStatus( msg );
	};

	
	this.loadConfigObject = function( objConf )
	{
		//填充表单
		form = $("nsisform");
		
		form.nameCn.value = objConf.nameCn;
		form.nameEn.value = objConf.nameEn;
		form.nameEnglish.value = objConf.nameEnglish;
		form.AppChanel.value = objConf.AppChanel;
		form.gameId.value = objConf.gameId;
		form.productMP.value = objConf.productMP;
		form.programName.value = objConf.programName;
			
			
		form.programGameName.value = objConf.programGameName;
		form.version.value = objConf.version;
		form.versionEx.value = objConf.versionEx;
		form.website.value = objConf.website;
		form.developer.value = objConf.developer;

		//form.textColor.value = objConf.textColor;
		
		//alert ( objConf.isPopularize );
		//if ( objConf.isPopularize == "true" )
		//{
		//	$("isPopularizeFalse").setAttribute("checked" , "");
		//	$("isPopularizeTrue").setAttribute("checked" , "checked");
		//}
		//else
		//{
		//	$("isPopularizeFalse").setAttribute("checked" , "checked");
		//	$("isPopularizeTrue").setAttribute("checked" , "");
		//}
		
		
		if ( objConf.compressType == "lzma" )
		{
			$("compressTypeLzma").setAttribute("checked" , "checked");
		}
		else if ( objConf.compressType == "bzip2" )
		{
			$("compressTypeBZip2").setAttribute("checked" , "checked");
		}
		else if ( objConf.compressType == "zlib" )
		{
			$("compressTypeZLib").setAttribute("checked" , "checked");
		}
		else
		{
			//$("compressTypeKZ").setAttribute("checked" , "checked");
		}

		if ( objConf.isSplitCompress == "customSplit" )
		{
			//开启自定义压缩
			$("sub_isSplitCompress").style.display = "";
			$("compressFileTab").style.display = "";
			$("isSplitCompressCustom").setAttribute("checked" , "checked");
			$("isSplitCompressDefault").setAttribute("checked" , "");
			$("isSplitCompressFalse").setAttribute("checked" , "");
			//alert(objConf.compressFileType);
			if ( objConf.compressFileType == "Extract7zMutiArchivesA" )
			{
				$("compressFile7z").setAttribute("checked" , "checked");
				$("compressFileZip").setAttribute("checked" , "");
//				objConfig.sizeFunction = "Get7zDataSize";
			}
			else
			{
				$("compressFileZip").setAttribute("checked" , "checked");
				$("compressFile7z").setAttribute("checked" , "");
				if( objConf.compressFileType == '' ){
					objConf.compressFileType = "ExtractZipMutiArchivesA";
				}
//				objConfig.sizeFunction = "GetZipDataSize";
			}

		}
		else if( objConf.isSplitCompress == "defaultSplit" )
		{
		//默认分卷压缩
			$("isSplitCompressDefault").setAttribute("checked" , "checked");
			$("isSplitCompressCustom").setAttribute("checked" , "");
			$("isSplitCompressFalse").setAttribute("checked" , "");
			$("compressFileZip").setAttribute("checked" , "");
			$("compressFile7z").setAttribute("checked" , "checked");
			objConf.compressFileType = "Extract7zMutiArchivesA";
//			objConfig.sizeFunction = "GetZipDataSize";
		}
		else if( objConf.isSplitCompress == "noSplit" )
		{
			//不开启分卷
			$("isSplitCompressFalse").setAttribute("checked" , "checked");
			$("isSplitCompressDefault").setAttribute("checked" , "");
			$("isSplitCompressCustom").setAttribute("checked" , "");
			$("compressFileZip").setAttribute("checked" , "");
			$("compressFile7z").setAttribute("checked" , "checked");
			objConf.compressFileType = "Extract7zMutiArchivesA";
		}


		form.splitCompressPassword.value = objConf.splitCompressPassword;
		form.compressFileName.value = objConf.compressFileName;
		form.zipFileSize.value = objConf.zipFileSize;	

		if ( objConf.isSetupDotnet )
		{
			form.isSetupDotnet.checked = true;
		}
		else
		{
			form.isSetupDotnet.checked = false;
		}
		if ( objConf.isSetupVcredist )
		{
			form.isSetupVcredist.checked = true;
		}
		else
		{
			form.isSetupVcredist.checked = false;
		}
		
		if ( objConf.isSetupVcredist2008 )
		{
			form.isSetupVcredist2008.checked = true;
		}
		else
		{
			form.isSetupVcredist2008.checked = false;
		}
		
		if ( objConf.isSetupDX )
		{
			form.isSetupDX.checked = true;
		}
		else
		{
			form.isSetupDX.checked = false;
		}
		form.versionDX.value = objConf.versionDX;
		
	};

	this.copySkin = function(){
		//设置皮肤
			var from = "";
			var to = "";
			if ( $("skinHeaderPath").value && $("skinHeaderPath").value != "" )
			{
				from = $("skinHeaderPath").value;
				to = NSISBrowser.getPath()+"Resources\\header.bmp";
				try
				{
					NSISBrowser.copyFile( from , to );
				}
				catch ( e )
				{
					
				}
			}
			if ( $("skinLeftPath").value && $("skinLeftPath").value != "" )
			{
				from = $("skinLeftPath").value;
				to = NSISBrowser.getPath()+"Resources\\left.bmp";
				try
				{
					
					NSISBrowser.copyFile( from , to );
				}
				catch ( e )
				{
					
				}
			}		
			if ( $("skinPTPath").value && $("skinPTPath").value != "" )
			{
				from = $("skinPTPath").value;
				to = NSISBrowser.getPath()+"Resources\\pt.bmp";
				try
				{
					
					NSISBrowser.copyFile( from , to );
				}
				catch ( e )
				{
					
				}
			}		
			if ( $("skinBottomPath").value && $("skinBottomPath").value != "" )
			{
				from = $("skinBottomPath").value;
				to = NSISBrowser.getPath()+"Resources\\bottom.bmp";
				try
				{
					
					NSISBrowser.copyFile( from , to );
				}
				catch ( e )
				{
					
				}
			}		
			if ( $("skinSplashPath").value && $("skinSplashPath").value != "" )
			{
				from = $("skinSplashPath").value;
				to = NSISBrowser.getPath()+"Resources\\splash.bmp";
				try
				{
					
					NSISBrowser.copyFile( from , to );
				}
				catch ( e )
				{
					
				}
			}		
			if ( $("skinSetupPath").value && $("skinSetupPath").value != "" )
			{
				from = $("skinSetupPath").value;
				to = NSISBrowser.getPath()+"Resources\\setup.ico";
				try
				{
					
					NSISBrowser.copyFile( from , to );
				}
				catch ( e )
				{
					
				}
			}
			if ( $("skinUninstallPath").value && $("skinUninstallPath").value != "" )
			{
				from = $("skinUninstallPath").value;
				
				to = NSISBrowser.getPath()+"Resources\\uninstall.ico";
				try
				{
					
					NSISBrowser.copyFile( from , to );
				}
				catch ( e )
				{
					
				}
			}
			
			if ( NSISBrowser.isDirExists( NSISBrowser.getPath()+"\\Resources" ) == false )
			{
				alert ('皮肤包不存在，请选择皮肤包');
				return;
			}
			var filelist = NSISBrowser.getFilelist( NSISBrowser.getPath()+"Resources" );
		
			if ( this._checkSkinPackage( filelist ) == false )
			{
				alert ('所选的皮肤包不完整，请确保文件夹中包含以下文件：\nheader.bmp\nleft.bmp\npt.bmp\nbottom.bmp\nsplash.bmp\nsetup.ico\nuninstall.ico');
				return;
			}
	};
/*	this.writerIni = function ( form )
	{
		fso = new ActiveXObject("Scripting.FileSystemObject");
		tf = fso.CreateTextFile("E:\\test.ini", true);  
		tf.WriteLine("要写入的内容");
		tf.Close();
	}
*/	
	this.WriteIniFile = function(form,filepath)
	{
		var content = "[Info]";; 
		try
			{
				if( !form.isSplitCompress.value )
				{
					//如果没有得到值，则用户用的可能是radiobox
					if ( $("isSplitCompressCustom").checked )
					{
					//自定义压缩
						if(!form.compressFileType.value)
						{
							if ( $("compressFileZip").checked )
							{
								content += "\r\nvolumeType=zip";
								//NSISViewer.writeNode(xmlfile,'volumeType','zip');
							}
							else if($("compressFile7z").checked)
							{
								content += "\r\nvolumeType=7z";
								//NSISViewer.writeNode(xmlfile,'volumeType','7z');
							}
							content += "\r\nvolumeName=";
							content += form.compressFileName.value;
							content += "\r\nsplitSize=";
							content += form.zipFileSize.value;
							content += "\r\npassword=";
							content += form.splitCompressPassword.value;
							NSISBrowser.writeFile( filepath , content );
						}				
					}
					else if ($("isSplitCompressDefault").checked)	
					{
						//默认压缩
						content += "\r\nvolumeType=7z";
						content += "\r\nvolumeName=";
						content += form.nameEnglish.value.toLowerCase();
						content += form.versionEx.value.toLowerCase();
						content += ".7z.001";
						content += "\r\nsplitSize=";
						content += "1.8g";
						content += "\r\npassword=";
						content += "";
						NSISBrowser.writeFile( filepath , content );
											
					}
				}
			}
		catch(err)
			{
			/*	alert("您选择了不保存自动打包配置文件或无写入文件权限，将导致无法使用自动打包模式，即将退出生成器，若需要自动打包模式，重新启动选择[是]即可！\n\n");
				NSISBrowser.exit();
			*/	
			txt="此页面存在一个错误。\n\n"
			txt+="错误描述: " + err.description + "\n\n"
			txt+="点击OK继续。\n\n"
			alert(txt)
			}
		
	};
	this.writeXml = function ( form )
	{
		var fso, tempfolder, xmlfile, schar; 
		try
			{
				fso = new ActiveXObject("Scripting.FileSystemObject"); 
				tempfolder = fso.GetSpecialFolder(0); 
				xmlfile = fso.CreateTextFile("splitVolumeDetails.xml",true,true); 
				schar = '\r'; 
				xmlfile.WriteLine('<?xml version="1.0" encoding="utf-16"?>'); 
				xmlfile.WriteLine('<splitDetails>'); 
				if( !form.isSplitCompress.value )
				{
					//如果没有得到值，则用户用的可能是radiobox
					if ( $("isSplitCompressCustom").checked )
					{
						if(!form.compressFileType.value)
						{
							if ( $("compressFileZip").checked )
							{
								NSISViewer.writeNode(xmlfile,'volumeType','zip');
							}
							else if($("compressFile7z").checked)
							{
								NSISViewer.writeNode(xmlfile,'volumeType','7z');
							}
							NSISViewer.writeNode(xmlfile,'volumeName',form.compressFileName.value);
							NSISViewer.writeNode(xmlfile,'password',form.splitCompressPassword.value);
							NSISViewer.writeNode(xmlfile,'splitSize',form.zipFileSize.value);
							
						}				
					}	
				}
				xmlfile.WriteLine('</splitDetails>'); 
				xmlfile.Close(); 
			}
		catch(err)
			{
				alert("您选择了不保存自动打包配置文件或无写入文件权限，将导致无法使用自动打包模式，即将退出生成器，若需要自动打包模式，重新启动选择[是]即可！\n\n");
				NSISBrowser.exit();
				
		/*	txt="此页面存在一个错误。\n\n"
			txt+="错误描述: " + err.description + "\n\n"
			txt+="点击OK继续。\n\n"
			alert(txt)*/
			}
		
	};
	this.submit = function( form ){
		
		if ( !form )
		{
			form = $('nsisform');
		}

		objConfig = new C_NSISConfigObject();
		objConfig.nameCn = form.nameCn.value;
		objConfig.nameEn = form.nameEn.value;//注册表项名
		objConfig.AppChanel = form.AppChanel.value;
		objConfig.nameEnglish = form.nameEnglish.value;
		objConfig.gameId = form.gameId.value;
		objConfig.productMP = form.productMP.value;
		objConfig.programName = form.programName.value;
		objConfig.outExeName = form.nameEnglish.value + "_setup_" + form.version.value + ".exe";
		objConfig.outExeTitle = "《" + form.nameCn.value + "》 " + form.versionEx.value + "版";
		
		
		objConfig.programGameName = form.programGameName.value;
		objConfig.version = form.version.value;
		objConfig.versionEx = form.versionEx.value;
		objConfig.website = form.website.value;
		objConfig.developer = form.developer.value;
		//objConfig.textColor = form.textColor.value;

		
		//objConfig.isPopularize = form.isPopularize.value;
		//if ( !objConfig.isPopularize )
		//{
			//如果没有得到值，则用户用的可能是radiobox
			//if ( $("isPopularizeTrue").checked )
			//{
				//objConfig.isPopularize = "true";
			//}
			//else
			//{
				//objConfig.isPopularize = "false";
			//}
		//}
		
		objConfig.compressType = form.compressType.value;
		if ( !objConfig.compressType )
		{
			//如果没有得到值，则用户用的可能是radiobox
			if ( $("compressTypeZLib").checked )
			{
				objConfig.compressType = "zlib";
			}
			else if ( $("compressTypeBZip2").checked )
			{
				objConfig.compressType = "bzip2";
			}
			else if ( $("compressTypeLzma").checked )
			{
				objConfig.compressType = "lzma";
			}
			else
			{
				objConfig.compressType = "";
			}
		}

		objConfig.isSplitCompress = form.isSplitCompress.value;
		if ( !objConfig.isSplitCompress )
		{
			//如果没有得到值，则用户用的可能是radiobox
			if ( $("isSplitCompressCustom").checked )
			{
				objConfig.isSplitCompress = "customSplit";
			}
			else if( $("isSplitCompressDefault").checked )
			{
				objConfig.isSplitCompress = "defaultSplit";
			}
			else if( $("isSplitCompressFalse").checked )
			{
				objConfig.isSplitCompress = "noSplit";
			}
		}
		if ( objConfig.isSplitCompress == "customSplit" )
		{
			objConfig.splitCompressPassword = form.splitCompressPassword.value;
			objConfig.compressFileName = form.compressFileName.value;
			objConfig.zipFileSize = form.zipFileSize.value;
			if (  !objConfig.compressFileType )
			{
				//如果没有得到值，则用户用的可能是radiobox
				if ( $("compressFileZip").checked )
				{
					objConfig.compressFileType= "ExtractZipMutiArchivesA";
					objConfig.sizeFunction = "GetZipArchiveSizeA";
				}
				else if ( $("compressFile7z").checked )
				{
					objConfig.compressFileType = "Extract7zMutiArchivesA";
					objConfig.sizeFunction = "Get7zArchiveSizeA";
				}
				else
				{
					objConfig.compressFileType = "ExtractZipMutiArchivesA";
					objConfig.sizeFunction = "GetZipArchiveSizeA";
				}
			}
		}
		else if( objConfig.isSplitCompress == "defaultSplit"  )
		{
			objConfig.splitCompressPassword = "";
			objConfig.compressFileName = form.nameEnglish.value + form.versionEx.value + ".7z.001";
			objConfig.zipFileSize = "1.8g";
			objConfig.compressFileType = "Extract7zMutiArchivesA";
			objConfig.sizeFunction = "Get7zArchiveSizeA";
		}

		objConfig.isSetupDotnet = form.isSetupDotnet.checked;
		objConfig.isSetupVcredist = form.isSetupVcredist.checked;
		objConfig.isSetupVcredist2008 = form.isSetupVcredist2008.checked;
		objConfig.isSetupDX = form.isSetupDX.checked;
//		objConfig.isSetupDX10 = form.isSetupDX10.checked;
//		if ( objConfig.isSetupDX == true )
//		{
//			objConfig.isSetupDX = false;
//			this.showError( "暂时不支持DirectX的安装" );
//		}
		objConfig.versionDX = form.versionDX.value;
		objConfig.versionDX = "4.9.0.904";
//		objConfig.versionDX10 = form.versionDX10.value;
//		objConfig.versionDX10 = "test";
		if ( !objConfig.versionDX || objConfig.versionDX == "" )
		{
			objConfig.versionDX = "";
		}

		var err = objConfig.isLegal();


		if ( err == "" )
		{

			//设置license
			var content;
			content = $("license").value;
			if( !content || content == '' )
			{
				this.showError( "没有填写版权信息" );
				return;
			}
			var filepath;
			filepath =  NSISBrowser.getPath()+"Resources\\license.txt";
			NSISBrowser.writeFile( filepath , content );
			this.copySkin();
			
			//生成成功，保存当前配置
			NSISViewer.save();
//			if ( !confirm("是否立即生成模板文件？") )
//			{
//				return;
//			}
			//生成模板
			content = objConfig.getContent();
			filepath = NSISBrowser.getPath()+objConfig.nameEn+'_Setup('+objConfig.versionEx+').nsi';
			NSISBrowser.writeFile( filepath , content );
			//alert(objConfig.compressFileType);

			this.showMessage("脚本生成成功!");
			alert ("脚本生成成功，并以NSI文件的形式保存在程序根目录:\n"+filepath);
			
			
//			NSISViewer.writeXml(form);
//			NSISViewer.writeIni(form);
//			var Ini = new IniCtrl();
//			Ini.Create("D:\\workspace\\test\\autoPatch\\autoPatchModule\\autoPatchModule0208\\autoPatchModule0208\\setting0331.ini");
//			Ini.Open("D:\\workspace\\test\\autoPatch\\autoPatchModule\\autoPatchModule0208\\autoPatchModule0208\\setting0331.ini");
			InifilePath = NSISBrowser.getPath() + "SD_NSIS\\settings.ini";
			//var contentIni = "[Test]\nuser=aaaa\ntestPass=234234"
			NSISViewer.WriteIniFile(form,InifilePath);
//			NSISBrowser.writeFile( form , InifilePath );
/*			Ini.AddSetting("Admin");

			//配置增加属性
			Ini.select("Admin");
			Ini.setAttributeCtrl("user","aaaaaa");
			Ini.setAttributeCtrl("pass","123123");

			//保存配置
			Ini.save();
			Ini.Close();
*/
//			content = objConfig.toJSONString();

//			filepath = NSISBrowser.getPath()+"Config\\"+'save.conf';
//			NSISBrowser.writeFile( filepath , content );



//			//生成成功
//			if ( confirm("是否立即编译") )
//			{
//				//要编译
//				try
//				{
//					ret = window.external.RunExec(_pathMakeNSIS,filepath,false);
//				}
//				catch ( e )
//				{
//					this._errHandler(e);
//				}
//			}

		}
		else
		{
			this.showError( err );
		}
	};
	
	
	
	this.selectSkin = function( skinName , img , path )
	{
		var filter;
		var inputHidden = null;

		switch ( skinName )
		{
			case 'setup':
				filter = '图标文件(*.ico)|*.ico';
				inputHidden = $("skinSetupPath");
				break;
			case 'uninstall':
				filter = '图标文件(*.ico)|*.ico';
				inputHidden = $("skinUninstallPath");
				break;
			case 'header':
				filter = '位图文件(*.bmp)|*.bmp';
				inputHidden = $("skinHeaderPath");
				break;
			case 'left':
				filter = '位图文件(*.bmp)|*.bmp';
				inputHidden = $("skinLeftPath");
				break;
			case 'pt':
				filter = '位图文件(*.bmp)|*.bmp';
				inputHidden = $("skinPTPath");
				break;
			case 'bottom':
				filter = '位图文件(*.bmp)|*.bmp';
				inputHidden = $("skinBottomPath");
				break;
			case 'splash':
				filter = '位图文件(*.bmp)|*.bmp';
				inputHidden = $("skinSplashPath");
				break;
			default:
				
		}
		
		if ( path == null )
		{
			path = NSISBrowser.selectFile( filter );
		}
		
		if ( path != "" )
		{
			//获得图片路径
			if ( img )
			{
				img.src = path;
			}
			if ( inputHidden )
			{
				inputHidden.value = path;
			}
		}
	};
	
	
	this.selectSkinPackage = function()
	{
		var path = NSISBrowser.selectFolder();
		if ( path == "" )
			return;
			
		var filelist = NSISBrowser.getFilelist( path );
	
		if ( this._checkSkinPackage( filelist ) == false )
		{
			alert ('选择的不是有效的皮肤包，请确保文件夹中包含以下文件：\nheader.bmp\nleft.bmp\npt.bmp\nbottom.bmp\nsplash.bmp\nsetup.ico\nuninstall.ico');
			return;
		}

		//完整性检查通过
		$("skinHeader").src = path + "\\header.bmp";
		$("skinHeaderPath").value = path + "\\header.bmp";
		$("skinLeft").src = path + "\\left.bmp";
		$("skinLeftPath").value = path + "\\left.bmp";
		$("skinPT").src = path + "\\pt.bmp";
		$("skinPTPath").value = path + "\\pt.bmp";
		$("skinBottom").src = path + "\\bottom.bmp";
		$("skinBottomPath").value = path + "\\bottom.bmp";
		$("skinSplash").src = path + "\\splash.bmp";
		$("skinSplashPath").value = path + "\\splash.bmp";
		
		$("skinSetupPath").value = path + "\\setup.ico";
		$("skinUninstallPath").value = path + "\\uninstall.ico";
		
		$("skinPath").value = path;
	};
	
	
	this.refreshLicense = function(){
		//var form = $('nsisform');
		//$("license").value = NSISLicenseTemplate.getLicense(form.nameCn.value,form.nameEnglish.value,form.website.value,form.developer.value);
	};
	
	this.showBorder = function( img )
	{
		if ( img )
		{
			//alert (img.width+","+img.height+","+img.offsetTop+","+img.offsetLeft);
			$("skinImgBorder").style.width = (img.offsetWidth-2)+"px";
			$("skinImgBorder").style.height = (img.offsetHeight-2)+"px";
			$("skinImgBorder").style.top = getAbsolutePosition(img).y;
			$("skinImgBorder").style.left = getAbsolutePosition(img).x;
			//$("skinImgBorder").style.top = img.style.top;
			//$("skinImgBorder").style.left = img.style.left;
			$("skinImgBorder").style.border='2px yellow solid';
			$("skinImgBorder").style.display='';
		}
	};

	
	this.hideBorder = function( img )
	{
		if ( img )
		{
			$("skinImgBorder").style.display='none';
		}
	};
	
	
	this.exit = function(){
		if ( confirm('您是否要退出系统？') )
		{
			NSISBrowser.exit();
		}
	};

	this.refreshTextColor = function(){
		try
		{
			$("mycolor").style.backgroundColor = $("textColor").value;
		}
		catch( e )
		{
			
		}
	
	};
	
	
	this.save = function(){
		//保存当前设置
		form = $('nsisform');

		objConfig = new C_NSISConfigObject();
		objConfig.nameCn = form.nameCn.value;
		objConfig.nameEn = form.nameEn.value;
		objConfig.nameEnglish = form.nameEnglish.value;
		objConfig.AppChanel = form.AppChanel.value;
		objConfig.gameId = form.gameId.value;
		objConfig.productMP = form.productMP.value;
		objConfig.programName = form.programName.value;
		
		
		objConfig.programGameName = form.programGameName.value;
		objConfig.version = form.version.value;
		objConfig.versionEx = form.versionEx.value;
		objConfig.website = form.website.value;
		objConfig.developer = form.developer.value;
		//objConfig.textColor = form.textColor.value;
		
		objConfig.outExeName = form.nameEnglish.value.toLowerCase() + "_setup_" + form.version.value.toLowerCase() + ".exe";
		objConfig.outExeTitle = "《" + form.nameCn.value + "》 " + form.versionEx.value + "版";
		
		//objConfig.isPopularize = form.isPopularize.value;
		//if ( !objConfig.isPopularize )
		//{
			////如果没有得到值，则用户用的可能是radiobox
			//if ( $("isPopularizeTrue").checked )
			//{
				//objConfig.isPopularize = "true";
			//}
			//else
			//{
				//objConfig.isPopularize = "false";
			//}
		//}
		
		objConfig.compressType = form.compressType.value;
		if ( !objConfig.compressType )
		{
			//如果没有得到值，则用户用的可能是radiobox
			if ( $("compressTypeZLib").checked )
			{
				objConfig.compressType = "zlib";
			}
			else if ( $("compressTypeBZip2").checked )
			{
				objConfig.compressType = "bzip2";
			}
			else if ( $("compressTypeLzma").checked )
			{
				objConfig.compressType = "lzma";
			}
			else
			{
				objConfig.compressType = "";
			}
		}

		objConfig.isSplitCompress = form.isSplitCompress.value;
		if ( !objConfig.isSplitCompress )
		{
			//如果没有得到值，则用户用的可能是radiobox
			if ( $("isSplitCompressCustom").checked )
			{
				objConfig.isSplitCompress = "customSplit";
			}
			else if ( $("isSplitCompressDefault").checked )
			{
				objConfig.isSplitCompress = "defaultSplit";
			}
			else
			{
				objConfig.isSplitCompress = "noSplit";
			}
		}
		
		if ( objConfig.isSplitCompress == "customSplit" )
		{
			objConfig.splitCompressPassword = form.splitCompressPassword.value;
			objConfig.compressFileName = form.compressFileName.value;
			objConfig.zipFileSize = form.zipFileSize.value;
			if (  !objConfig.compressFileType )
			{
				//如果没有得到值，则用户用的可能是radiobox
				if ( $("compressFileZip").checked )
				{
					objConfig.compressFileType= "ExtractZipMutiArchivesA";
					objConfig.sizeFunction = "GetZipArchiveSizeA";
				}
				else if ( $("compressFile7z").checked )
				{
					objConfig.compressFileType = "Extract7zMutiArchivesA";
					objConfig.sizeFunction = "Get7zArchiveSizeA";
				}
				else
				{
					objConfig.compressFileType = "ExtractZipMutiArchivesA";
					objConfig.sizeFunction = "GetZipArchiveSizeA";
				}
			}
		}
		else if( objConfig.isSplitCompress == "defaultSplit" )
		{
			objConfig.splitCompressPassword = "";
			objConfig.compressFileName = form.nameEnglish.value + form.versionEx.value + ".7z.001";
			objConfig.zipFileSize = "1.8g";
			objConfig.compressFileType = "Extract7zMutiArchivesA";
			objConfig.sizeFunction = "Get7zArchiveSizeA";
		}
		else
		{
			objConfig.splitCompressPassword = "";
			objConfig.compressFileName = form.nameEnglish.value + form.versionEx.value + ".7z.001";
			objConfig.zipFileSize = "1.8g";
			objConfig.compressFileType = "Extract7zMutiArchivesA";
			objConfig.sizeFunction = "Get7zArchiveSizeA";
		}

		objConfig.isSetupDotnet = form.isSetupDotnet.checked;
		objConfig.isSetupVcredist = form.isSetupVcredist.checked;
		objConfig.isSetupVcredist2008 = form.isSetupVcredist2008.checked;
		
		objConfig.isSetupDX = form.isSetupDX.checked;
//		objConfig.isSetupDX10 = form.isSetupDX10.checked;
//		if ( objConfig.isSetupDX == true )
//		{
//			objConfig.isSetupDX = false;
//			this.showError( "暂时不支持DirectX的安装" );
//		}
		objConfig.versionDX = form.versionDX.value;
		if ( !objConfig.versionDX || objConfig.versionDX == "" )
		{
			objConfig.versionDX = "";
		}
		
		var content = objConfig.toJSONString();
		var filepath = NSISBrowser.getPath()+"Config\\"+'save.conf';
		NSISBrowser.writeFile( filepath , content );
		
		content = $("license").value;
		if( content )
		{
			var temp = content.slice(-2);
			if("\r\n" != temp)
			{
				content += "\r\n";
			}
			filepath =  NSISBrowser.getPath()+"Resources\\license.txt";
			NSISBrowser.writeFile( filepath , content );
		}
		this.copySkin();

		
		this.showMessage("当前配置已保存");
	};
	
	//==Private Method================================================
	
	//状态条显示
	var _init = function( form )
	{
		//初始化
		if ( !form )
		{
			form = $("nsisform");
		}
		
		form.nameCn.value = "";
		form.nameEn.value = "";
		form.nameEnglish.value = "";
		form.AppChanel.value = "01";
		form.gameId.value = "";
		form.productMP.value = "1";
		form.programName.value = "";
			
			
		form.programGameName.value = "";
		form.version.value = "";
		form.versionEx.value = "";
		form.website.value = "http://";
		form.developer.value = "";

		//$("isPopularizeFalse").setAttribute("checked","checked");
		form.compressType.value = "zlib";
		//form.compressType[0].checked = 1;
		$("isSplitCompressFalse").setAttribute("checked","checked");
		form.splitCompressPassword.value = "sndagame";
		form.zipFileSize.value = "1.8G";
		form.compressFileName.value = "";
		$("compressFile7z").setAttribute("checked","checked");
		form.isSetupDotnet.checked = false;
		form.isSetupVcredist.checked = false;
		form.isSetupVcredist2008.checked = false;
		form.isSetupDX.checked = false;
		form.versionDX.value = "";
//		form.isSetupDX10.checked = false;
//		form.versionDX10.value = "";
		
		//form.textColor.value = "#FF0000";
		
		$("skinHeaderPath").value = "";
		$("skinLeftPath").value = "";
		$("skinPTPath").value = "";
		$("skinBottomPath").value = "";
		$("skinSplashPath").value = "";
		$("skinSetupPath").value = "";
		$("skinUninstallPath").value = "";

		$("skinPath").value = "";
	};
	
	var _showStatus = function ( str , second )
	{
		if ( _hTimerHideStatus != null )
			clearTimeout( _hTimerHideStatus );
		if ( second == null )
		{
			second = 5000;
		}

		_divStatus.innerHTML = str;
		_divStatus.style.visibility = 'visible';
		if ( second )
		{
			_hTimerHideStatus = setTimeout( _hideStatus , second );
		}
	};
	var _hideStatus = function ()
	{
		_divStatus.style.visibility = 'hidden';
		_hTimerHideStatus = null;
	};


	this._showMessage = function( msg )
	{
		$("status").value = msg;
	};
	
	//检查皮肤包是否完整
	this._checkSkinPackage = function ( filelist )
	{
		var requiredItems = ["header.bmp","left.bmp","pt.bmp","bottom.bmp","splash.bmp","setup.ico","uninstall.ico"]
		var i,j,arrFile;
		var foundCount = 0;
		try
		{
			for ( i=0;i<filelist.length;i++)
			{
				eval("arrFile="+filelist[i]);
				if ( arrFile[1] == 1 )
				{
					for ( j=0;j<requiredItems.length;j++)
					{
						if ( arrFile[0].toLowerCase() == requiredItems[j] )
						{
							foundCount++;
							break;
						}
					}
				}
			}
			
			
		}
		catch ( e )
		{
			return false;
		}

		if ( foundCount == requiredItems.length )
		{
			return true;
			
		}
		else
		{
			return false;
		}
	};
	

};

