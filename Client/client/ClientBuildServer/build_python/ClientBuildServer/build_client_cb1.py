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

is_debug = 0

g_curVer = 0
g_change_list=0
g_label_id=0
g_use_label=0

p4_root = ''
p4_name = ''
p4_project_name = ''


#p4_cmd = 'p4 sync %s'
#p4_checkout_ver = 'p4 edit //AgeOfDawn/08.Prog_CB1/Client/UE3/MMOGame/Config/DefaultVer.ini'

client_code_path = [r'//AgeOfDawn/08.Prog_CB1/...']

client_build_UE3_path='..\\source\\08.Prog_CB1\\Client\\UE3\\'

#defaultver_localpath = '..\\source\\DefaultVer.ini'

client_pdb_path='D:\\xampp\\htdocs\\aodpatch\\pdb\\'

#p4_cmd = "p4 sync %s"

vs_evn_cmd = r'%comspec% /k "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/vcvarsall.bat" x64'
vs_evn_cmd_2010_x86 = r'%comspec% /k "d:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/vcvarsall.bat" x86'


compile_flag_path_client = './is_compile_client'
flag_f_client = None

cl_r = re.compile('Change (\d+?) on')
name_r = re.compile('by (.*?)\@')
err_r = re.compile('(\d+?) Error\(s\)')

os.environ['P4PORT'] = '172.30.66.40:1668'
os.environ['P4USER'] = 'AutoBuild'
if is_debug:
    os.environ['P4CLIENT'] = 'autobuild_cw'
else:
    os.environ['P4CLIENT'] = 'AutoBuild_BUILDC'
os.environ['P4PASSWD'] = 'qwe123!@#'

def update_version(ver):
    print('------------- write ver file to %d' % ver)
    os.popen(r'del ../source/08.Prog_CB1/Common/define/version.h /F/Q')
    os.popen(r'echo #ifndef _VERSION_H_ > ../source/08.Prog_CB1/Common/define/version.h')
    os.popen(r'echo #define _VERSION_H_ >> ../source/08.Prog_CB1/Common/define/version.h')
    os.popen(r'echo #define MAJOR_VERSION (0) >> ../source/08.Prog_CB1/Common/define/version.h')
    os.popen(r'echo #define MINOR_VERSION (1) >> ../source/08.Prog_CB1/Common/define/version.h')
    os.popen(r'echo #define BUILD_NUMBER (%d) >> ../source/08.Prog_CB1/Common/define/version.h' % ver)
    os.popen(r'echo #endif //_VERSION_H_ >> ../source/08.Prog_CB1/Common/define/version.h')

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
   
def compile_info_client():
    global flag_f_client
    if os.path.isfile(compile_flag_path_client):
        buf = open(compile_flag_path_client, 'r').read()
        return True, buf
    return False, None



def start_compile_client():
    global flag_f_client
    if os.path.isfile(compile_flag_path_client):
        return True
    flag_f_client = open(compile_flag_path_client, 'w')
    return False


    
def stop_compile_client():
    global flag_f_client
    flag_f_client.close()
    os.remove(compile_flag_path_client)


    
def compile_fail_info_client(v, info):
    file_path = 'static/%s_%s_err_client.txt' % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()), v)
    open(file_path, 'w').write(info)



def compile_fail_info_clientsript(v, info):
    file_path = 'static/%s_%s_err_clientscript.txt' % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()), v)
    open(file_path, 'w').write(info)


    
def compile_devclient(compile_type):
    global flag_f_client
    client_sln_path=r'../source/08.Prog_CB1/Client/UE3/Development/Src/UE3.sln'
    print '------------- Try to compile client exe: ', client_sln_path
    os.path.join(p4_root, vs_evn_cmd_2010_x86)
    p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
        stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    #compile_type = 'Release|Mixed platforms'
    exec_cmd = 'devenv "%s" /build "%s"\n' % (client_sln_path, compile_type)
        
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

    return result_str

