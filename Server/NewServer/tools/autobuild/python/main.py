# -*- coding: gb2312 -*-
# !/usr/bin/env python
# Filename: AutoBuild.py

'Function overview'

' PrintHelpInfo()           Display command-line help'
' CmdLine_Process()         Process command-line arguments'
' Get_New_Revision()        Retrieve and store the latest revision'
' Merge_StringTable()       Merge StringTable'
' Generate_HtmlFile()       Analyze batch output logs and generate HTML'
' Send_Mail()               Email build results as HTML to the specified users '

import os
import string
import datetime
import sys
import getopt
import MySQLdb
from StringTable import GenStringTable

# Global constants
ServerName = "BuildSvr"

szLogFile = ""
szDirName = ""

nErrorCount = 0
nWarningCount = 0

ANCHOR_LIST = []

SVN_SRC_LOCATION = "https://192.168.10.5/svn/feitian/stables/2010_07_05_4418_6220_2461"
SVN_DATA_LOCATION = "https://192.168.10.5/svn/FeiTian_Data/stables/2010_07_05_4418_6220_2461"
SVN_GD_LOCATION = "https://192.168.10.5/svn/FeiTian_GameData/stables/2010_07_05_4418_6220_2461"

#SVN_SRC_LOCATION = "https://192.168.10.5/svn/feitian/stables/2010_07_05_4364_6122_2337"
#SVN_DATA_LOCATION = "https://192.168.10.5/svn/FeiTian_Data/stables/2010_07_05_4364_6122_2337"
#SVN_GD_LOCATION = "https://192.168.10.5/svn/FeiTian_GameData/stables/2010_07_05_4364_6122_2337"

#SVN_SRC_LOCATION = "https://192.168.10.5/svn/feitian/branches/2010.6"
#SVN_DATA_LOCATION = "https://192.168.10.5/svn/FeiTian_Data/branches/2010.6"
#SVN_GD_LOCATION = "https://192.168.10.5/svn/feitian_GameData/branches/2010.6"

#SVN_SRC_LOCATION = "https://192.168.10.5/svn/feitian/trunk"
#SVN_DATA_LOCATION = "https://192.168.10.5/svn/FeiTian_Data/trunk/Data"
#SVN_GD_LOCATION = "https://192.168.10.5/svn/FeiTian_GameData/trunk"

#SVN_SRC_LOCATION = "https://192.168.10.5/svn/feitian/stables/2010_04_29_4240_6017_2186"
#SVN_DATA_LOCATION = "https://192.168.10.5/svn/FeiTian_Data/stables/2010_04_29_4240_6017_2186"
#SVN_GD_LOCATION = "https://192.168.10.5/svn/FeiTian_GameData/stables/2010_04_29_4240_6017_2186"

#SVN_SRC_LOCATION = "https://192.168.10.5/svn/feitian/stables/2010_03_04_3931_5653_1523"
#SVN_DATA_LOCATION = "https://192.168.10.5/svn/FeiTian_Data/stables/2010_03_04_3931_5653_1523"
#SVN_GD_LOCATION = "https://192.168.10.5/svn/FeiTian_GameData/stables/2010_03_04_3931_5653_1523"

#SVN_SRC_LOCATION = "https://192.168.10.5/svn/feitian/stables/0_12_76_3510_5267_1398"
#SVN_DATA_LOCATION = "https://192.168.10.5/svn/FeiTian_Data/stables/0_12_76_3510_5267_1398"
#SVN_GD_LOCATION = "https://192.168.10.5/svn/FeiTian_GameData/stables/0_12_76_3510_5267_1398"

SVN_SRC_REV = "head"
SVN_DATA_REV = "head"
SVN_GD_REV = "head"

IsGDC = True
IsTgpData = True
IsTgpGd = True
IsInstall = True
ClientIsCompile = True
bAddShell = True

MAJOR_VERSION = 0
MINOR_VERSION = 12
BASE_VERSION = str(MAJOR_VERSION) + "." + str(MINOR_VERSION) 
szVersion = ""
nBuildNumber = 0

BUILDER_TYPE = "Public"
BUILD_EDITION_LIST =[
    {
        'name': 'Debug Server By IncrediBuild',
        'command': 'BuildConsole SourceCode\\Feitian.sln /CFG=\"Debug Server|WIN32\"'
    },
    {
        'name': 'Debug Client By IncrediBuild',
        'command': 'BuildConsole SourceCode\\Feitian.sln /CFG=\"Debug Client|WIN32\"'
    },
    {
        'name': 'Final Release By IncrediBuild',
        'command': 'BuildConsole SourceCode\\Feitian.sln /CFG=\"Final Release|WIN32\"'
    },
#    {
#        'name': 'Release Server By IncrediBuild',
#        'command': 'BuildConsole SourceCode\\Feitian.sln /CFG=\"Release Server|WIN32\"'
#    },
#    {
#        'name': 'Release Client By IncrediBuild',
#        'command': 'BuildConsole SourceCode\\Feitian.sln /CFG=\"Release Client|WIN32\"'
#    },
    {
        'name': 'GDC By IncrediBuild',
        'command': 'BuildConsole SourceCode\\Feitian.sln /CFG=\"GDC|WIN32\"'
    },
]

szSrcRev = "0000"
szDataRev = "0000"
szGameDataRev = "0000"

szOldSrcRev = "0000"
szOldDataRev = "0000"
szOldGameDataRev = "0000"

## Helper functions
def bprint( szString ):
    global szLogFile
    print(szString)
    if szLogFile != "":
        os.popen("ECHO " + szString + ">> " + szLogFile)

## Display help
def PrintHelpInfo():
    HelpInfo  = '命令行格式 python.exe AutoBuild.py [--help] [--builder_type] [--base_version]\n'
    HelpInfo += '                                 [--code] [--data] [--gd] [--build_edition]\n\n'
    HelpInfo += '--help               显示帮助信息 \n\n'
    HelpInfo += '--base_version       程序基础版本号\n\n'
    HelpInfo += '--code [链接] [版本] 生成指定版本的 code \n'
    HelpInfo += '                     链接:可选;指定 code 库的地址\n'
    HelpInfo += '                     默认为 https://192.168.10.5/svn/feitian/trunk\n'
    HelpInfo += '                     版本:指定 cdoe 的版本,默认为 head\n'
    HelpInfo += '                     链接和版本号用 # 分隔\n'
    HelpInfo += '                     not:不编译源代码\n\n'
    HelpInfo += '--build_edition      编译指定版本的工程，是 code 命令的附加选项\n'
    HelpInfo += '                     参数:1  Build Debug Server By Incredibuild\n'
    HelpInfo += '                     参数:2  Build Relase Server By Incredibuild\n'
    HelpInfo += '                     参数:3  Build Debug Client By Incredibuild\n'
    HelpInfo += '                     参数:4  Build Release Client By Incredibuild\n'
    HelpInfo += '--data [链接] [版本] 生成指定版本的 Data \n'
    HelpInfo += '                     链接:可选;指定 Data 库的地址\n'
    HelpInfo += '                     默认为 https://192.168.10.5/svn/FeiTian_Data/trunk\n'
    HelpInfo += '                     版本:可选;指定 Data 的版本,默认为 head\n'
    HelpInfo += '                     链接和版本号用 # 分隔\n'
    HelpInfo += '                     not:不更新Data\n\n'
    HelpInfo += '--gd [链接] [版本]   生成指定版本的 GameData \n'
    HelpInfo += '                     链接:可选;指定 GameData 库的地址\n'
    HelpInfo += '                     默认为 https://192.168.10.5/svn/FeiTian_GameData/trunk\n'
    HelpInfo += '                     版本:可选;指定 GameData 的版本,默认为 head\n'
    HelpInfo += '                     链接和版本号用 # 分隔\n'
    HelpInfo += '                     not:不更新GameData\n\n'
    HelpInfo += '--tgp data           打包客户端 Data 目录\n'
    HelpInfo += '--tgp gd             打包客户端 GameData \n'
    HelpInfo += '--tgp not            不打包\n\n'
    HelpInfo += '--gdc                是否编译 GameData \n\n'
    HelpInfo += '--gen_install_packet 是否生成客户端安装包 \n\n'
    print( HelpInfo )

