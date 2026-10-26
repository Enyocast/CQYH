#coding=gbk

url_template = r'http://172.30.61.44:8012/sendnotify.cgi?msg=%s&receiver=%s'


user_list = [
'chenwang'
]

import urllib
def send_msg(info):
    for name in user_list:
        url = url_template % (info, name)
        urllib.urlopen(url).read()

import sys

print "User:" + sys.argv[1] + " Changelist:" + sys.argv[2]
send_msg("User:" + sys.argv[1] + " Changelist:" + sys.argv[2])