def cook_data(exePath, isFull):
    #global flag_f_client
    p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
        stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    if isFull:
        exec_cmd = '%s CookPackages -platform=PC -log -AUTOCOOKMAPS -final_release -multilanguagecook=INT+CHN -BUILDMACHINE -DEMOMODE -NOPAUSE -full\n' % (exePath)
    else:
        exec_cmd = '%s CookPackages -platform=PC -log -AUTOCOOKMAPS -final_release -multilanguagecook=INT+CHN -BUILDMACHINE -DEMOMODE -NOPAUSE\n' % (exePath)
        
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

    return result_str

def compile_client_script(buildArg):
    global flag_f_client
  
    os.path.join(p4_root, vs_evn_cmd_2010_x86)
    p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
        stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    
    exec_cmd = '..\\source\\08.Prog_CB1\\Client\\UE3\\Binaries\\Win32\\MMOGame.com make -auto -DEMOMODE -NOPAUSEONSUCCESS -full ' + buildArg + '\n'
    
    print '------------- Try to compile client script: ', exec_cmd
    
    p.stdin.write(exec_cmd)
    p.stdin.write('exit\n')
    
    result_str = ''
    while True:
        buf = p.stdout.read(8)
        if not buf:
            print '!!!!!!!!!!!!!!!break reading....'
            break
        
        flag_f_client.write(buf)
        flag_f_client.flush()
        result_str += buf
        #print buf

    print '------------ compile_client_script:', result_str
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
    print '--------------result:', result_str
    if result_str.find('Success') < 0:
        compile_fail_info_clientsript(v, result_str)
        return False, result_str

    return True, result_str

def gen_ver_ini(ver, iniPath):
    #os.system(p4_checkout_ver)
    
    #os.remove(defaultver_localpath)
    #os.mkdir(iniPath)
    ver_f = open(iniPath, 'w+')
    #ver_info = '[ver]\r\nChangeList=%s' % ver
    ver_info = '%s' % ver
    print '------------- gen_ver_ini' + ver_info
    ver_f.write(ver_info)
    ver_f.flush()
    ver_f.close()
    

def update_client_code(iniPath, useLabel, clNum, labNum):
    global g_curVer
    print '------------- update_client_code...', iniPath, useLabel, clNum, labNum
    max_v = 0
    name = ''

    p4_cmd = "p4 sync "
    
    for d in client_code_path:
        if useLabel:
            exec_cmd = p4_cmd + "-n " + d + " @LC" + str(labNum)
            max_v = labNum
        else:
            exec_cmd = p4_cmd + d + ' ' + str(clNum)
            max_v = clNum

        
        os.system(exec_cmd)
        print '------------- update_client_code...', exec_cmd
        print '------------- update_client_code...', iniPath, useLabel, clNum, labNum
        
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

client_qa_path='C:\\AutoBuild\\edition\\client_qa_build\\'

def copy_for_qa(ver, binDir, scriptDir, targetDir, patchDir):
    #copy_client_ver_files = 'copy ' + defaultver_localpath + ' ' + targetDir + 'DefaultVer.ini /Y '
    copy_client_bin_files = 'xcopy ' + client_build_UE3_path + 'Binaries\\*.* ' + targetDir + '\\' + binDir + '\\ /F /Y /R /Q'
    copy_client_bin_files32 = 'xcopy ' + client_build_UE3_path + 'Binaries\\Win32\\*.* ' + targetDir + '\\' + binDir + '\\Win32\\ /S /F /R /Y /Q'
    copy_client_bin_files64 = 'xcopy ' + client_build_UE3_path + 'Binaries\\Win64\\*.* ' + targetDir + '\\' + binDir + '\\Win64\\ /S /F /R /Y /Q' 
    copy_client_script_files = 'xcopy ' + client_build_UE3_path + scriptDir + '\\*.* ' + targetDir + '\\' + scriptDir + '\\ /S /F /Y /R /Q'
    #copy_client_editor_files = 'copy ' + client_build_UE3_path + 'Binaries\\UnrealEdCSharp.dll ' + targetDir + '\\UnrealEdCSharp.dll' + ' /Y'

    os.system(copy_client_bin_files)
    os.system(copy_client_bin_files32)
    ##os.system(copy_client_bin_files64)
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
    #os.system('pause')

