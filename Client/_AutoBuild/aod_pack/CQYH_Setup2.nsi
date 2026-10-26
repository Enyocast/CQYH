#脚本版本 1.0.3


#*******************以下可修改***********************# 

#license等页面的颜色定义，默认为蓝色(3E66AC)，根据需要自行修改。格式为：6个字节的16进制，RRGGBB
!define MUI_TEXT_BGCOLOR 3E66AC
 
#游戏的中文名
!define PRODUCT_CHS_NAME "传奇永恒"
!define PRODUCT_TEST_NAME "传奇永恒"

#游戏的英文简称（对应注册表键值）
!define PRODUCT_EN_NAME "CQYH"

#游戏的英文名（给人看的名字）
!define PRODUCT_ENGLISH_NAME "Lengend of Eternal"
!define SETUP_EXE_NAME "CQYH"

#游戏ID编号
!define PRODUCT_GAMEID "991002359"
#sjj 2010-10-12
!define PRODUCT_GAMEID_INT 991002359

#自行设定的倍数,可以为小数
!define PRODUCT_MP "1"

#游戏客户端启动程序名(相对于游戏安装目录)
!define PROGRAM_NAME "CQYH\Launcher.exe"
#!define PROGRAM_NAME "CQYH\Binaries\Win32\MMOGame-Win32-Shipping.exe"


#游戏客户端主程序名(相对于游戏安装目录：如：《热血传奇》：此处应为：data\mir2.exe)
!define PROGRAM_GAME_NAME "CQYH\Binaries\Win32\MMOGame-Win32-Shipping.exe"
!define PROGRAM_GAME_DIR "CQYH\Binaries\Win32\"

#客户端版本号
#!define PRODUCT_VERSION "0.0.0.1"

#对外版本号，安装时显示
!define PRODUCT_EXT_VERSION "OB"

#游戏主页
!define PRODUCT_WEB_SITE "http://cq.sdo.com"

#渠道来源
!define PRODUCT_APPCHANEL "01"

#sjj 2011-02-23 安装包是光盘版还是硬盘版 0-硬盘版 1-光盘版
#!define SETUP_FROM_CD 1

#sjj 2010-06-17
#改变协议的windows消息宏定义
!define EM_SETCHARFORMAT		0x444
!define SCF_ALL					0x0004
!define CFM_COLOR				0x40000000
!define GB2312_CHARSET          134


#=======================压缩方式设置==========================#
#                                                             #
#   不同的压缩方式会对CPU、内存等系统资源占用不同		      #
#	zlib方式占用CPU较少20%左右，但压缩率只有50%               #
#   bzip2、lzma压缩率都在40%以上，但CPU占用率高               #
#   lzma采用7zib算法，压缩慢解压快                            #
#   /SDLID参数：以固实的方式压缩，可以增加压缩率，            #
#				但会生成一个与原文件同样大的临时文件          #
#         根据游戏具体需要，修改本部分。                      #
#                                                             #
#=============================================================#
#压缩方式，取值为zlib,bzip2,lzma三种
!define PRODUCT_COMPRESS_TYPE "lzma"

#=======================带zip文件的安装包=======================#
#                                                             	#
#    去掉ZIP_FILENAME宏前的注释即可                           	#
#    当data.zip为分卷压缩时，要确保其它的分卷文件都被包含进来了	#
#                                                             	#
#===============================================================#
#Zip文件路径
#sjj 2010-10-12
!define ZIP_FILENAME	"CQYH.zip"
#!define ZIP_FILENAME	"CQYH.7z.001"
!define ZIP_PASSWORD ""
#sjj 2010-12-29 分卷数量
#!define ZIP_FILE_NUM    1
!include "aod_ver.nsh"
!include "nsProcess.nsh"

#分卷信息文件名
!define ZIP_VOLUMINFO_FILENAME "VolumInfo.ini"

#是否安装DOTNET插件
!define SETUP_DOTNET
#是否安装VCREDIST插件
!define SETUP_VCREDIST
#是否安装最新的DX驱动
!define SETUP_DIRECTX
#!define DX_VERSION "4.9.0.904"

#提交软硬件信息
!define DEVICE_INFO_SUBMIT
#####################################################################################

#sjj 2011-08-10 定义完成页面增加自定义checkbox
!define USER_DEFINE_CHECKBOX

#sjj 2011-01-21 起点中文快捷方式
#!define SETUP_QIDIAN_LINK
!ifdef SETUP_QIDIAN_LINK
	!define LINK_QD_ENFORCE
	!define LINK_QD_ICO	"qd_logo.ico"
	!define LINK_QD_NAME	"起点中文网"
	!define LINK_QD_SITE1	"http://www.qidian.com/newindex.aspx?db=102&appid="
	!define LINK_QD_SITE2	"&type=client&url=http://www.qidian.com/"
!endif


!define SETUP_SYSTEM_INFO # 2012-06-27 软硬件信息收集 
######################################################################################

#sjj 2010-12-29 自定义用户取消事件
!define MUI_CUSTOMFUNCTION_ABORT OnUserAbort

!ifdef MUI_TEXT_COLOR
  !undef MUI_TEXT_COLOR
!endif
!define MUI_TEXT_COLOR 000000

#*******************以上可修改***********************# 
#*******************以下严禁修改区域***********************# 
;此处代码严禁修改，如擅自变动经查实后将对纂改者进行问责

!define TEMPLATE_VERSION "1.0.3"

#客户端信息收集后台接口地址
!define PRODUCT_NVER n103
!define PRODUCT_WEB_VERSIONREPORT "http://uv.sdo.com/userinfo.asp?nver=${PRODUCT_NVER}"

#客户端版本检查
!define PRODUCT_WEB_CHECKMD5 "http://116.211.11.59/checkmd5.php"

#通行证注册页面
!define PRODUCT_WEB_REGISTER "http://register.sdo.com/sdo/reg/sdg/inputinfo.asp?from=${PRODUCT_GAMEID}"


#=======================卸载调查==============================#
#                                                             #
#   卸载调查公司统一采用弹出方式，弹出页面地址请与吴超确认    #
#         根据游戏具体需要，修改本部分。                      #
#                                                             #
#=============================================================#
;卸载调查弹出页面
!define PRODUCT_WEB_SURVEY_POP "http://uv.sdo.com/survey.asp?gameid=${PRODUCT_GAMEID}&ver=${PRODUCT_VERSION}"

;卸载弹出查看更多游戏页面
!define PRODUCT_VOTE_SITE "http://www.sdo.com"

#------------本脚本基于修改过的NSIS 2.11版，如果发现不能正确编译请使用公司修改版覆盖--------------------#
!define PRODUCT_PUBLISHER "SNDA"
!define PRODUCT_UNINST_KEY   "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_EN_NAME}"
!define PRODUCT_UNINST_ROOT_KEY  "HKLM"

#如果没有定义卸载文件名
!ifndef PRODUCT_UNINSTALL_LOG
	!define PRODUCT_UNINSTALL_LOG "uninst"
!endif


SetCompressor ${PRODUCT_COMPRESS_TYPE}
Name "《${PRODUCT_CHS_NAME}》${PRODUCT_EXT_VERSION}版"
OutFile "${SETUP_EXE_NAME}_Setup(${PRODUCT_VERSION}).exe"
CRCCHECK force
XPStyle on
SetDatablockOptimize on

RequestExecutionLevel admin

#*******************以上严禁修改区域***********************# 


!define MUI_SKIN "InstallWizard"

!include "WinVer.nsh" 