## Process command-line arguments
def CmdLine_Process():
    global BUILDER_TYPE
    global SVN_SRC_LOCATION
    global SVN_SRC_REV
    global SVN_DATA_LOCATION
    global SVN_DATA_REV
    global SVN_GD_LOCATION
    global SVN_GD_REV
    global IsGDC
    global BASE_VERSION
    global BUILD_EDITION_LIST
    global ClientIsCompile
    global IsTgpData
    global IsTgpGd

    try:
        opts,args = getopt.getopt( sys.argv[1:],
                                   "",
                                   ["help",
                                    "builder_type=",
                                    "base_version=",
                                    "code=",
                                    "build_edition=",
                                    "data=",
                                    "gd="
                                   ]
                                 )
    except getopt.GetoptError:
        print "参数错误"
        os._exit(1)

    if opts:
        for o,a in opts:
            localCmd  = o.lower()
            localPara = a.lower()
            
            if localCmd == "--builder_type":
                if localPara == "test":
                    # Internal developer debugging
                    BUILDER_TYPE = "test"
                else:
                    BUILDER_TYPE = ""
            elif localCmd == "--help":
                # Do nothing else if the user requests help
                PrintHelpInfo()
                os._exit(0)
            elif localCmd == "--base_version":
                if localPara:
                    BASE_VERSION = localPara
                else:
                    print "基础版本参数错误"
                    os._exit(0)
            elif localCmd == "--code":
                # Source code options
                if localPara == "not":
                    # Do not build
                    SVN_SRC_LOCATION = ""
                    SVN_SRC_REV = ""
                else:
                    local_List_Para = localPara.split("#")
                    if len(local_List_Para) != 2:
                        print "src 命令参数错误"
                        os._exit(0)
                    if local_List_Para[0]:
                        SVN_SRC_LOCATION = local_List_Para[0]
                    if local_List_Para[1]:
                        SVN_SRC_REV = local_List_Para[1]
            elif localCmd == "--build_edition":
                if localPara:
                    BUILD_EDITION_LIST = []
                    localBuild_Edition = False
                    if "1" in localPara:
                        local_Dict_Build_Edition = {'name':'Debug Server By IncrediBuild','command':'BuildConsole SourceCode\\Feitian.sln /CFG=\"Debug Server|WIN32\"'}
                        BUILD_EDITION_LIST.append(local_Dict_Build_Edition)
                        localBuild_Edition = True
                    if "2" in localPara:
                        local_Dict_Build_Edition = {'name':'Debug Client By IncrediBuild','command':'BuildConsole SourceCode\\Feitian.sln /CFG=\"Debug Client|WIN32\"'}
                        BUILD_EDITION_LIST.append(local_Dict_Build_Edition)
                        localBuild_Edition = True
                        ClientIsCompile = True
                    if "3" in localPara:
                        local_Dict_Build_Edition = {'name':'Release Server By IncrediBuild','command':'BuildConsole SourceCode\\Feitian.sln /CFG=\"Release Server|WIN32\"'}
                        BUILD_EDITION_LIST.append(local_Dict_Build_Edition)
                        localBuild_Edition = True
                    if "4" in localPara:
                        local_Dict_Build_Edition = {'name':'Release Client By IncrediBuild','command':'BuildConsole SourceCode\\Feitian.sln /CFG=\"Release Client|WIN32\"'}
                        BUILD_EDITION_LIST.append(local_Dict_Build_Edition)
                        localBuild_Edition = True
                        ClientIsCompile = True
                    if not localBuild_Edition:
                        print "build_edition 选项参数错误"
                        os._exit(0)
                else:
                    print "build_edition 选项不能为空"
                    os._exit(0)
            elif localCmd == "--data":
                # Data options
                if localPara == "not":
                    # Do not build
                    SVN_DATA_LOCATION = ""
                    SVN_DATA_REV = ""
                else:
                    local_List_Para = localPara.split("#")
                    if len(local_List_Para) != 2:
                        print "data 命令参数错误"
                        os._exit(0)
                    if local_List_Para[0]:
                        SVN_DATA_LOCATION = local_List_Para[0]
                    if local_List_Para[1]:
                        SVN_DATA_REV = local_List_Para[1]
            elif localCmd == "--gd":
                # GameData options
                if localPara == "not":
                    # Do not update
                    SVN_GD_LOCATION = ""
                    SVN_GD_REV = ""
                else:
                    local_List_Para = localPara.split("#")
                    if len(local_List_Para) != 2:
                        print "gd 命令参数错误"
                        os._exit(0)
                    if local_List_Para[0]:
                        SVN_GD_LOCATION = local_List_Para[0]
                    if local_List_Para[1]:
                        SVN_GD_REV = local_List_Para[1]
            elif localCmd == "--gdc":
                # Build GameData
                if localPara == "not":
                    # Do not build
                    IsGDC = False
                else:
                    IsGDC = True
            elif localCmd == "--tgp":
                if localPara == "not":
                    # Do not package
                    IsTgpData = False
                    IsTgpGd = False
                elif localPara == "data":
                    # Package client Data
                    IsTgpData = True
                    IsTgpGd = False
                elif localPara == "gd":
                    # Package client GameData
                    IsTgpData = False
                    IsTgpGd = True
                else:
                    print "tgp 命令参数错误"
                    os._exit(0)
                    
def Init():
    global BUILDER_TYPE
    global ServerName
    global ANCHOR_LIST
    
    #   Set environment variables
    os.environ['PATH'] = os.environ['PATH'] + ";\"C:\\Program Files\\CollabNet Subversion Client\\\""
    os.environ['PATH'] = os.environ['PATH'] + ";\"C:\\Program Files\\Xoreax\\IncrediBuild\\\""
    os.environ['PATH'] = os.environ['PATH'] + ";\"C:\\Program Files\\febooti Command line email\\\""
    os.environ['PATH'] = os.environ['PATH'] + ";\"D:\\Program Files\\Microsoft Visual Studio 8\\Common7\\IDE\\\""
    os.environ['PATH'] = os.environ['PATH'] + ";\".\\SourceCode\\3rd\\DirectX9\\Bin\\x86\\\""
    os.environ['PATH'] = os.environ['PATH'] + ";\"C:\\Program Files\\MySQL\\MySQL Server 5.1\\bin\\\""
    os.environ['PATH'] = os.environ['PATH'] + ";\"C:\\Program Files\\NSIS\\\""
    
    # Create the Logs directory
    bprint("创建 Logs 目录")
    os.popen("If Not Exist Logs MD Logs")

