#脚本版本 1.0.0


#*******************以下可修改***********************# 

#license等页面的颜色定义，默认为蓝色(3E66AC)，根据需要自行修改。格式为：6个字节的16进制，RRGGBB
!define MUI_TEXT_BGCOLOR 3E66AC ;改为默认黑色
 
#游戏的中文名
!define PRODUCT_CHS_NAME "传奇永恒"

#游戏的英文简称（对应注册表键值）
!define PRODUCT_EN_NAME "CQYH"

#游戏的英文名（给人看的名字）
!define PRODUCT_ENGLISH_NAME "CQYH"

#游戏ID编号
!define PRODUCT_GAMEID "991002359"
#sjj 2010-10-12
!define PRODUCT_GAMEID_INT 991002359

#自行设定的倍数,可以为小数
!define PRODUCT_MP "1"

#游戏客户端启动程序名(相对于游戏安装目录)
!define PROGRAM_NAME "CQYH\Launcher.exe"

#游戏客户端主程序名(相对于游戏安装目录：如：《热血传奇》：此处应为：data\mir2.exe)
!define PROGRAM_GAME_NAME "CQYH\Binaries\Win32\MMOGame-Win32-Shipping.exe"

#游戏进程名
!define PROCESS_NAME "MMOGame-Win32-Shipping.exe"

!include "aod_patch_ver.nsh"

#客户端版本号
!define PRODUCT_VERSION "${PRODUCTION_VERSION_TO}"

#对外版本号，安装时显示
!define PRODUCT_EXT_VERSION "${PRODUCTION_VERSION_FROM}-${PRODUCTION_VERSION_TO}"

#游戏主页
!define PRODUCT_WEB_SITE "http://cq.sdo.com"

#sjj 2011-02-23 安装包是光盘版还是硬盘版 0-硬盘版 1-光盘版
#!define SETUP_FROM_CD 1

#sjj 2010-06-17
#改变协议的windows消息宏定义
!define EM_SETCHARFORMAT		0x444
!define SCF_ALL					0x0004
!define CFM_COLOR				0x40000000
!define GB2312_CHARSET          134
#设置为可根目录安装模式
AllowRootDirInstall true

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
!define PRODUCT_COMPRESS_TYPE "zlib"

#=======================带zip文件的安装包=======================#
#                                                             	#
#    去掉ZIP_FILENAME宏前的注释即可                           	#
#    当data.zip为分卷压缩时，要确保其它的分卷文件都被包含进来了	#
#                                                             	#
#===============================================================#
#Zip文件路径
#sjj 2010-10-12
##!define ZIP_FILENAME	"data.zip"
#!define ZIP_FILENAME	""
#!define ZIP_PASSWORD ""
#sjj 2010-12-29 分卷数量
!define ZIP_FILE_NUM    1
#分卷信息文件名
#!define ZIP_VOLUMINFO_FILENAME "VolumInfo.ini"


#####################################################################################

#sjj 2011-08-10 定义完成页面增加自定义checkbox
!define USER_DEFINE_CHECKBOX

######################################################################################

#sjj 2010-12-29 自定义用户取消事件
!define MUI_CUSTOMFUNCTION_ABORT OnUserAbort
!ifdef MUI_TEXT_COLOR
  !undef MUI_TEXT_COLOR
!endif
!define MUI_TEXT_COLOR 000000
#*******************以上可修改***********************# 
#*******************以下严禁修改区域***********************# 
#此处代码严禁修改，如擅自变动经查实后将对纂改者进行问责

!define TEMPLATE_VERSION "1.0.0"

#客户端信息收集后台接口地址
!define PRODUCT_NVER n1000
!define PRODUCT_WEB_VERSIONREPORT "http://uv.sdo.com/userinfo.asp?nver=${PRODUCT_NVER}"


SetCompressor ${PRODUCT_COMPRESS_TYPE}
Name "《${PRODUCT_CHS_NAME}》${PRODUCT_EXT_VERSION}补丁包"
OutFile "${PRODUCT_ENGLISH_NAME}_Setup(${PRODUCTION_VERSION_FROM}-${PRODUCTION_VERSION_TO}).exe"
CRCCHECK force
XPStyle on
SetDatablockOptimize on

RequestExecutionLevel admin

#*******************以上严禁修改区域***********************# 


!define MUI_SKIN "InstallWizard"

#-------新Skin的脚本文件Modern UI Experience\System.nsh已经修改过，增加了背景图片和版本信息文字。-------#
!include "MUIXP.nsh"
!include "nsDialogs.nsh"
!include "UsefulLib.nsh"

