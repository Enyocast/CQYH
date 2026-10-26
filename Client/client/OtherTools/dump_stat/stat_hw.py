__author__ = 'dbg'
import os
import re
import hashlib
import sys
import TabFile

class HardwareData:
    def __init__(self):
        self.RoleID = ''
        self.CapLvGPU = 0
        self.CapLvCPU = 0
        self.CapLvMem = 0
        self.GPUInfo = ''
        self.CPUInfo = ''
        self.MemSize = 0
        self.OSInfo = ''
        self.MemoryInfo = ''
        self.VMType = ''
        self.VerInfo = ''


class UserData:
    def __init__(self):
        self.RoleID = ''
        self.RoleName = ''
        self.UserName = ''
        self.Level = 0
        self.ComputerName = ''
        self.CrashType = ''
        self.CrashLog = ''
        self.CrashID = 0
        self.TimeOfCrash = ''
        #self.HardwareData = HardwareData()
        #self.FoundLogFile = False

allExcelData=[]

# roleid -> HardwareData
allHardwareData = {}
gpuData = {}
cpuData = {}
memSizeData = {}

gpuLv = {}
cpuLv = {}

lostUser = {}
lostUserFile = None

# roleid -> UserData
allUserData = {}

def load_hardwareinfo(fileName):
    if not os.path.isfile(fileName):
        print 'File not found:', fileName
        return

    print 'processing hardware log:', fileName

    hardwareTabFile = TabFile.TabFile(fileName)
    hardwareTabFile.Init()

    Idx_RoleID = 4
    Idx_GPUInfo = 31
    Idx_CPUInfo = 11
    Idx_MemorySize = 19

    #print hardwareTabFile.row, hardwareTabFile.column
    #print hardwareTabFile.GetValue(1, Idx_RoleID),  hardwareTabFile.GetValue(2, Idx_RoleID)

    for i in range(2, hardwareTabFile.row, 1):
        key = hardwareTabFile.GetValue(i, Idx_RoleID)
        if not allHardwareData.has_key(key):
            hdDat = HardwareData()
            hdDat.RoleID = key
            hdDat.GPUInfo = hardwareTabFile.GetValue(i, Idx_GPUInfo).strip(' ')
            if hdDat.GPUInfo == "":
                #print "GPU is none!", i + 1
                hdDat.GPUInfo = hardwareTabFile.GetValue(i, Idx_GPUInfo).strip(' ')

            #print hdDat.GPUInfo
            hdDat.CPUInfo = hardwareTabFile.GetValue(i, Idx_CPUInfo).strip(' ')
            if hdDat.CPUInfo == "":
                #print "CPU is none!", i + 1
                hdDat.CPUInfo = hardwareTabFile.GetValue(i, Idx_CPUInfo).strip(' ')

            hdDat.MemSize = int(round(float(hardwareTabFile.GetValue(i, Idx_MemorySize))))

            allHardwareData[key] = hdDat

            if gpuData.has_key(hdDat.GPUInfo):
                if hdDat.GPUInfo == "" or hdDat.GPUInfo == None:
                    print "GPUInfo is none!", i + 1
                gpuData[hdDat.GPUInfo] = gpuData[hdDat.GPUInfo] + 1
            else:
                gpuData[hdDat.GPUInfo] = 1

            if cpuData.has_key(hdDat.CPUInfo):
                if hdDat.CPUInfo == "" or hdDat.CPUInfo == None:
                    print "CPUInfo is none!", i + 1
                cpuData[hdDat.CPUInfo] = cpuData[hdDat.CPUInfo] + 1
            else:
                cpuData[hdDat.CPUInfo] = 1

            if memSizeData.has_key(hdDat.MemSize):
                memSizeData[hdDat.MemSize] = memSizeData[hdDat.MemSize] + 1
            else:
                memSizeData[hdDat.MemSize] = 1


def gen_hwstat():
    f = open('stat_gpu.txt', 'w+')
    if f :
        f.write('GPU')
        f.write('\t')
        f.write('Count')
        f.write('\t')
        f.write('Rank')
        f.write('\n')
        for k in gpuData.keys():
            #print k, gpuData[k]
            f.write(str(k))
            f.write('\t')
            f.write(str(gpuData[k]))
            f.write('\t')

            writed = False
            for x in allHardwareData.values():
                if x.GPUInfo == k:
                    f.write(str(x.CapLvGPU))
                    writed = True
                    break
            if not writed:
                f.write("")

            f.write('\n')
        f.close()

    f = open('stat_cpu.txt', 'w+')
    if f :
        f.write('CPU')
        f.write('\t')
        f.write('Count')
        f.write('\t')
        f.write('Rank')
        f.write('\n')
        for k in cpuData.keys():
            f.write(k)
            f.write('\t')
            f.write(str(cpuData[k]))
            f.write('\t')

            writed = False
            for x in allHardwareData.values():
                if x.CPUInfo == k:
                    f.write(str(x.CapLvCPU))
                    writed = True
                    break
            if not writed:
                f.write("")

            f.write('\n')
        f.close()

    f = open('stat_mem.txt', 'w+')
    if f :
        f.write('memSizeData')
        f.write('\t')
        f.write('Count')
        f.write('\t')
        f.write('Rank')
        f.write('\n')
        for k in memSizeData.keys():
            f.write(str(k))
            f.write('\t')
            f.write(str(memSizeData[k]))
            f.write('\t')
            f.write(str(memSizeData[k]))
            f.write('\n')
        f.close()

    #print len(allHardwareData), len(gpuData), len(cpuData)