## Get and store the latest revision
def Get_New_Revision():
    global BASE_VERSION
    global SVN_SRC_LOCATION
    global SVN_SRC_REV
    global SVN_DATA_LOCATION
    global SVN_DATA_REV
    global SVN_GD_LOCATION
    global SVN_GD_REV
    global szOldSrcRev
    global szOldDataRev
    global szGameDataRev
    global BUILDER_TYPE
    global szLogFile
    global szHtmlFile
    global szVersion
    global szDirName

    global szSrcRev
    global szDataRev
    global szGameDataRev
    global szOldSrcRev
    global szOldDataRev
    global szOldGameDataRev

    # Get the Source revision
    if SVN_SRC_LOCATION and SVN_SRC_REV:
        bprint("svn info " + SVN_SRC_LOCATION + " -r " + SVN_SRC_REV + " > svninfo.txt")
        os.popen("svn info " + SVN_SRC_LOCATION + " -r " + SVN_SRC_REV + " > svninfo.txt")
        fh = open("svninfo.txt","r")
        for szLine in fh.readlines():
            rev = string.find(szLine,"Revision: ")
            if rev >= 0:
                szSrcRev = string.strip(szLine[10:], " \n")
                break
        fh.close()
        os.popen("del svninfo.txt")
        bprint("获取当前的源代码版本：" + szSrcRev)
        if (szSrcRev == "0000"):
            exit(0)

    # Get the latest Data revision
    if SVN_DATA_LOCATION and SVN_DATA_REV:
        os.popen("svn info " + SVN_DATA_LOCATION + " -r " + SVN_DATA_REV + " > svninfo.txt")
        fh = open("svninfo.txt","r")
        for szLine in fh.readlines():
            rev = string.find(szLine,"Revision: ")
            if rev >= 0:
                szDataRev = string.strip(szLine[10:], " \n")
                break
        fh.close()
        os.popen("del svninfo.txt")
        bprint("获取当前的 Data 版本：" + szDataRev)
        if (szDataRev == "0000"):
            exit(0)

    # Get the latest GD revision
    if SVN_GD_LOCATION and SVN_GD_REV:
        os.popen("svn info " + SVN_GD_LOCATION + " -r " + SVN_GD_REV + " > svninfo.txt")

        fh = open("svninfo.txt","r")
        for szLine in fh.readlines():
            rev = string.find(szLine,"Revision: ")
            if rev >= 0:
                szGameDataRev = string.strip(szLine[10:]," \n")
                break
        fh.close()
        os.popen("del svninfo.txt")
        bprint("获取当前的 GameData 版本：" + szGameDataRev)
        if (szGameDataRev == "0000"):
            exit(0)

    # Get the previous revision
    try:
        rev = open("rev.dat","r")
        try:
            szOldSrcRev = string.strip(rev.readline(), " \n")
            szOldDataRev = string.strip(rev.readline(), " \n")
            szOldGameDataRev = string.strip(rev.readline(), " \n")
        finally:
           rev.close()
    except IOError:
        szOldSrcRev = "0000"
        szOldDataRev = "0000"
        szOldGameDataRev = "0000"

    bprint("获取上次的源代码版本：" + szOldSrcRev)
    bprint("获取上次的Data版本：" + szOldDataRev)
    bprint("获取上次的GameData版本：" + szOldGameDataRev)

    if SVN_SRC_REV and SVN_DATA_REV and SVN_GD_REV:
        # Store the latest revision
        try:
            rev = open("rev.dat","w")
            try:
                rev.write(szSrcRev + "\n")
                rev.write(szDataRev + "\n")
                rev.write(szGameDataRev + "\n")
                bprint("存储当前版本成功!")
            finally:
                rev.close()
        except IOError:
            bprint("存储当前版本失败!")

    if SVN_SRC_REV or SVN_DATA_REV or SVN_GD_REV:
        # Get the date and time
        tDate = datetime.datetime.now()
        szDate = tDate.strftime("%Y_%m_%d_%H_%M_%S")
        szDirName = szDate + "_" + szSrcRev + "_" + szDataRev + "_" + szGameDataRev
        szLogFile  = "Logs\\" + szDirName + ".log"
        szHtmlFile = "Logs\\" + szDirName + ".html"

        bprint( "log 文件是" + szLogFile)
        bprint( "html 文件是" + szHtmlFile)

        #   Create the version directory
        os.popen("IF NOT EXIST Build MD Build")
        os.popen("MD Build\\" + szDirName)

        if SVN_SRC_REV:
            # Save Source changes between the two revisions
            bprint("svn log " + SVN_SRC_LOCATION + " -r " + szOldSrcRev + ":" + SVN_SRC_REV + " > Logs\\" + szDirName + "_src_change_history.log")
            os.popen("svn log SourceCode -r " + szOldSrcRev + ":" + SVN_SRC_REV+ " > Logs\\" + szDirName + "_src_change_history.log")
            bprint("创建 Source 版本更新文件成功!")

        if SVN_DATA_REV:
            # Save Data changes between the two revisions
            bprint("svn log " + SVN_DATA_LOCATION + " -r " + szOldDataRev + ":" + SVN_DATA_REV + " > Logs\\" + szDirName + "_data_change_history.log")
            os.popen("svn log " + SVN_DATA_LOCATION + " -r " + szOldDataRev + ":" + SVN_DATA_REV+ " > Logs\\" + szDirName + "_data_change_history.log")
            bprint("创建 Data 版本更新文件成功!")

        if SVN_GD_REV:
            # Save GD changes between the two revisions
            bprint("svn log " + SVN_GD_LOCATION + " -r " + szOldGameDataRev + ":" + SVN_GD_REV + " > Logs\\" + szDirName + "_gamedata_change_history.log")
            os.popen("svn log " + SVN_GD_LOCATION + " -r " + szOldGameDataRev + ":" + SVN_GD_REV+ " > Logs\\" + szDirName + "_gamedata_change_history.log")
            bprint("创建 gd 版本更新文件成功!")

def IncreaseBuildNumber():
    global nBuildNumber
    global szVersion
    global szLogFile
    global szHtmlFile
    global szDirName

    # Insert into the Build database and obtain a build number
    try:
        conn = MySQLdb.connect(host="192.168.10.5",user="root",passwd="root",db="build",charset="utf8") 
        try:
            cursor = conn.cursor()

            BuildEdition = ""
            for e in BUILD_EDITION_LIST:
                BuildEdition = BuildEdition + e["name"] + " ; "
            bprint(BuildEdition)

            sqlstr = "INSERT INTO build(MajorVersion, MinorVersion, SrcLocation, SrcRevision, DataLocation, DataRevision, GDLocation," +\
                     " GDRevision, BuildType, BuildEdition, TGP_DATA, TGP_GD, GDC, InstallPackage) " +\
                     "VALUES(" + str(MAJOR_VERSION) + "," + str(MINOR_VERSION) + ",\"" + SVN_SRC_LOCATION + "\",\"" + szSrcRev + "\",\"" + SVN_DATA_LOCATION + "\",\"" +\
                     szDataRev + "\",\"" + SVN_GD_LOCATION + "\",\"" + szGameDataRev + "\",\"" + BUILDER_TYPE + "\",\"" + BuildEdition + "\"," + str(int(IsTgpData)) + "," +\
                     str(int(IsTgpGd)) + "," + str(int(IsGDC)) + "," + str(int(IsInstall)) + ")"
            bprint(sqlstr)
            cursor.execute(sqlstr)

            sqlstr = "SELECT LAST_INSERT_ID()"
            cursor.execute(sqlstr)
            row = cursor.fetchone()
            nBuildNumber = row[0]
            
            conn.commit()
            cursor.close()
            bprint("向Build数据库插入新纪录成功!")
        finally:
            conn.close()
    except Exception,ex:
        print Exception,":",ex

    bprint(str(nBuildNumber))

    VERSION_FILE_NAME = "SourceCode\\Src\\_version.h"
    TEMP_VERSION_FILE_NAME = "SourceCode\\Src\\__version.h"

    fSrc = open(VERSION_FILE_NAME, "r")
    fDest = open(TEMP_VERSION_FILE_NAME, "w")
    for szLine in fSrc.readlines():
        ver = string.find(szLine, "VER_BUILD")
        if ver >= 0:
            szLine = szLine[0:18] + str(nBuildNumber) + "\n"
            
        ver = string.find(szLine, "VER_REVISION")
        if ver >= 0:
            szLine = "#define\tVER_REVISION\t" + szSrcRev + "\n"

        fDest.write(szLine)

    fSrc.close()
    fDest.close()
    if nBuildNumber > 0:
        os.system("del " + VERSION_FILE_NAME)
        os.system("move " + TEMP_VERSION_FILE_NAME + " " + VERSION_FILE_NAME)
        os.popen("svn -m \"<increased build number to " + str(nBuildNumber) + " by auto build>\" commit " + VERSION_FILE_NAME + " >> " + szLogFile)

    szVersion = BASE_VERSION + "." + str(nBuildNumber) + "." + szSrcRev + "." + szDataRev + "." + szGameDataRev

    ## Append build number to build directory name
    szNewDirName = szDirName + "_" + str(nBuildNumber)
    os.system("REN Build\\" + szDirName + " " + szNewDirName)
    szDirName = szNewDirName;

    szNewLogFile  = "Logs\\" + szDirName + ".log"
    os.system("REN " + szLogFile + " " + szNewLogFile)
    szLogFile = szNewLogFile
    szHtmlFile = "Logs\\" + szDirName + ".html"
        