!include "x64.nsh"
!include "LogicLib.nsh"
!include "WinMessages.nsh"


!include "FontName.nsh"
!include "FontReg.nsh"
!include "FontRegAdv.nsh"


${VerCmp}

#[[INCLUDE_ADD_START]]#  //重要标志，请勿修改
#[[INCLUDE_ADD_COMMENT]]#
#[[INCLUDE_ADD_END]]#  //重要标志，请勿修改

#欢迎页面
!define MUI_WELCOMEFINISHPAGE_BITMAP_NOSTRETCH
;!define MUI_ABORTWARNING #sjj 2010-12-29 去掉默认的取消事件,采用自定义事件
!define MUI_ICON "Resources\setup.ico"
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
#sjj 2010-12-29 离开此页面时检查安装路径长度是否过长
;!define MUI_PAGE_CUSTOMFUNCTION_LEAVE SDDirectoryPageLeave
;!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

#插入完成安装页面
# sjj  2010-06-11 完成页面初始化，显示，完成函数
!ifdef USER_DEFINE_CHECKBOX
!define MUI_PAGE_CUSTOMFUNCTION_PRE   FinishPagePre
!define MUI_PAGE_CUSTOMFUNCTION_SHOW  FinishPageShow
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE FinishPageLeave
!endif

!define MUI_FINISHPAGE_TEXT "《${PRODUCT_CHS_NAME}》客户端 已经成功安装\n\n您可以使用盛大通行证直接登陆《${PRODUCT_CHS_NAME}》游戏了!"
;!define MUI_FINISHPAGE_RUN "$INSTDIR\${PROGRAM_NAME}"
;!define MUI_FINISHPAGE_RUN_TEXT "运行${PRODUCT_CHS_NAME}"
!define MUI_FINISHPAGE_SHOWREADME "${PRODUCT_WEB_SITE}"
!define MUI_FINISHPAGE_SHOWREADME_TEXT "打开官方主页"
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION SDOpenHomeUrl
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

ReserveFile "${NSISDIR}\Plugins\advsplash.dll"
ReserveFile "${NSISDIR}\Plugins\UserInfo.dll"
ReserveFile "${NSISDIR}\Plugins\Installoptions.dll"
ReserveFile "${NSISDIR}\Plugins\Web.dll"
ReserveFile "${NSISDIR}\Plugins\ZipSetup.dll"
#sjj 2010-12-29
ReserveFile "${NSISDIR}\Plugins\ZipSubVolumCheck.dll"
ReserveFile "${NSISDIR}\Plugins\7za.dll"
ReserveFile "Resources\left.bmp"
ReserveFile "Resources\splash.png"
ReserveFile "Resources\pt.bmp"

#ReserveFile "Plugins\HeelUpdate.dll"
#ReserveFile "Plugins\UpdaterPList.dll"
#ReserveFile "Plugins\XDelta3WrapFactory.dll"
#ReserveFile "Plugins\PackageInstall.dll"
#ReserveFile "Plugins\PackageInfo.xml"
#ReserveFile "Plugins\ZlibWrap.dll"

BrandingText " 《${PRODUCT_CHS_NAME}》 盛大互动娱乐"

VIProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey  "FileVersion" "${PRODUCT_VERSION}"
VIAddVersionKey  "FileDescription" "《${PRODUCT_CHS_NAME}》客户端差异补丁安装包"
VIAddVersionKey  "LegalCopyright" "盛大网络发展有限公司"
VIAddVersionKey  "ProductName" "《${PRODUCT_CHS_NAME}》"
VIAddVersionKey  "CompanyName" "盛大网络发展有限公司"


Section "MainSection" SEC01
	SetOutPath $PLUGINSDIR
	SetOverwrite on

	;解压zip/7z包
	!ifdef ZIP_FILENAME
        #sjj 2010-10-12
        ZipSetup::ExtractAll "$PLUGINSDIR\${ZIP_FILENAME}" "$PLUGINSDIR" "${ZIP_PASSWORD}"
        #ZipSetup::zip "$EXEDIR\${ZIP_FILENAME}" "$PLUGINSDIR" "${ZIP_PASSWORD}"
		Pop $R0
		Pop $R1
		Delete "$EXEDIR\7za.dll"
		IntCmp $R0 -1 +1 +3 +3
		MessageBox MB_OK|MB_ICONEXCLAMATION $R1 /SD IDOK
		Quit
	!endif
	

	;在这里添加客户端文件
	File /r "PatchMPQ.exe"
	File /r "XDelta3WrapFactory.dll"
	File /r "XDelta3WrapFactory2.dll"
	File /r "zlibwapi.dll"
	File /r "zlibwapid.dll"
	File /r "ZlibWrap.dll"
	File /r "log4cplusU.dll"
	File /r "LocalVersion.xml"
	
	nsExec::Exec '"$PLUGINSDIR\PatchMPQ.exe" ${PRODUCTION_VERSION_FROM} ${PRODUCTION_VERSION_TO}'
   
  SetOutPath $INSTDIR
