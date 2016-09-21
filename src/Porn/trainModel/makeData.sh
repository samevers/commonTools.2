#!/bin/sh

## Delete noise words
## Because there is too much "ͼƬ" keywords in training file.
cat data/porn.seg | perl postdo.pl > tmp/x
mv tmp/x tmp/porn.seg
cat data/common.seg | perl postdo.pl > tmp/x
mv tmp/x tmp/common.seg


for (( i = 1; i <= 20; i++ ))
do
	commonfile="common."$i".seg"
	python shuffle.py data/common.seg | awk '{print $0}'> tmp/$commonfile
done

for (( i = 1; i <= 20; i++ ))
do
	commonfile=tmp/"common."$i".seg"
	trainfile="train."$i".seg"
	cat $commonfile tmp/porn.seg > train/$trainfile
done
