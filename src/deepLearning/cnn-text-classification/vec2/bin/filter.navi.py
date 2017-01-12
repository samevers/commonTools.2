#!/usr/bin/python

import sys,os,re

hash_navi = {}
FILEnavi = file("./data_/navigate_query.list", 'r')
for line in FILEnavi.readlines():
	line = line.strip()
	hash_navi[line] = 1
FILEnavi.close()
#######################
for line in sys.stdin:
	line = line.strip()
	arr = line.split(" ")
	if line.find("terminal outcome") == -1:
		continue
	query = arr[4]
	query = query[1:-2]
	
	if query not in hash_navi:
		sys.stdout.write("%s\n" % line)
