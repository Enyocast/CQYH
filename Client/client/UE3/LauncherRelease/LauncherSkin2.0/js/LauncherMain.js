<!--
var isDoZone = false;
var LauncherMain =
{
	"timeT":"",
	"LastTime": new Date(),
	"CheckTime": function(name)
	{
		var myDate = new Date();
		timeT += "\n";
		function second(d)
		{
			return d.getHours()*3600 + d.getMinutes()*60 + d.getSeconds();
		}
		timeT += name + "time:" + second(myDate) - second(LauncherMain.LastTime);		
	},
    // 初始化
    "Init": function ()
    {
		Launcher.Init();
        window.external.onSkinLoaded();		
        // 设置当前区
		var curZoneName = LauncherMain.GetCookie("curZoneName");
		var pageElement = document.getElementById("curZoneName");
		if (pageElement != null && curZoneName != null)
		{
			//curZoneName = "ppp";
			pageElement.innerHTML = curZoneName;
		}
		
		// 禁止选中
        document.body.onselectstart = function ()
        {
            return false;
        };
        // 拖动
        Launcher.EnableMove("moveable");
//		var oldFun = Launcher.MoveWindow;
//		Launcher.MoveWindow=function()
//		{
//			ShowHideG_Set("hide");
//			oldFun();
//		}
		
        // 最小化
        var a = document.getElementById("btn_min");
		if (a!=null)
		{			
			a.onclick = function ()
			{
				Launcher.Minimize();
			};
		}

        // 关闭
        a = document.getElementById("btn_close");
        if (a!=null)
		{			
			a.onclick = function ()
			{ 
				Launcher.Close();
			};
        }
        // 开始
		var startGame = function ()
		{	
			if(LauncherMain.Startable == false)
				alert("正在更新");
			else if (LauncherMain.GlobalEnterGameInfo.length <2)
				alert("请选择游戏区");
			else
			{
				//alert( LauncherMain.GlobalEnterGameAreaID );
				if ( LauncherMain.GlobalEnterGameAreaID == "" )
				{
					LauncherMain.GlobalEnterGameAreaID = "0";
				}
				if( Launcher.StartUpdate( LauncherMain.GlobalEnterGameAreaID , "CQYHzone") == 0 )
				{
					Launcher.StartGame(LauncherMain.CurGame.id, LauncherMain.GlobalEnterGameInfo);
				}
				else
				{
					isDoZone = true;
				}
			}
				
		}
		a = document.getElementById("enter");
        if (a!=null)					
			a.onclick = startGame;
		
		// 加载iframe
		var frames = document.getElementsByTagName("iframe");
		for (var i=0; i< frames.length; ++i)
		{
			frames[i].src = frames[i].getAttribute("d_src");
		}		

		// 获取本地版本
		var v = Launcher.ReadIniValue("etc\\home.ini", "ServerName", "version");

		a = document.getElementById("apDiv5");
        if (a!=null && v.length>=5)
		{
			a.innerHTML = "当前客户端版本为: " + v;
		}
		
		// 设置当前区
		LauncherMain.CurZone=LauncherMain.GetCookie("CurZone");
		
		// 加载 本地 服务器列表
		var serversStr= Launcher.ReadFromFiled("LauncherSkin2.0\\js\\servers.js", "utf8");
		
		LauncherMain.LoadServersFromStr(serversStr);
		LauncherMain.RefreshZoneList();
		
		// 加载 远程 服务器列表
		LauncherMain.ReGetServers(
					"http://cq.dorado.sdo.com/cq/servers.js"
					//"http://sa.autopatch.sdo.com/sa/Commonupdatenew/web/Scripts/servers.js"
					,"LauncherSkin\\js\\servers.js"
					,"utf8");
          
      LauncherMain.ShowVersionCode();
	  
	  var strLocalCurVer = Launcher.GetLocalCurVer("CQYHzone", "0");
	  Launcher.WriteToFile("CliV.ini", strLocalCurVer, "utf8", false);
    },
    //数据	
    "CurGame": {
        "id": "991002359"
    },
    "InstalledGames": [],
    "Startable": true,
	"CurZone":"",
	
    //显示版本号 20131014 xuximing@snda.com
    
    'ShowVersionCode': function(){
      var ele = window.document.getElementById("VersionCode");
      var codeInf = window.external.GetLocalCurVer("CQYHzone", "0");
      ele.innerHTML = '当前版本:' + codeInf;
    },
    
    // 向内操作，外部操作内部元素
    "SetInfo": function (index, info)
    {		
        var a = window.document.getElementById("Message");
        if (a == null) return;        
        a.innerHTML = "获取更新文件: " + info;
    },

    "SetProgress": function (index, progress)
    {	 	
		var a = window.document.getElementById("Progress");
        if (a == null || progress <= 0) return;			 		
		a.style.width = progress.toString() + "%";		
        a = window.document.getElementById("ProgressNum");
        if (a == null || progress <= 0) return;
        a.innerHTML = progress.toString() + "%";
    },

    // 自用函数  
	"SetCookie":function(name,value, days)//写cookies函数
	{
		var exp  = new Date();
		exp.setTime(exp.getTime() + days*24*60*60*1000);
		document.cookie = name + "="+ escape (value) + ";expires=" + exp.toGMTString();
	},
	"GetCookie":function(name)//取cookies函数        
	{
		var arr = document.cookie.match(new RegExp("(^| )"+name+"=([^;]*)(;|$)"));
		 if(arr != null) return unescape(arr[2]); return null;

	},
	"DelCookie":function(name)//删除cookie
	{
		var exp = new Date();
		exp.setTime(exp.getTime() - 1);
		var cval=getCookie(name);
		if(cval!=null) document.cookie= name + "="+cval+";expires="+exp.toGMTString();
	},
    //从远程js 或json格式的js文件中读取服务器列表数组
    "ReGetServers": function (URL, saveToLocalFileName, codePage)
    {
		var serversStr = Launcher.GetURL(URL, codePage);
		if (serversStr=="")
			return;					

		LauncherMain.LoadServersFromStr(serversStr);
					
		LauncherMain.RefreshZoneList();
        Launcher.WriteToFile(saveToLocalFileName, serversStr, codePage, false);                
    },

    //当前所要进入的游戏接入区组信息 即为启动游戏所必须的参数
    "GlobalEnterGameInfo": "",
	//当前所要进入区的ID
    "GlobalEnterGameAreaID": "",

    //服务器列表  直接读取本地的json2.js文件
    "servers": [],
	"LoadServersFromStr": function ( serverStr )
	{
		if (serverStr.length<5)
			return;
		var version = 0; //为了消除本地文件为json格式时 全局version=2的影响		

        eval(serverStr);
		
		if (version == 2) // json对像格式
		{
			LauncherMain.servers = servers;	 		
			return;
		}
		// 数组格式
		LauncherMain.servers=[];
		for (var i = 0; i < servers.length; i++)
        {
			LauncherMain.servers[i]={"list":[]};

			LauncherMain.servers[i].foldname = servers[i][0];// 目录名

            for (var j = 1; j < servers[i].length; j++) // 所有区
            {

				LauncherMain.servers[i].list.push(
					{
						"showname":	servers[i][j][0],
						"id":		servers[i][j][1],
						"address":	servers[i][j][2],
						"status":	servers[i][j][3],
						"useable":	(servers[i][j][4]==null)?1:0
					} );
			}
		}
	},
 
    //json格式时
    // 向内操作，外部操作内部元素   构造游戏服务器区组列表
    "RefreshZoneList": function ()
    {
		//服务器列表Dom
		var elemDom = $('.sub_sc');
		//alert("RefreshZoneList");
		var a = document.getElementById("lastZoneName");
		
		if (a!=null)
			a.innerHTML = LauncherMain.GetCookie("lastZoneName");

		//清空Dom界面
		elemDom.html('');

		// 刷新界面
        for (var i = 0; i < LauncherMain.servers.length; i++)
        {
			if (LauncherMain.servers[i] == null){
				continue;
			}
			
			/*
			// 找到目录元素
			var elemId;			
			switch (LauncherMain.servers[i].foldname)
			{
            case "推荐专区":
				elemId = "s1";
				break;
            case "电信专区":
				elemId = "s2";
				break;
			case "网通专区":	
				elemId = "s3";
				break;
			default:
				continue;
			}

			var element = document.getElementById(elemId);
			//if (element==null)
			//	continue;
			*/


			// 生成HTML
			var html = '<strong class="s_title"> '+LauncherMain.servers[i].foldname+'：</strong>\r\n'
			var fold = LauncherMain.servers[i];

			for (var j = 0; j < fold.list.length; j++)
            {
				if (fold.list[j] == null)
					continue;
				if (fold.list[j].useable == 1) 
				{
					html += "<a href=\"#\" "
							+ "id=\"" + LauncherMain.servers[i].list[j].id + "\""
							+ " onclick=\"LauncherMain.ClickServer("+i+"," +j+ ")\" "
							+ " ondblclick=\"LauncherMain.ClickServer("+i+"," +j+ "); \" "							
							+">";


					

					if(LauncherMain.servers[i].list[j].status=="1")
						html += "<em><img src=\"images/new.png\" /></em>";
					if(LauncherMain.servers[i].list[j].status=="2")
						html += "<em><img src=\"images/hot.png\" /></em>";
					if(LauncherMain.servers[i].list[j].status=="3")
						html += "<em><img src=\"images/fire.png\" /></em>";
					if(LauncherMain.servers[i].list[j].status=="4")
						html += "<em><img src=\"images/maintenance.png\" /></em>";
					if(LauncherMain.servers[i].list[j].status=="5")
						html += "<em><img src=\"images/recommend.png\" /></em>";
					if(LauncherMain.servers[i].list[j].status=="6")
						html += "<em><img src=\"images/star.png\" /></em>";
					if(LauncherMain.servers[i].list[j].status=="7")
						html += "<em><img src=\"images/stop.png\" /></em>";

					html +="<span>"+ LauncherMain.servers[i].list[j].showname+"</span>";

					html += "</a>\r\n";
				}
                else
					html += "<a class=\"useless\" href=\"#\" "
							+ " onclick=\"alert('服务器正在维护！')\" "
							+">"
							+ LauncherMain.servers[i].list[j].showname
							+ "</a>\r\n";
				// 是否当前区
				if (fold.list[j].id == LauncherMain.CurZone)
				{	
					LauncherMain.ClickServer(i,j);				
					if (fold.list[j].useable!=1)
					{					
						LauncherMain.GlobalEnterGameInfo = "";
						a = document.getElementById("curZoneName");
						if (a!=null)
							a.innerHTML = fold.list[j].showname +"(维护中)";
					}
				}
			}
			html += "<br />\r\n";


			//添加服务器列表
			elemDom.append(html);
			// 设置界面
			//element.innerHTML = html;
        }		
    },
	"SetVersion":function ()
	{
		var strLocalCurVer = Launcher.GetLocalCurVer("CQYHzone");
		var strServerLatestVer = Launcher.GetServerLatestVer("CQYHzone", LauncherMain.GlobalEnterGameAreaID);
		var ctrlVerInfo = window.document.getElementById("VersionCode");
		var strVerInfo = "当前版本号：" + strLocalCurVer + " 服务器版本号：" + strServerLatestVer;
		
		
		
		//var strLocalCurVer = Launcher.GetLocalCurVer("CQYHzone", "0");
		Launcher.WriteToFile("CliV.ini", strLocalCurVer, "ASCII", false);
		//alert("SetVersion" + strLocalCurVer);
		ctrlVerInfo.innerHTML = strVerInfo;
	},

    //点击选择所要进入的服务器 此时该服务器信息存入LauncherMain的成员变量GlobalEnterGameInfo里
    "ClickServer": function (zi,si)
    {
        var server = LauncherMain.servers[zi].list[si];
		//var ips = Launcher.NameToIp(server.address.split("#"));
		var ips = server.address.split("#");
		//var test = "127.0.0.1:8701#127.0.0.2:8701".split("#");
		
		//alert(test);
		//alert(server.address);
		//alert(ips[0]);
		//alert(ips[1]);
		
		var ServerIP1 =		ips[0].split(":")[0];
        var ServerPort1 =	ips[0].split(":")[1];		
		var ServerIP2 =		ips[1].split(":")[0];
        var ServerPort2 =	ips[1].split(":")[1];
		
        var AreaID = 		server.id.split("_")[1];
        var GroupID =		server.id.split("_")[2];
		
       // LauncherMain.GlobalEnterGameInfo = " " + ServerIP + " " + ServerPort + " " + AreaID + " " + GroupID;

		LauncherMain.GlobalEnterGameInfo =AreaID + "," + GroupID + "," + ServerIP1 + "," + ServerPort1 + "," + ServerIP2 + "," + ServerPort2 + "," + server.showname;
		//alert(LauncherMain.GlobalEnterGameInfo);
		LauncherMain.GlobalEnterGameAreaID = AreaID;

//alert("ClickServer");
		var a = document.getElementById("selectedZoneName");
		if (a!=null)
			a.innerHTML = LauncherMain.servers[zi].list[si].showname;

		a = document.getElementById("curZoneName");

		if (a!=null)
			a.innerHTML = LauncherMain.servers[zi].list[si].showname;

		a = document.getElementById("curZoneVersion");
		if (a!=null)
			a.innerHTML = currentversion; 

		// 设置显示状态
		a = document.getElementById(LauncherMain.CurZone);
		if (a!=null)
			a.className = "";
			
		a = document.getElementById(server.id);
		if (a!=null)
			a.className = "selected";

		// 设置当前值
		LauncherMain.CurZone = server.id;
		LauncherMain.SetCookie("CurZone", server.id, 30);
		LauncherMain.SetCookie("lastZoneName", LauncherMain.servers[zi].list[si].showname, 30);

    }
};

