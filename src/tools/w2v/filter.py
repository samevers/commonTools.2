#! /usr/bin/python 
#encoding:gb18030
############################################
#
# Author: lichao
# Create time: 2014 11月 30 00时03分26秒
# E-Mail: lichaotx020@sogou-inc.com
# version 1.0
#
############################################

import sys,os,re
from optparse import OptionParser
import gl

rex=re.compile(r'(^[a-zA-Z0-9]+$)')
for line in sys.stdin:
	line = line.strip()
	arr = line.split("\t")
	line = ""
	# 去掉单字
	if len(arr[0]) < 3:
		continue

	# 去掉单字扩展词
	for w in arr:
		loc = w.find(":")
		if loc > -1:
			ext = w[:loc]
			if len(ext) > 2:
				line = line + w + "\t"
			else:
				v = 1
		else:
			line = line + w + "\t"


	query = gl.strQ2B(arr[0].decode("gb18030")).encode("gb18030")
	# 字母的留下
	if query.isalpha():
		sys.stdout.write("%s\n" % line)
		continue
	# 去掉数字和字母组合
	if rex.match(query):
		continue;
	else:
		sys.stdout.write("%s\n" % line)