def _compile_client2(scriptVer, cppVer, scriptDir, binDir, patchDir):
    print '------------- Compile Client...', scriptVer, cppVer, scriptDir, binDir, patchDir
    copy_for_qa(19888, binDir, scriptDir, client_qa_path, patchDir)

    
    
def _compile_client(scriptVer, cppVer, scriptDir, binDir, patchDir, iniPath, copyForQA=True):
    print '------------- Compile Client...', scriptVer, cppVer, scriptDir, binDir

    print '------------- Init P4'
    if not init_p4_data():
        sys.stderr.write('------------- Client Init p4 failed.\n')
        return
        
    v, name = update_client_code(iniPath, g_use_label, g_change_list, g_label_id)

    if not v:
        sys.stderr.write('------------- Client update codes fail.\n')
        return
    print '------------- Update client to:%d' % v
	
    update_version(v)

    if start_compile_client() :
        sys.stderr.write('------------- Client is Compiling, abort action!\n')
        return
    #    sys.exit(-1)
    
    #result, buf = compile_dev_client_script(v, scriptVer)
    result, buf = compile_dev_client(v, cppVer)
    result, buf = compile_dev_client_script(v, scriptVer)
    
    p4_cmd = "p4 revert //AgeOfDawn/08.Prog_CB1/Client/UE3/Development/Src/MMOGame/Inc/..."
    os.system(p4_cmd)
     
    #result, buf
    #result = 1
    if result:
        print '---------- Client Compile ok, starting copy...'
	#复制到中间目录供QA更新
        if copyForQA:
            copy_for_qa(v, binDir, scriptDir, client_qa_path, patchDir)

        if not is_debug and not g_use_label: 
            label_cmd = 'p4 tag -a -l LC' + str(v) + ' //AgeOfDawn/08.Prog_CB1/...@' + str(v)        
            os.system(label_cmd)        
            print label_cmd
            
        stop_compile_client()
        #vv = 'bin_%d_%s' % (v, time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()))
        #ver_path = '%s/%s' % (output_root, vv)
        if copyForQA and binDir == 'BinariesEditor':
            rtx.send_msg_qa((u'-----Editor编译成功%s %s,请运行08.Prog_CB1/__UpdateQAEditor.bat 更新.\nChangeList:%s' % (scriptVer, cppVer, str(v))))
        elif copyForQA:
            rtx.send_msg_qa((u'----客户端编译成功%s %s,请运行08.Prog_CB1/__UpdateQAClient.bat 更新.\nChangeList:%s' % (scriptVer, cppVer, str(v))))
        
        #sys.exit(0)
    else:
        print '---------- Client Compile failed!'
        stop_compile_client()

        log_file = open((u'D:\\xampp\\htdocs\\buildlog\\%s.log' % str(v)), 'w')
        log_file.write(buf)
        log_file.close()

        log_url = (u'http://172.30.66.33:888/buildlog/%s.log' % str(v))
    
        rtx.send_msg_qa((u'-----客户端版本编译失败! %s %s\n ChangeList:%s, 最晚提交:%s \n Log:[%s|%s]' % (scriptVer, cppVer, str(v), name, log_url, log_url)))
        #sys.exit(-1)

	
	
    
