#coding=utf-8
import re
import os

def get_rtx_user_list():
    user_lst = []
    pattern = re.compile(u'UserName=\"\S*\"')
    #pattern = re.compile(u'UserName=\"[\u4e00-\u9fff]+\"')
    fp = open(u'rtx_user.xml', u'r')
    for lineStr in fp:
        #print type(lineStr)
        unicodeStr = unicode(lineStr.decode(u'gbk'))
        match = pattern.search(unicodeStr)
        if match:
            userName = unicode(unicodeStr[match.start(0) + len(u'UserName=\"'):match.end(0) - 1])
            #print userName, type(userName)# .decode(u'utf-8').encode(u'gbk')
            #print type(userName)
            user_lst.append(userName)
    fp.close()
    return user_lst

#lst = get_rtx_user_list()
#for nm in lst:
#    print nm #.decode(u'utf-8').encode(u'gbk')