#-------新Skin的脚本文件Modern UI Experience\System.nsh已经修改过，增加了背景图片和版本信息文字。-------#
#-------背景图片变换的实现尚未研究出--------------------------------------------------------------------#
!include "MUIXP.nsh"
!include "nsDialogs.nsh"
!include "UsefulLib.nsh"

!include "x64.nsh"
!include "LogicLib.nsh"
!include "WinMessages.nsh"


!include "FontName.nsh"
!include "FontReg.nsh"
!include "FontRegAdv.nsh"

!macro InstallMyOTFFont FontFile MyFontName
  Push $0  
  Push $R0
  Push $R1
  Push $R2
  
  !define Index 'Line${__LINE__}'
  
; Get the Font's File name
  ${GetFileName} ${FontFile} $0
  !define FontFileName $0
  
  SetOutPath "$FONTS"
  #SetOutPath $FONT_DIR
  IfFileExists "$FONT_DIR\${FontFileName}" ${Index}
	#MessageBox MB_OK '${FontFile}'
    File '${FontFile}'

${Index}:
  ReadRegStr $R0 HKLM "SOFTWARE\Microsoft\Windows NT\CurrentVersion" "CurrentVersion"
  IfErrors "${Index}-9x" "${Index}-NT"

"${Index}-NT:"
  StrCpy $R1 "Software\Microsoft\Windows NT\CurrentVersion\Fonts"
  goto "${Index}-GO"

"${Index}-9x:"
  StrCpy $R1 "Software\Microsoft\Windows\CurrentVersion\Fonts"
  goto "${Index}-GO"

"${Index}-GO:"
  ClearErrors
  #!insertmacro FontName "$FONT_DIR\${FontFileName}"
  StrCpy $R2 "${MyFontName}"
  #pop $R2s
  #IfErrors 0 "${Index}-Add"
  #  MessageBox MB_OK "$R2"
  #  goto "${Index}-End"
    
#"${Index}-Add:"
#  StrCpy $R2 "$R2 (TrueType)"
#  ClearErrors
  ReadRegStr $R0 HKLM "$R1" "$R2"
  IfErrors 0 "${Index}-End"
    System::Call "GDI32::AddFontResourceA(t) i ('${FontFileName}') .s"
    WriteRegStr HKLM "$R1" "$R2" "${FontFileName}"
    goto "${Index}-End"

"${Index}-End:"

  !undef Index
  !undef FontFileName
  
  pop $R2
  pop $R1
  Pop $R0 
  Pop $0
!macroend


${VerCmp}

#[[INCLUDE_ADD_START]]#  //重要标志，请勿修改
#[[INCLUDE_ADD_COMMENT]]#
#[[INCLUDE_ADD_END]]#  //重要标志，请勿修改

#欢迎页面
!define MUI_WELCOMEFINISHPAGE_BITMAP_NOSTRETCH
!define MUI_ICON "Resources\setup.ico"
!define MUI_UNICON "Resources\uninstall.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "Resources\left.bmp"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "Resources\Header.bmp"
!define MUI_BOTTOMIMAGE
!define MUI_BOTTOMIMAGE_BITMAP "Resources\Bottom.bmp"
!define MUI_WELCOMEFINIMIDDLE_BITMAP "Resources\pt.bmp"
!insertmacro MUI_PAGE_WELCOME

#安装协议
!insertmacro MUI_PAGE_LICENSE "Resources\license.txt"

#安装路径选择
;!define MUI_PAGE_CUSTOMFUNCTION_PRE SDDirectoryPagePre
#离开此页面时检查安装路径长度是否过长
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE SDDirectoryPageLeave
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

#插入完成安装页面
#完成页面初始化，显示，完成函数
!ifdef USER_DEFINE_CHECKBOX
!define MUI_PAGE_CUSTOMFUNCTION_PRE   FinishPagePre
!define MUI_PAGE_CUSTOMFUNCTION_SHOW  FinishPageShow
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE FinishPageLeave
!endif

!define MUI_FINISHPAGE_TEXT "《${PRODUCT_CHS_NAME}》客户端 已经成功安装\n\n您可以使用盛大通行证直接登陆《${PRODUCT_CHS_NAME}》游戏了!"
!define MUI_FINISHPAGE_RUN ""
!define MUI_FINISHPAGE_RUN_TEXT "运行${PRODUCT_TEST_NAME}"
!define MUI_FINISHPAGE_SHOWREADME "${PRODUCT_WEB_SITE}"
!define MUI_FINISHPAGE_SHOWREADME_TEXT "打开官方主页"
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION SDOpenHomeUrl
!insertmacro MUI_PAGE_FINISH
;显示卸载调查选项
!define MUI_FINISHPAGE_RUN ""
!define MUI_FINISHPAGE_RUN_TEXT "参加卸载调查"
!define MUI_FINISHPAGE_RUN_FUNCTION un.OpenSurveyUrl

!define MUI_FINISHPAGE_SHOWREADME "${PRODUCT_VOTE_SITE}"
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION un.OpenVoteSite
!define MUI_FINISHPAGE_SHOWREADME_TEXT "查看盛大更多游戏"
#!define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED
!define SC_CLOSE 0xF060

#---------------------------
!insertmacro MUI_UNPAGE_INSTFILES
!define MUI_PAGE_CUSTOMFUNCTION_SHOW  un.FinishPageShow
!insertmacro MUI_UNPAGE_FINISH
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

ReserveFile "${NSISDIR}\Plugins\advsplash.dll"
ReserveFile "${NSISDIR}\Plugins\UserInfo.dll"
ReserveFile "${NSISDIR}\Plugins\Installoptions.dll"
ReserveFile "${NSISDIR}\Plugins\ZipSetup.dll"
ReserveFile "${NSISDIR}\Plugins\ZipSubVolumCheck.dll"
ReserveFile "${NSISDIR}\Plugins\7za.dll"
ReserveFile "${NSISDIR}\Plugins\DataCollection.dll"
ReserveFile "${NSISDIR}\Plugins\VersionCheck.dll"
ReserveFile "${NSISDIR}\Plugins\SystemInfoKeys.xml"
ReserveFile "${NSISDIR}\Plugins\Serverlist.ini"
ReserveFile "Resources\left.bmp"
ReserveFile "Resources\splash.png"



!macro CHECKDELETE FULLFILENAME
	${If} ${FileExists} ${FULLFILENAME}
	    Delete ${FULLFILENAME}
	${EndIf}
!macroend
#[[RESERVEFILE_ADD_START]]#  //重要标志，请勿修改
#[[RESERVEFILE_ADD_COMMENT]]#
#[[RESERVEFILE_ADD_END]]#  //重要标志，请勿修改

#--------使用新的SKIN导致BrandingText被覆盖，有谁能让它显示出来？-------#
BrandingText " 《${PRODUCT_CHS_NAME}》 盛大互动娱乐"

VIProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey  "FileVersion" "${PRODUCT_VERSION}"
VIAddVersionKey  "FileDescription" "《${PRODUCT_CHS_NAME}》客户端安装包"
VIAddVersionKey  "LegalCopyright" "盛大网络发展有限公司"
VIAddVersionKey  "ProductName" "《${PRODUCT_CHS_NAME}》"
VIAddVersionKey  "CompanyName" "盛大网络发展有限公司"

Var  Suffix
Var  SysLCID
Var  ResDotNet
Var  ResVC
Var  Delete7zFlag
Var  DeleteVolumeFlag
!define VCREDIST_REG_KEY "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{837b34e3-7c30-493c-8f6a-2b0f04e2912c}"

