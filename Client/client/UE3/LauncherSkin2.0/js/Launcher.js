<!--
var Launcher =
{
    // 初始化
	// 说明：通用的基本初始化操作，包括启动扩展调用、禁止窗口内容选中、
	// 启动moveable样式的拖动
    "Init": function ()
    {
		// 启动扩展调用
		Launcher.external_ready = true;
        // 禁止窗口内容选中
        document.body.onselectstart = function ()
        {
            return false;
        };
        // 启动moveable样式的拖动
        Launcher.EnableMove("moveable");
		
		Launcher.UpdateWindow();
		// 吃掉错误，（好像不能完全吃掉）
		window.onerror =function () { return true; };
    },
	
	// 是否使用扩展接口的控制信号
	"external_ready":false,
	
	//
    // 以下可以使用的扩展接口的包装，用于调用外部接口
	//
	
	// 更新窗口，包括形状、背景等，在窗口形状、背景、半透明内容发生变化时调用
    "UpdateWindow": function ()
    {
		if( Launcher.external_ready)
			window.external.UpdateWindow(); 
    },
	"ReadFromFiled": function (path, codePage)
    {
		//if (window.external.ReadFromFile != undefined)
			return window.external.ReadFromFile(path, codePage);
		//return "";
    },
	// 窗口开始拖动，如果设定了某个位置，可以用鼠标拖动窗口，则应在鼠标左键按下时，调用此接口
    "MoveWindow": function ()
    {
		if( Launcher.external_ready )
			return window.external.MoveWindow();
    },
	// 最小化窗口，调用此接口可使窗口最小化
    "Minimize": function ()
    {
		if( Launcher.external_ready)
			return window.external.MinimizeLauncher();
    },
	// 关闭窗口，调用此接口可以关闭窗口，这将引起程序退出
    "Close": function ()
    {
		if( Launcher.external_ready)
			return window.external.CloseLauncher();
    },
	
	// 开始游戏，在需要启动游戏时调用，调用后将直接启动游戏程序，（游戏程序的路径在配置文件中配置）
	// 参数：gameidName, 游戏的ID名称，需和配置文件中配置一致。比如"SuddenAttack"
	//       param，游戏的启动参数，即游戏启动命令行中的参数，如“-192.168.20.2:6053 -start”
    "StartGame": function (gameidName, param)
    {
		if( Launcher.external_ready)		
		{
			var paras = "-sdo -ip=" + param;
			return window.external.StartGame(gameidName, paras);
		}
    },
	// 启动分区更新，一般在游戏真正启动前调用
	// 参数：areaNo，区号
	//		 upname，更新内容名称，需和配置中一致，如“SuddenAttackZone“
	// 返回：0, 目前无需更新
	//		 1，更新已启动
	"StartUpdate": function (areaNo, upname)
	{
		if( Launcher.external_ready)
			return window.external.StartUpdate(areaNo, upname);
	},
	// 运行一个exe文件，一般在程序需要启动外部辅助程序时调用，如启动系统配置程序等
	// 参数：exePath,启动文件的路径，以Launcher目录为原点的相对路径
	//		 param，程序的启动参数
	//		 flag, 0：启动后立即返回；1：启动后等待结束后返回
	"RunExe": function(exePath, param, flag)
	{
		if( Launcher.external_ready)
			return window.external.RunExe(exePath, param, flag);
	},
	"GetLocalCurVer": function (strUpdateName)
	{
		if( Launcher.external_ready)
			return window.external.GetLocalCurVer(strUpdateName, "0");
	},
	
	"GetServerLatestVer": function (strUpdateName, strAreaNo)
	{
		if( Launcher.external_ready)
			return window.external.GetServerLatestVer(strUpdateName, strAreaNo);
	},

	// 读取文本文件内容
	// 参数：path, 文件所在路径，以Launcher目录为原点的相对路径
	//		 codePage，文件编码，如“utf8”
	// 返回：文件的所有内容字符串
	// 说明：请勿读取太大的文件
	"ReadFromFile": function (path, codePage)
    {
		if( Launcher.external_ready)
			return window.external.ReadFromFile(path, codePage);		
    },
	// 写入文本文件内容
	// 参数：path, 文件所在路径，以Launcher目录为原点的相对路径
	//		 content, 文件内容，字符串格式
	//		 codePage，文件编码，如“utf8”
	//		 isAppend, 是否添加，如果为true，则新写内容在文件最后
	
	"WriteToFile": function (path, content, codePage, isAppend)
    {
		if( Launcher.external_ready)
			return window.external.WriteToFile(path, content, codePage, isAppend);
    },
	// 读取网络文件内容（文本）
	// 参数：url, 网络内容所在的url
	//		 code_page,文件编码，如“utf8”
	// 返回：返回文件的所有内容
	// 说明：请勿读取太大的文件
	"GetURL": function(url, code_page)
	{
		if( Launcher.external_ready)
			return window.external.GetURL(url, code_page);
	},
	// 从网络下载文件
	// 参数：url, 网络内容所在的url
	//		 file，保存为本地的文件路径
	// 返回：返回下载文件的大小
	// 说明：1，可以适用于任意类型内容
	//		 2，同步下载，直到下载完成才返回，下载太大的文件可能有很长时间无法做用户响应	
	"DownloadToFile": function(url, file)
	{
		if( Launcher.external_ready)
			return window.external.DownloadToFile(url, file);
	},
	
	// 启用Ping功能
	// 参数：pingliststr，目标地址列表，格式如下
	//			[{"id":"1", "ip":"192.168.0.1"},{"id":"2", "ip":"192.168.0.2"}]
	//			说明 id：自定，返回结果时的标识；ip:目标地址
	//		 ping_count：Ping的次数
	// 说明：异步调用，调用后立即返回，Pint的结果通过回调返回	
	"DoPing": function(pingliststr, ping_count)
	{
		if( Launcher.external_ready)
			return window.external.DoPing(pingliststr, count);
	}, 
	// 跨框架Js调用
	// 参数：docName，目标框架的doc名称（每个DOC通过JS调用接口返回自己的名称）
	//		 func，JS函数名
	//		 paramlist，参数列表，每个参数以‘,’分隔,参数中含有‘,’以‘\’进行转义,‘\’使用‘\\’表示
	//				如：param1,param2, p\,pp, p\\ppp...
	"AcrossFrameCallJsFunc":function (docName, func, paramlist)
	{
		if( Launcher.external_ready)
			return window.external.AcrossFrameCallJsFunc(docName, func, paramlist);
	},
	// 读去INI文件中指定项的内容
	// 参数：file，ini文件的路径，以Launcher所在目录为原点的相对路径
	//		 section，ini文件中的分组
	//		 key，ini文件中的key
	// 返回：返回INI文件中该项的内容
	"ReadIniValue":function (file, section, key)
	{	
		if( Launcher.external_ready)
			return window.external.ReadIniValue(file, section, key);
	},
		
	"NameToIp":function (name)
	{	
		if( Launcher.external_ready)
			return window.external.NameToIp(name);
	},	

	//
    // 以下为实用，自用函数
	// 
	
	// 对网页中，所有某个class样式的元素，启用鼠标拖动窗口
	// 参数：cls，样式名
	"mousedown": false,
    "EnableMove": function (cls)
    {
        var oa = Launcher.getElementsByClassName(cls);
        for (i = 0; i < oa.length; i++)
        {
            oa[i].onmousedown = function ()
            {	
				Launcher.mousedown=true;
            };
			oa[i].onmousemove = function()
			{
				if (Launcher.mousedown)
				{
					Launcher.mousedown=false;
					Launcher.MoveWindow();
				}
			};
			oa[i].ondragstart = function ()
			{		
				Launcher.mousedown=true;			
				return false;
			}			
        }		
    },
	// 获取某样式的所有元素
	// 参数：eleClassName，样式名
    "getElementsByClassName": function (eleClassName)
    {
        var getEleClass = []; //定义一个数组
        var myclass = new RegExp("\\b" + eleClassName + "\\b"); //创建一个正则表达式对像
        var elem = document.getElementsByTagName("*"); //获取文档里所有的元素
        for (var h = 0; h < elem.length; h++)
        {
            var classes = elem[h].className; //获取class对像
            if (myclass.test(classes)) getEleClass.push(elem[h]); //正则比较，取到想要的CLASS对像
        }
        return getEleClass; //返回数组
    },
	//刷新当前应该显示的图片，“正在更新” or “进入游戏”
	//strUpdateName为当前正在更新的更新名字，入panlongpre，panlongzone
	//strAreaNo为当前更新时选中的区，前置更新时，传入“0”，分区更新时，传入选中区的No
	"RefreshStartImg":function(strUpdateName,  strAreaNo)
	{
		//alert('运行显示图片判断');
		var strLocalCurVer = Launcher.GetLocalCurVer(strUpdateName);
		var strServerLatestVer = Launcher.GetServerLatestVer(strUpdateName, strAreaNo);
		if(strLocalCurVer != strServerLatestVer)
		{
			$("#btn_startGame").removeClass("go_game");
			$("#btn_startGame").addClass("go_game1");
		}
		else
		{
			$("#btn_startGame").removeClass("go_game1");
			$("#btn_startGame").addClass("go_game");
		}
    }
};

