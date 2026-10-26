#coding=utf8
#!/usr/bin/env python

import os, sys, time
import re
import subprocess
import getopt
import shutil
import rtx
import datetime
from multiprocessing import Pool
import urllib
import dir_cfg
#import encode_files

is_debug = 0

g_SeekFreeMap = False
g_curVer = 0
g_change_list=0
g_label_id=0
g_use_label=0
g_update_p4=True
g_use_mpq=0
g_split_upk=0
g_useSkipUnused=False
g_branch_name=''
g_is_rebuild = False
g_NOAUTOMAPLIST = False
g_use_ver = u'0.0.0.0'

dbg_skip_compile=False
dbg_skip_split=False
dbg_skip_cook=False
dbg_skip_resref=False

p4_root = ''
p4_name = ''
p4_project_name = ''

client_code_path=[]
client_build_UE3_path=''

tmpCookDir = dir_cfg.tmpCfgDir
client_pdb_path = dir_cfg.client_pdb_path

#p4_cmd = "p4 sync -q %s"

vs_evn_cmd = r'%comspec% /k "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/vcvarsall.bat" x64'
vs_evn_cmd_2010_x86 = r'%comspec% /k "F:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/vcvarsall.bat" x86'
vs_evn_cmd_2010_x64 = r'%comspec% /k "F:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/vcvarsall.bat" x86_amd64'

debug_log_file = './debug.log'
compile_flag_path_client = 'is_compile_client'
compile_flag_path_cook = 'is_cook_client'
flag_f_debuglog = None
flag_f_client = None
flag_f_cook = None


cl_r = re.compile('Change (\d+?) on')
name_r = re.compile('by (.*?)\@')
err_r = re.compile('(\d+?) Error\(s\)')

os.environ['P4PORT'] = '172.30.66.41:1668'
os.environ['P4USER'] = 'AutoBuild'
if is_debug:
    os.environ['P4CLIENT'] = 'autobuild_cw'
else:
    os.environ['P4CLIENT'] = 'autobuild_BUILDC_8089'
os.environ['P4PASSWD'] = 'qwe123!@#'

def del_file(fileName):
    cmdStr = 'del /F /Q ' + fileName
    os.system(cmdStr)

print 'shit'
def get_vs_bat():
    return vs_evn_cmd_2010_x86

def update_version(ver):
    print('------------- write ver file to %d' % ver)
    #os.system(('del /F /Q ..\\source\\08.Prog' + g_branch_name + '\\Common\\define\\version.h'))
    del_file('..\\source\\08.Prog' + g_branch_name + '\\Common\\define\\version.h')
    os.system(('echo #ifndef _VERSION_H_ > ..\\source\\08.Prog' + g_branch_name + '\\Common\\define\\version.h'))
    os.system(('echo #define _VERSION_H_ >> ..\\source\\08.Prog' + g_branch_name + '\\Common\\define\\version.h'))
    os.system(('echo #define MAJOR_VERSION (0) >> ..\\source\\08.Prog' + g_branch_name + '\\Common\\define\\version.h'))
    os.system(('echo #define MINOR_VERSION (1) >> ..\\source\\08.Prog' + g_branch_name + '\\Common\\define\\version.h'))
    os.system((('echo #define BUILD_NUMBER (%d) >> ..\\source\\08.Prog' + g_branch_name + '\\Common\\define\\version.h') % ver))
    os.system((('echo #define MMO_GAME_VER TEXT("%s") >> ..\\source\\08.Prog' + g_branch_name + '\\Common\\define\\version.h') % g_use_ver))
    os.system(('echo #endif //_VERSION_H_ >> ..\\source\\08.Prog' + g_branch_name + '\\Common\\define\\version.h'))

    return True
	
def get_cur_version(d):
    global g_curVer
    print '-------------  cur_version : %d' % (g_curVer)
    return g_curVer

#    max_v = 0
#    r = cl_r.findall(run_cmd('p4 changelists -m 1 %s' % (d)))
#    if r and r[0]:
#        v = int(r[0])
#        print '-------------  cur_version %s version: %d' % (d, v)
#        max_v = max(max_v, v)
#        return max_v
#    else:
#        return 0

def run_cmd(cmd):
    p = subprocess.Popen(args=cmd, shell=True,
                         stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    return p.stdout.read()

    
def init_p4_data():
    global p4_root
    buf = run_cmd('p4 info')
    l = buf.split('\n')
    for i in l:
        if i.find('Client root') >= 0:
            idx = i.find(':')
            p4_root = i[idx + 1:].strip().rstrip()
    return p4_root


#---------------------------
# build client
#---------------------------
   
def print_debug_info(prefix):
    print '============[ ', prefix, ' ]============'
    print ' g_branch_name:', g_branch_name
    print ' g_change_list:', g_change_list
    print ' g_use_label:', g_use_label
    print ' g_label_id:', g_label_id
    print ' g_use_mpq:', g_use_mpq
    print ' g_useSkipUnused:', g_useSkipUnused
    print ' g_is_rebuild:', g_is_rebuild
    print ' g_NOAUTOMAPLIST:', g_NOAUTOMAPLIST
    print ' g_use_ver:', g_use_ver
    print '============[#', prefix, '#]============'

def compile_info_client():
    global flag_f_client
    retVal = False
    buf = ''
    if os.path.isfile(compile_flag_path_client):
        buf = open(compile_flag_path_client, 'r').read()
        retVal = True
        #return True, buf

    if os.path.isfile(compile_flag_path_cook):
        #buf = buf + open(compile_flag_path_cook, 'r').read()
        #return True, buf
        retVal = True

    logFile = dir_cfg.get_game_log_dir(g_branch_name) + 'Launch.log'
    if os.path.isfile(logFile):
        buf = buf + open(logFile, 'r').read()
    #print buf
    return retVal, buf


def start_debug_log():
    global flag_f_debuglog
    global debug_log_file

    #print '--- before:', debug_log_file
    if flag_f_debuglog != None:
        return False

    #print '==== after:', debug_log_file
    flag_f_debuglog = open(debug_log_file, 'w')
    return True


def debug_log(str):
    global flag_f_debuglog

    if flag_f_debuglog == None:
        start_debug_log()

    flag_f_debuglog.write(str)
    flag_f_debuglog.flush()


def run_console_cmd(cmdStr):
    debug_log(cmdStr + '\n')
    os.system(cmdStr)
    print '##### run_console_cmd:', cmdStr


def start_compile_client():
    global flag_f_client
    if os.path.isfile(compile_flag_path_client):
        return False
    flag_f_client = open(compile_flag_path_client, 'w')
    return True


    
def stop_compile_client():
    global flag_f_client
    print "*********** stop_compile_client"
    if flag_f_client != None:
        flag_f_client.close()
        #os.remove(compile_flag_path_client)
        os.system('del /Q ' + compile_flag_path_client)
        flag_f_client = None

def is_building():
    global flag_f_cook
    if os.path.isfile(compile_flag_path_client):
        print '*** is building!!!'
        return True
    return False

def is_cooking():
    global flag_f_cook
    if os.path.isfile(compile_flag_path_cook):
        print '*** is cooking!!!'
        return True
    return False

def start_cook_client():
    global flag_f_cook
    if os.path.isfile(compile_flag_path_cook):
        return False
    flag_f_cook = open(compile_flag_path_cook, 'w')
    return True



def stop_cook_client():
    global flag_f_cook
    print "*********** stop_compile_client"

    if flag_f_cook != None:
        flag_f_cook.close()
    os.system('del /Q ' + compile_flag_path_cook)
    #os.remove(compile_flag_path_cook)


    
def compile_fail_info_client(v, info):
    file_path = 'static/%s_%s_err_client.txt' % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()), v)
    open(file_path, 'w').write(info)