## Update Data and GD from SVN
def SvnUpdate():
    global szLogFile
    global szDirName
    global BUILDER_TYPE
    global SVN_DATA_LOCATION
    global SVN_DATA_REV
    global SVN_GD_LOCATION
    global SVN_GD_REV
    global SVN_SRC_LOCATION
    global SVN_SRC_REV
    global IsGDC
    global ANCHOR_LIST

    localAnchor_List_Insert_Position = 0
    # Process Data resources
    # Update the Data directory
    if SVN_DATA_LOCATION and SVN_DATA_REV:
        localDictData = { 'anchor': 'UPDATE_DATA','name': '从SVN更新Data数据','string': '从SVN更新Data数据...'}
        ANCHOR_LIST.append( localDictData )
        localAnchor_List_Insert_Position += 1
        bprint("从SVN更新Data数据...")
        if not os.path.exists('Build\\Data'):
            os.popen("svn co " + SVN_DATA_LOCATION + " -r " + SVN_DATA_REV + " Build\\Data >> " + szLogFile)
        else:
            os.popen("svn switch " + SVN_DATA_LOCATION + " -r " + SVN_DATA_REV + " Build\\Data >> " + szLogFile)
#        os.popen("svn revert Build\\Data -R >> " + szLogFile)
        bprint("成功获取Data数据！")
    # Package the Data directory

    # Process GameData
    # Get GameData from SVN
    if SVN_GD_LOCATION and SVN_GD_REV:
        localDictGd = {'anchor': 'GET_GAME_DATA','name': '从SVN获取GameData数据','string': '从SVN获取GameData数据...'}
        ANCHOR_LIST.append(localDictGd)
        localAnchor_List_Insert_Position += 1
        bprint("从SVN获取GameData数据...")
        bprint("GameData 所在SVN地址为: " + SVN_GD_LOCATION)
        bprint("svn export \"" + SVN_GD_LOCATION + "\" -r " + SVN_GD_REV + " \"Build\\" + szDirName + "\\GameData\"")
        os.popen("svn export \"" + SVN_GD_LOCATION + "\" -r " + SVN_GD_REV + " \"Build\\" + szDirName + "\\GameData\" >> " + szLogFile)
        bprint("成功获取GameData数据！")

    # Preprocess path data
    bprint("预处理寻路数据")
    os.system("Build\\MapPreprocessor.exe Build\\Data\\Terrain\\map_new0604 all Build\\" + szDirName + "\\GameData\\GameData")
    os.system("Build\\MapPreprocessor.exe Build\\Data\\Terrain\\氏族领地 all Build\\" + szDirName + "\\GameData\\GameData")
    os.system("Build\\MapPreprocessor.exe Build\\Data\\Terrain\\婴儿岛 all Build\\" + szDirName + "\\GameData\\GameData")
    
    # Build code
    if SVN_SRC_LOCATION:
        localDictSource = { 'anchor': 'GET_SOURCE_CODE','name': '从SVN获取源代码','string': '从SVN更新源代码...'}
        ANCHOR_LIST.append(localDictSource)
        localAnchor_List_Insert_Position += 1
        bprint("从SVN更新源代码...")
        # Remove the source directory
        bprint("删除源代码目录...")
        if BUILDER_TYPE != "test":
            os.popen("IF EXIST SourceCode RD SourceCode /s /q")
            if os.path.exists("SourceCode"):
                bprint("无法删除源代码目录！")
                os._exit(0)
        bprint("删除源代码目录成功！")
        # Get source code from SVN
        bprint("源代码所在SVN地址为: " + SVN_SRC_LOCATION)
        if BUILDER_TYPE != "test":
            print "svn co " + SVN_SRC_LOCATION + " -r " + SVN_SRC_REV + " SourceCode >> " + szLogFile
            os.popen("svn co " + SVN_SRC_LOCATION + " -r " + SVN_SRC_REV + " SourceCode >> " + szLogFile)
        bprint("成功获取源代码！")

        # Add the build number
        IncreaseBuildNumber()

        # Build all specified configurations
        for e in BUILD_EDITION_LIST:
            bprint("正在编译 " + e['name'] + " 版本...")
            ANCHOR_LIST.insert(localAnchor_List_Insert_Position,{'anchor': e['name'], 'name': '编译' + e['name'], 'string': '正在编译 ' + e['name'] + ' 版本...'})
            localAnchor_List_Insert_Position += 1
            if BUILDER_TYPE != "test":
                os.popen(e['command'] + ' >> ' + szLogFile)

## Process server code files
def Process_Server():
    global szDirName
    global SVN_SRC_REV
    global SVN_DATA_REV
    global SVN_GD_REV
    global ANCHOR_LIST

    if SVN_SRC_REV and SVN_DATA_REV and SVN_GD_REV:
        localDictServer = { 'anchor': 'PROCESS_SERVER_FILES','name': '处理服务端相关文件','string': '正在处理服务端相关文件...'}
        ANCHOR_LIST.append(localDictServer)
        bprint("正在处理服务端相关文件...")
        # Copy built files
        os.system("MD \"Build\\" + szDirName + "\\ServerDebug\"")
        os.system("copy \"SourceCode\\Bin\\Debug\\FTSvrMain.exe\" \"Build\\" + szDirName + "\\ServerDebug\"")

        os.system("MD \"Build\\" + szDirName + "\\ServerRelease\"")
        os.system("copy \"SourceCode\\Bin\\Release\\FTSvrMain.exe\" \"Build\\" + szDirName + "\\ServerRelease\"")

        os.system("MD \"Build\\" + szDirName + "\\ServerFinal\"")
        os.system("copy \"SourceCode\\Bin\\Final Release\\FTSvrMain.exe\" \"Build\\" + szDirName + "\\ServerFinal\"")

        # Copy related dynamic libraries
        os.system("copy \"SourceCode\\3rd\\MySQL\\lib\\debug\\libmysql.dll\" \"Build\\" + szDirName + "\\ServerDebug\"")
        os.system("copy \"SourceCode\\3rd\\zlib\\zlib1.dll\" \"Build\\" + szDirName + "\\ServerDebug\"")
        os.system("copy \"SourceCode\\3rd\\DirectX9\\Bin\\x86\\d3dx9d_36.dll\" \"Build\\" + szDirName + "\\ServerDebug\"")
        os.system("copy \"SourceCode\\dbghelp.dll\" \"Build\\" + szDirName + "\\ServerDebug\"")
        os.system("copy \"SourceCode\\3rd\\GMC\\Debug\\*.dll\" \"Build\\" + szDirName + "\\ServerDebug\"")
        os.system("MD \"Build\\" + szDirName + "\\ServerDebug\\Microsoft.VC80.DebugCRT\"")
        os.system("copy \"SourceCode\\3rd\\GMC\\Debug\\Microsoft.VC80.DebugCRT\\*.*\" \"Build\\" + szDirName + "\\ServerDebug\"")

        os.system("copy \"SourceCode\\3rd\\MySQL\\lib\\opt\\libmysql.dll\" \"Build\\" + szDirName + "\\ServerRelease\"")
        os.system("copy \"SourceCode\\3rd\\zlib\\zlib1.dll\" \"Build\\" + szDirName + "\\ServerRelease\"")
        os.system("copy \"SourceCode\\3rd\\DirectX9\\Bin\\x86\\d3dx9_36.dll\" \"Build\\" + szDirName + "\\ServerRelease\"")
        os.system("copy \"SourceCode\\dbghelp.dll\" \"Build\\" + szDirName + "\\ServerRelease\"")
        os.system("copy \"SourceCode\\3rd\\GMC\\Release\\*.dll\" \"Build\\" + szDirName + "\\ServerRelease\"")
        os.system("MD \"Build\\" + szDirName + "\\ServerRelease\\Microsoft.VC80.CRT\"")
        os.system("copy \"SourceCode\\3rd\\GMC\\Release\\Microsoft.VC80.CRT\\*.*\" \"Build\\" + szDirName + "\\ServerRelease\"")

        os.system("copy \"SourceCode\\3rd\\MySQL\\lib\\opt\\libmysql.dll\" \"Build\\" + szDirName + "\\ServerFinal\"")
        os.system("copy \"SourceCode\\3rd\\zlib\\zlib1.dll\" \"Build\\" + szDirName + "\\ServerFinal\"")
        os.system("copy \"SourceCode\\3rd\\DirectX9\\Bin\\x86\\d3dx9_36.dll\" \"Build\\" + szDirName + "\\ServerFinal\"")
        os.system("copy \"SourceCode\\dbghelp.dll\" \"Build\\" + szDirName + "\\ServerFinal\"")
        os.system("copy \"SourceCode\\3rd\\GMC\\Release\\*.dll\" \"Build\\" + szDirName + "\\ServerFinal\"")
        os.system("MD \"Build\\" + szDirName + "\\ServerFinal\\Microsoft.VC80.CRT\"")
        os.system("copy \"SourceCode\\3rd\\GMC\\Release\\Microsoft.VC80.CRT\\*.*\" \"Build\\" + szDirName + "\\ServerFinal\"")

        # Create the Debug server update package
        os.system("md Build\\" + szDirName + "\\ServerDebug\\SQLUpdate")
        os.system("xcopy Build\\" + szDirName + "\\GameData\\*.* Build\\" + szDirName + "\\ServerDebug\\ /E/Y")
        os.system("xcopy SvrUpdate\\*.* Build\\" + szDirName + "\\ServerDebug /E/Y")
        os.system("del Build\\" + szDirName + "\\ServerDebug\\UpdateBishop.ini /Q")
        os.system("xcopy SourceCode\\SQL\\SQLUpdate\*.* Build\\" + szDirName + "\\ServerDebug\\SQLUpdate /E/Y")

        localCurrDir = os.getcwd()              # Save the current working directory
        os.chdir("Build\\" + szDirName + "\\ServerDebug")                 # Enter the specified directory
        os.system("FTSvrUpdate.exe make " + szVersion)
        os.chdir(localCurrDir)                  # Return to the previous working directory

        # Create the Final Release server update package
        os.system("md Build\\" + szDirName + "\\ServerFinal\\SQLUpdate")
        os.system("xcopy Build\\" + szDirName + "\\GameData\\*.* Build\\" + szDirName + "\\ServerFinal\\ /E/Y")
        os.system("xcopy SvrUpdate\\*.* Build\\" + szDirName + "\\ServerFinal /E/Y")
        os.system("del Build\\" + szDirName + "\\ServerFinal\\UpdateBishop.ini /Q")
        os.system("xcopy SourceCode\\SQL\\SQLUpdate\*.* Build\\" + szDirName + "\\ServerFinal\\SQLUpdate /E/Y")

        localCurrDir = os.getcwd()              # Save the current working directory
        os.chdir("Build\\" + szDirName + "\\ServerFinal")                 # Enter the specified directory
        os.system("FTSvrUpdate.exe make " + szVersion)
        os.chdir(localCurrDir)                  # Return to the previous working directory

