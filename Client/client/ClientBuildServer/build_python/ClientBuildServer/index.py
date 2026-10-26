#!/usr/bin/python
#coding=utf8


import subprocess
import os, sys
import web
import time, datetime
import build_client
import shutil
import case
import rtx
import codecs
import version_mgr
import fix_url_list_mgr
import dir_cfg

if sys.platform == 'win32':
    import win32_process

output_root = '../edition'
running_path = 'run_bin'
guard_process = None
oper_log_file='./_oper.log'
file_f_oper_log_file = None

server_process_name = [
    'gameserver',
    'manageserver',
    'dbserver',
    'loginserver',
    'gateserver',
    'guardserver'
]

urls = (
    '/', 'CIndex',
)

def log_oper(str):
    global file_f_oper_log_file
    global oper_log_file

    if file_f_oper_log_file == None:
         file_f_oper_log_file = open(oper_log_file, 'w')

    file_f_oper_log_file.write(str + '\n')
    file_f_oper_log_file.flush()

def start_process():
    pre_path = os.getcwd()
    if os.path.isdir(os.path.join(output_root, running_path)):
        si = subprocess.STARTUPINFO()
        si.dwFlags = subprocess.STARTF_USESHOWWINDOW
        os.chdir(os.path.join(output_root, running_path))
        global guard_process
        if guard_process is not None:
            ret = subprocess.Popen.poll(guard_process)
            if ret is None:
                subprocess.Popen.terminate(guard_process)
                time.sleep(10)
                guard_process = None;
        
        guard_process = subprocess.Popen(os.path.join(output_root, running_path, 'guardserver/guardserver64_d.exe start primary'),\
                                    #stdin=subprocess.PIPE,stdout=subprocess.PIPE,\
                                    creationflags=subprocess.CREATE_NEW_CONSOLE)
        os.chdir(pre_path)
def run_case():
    pass

def stop_process():
    global guard_process
    if guard_process is not None:
        ret = subprocess.Popen.poll(guard_process)
        if ret is None:
            subprocess.Popen.terminate(guard_process)
            guard_process = None;
            pre_path = os.getcwd()
            if os.path.isdir(os.path.join(output_root, running_path)):
                os.chdir(os.path.join(output_root, running_path))
                guard_process = subprocess.Popen(os.path.join(output_root, running_path, 'guardserver/guardserver64_d.exe stop'),\
                                                 creationflags=subprocess.CREATE_NEW_CONSOLE)
                time.sleep(30)
                os.chdir(pre_path)
                if guard_process is not None:
                    ret = subprocess.Popen.poll(guard_process)
                    if ret is None:
                        subprocess.Popen.terminate(guard_process)
                    guard_process = None
        else:
           guard_process = None 
    return
    
def get_running_ver():
    run_p = os.path.join(output_root, running_path, 'ver.txt')
    if os.path.isfile(run_p):
        return open(run_p, 'r').read()
    return ''

def run_version(ver):
    if ver == running_path:
        start_process()
        return True
    
    run_p = os.path.join(output_root, running_path)
    p = os.path.join(output_root, ver)
    if not os.path.isdir(p):
        return False
    
    stop_process()
    
    #if os.path.isdir(run_p):
    #    os.system('copy %s _log_history/')
    #    os.system('rmdir /s /q "%s"' % run_p)

    #shutil.copytree(p, run_p)
    run_p = run_p.replace('/', '\\')
    p = p.replace('/', '\\')
    print('xcopy %s %s /E /Y' % (p, run_p))
    os.system('xcopy "%s" "%s" /E /Y /R /C' % (p, run_p))
    open(os.path.join(run_p, 'ver.txt'), 'w').write(ver)
    
    start_process()
    return True

def get_avaliable_servers():
    return os.listdir(output_root)
	
def get_err_log():
    return os.listdir('./static')

def get_change_list2():
	branch_num = []
	buf = run_cmd('p4.exe changes -m 50')
	l = buf.split('\n')
	for i in l:
		if i.find('on') >= 0:
			t1 = i.split("on")
			if t1[0].find('Change') >= 0:
				t2 = t1[0].split('Change')
			branch_num.append(t2[1])	
	return branch_num    