#*******************以下严禁修改区域*********************************************************************#
#数据格式版本号
!define DVersion "1.5"
!define DataForSubmit ',"DVersion":"${DVersion}","GameID":"${PRODUCT_GAMEID}","GVersion":"${PRODUCT_VERSION}","AppVersion":"${TEMPLATE_VERSION}"'
!define DataSubmitFlag 7
!define ERR_START_INST      	"12010000"
!define ERR_QUIT_INST       	"12020000"
!define ERR_FINISH_INST     	"12030000"
!define ERR_START_UNINST    	"12040000"
!define ERR_QUIT_UNINST     	"12050000"
!define ERR_FINISH_UNINST     	"12060000"
!define ERR_DATA_PACK 			"12990103"
!define ERR_PLUGINS_INST 		"12500101"
!define ERR_DELETE_FILE     	"12990201"
!define ERR_DISK_OVERFLOW   	"12990102"
#*******************以上严禁修改区域**********************************************************************#

#该区段必须是第一个区段，用于设置安装路径(在用户选择的安装路径后面加上游戏目录)
/*
Section -MakeSureInstDir
    ;MessageBox MB_OK "INSTDIR in makesureinstdir is ---- $INSTDIR "
	Push $INSTDIR
	Call SDGetParent
	Pop $0
	${If} $SysLCID == 1
		StrCpy $Suffix ${PRODUCT_CHS_NAME}
	${Else}
		StrCpy $Suffix ${PRODUCT_EN_NAME}
	${EndIf}
	${If} $INSTDIR != "$0\$Suffix"
		StrCpy $INSTDIR "$INSTDIR\$Suffix"
		SetOutPath "$INSTDIR"
	${EndIf}
	
	MessageBox MB_OK "$INSTDIR"
SectionEnd
*/

Section "CQYHFonts"
  ;MessageBox MB_OK "$INSTDIR"
  
  #File "msyh.ttf"
  #File "SourceHanSansCN-Medium.otf"

  
  SetOverwrite ifnewer
  SetOutPath "$FONTS"
  #File "*.*"
  #StrCpy $FONT_DIR $FONTS
  #!insertmacro FontNameVer
  #!insertmacro InstallTTFFont "AgeOfDawn.ttf"
  #!insertmacro InstallTTF "方正兰亭中黑_GBK.ttf"
  #!insertmacro InstallTTF "方正兰亭准黑_GBK.ttf"
  #!insertmacro InstallTTFFont "方正粗圆_GBK.ttf"
  #!insertmacro InstallTTFFont "方正隶二_GBK.ttf"
  #!insertmacro InstallTTFFont "方正隶变_GBK.ttf"
  #!insertmacro InstallTTFFont "方正魏碑_GBK.ttf"
  #!insertmacro InstallTTF "msyh.ttf"
  #!insertmacro InstallTTF "SourceHanSansCN-Medium.otf"
  
  !insertmacro InstallMyOTFFont "AgeOfDawn.ttf" "AgeOfDawn (TrueType)"
  #!insertmacro InstallTTF "方正兰亭中黑_GBK.ttf"
  #!insertmacro InstallTTF "方正兰亭准黑_GBK.ttf"
  !insertmacro InstallMyOTFFont "方正粗圆_GBK.ttf" "方正粗圆_GBK (TrueType)"
  !insertmacro InstallMyOTFFont "方正隶二_GBK.ttf" "方正隶二_GBK (TrueType)"
  !insertmacro InstallMyOTFFont "方正隶变_GBK.ttf" "方正隶变_GBK (TrueType)"
  !insertmacro InstallMyOTFFont "方正魏碑_GBK.ttf" "方正魏碑_GBK (TrueType)"
  
  #!insertmacro FontNameVer
  #!insertmacro FontName "msyh.ttf"
  #!insertmacro InstallTTFFont "msyh.ttf"
  #!insertmacro InstallMyOTFFont "msyh.ttf" "Microsoft YaHei (TrueType)"
  
  #!insertmacro FontName "SourceHanSansCN-Medium.otf"
  #!insertmacro InstallOTFFont "SourceHanSansCN-Medium.otf"
  !insertmacro InstallMyOTFFont "SourceHanSansCN-Medium.otf" "Source Han Sans CN Medium (TrueType)"
  
  #!insertmacro InstallFONFont "msyh.ttf" ${FontName}
  #!insertmacro InstallFONFont "SourceHanSansCN-Medium.otf"  ${FontName}
  
SectionEnd

Section -Post
#*******************以下严禁修改区域***********************# 
	WriteUninstaller "$INSTDIR\${PRODUCT_UNINSTALL_LOG}.exe"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "${PRODUCT_CHS_NAME}"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\${PRODUCT_UNINSTALL_LOG}.exe"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\${PRODUCT_UNINSTALL_LOG}.exe"
#*******************以上严禁修改区域***********************# 
SectionEnd

Section "MainSection" SEC01
	SetOutPath $INSTDIR
	SetOverwrite on
	;MessageBox MB_OK "$INSTDIR"

	!ifdef SETUP_VCREDIST
		#vcredist_x86_vs2010.exe
		#File "/oname=$TEMP\vcredist_x86_vs2010.exe" "components\vcredist_x86_vs2010.exe"
		File "components\vcredist_x86_vs2010.exe"
		ExecWait '"$INSTDIR\vcredist_x86_vs2010.exe" /q'
		#Delete   '"$TEMP\vcredist_x86_vs2010.exe"'
		#StrCpy $0 0
		#Call CheckVCInstalled
		#Pop $0
		#${If} $0 == -1
		#	StrCpy $ResVC -1
		#${EndIf}

	!endif

	!ifdef SETUP_DOTNET
		#.Net Framework
		#push 0
		#pop $0
		#ReadRegDWORD $0 HKLM "SOFTWARE\Microsoft\NET Framework Setup\NDP\v2.0.50727" Install
		#IntCmp $0 1 +4 0 0
			File "components\dotNetFx40_Full_x86_x64.exe"
			ExecWait '"$INSTDIR\dotNetFx40_Full_x86_x64.exe" /norestart'
			#Delete   '"$INSTDIR\dotNetFx40_Full_x86_x64.exe"'
		#StrCpy $0 0
		;ReadRegDWORD $0 HKLM "SOFTWARE\Microsoft\NET Framework Setup\NDP\v2.0.50727" Install
		;${If} $0 != 1
		;	StrCpy $ResDotNet -1
		;${EndIf}
	!endif

	${If} ${RunningX64}
	#MessageBox MB_OK "64Bit OS"
	${Else}
		${If} ${IsWin7}
			ExecWait "$INSTDIR\Enb3GMem.bat"
		${ElseIf} ${IsWinVista}
			ExecWait "$INSTDIR\Enb3GMem.bat"
		${EndIf}
	${EndIf}
	
	!ifdef SETUP_DIRECTX
		File /r "components\dx9"
		ExecWait '"$INSTDIR\dx9\DXSETUP.exe" /silent'
		
	!endif
	
	
	#sjj 2011-01-21 释放起点图标文件
	!ifdef SETUP_QIDIAN_LINK
		File "/oname=$TEMP\${LINK_QD_ICO}" "components\${LINK_QD_ICO}"
	!endif

	;解压zip/7z包
	!ifdef ZIP_FILENAME
        #sjj 2010-10-12
        ZipSetup::ExtractAll "$EXEDIR\${ZIP_FILENAME}" "$INSTDIR" "${ZIP_PASSWORD}"
        #ZipSetup::ExtractAllBy7z "$EXEDIR\${ZIP_FILENAME}" "$INSTDIR" "${ZIP_PASSWORD}"
		
		Pop $R0
		Pop $R1
		${If} $R0 == -1
				StrCpy $R1 "分卷资源包损坏，请前往官网${PRODUCT_WEB_SITE}重新下载!$EXEDIR\${ZIP_FILENAME}"
				MessageBox MB_OK|MB_ICONEXCLAMATION $R1 /SD IDOK
				ClearErrors
				!insertmacro CHECKDELETE "$EXEDIR\7za.dll"
				IfErrors 0 _delete_7z_no_error
					#7za删除失败,此处要退出，故先上报
				    StrCpy $Delete7zFlag -1
				    Push ${ERR_DELETE_FILE}
        			StrCpy $R0 '${DataForSubmit},"AppChanel":"${PRODUCT_APPCHANEL}","ErrorMsg":"7z"'
					Push $R0
					Call SubmitErrData
			_delete_7z_no_error:
				#安装包错误上报
			    Push ${ERR_DATA_PACK}
			    StrCpy $R0 '${DataForSubmit},"AppChanel":"${PRODUCT_APPCHANEL}","ErrorMsg":"DATA_BROKEN"'
			    Push $R0
				Call SubmitErrData
				Quit
		
		${EndIf}
		ClearErrors
		!insertmacro CHECKDELETE "$EXEDIR\7za.dll"
		IfErrors 0 _delete_7z_no_error_2
			#7za删除失败上报
			StrCpy $Delete7zFlag -1
		_delete_7z_no_error_2:
		
	!endif

	;在这里添加客户端文件
	File /r "Client\*"
	;File /r "d:\_pack_dir\bin\*"

