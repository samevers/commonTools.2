#!/bin/bash
echo "Begin to train processing ........"
cd /search/huyonghua/InterVRWordList/data/_in/model/vslog/
cat querylog.image | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/image.cor
cat querylog.video | awk -F"\t" '{print $1}'  > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/video.cor
cat querylog.shop | awk -F"\t" '{print $1}'  > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/shop.cor
cat querylog.shop.dianzi | awk -F"\t" '{print $1}'  >> /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/shop.cor
cat querylog.shop.fushi | awk -F"\t" '{print $1}'  >> /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/shop.cor
cat querylog.music | awk -F"\t" '{print $1}'  > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/music.cor
cat querylog.job  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/job.cor
cat querylog.game  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/game.cor
cat querylog.fangchan  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/fangchan.cor
cat querylog.map  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/map.cor
cat querylog.software  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/soft.cor
cat querylog.sucai  | awk -F"\t" '{print $1}' >> /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/image.cor
cat querylog.wenda  | awk -F"\t" '{print $1}' > /search/huyonghua/tools/jiebademo-master/jiebademo/outSeg2/tag/vec2/data_/train_cor/wenda.cor
