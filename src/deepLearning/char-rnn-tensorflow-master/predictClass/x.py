#! /usr/bin/python 
#encoding:gb18030
############################################
#
# Author: 
# E-Mail:@sogou-inc.com
# Create time: 2016 12�� 21 17ʱ31��27��
# version 1.0
#
############################################


import sys,os,re

for line in sys.stdin:
  line = line.strip()
  if line.find("\u") != -1:
    line = line[1:]
    print line.encode("gbk")
