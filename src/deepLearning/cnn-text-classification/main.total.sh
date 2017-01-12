#!/bin/bash

## (1) segment
## (2) preProcessing
cat data/video.query.delFilm.seg data/web.novideo.query.seg.2000w.shuffle | python bin/vocab.py > data/vocab.dat 
cat data/video.query.delFilm.seg | awk '{print "1	"$0}' > tmp/all.video
cat data/web.novideo.query.seg.2000w.shuffle | awk '{print "0	"$0}' >> tmp/all.video
python bin/random_.py tmp/all.video > x
mv x tmp/all.video
cat data/video.query.delFilm.seg data/web.novideo.query.seg.2000w.shuffle > tmp/total.seg
cat data/video.query.delFilm.seg | python bin/makeTrain.py > tmp/video.query.delFilm.seg.train
cat data/web.novideo.query.seg.2000w.shuffle | python bin/makeTrain.py > tmp/web.novideo.query.seg.train
## (3) w2v
rm -rf data/video.vectors.bin
time ./vec2/bin/word2vec -train tmp/total.seg -output data/video.vectors.bin -cbow 0 -size 100 -window 5 -negative 0 -hs 1 -sample 1e-3 -threads 12 -binary 0
## postProcessing 
cat data/video.vectors.bin | perl data/replaceSpace.pl > x
mv x data/video.vectors.bin
## (4) train
nohup python bin/traintest1.sam.py > log.txt &
