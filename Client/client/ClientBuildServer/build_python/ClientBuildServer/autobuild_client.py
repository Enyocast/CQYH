#!/usr/bin/env python
#coding: utf-8

import sys, os, re
import urllib
import time

build_url = 'http://172.30.68.97:8089/?action=compile_client'

def geturl(url):
    return urllib.urlopen(url).read()


geturl(build_url)