// 外部将会调用的JS接口

function AddGame(gameName, gameid, ico)
{
    var game ={
		"game":gameName,
		"gameid":gameid,
		"ico":ico
	};	
    LauncherMain.InstalledGames.push(game);
	Launcher.AcrossFrameCallJsFunc("G_Set", "GameInstalled", gameid);
}

function SetCurrentGame(gameid)
{
    LauncherMain.CurGame.id = gameid;
}

function ClearGameList()
{
}

function SetProgress(gameid, progress, taskName)
{
    if (gameid != LauncherMain.CurGame.id) return; 
    if( progress == -1 )
		LauncherMain.SetInfo(0, taskName);
	else
		LauncherMain.SetProgress(0, progress); 
	if ( progress != 100 && progress != -1 )
	{
		DisableStart(gameid);
	}
}

function UpdateComplete(gameid, item)
{
 	EnableStart(gameid);
} 
 
//LauncherDlg会通过调用IE的JavaScript Excute接口来回调此接口
//回调时机：前置更新和分区更新，启动时，或者执行完一个补丁完毕时，会调用此接口更新本地版本号
//launcher 2.0.1以及以上版本支持的回调接口
function SetVersion(strCurLocalVer)
{
	LauncherMain.SetVersion();
}
 
function DisableStart(gameid)
{	
    LauncherMain.Startable = false;	
	LauncherMain.SetVersion();
    var a = document.getElementById("enter");
    if (!a) return;  
	//a.src = "image2";	
}

function EnableStart(gameid)
{
	LauncherMain.Startable = true; 
	if ( isDoZone )  Launcher.StartGame(LauncherMain.CurGame.id, LauncherMain.GlobalEnterGameInfo);

   // var a = document.getElementById("enter");	
   // if (!a) return;	
    //a.src = "image3";
}

function GetDocName()
{
	return "LauncherMain";	
}

function GetOriginCoordinate()
{
}

function ShowHideG_Set(flag)
{
	var elm=window.document.getElementById('g_set');
	if (elm==null)
	{
		return;
	}

	if (flag =='auto')
	{
		if (elm.style.display == 'block')
			elm.style.display = 'none';
		else
			elm.style.display = 'block';
	}else if (flag =='show')
		elm.style.display = 'block';
	else if (flag =='hide')
		elm.style.display = 'none';
	Launcher.UpdateWindow();
}
-->