def GenerateServerMap():
    localCurrDir = os.getcwd()              # Save the current working directory
    os.chdir("MapGen")                 # Enter the specified directory
    bprint("TerrainForServer.exe ..\\Build\\" + szDirName + "\\GameData\\GameData ..\\Build\\Data ..\\Build\\" + szDirName + "\\GameData")
    os.system("TerrainForServer.exe ..\\Build\\" + szDirName + "\\GameData\\GameData ..\\Build\\Data ..\\Build\\" + szDirName + "\\GameData")
    os.chdir(localCurrDir)                  # Return to the previous working directory
    
## Get the database backup from machine 2
def BackupDatabase():
    global SVN_SRC_REV
    
    DB_SVR_IP = "192.168.10.2"
    DB_USER_NAME = "root"
    DB_PWD = "feitian"

    PAYSYS_DB_FILE = "SourceCode\\SQL\\FTPaysys-MySQL.sql"
    BISHOP_DB_FILE = "SourceCode\\SQL\\FTBishop-MySQL.sql"
    GAMEDB_DB_FILE = "SourceCode\\SQL\\FTGameDB-MySQL.sql"
    FTSVRLOG_DB_FILE = "SourceCode\\SQL\\FTServerLog-MySQL.sql"
    KINGLOG_DB_FILE = "SourceCode\\SQL\\KingFTLogDB-MySQL.sql"

    bprint("从2号机获取数据库备份")
    os.popen("mysqldump --host=" + DB_SVR_IP + " --user=" + DB_USER_NAME + " --password=" + DB_PWD + " --lock-all-tables --add-drop-database --add-drop-table --add-locks --skip-dump-date --result-file=" + PAYSYS_DB_FILE + " --no-data -R \"FTPaysys\"")
    os.popen("mysqldump --host=" + DB_SVR_IP + " --user=" + DB_USER_NAME + " --password=" + DB_PWD + " --lock-all-tables --add-drop-database --add-drop-table --add-locks --skip-dump-date --result-file=" + BISHOP_DB_FILE + " --no-data -R \"FTBishop\"")
    os.popen("mysqldump --host=" + DB_SVR_IP + " --user=" + DB_USER_NAME + " --password=" + DB_PWD + " --lock-all-tables --add-drop-database --add-drop-table --add-locks --skip-dump-date --result-file=" + GAMEDB_DB_FILE + " --no-data -R \"FTGameDB\"")
    os.popen("mysqldump --host=" + DB_SVR_IP + " --user=" + DB_USER_NAME + " --password=" + DB_PWD + " --lock-all-tables --add-drop-database --add-drop-table --add-locks --skip-dump-date --result-file=" + FTSVRLOG_DB_FILE + " --no-data -R \"FTServerLog\"")
    os.popen("mysqldump --host=" + DB_SVR_IP + " --user=" + DB_USER_NAME + " --password=" + DB_PWD + " --lock-all-tables --add-drop-database --add-drop-table --add-locks --skip-dump-date --result-file=" + KINGLOG_DB_FILE + " --no-data -R \"KingFTLogDB\"")
    if not os.path.exists(PAYSYS_DB_FILE):
        bprint("fatal error : 备份数据库文件FTPaysys-MySQL.sql失败！")
    if not os.path.exists(BISHOP_DB_FILE):
        bprint("fatal error : 备份数据库文件FTBishop-MySQL.sql失败！")
    if not os.path.exists(GAMEDB_DB_FILE):
        bprint("fatal error : 备份数据库文件FTGameDB-MySQL.sql失败！")
    if not os.path.exists(FTSVRLOG_DB_FILE):
        bprint("fatal error : 备份数据库文件FTServerLog-MySQL.sql失败！")
    if not os.path.exists(KINGLOG_DB_FILE):
        bprint("fatal error : 备份数据库文件KingFTLogDB-MySQL.sql失败！")

    os.popen("MD Build\\" + szDirName + "\\DBBackup")
    os.popen("Copy " + PAYSYS_DB_FILE + " Build\\" + szDirName + "\\DBBackup\\FTPaysys-MySQL.sql")
    os.popen("Copy " + BISHOP_DB_FILE + " Build\\" + szDirName + "\\DBBackup\\FTBishop-MySQL.sql")
    os.popen("Copy " + GAMEDB_DB_FILE + " Build\\" + szDirName + "\\DBBackup\\FTGameDB-MySQL.sql")
    os.popen("Copy " + FTSVRLOG_DB_FILE + " Build\\" + szDirName + "\\DBBackup\\FTServerLog-MySQL.sql")
    os.popen("Copy " + KINGLOG_DB_FILE + " Build\\" + szDirName + "\\DBBackup\\KingFTLogDB-MySQL.sql")

## Process client code files
def Process_Client():
    global szDirName
    global SVN_SRC_REV
    global SVN_DATA_REV
    global SVN_GD_REV
    global ANCHOR_LIST
    global IsGDC
    global IsTgpData
    global IsTgpGd
    global szLogFile
    
    if SVN_SRC_REV or SVN_DATA_REV or SVN_GD_REV:
        if SVN_SRC_REV:
            localDictClient = { 'anchor': 'PROCESS_CLIENT_FILES','name': '处理客户端相关文件','string': '正在处理客户端相关文件...'}
            ANCHOR_LIST.append(localDictClient)
            bprint("正在处理客户端相关文件...")
            # Copy built files
            os.system("MD \"Build\\" + szDirName + "\\ClientDebug\"")
            os.system("copy \"SourceCode\\Bin\\Debug\\Feitian2D.exe\" \"Build\\" + szDirName + "\\ClientDebug\"")

            os.system("MD \"Build\\" + szDirName + "\\ClientRelease\"")
            os.system("copy \"SourceCode\\Bin\\Release\\Feitian2R.exe\" \"Build\\" + szDirName + "\\ClientRelease\Feitian.exe")

            os.system("MD \"Build\\" + szDirName + "\\ClientFinal\"")
            os.system("copy \"SourceCode\\Bin\\Final Release\\Feitian.exe\" \"Build\\" + szDirName + "\\ClientFinal\Feitian.exe")
            os.system("copy \"Misc\\BugRpt.exe\" \"Build\\" + szDirName + "\\ClientFinal\BugRpt.exe")
