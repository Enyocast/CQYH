#coding=utf8
__author__ = 'Administrator'

import os
ver_file = 'fix_url_list.txt'

def read_list():
    vers = []

    if not os.path.isfile(ver_file):
        return vers

    fp = open(ver_file, u'r')

    for lineStr in fp:
        #print lineStr
        vers.append(lineStr[0:len(lineStr) - 1])
    return vers

def add_to_list(urlStr):
    #print u'====== Add new versin:', verStr
    fp = open(ver_file, u'a+')
    fp.write(urlStr + u'\n')
    fp.flush()
    fp.close()