def load_user_info(fileName):
    if not os.path.isfile(fileName):
        print 'File not found:', fileName
        return
    userTabFile = TabFile.TabFile(fileName)
    userTabFile.Init()

    Idx_RoleID = 1
    Idx_RoleName = 2
    Idx_UserName = 3
    Idx_Level = 4

    for i in range(2, userTabFile.row, 1):
        key = userTabFile.GetValue(i, Idx_RoleID)
        if not allUserData.has_key(key):
            hdDat = UserData()
            hdDat.RoleID = key
            userNameStr = userTabFile.GetValue(i, Idx_RoleName)
            hdDat.RoleName = unicode(userNameStr, 'utf8')
            hdDat.UserName = userTabFile.GetValue(i, Idx_UserName)
            lvStr = userTabFile.GetValue(i, Idx_Level)
            #lvStr = lvStr.replace(' ', '')
            #print lvStr, unicode(lvStr)
            fval = float(lvStr)
            hdDat.Level = int(round(fval))
            allUserData[key] = hdDat

def load_hw_rank(cpuLvFile, gpuLvFile):

    Idx_RoleID = 1
    Idx_Lv = 3

    if os.path.isfile(cpuLvFile):
        cpuLvTabFile = TabFile.TabFile(cpuLvFile)
        cpuLvTabFile.Init()

        for i in range(2, cpuLvTabFile.row, 1):
            key = cpuLvTabFile.GetValue(i, Idx_RoleID).strip(' ')

            for x in allHardwareData.values():
                if x.CPUInfo == key:
                    lvStr = cpuLvTabFile.GetValue(i, Idx_Lv)
                    if lvStr != "" and lvStr != None:
                        x.CapLvCPU = int(round(float(lvStr)))
                        break
    else:
        print 'File not found:', cpuLvFile


    if os.path.isfile(gpuLvFile):
        gpuLvTabFile = TabFile.TabFile(gpuLvFile)
        gpuLvTabFile.Init()

        for i in range(2, gpuLvTabFile.row, 1):
            key = gpuLvTabFile.GetValue(i, Idx_RoleID).strip(' ')

            for x in allHardwareData.values():
                #print x.GPUInfo, " == ", key, x.GPUInfo == key
                if x.GPUInfo == key:
                    lvStr = gpuLvTabFile.GetValue(i, Idx_Lv)
                    if lvStr != "" and lvStr != None:
                        x.CapLvGPU = int(round(float(lvStr)))
                        break
    else:
         print 'File not found:', gpuLvFile


class UserSummaryData:
    def __init__(self):
        self.TotalCapLv = 0
        self.Count = 1
        self.AvgCapLv = 0


def gen_stat_summ(lv):

    #otherUser = {}
    global lostUserFile
    global lostUser

    lostNoHWCnt = 0
    otherNoHWCnt = 0

    if not lostUserFile:
        lostUserFile = open('lost_user.txt', 'w+')
        lostUserFile.write('RoleID\t')
        lostUserFile.write('RoleName\n')

    for ke in allUserData.keys():
        if allUserData[ke].Level == lv:
            if lostUser.has_key(lv):
                if allHardwareData.has_key(ke):
                    lostUser[lv].TotalCapLv = allHardwareData[ke].CapLvCPU + allHardwareData[ke].CapLvGPU + allHardwareData[ke].CapLvMem
                else:
                    #print 'Key not found hardware:', ke, allUserData[ke].RoleName
                    lostUserFile.write(str(ke) + '\t' + allUserData[ke].RoleName.encode('gbk', errors='ignore').strip() + '\n')
                    lostNoHWCnt = lostNoHWCnt + 1

                lostUser[lv].Count = lostUser[lv].Count + 1
            else:
                lostUseData = UserSummaryData()
                lostUseData.Count = 1
                if allHardwareData.has_key(ke):
                    lostUseData.TotalCapLv = allHardwareData[ke].CapLvCPU + allHardwareData[ke].CapLvGPU + allHardwareData[ke].CapLvMem
                else:
                    #print 'Key not found hardware:', ke, allUserData[ke].RoleName
                    lostUserFile.write(str(ke) + '\t' + allUserData[ke].RoleName.encode('gbk', errors='ignore').strip() + '\n')
                    lostNoHWCnt = lostNoHWCnt + 1
                    lostUseData.TotalCapLv = 0

                lostUser[lv] = lostUseData
