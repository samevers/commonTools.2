testfile=$1
cat $testfile | /search/yonghuahu/tools/wordSegment/src/segment_bin > $testfile".seg"
testseg=$testfile".seg"

cd /search/yonghuahu/dm_/classify/textmodel
## predict
for(( i = 1; i <=20; i++ ))
do
	modelname="model."$i".gram"
	outname="test.dat.seg.out."$i
	logname="x."$i".gram"
	./src/main.gram $testseg $modelname > $logname
	mv $testseg".out" tmp/$outname
	pornout="pornScore."$i
	cat tmp/$outname| awk "/ºÚË¿|×ö°®|ÐÔ°®|É«Çé|È«Âã|ÂãÌå|ÐÔ¸ß³±|ÉÙ¸¾|AV|av|Ë¿×ã|×ã½»|ÐÔ½»|ÊìÅ®|·çÉ§|¿ÎÌå|ïýÌå|Òùµ´|ÂÒÂ×|µ´¸¾|ºó²å|ÐÔÂÒÒù|Ã«Æ¬|²åÎÒ|´óŒÅ|½Ð´²|»ÆÆ¬|ºÚ±Æ/" > tmp/$pornout
done

## vote the output
#python vote.py > test.dat.seg.out.ter