!ifdef ZIP_VOLUMINFO_FILENAME
	ClearErrors
    !insertmacro CHECKDELETE "${ZIP_VOLUMINFO_FILENAME}"
    IfErrors 0 _delete_voluminfoFile_no_error
			#volumeinfo删除失败上报
			StrCpy $DeleteVolumeFlag -1
	_delete_voluminfoFile_no_error:
	;Delete ${ZIP_VOLUMINFO_FILENAME} #删除多余的${ZIP_VOLUMINFO_FILENAME}，有个bug，当Client目录下没有文件的时候不能使用File /r，故不能使用/x的方式排出${ZIP_VOLUMINFO_FILENAME}
!endif
	Call InstSuccess
	
SectionEnd

Section -AdditionalIcons
	SetOutPath "$INSTDIR"
	;MessageBox MB_OK "$INSTDIR"
	${IsWinNT} $R0
	${If} $R0 == 0
		#Delete "$WINDIR\All Users\Desktop\${PRODUCT_CHS_NAME}.lnk"
		Delete "$WINDIR\All Users\Desktop\${PRODUCT_TEST_NAME}.lnk"
		
		SetOutPath "$INSTDIR\CQYH"
		#CreateShortCut "$WINDIR\All Users\Desktop\${PRODUCT_CHS_NAME}.lnk" "$INSTDIR\${PROGRAM_NAME}" "" "$INSTDIR\${PROGRAM_NAME}" 0
		
		
		#CreateShortCut "$WINDIR\All Users\Desktop\${PRODUCT_TEST_NAME}.lnk" "$INSTDIR\${PROGRAM_GAME_NAME}" "-seekfreeloading -FINAL_RELEASE -nohomedir" "$INSTDIR\${PROGRAM_GAME_NAME}" 0
		CreateShortCut "$WINDIR\All Users\Desktop\${PRODUCT_TEST_NAME}.lnk" "$INSTDIR\CQYH\Launcher.exe" "" "$INSTDIR\CQYH\LauncherModules\Game.ico"
		
		goto Continue
	${EndIf}
	SetShellVarContext all
	#Delete "$DESKTOP\${PRODUCT_CHS_NAME}.lnk"
	Delete "$DESKTOP\${PRODUCT_TEST_NAME}.lnk"
	${If} ${RunningX64}
	#MessageBox MB_OK "64Bit OS"
	${Else}
		${If} ${IsWin7}
			#MessageBox MB_OK "Win7 32"
			Delete "$DESKTOP\开启3G内存扩展模式.lnk"
			Delete "$DESKTOP\关闭3G内存扩展模式.lnk"		
		${ElseIf} ${IsWinVista}
			#MessageBox MB_OK "Vista 32"
			Delete "$DESKTOP\开启3G内存扩展模式.lnk"
			Delete "$DESKTOP\关闭3G内存扩展模式.lnk"		
		${EndIf}
	${EndIf}
	
	SetOutPath "$INSTDIR\CQYH"
	#CreateShortCut "$DESKTOP\${PRODUCT_CHS_NAME}.lnk" "$INSTDIR\${PROGRAM_NAME}" "" "$INSTDIR\CQYH\${PROGRAM_NAME}" 0
	
	
	#CreateShortCut "$DESKTOP\${PRODUCT_TEST_NAME}.lnk" "$INSTDIR\${PROGRAM_GAME_NAME}" "-seekfreeloading -FINAL_RELEASE -nohomedir" "$INSTDIR\${PROGRAM_GAME_NAME}" 0
	CreateShortCut "$DESKTOP\${PRODUCT_TEST_NAME}.lnk" "$INSTDIR\CQYH\Launcher.exe" "" "$INSTDIR\CQYH\LauncherModules\Game.ico"
	
	${If} ${RunningX64}
	#MessageBox MB_OK "64Bit OS"
	${Else}
		${If} ${IsWin7}
			#MessageBox MB_OK "Win7 32"
			CreateShortCut "$DESKTOP\开启3G内存扩展模式.lnk" "$INSTDIR\Enb3GMem.bat" "" "$INSTDIR\CQYH\LauncherModules\Game.ico"
			CreateShortCut "$DESKTOP\关闭3G内存扩展模式.lnk" "$INSTDIR\Dis3GMem.bat" "" "$INSTDIR\CQYH\LauncherModules\Game.ico"
		${ElseIf} ${IsWinVista}
			#MessageBox MB_OK "Vista 32"
			CreateShortCut "$DESKTOP\开启3G内存扩展模式.lnk" "$INSTDIR\Enb3GMem.bat" "" "$INSTDIR\CQYH\LauncherModules\Game.ico"
			CreateShortCut "$DESKTOP\关闭3G内存扩展模式.lnk" "$INSTDIR\Dis3GMem.bat" "" "$INSTDIR\CQYH\LauncherModules\Game.ico"
		${EndIf}
	${EndIf}
	