def _release_client(targetDir, scriptDirName, binDirName, copyToBackupServer, patchDir, iniPath):
    
	#copy_client_ver_files = 'copy ' + defaultver_lcompile_client_scriptocalpath + ' ' + targetDir + 'DefaultVer.ini /Y '
   # copy_client_bin_files = 'xcopy ' + client_build_UE3_path + 'Binaries/*.* ' + targetDir + '/' + binDir + '/ /S /F /Y /R'
    #copy_client_script_files = 'xcopy ' + client_build_UE3_path + 'MMOGame/' + scriptDir + '/*.* ' + targetDir + '/' + scriptDir + ' /S /F /Y /R'
    #copy_client_editor_files = 'copy ' + client_build_UE3_path + 'Binaries/UnrealEdCSharp.dll ' + targetDir + '/UnrealEdCSharp.dll' + ' /Y'
   
   
    #copy_client_bin_files = 'xcopy ' + client_qa_path + '*.* ' + client_bin_release_path + ' /S /F /Y /R'
    #copy_client_script_files = 'xcopy ' + client_scriptout_path + '*.* ' + client_script_release_path + ' /S /F /Y /R'
    #copy_client_ver_files = 'copy ' + client_veriniout_path + ' ' + defaultver_localpath + ' /Y '

    #copy_client_editor_files = 'copy ' + client_binout_editor_dll_path + ' ' + client_release_editor_dll_path + ' /Y '
	
    copy_to_pubb = 'xcopy ' + client_qa_path + binDirName + '\\*.* ' + targetDir +  binDirName + '\\ /S /F /Y /R /Q'
    copy_to_pub1 = 'xcopy ' + client_qa_path + binDirName + '\\MMOGame.* ' + targetDir +  binDirName + '\\ /S /F /Y /R /Q'
    copy_to_pub2 = 'xcopy ' + client_qa_path + scriptDirName + '\\*.* ' + targetDir +  scriptDirName + '\\ /S /F /Y /R /Q'
    copy_to_pub3 = 'copy ' + iniPath + " " + targetDir + binDirName + '\\ /Y'
    copy_to_pub4 = 'copy ' + client_qa_path + '*.dll ' + targetDir +' /Y'

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

    pdbPath = client_pdb_path + v

    cpyCmd = 'D:\\WinRAR\\rar.exe a -r ' + pdbPath + '\\' + str(v) + '.rar C:\\AutoBuild\\Source\\08.Prog_CB1\\Client\\UE3\\Development\\Intermediate\\*.cpp'
    os.system(cpyCmd)
    
    cpyCmd = 'xcopy ' + client_qa_path + binDirName + '\\Win32\\MMOGame.exe ' + pdbPath + '\\ /Y /Q'    
    os.system(cpyCmd)
    print '----------' + cpyCmd

    cpyCmd = 'xcopy ' + client_qa_path + binDirName + '\\Win32\\MMOGame.pdb ' + pdbPath + '\\ /Y /Q'
    os.system(cpyCmd)
    
    print '----------' + cpyCmd

    cpyCmd = 'symstore add /r /f ' + client_qa_path + binDirName + '\\Win32\\MMOGame.pdb /s \"D:\\xampp\\htdocs\\symbols\\" /t \"CQYH\" /v \"1.0.0.' + str(v) + ' /c \"CQYHPDB\"'  
    os.system(cpyCmd)
    print '----------' + cpyCmd

    cpyCmd = 'xcopy ' + client_qa_path + '\\' + scriptDirName + '\\*.* ' + pdbPath + '\\' + scriptDirName + '\\ /S /F /Y /R /Q'
    os.system(cpyCmd)
    print '----------' + cpyCmd

    cpyCmd = 'ViGenerator.exe ' + targetDir + ' ' + patchDir
    #cpyCmd = 'copy ' + client_qa_path + 'UnrealEdCSharp.dll ' + pdbPath + '\\UnrealEdCSharp.dll' + ' /Y'
    os.system(cpyCmd)
    print '----------' + cpyCmd
    
    return v
   

def compile_client():
    rtx.send_msg_qa(u'-------开始编译游戏!')
    _compile_client('-DEV_RELEASE', 'Release|Mixed platforms', 'MMOGame\\ScriptDevRelease', 'BinariesDev', 'D:\\xampp\\htdocs\\aodpatch\\qaclient_bin_patch\\', 'C:\\AutoBuild\\edition\\client_qa_build\\BinariesDev\\ver.ini')

def compile_editor():
    rtx.send_msg_qa(u'-------开始编译Editor!')
    _compile_client('-EDITOR_RELEASE', 'Release|Mixed platforms', 'MMOGame\\ScriptEditorRelease', 'BinariesEditor', 'D:\\xampp\\htdocs\\aodpatch\\qaeditor_bin_patch\\', 'C:\\AutoBuild\\edition\\client_qa_build\\BinariesEditor\\ver.ini')

