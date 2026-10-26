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
			    if(LauncherMain.Startable == false) {
			        if (confirm("游戏正在更新中，确认强行关闭吗？")) 
			            Launcher.Close();
			    }
			    else {
			        Launcher.Close();
			    }			        
			};
        }
        // 开始
		var startGame = function ()
		{	
			if(LauncherMain.Startable == false)
				alert("正在更新");
			else if (LauncherMain.GlobalEnterGameInfo.length <2)
				alert("请选择游戏区服");
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
		//LauncherMain.ReGetServers(
		//			"http://cq.dorado.sdo.com/cq/servers_all.js"
		//			//"http://sa.autopatch.sdo.com/sa/Commonupdatenew/web/Scripts/servers.js"
		//			,"LauncherSkin\\js\\servers.js"
        //			,"utf8");
		LauncherMain.ReGetAllServers("LauncherSkin\\js\\servers.js", "utf8");
          
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
    "aServersAddress": [
        "https://cq.dorado.sdo.com/cq/",
		"http://cq.dorado.sdo.com/cq/",
        "http://back.dorado.sdo.com/cq/",
        "http://115.182.80.182/cq/",
        "http://180.96.39.10/cq/"
    ],
    "ServerAllName": "servers_all.js",
    "ServerEachName": "servers_{0}.js",
    "ReGetAllServers": function(saveToLocalFileName, codePage){
        var serversStr = "";
        for(var i = 0; i < LauncherMain.aServersAddress.length; i++) {            
            serversStr = Launcher.GetURL(LauncherMain.aServersAddress[i] + LauncherMain.ServerAllName, codePage);
            if (serversStr != "") break;
        }

        if (serversStr != "") {
            LauncherMain.LoadServersFromStr(serversStr);
					
            LauncherMain.RefreshZoneList();
            Launcher.WriteToFile(saveToLocalFileName, serversStr, codePage, false);
        }
    },

    //当前所要进入的游戏接入区组信息 即为启动游戏所必须的参数
    "GlobalEnterGameInfo": "",
	//当前所要进入区的ID
    "GlobalEnterGameAreaID": "",

    //服务器列表  直接读取本地的json2.js文件
    "servers": [],
	"LoadServersFromStr": function ( serverStr )
	{
	    if (serverStr.length < 5)
	        return;

	    var serversJson = eval("(" + serverStr + ")");
	    var version = serversJson.version;

	    if (version == 3) // json对像格式
	    {
	        LauncherMain.servers = serversJson.servers;	 		
	        return;
	    }
	},
 
    //json格式时
    // 向内操作，外部操作内部元素   构造游戏服务器区组列表
    "RefreshZoneList": function ()
    {
        //服务器列表Dom
        var areaElemDom = $('.t_leftCon ul');
        var groupElemDom = $('.t_rightCon ul');

        var lastZoneName = LauncherMain.GetCookie("lastZoneName");
        var CurZone = LauncherMain.GetCookie("CurZone");
        var CurGroup = LauncherMain.GetCookie("CurGroup");
        if (CurZone == null) CurZone = 1; 
        if (CurGroup == null) CurGroup = 1;

        var a = document.getElementById("lastZoneName");
        if (a!=null)
            a.innerHTML = lastZoneName;

        //清空Dom界面
        areaElemDom.empty();
        groupElemDom.empty();

        // 检查CurZone 有效性
        var zoneActived = false;
        for (var i = 0; i < LauncherMain.servers.length; i++)
        {
            if (LauncherMain.servers[i] == null){
                continue;
            }
            var area = LauncherMain.servers[i];
            if (CurZone == area.areaid) {
                zoneActived = true;
                break;
            }
        }
        if (!zoneActived) { CurZone = 1; CurGroup = 1; }
        
        // 刷新界面
        for (var i = 0; i < LauncherMain.servers.length; i++)
        {
            if (LauncherMain.servers[i] == null){
                continue;
            }
            var area = LauncherMain.servers[i];

            var html = "<li><a class=\"" + (area.areaid == CurZone ? "on5" : "") + "\" href=\"javascript:;\" data-areaid=\"" + area.areaid + "\"><span>" + area.linetype + "</span><i>" + area.areaname + "</i></a></li>";
            //添加服务器列表
            areaElemDom.append(html);

            if (area.areaid == CurZone && area.list.length > 0){
                for(var j = 0; j < area.list.length; j++){
                    var group = area.list[j];		
                    
                    groupElemDom.append(LauncherMain.CreateGroupDom(group));

                    if (group.groupid == CurGroup){
                        LauncherMain.ClickServer(group.areaid,group.groupid);
                        //if (group.useable == 0){
                        //    LauncherMain.GlobalEnterGameInfo = "";
                        //    $("#curZoneName").text("");
                        //}
                    }
                }
            }
        }
    },
    // 加载首次servers中组列表
    "GetGroupListByArea": function(areaid)
    {
        if (LauncherMain.servers.length <= 0)
            return [];
        for(var i = 0; i < LauncherMain.servers.length; i++){
            if (LauncherMain.servers[i].areaid == areaid)
                return LauncherMain.servers[i].list;
        }
        return [];
    },
    // 重新获取组列表信息
    "ReGetGroups": function(areaid)
    {
        //var url = "http://cq.dorado.sdo.com/cq/servers_" + areaid + ".js";
        //areaStr = Launcher.GetURL(url, "utf8");

        var areaStr = "";
        for(var i = 0; i < LauncherMain.aServersAddress.length; i++) {            
            areaStr = Launcher.GetURL(LauncherMain.aServersAddress[i] + LauncherMain.ServerEachName.replace("{0}", areaid), "utf8");
            if (areaStr != "") break;
        }
        
        if (areaStr == "")
            return [];		
        var areaJson = eval("(" + areaStr + ")");
        return areaJson.list;
    },
    // 刷新界面组列表
    "RefreshGroupList": function(areaid)
    {
        var groups = LauncherMain.ReGetGroups(areaid);
        if (groups.length <= 0) {
            groups = LauncherMain.GetGroupListByArea(areaid);
        }
        $('.t_rightCon ul').empty();
        for (var i = 0; i < groups.length; i++)
            $('.t_rightCon ul').append(LauncherMain.CreateGroupDom(groups[i]));
    },
    "GetGroupInfo": function(areaid, groupid)
    {
        var groups = LauncherMain.GetGroupListByArea(areaid);
        for(var i =0; i <groups.length;i++)
        {
            if (groups[i].groupid == groupid){
                return groups[i];
            }
        }
        return null;
    },
    // 生成组DOM元素
    "CreateGroupDom": function(group)
    {
        var CurGroup = LauncherMain.GetCookie("CurGroup");
        var CurZone = LauncherMain.GetCookie("CurZone");
        if (CurZone == null) CurZone = 1; 
        if (CurGroup == null) CurGroup = 1;

        var groupHtml = "<li>"

        groupHtml += "<a data-areaid=\"" + group.areaid + "\" data-groupid=\"" + group.groupid +  "\" class=\"" + ((CurZone == group.areaid && CurGroup == group.groupid) ? "on6" : "") + "\" onclick=\"LauncherMain.ClickServer(" + group.areaid + "," + group.groupid + ")\" href=\"javascript:;\">";
        /*
        if (group.useable == 1)
        {         
            groupHtml += "<a data-areaid=\"" + group.areaid + "\" data-groupid=\"" + group.groupid +  "\" class=\"" + ((CurZone == group.areaid && CurGroup == group.groupid) ? "on6" : "") + "\" onclick=\"LauncherMain.ClickServer(" + group.areaid + "," + group.groupid + ")\" href=\"javascript:;\">";
        }
        else
        { // 维护           
            groupHtml += "<a href=\"javascript:;\" class=\"useless\" onclick=\"alert('服务器维护中');\">";
        }
        */
        
        groupHtml += "<div class=\"servicePic\">";

        // 组标记
        if (group.tag == "1")
            groupHtml += "<img src=\"images/pic1.png\" />";
        else if (group.tag == "2")
            groupHtml += "<img src=\"images/pic2.png\" />";
        
        groupHtml += "</div>";
        groupHtml += "<span>" + group.groupname + "</span>";

        // 组状态
        if (group.useable == 1)
        {
            // 正常
            if (group.status == "0")
                groupHtml += "<em><b><img src=\"images/color_1.png\"/></b><i class=\"color_green\">正常</i></em>";
            else if (group.status == "1")
                groupHtml += "<em><b><img src=\"images/color_2.png\"/></b><i class=\"color_red\">火爆</i></em>";                
            else if (group.status == "3")
                groupHtml += "<em><b><img src=\"images/color_3.png\"/></b><i class=\"color_yellow\">预注册</i></em>";
            else if (group.status == "4")
                groupHtml += "<em><b><img src=\"images/color_2.png\"/></b><i class=\"color_red\">入驻已满</i></em>";
        } else {
            // 维护
            groupHtml += "<em><b><img src=\"images/color_4.png\"/></b><i class=\"color_gray\">维护中</i></em>";
        }        
                    
        groupHtml += "</a></li>";

        return groupHtml;
    },
    "ClickFixClient": function()
    {
        if(LauncherMain.Startable == false) {
            alert("游戏正在更新时，请勿点击“客户端修复”按钮，以免影响您的正常更新。");
            return;
        }
        if (Launcher.RunExe("FixClient.exe","",0) == 0)
            Launcher.Close();
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
	"ClickServer": function (areaid, groupid)
    {
        var server = LauncherMain.GetGroupInfo(areaid, groupid);
        //var server = LauncherMain.servers[zi].list[si];
        //var ips = Launcher.NameToIp(server.address.split("#"));
        var ips = server.address.split("#");
		
        var ServerIP1 =		ips[0].split(":")[0];
        var ServerPort1 =	ips[0].split(":")[1];		
        var ServerIP2 =		ips[1].split(":")[0];
        var ServerPort2 =	ips[1].split(":")[1];
		
        var AreaID = server.areaid;
        var GroupID = server.groupid;
		
        // LauncherMain.GlobalEnterGameInfo = " " + ServerIP + " " + ServerPort + " " + AreaID + " " + GroupID;

        LauncherMain.GlobalEnterGameInfo =AreaID + "," + GroupID + "," + ServerIP1 + "," + ServerPort1 + "," + ServerIP2 + "," + ServerPort2 + "," + server.groupname;
        LauncherMain.GlobalEnterGameAreaID = AreaID + "_" + GroupID;

        var a = document.getElementById("selectedZoneName");
        if (a!=null)
            a.innerHTML = server.groupname;
        //a.innerHTML = LauncherMain.servers[zi].list[si].showname;

        a = document.getElementById("curZoneName");
        if (a!=null)
            a.innerHTML = server.groupname;
        //a.innerHTML = LauncherMain.servers[zi].list[si].showname;

        //a = document.getElementById("curZoneVersion");
        //if (a!=null)
        //	a.innerHTML = currentversion; 

        // 设置当前值
        LauncherMain.CurZone = server.areaid;
        LauncherMain.SetCookie("CurZone", server.areaid, 30);
        LauncherMain.SetCookie("CurGroup", server.groupid, 30);
        LauncherMain.SetCookie("lastZoneName", server.groupname, 30);
		
        //LauncherMain.CurZone = server.id;
        //LauncherMain.SetCookie("CurZone", server.id, 30);
        //LauncherMain.SetCookie("lastZoneName", LauncherMain.servers[zi].list[si].showname, 30);

        //Launcher.StartUpdate( LauncherMain.GlobalEnterGameAreaID , "CQYHzone");
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