Continue:
	#Delete "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}.lnk"
	#Delete "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}.lnk"
	Delete "$SMPROGRAMS\盛大网络\${PRODUCT_TEST_NAME}.lnk"
	${If} ${RunningX64}
	#MessageBox MB_OK "64Bit OS"
	${Else}
		${If} ${IsWin7}
			#MessageBox MB_OK "Win7 32"
			Delete "$SMPROGRAMS\盛大网络\开启3G内存扩展模式.lnk"
			Delete "$SMPROGRAMS\盛大网络\关闭3G内存扩展模式.lnk"		
		${ElseIf} ${IsWinVista}
			#MessageBox MB_OK "Vista 32"
			Delete "$SMPROGRAMS\盛大网络\开启3G内存扩展模式.lnk"
			Delete "$SMPROGRAMS\盛大网络\关闭3G内存扩展模式.lnk"		
		${EndIf}
	${EndIf}
	
	SetOutPath "$INSTDIR"
	RMDir /r "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}"
	CreateDirectory "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}"
	
	SetOutPath "$INSTDIR\CQYH"
	CreateShortCut "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}\${PRODUCT_CHS_NAME}.lnk" "$INSTDIR\CQYH\Launcher.exe" "" "$INSTDIR\CQYH\LauncherModules\Game.ico"
	
	#SetOutPath "$INSTDIR\CQYH\Binaries\Win32"
	#CreateShortCut "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}\${PRODUCT_TEST_NAME}.lnk" "$INSTDIR\${PROGRAM_GAME_NAME}" "-seekfreeloading -FINAL_RELEASE -nohomedir" "$INSTDIR\${PROGRAM_GAME_NAME}" 0
	
	${If} ${RunningX64}
	#MessageBox MB_OK "64Bit OS"
	${Else}
		${If} ${IsWin7}
			#MessageBox MB_OK "Win7 32"
			MessageBox MB_OK "检测到您的安装的是32位系统，请在游戏安装完成后，用管理员模式运行游戏安装菜单中或桌面的【开启3G内存扩展模式】菜单项，再重新启动，以保证游戏正常运行。建议您升级到64位系统。"
			CreateShortCut "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}\开启3G内存扩展模式.lnk" "$INSTDIR\Enb3GMem.bat" "" "$INSTDIR\CQYH\LauncherModules\Game.ico"
			CreateShortCut "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}\关闭3G内存扩展模式.lnk" "$INSTDIR\Dis3GMem.bat" "" "$INSTDIR\CQYH\LauncherModules\Game.ico"
		${ElseIf} ${IsWinVista}
			#MessageBox MB_OK "Vista 32"
			MessageBox MB_OK "检测到您的安装的是32位系统，请在游戏安装完成后，用管理员模式运行游戏安装菜单中或桌面的【开启3G内存扩展模式】菜单项，再重新启动，以保证游戏正常运行。建议您升级到64位系统。"
			CreateShortCut "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}\开启3G内存扩展模式.lnk" "$INSTDIR\Enb3GMem.bat" "" "$INSTDIR\CQYH\LauncherModules\Game.ico"
			CreateShortCut "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}\关闭3G内存扩展模式.lnk" "$INSTDIR\Dis3GMem.bat" "" "$INSTDIR\CQYH\LauncherModules\Game.ico"
		${EndIf}
	${EndIf}
	
	SetOutPath "$SMPROGRAMS"
	CreateShortCut "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}\卸载${PRODUCT_CHS_NAME}.lnk" "$INSTDIR\${PRODUCT_UNINSTALL_LOG}.exe" "" "$INSTDIR\${PRODUCT_UNINSTALL_LOG}.exe" 0
	${RefreshIcon}
	SetOutPath "$INSTDIR"
SectionEnd


Section Uninstall
	Push "${PROGRAM_NAME}"
	
	;KillProcDLL::KillProc "LauncherUpdateService.dat"
	${nsProcess::KillProcess} "LauncherUpdateService.dat" $R0
	${nsProcess::KillProcess} "Launcher.dat" $R0
	;MessageBox MB_OK $R0
	
	;删除桌面快捷方式
	#Delete "$WINDIR\All Users\Desktop\${PRODUCT_CHS_NAME}.lnk"
	Delete "$WINDIR\All Users\Desktop\${PRODUCT_TEST_NAME}.lnk"

	SetShellVarContext all

	;删除桌面快捷方式
	#Delete "$DESKTOP\${PRODUCT_CHS_NAME}.lnk"
	Delete "$DESKTOP\${PRODUCT_TEST_NAME}.lnk"
	;删除开始菜单目录
	RMDir /r "$SMPROGRAMS\盛大网络\${PRODUCT_CHS_NAME}"


	;删除安装目录下的全部文件
	RMDir /r  "$INSTDIR\CQYH"
	RMDir /r  "$INSTDIR\Dx9"
	Delete "$INSTDIR\Dis3GMem.bat"
	Delete "$INSTDIR\dotNetFx40_Full_x86_x64.exe"
	Delete "$INSTDIR\Enb3GMem.bat"
	Delete "$INSTDIR\vcredist_x86_vs2010.exe"	

	DeleteRegKey HKLM "Software\snda\${PRODUCT_EN_NAME}"
	DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
	SetAutoClose true
	
SectionEnd

#*******************函数定义开始***********************#

Function .onInit

	InitPluginsDir
	File "/oname=$PLUGINSDIR\Header.bmp" "Resources\Header.bmp"  
	File "/oname=$PLUGINSDIR\pt.bmp" "Resources\pt.bmp"
	File "/oname=$PLUGINSDIR\left.bmp" "Resources\left.bmp"
	File "/oname=$PLUGINSDIR\splash.png" "Resources\splash.png"
	File "/oname=$PLUGINSDIR\advsplash.dll" "${NSISDIR}\Plugins\advsplash.dll"
	File "/oname=$PLUGINSDIR\ZipSetup.dll" "${NSISDIR}\Plugins\ZipSetup.dll"
	File "/oname=$PLUGINSDIR\DataCollection.dll" "${NSISDIR}\Plugins\DataCollection.dll"
	File "/oname=$PLUGINSDIR\SystemInfoKeys.xml" "${NSISDIR}\Plugins\SystemInfoKeys.xml"
	File "/oname=$PLUGINSDIR\Serverlist.ini" "${NSISDIR}\Plugins\Serverlist.ini"
	File "/oname=$PLUGINSDIR\UserInfo.dll" "${NSISDIR}\Plugins\UserInfo.dll"
	File "/oname=$PLUGINSDIR\VersionCheck.dll" "${NSISDIR}\Plugins\VersionCheck.dll"
    Push 0
    Pop $ResDotNet
    Push 0
    Pop $ResVC
!ifdef ZIP_FILENAME
	File "/oname=$PLUGINSDIR\ZipSubPackSizeCheck.dll" "${NSISDIR}\Plugins\ZipSubPackSizeCheck.dll"
	File "/oname=$PLUGINSDIR\${ZIP_VOLUMINFO_FILENAME}" "Client\${ZIP_VOLUMINFO_FILENAME}"
	!ifndef SETUP_FROM_CD
		File "/oname=$EXEDIR\7za.dll" "${NSISDIR}\Plugins\7za.dll"
		${If} ${FileExists} "$EXEDIR\7za.dll"
		      SetFileAttributes "$EXEDIR\7za.dll" FILE_ATTRIBUTE_HIDDEN
		${EndIf}
	!endif
!endif

	#*******************以下严禁修改区域***********************# 
	Push "VER"         ; push the search string onto the stack
	Push "F"   ; push a default value onto the stack
	Call GetParameterValue
	Pop $2
	StrCmp $2 "T" 0 CHECK_VER_END
	SetOutPath $PLUGINSDIR
	StrCpy $0 ${PRODUCT_WEB_CHECKMD5}
	StrCpy $1 ${PRODUCT_GAMEID}
	StrCpy $2 ${PRODUCT_NVER}
	StrCpy $3 $PLUGINSDIR
	System::Call 'VersionCheck::CheckSrcCodeVersionA(tr0,tr1,tr2,tr3,t.R1,t"")t.R2'
	MessageBox MB_OK|MB_ICONEXCLAMATION "$R1" /SD IDOK
	QUIT
