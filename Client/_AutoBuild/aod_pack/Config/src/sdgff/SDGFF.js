/**
 * SDG浏览器类
 * 
 * 负责最最基本的功能函数调用和错误处理
 * 
 * 方法列表：
 *    call : function( fnName , params... )	//执行插件内部函数，如果出错，抛出异常
 * 
 * 依赖：
 *    json.js
 * 
 * @author: xufeng@snda.com
 */
var C_SDGBrowser = function( modName ){
	
	var dllName = '';

	if ( modName == null || modName == '' )
	{
		dllName =  'sdplug.dll';
	}
	else
	{
		dllName = modName;
	}
	

	this.call = function( fnName )
	{
		var arrParam = [];
		var i;
		for ( i=1;i<arguments.length;i++)
		{
			//有参数
			arrParam.push(arguments[i]);
		}

		//调用外部方法
		var ret = false;
		try
		{
			//总是返回固定格式的JSON字符串
			//[bool,string]
			//其中，bool值指明了调用是否成功，string为被调用功能函数的返回值，也已经经过JSONEncode过了
			if ( isDebug )
			{
				alert ( 'Send Params:'+arrParam.toJSONString() );
			}
			ret = window.external.SDFunc( dllName , arrParam.toJSONString() , fnName );
			if ( isDebug )
			{
				alert ( 'Get Returned String:'+ret );
			}
		}
		catch ( e )
		{
			throw new Error( e.number , e.description );
		}

		//解析返回值
		var arr;
		try
		{
			eval("arr="+ret+";");
		}
		catch ( e )
		{
			throw new Error( arr[0] , '解析返回值失败:'+ret );
		}
		
		if ( arr.length != 2 )
		{
			throw new Error( arr[0] , '返回值不能识别' );
		}

		//解析成功，分析返回值
		if ( arr[0] == 0 )
		{
			//解析第2个元素
			try
			{
				var msg = "";
				if ( arr[1] != "" )
				{
					eval("msg="+arr[1]+";");
				}
			}
			catch( e )
			{
				throw new Error( arr[0] , "解析返回消息失败：" + arr[1] );
				return this._errorOccur( arr[0] , "解析返回消息失败：" + arr[1] );
			}
			//成功
			if ( isDebug )
			{
				alert ('Parse Return:'+msg);
			}
			return msg;
		}
		else
		{
			//失败
			throw new Error( arr[0] , arr[1] );
		}
	};
};

