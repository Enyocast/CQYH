#coding=gbk

url_template = r'http://172.30.61.44:8012/sendnotify.cgi?msg=%s&receiver=%s'


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
'zhaozhenyang'
]

import urllib
def send_msg(info):
    for name in user_list:
        url = url_template % (info, name)
        urllib.urlopen(url).read()
