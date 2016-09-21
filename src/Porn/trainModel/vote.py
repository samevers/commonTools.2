#!/usr/bin/python

import sys,os,re
import os.path

dir=sys.argv[1]
voteWeb = {}
votePorn = {}
voteOut = {}
content = {}
rex = re.compile(r'^(.*?)MAX_CLASS:(.*?) (.*)$')
rexconfidence = re.compile(r'^(.*?)confidence:(.*?) (.*)$')
rexporn = re.compile(r'^porn:(.*?) (.*)$')
for parent, dirnames, filenames in os.walk(dir):
	for f in filenames:
		f = "out/" + f
		fin = open(f, 'r')
		num = 1
		for line in fin.readlines():
			line = line.strip()
			# query
			loc = line.find("||")
			query = ""
			if loc > -1:
				query = line[loc:]
			if num not in content:
				content[num] = query
			else:
				if query != content[num]:
					sys.stderr.write("ERROR: query is not equal in line: %d" % num)
					exit()
			confidence = 0
			m = rexconfidence.match(line)
			if m:
				confidence = m.group(2)
			porn = 0
			mporn = rexporn.match(line)
			if mporn:
				porn = float(mporn.group(1))
			if m and mporn:
				#and porn > 0:
				if num in voteOut:
					voteOut[num] += float(confidence)
				else:
					voteOut[num] = float(confidence)
			num += 1
fin.close()


fout = open("test.dat.seg.ter", 'w')
for n,v in voteOut.items():
	if v < 0:
		fout.write("%d\t%f\t%s\n" % (n,voteOut[n],content[n]))
fout.close()
