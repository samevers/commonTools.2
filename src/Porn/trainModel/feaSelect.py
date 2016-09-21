#!/usr/bin/python
import sys,os,re

hashFea = {}
fin = open("features/features.txt", 'r')
for line in fin.readlines():
	line = line.strip()
	arr = line.split(" ")
	term = arr[0]
	hashFea[term]= 1
fin.close()

modelfile= sys.argv[1]
modelfin = open(modelfile, 'r')
for line in modelfin.readlines():
	line = line.strip()
	if line.find("##class##") != -1:
		print line
	else:
		arr = line.split(" ")
		term = arr[0]
		if term in hashFea:
			print line

modelfin.close()
