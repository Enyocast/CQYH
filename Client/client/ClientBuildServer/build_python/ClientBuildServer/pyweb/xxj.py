#!/usr/bin/python
#coding=utf8

'''
机器人管理web接口。
'''

import subprocess
import os
import web
import time

urls = (
    '/', 'CIndex',
)

r_name = {
    12327: '非诚勿扰娘',
    12328: '坚持浪漫主义',
    12329: '在悸动的季节里',
    12330: '你好了我也就好了',
    12331: '低调拉风de囡囡',
    12332: '霓虹浮云er',
    12333: '爱在爱琴海mm',
    12335: '普罗旺斯的女王',
    12336: '南贤俊1号',
    12337: 'BABYLOVE颖',
    12339: '骑着卡拉去溜猫',
    12340: '真莹莹1990',
    12341: '裘思楠',
    12342: '射手曾经是处男',
    12343: '听浪小筑',
    12345: '只为了自己而存在',
    12346: 'oo0宝儿0oo',
    12347: '无花果2002',
    12351: '菠萝菠萝蜜_蜜',
    12352: '木奉木奉饄',
    12357: '了雪无晴',
    12362: '--單單--恐龙',
    12366: '包子同学战无不胜',
    12372: '筱芎Ivy',
    12377: '玻璃_鱼',
    12382: '马尔泰若楠',
    }

robot_path = '/home/chuan/pytest/robot/'

def kill_lala(pid):
    os.system('kill -9 %s' % pid)
    time.sleep(0.2)

def kill_amy(is_sina=False, is_spike=False):
    if not is_sina:
        os.system(robot_path + 'kill_local.sh')
    else:
        if not is_spike:
            os.system(robot_path + 'kill_sina.sh')
        else:
            os.system(robot_path + 'kill_spike.sh')

def start_amy(is_sina=False, is_spike=False):
    if get_amy_process_info(is_sina, is_spike):
        return
    
    if not is_sina:
        os.system(robot_path + 'start_local.sh')
    else:
        if not is_spike:
            os.system(robot_path + 'start_sina.sh')
        else:
            os.system(robot_path + 'start_spike.sh')
    time.sleep(0.3)
    return

def get_amy_process_info(is_sina=False, is_spike=False):
    if not is_sina:
        buf = run_cmd('ps aux|grep amy\.py|grep -v grep|grep config_local_amy')
    else:
        if not is_spike:
            buf = run_cmd('ps aux|grep amy\.py|grep -v grep|grep config_amy')
        else:
            buf = run_cmd('ps aux|grep amy\.py|grep -v grep|grep config_spike')
            
    l = [i for i in buf.split(' ') if i]
    if buf:
        d = {}
        d['pid'] = l[1]
        d['memory'] = int(l[5])/1000.0
        return d
    else:
        return None

def get_lala_process_info(is_sina=False, is_spike=False):
    if not is_sina:
        buf = run_cmd('ps aux|grep lala\.py|grep -v grep|grep config_local_amy')
    else:
        if not is_spike:
            buf = run_cmd('ps aux|grep lala\.py|grep -v grep|grep config_amy')
        else:
            buf = run_cmd('ps aux|grep lala\.py|grep -v grep|grep config_spike')
        
    if not buf.split('\n'):
        return None
    
    l = [i for i in buf.split('\n') if i]
    ll = []
    for i in l:
        t = [x for x in i.split(' ') if x]
        tl = {}
        tl['pid'] = t[1]
        tl['cpu'] = t[2]
        tl['memory'] = int(t[5])/1000
        tl['user_id'] = t[15]
        tl['room_id'] = t[21]
        tl['name'] = '%20s' % r_name.get(int(tl['user_id']))
        ll.append(tl)

    return ll

def run_cmd(cmd):
    p = subprocess.Popen(args=cmd, shell=True,
                         stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    return p.stdout.read()

def get_db():
    return web.database(host='10.240.168.64', dbn='mysql', user='root',
                        pw='lalalala', db='lzwwq')

class CIndex:
    def show_page(self):
        render = web.template.render('templates')
        d = {}
        d['amy'] = get_amy_process_info(True)
        d['lala'] = get_lala_process_info(True)

        d['amy_local'] = get_amy_process_info(False)
        d['lala_local'] = get_lala_process_info(False)

        d['amy_spike'] = get_amy_process_info(True, True)
        d['lala_spike'] = get_lala_process_info(True, True)
        return render.xxj(d)
    
    def GET(self):
        d = web.input()
        if 'kill_amy' in d:
            t = d['kill_amy']
            if t == 'sina':
                kill_amy(True)
            elif t == 'spike':
                kill_amy(True, True)
            else:
                kill_amy(False)
        elif 'kill_lala' in d:
            pid = d['kill_lala']
            kill_lala(pid)
        elif 'start_amy' in d:
            t = d['start_amy']
            if t == 'sina':
                start_amy(True)
            elif t == 'spike':
                start_amy(True, True)
            else:
                start_amy(False)

        return self.show_page()

if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()