def compile_shipping(isFull):
    #global g_curVer

    #cpyCmd = u'C:\\AutoBuild\\aod_pack\\SD_NSIS\\makensis.exe C:\\AutoBuild\\aod_pack\\CQYH_Setup.nsi'
    #os.system(cpyCmd)
    #return


    startTime = datetime.datetime.now()
    
    rtx.send_msg_qa(u'[1/7]--编译Release|Mixed platforms开始，请不要再次点击编译发行版本...')

    if start_compile_client():
        return

   
    #'''

    _compile_client('-DEV_RELEASE', 'Release|Mixed platforms', 'MMOGame\\ScriptDevRelease', 'BinariesShipping', 'D:\\xampp\\htdocs\\aodpatch\\shipping_bin_patch\\', 'C:\\AutoBuild\\edition\\client_qa_build\\BinariesShipping\\ver.ini', False)
   
    compile_client_script('-FINAL_RELEASE')
    
   
    rtx.send_msg_qa(u'[2/7]--编译Shipping|Mixed platforms开始，请不要再次点击编译发行版本...')
    compile_devclient('Shipping|Mixed platforms')

   

    rtx.send_msg_qa(u'[3/7]--编译完成，开始烘焙数据，请耐心等待...')
    cook_data('C:\\AutoBuild\\Source\\08.Prog_CB1\\Client\\UE3\\Binaries\\Win32\\MMOGame.exe', isFull)

    
    
    rtx.send_msg_qa(u'[4/7]--烘焙数据完成，正在准备安装目录结构，请耐心 等待...')

    targCookVerDir = 'C:\\AutoBuild\\edition\\Shipping_Bin\\CQYH\\'
    srcPatchDir = 'C:\\AutoBuild\\edition\\Shipping_Bin\\'

    cpyCmd = 'rd ' + targCookVerDir + '\\ /Q /S'
    os.system(cpyCmd)
     
    cookDirList = [
	#'xcopy ' + client_build_UE3_path + 'MMOGame\\ScriptFinalRelease\\*.* ' + targCookVerDir + 'MMOGame\\ScriptFinalRelease\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'MMOGame\\CookedPC\\*.* ' + targCookVerDir + 'MMOGame\\CookedPC\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'MMOGame\\Config\\*.* ' + targCookVerDir + 'MMOGame\\Config\\' + ' /S /F /Y /R /Q /EXCLUDE:ex.txt',
        'xcopy ' + client_build_UE3_path + 'MMOGame\\Localization\\*.* ' + targCookVerDir + 'MMOGame\\Localization\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'MMOGame\\Movies\\*.* ' + targCookVerDir + 'MMOGame\\Movies\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'MMOGame\\Splash\\*.* ' + targCookVerDir + 'MMOGame\\Splash\\' + ' /S /F /Y /R /Q',
        #'xcopy ' + client_build_UE3_path + 'MMOGame\\Flash\\Fonts\\*.* ' + targCookVerDir + 'MMOGame\\Flash\\Fonts\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'MMOGame\\Content\\\CursorAni\\*.* ' + targCookVerDir + 'MMOGame\\Content\\\CursorAni\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'MMOGame\\Content\\\MapsGlobalInfo\\*.npc ' + targCookVerDir + 'MMOGame\\CookedPC\\\MapsGlobalInfo\\' + ' /S /F /Y /R /Q',
        #'xcopy ' + client_build_UE3_path + 'MMOGame\\Content\\*ShaderCache*.* ' + targCookVerDir + 'MMOGame\\Content\\' + ' /S /F /Y /R /Q',
        #'xcopy ' + client_build_UE3_path + 'Engine\\*.* ' + targCookVerDir + 'Engine\\' + ' /S /F /Y /R /Q /EXCLUDE:ex.txt',
        'xcopy ' + client_build_UE3_path + 'Engine\\Config\\*.ini ' + targCookVerDir + 'Engine\\Config\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'Engine\\Config\\*.txt ' + targCookVerDir + 'Engine\\Config\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'Engine\\Content\\*.* ' + targCookVerDir + 'Engine\\Content\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'Engine\\Localization\\*.* ' + targCookVerDir + 'Engine\\Localization\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'Engine\\Shaders\\Binaries\\*.* ' + targCookVerDir + 'Engine\\Shaders\\Binaries\\' + ' /S /F /Y /R /Q',
        
        'xcopy ' + client_build_UE3_path + 'SDO\\*.* ' + targCookVerDir + 'SDO\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'Launcher\\*.* ' + targCookVerDir + '\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'LauncherRelease\\*.* ' + targCookVerDir + '\\' + ' /S /F /Y /R /Q',
        'xcopy ' + client_build_UE3_path + 'Binaries\\Win32\\GPK\*.* ' + targCookVerDir + 'Binaries\\Win32\\GPK\\' + ' /S /F /Y /R /Q',
        #'xcopy ' + client_build_UE3_path + 'Binaries\\Win32\\*.dll ' + targCookVerDir + 'Binaries\\Win32\\' + ' /S /F /Y /R /Q',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\MMOGame-Win32-Shipping.exe ' + targCookVerDir + 'Binaries\\Win32\\MMOGame.exe /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\Apex*.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\cudart32_41_22.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\EasyHook32.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\GPKitClt.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\libogg.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\libresample.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\libvorbis.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\libvorbisfile.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\nvtt.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\ogg.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\PhysX3GpuCHECKED_x86.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\PhysXCooking.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\PhysXCore.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\PhysXDevice.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\PhysXExtensions.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\PhysXLoader.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\wxmsw28u_adv_vc_custom.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\wxmsw28u_aui_vc_custom.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\wxmsw28u_core_vc_custom.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\wxmsw28u_html_vc_custom.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\wxmsw28u_richtext_vc_custom.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\wxmsw28u_vc_custom.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\wxmsw28u_xml_vc_custom.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\wxmsw28u_xrc_vc_custom.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        #'copy ' + client_build_UE3_path + 'Binaries\\Win32\\xinput1_3.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        #'copy ' + client_build_UE3_path + 'Binaries\\Win32\\D3DCompiler_43.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        #'copy ' + client_build_UE3_path + 'Binaries\\Win32\\D3DX9_43.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        #'copy ' + client_build_UE3_path + 'Binaries\\Win32\\d3dx11_43.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        #'copy ' + client_build_UE3_path + 'Binaries\\Win32\\X3DAudio1_7.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        #'copy ' + client_build_UE3_path + 'Binaries\\Win32\\XAPOFX1_5.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\msvcp100.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy ' + client_build_UE3_path + 'Binaries\\Win32\\msvcr100.dll ' + targCookVerDir + 'Binaries\\Win32\\ /Y',
        'copy C:\\AutoBuild\\aod_pack\\MMOGameCfg\\IP.ini ' + targCookVerDir + 'MMOGame\\Config\\IP.ini /Y',
	]

    for copy_cooked in cookDirList:
        print copy_cooked
        os.system(copy_cooked)

    #for copy_cooked in cookDirList:
    #    print copy_cooked

    rtx.send_msg_qa(u'[5/7]--正在生成PATCH，请耐心 等待...')

    cpyCmd = 'rd D:\\xampp\\htdocs\\aodpatch\\shipping_bin_patch\\ /Q /S'
    os.system(cpyCmd)
    
    cpyCmd = 'ViGenerator.exe ' + srcPatchDir + ' ' + 'D:\\xampp\\htdocs\\aodpatch\\shipping_bin_patch\\'
    os.system(cpyCmd)

    cpyCmd = 'copy C:\\AutoBuild\\aod_pack\\MMOGameCfg\\IPOuter.ini ' + targCookVerDir + 'MMOGame\\Config\\IP.ini /Y'
    os.system(cpyCmd)
    
    #'''
    
    #rtx.send_msg_qa(u'[6/7]--PATCH生成完成，正在打包，请耐心 等待...')

    
    d = datetime.datetime.now()
    d = d.strftime('%Y_%m_%d_')

    
    verDir = str(d) + str(g_label_id)

    print verDir
    
    genVerBat = '@echo set mmoVer=' + verDir + '> C:\\AutoBuild\\Source\\08.Prog_CB1\\Client\\PackageTool\\MMOGameVer.bat'
    os.system(genVerBat)

    #cpyCmd = 'C:\\AutoBuild\\Source\\08.Prog_CB1\\Client\\PackageTool\\PackMMOGameShipping.bat'
    #os.system(cpyCmd)
    cpyCmd = u'C:\\AutoBuild\\aod_pack\\autopack.bat ' + str(g_label_id) + ' c:\\' + verDir + '\\'
    #os.system(cpyCmd)

    #d = datetime.datetime.now()
    #d = d.strftime('%Y_%m_%d_')
    #verDir = str(d) + str(g_label_id)
    
    cpyCmd = 'xcopy c:\\' + verDir + '\\*.* D:\\xampp\\htdocs\\aodpatch\\Install\\' + verDir + '\\ /S /F /Y /R /Q'
    #os.system(cpyCmd)
    
    cpyCmd = 'rd c:\\' + verDir + '\\ /Q /S'
    #os.system(cpyCmd)
    
    timeDur = datetime.datetime.now() - startTime
    
    strUrl = 'http://172.30.66.33:888/aodpatch/Install/' + verDir
    rtx.send_msg(u'[7/7]--发行版本制作完成，请通过PATCH更新\"最终发行版本\"，版本号：' + str(g_label_id) + u'\r共用时：' + str(timeDur))

    stop_compile_client()

