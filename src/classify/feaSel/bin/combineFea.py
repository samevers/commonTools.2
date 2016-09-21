#!/usr/bin/python
#coding=gbk
import sys
#sys.setdefaultencoding("gbk")
hashFea = {}
for i in range(1,21):
	filename = "out/output." + str(i)
	fin = open(filename, 'r')
	for line in fin.readlines():
		line = line.strip()
		arr = line.split("\t")
		term = arr[0]
		weight = arr[2]
		if len(term) > 20:
			continue
		if term not in hashFea:
			try:
				hashFea[term] = float(weight)
			except:
				continue
		else:
			hashFea[term] += float(weight)
hash_tmp = sorted(hashFea.items(), key = lambda asd:asd[1], reverse=True)
for k,v in hash_tmp:
	print k,v