def compile_fail_info_clientsript(v, info):
    file_path = 'static/%s_%s_err_clientscript.txt' % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()), v)
    open(file_path, 'w').write(info)


    
def compile_devclient(compile_type):
    global flag_f_client
    client_sln_path=r'../source/08.Prog' + g_branch_name + '/Client/UE3/Development/Src/UE3.sln'
    print '------------- Try to compile client exe: ', client_sln_path
    os.path.join(p4_root, vs_evn_cmd_2010_x86)
    p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
        stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    #compile_type = 'Release|Mixed platforms'
    if g_is_rebuild:
        #exec_cmd = 'devenv "%s" /Rebuild "%s"\n' % (client_sln_path, compile_type)
        exec_cmd = 'devenv "%s" /Rebuild "%s"\n' % (client_sln_path, compile_type)
    else:
        exec_cmd = 'devenv "%s" /build "%s"\n' % (client_sln_path, compile_type)

    print exec_cmd

    p.stdin.write(exec_cmd)
    p.stdin.write('exit\n')
    
    result_str = ''
    while True:
        buf = p.stdout.read(8)
        if not buf:
            break

        if flag_f_client != None:
            flag_f_client.write(buf)
            flag_f_client.flush()

        result_str += buf

    return result_str

def cook_data(exePath, isFull):
#    global dbg_skip_resref
    global flag_f_client

    p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
        stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    if g_useSkipUnused:
        #if not dbg_skip_resref:
        #    gen_res_ref_table()

        if isFull:
            if g_NOAUTOMAPLIST:
                exec_cmd = '%s CookPackages -SKIPUNUSED -platform=PC -log -Processes=32 -AUTOCOOKMAPS -final_release -multilanguagecook=INT+CHN -BUILDMACHINE -DEMOMODE -NOPAUSE -full -NOAUTOMAPLIST -SAVESHADERSATEND'% (exePath)
            else:
                exec_cmd = '%s CookPackages -SKIPUNUSED -platform=PC -log -Processes=32 -AUTOCOOKMAPS -final_release -multilanguagecook=INT+CHN -BUILDMACHINE -DEMOMODE -NOPAUSE -full -SAVESHADERSATEND' % (exePath)
        else:
            if g_NOAUTOMAPLIST:
                exec_cmd = '%s CookPackages -SKIPUNUSED -platform=PC -log -Processes=32 -AUTOCOOKMAPS -final_release -multilanguagecook=INT+CHN -BUILDMACHINE -DEMOMODE -NOPAUSE -NOAUTOMAPLIST -SAVESHADERSATEND' % (exePath)
            else:
                exec_cmd = '%s CookPackages -SKIPUNUSED -platform=PC -log -Processes=32 -AUTOCOOKMAPS -final_release -multilanguagecook=INT+CHN -BUILDMACHINE -DEMOMODE -NOPAUSE -SAVESHADERSATEND' % (exePath)
    else:
        if isFull:
            if g_NOAUTOMAPLIST:
                exec_cmd = '%s CookPackages -platform=PC -log -Processes=32 -AUTOCOOKMAPS -final_release -multilanguagecook=INT+CHN -BUILDMACHINE -DEMOMODE -NOPAUSE -full -NOAUTOMAPLIST -SAVESHADERSATEND' % (exePath)
            else:
                exec_cmd = '%s CookPackages -platform=PC -log -Processes=32 -AUTOCOOKMAPS -final_release -multilanguagecook=INT+CHN -BUILDMACHINE -DEMOMODE -NOPAUSE -full -SAVESHADERSATEND' % (exePath)
        else:
            if g_NOAUTOMAPLIST:
                exec_cmd = '%s CookPackages -platform=PC -log -Processes=32 -AUTOCOOKMAPS -final_release -multilanguagecook=INT+CHN -BUILDMACHINE -DEMOMODE -NOPAUSE -NOAUTOMAPLIST -SAVESHADERSATEND' % (exePath)
            else:
                exec_cmd = '%s CookPackages -platform=PC -log -Processes=32 -AUTOCOOKMAPS -final_release -multilanguagecook=INT+CHN -BUILDMACHINE -DEMOMODE -NOPAUSE -SAVESHADERSATEND' % (exePath)

    if g_SeekFreeMap:
        exec_cmd = exec_cmd + ' -SEEKFREEMAP\n'
    else:
        exec_cmd = exec_cmd + '\n'

    print p, exec_cmd    
    p.stdin.write(exec_cmd)
    p.stdin.write('exit\n')
    
    result_str = ''
    while True:
        buf = p.stdout.read(8)
        if not buf:
            break

        if flag_f_client != None:
            flag_f_client.write(buf)
            flag_f_client.flush()

        #if flag_f_cook != None:
        #    flag_f_cook.write(buf)
        #    flag_f_cook.flush()

        result_str += buf

    return result_str

def compile_client_script(buildArg):
    global flag_f_client
  
    os.path.join(p4_root, vs_evn_cmd_2010_x86)
    p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
        stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    
    exec_cmd = '..\\source\\08.Prog' + g_branch_name + '\\Client\\UE3\\Binaries\\Win64\\MMOGame.com make -auto -DEMOMODE -NOPAUSEONSUCCESS -full ' + buildArg + '\n'
    
    print '------------- Try to compile client script: ', exec_cmd
    
    p.stdin.write(exec_cmd)
    #p.stdin.write('pause\r\n')
    p.stdin.write('exit\n')
    
    result_str = ''
    while True:
        buf = p.stdout.read(8)
        if not buf:
            print '!!!!!!!!!!!!!!!break reading....'
            break

        if flag_f_client != None:
            flag_f_client.write(buf)
            flag_f_client.flush()

        result_str += buf
        #print buf

    print '------------ compile_client_script:', result_str
    return result_str

def get_exe_path():
    global g_split_upk
    if g_split_upk:
        return tmpCookDir + 'Binaries\\Win64\\MMOGame.exe'
    else:
        return '..\\source\\08.Prog' + g_branch_name + '\\Client\\UE3\\Binaries\\Win64\\MMOGame.exe'

