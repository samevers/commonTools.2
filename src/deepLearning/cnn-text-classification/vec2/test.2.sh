#!/bin/sh

#file=$1
#echo ${file} | python bin/segsam.py | python bin/wsplit.py | ./bin/w2v-distance vectors.vslog.bin > x 
#cat ../prove-vec/data/word.dic | ./bin/w2v-distance vectors.vslog.bin > data_/vectors.words.bin.2
#cat ${file} | python bin/segsam.py | python bin/wsplit.py | ./bin/w2v-distance vectors.vslog.bin > x 
#python bin/classify.extend.2vec.py x
#cat ../x.2vec.cla 
#cat data_/train_cor/train.all | python bin/gen-word.py > data_/train_cor/word.dic
cat data_/train_cor/word.dic | ./bin/w2v-distance > model/word.weight.bin
