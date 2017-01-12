#!/bin/bash

###############
# Author : Huyonghua
# Date: 2014/11/24
# Mail: huyonghua117421@sogou-inc.com
###############

input=/user/web_nlp/huyonghua/w2v/data/*
output=/user/web_nlp/huyonghua/w2v/model
hadoop fs -rmr $output

hadoop org.apache.hadoop.streaming.HadoopStreaming \
        -D mapred.map.tasks=1000 \
        -D mapred.reduce.tasks=100 \
        -D mapred.job.name=w2vmodel  \
        -input ${input} \
        -output ${output} \
        -file  ./vectors.vslog.bin \
        -file bin/w2v-distance \
        -mapper cat \
        -reducer ./w2v-distance