def release_client():    
    v = _release_client('C:\\AutoBuild\\edition\\client_bin\\', 'MMOGame\\ScriptDevRelease', 'BinariesDev', 0, 'D:\\xampp\\htdocs\\aodpatch\\client_bin_patch\\', 'C:\\AutoBuild\\edition\\client_qa_build\\BinariesDev\\ver.ini')
    rtx.send_msg((u'-------客户端开发版本发布成功,请运行08.Prog_CB1/Client/UE3/FilePatch.exe  更新.\nChangeList:%s' % v))
	
def release_editor():
    v = _release_client('C:\\AutoBuild\\edition\\editor_bin\\', 'MMOGame\\ScriptEditorRelease', 'BinariesEditor', 0, 'D:\\xampp\\htdocs\\aodpatch\\editor_bin_patch\\', 'C:\\AutoBuild\\edition\\client_qa_build\\BinariesEditor\\ver.ini')
    #rtx.send_msg((u'-------客户端开发版本发布成功,请运行08.Prog_CB1/Client/UE3/FilePatch.exe  更新.\nChangeList:%s' % v))
    #rtx.send_msg((u'-------edititor 08.Prog_CB1/Client/UE3/FilePatch.exe  \nChangeList:%s' % v))
    rtx.send_msg((u'-------编辑器版本发布成功,请运行08.Prog_CB1/Client/UE3/FilePatch.exe  更新.\nChangeList:%s' % v))
	
