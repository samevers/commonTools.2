#!/usr/bin/python


import sys,os,re
import jieba
import gl
## a given threshold value
threshold = 0.0
#WORDWEIGHTFILE = file("model/model.word.out.w_vr",'r')
WORDWEIGHTFILE = file("model/model.word.out",'r')
EXTENDFILE = file("./data_/vectors_bin/vectors.bin.model.post", 'r')
'''                     
NOTE: weight of extending word is different.
        The word itself weights 1.0;
        The word +1&-1 weights 0.8;
        The word +2&-2 weights 0.6;
        The word +3&-3 weights 0.4;
'''                     
                        
# Neighbor Word weight value;   
w0 = 1
w1 = 0.8       
w2 = 0.6       
w3 = 0.4

print "Begin to load word weight file ................"
hash_wordweight = {}
hash_extend = {}
num = 0
hash_vr = {}
for line in WORDWEIGHTFILE.readlines():
	line = line.strip()
	arr = line.split("\t")
	word = arr[0]
	vr = arr[1]
	weight = arr[4]
	word_vr = word + " " + vr
	hash_wordweight[word_vr] = weight
	hash_vr[vr] = 1
	num = num + 1
	if num % 2000 == 0:
		print ".",
WORDWEIGHTFILE.close()
print "\nWord weight file loaded .................. OK !"

print "Begin to load extend file ..... \n";
for line in EXTENDFILE.readlines():
	line = line.strip()
	arr = line.split("\t")
	word = arr[0]
	if len(word) < 3 or word.isdigit() or word.isalpha():
		continue
	loc = line.find("\t")
	line = line[loc+1:]
	hash_extend[word] = line;
EXTENDFILE.close()

print "\n\nNow begin to process the input ..................."

num = 0
inputname = sys.argv[1]
inputfile = file(inputname,'r')
if inputname.find("/") == -1:
	outputname = "../" + inputname + ".extend.2vec.cla"
else:
	loc = inputname.index("/")
	outputname = inputname[loc + 1:]
	outputname = "../" + outputname + ".extend.2vec.cla"
	print outputname
outputfile = file(outputname, 'w')
line = ""
for line_ in inputfile.readlines():
	num = num + 1
	if num % 2000 == 0:
		print ".",
	line_ = line_.strip()
	if line == "":
		line = line_;
	else:
		line = line + "\t" + line_
	arr_2 = line_.split("\t")
	#for i in range(0,len(arr_2)):
	for chunk in arr_2:
		#chunk = arr_2[i]
		loc = chunk.find(":")
		ww = chunk[loc+1:]
		if ww in hash_extend:
			line = line + "\t" + hash_extend[ww]
	if line_ == "===":
		ok = 1
	else:
		continue
	print line
	line.replace("\t\t","\t")
	arr_2 = line.split("\t")
	oriline = arr_2[0] ## new add
	hash_vr_weight = {}
	hash_vr_num = {}
	# test
	hash_vr_extend = {}
	for vr in hash_vr:
		#oriline = ""
		extend = ""
		weight_vr = 0.0
		num_vr = 0
		for i in range(0,len(arr_2)):
			w = arr_2[i]
			loc = w.find(":")
			if loc  == -1:
				#oriline = oriline + w + " "
				ex_prob = "1";
			else:
				ex_prob = w[loc+1:]
				w = w[0:loc]
			if len(w) < 3:
				continue
			if w.isdigit():
				continue
			word_vr = w + " " + vr
			if word_vr in hash_wordweight:
				num_vr = num_vr + 1
				if ex_prob.find(":") != -1:
					continue
#				print weight_vr,hash_wordweight[word_vr],ex_prob
				try:
					weight_vr = weight_vr + float(hash_wordweight[word_vr])*float(ex_prob)
				except:
					weight_vr = weight_vr
		avg = 0.0
		if num_vr > 0:
			hash_vr_num[vr] = num_vr
			avg = float(weight_vr)/float(num_vr)
			hash_vr_weight[vr] = float(weight_vr)/float(num_vr)
		outputfile.write("extend outcome on <%s> : %s\t%.15f\t%d\t%.15f\n" % (oriline,vr,weight_vr,num_vr,avg))
		#oriline = ""
	## output classify outcome
	hash_tmp = sorted(hash_vr_weight.iteritems(), key=lambda hash_vr_weight:hash_vr_weight[1], reverse=True)
	flag = 0
	weight1 = 0
	weight2 = 0
	top = 2
	vr1 = ""
	vr2 = ""
	for vr,weight in hash_tmp:
		## outputfile.write("extend outcome on <%s> : \t%s\t%.10f------------\n" % (vr,hash_vr_extend[vr], weight))
		#outputfile.write("cadidate : %s %f\n" % (vr,weight))
		if top == 2:
			#if hash_vr_num[vr] > 0:
			vr1 = vr
			weight1 = weight#/hash_vr_num[vr]
			#else:
			#	weight1 = 0
			top = top - 1
			continue
		elif top ==1:
			#if hash_vr_num[vr] > 0:
			vr2 = vr
			weight2 = weight#/hash_vr_num[vr]
			#else:
			#	weight2 = 0
		else:
			break
		top = top -1
		if weight1 == 0 and weight2 == 0:
			break
		if weight1 < threshold:
			break;
		if weight2/weight1 <= 0.6: # and weight1 > threshold:
			outputfile.write("[terminal outcome] <%s>: %s %f %f	%f\n" % (oriline,vr1, weight1, weight2,weight1))
			flag = 1
		if weight2/weight1 > 0.6:
			outputfile.write("[terminal outcome] <%s>: %s	%s %f %f	%f\n" % (oriline,vr1, vr2, weight1, weight2,weight1))
			flag = 1
		if flag == 1:
			break
	if flag == 0:
		outputfile.write("[none outcome] : none %s\n" % oriline)
	line = ""
inputfile.close()
outputfile.close()
