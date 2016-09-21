#!/usr/bin/python

import sys,os,re
import numpy as np


corpus = []
FIN = open(sys.argv[1], 'r')
for line in FIN.readlines():
	line = line.strip()
	corpus.append(line)

FIN.close()
idx = np.arange(len(corpus))
np.random.shuffle(idx)
idx=idx[:300000]
data = (corpus[n] for n in idx)
for q in data:
	print q
