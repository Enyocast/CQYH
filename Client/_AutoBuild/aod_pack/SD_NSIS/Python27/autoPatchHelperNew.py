# -*- coding = gbk -*-
import re
import os,sys,getopt
import time
import ConfigParser
import subprocess
import string
import xml.dom.minidom
#from xml.etree import ElementTree
import logging
import traceback
import locale
import threading,random
import contextlib
import md5
#from xml.etree import ElementTree # part of python distribution
#from ElementTree import SimpleXMLTreeBuilder # part of your codebase
#ElementTree.XMLTreeBuilder = SimpleXMLTreeBuilder.TreeBuilder

reload(sys) 
sys.setdefaultencoding('utf8') 

newlines = ['\n', '\r\n', '\r']
def unbuffered(proc, stream='stdout'):
    stream = getattr(proc, stream)
    with contextlib.closing(stream):
        while True:
            out = []
            last = stream.read(1)
            # Don't loop forever
            if last == '' and proc.poll() is not None:
                break
            while last not in newlines:
                # Don't loop forever
                if last == '' and proc.poll() is not None:
                    break
                out.append(last)
                last = stream.read(1)
            out = ''.join(out)
            yield out

class FlushFile(object):
    """Write-only flushing wrapper for file-type objects."""
    def __init__(self, f):
        self.f = f
    def write(self, x):
        self.f.write(x)
        self.f.flush()
class cmdProcessThread(threading.Thread):
    def __init__(self,cmdline):
        threading.Thread.__init__(self);
        self.thread_stop = False
        self._cmdLine = cmdline
    def run(self):
        self._outMsg = sys.stdout.read()
        print "这是线程中"+self._outMsg
        #subprocess.call(self._cmdLine);
    def stop(self):
        self.thread_stop = True
#================================
#===================================
class userException(Exception):
    '''异常处理类'''
    def __init__(self,errMsg):
        Exception.__init__(self)
        self.errMsg = errMsg
#================================
#===================================
class strDecode():
    '''将utf-8编码的字符unicode化，防止中文乱码'''
    def __init__(self,str):
        type = sys.getfilesystemencoding()
        if isinstance(str,unicode):
            self.unicodeStr = str.encode('gb2312')
        else:
            self.unicodeStr = str.decode('utf8').encode('gb2312')
#===============================================================================
# class strEncode():
#     '''将unicode字符gbk化'''
#     def __init__(self,str):
#         self.ansiStr = str.encode('gbk')
#===============================================================================
        

