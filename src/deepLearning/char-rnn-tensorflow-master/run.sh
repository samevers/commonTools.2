#! /bin/bash
############################################
#
# Author: 
# E-Mail:@sogou-inc.com
# Create time: 2016 12ÔÂ 20 17Ê±44·Ö29Ãë
# version 1.0
#
############################################
#python train.sam.py --rnn_size=128 --num_layers=3 --model=lstm --batch_size=50 --seq_length=10 --save_every=500 
#python predict.py --filename=data/tinyshakespeare/test.10w > tmp/out
cat tmp/out | perl bin/thres2.pl  > tmp/out.thres
cat tmp/out.thres | perl bin/sort.pl > tmp/out.thres.sort


# threshold of model <model.ckpt-23495099> is >= 0.006


#cd porn
#cat ../tmp/out.thres.sort | perl bin/porn.pl > ../tmp/out.thres.sort.delPorn