#            os.system("copy \"SourceCode\\Bin\\Final Release\\BugRpt.exe\" \"Build\\" + szDirName + "\\ClientFinal\BugRpt.exe")

            #Add UPX Shell
            if bAddShell:
                os.system("UPX\\upx.exe --force --best --compress-icons=0 Build\\" + szDirName + "\\ClientFinal\\Feitian.exe")

            # Copy related dynamic libraries
            os.system("copy \"SourceCode\\3rd\\fmodex\\*.dll\" \"Build\\" + szDirName + "\\ClientDebug\"")
            os.system("copy \"SourceCode\\3rd\\PhysX\\bin\\win32\\*.dll\" \"Build\\" + szDirName + "\\ClientDebug\"")
            os.system("copy \"SourceCode\\3rd\\zlib\\zlib1.dll\" \"Build\\" + szDirName + "\\ClientDebug\"")
            os.system("copy \"SourceCode\\3rd\\DirectX9\\Bin\\x86\\d3dx9d_36.dll\" \"Build\\" + szDirName + "\\ClientDebug\"")
            os.system("copy \"SourceCode\\msvcp80d.dll\" \"Build\\" + szDirName + "\\ClientDebug\"")
            os.system("copy \"SourceCode\\msvcr80d.dll\" \"Build\\" + szDirName + "\\ClientDebug\"")
            os.system("copy \"SourceCode\\Microsoft.VC80.DebugCRT.manifest\" \"Build\\" + szDirName + "\\ClientDebug\"")
            os.system("copy \"SourceCode\\dbghelp.dll\" \"Build\\" + szDirName + "\\ClientDebug\"")

            os.system("copy \"SourceCode\\3rd\\fmodex\\*.dll\" \"Build\\" + szDirName + "\\ClientRelease\"")
            os.system("copy \"SourceCode\\3rd\\PhysX\\bin\\win32\\*.dll\" \"Build\\" + szDirName + "\\ClientRelease\"")
            os.system("copy \"SourceCode\\3rd\\zlib\\zlib1.dll\" \"Build\\" + szDirName + "\\ClientRelease\"")
            os.system("copy \"SourceCode\\3rd\\DirectX9\\Bin\\x86\\d3dx9_36.dll\" \"Build\\" + szDirName + "\\ClientRelease\"")
            os.system("copy \"SourceCode\\msvcp80.dll\" \"Build\\" + szDirName + "\\ClientRelease\"")
            os.system("copy \"SourceCode\\msvcr80.dll\" \"Build\\" + szDirName + "\\ClientRelease\"")
            os.system("copy \"SourceCode\\Microsoft.VC80.CRT.manifest\" \"Build\\" + szDirName + "\\ClientRelease\"")
            os.system("copy \"SourceCode\\dbghelp.dll\" \"Build\\" + szDirName + "\\ClientRelease\"")

            os.system("copy \"SourceCode\\3rd\\fmodex\\*.dll\" \"Build\\" + szDirName + "\\ClientFinal\"")
            os.system("copy \"SourceCode\\3rd\\PhysX\\bin\\win32\\*.dll\" \"Build\\" + szDirName + "\\ClientFinal\"")
            os.system("copy \"SourceCode\\3rd\\zlib\\zlib1.dll\" \"Build\\" + szDirName + "\\ClientFinal\"")
            os.system("copy \"SourceCode\\3rd\\DirectX9\\Bin\\x86\\d3dx9_36.dll\" \"Build\\" + szDirName + "\\ClientFinal\"")
            os.system("copy \"SourceCode\\msvcp80.dll\" \"Build\\" + szDirName + "\\ClientFinal\"")
            os.system("copy \"SourceCode\\msvcr80.dll\" \"Build\\" + szDirName + "\\ClientFinal\"")
            os.system("copy \"SourceCode\\Microsoft.VC80.CRT.manifest\" \"Build\\" + szDirName + "\\ClientFinal\"")
            os.system("copy \"SourceCode\\dbghelp.dll\" \"Build\\" + szDirName + "\\ClientFinal\"")

        os.system("DEL Misc\\Launcher.ini")
        os.system("ECHO [Update]" + " > Misc\\Launcher.ini")
        os.system("ECHO UpdateServer=ft.autoupdate.kingsoft.com" + " >> Misc\\Launcher.ini")
        os.system("ECHO UpdateFolder=ft" + " >> Misc\\Launcher.ini")
        os.system("ECHO CurrentVersion=" + str(nBuildNumber) + " >> Misc\\Launcher.ini")

        # Copy configuration files
        os.system("copy Misc\\Launcher.exe Build\\" + szDirName + "\\ClientDebug\\")
        os.system("copy Misc\\Launcher.exe Build\\" + szDirName + "\\ClientRelease\\")
        os.system("copy Misc\\Launcher.exe Build\\" + szDirName + "\\ClientFinal\\")

        os.system("copy Misc\\Launcher.ini Build\\" + szDirName + "\\ClientDebug\\")
        os.system("copy Misc\\Launcher.ini Build\\" + szDirName + "\\ClientRelease\\")
        os.system("copy Misc\\Launcher.ini Build\\" + szDirName + "\\ClientFinal\\")

        os.system("copy Misc\\CustomerSurvey.exe Build\\" + szDirName + "\\ClientDebug\\")
        os.system("copy Misc\\CustomerSurvey.exe Build\\" + szDirName + "\\ClientRelease\\")
        os.system("copy Misc\\CustomerSurvey.exe Build\\" + szDirName + "\\ClientFinal\\")

        # Create the data directory under the program directory
        os.popen("md Build\\" + szDirName + "\\ClientFinal\\Data")

        # Package client Data resources
        if SVN_DATA_REV and IsTgpData:
            bprint("打包Data资源")
            localCurrDir = os.getcwd()      # Save the current working directory
            os.chdir("Build")               # Enter the specified directory
            os.system("tgp.exe create Data")        # Package Data
            if os.path.exists("Data.tgp"):
                bprint("成功打包Data资源")
            else:
                bprint("fatal error:打包Data资源失败!")
            os.system("move Data.tgp " + szDirName + "\\ClientFinal\\Data")
            os.chdir(localCurrDir)          # Return to the previous working directory

            ## copy empty patch file
            os.system("copy Misc\\Patch.tgp Build\\" + szDirName + "\\ClientFinal\\Data")
            
        # Build client GameData resources
        if SVN_GD_REV:
            if IsGDC:
                bprint("调用GDC编译GameData资源")
                os.system("copy SourceCode\\bin\\debug\\gdc.exe Build\\ /Y")
                localCurrDir = os.getcwd()      # Save the current working directory
                localGdcDir = "Build"
                os.chdir(localGdcDir)           # Enter the local GameData directory to build
                os.system("gdc.exe " + szDirName + "\\GameData\\GameData")           # Run the GameData build command
                os.system("move FTGameData.* " + szDirName + "\\GameData\\GameData");
                os.chdir(localCurrDir)          # Return to the previous working directory
                os.system("move Build\\gdc.* " + szDirName + "\\GameData\\GameData")
                bprint("成功编译GameData数据")
                
            if IsTgpGd:
                # Package client GameData
                bprint("打包GameData资源")
                localCurrDir = os.getcwd()              # Save the current working directory
                localGdTgpDir = "Build\\" + szDirName + "\\GameData"
                os.chdir(localGdTgpDir)                 # Enter the specified directory
                os.system("..\\..\\tgp.exe create GameData")    # Package GameData
                if os.path.exists("GameData.tgp"):
                    bprint("成功打包GameData资源")
                else:
                    bprint("fatal error:打包GameData资源失败!")
                os.system("move GameData.tgp ..\\ClientFinal\\Data")
                os.chdir(localCurrDir)                  # Return to the previous working directory