"""        else:
            if lostUser.has_key(lv + 1):
                if allHardwareData.has_key(ke):
                    lostUser[lv + 1].TotalCapLv = allHardwareData[ke].CapLvCPU + allHardwareData[ke].CapLvGPU + allHardwareData[ke].CapLvMem
                else:
                    #print 'Key not found hardware:', ke, allUserData[ke].RoleName
                    lostUserFile.write(str(ke) + '\t' + allUserData[ke].RoleName.encode('gbk', errors='ignore').strip() + '\n')
                    otherNoHWCnt = otherNoHWCnt + 1

                lostUser[lv + 1].Count = lostUser[lv + 1].Count + 1
            else:
                otherUseData = UserSummaryData()
                otherUseData.Count = 1

                if allHardwareData.has_key(ke):
                    otherUseData.TotalCapLv = allHardwareData[ke].CapLvCPU + allHardwareData[ke].CapLvGPU + allHardwareData[ke].CapLvMem
                else:
                    #print 'Key not found hardware:', ke, allUserData[ke].RoleName
                    lostUserFile.write(str(ke) + '\t' + allUserData[ke].RoleName.encode('gbk', errors='ignore').strip() + '\n')
                    otherNoHWCnt = otherNoHWCnt + 1

                lostUser[lv + 1] = otherUseData
"""

    #print "Key HW info not found, lost:", lostNoHWCnt, " Other:", otherNoHWCnt

    #for ke in lostUser.keys():
    #    lostUser[ke].AvgCapLv = lostUser[ke].TotalCapLv / lostUser[ke].Count

    #for ke in otherUser.keys():
    #    otherUser[ke].AvgCapLv = otherUser[ke].TotalCapLv / otherUser[ke].Count

    #write_summ('user_summary_' + str(lv) + ".txt", lostUser)
    #write_summ('user_summary_' + str(lv) + "_up.txt", otherUser)

#
# write_summ
#
def write_summ(fileName, dic):
    f = open(fileName, 'w+')
    if f:
        f.write('Lv')
        f.write('\t')
        f.write('Count')
        f.write('\t')
        f.write('AvgCapLv')
        f.write('\n')

        for k in dic.keys():
            f.write(str(k))
            f.write('\t')

            f.write(str(dic[k].Count))
            f.write('\t')

            f.write(str(dic[k].AvgCapLv))
            f.write('\n')
    f = None


def test():
    f = open('user_stat.txt', 'w+')
    if f :
        f.write('RoleID')
        f.write('\t')
        f.write('RoleName')
        f.write('\t')
        f.write('MaxLevel')
        f.write('\t')
        f.write('HardwareCapLv')
        f.write('\n')
        for k in allUserData.keys():
            f.write(str(k))
            f.write('\t')
            f.write(str(allUserData[k].RoleName.encode('gbk', errors='ignore').strip()))#.encode(u'gbk', ignore)))
            f.write('\t')
            f.write(str(allUserData[k].Level))
            f.write('\t')
            # find user's hardware cap lv
            if allHardwareData.has_key(k):
                f.write(str(allHardwareData[k].CapLvCPU + allHardwareData[k].CapLvGPU + allHardwareData[k].CapLvMem))
            else:
                f.write('0')

            f.write('\n')
        f.close()

if __name__ == '__main__':

    global lostUserFile
    global lostUser

    print 'processing hardware log...'
    load_hardwareinfo('ClientHardwareInfo_2015_03_18_.txt')
    load_hardwareinfo('ClientHardwareInfo_2015_03_19.txt')
    load_hardwareinfo('ClientHardwareInfo_2015_03_20.txt')
    load_hardwareinfo('ClientHardwareInfo_2015_03_21.txt')
    load_hardwareinfo('ClientHardwareInfo_2015_03_23.txt')

    print 'processing hardware rank...'
    load_hw_rank('stat_rank_cpu.txt', 'stat_rank_gpu.txt')

    gen_hwstat()

    print 'processing user info...'
    load_user_info('exportdb324.txt')

    print 'processing summary...'
    for i in range(1, 40, 1):
        gen_stat_summ(i)

    lostUserFile.close()

    for ke in lostUser.keys():
        lostUser[ke].AvgCapLv = lostUser[ke].TotalCapLv / lostUser[ke].Count

    write_summ('user_summary_1-35.txt', lostUser)
