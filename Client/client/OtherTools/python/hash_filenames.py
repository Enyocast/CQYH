#coding=utf8

import re
import os
import sys
import hashlib
from multiprocessing import Pool
import shutil

#-------------------------------
def find_log_files(searchDir, logFiles):
    if searchDir[-1] != u'\\':
        searchDir += u'\\'

    files = os.listdir(searchDir)
    skipExt = ['py', 'xlsx', 'lua', 'log', 'xlsm', 'xls']
    for fi in files:
        #print fi
        if os.path.isdir(searchDir + fi):
            find_log_files(searchDir + fi, logFiles)
        elif os.path.isfile(searchDir + fi):
            file_lists = fi.split('.')
            file_ext = file_lists[-1]

            for testExt in skipExt:
                if file_ext == testExt:
                    continue
                
            logFiles.append([fi, searchDir])

    return logFiles
#-------------------------------

def my_copy_file(cmd):
    os.system(cmd)

def proc():
    #logFiles = ['Launch.log']
    logFiles = []
    find_log_files(unicode(sys.argv[1]), logFiles)
    targDir = unicode(sys.argv[2]).encode('gbk')
    if targDir[-1] != '\\':
        targDir += '\\'
        
    os.system(u'md ' + targDir)
    os.system(u'del ' + targDir + u'*.* /s /q')
    #find_log_files(os.getcwd(), logFiles)
    #print logFiles

    fileHashMap = {}

    cppFilePath = u'h:\\p4\\08.Prog\\Client\\UE3\\Development\\Src\\Core\\Src\\file_name_hash_table.cpp'
    #cppFilePath = targDir + u'file_name_hash_table.cpp'
    cppFile = open(cppFilePath, u'w+')
    #cppFile = open(u'file_name_hash_table.cpp', u'w+')
    cppFile.write(u'#include "Core.h"\n')
    cppFile.write(u'#include "FFileManagerWindows.h"\n')
    cppFile.write(u'#if M_HASH_FILE_NAME\n')
    cppFile.write(u'INT g_fileHashTableSize = ' + str(len(logFiles) * 2) + ';\n')
    cppFile.write(u'const TCHAR* g_fileHashTable[] = {\n')

    saltKey = unicode(hashlib.md5(u'HaCk#AtTaCkInG@LiOn$FiNdMe"(<={"').hexdigest()).encode('gbk')
    
    #pool = Pool(processes=10)

    copyiedFiles = []
    copyiedFilesSrc = []
    
    for f in logFiles:        
        #f = unicode(f)
        #print f, type(f)
        k = f[0].encode('gbk', 'ignore') #.decode('gbk', 'ignore')
        kdir = f[1].encode('gbk', 'ignore')
        #print k, f
        if fileHashMap.has_key(k):
            cppFile.write(u'=============')
        hk = k + saltKey
        #print k, saltKey

        file_lists = k.split('.')
        file_ext = file_lists[-1]

        hashVal = ''

        if file_ext == 'u':
            hashVal = k
        else:
            hashVal = hashlib.md5(hk).hexdigest().encode('gbk')

        copyiedFiles.append(hashVal)
        copyiedFilesSrc.append(f[0])
        cppFile.write(u'\tTEXT("')
        cppFile.write(hashVal)
        cppFile.write(u'") , TEXT("')


        foundLoc = k.find('_LOC_INT') != -1
        #foundLoc = foundLoc or (k == u'Startup.upk')
        isStartupUpk = k.find('.upk') != -1
        isStartupUdk = k.find('.udk') != -1

        if file_ext == 'u':
            print k, '.u keep original'
            cppFile.write(k)
        elif foundLoc or isStartupUpk or  isStartupUdk:
            #print file_lists[0], 'used for LOC_ file hash'
            cppFile.write(file_lists[0])
        else:
            cppFile.write(k)
            
        cppFile.write(u'"),\n')

        #if(k == u'Startup.upk'):
        #    print k

        shutil.copy(kdir + k, targDir + hashVal)
        
        #cmd = u'copy '.encode('gbk') + kdir + k + ' ' + targDir + hashVal
        #print cmd
        
        #os.system(cmd)
        #pool.apply_async(my_copy_file, [cmd])

    cppFile.write(u'};\n')
    cppFile.write(u'#endif\n')
    cppFile.flush()
    cppFile.close()

    #return
    print 'copy file completed, start checking...'
    i = 0    
    while i < len(copyiedFiles):
        if not os.path.isfile(targDir + copyiedFiles[i]):
            print copyiedFilesSrc[i], copyiedFiles[i], ' not found in target dir'
        i = i + 1
        #print i
            
    print targDir + u'file_name_hash_table.cpp', len(logFiles)

if __name__ == '__main__':
    proc()