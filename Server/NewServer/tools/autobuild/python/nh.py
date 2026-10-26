#coding: gbk
#!/usr/bin/env python

import os, sys, time
import re
import subprocess
import getopt
import shutil
import rtx
import string

p4_root = ''

log_flag_path = 'log_%s.txt' % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()))
output_root = 'D:\\AutoBuild'
edition_root = 'edition'
commonconfig_root = 'commonconfig'
globalconfig_root = 'globalconfig'
log_root = 'log'
data_root = 'data'

sln_src_path = 'D:\\AutoBuild\\SourceCode\\08.Prog'
sln_common_path = 'Common'
sln_newser_path = 'NewServer'
sln_slotution_path = 'src\universe.sln'
sln_asimov_path = 'src\asimov\asimov.sln'

maintaintoolpath = ''

redmine_log_html = 'http://172.30.66.35/build/log/'
bin_path = 'bin'
pdb_path = 'pdb'
pak_path = 'pak'

dir_copy_list = [	
					'commonconfig',
					'globalconfig',	
					'dyncodebin64',	
					'gmconfig',
]

pdb_copy_list = [
					'gameserver',
					'gateserver',
					'datalogserver',
					'manageserver',
					'balanceserver',
					'loginserver',
					'dbserver',
					'gmserver',
					'guardserver'
]

file_copy_list_debug = [
					'libeay64_d.dll',
					'libmysql64_d.dll',
					'lua64_d.dll',
					'ssleay64_d.dll',
					'SdoBase.dll',	
					'sotsapi.dll',
					'RpcClt.dll',
					'gpkitsvr64.dll',										
					'ToolsGetConfig.ini',
					'start_server_d.bat',
					'stop_server_d.bat',
					'start_server_single.bat',
					'balanceserver64_d.exe',
					'datalogserver64_d.exe',
					'dbserver64_d.exe',
					'gameserver64_d.exe',
					'gateserver64_d.exe',					
					'manageserver64_d.exe',
					'loginserver64_d.exe',
					'gmserver64_d.exe',					
					'ToolsGetConf.exe',
					'libeay64.dll',
					'libmysql64.dll',
					'lua64.dll',
					'ssleay64.dll',
					'start_server.bat',
					'balanceserver64.exe',	
					'datalogserver64.exe',
					'dbserver64.exe',
					'gameserver64.exe',
					'gateserver64.exe',					
					'manageserver64.exe',
					'loginserver64.exe',
					'gmserver64.exe',
					'gmserver64_d.exe',
					'guardserver64.exe',
					'guardserver64_d.exe',
					'msvcr120.dll',
					'msvcr120d.dll',
					'msvcp120.dll',
					'msvcp120d.dll',
					'fcmsdk_X64.dll',
]

guard_copy_list = [
					'guardserver64.exe',
					'guardserver64_d.exe',
]

common_copy_list = [
					'global_config.lua',
]

compile_script_list = [
					'globalconfig',
					'commonconfig\script',
]

p4_cmd = "p4 sync %s"
vs_evn_cmd = '%comspec% /k "C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat" x64\n'
rebuild_flag = False
compile_flag_path = 'is_compile'

flag_f = None
flag_log = None
flag_html = None

cl_r = re.compile('Change (\d+?) on')
name_r = re.compile('by (.*?)\@')
err_r = re.compile('(\d+?) Error\(s\)')

def get_cur_version(d):
    max_v = 0
    r = cl_r.findall(run_cmd('p4 changelists -m 1 %s' % (d)))
    if r and r[0]:
        v = int(r[0])
        print '%s version: %d' % (d, v)
        max_v = max(max_v, v)
        return max_v
    else:
        return 0