// 外部将会调用的JS接口
// 请在各自的JS中实现
/*
// 增加游戏列表中的内容（可以实现为空）
function AddGame(gameName, gameid, ico)
{
}
// 设置当前游戏的id（可以实现为空）
function SetCurrentGame(gameid)
{
    
}
// 清空游戏列表（可以实现为空）
function ClearGameList()
{}

// 设置更新进度
// 参数: gameid, 游戏ID，请检查是否与自己的游戏名一致
// 		 progress,进度，0-100
//		 taskName,更新进展信息（仅Progress==-1时有效）
function SetProgress(gameid, progress, taskName)
{}

// 设置启动按钮为“不”可用
// 参数: gameid, 游戏ID，请检查是否与自己的游戏名一致
function DisableStart(gameid)
{}

// 设置启动按钮为 “可用”
// 参数: gameid, 游戏ID，请检查是否与自己的游戏名一致
function EnableStart(gameid)
{}

// 获取DOC名称，该名称可以在AcrossFrameCallJsFunc时使用
function GetDocName()
{}

//获取固定点坐标，如果在界面网页变化的过程中，在网页的上部、左边进行内容变动，
//导致主体内容下移或右移，这时可以返回主体部分的坐标，从而使界面主体保持不动
// 通常可以返回主体中任意某个元素的坐标
// 如不存在上部、左边的变动，可以返回
// 返回格式为 ”123，345“
function GetOriginCoordinate()
{}

// DoPing的结果返回调用
// 参数:id, 调用DoPing时传入的标识
// 		 responseTime，ping的返回时间，单位（ms)
function PingResult(id, responseTime)
{}
*/
-->