def get_change_list():
	branch_num = []
	#os.environ['P4COMMANDCHARSET'] = 'UTF8'
	buf = run_cmd('p4.exe changes -m 50')
	l = buf.split('\n')
	for i in l:
            #print i.codec()
            #print i
            #print i.encode("utf8")
            branch_num.append(unicode(i, encoding="gbk", errors="replace"))
		#if i.find('on') >= 0:
		#	t1 = i.split("on")
		#	if t1[0].find('Change') >= 0:
		#		t2 = t1[0].split('Change')
		#	branch_num.append(t2[1])
	    
	return branch_num

def get_change_list_numb_from_str(strCl):
    if strCl.find('on') >= 0:
        t1 = strCl.split("on")
        if t1[0].find('Change ') >= 0:
            t2 = t1[0].split('Change ')
            return int(t2[1])
    return int(strCl)

def get_label_list():
	labs_num = []
	#os.environ['P4COMMANDCHARSET'] = 'UTF8'
	buf = run_cmd('p4.exe labels')
	l = buf.split('\n')
	for i in l:
            #print i.codec()
            #print i
            #print i.encode("utf8")
            if i != '':
                labs_num.append(get_label_numb_from_str(i))
        #print labs_num
        labs_num.sort(reverse=True)
        #sorted(labs_num, reverse=True)
        #print labs_num
	return labs_num

def get_label_numb_from_str(strCl):
    pos1 = strCl.find(' ')
    pos2 = strCl.find(' ', pos1 + 1)
    return int(strCl[pos1+3:pos2])

def get_process_info(is_sina=False, is_spike=False):
    l = []
    if sys.platform == 'win32':
        sp = win32_process.EnumProcesses()
        for tn, tp in sp.items():
            print tn, tp
        for p in server_process_name:
            for tn, tp in sp.items():
                if tn.find(p) >= 0:
                    l.append([tn, tp])

    return l