CHECK_VER_END:
#*******************以上严禁修改区域***********************# 
	
	;开始安装要提前释放的资源文件
	Call SDInitREC

	;advsplash::show 1000 600 400 -1 "$PLUGINSDIR\splash"
	advsplash::show 2000 1400 1000 0x1856B1 $PLUGINSDIR\splash
	;Pop $0
	System::Call 'Kernel32::CreateMutexA(i 0,i 0,t "${PRODUCT_EN_NAME}.install") i .r1 ?e'
	Pop $0
	strCmp $0 0 +3
		MessageBox MB_OK|MB_ICONEXCLAMATION "《${PRODUCT_CHS_NAME}》客户端 安装向导已经在运行" /SD IDOK
		Quit
	Push ${PROGRAM_NAME}
	Call SDCheck
	ReadRegDWORD $R0 HKLM "SYSTEM\ControlSet001\Control\Nls\Language" Default
	${If} $R0 == "0804"
		StrCpy $SysLCID 1 ;系统为中文版
		StrCpy $INSTDIR "$PROGRAMFILES\盛大网络\${PRODUCT_CHS_NAME}"
	${Else}
	    StrCpy $SysLCID 0 ;系统为非中文版
	    StrCpy $INSTDIR "$PROGRAMFILES\SNDA\${PRODUCT_EN_NAME}"
	${EndIf}
	
	;KillProcDLL::KillProc "LauncherUpdateService.dat"
	${nsProcess::KillProcess} "LauncherUpdateService.dat" $R0
	${nsProcess::KillProcess} "Launcher.dat" $R0
	;MessageBox MB_OK $R0
	;取zip/7z包的大小
	!ifdef ZIP_FILENAME
		
	#************************************************************************************************************#
	    #判断分卷是否齐全
	    SetOutPath $PLUGINSDIR
	    System::Call 'ZipSubPackSizeCheck::ZipSubPackSizeCheckA(t "${ZIP_FILENAME}",i ${ZIP_FILE_NUM}, t "$PLUGINSDIR", t "${PRODUCT_WEB_SITE}",t .r0)i.r1'
		#分卷不全
		${If} $0 != "" 
		${OrIf} $1 != 1
			MessageBox MB_OK $0
			Push ${ERR_DATA_PACK}
			StrCpy $R0 '${DataForSubmit},"AppChanel":"${PRODUCT_APPCHANEL}","ErrMsg":"$0"'
			Push $R0
			Call SubmitErrData
			Quit
		${EndIf}
       #************************************************************************************************************#	
		;获取zip/7z包大小
        #sjj 2010-10-12
        #ZipSetup::GetZipDataSize "$EXEDIR\${ZIP_FILENAME}" "${ZIP_PASSWORD}"
        ZipSetup::Get7zDataSize "$EXEDIR\${ZIP_FILENAME}" "${ZIP_PASSWORD}"

		Pop $R1
		System::Int64Op $R1 / 1024
		Pop $R1

		SectionGetSize ${SEC01} $R0
		IntOp $R0 $R0 + $R1
		;安装大小 占用空间
		SectionSetSize ${SEC01} 7121568
	!endif
	Push ${ERR_START_INST}
	StrCpy $R0 '${DataForSubmit},"AppChanel":"${PRODUCT_APPCHANEL}"'
	Push $R0
	Call SubmitErrData

FunctionEnd

Function .onInstSuccess
	HideWindow
	#安装完成上报
	Push ${ERR_FINISH_INST}
	StrCpy $R0 '${DataForSubmit},"AppChanel":"${PRODUCT_APPCHANEL}"'
	Push $R0
	Call SubmitErrData
FunctionEnd

Function InstSuccess
#*******************以下严禁修改区域***********************#
	WriteRegStr HKLM "Software\snda\${PRODUCT_EN_NAME}" "Path" "$INSTDIR"
	WriteRegStr HKLM "Software\snda\${PRODUCT_EN_NAME}" "version" "${PRODUCT_VERSION}"
	WriteRegStr HKLM "Software\snda\${PRODUCT_EN_NAME}" "Loader" "$INSTDIR\${PROGRAM_NAME}"
	WriteRegStr HKLM "Software\snda\${PRODUCT_EN_NAME}" "MainProg" "$INSTDIR\${PROGRAM_GAME_NAME}"
#*******************以上严禁修改区域***********************#
	#提交软硬件信息
	!ifdef DEVICE_INFO_SUBMIT
	    Push 0
		StrCpy $R0 ',"Game_ID":${PRODUCT_GAMEID},"Game_Version":"${PRODUCT_VERSION}"'
		Push $R0
		Call SubmitErrData
	!endif
FunctionEnd

Function SubmitErrData
    SetOutPath $PLUGINSDIR
    Exch $1 ;submit data
    Exch
    Exch $0 ;errCode
	System::Call 'DataCollection::WriteAndSubmitDataForNSISA(t r0,t r1 ,i ${DataSubmitFlag})i.r3 '
    ;MessageBox MB_OK $3
FunctionEnd

Function FindLargestDisk
	System::Call 'kernel32::GetLogicalDrives()i.r0'
	StrCpy $1 $windir 3
	StrCpy $2 0
	StrCpy $4 65
	loop:
	    IntOp $3 $0 & 1
	     ${If} $3 <> 0
	        IntFmt $3 "%c:" $4
	        System::Call 'kernel32::GetDiskFreeSpaceEx(tr3,*l.r5,*l,*l)i'
	        ${If} $5 L> $2
	            StrCpy $2 $5
	            ;Push $3
	            StrCpy $1 $3
	        ${EndIf}
	    ${EndIf}
	    IntOp $4 $4 + 1
	    IntOp $0 $0 >> 1
	    StrCmp $0 0 "" loop
	  	System::Int64Op $2 / 1024
	Push $2
	Push $1
FunctionEnd

#打开官方主页
Function SDOpenHomeUrl
	EXEC '"$PROGRAMFILES\Internet Explorer\IExplore.exe" ${PRODUCT_WEB_SITE}'
FunctionEnd

Function SDCheck
	ClearErrors
	UserInfo::GetName
	IfErrors 0 +2
		goto done
	Pop $0
	UserInfo::GetAccountType
	Pop $1
	StrCmp $1 "Admin" +3 0
	MessageBox MB_OK '用户 "$0" 没有本机管理员权限 $\r$\n\
	《${PRODUCT_CHS_NAME}》 安装向导退出' /SD IDOK
	Quit
done:
FunctionEnd

;开始安装前要提前释放的资源文件
Function SDInitREC
#[[SDINITREC_ADD_START]]#  //重要标志，请勿修改
#[[SDINITREC_ADD_COMMENT]]#
#[[SDINITREC_ADD_END]]#  //重要标志，请勿修改
FunctionEnd




#自定义的函数
#[[FUNCTION_ADD_START]]#  //重要标志，请勿修改
#[[FUNCTION_ADD_COMMENT]]#
#[[FUNCTION_ADD_END]]#  //重要标志，请勿修改

Function un.onUninstSuccess
	HideWindow
	#卸载完成上报
	Push ${ERR_FINISH_UNINST}
	Push ${DataForSubmit}
	Call un.SubmitErrData

FunctionEnd