SectionEnd


#*******************函数定义开始***********************#

Function .onInit

	InitPluginsDir
	File "/oname=$PLUGINSDIR\Header.bmp" "Resources\Header.bmp"
	File "/oname=$PLUGINSDIR\Bottom.bmp" "Resources\Bottom.bmp"
	File "/oname=$PLUGINSDIR\pt.bmp" "Resources\pt.bmp"
	File "/oname=$PLUGINSDIR\left.bmp" "Resources\left.bmp"
	File "/oname=$PLUGINSDIR\splash.png" "Resources\splash.png"
	File "/oname=$PLUGINSDIR\advsplash.dll" "${NSISDIR}\Plugins\advsplash.dll"
	File "/oname=$PLUGINSDIR\UserInfo.dll" "${NSISDIR}\Plugins\UserInfo.dll"
	File "/oname=$PLUGINSDIR\ZipSetup.dll" "${NSISDIR}\Plugins\ZipSetup.dll"

    #sjj 2010-12-29
	!ifdef ZIP_FILENAME
	File "/oname=$PLUGINSDIR\ZipSubVolumCheck.dll" "${NSISDIR}\Plugins\ZipSubVolumCheck.dll"
	!ifndef SETUP_FROM_CD
	File "/oname=$EXEDIR\7za.dll" "${NSISDIR}\Plugins\7za.dll"
	!endif
	;File "/oname=c:\${ZIP_VOLUMINFO_FILENAME}" "Client\${ZIP_VOLUMINFO_FILENAME}"
	!endif
	
	File "/oname=$PLUGINSDIR\Web.dll" "${NSISDIR}\Plugins\Web.dll"
	File "/oname=$PLUGINSDIR\md5dll.dll" "${NSISDIR}\Plugins\md5dll.dll"
	
	System::Call 'Kernel32::CreateMutexA(i 0,i 0,t "Client mend") i .r1 ?e'
	Pop $0
	strCmp $0 0 +3
		MessageBox MB_OK|MB_ICONEXCLAMATION "《${PRODUCT_CHS_NAME}》补丁包已经在运行" /SD IDOK
	 	Quit
	Push "${PROCESS_NAME}"
	Call SDFindProcess

	advsplash::show 1000 600 400 -1 "$PLUGINSDIR\splash"
	Call SDCheck
	StrCpy $INSTDIR "$PROGRAMFILES\盛大网络\${PRODUCT_CHS_NAME}"

	;取zip/7z包的大小
	!ifdef ZIP_FILENAME
		
		File "/oname=$PLUGINSDIR\${ZIP_FILENAME}" "${ZIP_PATH}"
       #************************************************************************************************************#	
				;获取zip/7z包大小
        #sjj 2010-10-12
        #ZipSetup::GetZipDataSize "$EXEDIR\${ZIP_FILENAME}" "${ZIP_PASSWORD}"
        ZipSetup::GetZipDataSize "$PLUGINSDIR\${ZIP_FILENAME}" "${ZIP_PASSWORD}"

		Pop $R1
		System::Int64Op $R1 / 1024
		Pop $R1

		SectionGetSize ${SEC01} $R0
		IntOp $R0 $R0 + $R1
		SectionSetSize ${SEC01} $R0
	!endif
FunctionEnd

Function .onGUIEnd
;	BgImage::Destroy
FunctionEnd

Function .onInstSuccess
	HideWindow
	;提交客户端信息
	;Web::SubmitVersionInfo "${PRODUCT_WEB_VERSIONREPORT}" "${PRODUCT_GAMEID}" "${PRODUCT_VERSION}" "install" "0"
FunctionEnd


#打开官方主页
Function SDOpenHomeUrl
	EXEC '"$PROGRAMFILES\Internet Explorer\IExplore.exe" ${PRODUCT_WEB_SITE}'
FunctionEnd