def release_shipping():
    startTime = datetime.datetime.now()
        
    if start_compile_client():
        return
    
    rtx.send_msg_qa(u'正在打包，请耐心等待,版本号：' + str(g_label_id))

    
    d = datetime.datetime.now()
    d = d.strftime('%Y_%m_%d_')

    
    verDir = str(d) + str(g_label_id)

    print verDir
    
    genVerBat = '@echo set mmoVer=' + verDir + '> C:\\AutoBuild\\Source\\08.Prog_CB1\\Client\\PackageTool\\MMOGameVer.bat'
    os.system(genVerBat)

    cpyCmd = u'C:\\AutoBuild\\aod_pack\\autopack.bat ' + str(g_label_id) + ' c:\\' + verDir + '\\'
    os.system(cpyCmd)

    cpyCmd = 'xcopy c:\\' + verDir + '\\*.* D:\\xampp\\htdocs\\aodpatch\\Install\\' + verDir + '\\ /S /F /Y /R /Q'
    os.system(cpyCmd)
    
    cpyCmd = 'rd c:\\' + verDir + '\\ /Q /S'
    #os.system(cpyCmd)
    
    timeDur = datetime.datetime.now() - startTime
    
    strUrl = 'http://172.30.66.33:888/aodpatch/Install/' + verDir
    rtx.send_msg(u'打包制作完成，版本号：' + str(g_label_id) + u'\r[' + strUrl + u'|' + strUrl + u']\r共用时：' + str(timeDur))

    stop_compile_client()
    