def run_cmdlet(buildArg):
    global flag_f_client

    os.path.join(p4_root, vs_evn_cmd_2010_x86)
    p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
        stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    exec_cmd = '..\\source\\08.Prog' + g_branch_name + '\\Client\\UE3\\Binaries\\Win64\\MMOGame.exe ' + buildArg + ' -BUILDMACHINE -DEV_RELEASE -NOPAUSE -DEMOMODE\n'
    #exec_cmd = '..\\source\\08.Prog' + g_branch_name + '\\Client\\UE3\\Binaries\\Win32\\MMOGame.exe ' + buildArg + ' -DEV_RELEASE -NOPAUSE -DEMOMODE\n'

    print '------------- Try to run_cmdlet: ', exec_cmd

    p.stdin.write(exec_cmd)
    p.stdin.write('exit\n')

    result_str = ''
    while True:
        buf = p.stdout.read(8)
        if not buf:
            print '!!!!!!!!!!!!!!!break reading....'
            break

        if flag_f_client != None:
            flag_f_client.write(buf)
            flag_f_client.flush()

        result_str += buf
        #print buf

    print '------------ run_cmdlet:', result_str
    return result_str

def compile_dev_client(v, compile_type):
    #print '------------- compile_dev_client', v
    result_str = compile_devclient(compile_type)
    #rr = err_r.findall(result_str)
    if result_str.find('Build FAILED.') >= 0:
        compile_fail_info_client(v, result_str)
        return False, result_str

    return True, result_str

def compile_dev_client_script(v, buildArg):
    print '------------- compile_dev_client_script', v
    result_str = compile_client_script(buildArg)
    print '--------------compile script result:', result_str
    if result_str.find('Success') < 0:
        compile_fail_info_clientsript(v, result_str)
        return False, result_str

    return True, result_str

def gen_ver_ini(ver, inIniPath):
    #os.system(p4_checkout_ver)
    
    #os.remove(defaultver_localpath)
    #os.mkdir(iniPath)
    iniPath = inIniPath
    #inIniPath.replace('edition', 'edition\\' + g_branch_name)
    print '-------- gen_ver_ini:', iniPath
    ver_f = open(iniPath, 'w+')
    #ver_info = '[ver]\r\nChangeList=%s' % ver
    ver_info = '%s' % ver
    print '------------- gen_ver_ini' + ver_info
    ver_f.write(ver_info)
    ver_f.flush()
    ver_f.close()
    

def update_client_code(inIniPath, useLabel, clNum, labNum):
    global g_curVer

    iniPath = inIniPath.replace('edition', 'edition\\' + g_branch_name)
    print '------------- update_client_code...', iniPath, useLabel, clNum, labNum, g_branch_name
    max_v = 0
    name = ''

    p4_cmd = "p4 sync -q "
    
    for d in client_code_path:
        if useLabel:
            exec_cmd = p4_cmd + "-n " + d + " @LC" + str(labNum)
            max_v = labNum
        else:
            exec_cmd = p4_cmd + d + ' ' + str(clNum)
            max_v = clNum

        
        os.system(exec_cmd)
        print '------------- update_client_code...', exec_cmd
        print '------------- update_client_code...', iniPath, useLabel, clNum, labNum, g_branch_name
        
        #bbuf = run_cmd('p4 changelists -m 1 %s' % (d))
        #print bbuf
        #r = cl_r.findall(bbuf)
        #nr = name_r.findall(bbuf)
        #print '------------- p4 changelists -m 1 %s' % (d)
        #if r and r[0]:
        #    v = int(r[0])
        #    print '------------- %s version: %d' % (d, v)
        #    max_v = max(max_v, v)
        #    if max_v == v:
        #        if nr and nr[0]:
        #            name = nr[0]
        #else:
        #    #sys.abort()
        #    pass

    # generate client ver ini file
    gen_ver_ini(max_v, iniPath)    

    g_curVer = int(max_v)
    return int(max_v), name



#----------------------------------------------
# compile client
#----------------------------------------------

#client_qa_path= dir_cfg.client_qa_path

def copy_for_qa(ver, binDir, scriptDir, inTargetDir, inPatchDir):

    targetDir = inTargetDir.replace('edition', 'edition\\' + g_branch_name)
    patchDir = inPatchDir.replace('aodpatch', 'aodpatch\\' + g_branch_name)

    #copy_client_ver_files = 'copy ' + defaultver_localpath + ' ' + targetDir + 'DefaultVer.ini /Y '
    copy_client_bin_files = 'robocopy ' + client_build_UE3_path + 'Binaries\\ ' + targetDir + binDir + '\\ *.* /MT:32 /E /NFL'
    copy_client_bin_files32 = 'robocopy ' + client_build_UE3_path + 'Binaries\\Win32\\ ' + targetDir + binDir + '\\Win32\\ *.* /MT:32 /E /NFL'
    copy_client_bin_files64 = 'robocopy ' + client_build_UE3_path + 'Binaries\\Win64\\ ' + targetDir + binDir + '\\Win64\\ *.* /MT:32 /E /NFL'
    copy_client_script_files = 'robocopy ' + client_build_UE3_path + scriptDir + '\\ ' + targetDir + scriptDir + '\\ *.* /MT:32 /E /NFL'
    #copy_client_editor_files = 'copy ' + client_build_UE3_path + 'Binaries\\UnrealEdCSharp.dll ' + targetDir + '\\UnrealEdCSharp.dll' + ' /Y'

    os.system(copy_client_bin_files)
    os.system(copy_client_bin_files32)
    os.system(copy_client_bin_files64)
    os.system(copy_client_script_files)
    #os.system(copy_client_ver_files)
    #os.system(copy_client_editor_files)

    print copy_client_bin_files
    print copy_client_bin_files32
    print copy_client_bin_files64
    print copy_client_script_files
    #print copy_client_editor_files

    cpyCmd = 'ViGenerator.exe ' + targetDir + ' ' + patchDir
    os.system(cpyCmd)
    os.system(cpyCmd)
    #os.system('pause')

#def _compile_client2(scriptVer, cppVer, scriptDir, binDir, patchDir):
#    print '------------- Compile Client...', scriptVer, cppVer, scriptDir, binDir, patchDir
#    copy_for_qa(19888, binDir, scriptDir, client_qa_path, patchDir)

    
    
