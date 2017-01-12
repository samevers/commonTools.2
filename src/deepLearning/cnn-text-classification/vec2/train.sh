#!/bin/bash
echo "Begin to train processing ........"
#cd /search/huyonghua/InterVRWordList/data/_in/model/vslog/
#cat querylog.image | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/image.cor
#cat querylog.video | awk -F"\t" '{print $1}'  > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/video.cor
#cat querylog.shop | awk -F"\t" '{print $1}'  > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/shop.cor
#cat querylog.shop.dianzi | awk -F"\t" '{print $1}'  >> /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/shop.cor
#cat querylog.shop.fushi | awk -F"\t" '{print $1}'  >> /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/shop.cor
#cat querylog.music | awk -F"\t" '{print $1}'  > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/music.cor
#cat querylog.job  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/job.cor
#cat querylog.game  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/game.cor
#cat querylog.fangchan  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/fangchan.cor
#cat querylog.map  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/map.cor
#cat querylog.software  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/soft.cor
#cat querylog.sucai  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/image.cor
#cat querylog.wenda  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/wenda.cor

#echo "complete train corpus from vslog directory to vec2 dir .........."

# accuquery copy
#echo "Begin to combine train corpus with accurate query ..............."
#hadoop fs -get /user/web_nlp/yonghuahu/vs_baidu_360/* ./accuquery_filter
#path=accuquery_filter/video.accuquery.filter
#if [ -d $path ]; then
#	linecount=`wc -l ${date}/video.accuquery.filter | awk '{print $1}'`
#	if [[ ${linecount} -gt 10000 ]];then
#		cp ${date}/video.accuquery.filter ./
#		cat video.accuquery.filter >> /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/video.cor
#	fi
#fi
#path=accuquery_filter/image.accuquery.filter
#if [ -d $path ]; then
#	linecount=`wc -l ${date}/image.accuquery.filter | awk '{print $1}'`
#	if [[ ${linecount} -gt 10000 ]];then
#		cp ${date}/image.accuquery.filter ./
#		cat image.accuquery.filter >> /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/image.cor
#	fi
#fi
#
#path=accuquery_filter/shop.accuquery.filter
#if [ -d $path ]; then
#	linecount=`wc -l ${date}/shop.accuquery.filter | awk '{print $1}'`
#	if [[ ${linecount} -gt 10000 ]];then
#		cp ${date}/shop.accuquery.filter ./
#		cat shop.accuquery.filter >> /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/shop.cor
#	fi
#fi
#
#path=accuquery_filter/music.accuquery.filter
#if [ -d $path ]; then
#	linecount=`wc -l ${date}/music.accuquery.filter | awk '{print $1}'`
#	if [[ ${linecount} -gt 10000 ]];then
#		cp ${date}/music.accuquery.filter ./
#		cat music.accuquery.filter >> /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/music.cor
#	fi
#fi
#
#path=accuquery_filter/baike.accuquery.filter
#if [ -d $path ]; then
#	linecount=`wc -l ${date}/baike.accuquery.filter | awk '{print $1}'`
#	if [[ ${linecount} -gt 10000 ]];then
#		cp ${date}/baike.accuquery.filter ./
#		cat baike.accuquery.filter > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/baike.cor
#	fi
#fi
#
#path=accuquery_filter/game.accuquery.filter
#if [ -d $path ]; then
#	linecount=`wc -l ${date}/game.accuquery.filter | awk '{print $1}'`
#	if [[ ${linecount} -gt 10000 ]];then
#		cp ${date}/game.accuquery.filter ./
#		cat game.accuquery.filter >> /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/game.cor
#	fi
#fi
#
#path=accuquery_filter/news.accuquery.filter
#if [ -d $path ]; then
#	linecount=`wc -l ${date}/news.accuquery.filter | awk '{print $1}'`
#	if [[ ${linecount} -gt 10000 ]];then
#		cp ${date}/news.accuquery.filter ./
#		cat ${date}/news.accuquery.filter > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/news.cor
#	fi
#fi
#
#path=accuquery_filter/novel.accuquery.filter
#if [ -d $path ]; then
#	linecount=`wc -l ${date}/novel.accuquery.filter | awk '{print $1}'`
#	if [[ ${linecount} -gt 10000 ]];then
#		cp ${date}/novel.accuquery.filter ./
#		cat ${date}/novel.accuquery.filter > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/novel.cor
#	fi
#fi
#path=accuquery_filter/soft.accuquery.filter
#if [ -d $path ]; then
#	linecount=`wc -l ${date}/soft.accuquery.filter | awk '{print $1}'`
#	if [[ ${linecount} -gt 10000 ]];then
#		cp ${date}/soft.accuquery.filter ./
#		cat ${date}/soft.accuquery.filter >>/search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/soft.cor
#	fi
#fi



## segment
echo "Begin to segment and code-post ..............................."
cd /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/

