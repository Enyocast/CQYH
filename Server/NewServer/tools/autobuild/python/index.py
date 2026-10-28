#!/usr/bin/python
#coding=utf8

'''
# Entry point for the Jiutian server automated build script.
'''

import subprocess
import os, sys
import web
import time
import shutil
import string

edition_path = "..\\edition"

urls = (
	'/', 'CIndex',
)

def run_cmd(cmd):
	p = subprocess.Popen(args=cmd, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)	
	return p.stdout.read()

def distribute_version(ver):
	if not os.path.isdir(os.path.join(os.path.join(output_root, edition_path), ver)):
		os.exit(-1)
		
	if os.path.isdir(os.path.join(os.path.join(output_root, edition_path), runbin_path)):
		files = os.listdir(os.path.join(os.path.join(output_root, edition_path), runbin_path))
		for file in files:
			if cmp(file,'log'):
				file_name = os.path.join(os.path.join(os.path.join(output_root, edition_path), runbin_path), file)
				if os.path.isdir(file_name):
					os.system('rmdir /s /q "%s"' % file_name)
				else:
					os.system('del /f /q "%s"' % file_name)
		
	src_path = os.path.join(os.path.join(output_root, edition_path), ver)
	dst_path = os.path.join(os.path.join(output_root, edition_path), runbin_path)
	files = os.listdir(src_path)
	for file in files:
		file_name = os.path.join(os.path.join(os.path.join(output_root, edition_path), ver), file)
		if os.path.isdir(file_name):
			shutil.copytree(file_name, os.path.join(dst_path, file))
		else:
			shutil.copy(file_name, dst_path)
			
	#shutil.copytree(src_path, os.path.join(os.path.join(output_root, edition_path), runbin_path))
	
	if not os.path.isdir(os.path.join(os.path.join(os.path.join(output_root, edition_path), runbin_path), ver)):
		os.mkdir(os.path.join(os.path.join(os.path.join(output_root, edition_path), runbin_path), ver))
	
	rtx.send_msg((u'服务器发布版本成功, 版本号 : %s' % (ver)).encode('gbk'))
	
	return True

def get_versions():
	global edition_path
	servers = []
	os.system("If Not Exist Logs MD " + edition_path)
	dirs = os.listdir(edition_path)
	for dir in dirs[::-1]:
		if dir.find('runbin') < 0 and dir.find('pak') < 0:
			server["name"] = dir
			server["ip"] = "http://172.30.66.35/build/pak/" + dir + ".zip"
			servers.append(server)
				
	return servers
	
class CIndex:
	def show_page(self, pre_data = {}):
		render = web.template.render('templates')
		d = pre_data
		d['versions'] = get_versions()

		return render.index(d)

	def POST(self):
		print '-----------POST------'
		d = web.input()
		v = {}
		v['msg'] = ''	
		revision_number = d['revision']
		branch_name = d['branch']
		build_type = d['type']

		print revision_number
		print branch_name
		print build_type
		print d['action']
		
		if 'action' in d:
			if d['action'] == 'compile':
				os.system("python.exe build.py " + revision_number + " " + branch_name + " " + build_type)
				v['msg'] = u'end'
			else:
				v['msg'] = u'invalid action'

		return self.show_page(v)

	def GET(self):
		print '-----------GET------'	
		d = web.input()
		v = {}
		v['msg'] = ''	
		
		if 'action' in d:
			if d['action'] == 'distribute':
				distribute_version(d['version'])
				v['msg'] = u'distribute successfully'
			else:
				v['msg'] = u'invalid action'
				
		return self.show_page(v)
		
if __name__ == "__main__":
	app = web.application(urls, globals())
	app.run()
