#! /usr/bin/python 
#encoding:gb18030
############################################
#
# Author: lichao
# Create time: 2014  9�� 12 16ʱ05��59��
# E-Mail: lichaotx020@sogou-inc.com
# version 1.0
#
############################################

import sys,os
from optparse import OptionParser
import jieba
import gl

for line in sys.stdin:
	line = line.strip()
	try:
		line = gl.strQ2B(line.decode("gb18030")).encode("gb18030")
	except:
		line = line
	segment = " ".join(jieba.cut(line))
	try:
		print segment.encode('gb18030')
	except:
		print segment.encode('utf8')