#检查此时游戏是否正在运行
Function SDFindProcess
	Exch $0
	FindProcDll::FindProc $0
	StrCmp $R0 1 0 +3
	MessageBox MB_OK '《${PRODUCT_CHS_NAME}》 正在运行中，请结束游戏后,再次尝试安装！$\r$\n\
	若未发现游戏客户端运行，请查看windows进程管理器，$\r$\n\
	确保 《${PROCESS_NAME}》进程不存在后，重新启动安装包！' /SD IDOK
	Quit
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


Function SDDirectoryPagePre
	ReadRegStr $0 HKLM "SOFTWARE\snda\${PRODUCT_EN_NAME}" "Path"
	StrCmp $0 "" 0 +2
		goto EndPre
		StrCpy $INSTDIR $0
EndPre:

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


#sjj  2010-06-11 完成页面的初始化函数
Function FinishPagePre

	# 设置第一个checkbox位置(top的位置 $R1), 总的checkbox数目($R2)
	Push $R1
	Push $R2
	Intop $R1 80 + 0

	# 重新调整原始2个checkbox位置
	
	# 启动游戏
;	Intop $R2 $R1 + 11
;    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Type" "Label"
;	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Text" "运行${PRODUCT_CHS_NAME}"
;	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Left" 62
;	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Right" 221
;	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Top" 	$R1
;	!insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 4" "Bottom" $R2

;    Intop $R2 $R1 + 8
;    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Type" "CheckBox"
;    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Text" "运行${PRODUCT_CHS_NAME}"
;    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Left" 47
;    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Right" 55
;	 !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Top" $R1
;	 !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "Bottom" $R2
;    !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "Field 5" "State" "1"
    
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

	Pop $R2
	Pop $R1

FunctionEnd

#sjj  2010-06-11 完成页面 显示时的函数
Function FinishPageShow
	;这个ID是取消按钮
	GetDlgItem $R5 $HWNDPARENT 2
	EnableWindow $R5 0
	ShowWindow $R5 ${SW_HIDE}
	
	;上一步
	GetDlgItem $R5 $HWNDPARENT 3
	EnableWindow $R5 0
	ShowWindow $R5 ${SW_HIDE}
FunctionEnd

#sjj  2010-06-11 完成页面结束时调用的函数
Function FinishPageLeave

	ShowWindow $HWNDPARENT ${SW_HIDE}  #隐藏窗口

	StrCpy $3 "-"   # 信息提交
	StrCpy $4 "-"
	StrCpy $5 "-"
	StrCpy $6 "-"
	#酷6
	StrCpy $7 "-"
	#微端
	StrCpy $8 "-"
# 信息提交
    StrCpy $1 "0"
	!ifdef SETUP_FROM_CD
	StrCpy $1 "1"
	!endif 
	StrCpy $2 "-" ; 当前版本没有2144
	Web::SubmitVersionInfo "${PRODUCT_WEB_VERSIONREPORT}" "${PRODUCT_GAMEID}" "${PRODUCT_VERSION}" "install" "$1,$2,$3,$4,$5,$6,$7,$8"

	!ifdef SETUP_CLOUD_PLG
		Exec '"$Temp\SDG_SHOWPOP.exe" -bid601'
	!endif
FunctionEnd

#sjj 2010-12-29 自定义取消操作
Function OnUserAbort
   MessageBox MB_YESNO|MB_DEFBUTTON2 "确定退出安装?" IDYES NoCancelAbort
   ;EXEC '"$PROGRAMFILES\Internet Explorer\IExplore.exe" ${PRODUCT_VOTE_SITE}'
     Abort
NoCancelAbort:
FunctionEnd

#sjj 2010-12-29 安装路径选择页面离开时事件函数
Function SDDirectoryPageLeave
    SetOutPath $INSTDIR
    StrLen $7 $INSTDIR
	IntCmp $7 190 _equ_ _lessthan_ _morethan_
_equ_:
_morethan_:
	MessageBox MB_OK "选择安装路径过长,请重选选择安装路径!"
  	Abort
_lessthan_:
	IfFileExists $INSTDIR\${PROGRAM_NAME} havefile 0
	MessageBox MB_OK|MB_ICONEXCLAMATION "补丁包安装路径选择错误!$\r$\n当前路径'$INSTDIR'不为游戏《${PRODUCT_CHS_NAME}》的安装目录$\r$\n请重新选择补丁包安装目录!保证其为正确的游戏目录!" /SD IDOK
	Abort
	havefile:
FunctionEnd


