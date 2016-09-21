#!/bin/sh

pornfile="testdata/porn.seg"

## CHI
for (( i = 1; i <= 20; i++ ))
do
	commonfile="testdata/common."$i".seg"
	output="out/output."$i
	rm -rf tmp/*
	cp $commonfile $pornfile tmp/
	./feaChi tmp/ $output
done

python bin/combineFea.py > featuresCHI.txt