Function un.onInit
    System::Call 'Kernel32::CreateMutexA(i 0,i 0,t "${PRODUCT_EN_NAME}.uninstall") i .r1 ?e'
	Pop $0
	${If} $0 != 0
		MessageBox MB_OK|MB_ICONEXCLAMATION "《${PRODUCT_CHS_NAME}》客户端 卸载向导已经在运行!此操作无法完成!" /SD IDOK
		Quit
	${EndIf}
	File "/oname=$PLUGINSDIR\DataCollection.dll" "${NSISDIR}\Plugins\DataCollection.dll"
	File "/oname=$PLUGINSDIR\SystemInfoKeys.xml" "${NSISDIR}\Plugins\SystemInfoKeys.xml"
	File "/oname=$PLUGINSDIR\Serverlist.ini" "${NSISDIR}\Plugins\Serverlist.ini"
	#开始卸载上报
	Push ${ERR_START_UNINST}
	Push ${DataForSubmit}
	Call un.SubmitErrData
	MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您确认想要完全删除《${PRODUCT_CHS_NAME}》及它的所有组件吗？" IDYES __Start_Uninstall__
    #取消卸载
	Push ${ERR_QUIT_UNINST}
	Push ${DataForSubmit}
	Call un.SubmitErrData
	Abort
__Start_Uninstall__:
FunctionEnd




#打开卸载调查页面
Function un.OpenSurveyUrl
	SetOutPath $PLUGINSDIR
	System::Call 'DataCollection::GetClientInfo(t .r0)i.r3 '
	pop $0
	EXEC '"$PROGRAMFILES\Internet Explorer\IExplore.exe" ${PRODUCT_WEB_SURVEY_POP}$0'
FunctionEnd

#打开查看更多游戏网页
Function un.OpenVoteSite
	EXEC '"$PROGRAMFILES\Internet Explorer\IExplore.exe" ${PRODUCT_VOTE_SITE}'
FunctionEnd



Function un.SubmitErrData
    SetOutPath $PLUGINSDIR
    Exch $1 ;submit data
    Exch
    Exch $0 ;errCode
	System::Call 'DataCollection::WriteAndSubmitDataForNSISA(t r0,t r1 ,i ${DataSubmitFlag})i.r3 '
FunctionEnd

Function un.FinishPageShow
    ;这个ID是取消按钮
	GetDlgItem $R5 $HWNDPARENT 2
	EnableWindow $R5 0
	ShowWindow $R5 ${SW_HIDE}

	;上一步
	GetDlgItem $R5 $HWNDPARENT 3
	EnableWindow $R5 0
	ShowWindow $R5 ${SW_HIDE}
	
	;关闭按钮
	System::Call 'USER32::GetSystemMenu(i $hwndparent,i0)i.s'
	;${GetSystemMenu} $0 $HWNDPARENT
	System::Call "user32::EnableMenuItem(is, i${SC_CLOSE}, i${MF_DISABLED})"
FunctionEnd
Function .onVerifyInstDir
    ;MessageBox MB_OK "enter verify dir!"
FunctionEnd

/*
Function SDDirectoryPagePre
	ReadRegStr $0 HKLM "SOFTWARE\snda\${PRODUCT_EN_NAME}" "Path"
	${If} $0 != ""
	    StrCpy $INSTDIR $0
	    SetOutPath $INSTDIR
	${Else}
	    StrCpy $0 0
		loop:
			ClearErrors
			EnumRegKey $1 HKLM SOFTWARE\snda $0
			${If} $1 == ""
			    goto done
			${EndIf}
			IfErrors done ;如果发生错误则提前结束循环
			ReadRegStr $2 HKLM SOFTWARE\snda\$1 "Path"
			${If} $2 == ""
			    IntOp $0 $0 + 1
			    goto loop
			${EndIf}
			Push $2
			Call SDGetParent
			Pop $3
			${If} $SysLCID == 1
				StrCpy $Suffix ${PRODUCT_CHS_NAME}
			${Else}
				StrCpy $Suffix ${PRODUCT_EN_NAME}
			${EndIf}
			StrCpy $INSTDIR $3\$Suffix
			goto __End__
		done:
	    	Call  FindLargestDisk
	    	#$1中为最大盘符
	    	Pop $1
		    #$2中为最大盘剩余空间
		    Pop $2
		    StrCpy $3 "$1\Program Files"
			${If} $SysLCID == 1
				StrCpy $Suffix "盛大网络\${PRODUCT_CHS_NAME}"
			${Else}
				StrCpy $Suffix "SNDA\${PRODUCT_EN_NAME}"
			${EndIf}
			StrCpy $INSTDIR $3\$Suffix
        __End__:
	${EndIf}
FunctionEnd
*/
#安装路径选择页面离开时事件函数
Function SDDirectoryPageLeave
	${If} $SysLCID != 1
	    MessageBox MB_YESNO|MB_DEFBUTTON2 "请确保您选择的安装路径中不含非法字符，且为全英文路径！如已确认，请点击[ 是(Y) ]开始安装" IDYES _YES_
	    Abort
	${EndIf}
_YES_:
    SetOutPath $INSTDIR
    StrLen $7 $INSTDIR
	IntCmp $7 190 _equ_ _lessthan_ _morethan_
_equ_:
_morethan_:
	MessageBox MB_OK "选择安装路径过长,请重新选择安装路径!"
  	Abort
_lessthan_:

FunctionEnd


Function FinishPagePre
	# 设置第一个checkbox位置(top的位置 $R1), 总的checkbox数目($R2)
	Push $R1
	Push $R2
	Intop $R1 80 + 0

	# 重新调整原始2个checkbox位置
	
	# 启动游戏
	Intop $R2 $R1 + 11
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Type" "Label"
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Text" "运行${PRODUCT_TEST_NAME}"
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Left" 62
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Right" 221
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Top" 	$R1
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Bottom" $R2

    Intop $R2 $R1 + 8
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Type" "CheckBox"
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Text" "运行${PRODUCT_TEST_NAME}"
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Left" 47
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Right" 55
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Top" $R1
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Bottom" $R2
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "State" "1"
    
    # 打开官网
    Intop $R1 $R1 + 22
	Intop $R2 $R1 + 11
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Type" "Label"
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Text" "打开官方主页"
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Left" 62
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Right" 221
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Top" 	$R1
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 6" "Bottom" $R2

    Intop $R2 $R1 + 8
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Type" "CheckBox"
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Text" "打开官方主页"
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Left" 47
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Right" 55
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Top" $R1
	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "Bottom" $R2
    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 7" "State" "1"

	# 自定义
	
	Pop $R2
	Pop $R1

FunctionEnd

#完成页面 显示时的函数
Function FinishPageShow
	;这个ID是取消按钮
	GetDlgItem $R5 $HWNDPARENT 2
	EnableWindow $R5 0
	ShowWindow $R5 ${SW_HIDE}
	
	;上一步
	GetDlgItem $R5 $HWNDPARENT 3
	EnableWindow $R5 0
	ShowWindow $R5 ${SW_HIDE}
	
	;关闭按钮
	System::Call 'user32::GetSystemMenu(i $hwndparent,i0)i.s'
	System::Call "user32::EnableMenuItem(is, i${SC_CLOSE}, i${MF_DISABLED})"
FunctionEnd

#完成页面结束时调用的函数
Function FinishPageLeave
	ShowWindow $HWNDPARENT ${SW_HIDE}  #隐藏窗口
	ReadINIStr $0 "$PLUGINSDIR\ioSpecial.ini" "Field 5" "State"
	StrCmp $0 1 StartExe NoStart
StartExe:
    	#SetOutPath $INSTDIR
		SetOutPath "$INSTDIR\CQYH"
		
		;MessageBox MB_OK "$INSTDIR\CQYH"
		;MessageBox MB_OK "$INSTDIR\${PROGRAM_NAME}"
		
    	ExecWait '"$INSTDIR\${PROGRAM_NAME}"'
