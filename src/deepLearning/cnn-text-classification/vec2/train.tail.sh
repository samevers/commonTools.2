#!/bin/bash



## train word weight on vr
#echo "Begin to train word weight on vr corpus ................"
#cat data_/train_cor/*.cor.seg.tag | perl bin/train_word.204Corpus.pl 

## train word to vectors
echo "Begin to train vectors.bin file ......................."
sh demo-word.sh

## generate word dic
echo "Begin to generate word dictionary......................"
cat data_/train_cor/train.all | perl bin/gen-word.pl > data_/train_cor/word.dic

echo "END."
## generate word extend bin file.
##cat data_/train_cor/word.dic | ./bin/w2v-distance > model/word.weight.bin