## Run NSIS to generate the installer
def Nsis_Package():
    bprint("生成客户端安装包")
    os.popen("MD Build\\" + szDirName + "\\Install")

    localCurrDir = os.getcwd()              # Save the current working directory

    os.chdir("Build\\" + szDirName + "\\ClientFinal")
    os.system("copy ..\\..\\..\\Misc\\feitian.nsi .")
    os.system("copy ..\\..\\..\\Misc\\SimpleService.nsi .")
    os.system("copy ..\\..\\..\\Misc\\install.ico .")
    os.system("copy ..\\..\\..\\Misc\\EULA.zhCN.txt .")
    os.system("md 3rd")
    os.system("copy ..\\..\\..\\Misc\\3rd\\*.* 3rd\\")

    # Update the installer version
    os.system("echo !define PRODUCT_VERSION \"" + BASE_VERSION + "." + str(nBuildNumber) + "\" > Version.nsh")

    os.system("makensis.exe feitian.nsi")
    os.system("move FeiTianSetup.exe ..\\Install")
    os.system("del feitian.nsi")
    os.system("del SimpleService.nsi")
    os.system("del install.ico")
    os.system("del EULA.zhCN.txt")
    os.system("del version.nsh")
    os.system("rd 3rd /s /q")

    os.chdir(localCurrDir)                  # Return to the previous working directory

    if os.path.exists("Build\\" + szDirName + "\\Install\\FeiTianSetup.exe"):
        bprint("成功生成客户端安装包!")
    else:
        bprint("fatal error: 生成客户端安装包失败!")

                
## Merge StringTable
def Merge_StringTable():
    global szDirName
    global SVN_SRC_LOCATION
    global SVN_SRC_REV
    global SVN_GD_REV
    global SVN_GD_LOCATION
    global szLogFile
    global ClientIsCompile

    if SVN_SRC_LOCATION and ClientIsCompile:
        # SysStringTable-All.txt is generated by the build, so merge StringTable only when client source was built
        CODE_DEF_FILE = "SysStringTable-All.txt"
        DESIGN_DEF_FILE = "SysStringTable-Design.txt"
        RESULT_FILE = "SysStringTable.txt"

        bprint("合并 StringTable")
        CodeDefFile = 'SourceCode\\Src\\FTUserNetLib\\' + CODE_DEF_FILE
        DesignDefFile = 'Build\\' + szDirName + '\\GameData\\GameData\\' + DESIGN_DEF_FILE

        ResultFile = 'Build\\' + szDirName + '\\GameData\\GameData\\' + RESULT_FILE
        GenStringTable(CodeDefFile, DesignDefFile, ResultFile)
        os.popen('copy ' + ResultFile + ' Build\\' + szDirName + '\\GameData\\GameData\\0804\\' + RESULT_FILE)
        os.popen('copy '+ CodeDefFile + ' Build\\' + szDirName + '\\GameData\\GameData\\')
        if SVN_SRC_REV == 'head' and SVN_GD_REV == 'head' and BUILDER_TYPE != "test":
            bprint('提交 StringTable 至 SVN 库')
            if SVN_GD_LOCATION:
                bprint('svn co ' + SVN_GD_LOCATION + '/GameData' + ' -r ' + SVN_GD_REV + ' GameData\\')
                os.popen('svn co ' + SVN_GD_LOCATION + '/GameData' + ' -r ' + SVN_GD_REV + ' GameData\\')
            os.popen('copy ' + ResultFile + ' ' + 'GameData\\ >> ' + szLogFile)
            os.popen('copy ' + DesignDefFile + ' ' + 'GameData\\ >> ' + szLogFile)
            os.popen('copy ' + ResultFile + ' ' + 'GameData\\0804\\ >> ' + szLogFile)
            os.popen('svn commit GameData -m \"Generated by Auto Build\" >> ' + szLogFile)
            os.popen('IF EXIST GameData RD GameData /s /q')
        
def SubmitToTrac():
    global szVersion
    
    # Add the version number to the Trac database
    try:
        conn = MySQLdb.connect(host="192.168.10.5",user="root",passwd="root",db="trac",charset="utf8") 
        try:
            cursor = conn.cursor()
            strDescription = "Auto Build"
            sqlstr = "Insert Into version(name,time,description) values('" + szVersion + "',UNIX_TIMESTAMP(),'" + strDescription + "')"
            if BUILDER_TYPE != "test":
                nResultCount = cursor.execute(sqlstr)
            conn.commit()
            cursor.close()
            bprint("向Trac数据库插入新版本号成功!")
        finally:
            conn.close()
    except Exception,ex:
        print Exception,":",ex

## Analyze batch output logs and generate HTML
def Generate_HtmlFile():
    global SVN_SRC_LOCATION
    global SVN_SRC_REV
    global nErrorCount
    global nWarningCount
    global szLogFile
    global ANCHOR_LIST

    nErrorCount = 0
    nWarningCount = 0
    try:
        file = open(szHtmlFile,"w")
        try:
            file.write("<html>\n<head>\n</head>\n<body>\n")
            file.write(szLogFile + "<br>\n")
            file.write("<br>" + "Log Section List:<br>\n")
            index = 1
            for a in ANCHOR_LIST:
                file.write(str(index) + ". <a href=\"#" + a['anchor'] + "\">" + a['name'] + "</a><br>\n")
                index += 1
            file.write("<br>\n")
            
            fh = open(szLogFile,"r")
            for szLine in fh.readlines():
                szLine = string.strip(szLine,"\n")
                error1 = string.find(szLine, " : error ")
                error2 = string.find(szLine, "fatal error")
                error3 = string.find(szLine, "Commit failed")
                warning = string.find(szLine, ": warning ")
                if error1 >= 0 or error2 >= 0:
                    szNewLine = "<font color=\"#FF0000\">" + szLine + "</font><br>\n"
                    nErrorCount = nErrorCount + 1
                elif warning >= 0:
                    szNewLine = "<font color=\"#0000FF\">" + szLine + "</font><br>\n"
                    nWarningCount = nWarningCount + 1
                else:
                    bFound = False
                    for a in ANCHOR_LIST:
                        if a['string'] == szLine:
                            szNewLine = "<br><b><a name=\"" + a['anchor'] + "\">" + szLine + "</a></b><br>\n"
                            bFound = True
                    if not bFound:
                        szNewLine = szLine + "<br>\n"
                file.write(szNewLine)
            fh.close()
            file.write("</body></html>")
        finally:
            file.close()
            bprint("生成HTML文件成功!")
    except IOError:
        bprint("生成HTML文件失败!")
        #os._exit(0)