NoStart:
	!ifdef SETUP_QIDIAN_LINK
	    CreateShortCut "$DESKTOP\${LINK_QD_NAME}.lnk" "C:\Program Files\Internet Explorer\iexplore.exe" "${LINK_QD_SITE1}${PRODUCT_GAMEID}${LINK_QD_SITE2}" "$TEMP\${LINK_QD_ICO}" 0
	!endif
 	# 删除7za.dll失败
	${If} $Delete7zFlag == -1
	    Push ${ERR_DELETE_FILE}
        StrCpy $R0 '${DataForSubmit},"AppChanel":"${PRODUCT_APPCHANEL}","ErrorMsg":"7z"'
		Push $R0
		Call SubmitErrData
	${EndIf}
	#删除volume文件失败
	${If} $DeleteVolumeFlag == -1
	    Push ${ERR_DELETE_FILE}
        StrCpy $R0 '${DataForSubmit},"AppChanel":"${PRODUCT_APPCHANEL}","ErrorMsg":"volume"'
		Push $R0
		Call SubmitErrData
	${EndIf}
	#doneta安装失败
	!ifdef SETUP_DOTNET
	    ${If} $ResDotNet == -1
		    Push ${ERR_PLUGINS_INST}
			StrCpy $R0 '${DataForSubmit},"AppChanel":"${PRODUCT_APPCHANEL}","ErrorMsg":"DOTNET"'
			Push $R0
			Call SubmitErrData
		${EndIf}
	!endif
	#VC 安装失败
    

FunctionEnd

#sjj 2010-12-29 自定义取消操作
Function OnUserAbort
	MessageBox MB_YESNO|MB_DEFBUTTON2 "《${PRODUCT_CHS_NAME}》尚未安装完成，确定退出安装？" IDYES __QuitInst__
    Abort
	goto __NoCancel_Anort__
__QuitInst__:
    Push ${ERR_QUIT_INST}
	StrCpy $R0 '${DataForSubmit},"AppChanel":"${PRODUCT_APPCHANEL}"'
	Push $R0
	Call SubmitErrData
__NoCancel_Anort__:
FunctionEnd
Function SDGetParameters
   Push $R0
   Push $R1
   Push $R2
   Push $R3

   StrCpy $R2 1
   StrLen $R3 $CMDLINE

   ;Check for quote or space
   StrCpy $R0 $CMDLINE $R2
   StrCmp $R0 '"' 0 +3
	 StrCpy $R1 '"'
	 Goto loop
   StrCpy $R1 " "

   loop:
	 IntOp $R2 $R2 + 1
	 StrCpy $R0 $CMDLINE 1 $R2
	 StrCmp $R0 $R1 get
	 StrCmp $R2 $R3 get
	 Goto loop

   get:
	 IntOp $R2 $R2 + 1
	 StrCpy $R0 $CMDLINE 1 $R2
	 StrCmp $R0 " " get
	 StrCpy $R0 $CMDLINE "" $R2

   Pop $R3
   Pop $R2
   Pop $R1
   Exch $R0
FunctionEnd


Function GetParameterValue
  Exch $R0  ; get the top of the stack(default parameter) into R0
  Exch      ; exchange the top of the stack(default) with
            ; the second in the stack(parameter to search for)
  Exch $R1  ; get the top of the stack(search parameter) into $R1

  ;Preserve on the stack the registers used in this function
  Push $R2
  Push $R3
  Push $R4
  Push $R5

  Strlen $R2 $R1+2    ; store the length of the search string into R2

  Call SDGetParameters  ; get the command line parameters
  Pop $R3             ; store the command line string in R3

  # search for quoted search string
  StrCpy $R5 '"'      ; later on we want to search for a open quote
  Push $R3            ; push the 'search in' string onto the stack
  Push '"/$R1='       ; push the 'search for'
  Call StrStr         ; search for the quoted parameter value
  Pop $R4
  StrCpy $R4 $R4 "" 1   ; skip over open quote character, "" means no maxlen
  StrCmp $R4 "" "" next ; if we didn't find an empty string go to next

  # search for non-quoted search string
  StrCpy $R5 ' '      ; later on we want to search for a space since we
                      ; didn't start with an open quote '"' we shouldn't
                      ; look for a close quote '"'
  Push $R3            ; push the command line back on the stack for searching
  Push '/$R1='        ; search for the non-quoted search string
  Call StrStr
  Pop $R4

  ; $R4 now contains the parameter string starting at the search string,
  ; if it was found
next:
  StrCmp $R4 "" check_for_switch ; if we didn't find anything then look for
                                 ; usage as a command line switch
  # copy the value after /$R1= by using StrCpy with an offset of $R2,
  # the length of '/OUTPUT='
  StrCpy $R0 $R4 "" $R2  ; copy commandline text beyond parameter into $R0
  # search for the next parameter so we can trim this extra text off
  Push $R0
  Push $R5            ; search for either the first space ' ', or the first
                      ; quote '"'
                      ; if we found '"/output' then we want to find the
                      ; ending ", as in '"/output=somevalue"'
                      ; if we found '/output' then we want to find the first
                      ; space after '/output=somevalue'
  Call StrStr         ; search for the next parameter
  Pop $R4
  StrCmp $R4 "" done  ; if 'somevalue' is missing, we are done
  StrLen $R4 $R4      ; get the length of 'somevalue' so we can copy this
                      ; text into our output buffer
  StrCpy $R0 $R0 -$R4 ; using the length of the string beyond the value,
                      ; copy only the value into $R0
  goto done           ; if we are in the parameter retrieval path skip over
                      ; the check for a command line switch

; See if the parameter was specified as a command line switch, like '/output'
check_for_switch:
  Push $R3            ; push the command line back on the stack for searching
  Push '/$R1'         ; search for the non-quoted search string
  Call StrStr
  Pop $R4
  StrCmp $R4 "" done  ; if we didn't find anything then use the default
  StrCpy $R0 ""       ; otherwise copy in an empty string since we found the
                      ; parameter, just didn't find a value

done:
  Pop $R5
  Pop $R4
  Pop $R3
  Pop $R2
  Pop $R1
  Exch $R0 ; put the value in $R0 at the top of the stack
FunctionEnd


 Function StrStr
   Exch $R1 ; st=haystack,old$R1, $R1=needle
   Exch    ; st=old$R1,haystack
   Exch $R2 ; st=old$R1,old$R2, $R2=haystack
   Push $R3
   Push $R4
   Push $R5
   Push $R6
   StrLen $R3 $R1
   StrLen $R6 $R2
   StrCpy $R4 0
   ; $R1=needle
   ; $R2=haystack
   ; $R3=len(needle)
   ; $R4=cnt
   ; $R5=tmp
   loop:
     StrCpy $R5 $R2 $R3 $R4
     StrCmp $R5 $R1 done
     IntCmp $R4 $R6 done
     IntOp $R4 $R4 + 1
     Goto loop
 done:
   StrCpy $R1 $R2 "" $R4
   Pop $R6
   Pop $R5
   Pop $R4
   Pop $R3
   Pop $R2
   Exch $R1
 FunctionEnd
 
#获取父目录
Function SDGetParent
  Exch $R0
  Push $R1
  Push $R2
  Push $R3

  StrCpy $R1 0
  StrLen $R2 $R0

  loop:
	IntOp $R1 $R1 + 1
	IntCmp $R1 $R2 get 0 get
	StrCpy $R3 $R0 1 -$R1
	StrCmp $R3 "\" get
	Goto loop

  get:
	StrCpy $R0 $R0 -$R1

	Pop $R3
	Pop $R2
	Pop $R1
	Exch $R0
FunctionEnd


