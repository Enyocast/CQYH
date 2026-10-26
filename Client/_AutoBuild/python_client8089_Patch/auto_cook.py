#!/usr/bin/env python
#coding: utf-8
import urllib

url = u'http://172.30.66.33:8089/?action=auto_cook'
urllib.urlopen(url).read()