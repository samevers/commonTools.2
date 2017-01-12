#! /bin/bash
input=$1
echo $input
time ./bin/word2vec -train $input -output sam/vectors.bin -cbow 0 -size 200 -window 5 -negative 0 -hs 1 -sample 1e-3 -threads 12 -binary 1
./bin/w2v-distance sam/vectors.bin
