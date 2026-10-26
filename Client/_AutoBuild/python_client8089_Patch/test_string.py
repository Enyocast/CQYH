__author__ = 'Administrator'

import dir_cfg
import datetime

def test(strIn):
    newStr = strIn
    newStr = newStr.replace('aodpatch', 'aodpatch\\_Stable')
    print strIn
    print newStr

#test(dir_cfg.shipping_bin_patch)
print str(datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d %H:%M:%S'))