cat data_/train_cor/image.cor | sh segment.sh | awk -F"\t" '{print $2}' > data_/train_cor/image.cor.seg
cat data_/train_cor/video.cor | sh segment.sh | awk -F"\t" '{print $2}' > data_/train_cor/video.cor.seg
cat data_/train_cor/shop.cor | sh segment.sh  | awk -F"\t" '{print $2}'> data_/train_cor/shop.cor.seg
cat data_/train_cor/music.cor | sh segment.sh  | awk -F"\t" '{print $2}'> data_/train_cor/music.cor.seg
cat data_/train_cor/baike.cor | sh segment.sh | awk -F"\t" '{print $2}'> data_/train_cor/baike.cor.seg
cat data_/train_cor/wenda.cor | sh segment.sh | awk -F"\t" '{print $2}'> data_/train_cor/wenda.cor.seg
cat data_/train_cor/game.cor | sh segment.sh | awk -F"\t" '{print $2}'> data_/train_cor/game.cor.seg
cat data_/train_cor/map.cor | sh segment.sh  | awk -F"\t" '{print $2}'> data_/train_cor/map.cor.seg
cat data_/train_cor/job.cor | sh segment.sh  | awk -F"\t" '{print $2}'> data_/train_cor/job.cor.seg
cat data_/train_cor/novel.cor | sh segment.sh | awk -F"\t" '{print $2}'> data_/train_cor/novel.cor.seg
cat data_/train_cor/news.cor | sh segment.sh | awk -F"\t" '{print $2}'> data_/train_cor/news.cor.seg
cat data_/train_cor/soft.cor | sh segment.sh | awk -F"\t" '{print $2}' > data_/train_cor/soft.cor.seg
cat data_/train_cor/fangchan.cor | sh segment.sh | awk -F"\t" '{print $2}'> data_/train_cor/fangchan.cor.seg

#cat data_/train_cor/image.cor | sh segment.sh |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}' > data_/train_cor/image.cor.seg
#cat data_/train_cor/video.cor | sh segment.sh  |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}' > data_/train_cor/video.cor.seg
#cat data_/train_cor/shop.cor | sh segment.sh   |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}'> data_/train_cor/shop.cor.seg
#cat data_/train_cor/music.cor | sh segment.sh  |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}'> data_/train_cor/music.cor.seg
#cat data_/train_cor/baike.cor | sh segment.sh |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}' > data_/train_cor/baike.cor.seg
#cat data_/train_cor/wenda.cor | sh segment.sh |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}' > data_/train_cor/wenda.cor.seg
#cat data_/train_cor/game.cor | sh segment.sh |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}' > data_/train_cor/game.cor.seg
#cat data_/train_cor/map.cor | sh segment.sh |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}' > data_/train_cor/map.cor.seg
#cat data_/train_cor/job.cor | sh segment.sh  |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}' > data_/train_cor/job.cor.seg
#cat data_/train_cor/novel.cor | sh segment.sh |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}' > data_/train_cor/novel.cor.seg
#cat data_/train_cor/news.cor | sh segment.sh |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}' > data_/train_cor/news.cor.seg
#cat data_/train_cor/soft.cor | sh segment.sh |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}' > data_/train_cor/soft.cor.seg
#cat data_/train_cor/fangchan.cor | sh segment.sh |awk -F"\t" '{if($1!=$2){print $1" "$2}else{print $2}}' > data_/train_cor/fangchan.cor.seg


## combine all the corpus
echo "Begin to merge all the segment train corpus to train.all file .............."
cat data_/train_cor/*.cor.seg > data_/train_cor/train.all 

## make tag
echo "Begin to make vr tags ........................"
cat data_/train_cor/image.cor.seg | awk '{print "image "$0}' > data_/train_cor/image.cor.seg.tag
cat data_/train_cor/video.cor.seg | awk '{print "video "$0}' > data_/train_cor/video.cor.seg.tag
cat data_/train_cor/shop.cor.seg | awk '{print "shop "$0}' > data_/train_cor/shop.cor.seg.tag
cat data_/train_cor/music.cor.seg | awk '{print "music "$0}' > data_/train_cor/music.cor.seg.tag
cat data_/train_cor/baike.cor.seg | awk '{print "baike "$0}' > data_/train_cor/baike.cor.seg.tag
cat data_/train_cor/wenda.cor.seg | awk '{print "wenda "$0}' > data_/train_cor/wenda.cor.seg.tag
cat data_/train_cor/game.cor.seg | awk '{print "game "$0}' > data_/train_cor/game.cor.seg.tag
cat data_/train_cor/map.cor.seg | awk '{print "map "$0}' > data_/train_cor/map.cor.seg.tag
cat data_/train_cor/job.cor.seg | awk '{print "job "$0}' > data_/train_cor/job.cor.seg.tag
cat data_/train_cor/novel.cor.seg | awk '{print "novel "$0}' > data_/train_cor/novel.cor.seg.tag
cat data_/train_cor/news.cor.seg | awk '{print "news "$0}' > data_/train_cor/news.cor.seg.tag
cat data_/train_cor/soft.cor.seg | awk '{print "soft "$0}' > data_/train_cor/soft.cor.seg.tag
cat data_/train_cor/fangchan.cor.seg | awk '{print "fangchan "$0}' > data_/train_cor/fangcha.cor.seg.tag
### train word weight on vr
echo "Begin to train word weight on vr corpus ................"
#cat data_/train_cor/*.cor.seg.tag | perl bin/train_word.204Corpus.pl >> log.txt

## train word to vectors
echo "Begin to train vectors.bin file ......................."
sh demo-word.sh

## generate word dic
echo "Begin to generate word dictionary......................"
#cat data_/train_cor/train.all | perl bin/gen-word.pl > data_/train_cor/word.dic

echo "END."
## generate word extend bin file.
##cat data_/train_cor/word.dic | ./bin/w2v-distance > model/word.weight.bin
