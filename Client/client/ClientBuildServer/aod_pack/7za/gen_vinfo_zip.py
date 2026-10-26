# -*- coding:utf-8 -*-
import re
import os
import time
import sys

def gen_volum_info(srcPath, volumInfoIni, verNumb, vshHeadFilePath):
    

    print "processing---------", srcPath
    files = os.listdir(srcPath)

    viFile = open(volumInfoIni, 'w+')
    viFile.write('[VolumInfo]\r\n')
    zipfile_cnt = 0
    
    for fi in files:
        
        file_lists = fi.split('.') #分割出文件与文件扩展名
        file_ext = file_lists[-1] #取出后缀名(列表切片操作)

        if len(file_lists) == 3:
            file_ext = file_lists[1] #7z
            print fi, file_lists[1]
        else:
            file_ext = file_lists[-1]
            print fi, file_lists[-1]
            
        
        if os.path.isdir(srcPath + fi):
            #print "+++", fi
            pass
        elif os.path.isfile(srcPath + fi):
            #if file_ext == '7z':
            if file_ext == 'zip' or file_ext == 'cab':
                zipfile_cnt = zipfile_cnt + 1
                fip = open(srcPath + fi, 'rb')
                fip.seek(0, 2)
                sz = fip.tell()
                fip.close()
                viFile.write(fi + '=' + str(sz) + '\r\n')
                print "---", fi, sz

    viFile.write('[VolumNum]\r\n')
    viFile.write('volumnum=' + str(zipfile_cnt) + '\r\n')
    viFile.close()

    #aod_ver = open(u'C:\\AutoBuild\\aod_pack\\aod_ver.nsh', 'w')
    aod_ver = open(vshHeadFilePath, 'w')    
    
    tmpBuf = '!define ZIP_FILE_NUM    ' + str(zipfile_cnt) + '\r\n'
    aod_ver.write(tmpBuf)
    
    tmpBuf = '!define PRODUCT_VERSION \"' + str(verNumb) + '\"\r\n'
    
    aod_ver.write(tmpBuf)
    aod_ver.close()

    print '===== Write version to:', vshHeadFilePath
                  
    return
            
if __name__ == '__main__':
    print sys.argv[1], sys.argv[2], sys.argv[3]
    gen_volum_info(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