def _compile_client(scriptVer, cppVer, scriptDir, binDir, patchDir, iniPath, copyForQA=True):
    print '------------- Compile Client...', scriptVer, cppVer, scriptDir, binDir

    print '------------- Init P4'
    #start_compile_client()
    #result, buf = compile_dev_client_script(111, scriptVer)
    #stop_compile_client()
    #return

    if not init_p4_data():
        sys.stderr.write('------------- Client Init p4 failed.\n')
        return False
    v = 0
    name = ''

    #if g_update_p4:
    v, name = update_client_code(iniPath, g_use_label, g_change_list, g_label_id)
    #else
    #v = g_l

    if not v:
        sys.stderr.write('------------- Client update codes fail.\n')
        return False
    print '------------- Update client to:%d' % v
	
    update_version(v)

    if not start_compile_client() :
        sys.stderr.write('------------- _compile_client is Compiling, abort action!\n')
        return False
    #    sys.exit(-1)


    #result, buf = compile_dev_client_script(v, scriptVer)
    result, buf = compile_dev_client(v, cppVer)
    #result = True
    #buf = 'xxx'

    log_file = open(dir_cfg.get_compile_log_file(str(v)), 'w')
    log_file.write(buf)
    log_file.close()

    log_url = (u'http://172.30.66.33/buildlog/%s.log' % str(v))
    
    if not result:    
        print '---------- build_review Compile failed!'        
        rtx.send_msg_prog((u'分支【%s】 \n编译失败，请修正!\n ChangeList:%s, 提交人:%s \n Log:[%s|%s]' % (g_branch_name, (v), name, log_url, log_url)))
        return False

    result, buf = compile_dev_client_script(v, scriptVer)

    p4_cmd = 'p4 revert //AgeOfDawn/08.Prog' + g_branch_name + '/Client/UE3/Development/Src/MMOGame/Inc/...'
    os.system(p4_cmd)

    #result, buf
    #result = 1
    if result:
        print '---------- Client Compile ok, starting copy...'
        make_doodad_quest_cfg(True)

        if not is_debug and not g_use_label:
            label_cmd = 'p4 tag -a -l LC' + str(v) + ' //AgeOfDawn/08.Prog' + g_branch_name + '/...@' + str(v)
            os.system(label_cmd)
            print label_cmd

    #复制到中间目录供QA更新
        if copyForQA:
            copy_for_qa(v, binDir, scriptDir, dir_cfg.client_qa_path, patchDir)


        #stop_compile_client()
        #vv = 'bin_%d_%s' % (v, time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()))
        #ver_path = '%s/%s' % (output_root, vv)
        if copyForQA and binDir == 'BinariesEditor':
            rtx.send_msg_qa((u'分支【%s】 \nEditor编译成功%s %s\nChangeList:%s' % (g_branch_name, scriptVer, cppVer, str(v))))
        elif copyForQA:
            rtx.send_msg_qa((u'分支【%s】 \n游戏编译成功%s %s.\nChangeList:%s' % (g_branch_name, scriptVer, cppVer, str(v))))

        return True
        #sys.exit(0)
    else:
        print '---------- Client Compile failed!'
        stop_compile_client()

        log_file = open(dir_cfg.get_compile_log_file(str(v)), 'w')
        log_file.write(buf)
        log_file.close()

        log_url = (u'http://172.30.66.33/buildlog/%s.log' % str(v))

        rtx.send_msg_prog((u'分支【%s】 \n客户端版本编译失败! %s %s\n ChangeList:%s, 最晚提交:%s \n Log:[%s|%s]' % (g_branch_name, scriptVer, cppVer, str(v), name, log_url, log_url)))
        #sys.exit(-1)
        return False



def _release_client(inTargetDir, scriptDirName, binDirName, copyToBackupServer, inPatchDir, inIniPath):

    targetDir = inTargetDir.replace('edition', 'edition\\' + g_branch_name)
    patchDir = inPatchDir.replace('aodpatch', 'aodpatch\\' + g_branch_name)
    iniPath = inIniPath.replace('edition', 'edition\\' + g_branch_name)


	#copy_client_ver_files = 'copy ' + defaultver_lcompile_client_scriptocalpath + ' ' + targetDir + 'DefaultVer.ini /Y '
   # copy_client_bin_files = 'xcopy ' + client_build_UE3_path + 'Binaries/*.* ' + targetDir + '/' + binDir + '/ /S /F /Y /R'
    #copy_client_script_files = 'xcopy ' + client_build_UE3_path + 'MMOGame/' + scriptDir + '/*.* ' + targetDir + '/' + scriptDir + ' /S /F /Y /R'
    #copy_client_editor_files = 'copy ' + client_build_UE3_path + 'Binaries/UnrealEdCSharp.dll ' + targetDir + '/UnrealEdCSharp.dll' + ' /Y'


    #copy_client_bin_files = 'xcopy ' + client_qa_path + '*.* ' + client_bin_release_path + ' /S /F /Y /R'
    #copy_client_script_files = 'xcopy ' + client_scriptout_path + '*.* ' + client_script_release_path + ' /S /F /Y /R'
    #copy_client_ver_files = 'copy ' + client_veriniout_path + ' ' + defaultver_localpath + ' /Y '

    #copy_client_editor_files = 'copy ' + client_binout_editor_dll_path + ' ' + client_release_editor_dll_path + ' /Y '

    client_qa_path = dir_cfg.client_qa_path.replace('edition', 'edition\\' + g_branch_name)
    copy_to_pubb = 'robocopy ' + client_qa_path + binDirName + '\\ ' + targetDir +  binDirName + '\\ *.* /MT:32 /E /NFL'
    copy_to_pub1 = 'robocopy ' + client_qa_path + binDirName + '\\ ' + targetDir +  binDirName + '\\ MMOGame.* /MT:32 /E /NFL'
    copy_to_pub2 = 'robocopy ' + client_qa_path + scriptDirName + '\\ ' + targetDir +  scriptDirName + '\\ *.* /MT:32 /E /NFL'
    copy_to_pub3 = 'copy ' + iniPath + " " + targetDir + binDirName + '\\ /Y'
    copy_to_pub4 = 'robocopy ' + client_qa_path + ' ' + targetDir +' *.dll /MT:32 /E /NFL'

    print '----------' + copy_to_pubb
    print '----------' + copy_to_pub1
    print '----------' + copy_to_pub2
    print '----------' + copy_to_pub3
    print '----------' + copy_to_pub4

    os.system(copy_to_pubb)
    os.system(copy_to_pub1)
    os.system(copy_to_pub2)
    os.system(copy_to_pub3)
    #os.system(copy_to_pub4)


    targetDirList = [
	'\\\\172.30.68.104\\Edition\\',
	'\\\\172.30.68.148\\Edition\\'
	]

    if copyToBackupServer:
        for pubDir in targetDirList:
            #copy_to_tar = 'xcopy ' + client_qa_path + '*.* ' + pubDir +' /S /F /Y /R'
            #os.system(copy_to_tar)
            #print '----------' + copy_to_tar
            copy_to_pubd1 = 'xcopy ' + client_qa_path + binDirName + '\\MMOGame*.* ' + pubDir +  binDirName + '\\ /S /F /Y /R'
            copy_to_pubd2 = 'xcopy ' + client_qa_path + scriptDirName + '\\*.* ' + pubDir +  scriptDirName + '\\ /S /F /Y /R'
            copy_to_pubd3 = 'copy ' + client_qa_path + '\\*.ini ' + pubDir +'\\ /Y'

            print '----------' + copy_to_pubd1
            os.system(copy_to_pubd1)

            print '----------' + copy_to_pubd2
            os.system(copy_to_pubd2)

            print '----------' + copy_to_pubd3
            os.system(copy_to_pubd3)

    ver_f = open(iniPath, 'r')
    v = ver_f.read()

    pdbPath = client_pdb_path + v + '\\Win32'

    cpyCmd = dir_cfg.rar_exe + ' a -r ' + pdbPath + '\\' + str(v) + '.rar ' + dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\Development\\Intermediate\\*.cpp'
    os.system(cpyCmd)

    cpyCmd = 'xcopy ' + client_qa_path + binDirName + '\\Win32\\MMOGame.exe ' + pdbPath + '\\ /Y /Q'
    os.system(cpyCmd)
    print '----------' + cpyCmd

    cpyCmd = 'xcopy ' + client_qa_path + binDirName + '\\Win32\\MMOGame.pdb ' + pdbPath + '\\ /Y /Q'
    os.system(cpyCmd)

    cpyCmd = 'xcopy ' + client_qa_path + binDirName + '\\Win32\\MMOGame-Win32-Shipping.exe ' + pdbPath + '\\ /Y /Q'
    os.system(cpyCmd)
    cpyCmd = 'xcopy ' + client_qa_path + binDirName + '\\Win32\\MMOGame-Win32-Shipping.pdb ' + pdbPath + '\\ /Y /Q'
    os.system(cpyCmd)

    print '----------' + cpyCmd

    pdbPath = client_pdb_path + v + '\\Win64'

    cpyCmd = 'xcopy ' + client_qa_path + binDirName + '\\Win64\\MMOGame.exe ' + pdbPath + '\\ /Y /Q'
    os.system(cpyCmd)
    print '----------' + cpyCmd

    cpyCmd = 'xcopy ' + client_qa_path + binDirName + '\\Win64\\MMOGame.pdb ' + pdbPath + '\\ /Y /Q'
    os.system(cpyCmd)

    #print '----------' + cpyCmd

    pdbPath = client_pdb_path + v
    cpyCmd = 'xcopy ' + client_qa_path + '\\' + scriptDirName + '\\*.* ' + pdbPath + '\\' + scriptDirName + '\\ /S /F /Y /R /Q'
    os.system(cpyCmd)
    print '----------' + cpyCmd

    cpyCmd = 'ViGenerator.exe ' + targetDir + ' ' + patchDir
    #cpyCmd = 'copy ' + client_qa_path + 'UnrealEdCSharp.dll ' + pdbPath + '\\UnrealEdCSharp.dll' + ' /Y'
    os.system(cpyCmd)
    os.system(cpyCmd)
    print '----------' + cpyCmd

    if g_branch_name == '_Stable':
        cmd_str = dir_cfg.get_bat_file_path('update_to_08.bat')
        os.system(cmd_str)
    return v


