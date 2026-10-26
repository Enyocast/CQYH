#!/usr/bin/env python
#coding: utf-8

import sys, os, re
import urllib
import time

update_url = 'http://172.30.61.58:8089/?action=update'
refresh_url = 'http://172.30.61.58:8089'
compile_url = 'http://172.30.61.58:8089/?action=rebuild'
stop_url = 'http://172.30.61.58:8089/?action=stop_process'
change_version = 'http://172.30.61.58:8089/?action=run&version='
run_case = 'http://172.30.61.58:8089/?action=runcase'

v_r = re.compile(r'(bin_.*) <a')

def geturl(url):
    return urllib.urlopen(url).read()


comp_content = None
geturl(update_url)
comp_content = geturl(compile_url)
if not comp_content:
    print '编译失败'

if comp_content.find('编译成功') >= 0:
    print '编译成功'.decode('utf8')
    l = v_r.findall(geturl(refresh_url))
    v = max(l)
    geturl(stop_url)

    print 'version', v
    geturl(change_version + v)
    print 'change_version + v'
    time.sleep(5)
    geturl(run_case)
else:
    sys.exit(0)
