#!/bin/sh

file=$1

#cat ${file} | python bin/segsam.py | python bin/wsplit.py | ./bin/w2v-distance vectors.bin > ${file}.extend
#cp ${file}.extend ./tmp_

#python bin/classify.extend.2vec.py ${file}.extend
#cp ${file}.extend.2vec.cla ./tmp_

######################## split vr into singe files.
echo "stage0 ......"
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/image/" > ${file}.extend.image`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/video/" > ${file}.extend.video`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/shop/" > ${file}.extend.shop`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/music/" > ${file}.extend.music`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/soft/" > ${file}.extend.soft`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/baike/" > ${file}.extend.baike`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/game/" > ${file}.extend.game`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/job/" > ${file}.extend.job`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/map/" > ${file}.extend.map`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/news/" > ${file}.extend.news`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/wenda/" > ${file}.extend.wenda`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/novel/" > ${file}.extend.novel`
`cat ${file}.extend.2vec.cla | awk "/outcome\]/" |  awk "/fangchan/" > ${file}.extend.fangchan`
echo "stage1 ......"

mv ${file}.extend.image out_/
mv ${file}.extend.video out_/
mv ${file}.extend.shop out_/
mv ${file}.extend.music out_/
mv ${file}.extend.soft out_/
mv ${file}.extend.baike out_/
mv ${file}.extend.game out_/
mv ${file}.extend.job out_/
mv ${file}.extend.map out_/
mv ${file}.extend.news out_/
mv ${file}.extend.wenda out_/
mv ${file}.extend.novel out_/
mv ${file}.extend.fangchan out_/

echo "stage2 ......"

################### diff with pre-version of VR. ################
#perl bin/baseline.gen.4comp.pl data_/10w.txt.out.new.1112 > data_/data_/10w.txt.out.new.1112.4comp
perl bin/diff.pl data_/10w.txt.out.new.1112.4comp tmp_/10w.txt.extend.2vec.cla
cat tmp_/add.out | python bin/filter.navi.py > tmp_/add.out.2
mv tmp_/add.out.2 tmp_/add.out
echo "stage3 ......"
#mv tmp_/add.out tmp_/10w.txt.out.new.1112.add
#mv tmp_/reduce.out tmp_/10w.txt.out.new.1112.reduce

