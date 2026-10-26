# -*- coding:utf-8 -*-
import re
import os
import time
import sys

def gen_volum_info(srcPath, volumInfoIni, verNumb, vshHeadFilePath):
    
    print "processing---------", srcPath
    
    #aod_ver = open(u'C:\\AutoBuild\\aod_pack\\aod_ver.nsh', 'w')
    aod_ver = open(vshHeadFilePath, 'w')    
    
    #tmpBuf = '!define ZIP_FILE_NUM    ' + str(zipfile_cnt) + '\r\n'
    #aod_ver.write(tmpBuf)
    
    tmpBuf = '!define PRODUCT_VERSION \"' + str(verNumb) + '\"\r\n'
    
    aod_ver.write(tmpBuf)
    aod_ver.close()

    print '===== Write version to:', vshHeadFilePath
                  
    return
            
if __name__ == '__main__':
    print sys.argv[1], sys.argv[2], sys.argv[3]
    gen_volum_info(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