#    v = _release_client('C:\\AutoBuild\\edition\\shipping_bin\\', 'MMOGame\\ScriptFinalRelease', 'BinariesShipping', 0, 'D:\\xampp\\htdocs\\aodpatch\\shipping_bin_patch\\', 'C:\\AutoBuild\\edition\\client_qa_build\\BinariesShipping\\ver.ini')
#    rtx.send_msg((u'-------客户端最终发行版本发布成功,请运行08.Prog_CB1/Client/UE3/FilePatch.exe   更新.\nChangeList:%s' % v))

def build_review(user, change_list_id):
    pass
    #_build_review(user, change_list_id)
    #pass
    #pool = Pool(processes=1)
    #pool.apply_async(_build_review, [user, change_list_id])

    
def _build_review(user, change_list_id):

    print '=======start build_review', user, change_list_id
    
    if start_compile_client() :
        sys.stderr.write('------------- Client is Compiling, abort action!\n')
        return
    
    
    rtx.send_msg_qa((u'-----开始自动编译REVIEW版本，请在完成后再进行QA版本编译!\n ChangeList:%s, 提交人:%s' % (str(change_list_id), user)))
                      
    if not init_p4_data():
        sys.stderr.write('------------- build_review Init p4 failed.\n')
        stop_compile_client()
        return
        
    v, name = update_client_code('C:\\AutoBuild\\edition\\ver.ini', False, change_list_id, -1);

    if not v:
        sys.stderr.write('------------- build_review update codes fail.\n')
        stop_compile_client()
        return
                    
    print '------------- build_review Update client to:%s' % str(v)
	
    update_version(v)   
    
    
    result, buf = compile_dev_client(v, 'Release|Mixed platforms')

    log_file = open((u'D:\\xampp\\htdocs\\buildlog\\%s.log' % str(change_list_id)), 'w')
    log_file.write(buf)
    log_file.close()

    log_url = (u'http://172.30.66.33:888/buildlog/%s.log' % str(change_list_id))
    
    if not result:    
        print '---------- build_review Compile failed!'        
        rtx.send_msg_prog((u'-----编译失败，请立即修正!\n ChangeList:%s, 提交人:%s \n Log:[%s|%s]' % (str(change_list_id), user, log_url, log_url)))
        stop_compile_client()
    
        p4_cmd = "p4 revert //AgeOfDawn/08.Prog_CB1/Client/UE3/Development/Src/MMOGame/Inc/..."
        os.system(p4_cmd)
        return
    
        #log_file = open((u'D:\\xampp\\htdocs\\buildlog\\%s.log' % str(change_list_id)), 'w')
        #log_file.write(buf)
        #log_file.close()
        
    stop_compile_client()
    
    p4_cmd = "p4 revert -a"
    os.system(p4_cmd)
    
    rtx.send_msg_qa((u'-----编译成功!\n ChangeList:%s, 提交人:%s \n Log:[%s|%s]' % (str(change_list_id), user, log_url, log_url)))

def compile_shadercache():
    if start_compile_client():
        return;

    startTime = datetime.datetime.now()
    
    rtx.send_msg_qa(u'-----开始编译材质缓存')

    p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
        stdin=subprocess.PIPE, stdout=subprocess.PIPE)
                    
    exePath = "C:\\AutoBuild\\Source\\08.Prog_CB1\\Client\\UE3\\Binaries\\Win32\\MMOGame.exe"
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
                    
    rtx.send_msg_qa(u'-----材质缓存编译完成，用时：' + str(timeDur))
                    
    return result_str
    

def fix_mat_usage():
    if start_compile_client():
        return;

    startTime = datetime.datetime.now()
    
    rtx.send_msg_qa(u'-----开始修正材质使用标签')

    p = subprocess.Popen(args=vs_evn_cmd_2010_x86, shell=True,
        stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    exePath = "C:\\AutoBuild\\Source\\08.Prog_CB1\\Client\\UE3\\Binaries\\Win32\\MMOGame.exe"
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
                    
    rtx.send_msg_qa(u'-----材质使用标签修正完成，用时：' + str(timeDur))
    
    return result_str
