/**
 * 核心功能函数
 * 包装了NSIS核心对象的方法
 * 
 * 方法列表
 *     selectFile : function()
 *     selectFolder : function()
 *     setWindowSize : function( width , height )
 *     isFileExists : function( path )
 *     isDirExists : function( path )
 *     messageBox : function( msg )
 *
 * @author: xufeng@snda.com
 */
 
 
var C_NSISBrowser = function( browser ){
	var _browser = browser;
	
	//==Public Method=================================================
	/**
	 * 是否支持拖拽图片
	 *
	 * @return string
	 */
	this.getVersion = function()
	{
		try
		{
			return window.external.Version();
		}
		catch ( e )
		{
			return "";
		}

	};
	/**
	 * 选择一个文件
	 * 阻塞
	 * @param string	//指定文件类型
	 * @return Array	//返回选择的文件完整路径的数组
	 */
	this.selectFile = function( filter )
	{
		//指定文件类型name|*.bmp|name2|*.*
		var myreturn = '';
		if ( !filter )
		{
			filter = "浏览所有文件(*.*)|*.*";
		}
		
		try
		{
			myreturn = _browser.call("selectfile" , filter);
		}
		catch ( e )
		{
			this._errHandler( e );
		}
		
		return myreturn;
	};
	/**
	 * 选择一个文件夹
	 * 阻塞
	 *
	 * 
	 * @return string	//返回选择的文件夹的完整路径
	 */
	this.selectFolder = function()
	{
		var myreturn = '';
		try
		{
			myreturn = _browser.call("selectdir");
		}
		catch ( e )
		{
			this._errHandler( e );
		}
		return myreturn;
	};

	/**
	 * 检查文件是否存在
	 *
	 * @param string	//文件完整路径
	 * @return bool
	 */
	this.isFileExists = function( path )
	{
		var myreturn = '';
		try
		{
			myreturn = _browser.call("fileexists" , path);
		}
		catch ( e )
		{
			this._errHandler( e );
		}
		return myreturn;
	};
	/**
	 * 检查文件是否存在
	 *
	 * @param string	//文件完整路径
	 * @return bool
	 */
	this.isDirExists = function( path )
	{
		var myreturn = '';
		try
		{
			myreturn = _browser.call("direxists" , path);
		}
		catch ( e )
		{
			this._errHandler( e );
		}
		return myreturn;
	};
	/**
	 * 获得文件夹中的文件列表
	 *
	 * @param string	//文件完整路径
	 * @return bool
	 */
	this.getFilelist = function( path )
	{
		var myreturn = '';
		try
		{
			myreturn = _browser.call("listfile" , path);
		}
		catch ( e )
		{
			this._errHandler( e );
		}
		return myreturn;
	};
	/**
	 * 读取文件内容
	 *
	 * @param string	//文件完整路径
	 * @return bool
	 */
	this.readFile = function( path )
	{
		var myreturn = '';
		try
		{
			myreturn = _browser.call("readtextfile" , path );
		}
		catch ( e )
		{
			this._errHandler( e );
		}
		return myreturn;
	};
	/**
	 * 写文件内容
	 *
	 * @param string	//文件完整路径
	 * @param string	//文件内容
	 * @return bool
	 */
	this.writeFile = function( path , content )
	{
		var myreturn = '';
		try
		{
			myreturn = _browser.call("writetextfile" , content , path );
		}
		catch ( e )
		{
			this._errHandler( e );
		}
		return myreturn;
	};
	/**
	 * 复制文件
	 *
	 * @param string	//文件源地址
	 * @param string	//文件目的地址
	 * @param bool		//是否覆盖，默认值为true
	 * @return bool
	 */
	this.copyFile = function( from , to , isCover , fnCallback )
	{
		var myreturn = '';
		if ( isCover != false ){
			isCover = true;
		}

		try
		{
			myreturn = _browser.call("copyfile" , from , to , isCover );
		}
		catch ( e )
		{
			this._errHandler( e );
		}
		return myreturn;
	};
	/**
	 * 获得当前浏览器的绝对路径
	 *
	 * @return bool
	 */
	this.getPath = function()
	{
		try
		{
			return window.external.CurrInfo("currentdir");
		}
		catch ( e )
		{
			this._errHandler(e);
		}
		
	};
	/**
	 * 获得当前进程的ID
	 *
	 * @return bool
	 */
	this.getProcessId = function()
	{
		try
		{
			return window.external.CurrInfo("currentprocess");
		}
		catch ( e )
		{
			this._errHandler(e);
		}
		
	};
	/**
	 * 设置窗体大小
	 *
	 * @param int	//要设置的窗体宽度，单位像素
	 * @param int	//要设置的窗体高度，单位像素
	 * @return bool
	 */
	this.setWindowSize = function( width , height )
	{
		try
		{
			return window.external.UICtrl("SetWindowSize",width,height);
		}
		catch ( e )
		{
			this._errHandler(e);
		}
		
	};
	/**
	 * 移动窗口
	 *
	 * @param int	//水平方向移动多少像素，向左为正
	 * @param int	//垂直方向移动多少像素，向上为正
	 * @return void
	 */
	this.moveWindow = function( h , v )
	{
		try
		{
			window.external.UICtrl("MoveWindow" , h , v );
		}
		catch ( e )
		{
			this._errHandler(e);
		}
	};
	/**
	 * 是否显示边框
	 *
	 * @param bool	//是否显示边框
	 * @return void
	 */
	this.showBorder = function( isShow )
	{
		try
		{
			if ( isShow == false )
				window.external.UICtrl("ShowBorder" , 0 , 0);
			else
				window.external.UICtrl("ShowBorder" , 1 , 0);	
		}
		catch ( e )
		{
			this._errHandler(e);
		}

	};
	/**
	 * 是否支持拖拽图片
	 *
	 * @param bool
	 * @return void
	 */
	this.dragEnable = function( isEnable )
	{
		try
		{
			if ( isEnable == false )
				window.external.UICtrl("DragEnable" , 0 , 0 );
			else
				window.external.UICtrl("DragEnable" , 1 , 0 );
		}
		catch ( e )
		{
			this._errHandler(e);
		}

	};
	
	/**
	 * 设置网页区域的大小
	 *
	 * @param int	//要设置的网页区域宽度，单位像素
	 * @param int	//要设置的网页区域高度，单位像素
	 * @return bool
	 */
	this.setWebSize = function( width , height )
	{
		try
		{
			return window.external.UICtrl("setWebSize",width,height);
		}
		catch ( e )
		{
			this._errHandler(e);
		}
		
	};
	/**
	 * 设置网页区域的大小
	 *
	 * @param int	//要设置的网页区域宽度，单位像素
	 * @param int	//要设置的网页区域高度，单位像素
	 * @return bool
	 */
	this.setWindowState = function( state )
	{
		try
		{
			return window.external.UICtrl("setWindowState",state,0);
		}
		catch ( e )
		{
			this._errHandler(e);
		}
		
	};
	/**
	 * 退出程序
	 *
	 * @return void
	 */
	this.exit = function()
	{
		try
		{
			window.external.ExitProcess(0);
		}
		catch ( e )
		{
			this._errHandler(e);
		}
	};
	/**
	 * 编译nsis脚本
	 * 如果找不到makeNSIS的话，则弹出文件选择对话框
	 *
	 * @return bool
	 */
	this.makeNSIS = function()
	{
		try
		{
			alert ("ready to make NSIS");
			ret = window.external.RunExec("D:\\Project\\NSIS\\NSIS\\NSIS\\makensisw.exe","D:\\Project\\NSIS\\bin\\标准模板.nsi",false);
			
			alert ("complete,"+ret);
		}
		catch ( e )
		{
			this._errHandler(e);
		}
	};
	//==Private Method=====================================================
	/**
	 * 统一处理错误的逻辑
	 *
	 * @param Error
	 */
	this._errHandler = function( objError )
	{
		//alert ("Error Code:"+objError.number+"\nError Message:"+objError.description );
	};
};
