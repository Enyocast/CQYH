# -*- coding:utf-8 -*-
import re
import os
import time
import sys

def gen_volum_info(verfrom , verto ,targetzip, vshHeadFilePath):
    
    print "processing---------", vshHeadFilePath
    
    #aod_ver = open(u'C:\\AutoBuild\\aod_pack\\aod_patch_ver.nsh', 'w')
    aod_ver = open(vshHeadFilePath, 'w')    
    
    #tmpBuf = '!define ZIP_FILE_NUM    ' + str(zipfile_cnt) + '\r\n'
    #aod_ver.write(tmpBuf)
    
    tmpBuf = '!define PRODUCTION_VERSION_FROM \"' + str(verfrom) + '\"\r\n'
    tmpBuf = tmpBuf + '!define PRODUCTION_VERSION_TO \"' + str(verto) + '\"\r\n'
    tmpBuf = tmpBuf + '!define ZIP_FILENAME \"' + str(targetzip) + '\"\r\n'
    
    aod_ver.write(tmpBuf)
    aod_ver.close()

    print '===== Write version to:', vshHeadFilePath
                  
    return
            
if __name__ == '__main__':
    print sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]
    gen_volum_info(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