`cat tmp_/add.out | awk "/outcome\]/" |  awk "/ video/" | awk -F" " '$5 !~/哪些|哪种|那种|那个|那些|怎么|怎样|如何|什么|多少|那里|剧照|下载|图|网站|网址|主页|网页|网>|官网|地址|攻略|照片|图片|图解|壁纸|剧照|海报|播放器|游戏|小说|软件|音乐|种子/'> ${file}.extend.video`
`cat tmp_/add.out | awk "/outcome\]/" |  awk "/ image/" | awk '$5 !~/怎么|下载|个人资料|哪|怎么|怎样|如何|多少|什么|啊|吗|呢|么|视频|网>|官网|网址|网站|网页|主页|地址|攻略|播放|攻略|电影|电视剧|视频|播放|高清|国语|学校|学院|大学|中学|小说|软件|音乐|游戏/'> ${file}.extend.image`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ shop/" | awk '$5 !~/怎么|下载|个人资料|视频|网>|官网|网址|网站|网页|主页|地址|攻略|播放|攻略|电影|电视剧|视频|播放|高清|国语|学校|学院|大学|中学|小说|软件|音乐|游戏/'> ${file}.extend.shop`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ music/" | awk '$5 !~/怎么|个人资料|怎么|怎样|如何|多少|什么|视频|网>|官网|网址|网站|网页|主页|地址|攻略|攻略|视频|高清|国语|学校|学院|大学|中学|小说|软件|游戏/'> ${file}.extend.music`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ soft/" | awk '$5 !~/个人资料|怎样|如何|多少|什么|视频|网>|官网|网址|网站|网页|主页|地址|攻略|播放|攻略|电影|电视剧|视频|播放|高清|国语|学校|学院|大学|中学|小说|音乐|游戏/'> ${file}.extend.soft`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ baike/" > ${file}.extend.baike`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ game/" | awk '$5 !~/个人资料|视频|网>|官网|网址|网站|网页|主页|播放|攻略|电影|电视剧|视频|播放|高清|国语|学校|学院|大学|中学|小说|软件|音乐/'> ${file}.extend.game`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ job/" > ${file}.extend.job`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ map/" > ${file}.extend.map`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ news/" | awk '$5 !~/怎么|下载|个人资料|怎么|怎样|如何|多少|网>|官网|网址|网站|网页|主页|地址|攻略|播放|攻略|电影|电视剧|视频|播放|高清|国语|小说|软件|音乐|游戏/'> ${file}.extend.news`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ wenda/" > ${file}.extend.wenda`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ novel/" | awk '$5 !~/个人资料|视频|网>|官网|网址|网站|网页|主页|地址|攻略|播放|攻略|电影|电视剧|视频|播放|高清|国语|学校|学院|大学|中学|软件|音乐|游戏/'> ${file}.extend.novel`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ fangchan/" > ${file}.extend.fangchan`


echo "stage4 ......"
mv ${file}.extend.image out_/comp2vrqo
mv ${file}.extend.video out_/comp2vrqo
mv ${file}.extend.shop out_/comp2vrqo
mv ${file}.extend.music out_/comp2vrqo
mv ${file}.extend.soft out_/comp2vrqo
mv ${file}.extend.baike out_/comp2vrqo
mv ${file}.extend.game out_/comp2vrqo
mv ${file}.extend.job out_/comp2vrqo
mv ${file}.extend.map out_/comp2vrqo
mv ${file}.extend.news out_/comp2vrqo
mv ${file}.extend.wenda out_/comp2vrqo
mv ${file}.extend.novel out_/comp2vrqo
mv ${file}.extend.fangchan out_/comp2vrqo

################## diff with qc model baseline ################
#perl bin/baseline.gen.4comp.pl data_/10w.txt.model.baseline > data_/10w.txt.model.baseline.4comp
perl bin/diff.pl data_/10w.txt.model.baseline.4comp tmp_/10w.txt.extend.2vec.cla
#mv tmp_/add.out tmp_/10w.txt.model.baseline.add
#mv tmp_/reduce.out tmp_/10w.txt.model.baseline.reduce
echo "stage5 ......"

`cat tmp_/add.out | awk "/outcome\]/" |  awk "/ image/" > ${file}.extend.image`
`cat tmp_/add.out | awk "/outcome\]/" |  awk "/ video/" > ${file}.extend.video`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ shop/" > ${file}.extend.shop`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ music/" > ${file}.extend.music`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ soft/" > ${file}.extend.soft`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ baike/" > ${file}.extend.baike`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ game/" > ${file}.extend.game`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ job/" > ${file}.extend.job`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ map/" > ${file}.extend.map`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ news/" > ${file}.extend.news`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ wenda/" > ${file}.extend.wenda`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ novel/" > ${file}.extend.novel`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ fangchan/" > ${file}.extend.fangchan`

mv ${file}.extend.image out_/comp2modelBaseline
mv ${file}.extend.video out_/comp2modelBaseline
mv ${file}.extend.shop out_/comp2modelBaseline
mv ${file}.extend.music out_/comp2modelBaseline
mv ${file}.extend.soft out_/comp2modelBaseline
mv ${file}.extend.baike out_/comp2modelBaseline
mv ${file}.extend.game out_/comp2modelBaseline
mv ${file}.extend.job out_/comp2modelBaseline
mv ${file}.extend.map out_/comp2modelBaseline
mv ${file}.extend.news out_/comp2modelBaseline
mv ${file}.extend.wenda out_/comp2modelBaseline
mv ${file}.extend.novel out_/comp2modelBaseline
mv ${file}.extend.fangchan out_/comp2modelBaseline


echo "stage6 ......"
