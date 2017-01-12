#!/usr/bin/python

import sys,os,re
hash_ = {}
for line in sys.stdin:
	line = line.strip()
	arr = line.split(" ")
	for word in arr:
		#hash_[word] += 1
		#w = word.decode("gbk").encode("gbk")
		w = word
		if w not in hash_:
			hash_[w] = 1
		else:
			hash_[w] = hash_[w] + 1

for w,v in sorted(hash_.iteritems(), key = lambda asd:asd[1], reverse = True):
	print w,v
