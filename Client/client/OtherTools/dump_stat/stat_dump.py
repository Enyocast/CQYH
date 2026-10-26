__author__ = 'dbg'

import os
import re
import hashlib
import sys

class LogData:
    def __init__(self):
        self.OSInfo = ''
        self.MemoryInfo = ''
        self.VMType = ''
        self.GPUInfo = ''
        self.VerInfo = ''


class ExcelData:
    def __init__(self):
        self.ComputerName = ''
        self.UserName = ''
        self.CrashType = ''
        self.CrashLog = ''
        self.CrashID = 0
        self.TimeOfCrash = ''
        self.LogData = LogData()
        self.FoundLogFile = False

allExcelData=[]

pttnOS_Str = u'Init: OS Info:.*'.encode(u'utf-8')
pttnOS = re.compile(pttnOS_Str, re.U)

pttnMem_Str = u'Init: Memory total:.*'.encode(u'utf-8')
pttnMem = re.compile(pttnMem_Str, re.U)

vmKey = u'Virtual='.encode(u'utf-8')

pttnGPU_Str = u'Log: GPU:.*'.encode(u'utf-8')
pttnGPU = re.compile(pttnGPU_Str, re.U)

pttnVer_Str = u'CQYH Ver:.*'.encode(u'utf-8')
pttnVer = re.compile(pttnVer_Str, re.U)

def load_log(crashID, excelDat, logDir):
    logFile = logDir + str(crashID) + u'_Launch.log.txt'
    if not os.path.isfile(logFile):
        print 'File not found:', logFile
        excelDat.FoundLogFile = False
        return

    excelDat.FoundLogFile = True
    logFileHandle = open(logFile, u'r')
    for lineStr in logFileHandle:
        lineStr = lineStr.decode(u'gbk')
        #print lineStr

        matchOS = pttnOS.search(lineStr)
        matchMem = pttnMem.search(lineStr)
        matchGPU = pttnGPU.search(lineStr)
        matchVer = pttnVer.search(lineStr)

        if matchOS:
            matchStr = lineStr[matchOS.start() + len(pttnOS_Str) - 2:matchOS.end(0)]
            excelDat.LogData.OSInfo = matchStr
            #print crashID, matchStr
        elif matchMem:
            matchStr = lineStr[matchMem.start() + len(pttnMem_Str) - 2:matchMem.end(0)]
            excelDat.LogData.MemoryInfo = matchStr
            idx = matchStr.index(vmKey)
            if idx >= 0:
                totalLen = len(matchStr)
                vmemSize = matchStr[idx + len(vmKey):len(matchStr)]
                excelDat.LogData.VMType = vmemSize
            #print crashID, matchStr
        elif matchGPU:
            matchStr = lineStr[matchGPU.start() + len(pttnGPU_Str) - 2:matchGPU.end(0)]
            excelDat.LogData.GPUInfo = matchStr
            #print crashID, matchStr
        elif matchVer:
            matchStr = lineStr[matchVer.start() + len(pttnVer_Str) - 2:matchVer.end(0)]
            excelDat.LogData.VerInfo = matchStr
            #print crashID, matchStr