def run_cmd(cmd):
    p = subprocess.Popen(args=cmd, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    return p.stdout.read()
   
def init_p4_data():
	global p4_root
	buf = run_cmd("p4 info")
	l = buf.split('\n')
	for i in l:
		if i.find('Client root') >= 0:
			idx = i.find(':')
			p4_root = i[idx + 1:].strip().rstrip()
	return p4_root

def find_version(ver):
	#bbuf = run_cmd('p4.exe changelists -m1')
	
	#bb = bbuf.split('\n')
	#result = 'bin'
	
	#for i in bb:
	#	if i.find(ver) >= 0:
	#		print i	
	#		ppath = path.split('by')
	#		ppath = ppath[0].split('on')
	#		result = result + ppath[1] + '_' + ver
	#
	#print result
	#return result		
	return "Bin"
	
def update_server_codes(ver=None):
	max_v = 0
	name = ''
	#for d in server_codes:
	#   if not ver:
	#exec_cmd = p4_cmd % (d)
	#	else:
	#		exec_cmd = p4_cmd % (d) + ver
	#os.system(exec_cmd)
	
	bbuf = run_cmd('p4.exe changelists -m 1 %s' % (d))
	r = cl_r.findall(bbuf)
	nr = name_r.findall(bbuf)
	print 'p4 changelists -m 1 %s' % (d)
	if r and r[0]:
		v = int(r[0])
		print '%s version: %d' % (d, v)
		max_v = max(max_v, v)
		if max_v == v:
			if nr and nr[0]:
				name = nr[0]
	else:
		#sys.abort()
		pass
			
	return max_v, name
    
def compile_info():
	global flag_f

	if os.path.isfile(compile_flag_path):
		return True
		
	return False

def start_compile():
	global flag_f
	if os.path.isfile(compile_flag_path):
		return True
	flag_f = open(compile_flag_path, 'w')

	#globalfoncig_temp_path = os.path.join(os.path.join(src_root, bin_path), globalconfig_temp_root)
	#if os.path.isdir(globalfoncig_temp_path):
	#	
	#	globalconfig_temp_files = os.listdir(globalfoncig_temp_path)
	#	for globalconfig_temp_file in globalconfig_temp_files:
	#		os.remove(os.path.join(globalfoncig_temp_path, globalconfig_temp_file))
	
	#delete all the .exe files	
	for l in pdb_copy_list :
		filename = l + '64.exe'
		file_path = os.path.join(os.path.join(os.path.join(src_root, bin_path), l), filename)
		if os.path.isfile(file_path):
			os.remove(file_path)
		#if os.path.isdir(dir_path):
		#	os.system('rmdir /s /q "%s"' % dir_path)
		filename = l + '64_d.exe'
		file_path = os.path.join(os.path.join(os.path.join(src_root, bin_path), l), filename)
		if os.path.isfile(file_path):
			os.remove(file_path)			

	return False
    
def stop_compile():
	global flag_f
	flag_f.close()
	os.remove(os.path.join('D:\\AutoBuild\\python', compile_flag_path))
	
def compile_fail_info(binary_number, info):
    file_path = 'static/%s_%s_err.txt' % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()), binary_number)
    open(file_path, 'w').write(info)
    
