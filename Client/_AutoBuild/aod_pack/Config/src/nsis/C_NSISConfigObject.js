/**
 * 配置文件对象类
 *
 * 负责记录nsis的配置信息，并且提供生成配置内容的方法
 *
 * 方法列表
 *    generate : function()	//将配置信息转换成配置模板
 *    addFile : function( path )	//添加一个文件到文件列表，文件列表中的内容是不会重复的
 *    removeFile : function( path )	//移除一个文件
 *    getFilelist : function()		//获得文件列表
 *    addFolder : function( path )	//添加一个文件夹
 *    removeFolder : function( path )	//移除一个文件夹
 *    getFolderlist : function()	//获取文件夹列表
 *    setMainFolder : function( path )	//设置主文件夹
 * 
 * @author: xufeng@snda.com
 */
 

var C_NSISConfigObject = function()
{
	//==Config Property==============================================
	this.nameCn = '';
	this.nameEn = '';
	this.nameEnglish = '';
	this.AppChanel = '01';
	this.gameId = 0;
	this.productMP = 0 ;
	this.programName = '';

	this.programGameName = '';
	this.version = '';
	this.versionEx = '';
	this.setupType = 'disk';
	this.website = '';
	this.isNetBar = true;	//是否开启网吧安装页面
	
	this.outExeName = '';
	this.outExeTitle = '';
	
	this.isPopularize = false;	//是否开启推广员
	this.compressType = 'zlib';	//压缩方式zlib,bzip2,lzma
	this.isSplitCompress = false;
//	this.zipFileNum = 1;		//压缩文件个数
	this.splitCompressPassword = '';
	this.compressFileName = '';
	this.compressFileType = '';
	this.sizeFunction = "";
	
	this.isSetupDotnet = false;	//是否安装.NET
	this.isSetupVcredist = false;	//是否安装vcredist2005
	this.isSetupVcredist2008 = false;	//是否安装vcredist2008
	this.isSetupDX = false;		//是否安装DX
	//this.isSetupDX10 = false; //是否安装DX10
	this.versionDX = "";		//DX版本
	this.developer = "";
	this.license = "\r\n";//license
	
	//this.textColor = "";

	//==Template=====================================================
	//this._template = null;

	//==Public Method=================================================
//	/**
//	 * 设置NSIS模板
//	 *
//	 * @param C_NSISTemplate	//要设置的模板对象
//	 */
//	this.setTemplate = function( template )
//	{
//		this._template = template;
//	};
	/**
	 * 将配置信息生成配置文档
	 *
	 * @return string	//配置文档内容，如果返回空字符串，则表示配置失败
	 */
	this.getContent = function()
	{
		var err = this.isLegal();
		var myTemplate = "";
		var myLicense = "";
		var setup_type = (this.setupType == "disk")? "#": "";

		if ( err == "" )
		{
			myTemplate = NSISTemplate.getTemplate();
			//myLicense = NSISLicenseTemplate.getLicense(this.nameCn,this.nameEn,this.website,this.developer);
			
			myTemplate = myTemplate.replace( "#[[PRODUCT_CHS_NAME]]#" , this.nameCn );
			myTemplate = myTemplate.replace( "#[[PRODUCT_EN_NAME]]#" , this.nameEn );
			myTemplate = myTemplate.replace( "#[[PRODUCT_ENGLISH_NAME]]#" , this.nameEnglish );
			myTemplate = myTemplate.replace( "#[[PRODUCT_APP_CHANEL]]#" , this.AppChanel );
			myTemplate = myTemplate.replace( /#\[\[PRODUCT_GAMEID\]\]#/g , this.gameId );
			myTemplate = myTemplate.replace( "#[[PRODUCT_MP]]#" , this.productMP );
			myTemplate = myTemplate.replace( "#[[PROGRAM_NAME]]#" , this.programName );
			
			myTemplate = myTemplate.replace( "#[[PROGRAM_GAME_NAME]]#" , this.programGameName );
			myTemplate = myTemplate.replace( "#[[PRODUCT_VERSION]]#" , this.version );
			myTemplate = myTemplate.replace( "#[[PRODUCT_EXT_VERSION]]#" , this.versionEx );
			myTemplate = myTemplate.replace( "#[[SETUP_TYPE]]#" , setup_type );
			myTemplate = myTemplate.replace( "#[[PRODUCT_WEB_SITE]]#" , this.website );
			myTemplate = myTemplate.replace( "#[[SWITCH_NETBAR]]#" , this._getSwitchValue( this.isNetBar ) );
			
			myTemplate = myTemplate.replace( "#[[EXE_TITLE]]#" , this.outExeTitle );
			myTemplate = myTemplate.replace( "#[[OUT_EXE_NAME]]#" , this.outExeName );
			
			myTemplate = myTemplate.replace( "#[[SWITCH_COMMEND]]#" ,this._getSwitchValue( this.isPopularize ) );
			myTemplate = myTemplate.replace( "#[[PRODUCT_COMPRESSTYPE]]#" , this.compressType );
			myTemplate = myTemplate.replace( /#\[\[SWITCH_ZIPFILE\]\]#/g , this._getSwitchValueForSplit( this.isSplitCompress ) );
			myTemplate = myTemplate.replace( "#[[SWITCH_ZIPPASSWORD]]#" , this.splitCompressPassword );
//			myTemplate = myTemplate.replace( "#[[SWITCH_ZIP_FILE_NUM]]#" , this.zipFileNum );
			myTemplate = myTemplate.replace( "#[[ZIP_FILE_NAME]]#" , this.compressFileName );
			myTemplate = myTemplate.replace( "#[[UNZIP_FUNCTION]]#" , this.compressFileType );
			myTemplate = myTemplate.replace( "#[[UNZIP_SIZE_FUNCTION]]#" , this.sizeFunction );

			myTemplate = myTemplate.replace( "#[[SWITCH_SETUP_DOTNET]]#" , this._getSwitchValue( this.isSetupDotnet ) );
			//mytemplate = myTemplate.replace("#[[DONET_DOWNLOAD_URL]]#" , this.DonetDownloadURL );
			myTemplate = myTemplate.replace( "#[[SWITCH_SETUP_VCREDIST]]#" , this._getSwitchValue( this.isSetupVcredist ) );
			myTemplate = myTemplate.replace( "#[[SWITCH_SETUP_VCREDIST_2008]]#" , this._getSwitchValue( this.isSetupVcredist2008 ) );
			myTemplate = myTemplate.replace( "#[[SWITCH_SETUP_DIRECTX]]#" , this._getSwitchValue( this.isSetupDX ) );
			myTemplate = myTemplate.replace( "#[[SETUP_DX_VERSION]]#" , this.versionDX );
			

			//myTemplate = myTemplate.replace( "#[[SETUP_TEXT_COLOR]]#" , this.textColor );

		}

		return myTemplate;
	};

	/**
	 * 验证配置信息对象是否合法
	 * 此方法由setConfigObject方法调用
	 */
	this.isLegal = function()
	{
		var ret = '';
		if ( this.nameCn == '' )
		{
			ret = '游戏中文名不能为空';
		}
		else if ( this.nameEn == '' )
		{
//update			ret = '游戏英文简称不能为空';
			ret = '注册表项不能为空';
		}
		else if ( this.nameEnglish == '' )
		{
			ret = '游戏英文名不能为空';
		}
		else if ( this.AppChanel == '' )
		{
			ret = '渠道名称不能为空';
		}
		else if ( isNaN( this.gameId ) == true )
		{
			ret = '游戏ID必须是数字';
		}
		else if ( this.gameId <= 0 )
		{
			ret = '游戏ID必须大于0';
		}
		else if ( isNaN( this.productMP ) == true )
		{
			ret = '推广员奖励倍数必须是数字';
		}
		else if ( this.productMP <= 0 )
		{
			ret = '推广员奖励倍数必须大于0';
		}
		else if ( this.programName == '' )
		{
			ret = '游戏客户端启动程序名不能为空';
		}
		else if ( this.programGameName == '' )
		{
			ret = '游戏客户端主程序名不能为空';
		}
		else if ( this.version == '' )
		{
			ret = '客户端版本号不能为空';
		}
		else if ( this.version.match(/\d+\.\d+\.\d+\.\d+/) == null )
		{
			ret = "客户端版本号的格式必须是X.X.X.X";
		}
		else if ( this.versionEx == '' )
		{
			ret = '对外版本号不能为空';
		}
		else if ( this.setupType == '' )
		{
			ret = '安装包类型没选择';
		}
		else if ( this.website == '' )
		{
			ret = '游戏主页不能为空';
		}
		else if ( this.compressType != 'kz' && this.compressType != 'zlib' && this.compressType != 'bzip2' && this.compressType != 'lzma' )
		{
			ret = '压缩方式只能是zlib，bzip2，lzma';
		}
		else if ( this.website == 'http://' )
		{
			ret = '游戏网址不合法';
		}
		else if ( this.textColor == ''  )
		{
			ret = '游戏网址不合法';
		}else if( /*(this.isSplitCompress == customSplit) ||*/ (this.isSplitCompress == 'customSplit') ){	//是否使用了自定义分卷压缩
			if( this.compressFileName == '' ){
				ret = '压缩文件名为空';
			}else if( (this.compressFileType != 'ExtractZipMutiArchivesA') && (this.compressFileType != 'Extract7zMutiArchivesA') ){
				ret = '压缩方式只能是zip,7z';
			}
			if(this.compressFileType == 'ExtractZipMutiArchivesA'){
				var reg = /^.*\.zip$/ig;
				if(!reg.test( this.compressFileName)){
					ret = "压缩包名称与所选择的分卷压缩方式zip不一致"
				}
			}
			if(this.compressFileType == 'Extract7zMutiArchivesA'){
				var reg = /^.*\.7z\.001$/ig;
				if(!reg.test( this.compressFileName)){
					ret = "压缩包名称与所选择的分卷压缩方式7z不一致"
				}
			}
			if( this.zipFileSize == '' ){
				ret = '压缩文件大小不能为空';
			} else{
				var reg = /^[1-9]\d{0,10}$|^[0-9]\d{0,10}\.?\d{0,9}\M$|^[0-9]\d{0,9}\.?\d{0,9}\MB$|^[0-9]\d{0,9}\.?\d{0,9}\K$|^[0-9]\d{0,9}\.?\d{0,9}\KB$|^[0-9]\d{0,9}\.?\d{0,9}\G$|^[0-9]\d{0,9}\.?\d{0,9}\GB$/ig;
				if( !reg.test( this.zipFileSize ) || this.zipFileSize == 0){
					ret = "压缩文件大小必须为实数或实数加上以M,K,G,MB,KB,GB(不区分大小写)结尾且大于0";
				}
				if( this.zipFileSize > 2147483648 ) // 支持FAT32，单个分卷包大小小于2G
				{
					ret = "压缩文件大小设置错误,为了支持FAT32,请将单个压缩文件大小设置为2G以下！";
				}
			}
		}

		return ret;
	};
	
	
	//==Private Method=================================================
	/**
	 * 将true转换成空，false转换成#
	 * @param bool
	 * @return string
	 */
	this._getSwitchValue = function( param )
	{
		if ( param == true || param == 'true')
		{
			return '';
		}
		else
		{
			return '#';
		}
	};
	/**
	 * 将true转换成空，false转换成#
	 * @param bool
	 * @return string
	 */
	this._getSwitchValueForSplit = function( param )
	{
		if ( param == 'defaultSplit' || param == 'customSplit')
		{
			return '';
		}
		else
		{
			return '#';
		}
	};
};
 
 

