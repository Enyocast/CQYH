#!/usr/bin/env python
#coding: gbk

import os, sys, time
import re
import subprocess
import getopt
import shutil
import rtx

bin_path = 'C:/build/edition/run_bin/asimov'
case_flag_path = './case_running'
flag_f = None

cl_r = re.compile('Change (\d+?) on')
err_r = re.compile('(\d+?) Error\(s\)')

def run_cmd(cmd):
    p = subprocess.Popen(args=cmd, shell=True,
                         stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    return p.stdout.read()

def case_info():
    global flag_f
    if os.path.isfile(case_flag_path):
        buf = open(case_flag_path, 'r').read()
        return True, buf
    return False, None

def start_case():
    return False
    '''
    global flag_f
    if os.path.isfile(case_flag_path):
        return True
    flag_f = open(case_flag_path, 'w')
    flag_f.write("Running")
    return False'''
    
def stop_case():
    global flag_f
    flag_f.close()
    os.remove(case_flag_path)
    
def case_fail_info(v, info):
    file_path = 'case_err/%s_%s_case_err' % (time.strftime('%Y_%m_%d_%H_%M_%S', time.localtime()), v)
    open(file_path, 'w').write(info)

def runcase():
    if start_case():
        sys.stderr.write('Running.\n')
        return False, 'Running'

    pre_path = os.getcwd()
    os.chdir(bin_path)
    
    asimov_path = os.path.join(bin_path, 'asimov_d.exe')
    print asimov_path + ' --runcase'
    buf = run_cmd(asimov_path + ' --runcase')

    os.chdir(pre_path)
    
    #stop_case()

    if not buf:
        return False, ''

    if buf.find('failed') >= 0:
        return False, buf
    return True, buf
