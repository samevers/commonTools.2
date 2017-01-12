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

`cat tmp_/add.out | awk "/outcome\]/" |  awk "/ video/" | awk -F" " '$5 !~/��Щ|����|����|�Ǹ�|��Щ|��ô|����|���|ʲô|����|����|����|����|ͼ|��վ|��ַ|��ҳ|��ҳ|��>|����|��ַ|����|��Ƭ|ͼƬ|ͼ��|��ֽ|����|����|������|��Ϸ|С˵|���|����|����/'> ${file}.extend.video`
`cat tmp_/add.out | awk "/outcome\]/" |  awk "/ image/" | awk '$5 !~/��ô|����|��������|��|��ô|����|���|����|ʲô|��|��|��|ô|��Ƶ|��>|����|��ַ|��վ|��ҳ|��ҳ|��ַ|����|����|����|��Ӱ|���Ӿ�|��Ƶ|����|����|����|ѧУ|ѧԺ|��ѧ|��ѧ|С˵|���|����|��Ϸ/'> ${file}.extend.image`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ shop/" | awk '$5 !~/��ô|����|��������|��Ƶ|��>|����|��ַ|��վ|��ҳ|��ҳ|��ַ|����|����|����|��Ӱ|���Ӿ�|��Ƶ|����|����|����|ѧУ|ѧԺ|��ѧ|��ѧ|С˵|���|����|��Ϸ/'> ${file}.extend.shop`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ music/" | awk '$5 !~/��ô|��������|��ô|����|���|����|ʲô|��Ƶ|��>|����|��ַ|��վ|��ҳ|��ҳ|��ַ|����|����|��Ƶ|����|����|ѧУ|ѧԺ|��ѧ|��ѧ|С˵|���|��Ϸ/'> ${file}.extend.music`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ soft/" | awk '$5 !~/��������|����|���|����|ʲô|��Ƶ|��>|����|��ַ|��վ|��ҳ|��ҳ|��ַ|����|����|����|��Ӱ|���Ӿ�|��Ƶ|����|����|����|ѧУ|ѧԺ|��ѧ|��ѧ|С˵|����|��Ϸ/'> ${file}.extend.soft`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ baike/" > ${file}.extend.baike`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ game/" | awk '$5 !~/��������|��Ƶ|��>|����|��ַ|��վ|��ҳ|��ҳ|����|����|��Ӱ|���Ӿ�|��Ƶ|����|����|����|ѧУ|ѧԺ|��ѧ|��ѧ|С˵|���|����/'> ${file}.extend.game`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ job/" > ${file}.extend.job`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ map/" > ${file}.extend.map`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ news/" | awk '$5 !~/��ô|����|��������|��ô|����|���|����|��>|����|��ַ|��վ|��ҳ|��ҳ|��ַ|����|����|����|��Ӱ|���Ӿ�|��Ƶ|����|����|����|С˵|���|����|��Ϸ/'> ${file}.extend.news`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ wenda/" > ${file}.extend.wenda`
`cat  tmp_/add.out| awk "/outcome\]/" |  awk "/ novel/" | awk '$5 !~/��������|��Ƶ|��>|����|��ַ|��վ|��ҳ|��ҳ|��ַ|����|����|����|��Ӱ|���Ӿ�|��Ƶ|����|����|����|ѧУ|ѧԺ|��ѧ|��ѧ|���|����|��Ϸ/'> ${file}.extend.novel`
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
