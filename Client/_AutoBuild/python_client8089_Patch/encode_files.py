#coding=utf8

import re
import os
import sys
import threadpool
import hashlib
from multiprocessing import Pool
import shutil

#-------------------------------
def find_log_files(searchDir, logFiles):
    if searchDir[-1] != u'\\':
        searchDir += u'\\'

    files = os.listdir(searchDir)
    skipExt = ['py', 'xlsx', 'lua', 'log', 'xlsm', 'xls', 'usf']
    for fi in files:
        #print fi
        if os.path.isdir(searchDir + fi):
            find_log_files(searchDir + fi, logFiles)
        elif os.path.isfile(searchDir + fi):
            file_lists = fi.split('.')
            file_ext = file_lists[-1]

            #print file_lists
            found = False
            for testExt in skipExt:
                if file_ext == testExt:
                    #print fi, '========'
                    found = True

            if not found:
                #print fi
                logFiles.append([fi, searchDir])

    return logFiles
#-------------------------------

def copy_fun(cmd):
    os.system(cmd)
    #print '=====', cmd
   # thread.exit_thread()

def proc(srcD, tarD):
    #logFiles = ['Launch.log']
    logFiles = []
    find_log_files(unicode(srcD), logFiles)
    #return

    targDir = unicode(tarD).encode('gbk')
    if targDir[-1] != '\\':
        targDir += '\\'
        
    os.system(u'md ' + targDir)
    #os.system(u'del ' + targDir + u'*.* /s /q')
    #find_log_files(os.getcwd(), logFiles)
    #print logFiles

    pool = threadpool.ThreadPool(64)
    cmdLst = []

    for f in logFiles:        

        k = f[0].encode('gbk', 'ignore') #.decode('gbk', 'ignore')
        kdir = f[1].encode('gbk', 'ignore')

        relativeDir = kdir[len(srcD) : len(kdir)]
        subDirs = relativeDir.split('\\')

        mkDir = targDir

        #print '===========mkdirs'
        try:
            os.makedirs(targDir + relativeDir, mode=511)
        except OSError, why:
            #print 'dir already exist!'
            pass

        cmd = u'encry.exe ' + kdir + k + u' ' + targDir + relativeDir + k
        print '[src]' + kdir + k
        #print k, kdir, relativeDir, targDir + relativeDir
        #os.system(cmd)
        cmdLst.append(cmd)

    requests = threadpool.makeRequests(copy_fun, cmdLst)
    [pool.putRequest(req) for req in requests]
    pool.wait()

if __name__ == '__main__':
    proc(sys.argv[1], sys.argv[2])