#!/usr/bin/python

import sys,os,re

hash_v = {}
fin =open("data/vocab.dat", 'r')
tag = 1
for line in fin.readlines():
	line = line.strip()
	arr = line.split(" ")
	hash_v[arr[0]]= tag
	tag += 1

fin.close()

for line in sys.stdin:
	line = line.strip()
	arr = line.split(" ")
	for w in arr:
		if w in hash_v:
			sys.stdout.write("%s " % hash_v[w])
	sys.stdout.write("\n")