def compile_client():
    if is_cooking():
        rtx.send_msg(u'数据烘焙中，无法编译版本!')
        return
    rtxmsg = (u'分支【%s】 \n开始编译游戏\n运营版本号：%s') % (g_branch_name, str(g_use_ver))
    rtx.send_msg(rtxmsg)
    _compile_client('-DEV_RELEASE', 'Release|Mixed platforms', 'MMOGame\\ScriptDevRelease', 'BinariesDev', dir_cfg.qaclient_bin_patch, dir_cfg.dev_ver_ini)
    stop_compile_client()

def compile_editor():
    if is_cooking():
        rtx.send_msg(u'数据烘焙中，无法编译版本!')
        return

    rtxmsg = (u'分支【%s】 \n开始编译Editor') % (g_branch_name)
    rtx.send_msg(rtxmsg)
    _compile_client('-EDITOR_RELEASE', 'ReleaseEditor|Mixed platforms', 'MMOGame\\ScriptEditorRelease', 'BinariesEditor', dir_cfg.qaeditor_bin_patch, dir_cfg.editor_ver_ini)
    stop_compile_client()

def del_cook_log():
    cpyCmd = 'del ' + dir_cfg.get_game_log_dir('') + '*.log /q'
    #os.system(cpyCmd)

def make_doodad_quest_cfg(submitToP4):
    if submitToP4:
        p4_file = '//AgeOfDawn/08.Prog' + g_branch_name + '/Client/UE3/MMOGame/Config/quest_doodad.txt'
        p4_cmd = 'p4 edit ' + p4_file
        os.system(p4_cmd)
    else:
        del_file('..\\source\\08.Prog' + g_branch_name + '\\Client\\UE3\\MMOGame\\Config\\quest_doodad.txt')

    run_cmdlet('MakeQuestDoodadDropData')

    if submitToP4:
        p4_cmd = 'p4 revert -a'
        os.system(p4_cmd)

        p4_cmd = 'p4 resolve -ay'
        os.system(p4_cmd)

        p4_cmd = 'p4 submit -d AutoMakeQuestDoodadDropData'
        os.system(p4_cmd)

