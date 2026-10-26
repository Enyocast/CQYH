#coding=utf8

import re
import os
import sys
import hashlib

#-------------------------------
def find_log_files(searchDir, logFiles):
    if searchDir[-1] != u'\\':
        searchDir += u'\\'

    files = os.listdir(searchDir)

    for fi in files:
        #print fi
        if os.path.isdir(searchDir + fi):
            find_log_files(searchDir + fi, logFiles)
        elif os.path.isfile(searchDir + fi):
            file_lists = fi.split('.')
            file_ext = file_lists[-1]
            if file_ext != "py" and file_ext != "xlsx" and file_ext != "lua":
                logFiles.append([fi, searchDir])

    return logFiles
#-------------------------------

if __name__ == '__main__':

    #logFiles = ['Launch.log']
    logFiles = []
    find_log_files(unicode(sys.argv[1]), logFiles)
    targDir = unicode(sys.argv[2]).encode('gbk')
    if targDir[-1] != '\\':
        targDir += '\\'
        
    os.system(u'md ' + targDir)
    os.system(u'del ' + targDir + u' /s /q')
    #find_log_files(os.getcwd(), logFiles)
    #print logFiles

    fileHashMap = {}

    cppFile = open(targDir + u'file_name_hash_table.cpp', u'w+')
    #cppFile = open(u'file_name_hash_table.cpp', u'w+')
    cppFile.write(u'#include "Core.h"\n')
    cppFile.write(u'#include "FFileManagerWindows.h"\n')
    cppFile.write(u'#if M_HASH_FILE_NAME\n')
    cppFile.write(u'INT g_fileHashTableSize = ' + str(len(logFiles)) + ';\n')
    cppFile.write(u'const TCHAR* g_fileHashTable[] = {\n')

    saltKey = unicode(hashlib.md5(u'HaCk#AtTaCkInG@LiOn$FiNdMe"(<={"').hexdigest()).encode('gbk')
    
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
        hashVal = hashlib.md5(hk).hexdigest().encode('gbk')
        cppFile.write(u'\tTEXT("')
        cppFile.write(hashVal)
        cppFile.write(u'") , TEXT("')
        cppFile.write(k)
        cppFile.write(u'"),\n')
        cmd = u'copy '.encode('gbk') + kdir + k + ' ' + targDir + hashVal
        print cmd
        os.system(cmd)
        
                
    cppFile.write(u'};\n')
    cppFile.write(u'#endif\n')
    cppFile.flush()
    cppFile.close()
    print targDir + u'file_name_hash_table.cpp', len(logFiles)
