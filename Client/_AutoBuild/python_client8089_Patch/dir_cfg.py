#coding=utf8

import os

#bat_dir = 'D:\\_AutoBuild\\python_client8089\\'

# tools root
bat_dir = u'D:\\_AutoBuild\\bat_files\\'
pack_tool_root = u'D:\\_AutoBuild\\aod_pack\\'
source_root = u'D:\\_AutoBuild\\Source\\'
rar_exe = u'C:\\Program Files (x86)\\WinRAR\\rar.exe'
build_output_root = u'..\\edition'

# ver ini
shipping_ver_ini = u'D:\\_AutoBuild\\edition\\client_qa_build\\BinariesShipping\\ver.ini'
dev_ver_ini = u'D:\\_AutoBuild\\edition\\client_qa_build\\BinariesDev\\ver.ini'
editor_ver_ini = u'D:\\_AutoBuild\\edition\\client_qa_build\\BinariesEditor\\ver.ini'
p4_cl_ver_ini = 'D:\\_AutoBuild\\edition\\ver.ini'

# output dir
shipping_output_dir_bin_win32 = u'D:\\_AutoBuild\\edition\\Shipping_Bin\\CQYH\\Binaries\\Win32\\'
shipping_output_dir_root = u'D:\\_AutoBuild\\edition\\Shipping_Bin\\'
client_qa_path = u'D:\\_AutoBuild\\edition\\client_qa_build\\'
game_output_dir_root = u'D:\\_AutoBuild\\edition\\client_bin\\'
editor_output_dir_root = 'D:\\_AutoBuild\\edition\\editor_bin\\'

# http update server
qaclient_bin_patch = u'D:\\xampp\\htdocs\\aodpatch\\qaclient_bin_patch\\'
qaeditor_bin_patch = u'D:\\xampp\\htdocs\\aodpatch\\qaeditor_bin_patch\\'
shipping_bin_patch = u'D:\\xampp\\htdocs\\aodpatch\\shipping_bin_patch\\'
client_bin_patch = u'D:\\xampp\\htdocs\\aodpatch\\client_bin_patch\\'
editor_bin_patch = u'D:\\xampp\\htdocs\\aodpatch\\editor_bin_patch\\'

#pdb
client_pdb_path = u'D:\\xampp\\htdocs\\aodpatch\\pdb\\'

# 外放补丁
patch_root = u'D:\\xampp\\htdocs\\aodpatch\\patch\\'
fix_url_root = u'D:\\xampp\\htdocs\\Mir3DPatch\\'


# snapshot
snap_ver_root = u'd:\\_ver\\'

# logs
#build_log_dir = u'D:\\xampp\\htdocs\\buildlog\\'
compile_log_dir = u'D:\\xampp\\htdocs\\buildlog\\'
python_log_dir = u'D:\\_AutoBuild\\python_client8089\\static\\'

# split cook dir
tmpCookDir = u'd:\\_cook_auto\\Client\\UE3\\'

# pack temp dir
tmpCfgDir = u'C:\\_tmpSplitCook\\'

# sig exe
sig_exe = u'D:\\xampp\\htdocs\\aodpatch\\Exe\\MMOGame.exe'

# shader cache
shader_cache_src_root = u'D:\\shader_cache\\'
shader_cache_src = u'D:\\shader_cache\\MMOGame\\Content\\'
shader_cache_path_dir = u'D:\\xampp\\htdocs\\aodpatch\\shader_cache\\'



###########################################################################################

def exec_bat(batFileName, parms):
    global bat_dir
    cmd_str = bat_dir + batFileName + ' ' + parms
    os.system(cmd_str)
    print '******** exec bat:', cmd_str

def get_bat_file_path(batFileName):
    global bat_dir
    return bat_dir + batFileName

def get_game_log_dir(branchName):
    global source_root
    return source_root + '08.Prog' + branchName + '\\Client\\UE3\\MMOGame\\Logs\\'

def get_compile_log_file(fileName):
    global compile_log_dir
    return ((compile_log_dir + '%s.log') % fileName)