def stat_dumps(cvsFile, saveName, logDir):
    cvsFileHandle = open(cvsFile, u'r')
    print u'Open file:', cvsFile, cvsFileHandle
    i = 0

    tabSplit = u'\t'.decode('utf-8').encode(u'gbk')
    for lineStr in cvsFileHandle:
        i = i + 1
        #print i
        if i == 1:
            continue

        lineStr = lineStr.decode(u'utf-8')#.encode(u'gbk')
        #print lineStr
        splitStrs = lineStr.split(tabSplit)
        #print lineStr, splitStrs
        if len(splitStrs) < 6:
            print u'Error line:', lineStr
        else:
            if len(splitStrs[0]) == 0:
                print u'Error Line:', lineStr
                continue
            #print splitStrs
            excelData = ExcelData()
            excelData.ComputerName = splitStrs[0]
            excelData.UserName = splitStrs[1]
            excelData.CrashType = splitStrs[2]
            excelData.CrashLog = splitStrs[3]
            excelData.CrashID = splitStrs[4]
            excelData.TimeOfCrash = splitStrs[5][0:len(splitStrs[5]) - 1] # remove the return
            #print excelData.CrashID, excelData.TimeOfCrash
            load_log(excelData.CrashID, excelData, logDir)
            allExcelData.append(excelData)

    #print len(allExcelData)

    errDatMap = {}
    for d in allExcelData:
        key = unicode(hashlib.md5(d.CrashType).hexdigest()).encode(u'gbk')
        if errDatMap.has_key(key):
            errDatMap[key].append((d.CrashType, d))
        else:
            errDatMap[key] = [(d.CrashType, d)]

    summaryFile = open(saveName + u'_summary.csv', u'w+')
    for k in errDatMap:
        v = errDatMap[k]
        #print v[0][0],  len(v)
        summaryFile.write(v[0][0])
        summaryFile.write(u',')
        summaryFile.write(str(len(v)))
        summaryFile.write(u'\n')
    summaryFile.close()

    os.system(u'md stats')
    os.system(u'del /Q .\\stats\\*.*')
    #
    # byCRASH type
    #
    for k in errDatMap:
        fileName = u'stats\\' + k + u'.csv'

        v = errDatMap[k]

        detailFile = open(fileName, u'w+')
        detailFile.write(v[0][1].CrashLog.encode(u'gbk'));
        detailFile.write(u',Name,OSInfo,MemoryInfo,GPUInfo,VerInfo\n')

        detailFile.write(u'ID,Name,OSInfo,MemoryInfo,GPUInfo,VerInfo'.encode(u'gbk').encode(u'gbk'));
        detailFile.write(u'\n')
        for d in v:
            #print type(d), len(d), d
            #print d[1].LogData.GPUInfo
            detailFile.write(d[1].CrashID.encode(u'gbk'));
            detailFile.write(u',')

            detailFile.write(d[1].ComputerName.encode(u'gbk'));
            detailFile.write(u',')

            logDat = d[1].LogData
            detailFile.write(logDat.OSInfo.encode(u'gbk'));
            detailFile.write(u',')

            #detailFile.write(d[1].LogData.MemoryInfo.encode(u'gbk'));
            #detailFile.write(u',')

            detailFile.write(logDat.VMType.encode(u'gbk'));
            detailFile.write(u',')

            detailFile.write(logDat.GPUInfo.encode(u'gbk'));
            detailFile.write(u',')

            detailFile.write(logDat.VerInfo.encode(u'gbk'));
            detailFile.write(u',')

            detailFile.write(u'\n')




        #for d in v:
            #print d[1]
        detailFile.close()

    print len(errDatMap)

    #
    # by CRASH time
    #
    errDatMap = {}
    for d in allExcelData:
        key = unicode(hashlib.md5(d.TimeOfCrash).hexdigest()).encode(u'gbk')
        if not errDatMap.has_key(key):
            errDatMap[key] = [d.TimeOfCrash, 1]
        else:
            errDatMap[key][1] = errDatMap[key][1] + 1

    time_of_crash = open(saveName +  u'time_of_crash.csv', u'w+')
    time_of_crash.write(u'Time,Count\n'.encode(u'gbk'))
    for k in errDatMap:
        time_of_crash.write(errDatMap[k][0].encode(u'gbk'))
        time_of_crash.write(u',')
        time_of_crash.write(str(errDatMap[k][1]).encode(u'gbk'))
        time_of_crash.write(u'\n')
    time_of_crash.close()

if __name__ == '__main__':
    stat_dumps('dumpCrash924.txt',  '924', '.\\logs\\')
    stat_dumps('dumpCrash925.txt',  '925', '.\\logs\\')
    stat_dumps('dumpCrash926.txt',  '926', '.\\logs\\')
    stat_dumps('dumpCrash927.txt',  '927', '.\\logs\\')
    stat_dumps('dumpCrash928.txt',  '928', '.\\logs\\')
    stat_dumps('dumpCrash929.txt',  '929', '.\\logs\\')