def run_cmd(cmd):
    p = subprocess.Popen(args=cmd, shell=True,
                         stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    return p.stdout.read()




class CIndex:
    def show_page(self, pre_data = {}):
        render = web.template.render('templates')
        d = pre_data
        #d['process'] = get_process_info()
        d['available_servers'] = get_avaliable_servers()
        d['err_log'] = get_err_log()
        d['running_ver'] = get_running_ver()
        d['change_list'] = get_change_list()
        d['label_list'] = get_label_list()
        d['ver_list'] = version_mgr.read_vers()
        d['fix_url_list'] = fix_url_list_mgr.read_list()
        d['path_url'] = u''
        
        build_client.init_p4_data()
        v = []
        #for p in build_client.server_codes:
        #    v.append([p, build_client.get_cur_version(p)])
            
        for p in build_client.client_code_path:
            v.append([p, build_client.get_cur_version(p)])

        #if build_client.g_use_label:
        #    v.append(str(build_client.g_label_id))
        #else:
        #    v.append(str(build_client.g_change_list))
        
        d['cur_version'] = v
        vers = version_mgr.read_vers()
        verIdx = 0
        if len(vers) > 1:
            verIdx = len(vers) - 1
            d['last_ver'] = vers[verIdx]
        elif len(vers) == 1:
            d['last_ver'] = vers[0]
        else:
            d['last_ver'] = u'0.0.0.0'
        
        d['is_compile_client'], d['compile_info_client'] = build_client.compile_info_client()
        if d['compile_info_client']:
            d['compile_info_client'] = d['compile_info_client'].decode('gbk').encode('utf8', 'ignore')
        #d['case_running'], d['case_info'] = case.case_info()
        
        return render.index(d)

    def POST(self):
        d = web.input()

        v = {}
        v['msg'] = ''

        print '========================================================================='
        #print d

        if 'mmogame_exe_file' in d:
            mmoexe_file = web.input(mmogame_exe_file={})
            up_file_name = mmoexe_file['mmogame_exe_file'].filename
            targ_file_name = up_file_name
            #targ_file_name = dir_cfg.shipping_output_dir_bin_win32 + u'MMOGame.exe'
            #up_file_obj = mmoexe_file['mmogame_exe_file']
            #print mmoexe_file
            #print '===== upload:', mmoexe_file['mmogame_exe_file'].filename
            #print up_file_obj
            #print mmoexe_file['mmogame_exe_file'].value
            targFile = open(targ_file_name, u'w+')
            #targFile.write(mmoexe_file['mmogame_exe_file'].value)
            targFile.write(mmoexe_file['mmogame_exe_file'].file.read())
            targFile.flush()
            targFile.close()
            up_msg = (u'上传成功:%s' % (str(targ_file_name)))
            v['msg'] = up_msg
            return self.show_page(v)

    def GET(self):
        d = web.input()
        log_oper(str(d))

        v = {}
        v['msg'] = ''

        print '========================================================================='
        print d

        build_client.print_debug_info('Init')

        if 'send_rtx' in d:
            rtx.send_msg_all(d['send_rtx'])
            return self.show_page(v)

        if 'action' in d:
            if d['action'] == 'stop_current_build':
                build_client.stop_current_build()
                return self.show_page(v)

        if build_client.is_cooking() or build_client.is_building():
            return self.show_page(v)

        #增加运营版本号
        if 'new_ver_str' in d:
            print '====== new_ver_str', d
            new_ver_str = d['new_ver_str']
            vers = version_mgr.read_vers()
            for vv in vers:
                print vv
                if vv == new_ver_str:
                    v['msg'] = (u'版本号已存在:%s' % (new_ver_str))
                    return self.show_page(v)

            version_mgr.add_ver(new_ver_str)
            return self.show_page(v)

        # 增加全文件修复URL
        if 'fix_url_str' in d:
            print '====== fix_url_str', d
            fix_url_str = d['fix_url_str']
            vers = fix_url_list_mgr.read_list()
            for vv in vers:
                print vv
                if vv == fix_url_str:
                    v['msg'] = (u'URL已存在:%s' % (fix_url_str))
                    return self.show_page(v)

            fix_url_list_mgr.add_to_list(fix_url_str)
            return self.show_page(v)



        if 'ver_fix_files' in d:
            print '====== 生成全文件修复包', d
            ver_fix_files = d['ver_fix_files']
            fix_url_base = d['fix_url_lists']
            startTime = datetime.datetime.now()
            snap_ver_dir = dir_cfg.snap_ver_root
            src_ver_dir = snap_ver_dir + ver_fix_files
            target_dir = (dir_cfg.fix_url_root + u'%s') % (ver_fix_files)

            log_url = target_dir

            print target_dir
            if os.path.isdir(target_dir):
                v['msg'] = u'修复包已经存在：' + target_dir
                #print '====== target_dir exist', log_url
                return self.show_page(v)

            if not os.path.isdir(src_ver_dir):
                v['msg'] = u'所选的版本快照不存在：' + src_ver_dir
                return self.show_page(v)

            print '====== new_ver_str', target_dir
            #os.system(u'md ' + target_dir)
            cpyCmd = 'ViGenerator.exe ' + src_ver_dir + '\\CQYH\\ ' + target_dir + '\\ ' + ver_fix_files + ' ' + fix_url_base + ver_fix_files + '/'
            print cpyCmd
            os.system(cpyCmd)

            cpyCmd = 'copy /Y ' + target_dir + '\\' + 'CQYH.vimd5 ' + dir_cfg.fix_url_root + 'CQYH.vimd5'
            print cpyCmd
            os.system(cpyCmd)

            timeDur = datetime.datetime.now() - startTime
            v['msg'] = (u'-----全文件修复包生成成功!用时:%s\n [%s|%s]' % (str(timeDur), log_url, log_url))
            v['patch_url'] = log_url
            #rtx.send_msg_qa((u'-----全文件修复包生成成功!用时:%s\n [%s|%s]' % (str(timeDur), log_url, log_url)))
            print v
            return self.show_page(v)



        if 'ver_from' in d:

            ver_from = d['ver_from']
            ver_to = d['ver_to']

            if ver_from == ver_to:
                v['msg'] = '源版本号和目标版本号不能相同'

            if ver_from >= ver_to:
                v['msg'] = '目标版本号必须大于源版本号'
            #print ver_from, ver_to, ver_from == ver_to
            #return self.show_page(v)

            print '====== 补丁生成:', d

            use_mpq_patch = False
            #if 'use_mpq' in d:
            #    use_mpq_patch = d['use_mpq'] == 'on'

            startTime = datetime.datetime.now()
            snap_ver_dir = dir_cfg.snap_ver_root
            target_dir = (dir_cfg.patch_root + u'%s-%s') % (ver_from, ver_to)

            cmdStr = 'del /F /Q ' + snap_ver_dir + ver_from + '\\CQYH\\LocalVersion.xml'
            os.system(cmdStr)

            cmdStr = 'del /F /Q ' + snap_ver_dir + ver_from + '_MPQ\\CQYH\\LocalVersion.xml'
            os.system(cmdStr)

            cmdStr = 'del /F /Q ' + snap_ver_dir + ver_to + '\\CQYH\\LocalVersion.xml'
            os.system(cmdStr)

            cmdStr = 'del /F /Q ' + snap_ver_dir + ver_to + '_MPQ\\CQYH\\LocalVersion.xml'
            os.system(cmdStr)

            #if use_mpq_patch:
            #   target_dir = (dir_cfg.patch_root + u'%s-%s_MPQ') % (ver_from, ver_to)

            target_zip = u'%s\\CQYH_%s-%s.zip' % (target_dir, ver_from, ver_to)

            log_url = (u'%s%s-%s/CQYH_%s-%s.zip/' % (dir_cfg.patch_root, ver_from, ver_to, ver_from, ver_to))
            print target_zip, target_dir
            #print os.path.isfile(target_dir), target_dir
            #return self.show_page(v)
            #print '====== new_ver_str', d
            if os.path.isfile(target_zip):
                v['msg'] = (u'补丁文件已经存在：%s' % (log_url))
                print '====== new_ver_str 2', log_url
            else:
                print '====== new_ver_str', target_zip
                os.system(u'md ' + target_dir)
                delta_exe = snap_ver_dir + u'bindiff\\GenerateMergeDelta.exe'
                if False and use_mpq_patch:
                    cmd_str = u'PakPatcher.exe make %s %s %s %s' % (delta_exe, target_dir, ver_from, ver_to)
                    print cmd_str
                    os.system(cmd_str)
                else:
                    delta_exe = snap_ver_dir + u'bindiff\\GenerateMergeDelta.exe'
                    src_ver_dir = snap_ver_dir + ver_from + u'\\CQYH'
                    dest_ver_dir = snap_ver_dir + ver_to + u'\\CQYH'

                    if False and use_mpq_patch:
                        src_ver_dir = snap_ver_dir + ver_from + u'_MPQ\\CQYH'
                        dest_ver_dir = snap_ver_dir + ver_to + u'_MPQ\\CQYH'


                    cmd_str = u'%s -run_by_cmd_line -game_id CQYH -func_type generate_dir_delta -src_dir \"%s\" -dest_dir \"%s\" -delta_path \"%s\" -old_ver %s -new_ver %s' % (delta_exe, src_ver_dir, dest_ver_dir, target_zip, ver_from, ver_to)
                    print cmd_str
                    #timeDur = datetime.datetime.now() - startTime
                    #v['msg'] = (u'-----补丁生成成功!用时:%s\n [%s|%s]' % (str(timeDur), log_url, log_url))
                    os.system(cmd_str)

                    delta_exe = snap_ver_dir + u'bindiff\\PFlist.exe'
                    cmd_str = u'%s -run_by_cmd_line -func_type generate_file_list -patch_dir \"%s\" -base_url \"http://cq.autopatch.sdo.com/cq\" -backup_base_url \"http://cq.autopatch.sdo.com/cq\" -game_id CQYH -old_ver %s -new_ver %s' % (delta_exe, target_dir, ver_from, ver_to)
                    print cmd_str
                    os.system(cmd_str)

                    cmd_str = dir_cfg.get_bat_file_path('_patch_pack.bat ') + ver_from + ' '+ ver_to + ' ' + (u'CQYH_%s-%s.zip' % (ver_from, ver_to))
                    print cmd_str
                    os.system(cmd_str)

                timeDur = datetime.datetime.now() - startTime
                v['msg'] = (u'-----补丁生成成功!用时:%s\n [%s|%s]' % (str(timeDur), log_url, log_url))
                v['patch_url'] = log_url
                #rtx.send_msg_qa((u'-----补丁生成成功!用时:%s\n [%s|%s]' % (str(timeDur), log_url, log_url)))

            return self.show_page(v)

        if not build_client.is_building():

            if 'build_cl' in d:
                build_client.g_change_list = get_change_list_numb_from_str(d['build_cl'])
            #else:
            #    build_client.g_change_list = -1

            if 'use_label' in d:
                build_client.g_use_label = d['use_label'] == 'on'
            else:
                build_client.g_use_label = False

            if 'use_mpq' in d:
                build_client.g_use_mpq = d['use_mpq'] == 'on'
            else:
                build_client.g_use_mpq = False

            if 'split_upk' in d:
                build_client.g_split_upk = d['split_upk'] == 'on'
            else:
                build_client.g_split_upk = False

            if 'use_resref' in d:
                build_client.g_useSkipUnused = d['use_resref'] == 'on'
            else:
                build_client.g_useSkipUnused = False

            if 'build_label' in d:
                build_client.g_label_id = int(d['build_label'])
            #else:
            #    build_client.g_label_id = -1

            if 'build_branch' in d:
                build_client.g_branch_name = (d['build_branch'])

                if build_client.g_branch_name == u'主干':
                    build_client.g_branch_name = ''
            else:
                build_client.g_branch_name = ''

            print '###### Brunch:' , build_client.g_branch_name

            if 'dbg_skip_compile' in d:
                build_client.dbg_skip_compile = d['dbg_skip_compile'] == 'on'
            else:
                build_client.dbg_skip_compile = False

            if 'dbg_skip_split' in d:
                build_client.dbg_skip_split = d['dbg_skip_split'] == 'on'
            else:
                build_client.dbg_skip_split = False

            if 'SeekFreeMap' in d:
                build_client.g_SeekFreeMap = d['SeekFreeMap'] == 'on'
            else:
                build_client.g_SeekFreeMap = False

            if 'dbg_skip_cook' in d:
                build_client.dbg_skip_cook = d['dbg_skip_cook'] == 'on'
            else:
                build_client.dbg_skip_cook = False

            if 'dbg_skip_resref' in d:
                build_client.dbg_skip_resref = d['dbg_skip_resref'] == 'on'
            else:
                build_client.dbg_skip_resref = False

            #print '[Debug]current change list:', build_client.g_change_list,  build_client.g_use_label, build_client.g_label_id

            build_client.client_code_path = [r'//AgeOfDawn/08.Prog' + build_client.g_branch_name + '/Common/...',r'//AgeOfDawn/08.Prog' + build_client.g_branch_name + '/Client/UE3/...',r'//AgeOfDawn/08.Prog' + build_client.g_branch_name + '/NewServer/bin/commonconfig/...']
            build_client.client_build_UE3_path='..\\source\\08.Prog' + build_client.g_branch_name + '\\Client\\UE3\\'

            #print build_client.client_code_path, build_client.client_build_UE3_path
            #return self.show_page(v)

            build_client.g_is_rebuild = False
            build_client.g_NOAUTOMAPLIST = False
            build_client.g_skip_cook = False
            build_client.g_skip_compile = False

        build_client.print_debug_info('DebugInfo')

        if 'ver_use' in d:
            build_client.g_use_ver = d['ver_use']
        else:
            build_client.g_use_ver = u'0.0.0.0'

        if 'action' in d:
            cmdStr = u'del D:\\_AutoBuild\\Source\\08.Prog_CQ\\Client\\UE3\\MMOGame\\Logs\\*.* /F /Q'
            os.system(cmdStr)
            #if d['action'] == 'update':
                #v['update_ver'] = build_client.update_server_codes()
                #v['msg'] = '更新源代码版本为 ' + str(v['update_ver'])
            if d['action'] == 'make_doodad_quest_cfg':
                build_client.make_doodad_quest_cfg(True)
            elif d['action'] == 'auto_integrate':
                dir_cfg.exec_bat('update_to_08.bat')
            elif d['action'] == 'auto_compile_shipping':
                rtx.send_msg(u'开始自动编译SHIPPING版本，编译不过即时修正，保证晚上自动COOK版本')
                build_client.g_use_label = True
                build_client.g_branch_name=u'_OB_1130'
                build_client.g_label_id = get_label_list()[0]
                build_client.g_use_ver = u'8.8.8.8'
                build_client.g_is_rebuild = True
                build_client._compile_client('-FINAL_RELEASE', 'Shipping|Mixed platforms', 'MMOGame\\ScriptFinalRelease', 'BinariesShipping', dir_cfg.qaclient_bin_patch, dir_cfg.shipping_ver_ini)
                build_client.stop_compile_client()
            elif d['action'] == 'auto_cook':
                #print '--------------------------test---'
                #return self.show_page(v)
                #print get_label_list()
                #print '--------------------------test end---'
                #'''
                rtx.send_msg(u'开始自动COOK版本')
                build_client.fix_mat_usage()
                build_client.g_use_label = True
                build_client.g_branch_name=u'_OB_1130'
                build_client.g_NOAUTOMAPLIST = True
                build_client.g_use_mpq = True
                build_client.g_label_id = get_label_list()[0]
                build_client.g_use_ver = u'8.8.8.8'
                build_client.g_is_rebuild = True
                build_client.g_useSkipUnused = True
                #build_client.fix_mat_usage()
                #build_client.compile_client()
                build_client.compile_shipping(True)
                #build_client.compile_shadercache()
                #'''
                #pass

            elif d['action'] == 'patch_shipping':
                build_client.patch_shipping()
            elif d['action'] == 'patch_qa_build':
                build_client.patch_qabuild()
            elif d['action'] == 'pack_zip':# and build_client.g_use_label:
                startTime = datetime.datetime.now()
                log_url = (u'http://172.30.66.31/aodpatch/Install/%s/' % str(build_client.g_use_ver))
                if not os.path.isdir(dir_cfg.snap_ver_root +  str(build_client.g_use_ver)):
                    v['msg'] = u'版本号对应的快照目录没有：' +  str(build_client.g_use_ver)
                    return self.show_page(v)

                #print '========= pack_zip'
                rtxmsg = ((u'开始打包，请耐心等待！\n 运营版本号：%s') % (str(build_client.g_use_ver)))
                rtx.send_msg_qa(rtxmsg)
                cmd_str = dir_cfg.get_bat_file_path('_pack_ver_new.bat ') + str(build_client.g_use_ver)

                if build_client.g_use_mpq:
                    cmd_str = dir_cfg.get_bat_file_path('_pack_ver_new_mpq.bat ') + str(build_client.g_use_ver)

                print cmd_str
                os.system(cmd_str)
                timeDur = datetime.datetime.now() - startTime
                rtx.send_msg_qa((u'打包成功!\n运营版本号：%s用时:%s\n [%s|%s]' % (build_client.g_use_ver, str(timeDur), log_url, log_url)))
            elif d['action'] == 'snap_ver':
                if os.path.isdir(dir_cfg.snap_ver_root + str(build_client.g_use_ver)):
                    v['msg'] = (u'分支【%s】\n目标版本的快照已经存在，如果要重建请手动删除:%s' % (build_client.g_branch_name, str(build_client.g_use_ver)))
                else:
                    startTime = datetime.datetime.now()
                    #log_url = (u'http://172.30.66.31/aodpatch/Patch/%s/' % str(build_client.g_label_id))
                    rtx.send_msg_qa((u'分支【%s】制作版本快照开始，请耐心等待！请确认EXE等文件已经签名上传到%s\n 运营版本号：%s') %(build_client.g_branch_name, dir_cfg.shipping_output_dir_bin_win32.replace('edition', 'edition\\' + build_client.g_branch_name), build_client.g_use_ver))
                    os.system(dir_cfg.get_bat_file_path('_snap_ver.bat ') + str(build_client.g_use_ver) + ' ' + build_client.g_branch_name + ' ' + str(build_client.g_label_id))

                    attCmd = 'attrib -R -S ' + dir_cfg.snap_ver_root + str(build_client.g_use_ver) + '\\*.* /S /D'
                    os.system(attCmd)
                    print attCmd

                    timeDur = datetime.datetime.now() - startTime
                    rtx.send_msg_qa((u'分支【%s】\n版本快照创建成功!\n运营版本号：%s\n用时:%s' % (build_client.g_branch_name, build_client.g_use_ver, str(timeDur))))
            elif d['action'] == 'del_log':
                #os.system(u'del ' + dir_cfg.patch_root + '*.* /F /Q')
                #os.system(u'del ' + dir_cfg.python_log_dir + '*.* /F /Q')

                cmdStr = u'rd /S /Q ' + dir_cfg.get_game_log_dir(build_client.g_branch_name)
                os.system(cmdStr)
                print cmdStr

                cmdStr = u'rd D:\\_AutoBuild\\Source\\08.Prog' + build_client.g_branch_name + '\\Client\\UE3\\Engine\\Shaders\\WorkingDirectory\\  /S /Q'
                print cmdStr
                os.system(cmdStr)

                os.system(u'del ' + dir_cfg.python_log_dir + '  /S /Q')
            elif d['action'] == 'stop_current_build':
                build_client.stop_cook_client()
            elif d['action'] == 'compile_review':
                build_client.build_review(d['username'], d['build_cl'])
            elif d['action'] == 'compile_client':
                build_client.compile_client()
            elif d['action'] == 'compile_client_rebuild':
                build_client.g_is_rebuild = True
                build_client.compile_client()
            elif d['action'] == 'release_client':
                build_client.release_client()
            elif d['action'] == 'compile_editor':
                build_client.compile_editor()
            elif d['action'] == 'compile_editor_rebuild':
                build_client.g_is_rebuild = True
                build_client.compile_editor()
            elif d['action'] == 'release_editor':
                build_client.release_editor()
            elif d['action'] == 'compile_shipping_only':
                 build_client.g_is_rebuild = True
                 build_client.g_use_label = True
                 build_client.g_update_p4 = False
                 build_client._compile_client('-FINAL_RELEASE', 'Shipping|Mixed platforms', 'MMOGame\\ScriptFinalRelease', 'BinariesShipping', dir_cfg.qaclient_bin_patch, dir_cfg.shipping_ver_ini)
                 build_client.stop_compile_client()
            elif d['action'] == 'compile_shipping':
                build_client.g_is_rebuild = True
                if build_client.compile_shipping(False):
                    build_client.patch_shipping()
            elif d['action'] == 'compile_shipping_manual_config':
                build_client.g_NOAUTOMAPLIST = True
                build_client.g_is_rebuild = False
                if build_client.compile_shipping(False):
                    build_client.patch_shipping()
            elif d['action'] == 'compile_shipping_manual_config_full':
                build_client.g_NOAUTOMAPLIST = True
                build_client.g_is_rebuild = False
                if build_client.compile_shipping(True):
                    build_client.patch_shipping()
            elif d['action'] == 'compile_shipping_skip_cook':
                build_client.g_skip_cook = True
                build_client.g_NOAUTOMAPLIST = True
                build_client.g_is_rebuild = False
                if build_client.compile_shipping(False):
                    build_client.patch_shipping()
            elif d['action'] == 'compile_shipping_skip_cook_compile':
                build_client.g_skip_cook = True
                build_client.g_NOAUTOMAPLIST = True
                build_client.g_is_rebuild = False
                build_client.g_skip_compile = True
                if build_client.compile_shipping(False):
                    build_client.patch_shipping()

            elif d['action'] == 'compile_shipping_full':
                build_client.g_is_rebuild = True
                if build_client.compile_shipping(True):
                    build_client.patch_shipping()
            elif d['action'] == 'release_shipping':
                build_client.release_shipping()
                
            elif d['action'] == 'compile_shadercache':
                build_client.compile_shadercache()

            elif d['action'] == 'gen_res_ref_table':
                build_client.gen_res_ref_table()
                
            elif d['action'] == 'fix_mat_usage':
                build_client.fix_mat_usage()
                
            elif d['action'] == 'compile':
                if os.system('python build_client.py') >= 0:
                    v['msg'] = '编译成功'
                else:
                    v['msg'] = '编译失败'
            elif d['action'] == 'rebuild':
                if os.system('python build_client.py rebuild') >= 0:
                    v['msg'] = '编译成功'
                else:
                    v['msg'] = '编译失败'
            elif d['action'] == 'run':
                run_version(d['version'])
            elif d['action'] == 'stop_process':
                stop_process()
            elif d['action'] == 'runcase':
                retval, buf = case.runcase()
                if buf:
                    v['msg'] = '运行测试Case成功.'
                    
                if not retval:
                    v['msg'] = '运行测试Case失败.'
                    rtx.send_msg('Case fail, version: %s.\n%s.' %
                                 (get_running_ver(), buf))

        #print '[Debug]current change list:', build_client.g_change_list,  build_client.g_use_label, build_client.g_label_id
        build_client.print_debug_info('After Parse Var')
        #print d['cl']
        
        return self.show_page(v)

if __name__ == "__main__":
    #reload(sys)
    #sys.setdefaultencoding('utf-8')
    app = web.application(urls, globals())
    app.run()