def compile_shipping(isFull):

    # split upk -> cook -> copy to temp dir -> encrypt -> snapshot -> pack MPQ -> pack install

    global g_curVer
    global g_change_list
    global g_label_id
    global g_use_label
    global g_branch_name
    global g_is_rebuild
    global g_NOAUTOMAPLIST
    global dbg_skip_cook
    global dbg_skip_compile
    global dbg_skip_split
    global dbg_skip_resref
    global dbg_skip_resref

    #start_cook_client()
    #start_compile_client()
    #run_cmdlet('MakeQuestDoodadDropData')
    #stop_compile_client()
    #stop_cook_client()
    #return

    if is_cooking():
        rtx.send_msg(u'数据烘焙中...!')
        return False

    print g_branch_name, dbg_skip_cook, isFull
    #return False

    start_cook_client()

    debug_skip = 0

    del_cook_log()

    startTime = datetime.datetime.now()

    if not debug_skip:
        rtxmsg = (u'[1/7]分支【%s】 \n编译Release|Mixed platforms开始，请不要再次点击编译发行版本...\n运营版本号：%s\nChangeList:%s') % (g_branch_name, g_use_ver, str(g_label_id))
        rtx.send_msg_qa(rtxmsg)

    #if not start_compile_client():
    #    return False


    #'''

    shippingVerIni = dir_cfg.shipping_ver_ini.replace('edition', 'edition\\' + g_branch_name)
    gen_ver_ini(g_label_id, shippingVerIni)
    shippingVerIni = dir_cfg.shipping_ver_ini

    if not debug_skip and not dbg_skip_compile:
        result = True
        #_compile_client('-DEV_RELEASE', 'ReleaseX64|Mixed platforms', 'MMOGame\\ScriptDevRelease', 'BinariesShipping', dir_cfg.shipping_bin_patch, shippingVerIni, False)
        make_doodad_quest_cfg(False)
        #run_cmdlet('MakeQuestDoodadDropData')

    if not debug_skip and not dbg_skip_compile:
        if not result:
            stop_compile_client()
            stop_cook_client()
            return False

    if not debug_skip and not dbg_skip_compile:
        compile_client_script('-FINAL_RELEASE')

    if not debug_skip and not dbg_skip_compile:
        rtxmsg = (u'[2/7]分支【%s】 \n编译Shipping|Mixed platforms开始...\n运营版本号：%s\nChangeList:%s') % (g_branch_name, g_use_ver, str(g_label_id))
        rtx.send_msg_qa(rtxmsg)
        #每次都要REBUILD SHIPPING保证版本号正确链接到EXE的VER INFO中
        g_is_rebuild = True
        result_str = compile_devclient('Shipping|Mixed platforms')

    if not debug_skip and not dbg_skip_compile:
        if result_str.find('Build FAILED.') >= 0:

            ship_log_file = open(dir_cfg.get_compile_log_file(str(g_label_id)), 'w')
            ship_log_file.write(result_str)
            ship_log_file.close()
            ship_log_url = (u'http://172.30.66.33/buildlog/%s.log' % str(g_label_id))
            rtxmsg = (u'分支【%s】 \n编译SHIPPING失败，请修正!\nChangeList:%s\nLog:[%s|%s]') % (g_branch_name, str(g_label_id), ship_log_url, ship_log_url)
            rtx.send_msg_prog(rtxmsg)
            stop_compile_client()
            stop_cook_client()
            return False

    #if not debug_skip:
    #    rtx.send_msg_qa(u'[3/7]--编译发行版本EXE完成， 等待...')

    #复制到另一个地方

    if g_split_upk and not dbg_skip_split:
        rtxmsg = (u'[3/7]分支【%s】 \n开始复制目录准备分割...\n运营版本号：%s\nChangeList:%s') % (g_branch_name, g_use_ver, str(g_label_id))
        rtx.send_msg_qa(rtxmsg)

        cpyCmd = dir_cfg.bat_dir + '_copy_to_tmp_cook.bat ' + client_build_UE3_path + ' ' + tmpCookDir
        #cpyCmd = 'robocopy ' + client_build_UE3_path + ' ' + tmpCookDir + ' *.* /MIR /MT:32 /NFL'
        print cpyCmd
        #os.system('pause')
        os.system(cpyCmd)

        #cpyCmd = 'attrib -R /S ' + tmpCookDir + '*.*'
        #os.system(cpyCmd)


    #if g_useSkipUnused and not dbg_skip_resref:
        #gen_res_ref_table()
        #pass

    if g_split_upk and not dbg_skip_split:
        rtxmsg = (u'[4/7]分支【%s】 \n开始分割数据...\n运营版本号：%s\nChangeList:%s') % (g_branch_name, g_use_ver, str(g_label_id))
        rtx.send_msg_qa(rtxmsg)
        cookExe = tmpCookDir + 'Binaries\\Win64\\MMOGame.exe'
        cpyCmd = cookExe + ' ExportAllObjectMT ..\\..\\MMOGame\\Content\\MMOContent  -Processes=32 -BUILDMACHINE -DEMOMODE -NOPAUSE -DEV_RELEASE'
        os.system(cpyCmd)

    if g_useSkipUnused and not dbg_skip_resref:
        gen_res_ref_table()

    #rtxmsg = (u'[3/7]分支【%s】 \n编译Shipping|Mixed platforms完成，开始烘焙数据，请耐心等待...\n运营版本号：%s') % (g_branch_name, g_use_ver)
    #rtx.send_msg_qa(rtxmsg)

    if not dbg_skip_cook:
        #result = _compile_client('-DEV_RELEASE', 'Release|Mixed platforms', 'MMOGame\\ScriptDevRelease', 'BinariesShipping', 'D:\\xampp\\htdocs\\aodpatch\\shipping_bin_patch\\', shippingVerIni, False)
        if not debug_skip:
            #rtx.send_msg_qa(u'[3/6]--编译Shipping|Mixed platforms完成，开始烘焙数据，请耐心等待...')
            rtxmsg = (u'[3/7]分支【%s】 \n编译Shipping|Mixed platforms完成，开始烘焙数据，请耐心等待...\n运营版本号：%s\nChangeList:%s') % (g_branch_name, g_use_ver, str(g_label_id))
            rtx.send_msg_qa(rtxmsg)
            if g_split_upk:
                cookExe = tmpCookDir + 'Binaries\\Win64\\MMOGame.exe'
            else:
                cookExe = dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\Binaries\\Win64\\MMOGame.exe'
            cook_data(cookExe, isFull)

        if not debug_skip:
            rtxmsg = (u'[4/7]分支【%s】 \n烘焙数据完成，正在准备安装目录结构，请耐心等待...\n运营版本号：%s\nChangeList:%s') % (g_branch_name, g_use_ver, str(g_label_id))
            rtx.send_msg_qa(rtxmsg)
            #rtx.send_msg_qa(u'[4/6]--烘焙数据完成，正在准备安装目录结构，请耐心等待...')
    else:
        rtxmsg = (u'[3-4/7]分支【%s】 \n跳过烘焙数据，正在准备安装目录结构，请耐心等待...\n运营版本号：%s\nChangeList:%s') % (g_branch_name, g_use_ver, str(g_label_id))
        rtx.send_msg_qa(rtxmsg)
        #rtx.send_msg_qa(u'[3-4/6]--跳过烘焙数据，正在准备安装目录结构，请耐心等待...')

    cpyCmd = 'copy ' + client_build_UE3_path + 'Binaries\\Win32\\MMOGame-Win32-Shipping.exe ' + dir_cfg.sig_exe.replace('aodpatch', 'aodpatch\\' + g_branch_name) + ' /Y'
    os.system(cpyCmd)
    rtx.send_msg_cj((u'分支【%s】 \n请将以下文件签名后上传:[http://172.30.66.33/aodpatch/%s/Exe/MMOGame.exe|http://172.30.66.33/aodpatch/%s/Exe/MMOGame.exe]') %(g_branch_name, g_branch_name, g_branch_name))

    targCookVerDir = dir_cfg.shipping_output_dir_root + 'CQYH\\'
    srcPatchDir = dir_cfg.shipping_output_dir_root

    targCookVerDir = targCookVerDir.replace('edition', 'edition\\' + g_branch_name)
    srcPatchDir = srcPatchDir.replace('edition', 'edition\\' + g_branch_name)

    cpyCmd = 'rd ' + targCookVerDir + '\\ /Q /S'
    os.system(cpyCmd)

    cpyCmd = 'md ' + targCookVerDir + '\\'
    os.system(cpyCmd)

    cookedSrcDir = client_build_UE3_path
    if g_split_upk:
        cookedSrcDir = tmpCookDir

    tmpCfgDir = dir_cfg.tmpCfgDir
    cpyCmd = dir_cfg.get_bat_file_path('_copy_config.bat ') + g_branch_name + ' ' + tmpCfgDir
    #暂时全复制os.system(cpyCmd)
    cpyCmd = dir_cfg.get_bat_file_path('__copy_shipping_files.bat ')  + ' ' + client_build_UE3_path + ' ' + cookedSrcDir + ' ' + targCookVerDir
    print cpyCmd
    os.system(cpyCmd)

    if not debug_skip:
        rtx.send_msg_qa((u'[5/7]分支【%s】 \n正在生成PATCH，请耐心 等待...\n运营版本号：%s\nChangeList:%s') % (g_branch_name, g_use_ver, str(g_label_id)))

    shippingVerIni = dir_cfg.shipping_ver_ini.replace('edition', 'edition\\' + g_branch_name)
    gen_ver_ini(g_label_id, shippingVerIni)

    shipVerIni = srcPatchDir + 'CQYH\\Binaries\\Ver.ini'
    gen_ver_ini(g_label_id, shipVerIni)


    cpyCmd = 'rd ' + dir_cfg.shipping_bin_patch.replace('aodpatch', 'aodpatch\\' + g_branch_name) + ' /Q /S'
    os.system(cpyCmd)

    cpyCmd = 'ViGenerator.exe ' + srcPatchDir + ' ' + dir_cfg.shipping_bin_patch.replace('aodpatch', 'aodpatch\\' + g_branch_name)
    os.system(cpyCmd)

    #return


    #'''

    d = datetime.datetime.now()
    d = d.strftime('%Y_%m_%d_')


    verDir = str(d) + str(g_label_id)

    print verDir

    genVerBat = '@echo set mmoVer=' + verDir + '> ' + dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\PackageTool\\MMOGameVer.bat'
    os.system(genVerBat)

    timeDur = datetime.datetime.now() - startTime

    strUrl = 'http://172.30.66.33/aodpatch/Install/' + verDir
    if not debug_skip:
        rtx.send_msg((u'[6/7]分支【%s】 \n发行版本编译完成，请等待生成更新包...\n版本号：%s \n运营版本号：%s\n共用时：%s') % (g_branch_name, str(g_label_id), g_use_ver, str(timeDur)))

    stop_compile_client()
    stop_cook_client()

    return True

