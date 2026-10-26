#coding=gbk

url_template = r'http://172.30.68.104:8012/sendnotify.cgi?title=AutoBuild&msg=%s&receiver=%s'

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
	'zhangyuntian',
	'yaochanghai',
	'gaohuaxiang.watson',
	'jinyuanfei',
	'luchenlei',
	'avalon',
	'caixuhui',
	'zhaomeng01',
	'zhuqin',
	'xingbing',
	'zhaozhenyang',
	'yulefeng',
	'jinyinggang',
	'zhangjingxuan',
	'shujian',
	'梅显忠',	
	'ZHANGMIAO'
]   

compile_user_list = [
	'lixj',
	'李夏光',
	'wubin',
	'朱剑丘',
	'ZHANGMIAO',
	'梅显忠',
	'刘泓源'
]   

import urllib
def send_msg(info):
    for name in user_list:
        url = url_template % (info, name)
        urllib.urlopen(url).read()

def send_compile_msg(info):
    for name in compile_user_list:
        url = url_template % (info, name)
        urllib.urlopen(url).read()

		
