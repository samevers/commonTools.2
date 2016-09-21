cd ../textmodel/tmp
ln -s ../Porn/train/train.*.seg ./

cd ..

for(( i = 1; i <=20; i++ ))
do
	filename="train."$i".seg"
	modelname="model."$i".gram"
	echo $filename
	echo $modelname
	./src/main.gram tmp/$filename
	mv model.gram ../Porn/model_out/$modelname
done

## Features Selection
cd ../Porn/model_out
for(( i = 1; i <= 20; i++ ))
do
	modelfile="model."$i".gram"
	python ../feaSelect.py $modelfile > tmpfile
	mv tmpfile $modelfile
done

## ln -s 
cd ../../textmodel/tmp
for(( i = 1; i <=20; i++ ))
do
	modelfile="model."$i".gram"
	ln -s ../Porn/model_out/$modelfile ./
done