#================================
#==================================
class autoPatch():
    '''核心类，负责文件打包(7z or Zip)，并生成相应volumeInfo.ini文件'''
    def __init__(self,args):
        self._volumeType = ''
        self._volumeName = ''
        self._splitSize = ''
        self._pwd = ''
        self._isDoAll = True
        self._args = args
        self._nsisFileName = ''
        self._srcPath = ''
        self._iniFilePath = ''
        self._version = ''
        self._dataResorcePath = '' 
        self._SevenZipToolPath = ''
        self._WinZipToolPath = ''
        self._volumInfoIni =  ''
        self._volumInfoXML =  ''  
        self._makeNsisPath = ''
        self._makeInstallFile = ''
        self._tempZipName = ''
        #=======================================================================
        # self._nsisFileName = nsisFilePath
        # self._srcPath = os.path.dirname(nsisFilePath) + '\\'
        # self._iniFilePath = self._srcPath + 'settings.ini'
        # self._dataResorcePath = self._srcPath + 'SplitDataResource\*'
        # self._SevenZipToolPath = self._srcPath + 'SD_NSIS\\7za\\7za.exe'
        # self._volumInfoIni = self._srcPath + 'Client\VolumInfo.ini'
        # self._volumInfoXML = self._srcPath + 'SD_NSIS\InstallTool\resource\GameInfoReference.xml'  
        # self._makeNsisPath = self._srcPath + 'SD_NSIS\makensis.exe /V2'
        # self._makeInstallFile = self._srcPath + 'SD_NSIS\InstallTool\InstallMaker.bat '
        # self._tempZipName = self._srcPath + 'tempSplitZip.zip'
        #=======================================================================
        #logging.basicConfig(filename = os.path.join(os.getcwd(), 'autoPath.log'), level = logging.WARN, filemode = 'w', format = '%(asctime)s - %(levelname)s: %(message)s')
        #self._paramDict = {}
    def usage(self):
        '''usage'''
        print str(sys.argv[0])
        print 'usage: [optiona] arg1'
        print 'options:'
        print '    -h, --help        show this help usage message and then exit'
        print '    -p'
    def getCurFuncName(self):
        return sys._getframe().f_code.co_name  #当前函数名
    def isFile7z(self,str):
        return re.match(r'^.*\.7z\.\d{1,6}$',str)
    def isFileZip(self,str):
        return (re.match(r'^.*\.zip$',str) or re.match(r'^.*{1,6}\.cab',str))
    def ClearVolumeOfPath(self,volumeNamePre):
        logging.debug('[ENTER] enter ClearVolumeOfPath')
        logging.debug('the parameter volumeNamePre is :' + str(volumeNamePre))
        files = os.listdir(self._srcPath)
        for file in files:
            file_lists = file.split('.') 
            fileNamePre = '.'.join(file_lists[0:-1])
            fileNameExt = file_lists[-1] 
            if os.path.isdir(file) or len(file_lists) < 2:
                continue
            if len(file_lists) >= 3 and self._volumeType == '7z': 
                #fileNameMid = file_lists[1]
                if fileNamePre == volumeNamePre and self.isFile7z(file):#fileNameMid == '7z' and fileNameExt.isdigit():
                    os.remove(self._srcPath + file)
                    continue
            elif len(file_lists) >= 2 and self._volumeType == 'zip':
                if string.find(str(fileNamePre),str(volumeNamePre)) != -1 and (fileNameExt == 'cab' or fileNameExt == 'zip'):
                    os.remove(self._srcPath + file)
                    continue
        logging.debug('self._volumeType is :' + str(self._volumeType))
        logging.debug('[OUT] out ClearVolumeOfPath')
        return            
    #==================================
    # [Paramter]srcFilePath : the files that need to be packed
    #           packType    :  the pack Type (7z or Zip)
    #           splitSize   : the size of split size
    #           volumeName  : the name of volume name
    #           sevenZipPath : the path of 7za.exe
    #==================================
    def excute_pack(self):
        logger.debug('[ENTER] excute_pack')
        try:
            if self._volumeType == '7z':  
                volumeFileParts = self._volumeName.split('.')
                if len(volumeFileParts) < 3:
                    logger.error('7z分卷包名称 : ' + '%s'%self._volumeName + '错误，请检查！')
                    raise userException('7z volume file name : ' + '%s'%self._volumeName + 'Wrong, please check!')
                    return
                volumeFileName = '.'.join(volumeFileParts[0:-1])  
                if self._pwd == '':
                    cmdLine =  str(self._SevenZipToolPath) + ' a ' + str(self._srcPath) + str(volumeFileName) + ' ' + str(self._dataResorcePath) + '* ' + '-r -t7z -v' + str(self._splitSize)
                else:
                    cmdLine =  str(self._SevenZipToolPath) + ' a -p' + str(self._pwd) + ' ' + str(self._srcPath) + str(volumeFileName) + ' ' + str(self._dataResorcePath) + '* ' + '-r -t7z -v' + str(self._splitSize)
                
                logger.debug('7z分卷压缩 "' + str(self._volumeName) + '" 命令行：' + str(cmdLine))
            
                #===============================================================
                #可以实现输出到屏幕
                subprocess.call(cmdLine)
                #os.system(cmdLine)
                #===============================================================
                cmdLineListFile = str(self._SevenZipToolPath) + ' l ' +  str(self._srcPath) + str(self._volumeName)
                logger.debug("列举压缩包内容命令行：    " + str(cmdLineListFile))
                fileWholePath =  str(self._srcPath) + str(self._volumeName);
                if  not os.path.isdir( fileWholePath) and os.path.isfile(fileWholePath):
                    listProc = subprocess.Popen(cmdLineListFile,stdout = subprocess.PIPE)
                    listFiles = listProc.stdout.read()
                    logger.debug(str(listFiles))
                else:
                    logger.debug("未找到压缩包文件 " + str(fileWholePath) + "或者为目录")
                 
                #===============================================================
                # saveout = sys.stdout                                     
                # fsock = open('out.log', 'w')                             
                # sys.stdout = fsock                                       
                # print 'This message will be logged instead of displayed' 
                # sys.stdout = saveout                                     
                # fsock.close()                           
                #===============================================================
                #proc = cmdProcessThread(cmdLine);
                #proc.start();
                
                #proc.stop();
                
                #(si,so,se) = os.popen3(cmdLine)
                #outMsg = so.read()
                #logger.debug(str(outMsg))
                
                
                #proc = subprocess.Popen(args = cmdLine, stdout = subprocess.PIPE)
                #outMsg = proc.stdout.readlines()
                #subprocess.call(cmdLine)

                #print outMsg
                #logger.debug(str(outMsg))
            elif self._volumeType == 'zip':
                if os.path.isfile(self._tempZipName):
                    os.remove(self._tempZipName)
                volumeFileParts = self._volumeName.split('.')
                if len(volumeFileParts) < 2:
                    logger.error('zip分卷包名称 : ' + '%s'%self._volumeName + '错误，请检查！')
                    raise userException('Zip volume file name : ' + '%s'%self._volumeName + ' Wrong, please check!')
                if self._pwd == '':
                    cmdLine = str(self._WinZipToolPath) + ' -rp ' + str(self._tempZipName) + ' ' + str(self._dataResorcePath) + '*'
                else:
                    cmdLine = str(self._WinZipToolPath) + ' -s' + str(self._pwd) + ' -rp ' + str(self._tempZipName) + ' ' + str(self._dataResorcePath) + '*'
                logger.debug('Zip整包压缩  "' + str(self._tempZipName) + '" 命令行：' + str(cmdLine))
                #===============================================================
                #可以实现输出到屏幕
                subprocess.call(cmdLine)
                #os.system(cmdLine)
                #===============================================================
                #===============================================================
                # outMsg = subprocess.check_output(cmdLine)
                # print outMsg
                # logger.debug( type(outMsg))
                #===============================================================
                #logger.debug(outMsg.decode('gbk','ignore').encode('utf8'))
                volumeFileBaseName = '.'.join(volumeFileParts[0:-1])
                cmdLine = str(self._WinZipToolPath) + ' -ys' + str(string.atoi(self._splitSize) >> 10) + ' ' + str(self._tempZipName) + ' ' + str(self._srcPath) +  str(self._volumeName) 
                logger.debug('Zip分卷压缩  "' + str(self._volumeName) + '" 命令行：' + str(cmdLine))
                subprocess.call(cmdLine)
                #===============================================================
                # outMsg = subprocess.check_output(cmdLine) 
                # print outMsg
                #===============================================================
                #logger.debug(str(outMsg).decode('gbk','ignore').encode('utf8')) 
                cmdLineListFile = str(self._WinZipToolPath) + ' -v ' +  str(self._tempZipName) 
                logger.debug("列举压缩包内容命令行：    " + str(cmdLineListFile))
                fileWholePath =  str(self._tempZipName) ;
                if  not os.path.isdir( fileWholePath) and os.path.isfile(fileWholePath):
                    listProc = subprocess.Popen(cmdLineListFile,stdout = subprocess.PIPE)
                    listFiles = listProc.stdout.read()
                    logger.debug(str(listFiles))
                else:
                    logger.debug("未找到压缩包文件 " + str(fileWholePath) + "或者为目录")    
                if os.path.isfile(self._tempZipName):
                    os.remove(self._tempZipName)
        except userException,e:
            logger.error( str(self._volumeName) + ' 打包失败\r\n'  + e.errMsg + '\r\n' + traceback.format_exc())
            print '[ERROR] ' + strDecode(e.errMsg).unicodeStr + strDecode('\r\n打包 ').unicodeStr +  str(self._volumeName) + strDecode(' 失败，请检查！').unicodeStr
            sys.exit(-1)
        except subprocess.CalledProcessError, e:
            logger.error( str(self._volumeName) + ' 打包失败\r\n'  + e.output.decode('gbk','ignore').encode('utf8') +'\r\n' + traceback.format_exc() )
            print '[ERROR] ' + strDecode(e.output).unicodeStr + '\r\n打包 ' +  str(self._volumeName) + strDecode(' 失败，请检查！').unicodeStr
            print e.output
            sys.exit(-1)
        finally:
            logger.debug('[OUT] excute_pack')    
        return
    #===========================================================================
    # 
    #===========================================================================
    def excute_makeNsis(self):
        logger.debug('[ENTER] enter excute_makeNsis')
        try:
            cmdLine = str(self._makeNsisPath) + ' ' + str(self._nsisFileName)
            logger.debug('编译nsis命令行 ：' + str(cmdLine) )
            #subprocess.call(cmdLine)
            outMsg = subprocess.check_output(cmdLine)
            print outMsg
            logger.debug(str(outMsg).decode('gbk','ignore').encode('utf8'))
        except subprocess.CalledProcessError, e:
            print strDecode('[ERROR]无法使用 ').unicodeStr + str(self._makeNsisPath) + strDecode('编译').unicodeStr + str(self._nsisFileName) + strDecode('文件 \r\n').unicodeStr 
            print e.output
            logger.error('使用' +  str(self._makeNsisPath) +  '编译文件 ' + str(self._nsisFileName) + '失败\r\n'  + e.output.decode('gbk','ignore').encode('utf8') + '\r\n' + traceback.format_exc())
            sys.exit(-1)
            #raise userException('cannot  build ' + str(self._nsisFileName) + 'with ' + str(self._makeNsisPath))
        finally:
            logger.debug('[OUT] out excute_makeNsis')
        return
    #===========================================================================
    # 
    #===========================================================================
    def excute_makeInstallFile(self):
        logger.debug('[ENTER] enter excute_makeInstallFile')
        try:
            cmdLine = str(self._makeInstallFile)
            logger.debug('生成安装文件命令 ：' + str(cmdLine) )
            #subprocess.call(cmdLine)
            outMsg = subprocess.check_output(cmdLine)
            print outMsg
            logger.debug(str(outMsg).decode('gbk','ignore').encode('utf8'))
        except subprocess.CalledProcessError, e:
            print strDecode('[ERROR]安装文件生成文件 ').unicodeStr + str(self._makeInstallFile) + strDecode('不能执行').unicodeStr
            print e.output
            logger.error('安装文件生成文件' +  str(self._makeInstallFile) + '不能执行\r\n'  + e.output.decode('gbk','ignore').encode('utf8') + '\r\n' + traceback.format_exc())
            sys.exit(-1)
            #raise userException('cannot  build ' + str(self._nsisFileName) + 'with ' + str(self._makeNsisPath))
        finally:
            logger.debug('[OUT] out excute_makeInstallFile')
        return
    #===========================================================================
    # 
    #===========================================================================
    def parase_Ini(self):
        logger.debug('[ENTER] enter parase_Ini')
        
        try:
            config = ConfigParser.SafeConfigParser()
            print self._iniFilePath
            config.read(self._iniFilePath)
            self._volumeName = str(config.get("Info", "volumeName")) #.lower();
            self._volumeType = config.get("Info", "volumeType");
            self._pwd = config.get("Info", "password");
            splitSize = config.get("Info", "splitSize");
            tempSplitSize = splitSize;
            if re.match('^[0-9]\d{0,7}\.?\d{0,9}\K$',splitSize,re.IGNORECASE) or re.match('^[0-9]\d{0,7}\.?\d{0,9}\KB$',splitSize,re.IGNORECASE):
                number = float((re.findall(r'\d*\.?\d*', splitSize))[0])
                if number:
                    splitSize = int(number * 1024);
                else:
                    raise userException(str('您设置的分卷包大小为'+ str(tempSplitSize)+'其中包含未知错误，请检查或联系打包工具支持人员！'));
            elif re.match('^[0-9]\d{0,4}\.?\d{0,9}\M$',splitSize,re.IGNORECASE) or re.match('^[0-9]\d{0,4}\.?\d{0,9}\MB$',splitSize,re.IGNORECASE):
                number = float((re.findall(r'\d*\.?\d*', splitSize))[0])
                if number:
                    splitSize = int(number * 1024 * 1024);
                else:
                    raise userException(str('您设置的分卷包大小为'+ str(tempSplitSize)+'其中包含未知错误，请检查或联系打包工具支持人员！'));
                #splitSize = int( re.findall(r'\d+', splitSize)[0]) * 1024 * 1024
            elif re.match('^[0-9]\d{0,1}\.?\d{0,9}\G$',splitSize,re.IGNORECASE) or re.match('^[0-9]\d{0,1}\.?\d{0,9}\GB$',splitSize,re.IGNORECASE):
                number = float((re.findall(r'\d*\.?\d*', splitSize))[0])
                if number:
                    splitSize = int(number * 1024 * 1024 * 1024);
                else:
                    raise userException(str('您设置的分卷包大小为'+ str(tempSplitSize)+'其中包含未知错误，请检查或联系打包工具支持人员！'));
                #splitSize = int( re.findall(r'\.?\d+', splitSize)[0]) * 1024 * 1024 * 1024
            elif not re.match('^[1-9]\d{1,10}$'):
                raise userException('文件'+ str(self._iniFilePath)+' 中有错误 ，导致"分卷包大小"获取不成功，请检查ini文件后再试！')
            self._splitSize = str(splitSize)
            logger.debug('分卷压缩包 大小：' + str(self._splitSize) )
            
            #===================================================================
            # tree  = ElementTree.parse(str(self._iniFilePath))
            # root = tree.getroot()                
            # for child in root:
            #     nodeName = child.tag
            #     nodeText = child.text
            #     if nodeName == 'volumeType':
            #         self._volumeType = nodeText
            #         logger.debug('压缩包 类型：' + str(nodeText) )
            #     elif nodeName == 'volumeName':
            #         self._volumeName = nodeText
            #         logger.debug('压缩包 名称：' + str(nodeText) )
            #     elif nodeName == 'password':
            #         if nodeText == None:
            #             nodeText = ''
            #         self._pwd = nodeText
            #         logger.debug('分卷压缩包 密码：' + str(nodeText) )
            #     elif nodeName == 'splitSize':
            #         if re.match('^[1-9]\d{1,20}\K$',nodeText,re.IGNORECASE) or re.match('^[1-9]\d{1,20}\KB$',nodeText,re.IGNORECASE):
            #             nodeText = int( re.findall(r'\d+', nodeText)[0]) * 1024
            #         elif re.match('^[1-9]\d{1,20}\M$',nodeText,re.IGNORECASE) or re.match('^[1-9]\d{1,20}\MB$',nodeText,re.IGNORECASE):
            #             nodeText = int( re.findall(r'\d+', nodeText)[0]) * 1024 * 1024
            #         elif re.match('^[1-9]\d{1,3}\G$',nodeText,re.IGNORECASE) or re.match('^[1-9]\d{1,3}\GB$',nodeText,re.IGNORECASE):
            #             #print re.findall(r'\d+', nodeText)
            #             nodeText = int( re.findall(r'\d+', nodeText)[0]) * 1024 * 1024 * 1024
            #         elif not re.match('^[1-9]\d{1,20}$'):
            #             raise userException('文件'+ str(self._iniFilePath)+' 中有错误 ，导致"分卷包大小"获取不成功，请检查ini文件后再试！')
            #         self._splitSize = str(nodeText)
            #         logger.debug('分卷压缩包 大小：' + str(self._splitSize) )
            #===================================================================
            #   print child.tag,':',child.text
            print '################' 