def comp(d, debug=False, is_asimov=False, distribution=False):
	print 'Try to compile: '
	print d
	
	os.path.join(p4_root, d)
	print vs_evn_cmd
	p = subprocess.Popen(args=vs_evn_cmd, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	p.stdin.write("echo %path%\n")

	if distribution==False:
		if is_asimov==False:
			if debug:
				print '============x64 debug======================'
				#exec_cmd = 'msbuild.exe "%s" /t:Rebuild /p:Platform="x64" /p:Configuration="Debug" \r\n' % (os.path.join(p4_root, d))	
				exec_cmd = 'devenv "%s" /Rebuild "Debug|x64"' % (os.path.join(p4_root, d))
			else:
				print '============x64 release======================'			
				#exec_cmd = 'msbuild.exe "%s" /t:Rebuild /p:Platform="x64" /p:Configuration="Release" \r\n' % (os.path.join(p4_root, d))
				exec_cmd = 'devenv "%s" /Rebuild "Release|x64"' % (os.path.join(p4_root, d))
		else:
			print '============win32 release======================'
			exec_cmd = 'devenv "%s" /Rebuild "Release|Win32"' % (os.path.join(p4_root, d))
	else:
		if debug:
			print '============distribution debug======================'		
			#exec_cmd = 'msbuild.exe "%s" /t:Rebuild /p:Platform="x64" /p:Configuration="Final Debug" \r\n' % (os.path.join(p4_root, d))	
			exec_cmd = 'devenv "%s" /Rebuild "Final Debug|x64"' % (os.path.join(p4_root, d))
			print exec_cmd
		else:
			print '============distribution release======================'				
			#exec_cmd = 'msbuild.exe "%s" /t:Rebuild /p:Platform="x64" /p:Configuration="Final Release" \r\n' % (os.path.join(p4_root, d))
			exec_cmd = 'devenv "%s" /Rebuild "Final Release|x64"' % (os.path.join(p4_root, d))
			
	print(exec_cmd)	
	p.stdin.write(exec_cmd)
	p.stdin.write("\nexit\n")
	
	result_str = ''
	while True:
		buf = p.stdout.readline()
		if buf == '':
			break
		flag_f.write(buf)
		flag_f.flush()
		result_str += buf
	
	print result_str
	print 'ok'
	return result_str

def remove_files(path) :

	files = os.listdir(path)
		
	for file in files :
		file_path = os.path.join(path, file)	

		if os.path.isdir(file_path):
			remove_files(file_path)
		else :
			os.remove(file_path)
	
def sync_change_list(branch, change):

	result_str = ' '	
	
	#delete_dir_path = sln_src_path + '_' + branch
	#delete_dir_path = os.path.join(os.path.join(delete_dir_path, sln_newser_path), bin_path)
	#if os.path.isdir(delete_dir_path) :
	#	remove_files(delete_dir_path)
	
	#line = "begin to delete bin dir : " + delete_dir_path
	#print line
	
	line = "Begin sync changelist : " + change 
	print line

	newserver_command = "p4 sync -f " + sln_src_path
	
	if branch != "TRUNK" :
		newserver_command = newserver_command + '_' + branch
	
	common_command = os.path.join(newserver_command, sln_common_path)
	common_command = common_command + '\...'
	
	print '--------------------'
	print common_command
	print '--------------------'
	
	result_str = result_str + '-------------------- ' + common_command + ' --------------------'
	
	newserver_command = os.path.join(newserver_command, sln_newser_path)
	newserver_command = newserver_command + '\...'

	print '--------------------'
	print newserver_command
	print '--------------------'

	result_str = result_str + '-------------------- ' + newserver_command + ' --------------------'
	
	common_logs = os.popen(common_command).readlines()
	for common_log in common_logs :
		result_str = result_str + common_log
	
	newserver_logs = os.popen(newserver_command).readlines()
	for newserver_log in newserver_logs :
		result_str = result_str + common_log
	
	return result_str

def compile_server(binary_number, debug=False, distribution=False, is_asimov = False):
	global flag_f
	
	if is_asimov:
		solution_path = asi_paths
	else:
		solution_path = sln_paths
	
	result_str = comp(solution_path, debug, is_asimov, distribution)
	rr = err_r.findall(result_str)
	if result_str.find('Build FAILED.') >= 0:
		compile_fail_info(binary_number, result_str)
		return False, result_str

	return True, result_str

def start_log():
	global flag_log
	global flag_html
	
	if os.path.isfile(os.path.join(os.path.join(os.path.join(output_root, edition_root), log_root), log_flag_path)):
		flag_log.close()
		os.remove(os.path.join(os.path.join(output_root, edition_root), log_root), log_flag_path)
	flag_log = open(os.path.join(os.path.join(os.path.join(output_root, edition_root), log_root), log_flag_path), 'w')

	if os.path.isfile(os.path.join(os.path.join(os.path.join(output_root, edition_root), log_root), html_flag_path)):
		flag_html.close()
		os.remove(os.path.join(os.path.join(output_root, edition_root), log_root), html_flag_path)
	flag_html = open(os.path.join(os.path.join(os.path.join(output_root, edition_root), log_root), html_flag_path), 'w')
	
	flag_html.write('<html><head><meta http-equiv="Content-Type" content="text/html; charset=gb2312" /><title>服务器端编译结果</title></head><body><br/><a href="#syncinfo">1.P4 Sync Info</a><br/><a href="#debuginfo">2.Compile Info (Debug)</a><br/><a href="#releaseinfo">3.Compile Info (Release)</a><br/><a href="#asidebug">4.Compile Info (Asimov_Debug)</a><br/><a href="#asirelease">5.Compile Info (Asimov_Release)</a><br/>')
	flag_html.flush()	
		
	return True
	
def process_log(name, head, data):
	global flag_log
	global flag_html
	
	content = '<a name = ' + name + '><h2>' + head + '</h2><a><br/>'
	flag_html.write(content)
	flag_html.flush()
	
	content = head + ' : \n'
	flag_log.write(content)
	flag_log.flush()	
		
	l = data.split('\n')
	for line in l:
		content = line + '<br>'	
		flag_html.write(content)
		flag_html.flush()	
		
		content = line + '\n'
		flag_log.write(content)
		flag_log.flush()	

def process_log_only(head, data):
	content = head + ' : \n'
	flag_log.write(content)
	flag_log.flush()	
		
	l = data.split('\n')
	for line in l:		
		content = line + '\n'
		flag_log.write(content)
		flag_log.flush()
		
def process_log_area(name, head, data):
	global flag_log
	content = '<a name=' + name + '>' + head + '</a><br/><textarea style="width: 800px;height: 360px;font-size: smaller" >' + data + '</textarea><br/>'
	flag_html.write(content)
	flag_html.flush()

	content = head + ' : \n' + data
	flag_log.write(content)
	flag_log.flush()

def stop_log():
	global flag_log
	global flag_html
	
	flag_log.close()
 
	flag_html.write("</body></html>")
	flag_html.flush()
	flag_html.close()	
 
def analysis_log(log):
	global flag_html
	warningnum_ana = 0
	errornum_ana = 0
	l = log.split('\n')
	
	for i in l:
		if i.find('): error ') >= 0 or i.find('Project : error') >= 0 or i.find('fatal error') >= 0:			
			errornum_ana = errornum_ana + 1
			font_content = '<font color = "red">' + i + '</font><br/>'
		elif i.find('): warning ') >= 0:	
			warningnum_ana = warningnum_ana + 1
			font_content = '<font color = "green">' + i + '</font><br/>'
		else:
			font_content = '<font color = "black">' + i + '</font><br/>'	
			
		flag_html.write(font_content)
		flag_html.flush()
	
	return errornum_ana, warningnum_ana
 
def update_version(ver, branch_select):
	
	
	print '--------------------------'
	print 'Begin to update version : ' + ver
	
	ver_string = "update version to %s" % ver
	process_log_only("update_version", ver_string)
	
	if branch_select != "Trunk" : 
		script_temp = sln_src_path + '_' + branch_select	
	else:
		script_temp = sln_src_path		
		
	script_temp = os.path.join(script_temp, 'Common')
	script_temp = os.path.join(script_temp, 'define')
	script_temp = os.path.join(script_temp, 'version.h')

	command = "del " + script_temp + " /F/Q"
	os.popen(command)

	command = "echo #ifndef _VERSION_H_ > " + script_temp
	os.popen(command)

	command = "echo #define _VERSION_H_ >> " + script_temp
	os.popen(command)
	
	command = "echo #define MAJOR_VERSION (0) >> " + script_temp
	os.popen(command)

	command = "echo #define MINOR_VERSION (1) >> " + script_temp
	os.popen(command)	
	
	command = "echo #define BUILD_NUMBER (%s) >> " + script_temp
	command = command % ver
	os.popen(command)	
	
	command = "echo #endif //_VERSION_H_ >> " + script_temp
	os.popen(command)	

	return True
 
def compile_asi(sys):

	warningnum = 0
	errornum = 0
	
	print '----start to compile asi release version----'	
	result, buf = compile_server(sys.argv[i], True)
	process_log('asirelease', '5.Compile Info (Asimov_Release)', buf)		
	error_debug, warning_debug = analysis_log(buf)
	errornum = errornum + error_debug		
	warningnum = warningnum + warning_debug			
	if result == False:
		return False, error_debug, warning_debug
				
	return	True, errornum, warningnum

def compile_asimov(v, debug = False):
	global flag_f
	for d in asi_paths:
		result_str = comp(d, debug, True)
		rr = err_r.findall(result_str)
		if result_str.find('Build FAILED.') >= 0:
			compile_fail_info(v, result_str)
			return False, result_str

	return True, result_str
				
def compile_script_files(compile_script_path):
		
		files = os.listdir(compile_script_path)
		
		for file in files :
			file_path = os.path.join(compile_script_path, file)
			
			if os.path.isdir(file_path):
				compile_script_files(file_path)
			else :
				houzhui = os.path.splitext(file_path)[1]
				if houzhui == '.lua':
					temp_file_path = os.path.join(compile_script_path, 'temp.lua')
					os.rename(file_path, temp_file_path)
					command = 'D:\AutoBuild\python\luac64.exe -o ' + file_path + ' ' + temp_file_path  # + ' ' + '\x0D' + '\x0A'
					os.system(command)			
					del_command = 'del /f/s/q ' + temp_file_path
					os.system(del_command)

					#os.remove(file_path)	#here cannot delete file because occupied by system, neither can be by time.sleep(2)
					
def copy_compile_file(isFinal, branch) :
	
	if not os.path.isdir(edition_path):
		os.makedirs(edition_path)
	
	files = os.listdir(os.path.join(src_root, bin_path))
	
	shutil.copytree(os.path.join(os.path.join(src_root, bin_path), 'dyncodebin64'), os.path.join(edition_path, 'dyncodebin64'))		
	shutil.copytree(os.path.join(os.path.join(src_root, bin_path), 'gmconfig'), os.path.join(edition_path, 'gmconfig'))
	
	shutil.copytree(os.path.join(os.path.join(os.path.join(src_root, bin_path), 'manageserver'), 'oa_billing'), os.path.join(os.path.join(edition_path, 'manageserver'), 'oa_billing'))
	shutil.copytree(os.path.join(os.path.join(os.path.join(src_root, bin_path), 'loginserver'), 'oa_authorize'), os.path.join(os.path.join(edition_path, 'loginserver'), 'oa_authorize'))
	shutil.copy(os.path.join(os.path.join(os.path.join(src_root, bin_path), 'manageserver'), 'fcmsdk.ini'), os.path.join(edition_path, 'manageserver'))	
	
	#copy common file in common_copy_list	
	for commonfile in common_copy_list:
		for file in files:
			if file.find(commonfile) >= 0:
				shutil.copy(os.path.join(os.path.join(src_root, bin_path), commonfile), os.path.join(edition_path, commonfile))
	
	#copy .dll & .exe files with debug mode
	for file in files:
		if os.path.isdir(os.path.join(os.path.join(src_root, bin_path), file)):
			dirfiles = os.listdir(os.path.join(os.path.join(src_root, bin_path), file))
			for dir_file in dirfiles:
				for file_copy in file_copy_list_debug:
					if dir_file.find(file_copy) >= 0:
						if not os.path.isdir(os.path.join(edition_path, file)):
							os.mkdir(os.path.join(edition_path, file))
						shutil.copy(os.path.join(os.path.join(os.path.join(src_root, bin_path), file), dir_file), os.path.join(os.path.join(edition_path, file), dir_file))

		else:
			for file_copy in file_copy_list_debug:
				if file.find(file_copy) >= 0:
					shutil.copy(os.path.join(os.path.join(src_root, bin_path), file), edition_path)

	#copy globalconfig
	if isFinal :
		#copy needed files
		shutil.copytree(maintaintoolpath, os.path.join(edition_path, globalconfig_root))

		#copy other files
		glocalconfig_path = os.path.join(os.path.join(src_root, bin_path), globalconfig_root)
		otherfiles = os.listdir(glocalconfig_path)
		for otherfile in otherfiles:
			exist_path = os.path.join(os.path.join(edition_path, globalconfig_root), otherfile)
	
			if not os.path.isfile(exist_path):
				shutil.copy(os.path.join(os.path.join(os.path.join(src_root, bin_path), glocalconfig_path), otherfile), os.path.join(edition_path, globalconfig_root))
				
		shutil.copytree(os.path.join(os.path.join(src_root, bin_path), 'commonconfig'), os.path.join(edition_path, 'commonconfig'))					
				
	else:
		shutil.copytree(os.path.join(os.path.join(src_root, bin_path), 'commonconfig'), os.path.join(edition_path, 'commonconfig'))			
		shutil.copytree(os.path.join(os.path.join(src_root, bin_path), globalconfig_root), os.path.join(edition_path, globalconfig_root))
	
	#compile script
	for compile_script_file in compile_script_list :
		compile_script_files(os.path.join(edition_path, compile_script_file))
	
	#pak commonconfig & bin
	pre_path = os.getcwd()
	os.chdir(edition_path)		
	os.system('D:\\AutoBuild\\python\\pak.exe create commonconfig')
	os.system('D:\\AutoBuild\\python\\pak.exe create globalconfig')
	os.system('rmdir /s /q "%s"' % os.path.join(os.path.join(os.path.join(output_root, edition_root), edition_name), data_root))
	os.system('rmdir /s /q "%s"' % os.path.join(os.path.join(os.path.join(output_root, edition_root), edition_name), commonconfig_root))		
	os.system('rmdir /s /q "%s"' % os.path.join(os.path.join(os.path.join(output_root, edition_root), edition_name), globalconfig_root))
	
	os.mkdir(os.path.join(os.path.join(os.path.join(output_root, edition_root), edition_name), data_root))
	shutil.copy(os.path.join(os.path.join(os.path.join(output_root, edition_root), edition_name), 'commonconfig.pak'), os.path.join(os.path.join(os.path.join(os.path.join(output_root, edition_root), edition_name), data_root), 'commonconfig.pak'))		
	shutil.copy(os.path.join(os.path.join(os.path.join(output_root, edition_root), edition_name), 'globalconfig.pak'), os.path.join(os.path.join(os.path.join(os.path.join(output_root, edition_root), edition_name), data_root), 'globalconfig.pak'))		
	os.remove(os.path.join(os.path.join(os.path.join(output_root, edition_root), edition_name), 'commonconfig.pak'))
	os.remove(os.path.join(os.path.join(os.path.join(output_root, edition_root), edition_name), 'globalconfig.pak'))
	
	os.chdir(os.path.join(output_root, edition_root))
	
	zip_file_name = edition_name + '.zip'
	zip_command = 'D:\AutoBuild\python\zip_7z.exe -y a ' + os.path.join(os.path.join(output_root, edition_root), zip_file_name)+ ' ' + os.path.join(os.path.join(output_root, edition_root), edition_name)
	print '-------------------------------------------'
	print zip_command
	print '-------------------------------------------'
	
	os.system(zip_command)	
	
	#copy .pak to ./pak
	shutil.copy(os.path.join(os.path.join(output_root, edition_root), zip_file_name), os.path.join(os.path.join(output_root, edition_root), pak_path));				
	os.remove(os.path.join(os.path.join(output_root, edition_root), zip_file_name));
	
	os.chdir(pre_path)	
	
	#copy pdb file
	for dir_name in pdb_copy_list:
		for file in files:
			if file.find(dir_name) >= 0:
				dir_files = os.listdir(os.path.join(os.path.join(src_root, bin_path), file))
				for dir_file in dir_files:
					houzhui = os.path.splitext(os.path.join(os.path.join(os.path.join(src_root, bin_path), file), dir_file))[1]
					if houzhui == '.ilk' or houzhui == '.pdb':
						shutil.copy(os.path.join(os.path.join(os.path.join(src_root, bin_path), file), dir_file), os.path.join(edition_path, file))
	
	#run gendoc
	if branch != "TRUNK" :
		gen_doc_path = sln_src_path + '_' + branch
	
	gen_doc_path = os.path.join(gen_doc_path, sln_newser_path)
	
	os.chdir(os.path.join(gen_doc_path, 'doc'))
	
	print os.path.join(gen_doc_path, 'doc')
	
	print '------start to gen doc-----------'
	print os.path.join(os.path.join(gen_doc_path, 'doc'), 'gendoc.bat')
	
	os.system(os.path.join(os.path.join(gen_doc_path, 'doc'), 'gendoc.bat'))
	
	return True;

def delete_dir(path) :
	command = 'rd /s/q ' + path
	os.system(command)
	
	return True
	
def copy_asimov_file() :
	stop_compile()		
	return True	
		
if __name__ == '__main__':
	if not init_p4_data():
		sys.stderr.write('Init p4 fail.\n')
		os.exit(-1)
		
	if sys.argv[1] != 'Trunk':
		sln_paths_temp = sln_src_path + '_' + sys.argv[1]
		html_flag_path_temp = 'compile_log' + '_' + sys.argv[1] + '_%s_%s.html'	
	else :
		sln_paths_temp = sln_src_path
		html_flag_path_temp = 'compile_log_%s_%s.html'
		
	src_root = os.path.join(sln_paths_temp, sln_newser_path)
	sln_paths = os.path.join(src_root, sln_slotution_path)
	asi_paths = os.path.join(src_root, sln_asimov_path)
	html_flag_path = html_flag_path_temp % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()), sys.argv[2])	
	
	edition_name_temp = sys.argv[3] + '_' + sys.argv[1] + '_%s_%d'
	edition_name = edition_name_temp % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()), string.atoi(sys.argv[2]))			
	
	if start_compile():
		sys.stderr.write('Compiling.\n')
		sys.exit(-1)

	maintaintoolpath = os.path.join(src_root, 'tools\\maintaintool\\bin\\area_config\\globalconfig')

	set_env_command = 'p4 set P4CLIENT=builds'
		
	os.system(set_env_command)
	
	start_log()
	
	synctime_begin = '--------start to sync data: %s' % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()))			
	process_log('syncinfo', '1.P4 Sync Info', synctime_begin)
		
	delete_dir_path = sln_src_path + '_' + sys.argv[1]
	delete_dir_path = os.path.join(os.path.join(delete_dir_path, sln_newser_path), bin_path)	
	delete_dir(delete_dir_path)
	
	sync_log = sync_change_list(sys.argv[1], sys.argv[2])
	print sync_log
	
	process_log('syncinfo', '1.P4 Sync Info', sync_log)
	
	update_version(sys.argv[2], sys.argv[1])
		
	errornum = 0
	warningnum = 0
	
	synctime_end = "--------end to sync data: %s " % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()))			
	process_log('syncinfo', '1.P4 Sync Info', synctime_end)

	if sys.argv[3] == 'Server' :
		print '----start to compile debug version----'	
		
		compile_debug_begin = "--------start to compile debug: %s " % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()))			
		process_log('debuginfo', '2.Compile Info (Debug)', compile_debug_begin)
		
		result, buf = compile_server(sys.argv[2], True)
		process_log('debuginfo', '2.Compile Info (Debug)', buf)		
		error_debug, warning_debug = analysis_log(buf)
		errornum = errornum + error_debug
		warningnum = warningnum + warning_debug

		edition_path = os.path.join(os.path.join(output_root, edition_root), edition_name)
		
		compile_debug_end = "--------end to compile debug: %s " % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()))			
		process_log('debuginfo', '2.Compile Info (Debug)', compile_debug_end)
		
		print '----start to compile release version----'

		compile_release_begin = "--------start to compile release: %s " % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()))			
		process_log('releaseinfo', '3.Compile Info (Release)',  compile_release_begin)
		
		result, buf = compile_server(sys.argv[2], False)
		process_log('releaseinfo', '3.Compile Info (Release)', buf)	
		error_release, warning_release= analysis_log(buf)	
		errornum = errornum + error_release
		warningnum = warningnum + warning_release	
		
		compile_release_end = "--------end to compile release: %s " % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()))			
		process_log('releaseinfo', '3.Compile Info (Release)',  compile_release_end)
		
		copy_begin = "--------start to copy: %s " % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()))
		process_log('copyinfo', '4.Copy Files', copy_begin)
		
		copy_compile_file(False, sys.argv[1])
		
		copy_end = "--------end to copy: %s " % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()))			
		process_log('copyinfo', '4.Copy Files', copy_end)
		
	if sys.argv[3] == 'Final' : 
		print '----start to compile Final debug version----'
		buf = ' '
		result, buf = compile_server(sys.argv[2], True, True)
		process_log('debuginfo', '2.Compile Info (Final-debug)', buf)
		error_release, warning_release= analysis_log(buf)	
		errornum = errornum + error_release
		warningnum = warningnum + warning_release
		edition_path = os.path.join(os.path.join(output_root, edition_root), edition_name)			

		print '----start to compile Final release version----'		
		
		result, buf = compile_server(sys.argv[2], False, True)
		process_log('debuginfo', '2.Compile Info (release)', buf)		
		error_debug, warning_debug = analysis_log(buf)
		errornum = errornum + error_debug		
		warningnum = warningnum + warning_debug
		copy_compile_file(True, sys.argv[1])
			
	if sys.argv[3] == 'Asimov' : 
		print '----start to compile asimov release version----'		
		result, buf = compile_server(sys.argv[2], False, False, True)
		process_log('releaseinfo', '5.Compile Info (asimov)', buf)	
		error_release, warning_release= analysis_log(buf)	
		errornum = errornum + error_release
		warningnum = warningnum + warning_release
		edition_path = os.path.join(os.path.join(output_root, edition_root), edition_name)			

	print '--------begin to stop compile-----'		
	stop_compile()
	
	print '--------begin to stop log-----'
	stop_log()	

	html_link = redmine_log_html + html_flag_path		

	if errornum == 0:
		
		rtx.send_compile_msg((u'服务器程序编译成功, 版本号 %s, 其中error %d个, warning %d个, 编译详情请参见 %s' % (edition_name, errornum, warningnum, html_link)).encode('gbk'))		
		sys.exit(0)
		
	else:
		print 'Compile fail'
		rtx.send_compile_msg((u'服务器程序编译失败, 版本号 %s, 其中error %d个, warning %d个, 编译详情请参见 %s' % (edition_name, errornum, warningnum, html_link)).encode('gbk'))
		sys.exit(-1)			
