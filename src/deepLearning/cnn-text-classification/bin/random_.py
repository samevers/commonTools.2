#!/usr/bin/python


import sys

import numpy as np

SEED = 123
#np.random.seed(SEED)

corpus = []
filename=sys.argv[1]
FIN = open(filename, 'r')
for line in FIN.readlines():
	line = line.strip()
	corpus.append(line)
FIN.close()
idx= np.arange(len(corpus))
np.random.shuffle(idx)
idx = idx[:20000000]
data = (corpus[n] for n in idx)

for q in data:
	sys.stdout.write("%s\n" % q)