def release_client():
    v = _release_client(dir_cfg.game_output_dir_root, 'MMOGame\\ScriptDevRelease', 'BinariesDev', 0,  dir_cfg.client_bin_patch,  dir_cfg.dev_ver_ini)
    rtx.send_msg_all((u'分支【%s】 \n游戏发布成功,请运行08.Prog%s/Client/UE3/FilePatch.exe  更新.\nChangeList:%s' % (g_branch_name, g_branch_name, v)))

def release_editor():
    v = _release_client(dir_cfg.editor_output_dir_root, 'MMOGame\\ScriptEditorRelease', 'BinariesEditor', 0, dir_cfg.editor_bin_patch, dir_cfg.editor_ver_ini)
    rtx.send_msg_all((u'分支【%s】 \n编辑器发布成功,请运行08.Prog%s/Client/UE3/FilePatch.exe  更新.\nChangeList:%s' % (g_branch_name,g_branch_name, v)))

def build_review(user, change_list_id):
    pass
    #_build_review(user, change_list_id)
    #pass
    #pool = Pool(processes=1)
    #pool.apply_async(_build_review, [user, change_list_id])


def _build_review(user, change_list_id):

    print '=======start build_review', user, change_list_id

    if not start_compile_client() :
        sys.stderr.write('------------- _build_review is Compiling, abort action!\n')
        return


    rtx.send_msg_qa((u'开始自动编译REVIEW版本，请在完成后再进行QA版本编译!\n ChangeList:%s, 提交人:%s' % (str(change_list_id), user)))

    if not init_p4_data():
        sys.stderr.write('------------- build_review Init p4 failed.\n')
        stop_compile_client()
        return

    v, name = update_client_code(dir_cfg.p4_cl_ver_ini, False, change_list_id, -1)

    if not v:
        sys.stderr.write('------------- build_review update codes fail.\n')
        stop_compile_client()
        return

    print '------------- build_review Update client to:%s' % str(v)

    update_version(v)


    result, buf = compile_dev_client(v, 'Release|Mixed platforms')

    #log_file = open((u'D:\\xampp\\htdocs\\buildlog\\%s.log' % str(v)), 'w')
    log_file = open(dir_cfg.get_compile_log_file(str(v)), 'w')
    log_file.write(buf)
    log_file.close()

    log_url = (u'http://172.30.66.33/buildlog/%s.log' % str(v))

    if not result:
        print '---------- build_review Compile failed!'
        rtx.send_msg_prog((u'分支【%s】 \n编译失败，请立即修正!\n ChangeList:%s, 提交人:%s \n Log:[%s|%s]' % (g_branch_name, (change_list_id), user, log_url, log_url)))
        stop_compile_client()

        p4_cmd = 'p4 revert //AgeOfDawn/08.Prog' + g_branch_name + '/Client/UE3/Development/Src/MMOGame/Inc/...'
        os.system(p4_cmd)
        return

        #log_file = open((u'D:\\xampp\\htdocs\\buildlog\\%s.log' % str(change_list_id)), 'w')
        #log_file.write(buf)
        #log_file.close()

    stop_compile_client()

    p4_cmd = "p4 revert -a"
    os.system(p4_cmd)

    rtx.send_msg_qa((u'编译成功!\n ChangeList:%s, 提交人:%s \n Log:[%s|%s]' % (str(change_list_id), user, log_url, log_url)))