## Generate and send mail
def Send_Mail():
    global BUILDER_TYPE
    global ServerName
    global nErrorCount
    global nWarningCount
    global szHtmlFile
    global szDirName
    global SVN_SRC_REV
    global SVN_DATA_REV
    global SVN_GD_REV

    localPassword = "feitian1!"
    
    ## Mail recipients for test builds
    TEST_MAILTO_LIST = ['zhujianqiu@tracegames.net']
    ## Mail recipients for successful builds
    SUCC_MAILTO_LIST = ['alexjin@tracegames.net',
                        'lance@tracegames.net',
                        'lowieliang@tracegames.net',
                        'sunying@kingsoft.com',
                        'wangqi@kingsoft.com',
                        'wangjun@tracegames.net',
                        'zhangdong@tracegames.net',
                        'caca@tracegames.net',
                        'zhujianqiu@tracegames.net'
                       ]
    ## Mail recipients for failed builds
    FAIL_MAILTO_LIST = ['alexjin@tracegames.net',
                        'lowieliang@tracegames.net',
                        'wangjun@tracegames.net',
                        'zhangdong@tracegames.net',
                        'zhujianqiu@tracegames.net',
                        'wangjun@tracegames.net'
                       ]
    try:
        mail = open("mail.html","w")
        try:
            SendMailComStr = ""
            if nErrorCount == 0:
                szNewLine = "<html><b>本次编译成功!</b><br><br>"
                szNewLine+= "下载地址: <a href=\"\\\\" + ServerName + "\\Build\\" + szDirName
                szNewLine+= "\">\\\\" + ServerName + "\\Build\\" + szDirName + "</a><br><br>"
                szNewLine+= "Log文件: <a href=\"\\\\" + ServerName + "\\" + szHtmlFile
                szNewLine+= "\">\\\\" + ServerName + "\\" + szHtmlFile + "</a>"

                mail.write(szNewLine)
                mail.write("<br><br>服务端和客户端的安装教程:<br>")
                mail.write("&nbsp&nbsp<a href=\"\\\\" + ServerName + "\\Build\\ServerGuide.txt\">服务端教程</a><br>")
                mail.write("&nbsp&nbsp<a href=\"\\\\" + ServerName + "\\Build\\ClientGuide.txt\">客户端教程</a><br>")
                szNewLine = "<br>本次编译中产生了 " + str(nWarningCount) + " 警告 和 " + str(nErrorCount) + " 错误."
                mail.write(szNewLine)
                if SVN_SRC_REV:
                    szNewLine = "<br><a href=\"\\\\" + ServerName + "\\Logs\\" + szDirName + "_src_change_history.log\">本日 Source 更新日志</a>"
                    mail.write(szNewLine)
                if SVN_DATA_REV:
                    szNewLine = "<br><a href=\"\\\\" + ServerName + "\\Logs\\" + szDirName + "_data_change_history.log\">本日 Data 更新日志</a>"
                    mail.write(szNewLine)
                if SVN_GD_REV:
                    szNewLine = "<br><a href=\"\\\\" + ServerName + "\\Logs\\" + szDirName + "_gamedata_change_history.log\">本日 GameData 更新日志</a>"
                    mail.write(szNewLine)
                mail.write("<br><br>The mail is generated by AutoBuild v2.0, 2009")

                SendMailComStr = "febootimail -SMTP \"192.168.10.3\" -AUTH LOGIN -USER \"VersionReleaser\""
                SendMailComStr += " -PASS \"" + localPassword +  "\" -CHARSET GB2312 -FROM \"VersionReleaser@tracegames.net\""
                SendMailComStr += " -BCC \""
                if BUILDER_TYPE == "test":
                    SendMailComStr += ";".join(TEST_MAILTO_LIST)
                else:
                    SendMailComStr += ";".join(SUCC_MAILTO_LIST)
                SendMailComStr += "\" -SUBJECT \"Auto Build Report " + szVersion + "\""
                SendMailComStr += " -HTMLFILE \"mail.html\""
            else:
                szNewLine  = "<html><b><font color=\"#FF0000\">本次编译失败!</font></b><br><br>"
                szNewLine += "下载地址: <a href=\"\\\\" + ServerName + "\\Build\\" + szDirName
                szNewLine += "\">\\\\" + ServerName + "\\Build\\" + szDirName + "</a><br><br>"
                szNewLine += "Log文件: <a href=\"\\\\" + ServerName + "\\" + szHtmlFile + "\">\\\\" + ServerName + "\\" + szHtmlFile + "</a>"
                mail.write(szNewLine)
                szNewLine = "<br>本次编译中产生了 " + str(nWarningCount) + " 警告和 " + str(nErrorCount) + " 错误."
                mail.write(szNewLine)
                if SVN_SRC_REV:
                    szNewLine = "<br><a href=\"\\\\" + ServerName + "\\Logs\\" + szDirName + "_src_change_history.log\">本日 Source 更新日志</a>"
                    mail.write(szNewLine)
                if SVN_DATA_REV:
                    szNewLine = "<br><a href=\"\\\\" + ServerName + "\\Logs\\" + szDirName + "_data_change_history.log\">本日 Data 更新日志</a>"
                    mail.write(szNewLine)
                if SVN_GD_REV:
                    szNewLine = "<br><a href=\"\\\\" + ServerName + "\\Logs\\" + szDirName + "_gamedata_change_history.log\">本日 GameData 更新日志</a>"
                    mail.write(szNewLine)
                mail.write("<br><br>The mail is generated by AutoBuild v2.0, 2009")

                SendMailComStr  = "febootimail -SMTP \"192.168.10.3\" -AUTH LOGIN -USER \"VersionReleaser\""
                SendMailComStr += " -PASS \"" + localPassword +  "\" -CHARSET GB2312 -FROM \"VersionReleaser@tracegames.net\""
                SendMailComStr += " -BCC \""
                if BUILDER_TYPE == "test":
                    SendMailComStr += ";".join(TEST_MAILTO_LIST)
                else:
                    SendMailComStr += ";".join(FAIL_MAILTO_LIST)
                SendMailComStr += "\" -SUBJECT \"Auto Build Report\""
                SendMailComStr += " -HTMLFILE \"mail.html\""
        finally:
            mail.close()
            os.popen( SendMailComStr )
            bprint("发送邮件成功!")
    except IOError:
        bprint("发送邮件失败!")
        # os._exit(0)

if __name__ == '__main__':
    # Process command-line arguments
    CmdLine_Process()

    # Initialize
    Init()
'''
if __name__ == '__main__':
    # Process command-line arguments
    CmdLine_Process()

    # Initialize
    Init()

    # Version control

    # Get and store the latest revision
    Get_New_Revision()

    # Update Src, Data and GD from SVN
    SvnUpdate()

    # Generate server maps
    GenerateServerMap()

    # Process server files
    Process_Server()

    # Get the database backup from machine 2
    BackupDatabase()

    # Merge StringTable
    Merge_StringTable()

    # Process client files
    Process_Client()

    # Submit the version to Trac
    SubmitToTrac()
    
    # Create a standalone installer
    if IsInstall:
	    Nsis_Package()

    # Create an update package

    # Finish processing
    bprint("正在进行收尾处理...")
    localDictEnd = {'anchor': 'END_OPERATION','name': '收尾处理','string': '正在进行收尾处理...'}
    ANCHOR_LIST.append(localDictEnd)

    # Copy PDB files
    os.system("MD \"Build\\" + szDirName + "\\DebugPDB\"")
    os.system("copy \"SourceCode\\Bin\\Debug\\*.exe\" \"Build\\" + szDirName + "\\DebugPDB\"")
    os.system("copy \"SourceCode\\Bin\\Debug\\*.pdb\" \"Build\\" + szDirName + "\\DebugPDB\"")
    os.system("copy \"SourceCode\\Bin\Debug\\*.ilk\" \"Build\\" + szDirName + "\\DebugPDB\"")
    os.system("copy \"SourceCode\\Bin\\Debug\\*.exp\" \"Build\\" + szDirName + "\\DebugPDB\"")
    os.system("copy \"SourceCode\\Bin\\Debug\\*.lib\" \"Build\\" + szDirName + "\\DebugPDB\"")

    os.system("MD \"Build\\" + szDirName + "\\ReleasePDB\"")
    os.system("copy \"SourceCode\\Bin\\Release\\*.exe\" \"Build\\" + szDirName + "\\ReleasePDB\"")
    os.system("copy \"SourceCode\\Bin\\Release\\*.pdb\" \"Build\\" + szDirName + "\\ReleasePDB\"")
    os.system("copy \"SourceCode\\Bin\\Release\\*.ilk\" \"Build\\" + szDirName + "\\ReleasePDB\"")
    os.system("copy \"SourceCode\\Bin\\Release\\*.exp\" \"Build\\" + szDirName + "\\ReleasePDB\"")
    os.system("copy \"SourceCode\\Bin\\Release\\*.lib\" \"Build\\" + szDirName + "\\ReleasePDB\"")

    os.system("MD \"Build\\" + szDirName + "\\FinalPDB\"")
    os.system("copy \"SourceCode\\Bin\\Final Release\\*.exe\" \"Build\\" + szDirName + "\\FinalPDB\"")
    os.system("copy \"SourceCode\\Bin\\Final Release\\*.pdb\" \"Build\\" + szDirName + "\\FinalPDB\"")
    os.system("copy \"SourceCode\\Bin\\Final Release\\*.ilk\" \"Build\\" + szDirName + "\\FinalPDB\"")
    os.system("copy \"SourceCode\\Bin\\Final Release\\*.exp\" \"Build\\" + szDirName + "\\FinalPDB\"")
    os.system("copy \"SourceCode\\Bin\\Final Release\\*.lib\" \"Build\\" + szDirName + "\\FinalPDB\"")

    bprint("自动生成版本 " + szVersion + " 成功!")

    # Analyze batch output logs and generate HTML
    Generate_HtmlFile()
    
    # Send mail
    Send_Mail()
'''