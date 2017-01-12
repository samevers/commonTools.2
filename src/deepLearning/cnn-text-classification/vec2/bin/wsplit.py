#!/usr/bin/python

import sys,os,re
import gl
for line in sys.stdin:
	line = line.strip()
	line = line.replace("\t", " ")
	arr = line.split(" ")
	for w in arr:
		try:
			w = gl.strQ2B(w.decode("gb18030")).encode("gb18030")
		except:
			v = 1
		if w.isdigit():
			continue
		sys.stdout.write("%s\n" % w)
	line = line.replace(" ","")
	sys.stdout.write("===\n")
