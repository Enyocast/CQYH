#coding=utf8
__author__ = 'Administrator'

import os
ver_file = 'mmo_ver.txt'

def read_vers():
    vers = []

    if not os.path.isfile(ver_file):
        return vers

    fp = open(ver_file, u'r')

    for lineStr in fp:
        #print lineStr
        vers.append(lineStr[0:len(lineStr) - 1])
    return vers

def add_ver(verStr):
    #print u'====== Add new versin:', verStr
    fp = open(ver_file, u'a+')
    fp.write(verStr + u'\n')
    fp.flush()
    fp.close()

#if __name__ == '__main__':
    #r = [0, 1, 2, 3, 4, 5]
    #for i in r:
        #print i
    #    add_ver((u'%u.%u.%u.%u' % (i, i + 2, i + 3, i + 4 )))

    #print read_vers()