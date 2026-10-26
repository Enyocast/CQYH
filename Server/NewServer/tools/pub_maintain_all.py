#coding: utf8
#!/usr/bin/env python

import os, os.path, sys, time
import re
import subprocess
import getopt
import shutil
import string

import datetime
g_now = datetime.datetime.now()
g_now_str = g_now.strftime("%Y%m%d-%H%M%S")
	
maintaintool_need_copy_filelist = [
	'maintaintool.exe',
	'maintaintool.pdb',
	'maintaintool_config.lua',
	'7z.exe',
	'icudt52.dll',
	'icuin52.dll',
	'icuuc52.dll',
	'libEGL.dll',
	'libGLESv2.dll',
	'msvcp120.dll',
	'msvcr120.dll',
	'lua64.dll',
	#'lua64.pdb',
	'luac64.exe',
	'Qt5Core.dll',
	'Qt5Gui.dll',
	'Qt5Widgets.dll',
	#r'platforms\qwindowsd.pdb',
	r'platforms\qwindowsd.dll',
	r'platforms\qwindows.dll',
	r'toolconfig\maintainconfig.lua',
	r'area_config\gmsecurityconfig.lua',
	r'area_config\1_localhost\area_config.lua',
	r'area_config\1_localhost\127.0.0.1\guard_area_config.lua',
]
	
guard_need_copy_filelist = [
	r'guardconfig\guardconfig.lua',
	r'guardconfig\guard_area_config.lua',
	'guardserver64.exe',
	'guardserver64.pdb',
	'guard_config.lua',
	'guardserver_run.bat',
	'install_guard_service.bat',
	'uninstall_guard_service.bat',
	'lua64.dll',
	'lua64.pdb',
	'msvcp120.dll',
	'msvcr120.dll',
	'7z.exe',
]

def ensure_one_instance():
	taken_port = 61234
	import socket
	try:
		global s # to keep socket handle until script finished
		s = socket.socket()
		host = socket.gethostname()
		s.bind((host,taken_port))
	except:
		print "must have only one instance"
		raise Error()
	
def ensure_p4(src_path):
	pass
	
def generate_header(server_path):
	target_path = server_path + r"\..\Common\define\maintain_tool_version.h"
	
	if not os.path.exists(target_path):
		print(server_path+" is not server path, generate header failed!")
		raise Error();
	
	os.popen(r"del /F/Q "+target_path)
	os.popen(r"echo #ifndef _MAINTAIN_TOOL_VERSION_H_ > "						+target_path)
	os.popen(r"echo #define _MAINTAIN_TOOL_VERSION_H_ >> "						+target_path)
	os.popen(r'echo #define MAINTAIN_TOOLS_BUILD_VERSION "'+ g_now_str +'" >>'	+target_path)
	os.popen(r"echo #endif //_MAINTAIN_TOOL_VERSION_H_ >> "						+target_path)
	
def build(sln_path, debugOrRelease = "Release"):
	vs_paths = [	
		r'c:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat',
		r'd:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat',
	]
	for path in vs_paths:
		if os.path.exists(path):
			vs_path = path
			break
	
	vs_evn_cmd = '%comspec% /k "' + vs_path + '" x64\n'
	#print vs_evn_cmd
	p = subprocess.Popen(args=vs_evn_cmd, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	p.stdin.write("echo %path%\n")
			
	#exec_cmd = 'msbuild.exe "%s" /t:Rebuild /p:Platform="x64" /p:Configuration="Release" \r\n' % (os.path.join(p4_root, d))
	exec_cmd = 'devenv "'+ sln_path +'" /Rebuild "'+debugOrRelease+'|x64"'
	p.stdin.write(exec_cmd)
	
	p.stdin.write("\nexit\n")
	
	print "building, please wait"
	result_str = ''
	while True:
		buf = p.stdout.readline()
		if buf == '':
			break
		result_str += buf

	#print result_str
	print "building done"

	if result_str.find('Build FAILED.') >= 0:
		print result_str
		raise Error()

def archive(bin_path, need_copy_filelist, archive_path):	
	#clear
	if os.path.exists(archive_path):
		shutil.rmtree(archive_path)
	#os.mkdirs(archive_path)

	try:
		for entry in need_copy_filelist:
			dst_path = os.path.join(archive_path, entry)
			dst_dir = os.path.dirname(dst_path)
			if not os.path.exists(dst_dir):
				os.makedirs(dst_dir)
			shutil.copy(os.path.join(bin_path, entry), dst_path)
	except (IOError, os.error), why:
		print "archive failed! because " + str(why)
		raise IOError()
			
def compress(archive_path):
	zip_command = archive_path + r'\7z.exe -y a ' +archive_path+ '.zip ' +archive_path
	print zip_command
	os.system(zip_command)
		
if __name__ == '__main__':

	try:
		ensure_one_instance()
		
		maintaintool_archive_name = '_Maintaintool.' + g_now_str
		guard_archive_name = '_Guard.' + g_now_str

		root_path = os.getcwd()		# r'E:\p4\aod\08.Prog_CQ\NewServer\tools'
		maintaintool_src_path = root_path + r'\maintaintool\src'
		guard_src_path = root_path + r'\guardserver'
		
		ensure_p4(maintaintool_src_path)
		ensure_p4(guard_src_path)
		
		# 1
		generate_header(root_path + r"\..")
		
		# 2
		print "start to build maintaintool..."
		build(maintaintool_src_path + r"\maintaintool.sln")
		print "start to build guardserver..."
		build(guard_src_path + r"\guardserver.sln")	

		# 3
		archive(maintaintool_src_path + r"\..\bin", maintaintool_need_copy_filelist, maintaintool_archive_name)
		archive(guard_src_path + r"\..\..\bin\_Guard", guard_need_copy_filelist, guard_archive_name)
		
		# 4
		compress(maintaintool_archive_name)
		compress(guard_archive_name)
		
	finally:
		raw_input("Press any key to end...\n")	
		os._exit(0)
		