def compile_shadercache():
    #'''
    if not start_compile_client():
        return

    global flag_f_client

    result_str = ''
    del_cook_log()

    startTime = datetime.datetime.now()

    rtx.send_msg_qa((u'分支【%s】 \n开始编译材质缓存') % (g_branch_name))

    if 1 :
        os.system('del /F /Q  ' + dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\MMOGame\\Content\\GlobalShaderCache-PC-D3D-SM3.bin')
        os.system('del /F /Q  ' + dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\MMOGame\\Content\\LocalShaderCache-PC-D3D-SM3.upk')

        p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
            stdin=subprocess.PIPE, stdout=subprocess.PIPE)

        exePath = dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\Binaries\\Win64\\MMOGame.exe'
        exec_cmd = '%s PrecompileShaders platform=pc_sm3 -DEV_RELEASE -BUILDMACHINE -DEMOMODE -depends -forcedistributed -NOPAUSE\n' % (exePath)
        print p, exec_cmd
        p.stdin.write(exec_cmd)
        p.stdin.write('exit\n')

        result_str = ''
        while True:
            buf = p.stdout.read(8)
            if not buf:
                break
            flag_f_client.write(buf)
            flag_f_client.flush()
            result_str += buf

    stop_compile_client()

    timeDur = datetime.datetime.now() - startTime



    #'''
    targetDir = dir_cfg.shader_cache_src.replace('shader_cache', 'shader_cache\\' + g_branch_name + '\\shader_cache')
    patchDir = dir_cfg.shader_cache_path_dir.replace('aodpatch', 'aodpatch\\' + g_branch_name)

    os.system('xcopy  ' + dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\MMOGame\\Content\\GlobalShaderCache-PC-D3D-SM3.bin ' + targetDir +' /Y')
    os.system('xcopy  ' + dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\MMOGame\\Content\\LocalShaderCache-PC-D3D-SM3.upk ' + targetDir +' /Y')

    targetDir = dir_cfg.shader_cache_src_root.replace('shader_cache', 'shader_cache\\' + g_branch_name + '\\shader_cache')
    cpyCmd = 'ViGenerator.exe ' + targetDir + ' ' + patchDir
    os.system(cpyCmd)
    #urllib.urlopen(r'http://172.30.68.104:8089/?action=copy_shader_cache').read()
    rtx.send_msg((u'分支【%s】 \n材质缓存编译完成，用时：%s') % (g_branch_name, str(timeDur)))

    #result_str = 'str'

    return result_str


def fix_mat_usage():
    global flag_f_client

    if not start_compile_client():
        return

    del_cook_log()
    startTime = datetime.datetime.now()

    #g_branch_name = '_CB2_430'

    rtx.send_msg_qa((u'分支【%s】 \n开始修正材质使用标签:%s') % (g_branch_name, str(g_label_id)))

    p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
        stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    exePath = dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\Binaries\\Win64\\MMOGame.exe'
    exec_cmd = '%s SetMaterialUsage -forcedistributed -AutoCheckOutPackages -DEV_RELEASE -BUILDMACHINE -DEMOMODE -NOPAUSE\n' % (exePath)
    print p, exec_cmd
    p.stdin.write(exec_cmd)
    p.stdin.write('exit\n')

    result_str = ''
    while True:
        buf = p.stdout.read(8)
        if not buf:
            break
        flag_f_client.write(buf)
        flag_f_client.flush()
        result_str += buf

    stop_compile_client()

    timeDur = datetime.datetime.now() - startTime

    targetDir = dir_cfg.shader_cache_src.replace('shader_cache', 'shader_cache\\' + g_branch_name + '\\shader_cache')
    patchDir = dir_cfg.shader_cache_path_dir.replace('aodpatch', 'aodpatch\\' + g_branch_name)

    os.system('xcopy  ' + dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\MMOGame\\Content\\GlobalShaderCache-PC-D3D-SM3.bin ' + targetDir +' /Y')
    os.system('xcopy  ' + dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\MMOGame\\Content\\LocalShaderCache-PC-D3D-SM3.upk ' + targetDir +' /Y')

    targetDir = dir_cfg.shader_cache_src_root.replace('shader_cache', 'shader_cache\\' + g_branch_name + '\\shader_cache')
    cpyCmd = 'ViGenerator.exe ' + targetDir + ' ' + patchDir
    os.system(cpyCmd)

    #os.system(u'copy  ' + dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\MMOGame\\Content\\GlobalShaderCache-PC-D3D-SM3.bin ' + dir_cfg.shader_cache_src_root + ' /Y')
    #os.system(u'copy  ' + dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\MMOGame\\Content\\LocalShaderCache-PC-D3D-SM3.upk ' + dir_cfg.shader_cache_src_root + ' /Y')
    #urllib.urlopen(r'http://172.30.68.104:8089/?action=copy_shader_cache').read()

    #targetDir = dir_cfg.shader_cache_src_root.replace('shader_cache', 'shader_cache\\' + g_branch_name)
    #cpyCmd = 'ViGenerator.exe ' + targetDir + ' ' + patchDir
    #os.system(cpyCmd)

    rtx.send_msg((u'分支【%s】 \n材质使用标签修正完成，用时：%s') % (g_branch_name, str(timeDur)))


    #g_change_list = 0
    #g_use_label = True
    #g_label_id = 39552
    #client_code_path = [r'//AgeOfDawn/08.Prog' + g_branch_name + '/...']
    #client_build_UE3_path='..\\source\\08.Prog' + g_branch_name + '\\Client\\UE3\\'

    #compile_shipping(True)

    return result_str


def patch_shipping():
    srcPatchDir = dir_cfg.shipping_output_dir_root.replace('edition', 'edition\\' + g_branch_name)
    cpyCmd = 'ViGenerator.exe ' + srcPatchDir + ' ' + dir_cfg.shipping_bin_patch.replace('aodpatch', 'aodpatch\\' + g_branch_name)
    os.system(cpyCmd)
    rtx.send_msg_qa((u'[7/7]分支【%s】 \n发行版本更新包准备完成，可以更新了！') % (g_branch_name))
    #pass

def patch_qabuild():
    srcPatchDir = dir_cfg.client_qa_path.replace('edition', 'edition\\' + g_branch_name)
    cpyCmd = 'ViGenerator.exe ' + srcPatchDir + ' ' + dir_cfg.qaclient_bin_patch.replace('aodpatch', 'aodpatch\\' + g_branch_name)
    print cpyCmd
    os.system(cpyCmd)

    cpyCmd = 'ViGenerator.exe ' + srcPatchDir + ' ' + dir_cfg.qaeditor_bin_patch.replace('aodpatch', 'aodpatch\\' + g_branch_name)
    print cpyCmd
    os.system(cpyCmd)

    rtx.send_msg_qa((u'分支【%s】 \nQA版本更新包准备完成！') % (g_branch_name))
    #pass


def gen_res_ref_table():
    start_compile_client()
    #    return

    global flag_f_client

    #del_cook_log()
    startTime = datetime.datetime.now()

    #g_branch_name = '_CB2_430'

    p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
        stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    exePath = get_exe_path()
    #'' + dir_cfg.source_root + '08.Prog' + g_branch_name + '\\Client\\UE3\\Binaries\\Win64\\MMOGame.exe'

    rtx.send_msg((u'分支【%s】 \n开始生成资源引用列表:%s') % (g_branch_name, exePath))

    exec_cmd = '%s MakeRefList -Processes=32 -DEV_RELEASE -BUILDMACHINE -DEMOMODE -NOPAUSE\n' % (exePath)
    print p, exec_cmd
    p.stdin.write(exec_cmd)
    p.stdin.write('exit\n')

    result_str = ''
    while True:
        buf = p.stdout.read(8)
        if not buf:
            break

        if flag_f_client != None:
            flag_f_client.write(buf)
            flag_f_client.flush()

        #if flag_f_cook != None:
        #    flag_f_cook.write(buf)
        #    flag_f_cook.flush()

        result_str += buf

    #stop_compile_client()

    timeDur = datetime.datetime.now() - startTime
    print timeDur
    rtx.send_msg((u'分支【%s】 \n生成资源引用列表完成，用时：%s') % (g_branch_name, str(timeDur)))

    return result_str

def pack_mpq(srcDir, destDir):
    cpyCmd = 'PakPatcher.exe ' + srcDir + ' ' + destDir
    os.system(cpyCmd)

def stop_current_build():
    print '*******stop_current_build*********'

    cmd_str = 'taskkill /F /IM ViGenerator.exe'
    os.system(cmd_str)

    cmd_str = 'taskkill /F /IM MMOGame.exe'
    print cmd_str
    os.system(cmd_str)

    cmd_str = 'taskkill /F /IM MMOGame.com'
    print cmd_str
    os.system(cmd_str)

    cmd_str = 'taskkill /F /IM UE3ShaderCompileWorker.exe'
    print cmd_str
    os.system(cmd_str)

    print 'stop_compile_client()'
    stop_compile_client()

    print 'stop_cook_client()'
    stop_cook_client()

    #os.remove(compile_flag_path_client)
    #os.remove(compile_flag_path_cook)
    cmd_str = 'del /Q is_compile_client'
    os.system(cmd_str)
    #print cmd_str

    cmd_str = 'del /Q is_cook_client'
    os.system(cmd_str)
    #print cmd_str
