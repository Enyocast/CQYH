# -*- coding:utf-8 -*-
import re
import os
import time
import sys

def rename_zip(srcPath):
    
    if srcPath[-1] != '\\':
        srcPath += '\\'
        
    print "----renaming:", srcPath
    files = os.listdir(srcPath)
   
    for fi in files:
        
        file_lists = fi.split('.') #分割出文件与文件扩展名
        file_ext = file_lists[-1] #取出后缀名(列表切片操作)
        file_name = file_lists[0]
        
        #print "split:", fi, file_name, file_ext, srcPath + fi
        if os.path.isdir(srcPath + fi):
            print "Dir:", fi
            continue
        elif os.path.isfile(srcPath + fi):
            #print "File:", fi
            if file_ext == 'zip':
                print "skip:", fi
            else:
                compName = file_name + file_ext[1] + file_ext[2] + '.cab'
                print "proc:", file_name, compName
                os.system('ren ' + srcPath + fi + ' ' + compName)
    return
            
if __name__ == '__main__':
    print sys.argv[1]
    rename_zip(sys.argv[1])
