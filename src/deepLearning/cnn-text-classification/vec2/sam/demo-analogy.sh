#!/bin/bash

make
if [ ! -e text8 ];
then
	wget http://mattmahoney.net/dc/text8.zip -O text8.gz
	gzip -d text8.gz -f
fi
echo -----------------------------------------------------------------------------------------------------
echo Note that for the word analogy to perform well, the models should be trained on much larger data sets
echo Example input: paris france berlin
echo -----------------------------------------------------------------------------------------------------
time ./bin/word2vec -train text8 -output vectors.bin -cbow 0 -size 200 -window 5 -negative 0 -hs 1 -sample 1e-3 -threads 12 -binary 1
./w2v-word-analogy vectors.bin
