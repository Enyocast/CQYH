#coding=gbk
import rtx_list

url_template = r'http://172.30.68.97:8012/sendnotify.cgi?msg=[%s] %s&receiver=%s'
url_template_all = r'http://172.30.68.97:8012/sendnotify.cgi?msg=[%s] %s&receiver=%s'

user_list = [
'chenwang',
'zhuming',
'fangruyi',
'huyue',
'zhangwujun',
'yunyu',
'zhuweiqiang',
'baichenglin',
'suibo',
'wuweiyi',
'xialiang',
'yulu',
'华忠',
'songqi',
'dengxiaoshuang',
'songyuezhu',
'qinchuan',
'lixiaolong.bruce',
'Hemu',
'zhaohongfei',
'lubuyuan',
'shaojunjie',
'liuyang.ocean',
'朱剑丘',
'yangyun',
'huazhong',
'lixj',
'wubin',
'zhaohanhan',
'zhangguiquan',
'xiaoni',
'XiongJun',
'huqiongyu',
'longfei',
'qintao',
'yangyun02',
'zhanglinjian',
'ceping',
'lianhongkun',
'renbeili',
'yinyuna',
'wuliang',
'zhangqi',
'wuliang01',
'akillylove',
'songshenglan',
'李夏光',
'ZHANGMIAO',
'zhangyuntian',
'yaochanghai',
'gaohuaxiang.watson',
'jinyuanfei',
'luchenlei',
'juheqi',
'avalon',
'caixuhui',
'zhaomeng01',
'zhuqin',
'xingbing',
'zhaozhenyang',
'yulefeng',
'jinyinggang'
'zhangjingxuan',
'shujian',
'v.zhangkai',
'caojin'
]

qauser_list = [
'chenwang',
'fangruyi',
'zhuming'
]

qauser_list2 = [
'chenwang'
]

qauser_prog = [
'chenwang',
'zhuming',
'fangruyi',
'朱剑丘',
'lixj',
'wubin',
'zhanglinjian',
'李夏光',
'avalon',
'taoqun',
'zhangrui',
'zhaojun',
'caojin',
'刘泓源',
'lihuanyi',
'shanling'
]

qauser_client = [
'chenwang',
'caojin',
'zhuming',
'刘泓源'
]


import urllib
import datetime

def getTimeStr():
    return str(datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d %H:%M:%S'))

def send_msg_all(info):
    #send_msg_cw(info)
    for name in rtx_list.get_rtx_user_list():
        url = url_template_all % (getTimeStr(), info.encode('gbk'), name.encode('gbk'))
        print url
        urllib.urlopen(url).read()

def send_msg_qa(info):
    send_msg(info)

def send_msg(info):
    for name in qauser_client:
        print "=======", name
        url = url_template % (getTimeStr(), info.encode('gbk'), name)
        print url
        urllib.urlopen(url).read()

def send_msg_cw(info):
    url = url_template % (getTimeStr(), info.encode('gbk'), user_list)
    urllib.urlopen(url).read()

def send_msg_prog(info):
    for name in qauser_prog:
        url = url_template % (getTimeStr(), info.encode('gbk'), name)
        urllib.urlopen(url).read()

def send_msg_client(info):
    for name in qauser_client:
        url = url_template % (getTimeStr(), info.encode('gbk'), name)
        urllib.urlopen(url).read()

def send_msg_cj(info):
    url = url_template % (getTimeStr(), info.encode('gbk'), 'caojin')
    urllib.urlopen(url).read()
