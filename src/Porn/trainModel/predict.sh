
## INPUT is a segment outcome
INPUT=$1

cd ../classify/textModel
## predict
for(( i = 1; i <=20; i++ ))
do
	modelname="model."$i".gram"
	outname=$INPUT".out."$i
	logname="x."$i".gram"
	./src/main.gram $INPUT tmp/$modelname > log/$logname
	mv $INPUT".out" out/$outname
	pornout="pornScore."$i
	cat out/$outname| awk "/ºÚË¿|×ö°®|ÐÔ°®|É«Çé|È«Âã|ÂãÌå|ÐÔ¸ß³±|ÉÙ¸¾|AV|av|Ë¿×ã|×ã½»|ÐÔ½»|ÊìÅ®|·çÉ§|¿ÎÌå|ïýÌå|Òùµ´|ÂÒÂ×|µ´¸¾|ºó²å|ÐÔÂÒÒù|Ã«Æ¬|²åÎÒ|´óŒÅ|½Ð´²|»ÆÆ¬|ºÚ±Æ/" > tmp/$pornout
done

## vote the output
python vote.py out
cat $INPUT".ter" | sort -t "	" -k 2 -n > $INPUT".ter.sort"