#         except Exception, e:
#             print e
#             print  strDecode('[ERROR] 解析ini文件 ' + str(self._iniFilePath) + '出错').unicodeStr
#             logger.error('解析ini文件 ' + str(self._iniFilePath) + '出错\r\n' + str(e) + '\r\n' +  traceback.format_exc())
#             logger.debug('[OUT] out parase_Ini')
#             sys.exit(-1)
        except userException,e:
            print strDecode('[ERROR] An Handled Exception occur : " ' + e.errMsg + ' "').unicodeStr
            logger.error('An Handled Exception occur : " ' + e.errMsg + ' "\r\n' +  traceback.format_exc())
            logger.debug('[OUT] out parase_Ini')
            sys.exit(-1)
        except Exception,e:
            print strDecode('[ERROR] An Unhandled Exception occur: " ' + str(e) + ' "').unicodeStr
            logger.error('An Unhandled Exception occur : " ' + str(e) + ' "\r\n' +  traceback.format_exc())
            logger.debug('[OUT] out parase_Ini')
            sys.exit(-1)
            
        if self._volumeType == None \
            or self._srcPath == None \
            or self._volumeName == None \
            or self._splitSize == None \
            or self._dataResorcePath == None \
            or self._version == None \
            or self._SevenZipToolPath == None \
            or self._volumInfoIni == None \
            or self._volumInfoXML == None : 
            #print strDecode('[ERROR]' + str(self._iniFilePath)+'文件中有错误，导致字段获取不成功，请检查后再试！').unicodeStr
            logger.error(str(self._iniFilePath)+' 文件中有错误')
            raise userException('文件'+ str(self._iniFilePath)+' 中有错误 ，导致字段获取不成功，请检查后再试！')
        logger.debug('[OUT] out parase_Ini')
        return 
    def parseTypeFromName(self):
        logger.debug('[ENTER] enter parseTypeFromName')
        logger.debug('self._volumeName is :' + str(self._volumeName))
        file_lists = self._volumeName.split('.') 
        fileNamePre = file_lists[0:-1]
        fileNameExt = file_lists[-1] 
        if len(file_lists) >= 3 and fileNameExt == '001' and self.isFile7z(self._volumeName):
            self._volumeType = '7z'
        elif len(file_lists) >= 2 and fileNameExt == 'zip' and self.isFileZip(self._volumeName):
            self._volumeType = 'zip'
        logger.debug('self._volumeType is :' + str(self._volumeType))
        logger.debug('[OUT] out parseTypeFromName')
    #===========================================================================
    # 
    #===========================================================================
    def getVolumeFileList(self):
        logger.debug('[ENTER] enter getVolumeFileList')
        fileNameParts = self._volumeName.split('.')
        fileNamePre = '.'.join(fileNameParts[0:-1])
        volumeNameList = []
        if len(fileNameParts) < 2 :
            logger.error('分卷包' + str(self._volumeName) + '名称错误！')
            print strDecode('[ERROR]分卷包名称').unicodeStr + str(self._volumeName) + strDecode('错误，请检查！').unicodeStr
            return
        self.parseTypeFromName()
        if self._volumeType == '7z':
            index = 1
            while True:
                fileNameExt = '%03u'%index
                fileName = str(fileNamePre) + '.' + str(fileNameExt)
                if not os.path.isfile(str(self._srcPath) + str(fileName)):
                    break
                volumeNameList.append(fileName)
                index += 1
        elif self._volumeType == 'zip':
            index = 0
            while True:
                if not os.path.isfile(str(self._srcPath) + str(self._volumeName)):
                    break
                if index == 0:
                    volumeNameList.append(self._volumeName)
                elif index > 0:
                    fileNameMid = '%02u'%index
                    fileNameOld = str(fileNamePre) + '.z' + str(fileNameMid)
                    fileNameNew = str(fileNamePre) + str(fileNameMid) + '.cab'
                    if self._isDoAll:
                        if not os.path.isfile(str(self._srcPath) + str(fileNameOld)):
                            break
                        os.rename(fileNameOld,fileNameNew)
                        volumeNameList.append(fileNameNew)
                    else:
                        if not os.path.isfile(str(self._srcPath) + str(fileNameNew)):
                            break
                        volumeNameList.append(fileNameNew)
                index +=1
        logger.debug('分卷包list：' + str(volumeNameList[:]) )
        logger.debug('[OUT] out getVolumeFileList')
        return volumeNameList
    #===========================================================================
    # 
    #===========================================================================
    def writeVolumInfoFile(self):
        logger.debug('[ENTER] enter writeVolumInfoFile')
        volumeFileList = self.getVolumeFileList()
        if volumeFileList == []:
            logger.error('路径 ' + '%s'%self._srcPath + '下，无所需的' + '%s'%self._volumeName + '压缩包文件')
            print strDecode('[ERROR] 路径').unicodeStr + '%s'%self._srcPath + strDecode('中未找到任何与').unicodeStr + '%s'%self._volumeName + strDecode('有关的分卷压缩包，请检查后再试！').unicodeStr
            logger.debug('[OUT] out writeVolumInfoFile')
            sys.exit(-1)
        iniFilePath = os.path.dirname(self._volumInfoIni)
        if not os.path.isdir(iniFilePath):
            os.mkdir(iniFilePath) 
        cfgFile=ConfigParser.ConfigParser()
        itemNum = 0
        cfgFile.add_section("VolumInfo")
        viFile = open(self._volumInfoIni, 'w+')
        for file in volumeFileList:
            fileWholePath = self._srcPath + file
            if  not os.path.isdir(fileWholePath) and os.path.isfile(fileWholePath):
                size = os.path.getsize(fileWholePath)
                cfgFile.set("VolumInfo", str(file), str(size))
                itemNum += 1
        cfgFile.add_section("VolumNum")
        cfgFile.set("VolumNum",'volumNum',str(itemNum))
        cfgFile.write(viFile)
        viFile.close()
        logger.debug('[OUT] out writeVolumInfoFile')
    #=================================================================
    # 
    #=================================================================
    def writeVolumInfoAndmd5ToXML(self):
        logger.debug('[ENTER] enter writeVolumInfoAndmd5ToXML')
        volumeFileList = self.getVolumeFileList()
        if volumeFileList == []:
            logger.error('路径 ' + '%s'%self._srcPath + '下，无所需的' + '%s'%self._volumeName + '压缩包文件')
            print strDecode('[ERROR] 路径').unicodeStr + '%s'%self._srcPath + strDecode('中未找到任何与').unicodeStr + '%s'%self._volumeName + strDecode('有关的分卷压缩包，请检查后再试！').unicodeStr
            logger.debug('[OUT] out writeVolumInfoAndmd5ToXML')
            sys.exit(-1)
        iniFilePath = os.path.dirname(self._volumInfoIni)
        if not os.path.isdir(iniFilePath):
            os.mkdir(iniFilePath) 
        dom = xml.dom.minidom.parse(self._volumInfoXML)
        if not dom :
            logger.error('路径 ' + '%s'%self._srcPath + '下，无所需的' + '%s'%self._volumInfoXML + '压缩包文件')
            print strDecode('[ERROR] 路径').unicodeStr + '%s'%self._srcPath + strDecode('中未找到任何与').unicodeStr + '%s'%self._volumInfoXML + strDecode('有关的分卷压缩包，请检查后再试！').unicodeStr
            logger.debug('[OUT] out writeVolumInfoAndmd5ToXML')
            sys.exit(-1)
        root = dom.documentElement
        packinfoEles = root.getElementsByTagName("PackagesInfo")
        gameinfoEles = root.getElementsByTagName("GameInfo")
        subpackdetailEles = root.getElementsByTagName("SubPackageDetails")
        packinfo = packinfoEles[0]
        subdetail = subpackdetailEles[0]
        gameinfo = gameinfoEles[0]
        if not packinfo or not subdetail :
            logger.error('文件' + '%s'%(self._srcPath + '%s'%self._volumInfoXML) + '中没有元素 PackagesInfo 或者元素 SubPackageDetails' + '压缩包文件')
            print strDecode('[ERROR] 路径').unicodeStr + '%s'%self._srcPath + strDecode('中未找到任何与').unicodeStr + '%s'%self._volumInfoXML + strDecode('有关的分卷压缩包，请检查后再试！').unicodeStr
            logger.debug('[OUT] out writeVolumInfoAndmd5ToXML')
            sys.exit(-1)
        while subdetail.hasChildNodes():
            subdetail.removeChild(subdetail._get_firstChild())
        
        itemNum = 0
        
        viFile = open(self._volumInfoIni, 'w+')
        XMLFile = open(self._volumInfoXML, 'w+')
        for file in volumeFileList:
            fileWholePath = self._srcPath + file
            if  not os.path.isdir(fileWholePath) and os.path.isfile(fileWholePath):
                size = os.path.getsize(fileWholePath)
                fp = open(fileWholePath, 'rb')
                m = md5.new()
                while 1:
                    data = fp.read(8096)
                    if not data:
                        break
                    m.update(data)
                fp.close()
                md5value = m.hexdigest()                
                subdetailItem = dom.createElement("Package")
                subdetailItem.setAttribute("PackName" , file)
                subdetailItem.setAttribute("PackSize" , '%d'%size)
                subdetailItem.setAttribute("PackMd5" , md5value)
                subdetail.appendChild(subdetailItem)
                itemNum += 1
        packinfo.setAttribute("FirstPackName" , volumeFileList[0])        
        packinfo.setAttribute("PackPwd" , self._pwd)
        packinfo.setAttribute("PackNum" , '%d'%itemNum)
        gameinfo.setAttribute("GameVesion" , self._version)
        dom.writexml( XMLFile , '' , ' ' , '\n' , 'utf-8')
        XMLFile.close()
        logger.debug('[OUT] out writeVolumInfoAndmd5ToXML')
    #=================================================================
    # 
    #=================================================================
    def autoPatchExcute(self):
        logger.debug('[ENTER] enter autoPatchExcute')
        logger.debug('开始自动打包.......')
        volumeFileList = []
        try:
            opts,args = getopt.getopt(self._args,"hp:w:v:d:",["help","pack","write","version","dataDir"])
        except getopt.GetoptError,e:
            self.usage()
            logger.error('python脚本的输入参数错误' + str(e))
            logger.debug('[OUT] out autoPatchExcute')
            sys.exit(2)
        if (("-w" in opts) or ("--write" in opts)) and (("-p" in opts) or ("-pack" in opts)):
            self.usage()
            logger.error('"-p" 和  "-w"互斥，不可以同时出现在输入参数列表中!')
            logger.debug('[OUT] out autoPatchExcute')
            sys.exit(2)
        for opt,arg in opts:
            print "args: ", opt, '=', arg
            if opt in ("-h", "--help"):
                self.usage()
                logger.debug('help: \r\n' + self.usage())
                logger.debug('[OUT] out autoPatchExcute')
                sys.exit()
            elif opt in ("-p","--pack"):
                #self._nsisFileName = arg
                self._srcPath = arg + '\\'
            elif opt in ("-w","--write"):
                self._isDoAll = False
                logger.debug('self._isDoAll : ' + str(self._isDoAll) + ', 不对资源文件进行压缩，直接写入ini文件，进行nsis打包！')
                self._nsisFileName = arg
            elif opt in ("-v" , "--version"):
                self._version = arg
            elif opt in("-d", "--dataDir"):
                self._dataResorcePath = arg
                print self._dataResorcePath

        #print "NSIS:", self._nsisFileName, self._srcPath, os.path.dirname(self._nsisFileName)
        #self._srcPath = os.path.dirname(self._nsisFileName) + '\\'
        self._iniFilePath = self._srcPath + 'SD_NSIS\\settings.ini'

        #if(self._dataResorcePath == None or self._dataResorcePath == ''):
        #    self._dataResorcePath = self._srcPath + 'SplitDataResource\\'

        self._SevenZipToolPath = self._srcPath + 'SD_NSIS\\7za\\7za.exe'
        self._WinZipToolPath = self._srcPath + 'SD_NSIS\\winzip\\wzzip.exe'
        self._volumInfoIni = self._srcPath + 'Client\VolumInfo.ini'
        self._volumInfoXML = self._srcPath + 'SD_NSIS\\InstallTool\\resource\\GameInfoReference.xml'    
        #self._makeNsisPath = self._srcPath + 'SD_NSIS\makensis.exe '
        self._makeInstallFile = self._srcPath + 'SD_NSIS\InstallTool\InstallMaker.bat '
        self._tempZipName = self._srcPath + 'tempSplitZip' + str(time.strftime('%Y%m%d_%H%M%S',time.localtime(time.time()))) + '.zip'
        
        if self._isDoAll == False:
            try:
                print strDecode('欢迎使用半自动脚本编译模式！请根据下述指导完成打包：\r\n').unicodeStr
                #===============================================================
                # while True:
                #     self._volumeType = raw_input(u"请输入您想打包的分卷包类型(请均用小写字母)：\r\n".encode('gbk'))
                #     if not self._volumeType == '7z' and not self._volumeType == 'zip':
                #         print u'\r\n您的输入类型有误，或我们无法支持该类型，请重新输入！\r\n'.encode('gbk')
                #         continue
                #     else:
                #         break
                #===============================================================
                while True:
                    strTempInput = raw_input(u"\r\n请输入您想打包的第一个分卷包的名称(请输入全称，例如：data.zip或data.7z.001),请确保当前目录下存在您输入的分卷包:\r\n".encode('gbk'))
                    self._volumeName = strTempInput#.lower()
                    nameParts = self._volumeName.split('.')
                    nameExt = nameParts[-1]
                    if not (nameExt == '001' or nameExt == 'zip'):
                        print strDecode('\r\n您输入的名称后缀' + str(nameExt) + '有误或暂时无法支持此种文件格式，请检查后重新输入！\r\n').unicodeStr
                        continue
                    elif not (self.isFile7z(self._volumeName) or self.isFileZip(self._volumeName)):
                        print strDecode('\r\n您输入的名称' + str(nameExt) + '有误，请检查后重新输入！\r\n').unicodeStr
                        continue
                    else:
                        break
                #===============================================================
                # while True:
                #     self._splitSize = raw_input(u"\r\n请输入您希望的每个分卷包大小(单位为Byte),请合理分配每个分卷包的大小，避免分卷过小造成过多的分卷包,默认每个分卷包的大小不低于10KB，即10240B:\r\n".encode('gbk'))
                #     if not re.match(r'^\d{5}',self._splitSize) and not self._splitSize > 10240:
                #         print strDecode("\r\n您输入的分卷包大小不为数字或小于10KB，请重新输入！\r\n").unicodeStr
                #         continue
                #     else:
                #         break
                # while True:
                #     self._pwd = raw_input(u"\r\n请输入您想使用的打包密码(若您需要给zip包添加密码，那么请输入不少于8个字符的密码，而若不希望使用密码，请直接回车):\r\n".encode('gbk'))
                #     if self._volumeType == 'zip' and not self._pwd == '':
                #         if not re.match(r'^\d{8}$',self._pwd):
                #             print strDecode('\r\n您输入的密码不正确，请重新输入，注意，您的密码长度必须大于8个字符：\r\n').unicodeStr
                #             continue
                #     else:
                #         break
                #===============================================================
            except Exception,e:
                print strDecode('[ERROR] An Unhandled Exception occur: " ' + str(e) + ' "').unicodeStr
                logger.error('An Unhandled Exception occur : " ' + str(e) + ' "\r\n' +  traceback.format_exc())
                logger.debug('[OUT] out autoPatchExcute')
                sys.exit(-1) 
        logger.debug("*********************PARAMETER LIST****************************")
        logger.debug('self._srcPath:\r\n' + str(self._srcPath))
        logger.debug('\r\nself._iniFilePath :\r\n ' + str(self._iniFilePath))
        logger.debug('\r\nself._dataResorcePath :\r\n ' + str(self._dataResorcePath))
        logger.debug('\r\nself._version :\r\n ' + str(self._version))
        logger.debug('\r\nself._SevenZipToolPath :\r\n' + str(self._SevenZipToolPath))
        logger.debug('\r\nself._WinZipToolPath:\r\n' + str(self._WinZipToolPath))
        logger.debug('\r\nself._volumInfoIni:\r\n' + str(self._volumInfoIni))
        logger.debug('\r\nself._volumInfoXML:\r\n' + str(self._volumInfoXML))
        logger.debug('\r\nself._makeNsisPath:\r\n' + str(self._makeNsisPath))
        logger.debug('\r\nself._makeInstallFile:\r\n' + str(self._makeInstallFile))
        logger.debug('\r\nself._tempZipName:\r\n' + str(self._tempZipName))
        logger.debug('\r\nself._volumeType:\r\n' + str(self._volumeType))
        logger.debug('\r\nself._volumeName:\r\n' + str(self._volumeName))
        logger.debug('\r\nself._splitSize:\r\n' + str(self._splitSize))
        logger.debug('\r\nself._pwd:\r\n' + str(self._pwd))
        logger.debug("*********************PARAMETER LIST END****************************")
        try:
            if self._isDoAll == True:
                self.parase_Ini()
                volumeNameParts = self._volumeName.split('.')
                if len(volumeNameParts) < 2:
                    logger.error('分卷包名称""' + '%s'%self._volumeName + '错误，请检查您在模板生成器中的输入，应为：test.zip 或  test.7z.001!')
                    raise userException('分卷包名称""' + '%s'%self._volumeName + '错误，请检查您在模板生成器中的输入，应为：test.zip 或  test.7z.001!')
                    #print 'volume file name : ' + '%s'%self._volumeName + 'Wrong, please check!'
                    return 
                volumeNamePre = '.'.join(volumeNameParts[0:-1])
                volumeNameExt = volumeNameParts[-1]
                if volumeNameExt == '001':
                    self._volumeType = '7z'
                elif volumeNameExt == 'zip':
                    self._volumeType = 'zip'
                self.ClearVolumeOfPath(volumeNamePre)
                #拷贝字体文件和第三方库文件
                print '============================================\r\n'
                copySrcDir = self._srcPath + 'SD_NSIS\InstallTool\Install'
                copyDestDir = self._dataResorcePath + 'CQYH\Install'
                cmdLine = 'md ' + copyDestDir
                print 'makedir commondline:' + cmdLine
                os.popen(cmdLine)
                cmdLine = 'xcopy ' + copySrcDir + ' ' + copyDestDir + ' ' + '/s /y'
                print ' commondline:' + cmdLine
                os.popen(cmdLine)
             
                
                #开始打包
                print '============================================\r\n'
                print strDecode('开始打包 ').unicodeStr + str(self._volumeName) + strDecode(',这可能会花费您一点时间，请耐心等待.....\r\n').unicodeStr
                logger.debug('============================================')
                logger.debug('开始打包 ' + str(self._volumeName) + ',这可能会花费您一点时间，请耐心等待.....')          
                self.excute_pack()
                print strDecode('打包 ').unicodeStr + str(self._volumeName) + strDecode(' 结束, 您可以检查此包是否正确生成!\r\n').unicodeStr
                print '==============================================\r\n'
                logger.debug('打包 ' + str(self._volumeName) + ' 结束, 您可以检查此包是否正确生成!')
                logger.debug('==============================================\r\n')

                #开始写xml文件
                print '============================================\r\n'
                print strDecode('开始写入 ' + str(self._volumInfoXML) + ' 文件，请勿占用此文件！耐心等待........\r\n').unicodeStr
                logger.debug('==============================================')
                logger.debug('开始写入 ' + str(self._volumInfoXML) + ' 文件，请勿占用此文件！耐心等待........')
                self.writeVolumInfoAndmd5ToXML()
                print strDecode('写入 ' + str(self._volumInfoXML) + ' 文件结束！\r\n').unicodeStr
                print '==============================================\r\n'
                logger.debug('写入 ' + str(self._volumInfoXML) + ' 文件结束！')
                logger.debug('==============================================\r\n')

                #开始编译脚本
                #print '==========================================\r\n'
                #print strDecode('开始生成安装文件,  ').unicodeStr + strDecode('请耐心等待........\r\n').unicodeStr
                #logger.debug('==============================================')
                #logger.debug('开始生成安装文件:  ' + ' 文件，请耐心等待........')
                #self.excute_makeInstallFile()
                #print strDecode('安装文件  ').tr + strDecode(' 文件完成！\r\n').unicodeStr
                #print '==============================================\r\n'
                #logger.debug('安装文件  ' + str(self._nsisFileName) + ' 文件完成！')
                #logger.debug('==============================================\r\n')
                
                #开始写ini文件
                #print '============================================\r\n'
                #print strDecode('开始写入 ' + str(self._volumInfoIni) + ' 文件，请勿占用此文件！耐心等待........\r\n').unicodeStr
                #logger.debug('==============================================')
                #logger.debug('开始写入 ' + str(self._volumInfoIni) + ' 文件，请勿占用此文件！耐心等待........')
                #self.writeVolumInfoFile()
                #print strDecode('写入 ' + str(self._volumInfoIni) + ' 文件结束！\r\n').unicodeStr
                #print '==============================================\r\n'
                #logger.debug('写入 ' + str(self._volumInfoIni) + ' 文件结束！')
                #logger.debug('==============================================\r\n')
                
                #开始编译脚本
                #print '==========================================\r\n'
                #print strDecode('开始编译脚本  ').unicodeStr + str(self._nsisFileName) + strDecode(' 文件，请耐心等待........\r\n').unicodeStr
                #logger.debug('==============================================')
                #logger.debug('开始编译脚本  ' + str(self._nsisFileName) + ' 文件，请耐心等待........')
                #self.excute_makeNsis()
                #print strDecode('编译脚本  ').unicodeStr + str(self._nsisFileName) + strDecode(' 文件完成！\r\n').unicodeStr
                #print '==============================================\r\n'
                #logger.debug('编译脚本  ' + str(self._nsisFileName) + ' 文件完成！')
                #logger.debug('==============================================\r\n')
        except userException,e:
            print strDecode('[ERROR] An Handled Exception occur : " ' + e.errMsg + ' "').unicodeStr
            logger.error('An Handled Exception occur : " ' + e.errMsg + ' "\r\n' +  traceback.format_exc())
            sys.exit(-1)
        except Exception,e:
            print strDecode('[ERROR] An Unhandled Exception occur: " ' + str(e) + ' "').unicodeStr
            logger.error('An Unhandled Exception occur : " ' + str(e) + ' "\r\n' +  traceback.format_exc())
            sys.exit(-1)
        finally:
            logger.debug('[OUT] out autoPatchExcute')
        return
            
if __name__ == '__main__':
    logDir = os.getcwd() + '\\autoPackLog'
    if not os.path.isdir(logDir):
        os.mkdir(logDir)
    logging.basicConfig(filename = os.path.join(logDir , 'autoPatch_'+ '%s'%time.strftime('%Y%m%d_%H%M%S',time.localtime(time.time())) + '.log'), level = logging.DEBUG, filemode = 'w', format = '[%(asctime)s] - [%(levelname)s] :  %(message)s') 
    logger = logging.getLogger()
    patch = autoPatch(sys.argv[1:]) 
    logger.debug('[START] argvs is : ' + str(sys.argv[1:]) )
    patch.autoPatchExcute()
