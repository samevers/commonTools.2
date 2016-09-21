#!/bin/sh

pornfile="testdata/porn.seg"
## IG
for (( i = 1; i <= 20; i++ ))
do
	commonfile="testdata/common."$i".seg"
	output="out/output."$i
	rm -rf tmp/*
	cp $commonfile $pornfile tmp/
	./feaIg tmp/ $output
done

python bin/combineFea.ig.py > featuresIG.txt
