#! /usr/bin/env python
import sys
import tensorflow as tf
import numpy as np
import os
import time
import datetime
import data_helperstest1 as data_helpers

tf.flags.DEFINE_string("checkpoint_dir", "./runs", "Checkpoint directory from training run")
tf.flags.DEFINE_boolean("allow_soft_placement", True, "Allow device soft device placement")
tf.flags.DEFINE_boolean("log_device_placement", False, "Log placement of ops on devices")

FLAGS = tf.flags.FLAGS
FLAGS._parse_flags()

print("checkpoint_dir: ",FLAGS.checkpoint_dir)
checkpoint_file = 'model/20160926/model-100400'
#checkpoint_file = 'model/model-165300'
#checkpoint_file = 'model-1/model-221100'
#checkpoint_file = 'runs/1471418997/checkpoints/model-798300'
print("checkpoint_file: ",checkpoint_file)
w2vlst,vocabulary = data_helpers.get_voc()
voc_inv = {}
for i in vocabulary:
    voc_inv[vocabulary[i]] = i

#checkpoint_file = tf.train.latest_checkpoint(FLAGS.checkpoint_dir)
graph = tf.Graph()
with graph.as_default():
    session_conf = tf.ConfigProto(
      allow_soft_placement=FLAGS.allow_soft_placement,
      log_device_placement=FLAGS.log_device_placement)
    sess = tf.Session(config=session_conf)
    with sess.as_default():
        saver = tf.train.import_meta_graph("{}.meta".format(checkpoint_file))
        #saver = tf.train.import_meta_graph("model/model.meta".format(checkpoint_file))
        saver.restore(sess, checkpoint_file)
        embeddingW = graph.get_operation_by_name("embedding/W").outputs[0]
        convW3 = graph.get_operation_by_name("conv-maxpool-3/W").outputs[0]
        convW4 = graph.get_operation_by_name("conv-maxpool-4/W").outputs[0]
        convW5 = graph.get_operation_by_name("conv-maxpool-5/W").outputs[0]
        convb3 = graph.get_operation_by_name("conv-maxpool-3/b").outputs[0]
        convb4 = graph.get_operation_by_name("conv-maxpool-4/b").outputs[0]
        convb5 = graph.get_operation_by_name("conv-maxpool-5/b").outputs[0]
        outputW = graph.get_operation_by_name("W").outputs[0]
        outputb = graph.get_operation_by_name("output/b").outputs[0]
        embeddingW,convW3,convW4,convW5,convb3,convb4,convb5,outputW,outputb = sess.run([embeddingW,convW3,convW4,convW5,convb3,convb4,convb5,outputW,outputb])

ind = 0

for a in embeddingW:
    if ind in voc_inv:
        sys.stdout.write(voc_inv[ind] + "\tEMBEDDING\t" + str(ind)),
        ind += 1
        for b in a:
            sys.stdout.write("\t" + str(b)),
        sys.stdout.write("\n"),

for a in convW3:
    for b in a:
        sys.stdout.write("convW3")
        for c in b:
            for d in c:
                sys.stdout.write("\t" + str(d))
        sys.stdout.write("\n"),

for a in convW4:
    for b in a:
        sys.stdout.write("convW4")
        for c in b:
            for d in c:
                sys.stdout.write("\t" + str(d))
        sys.stdout.write("\n"),

for a in convW5:
    for b in a:
        sys.stdout.write("convW5")
        for c in b:
            for d in c:
                sys.stdout.write("\t" + str(d))
        sys.stdout.write("\n"),

sys.stdout.write("convb3")
for a in convb3:
    sys.stdout.write("\t" + str(a))
sys.stdout.write("\n"),

sys.stdout.write("convb4")
for a in convb4:
    sys.stdout.write("\t" + str(a))
sys.stdout.write("\n"),

sys.stdout.write("convb5")
for a in convb5:
    sys.stdout.write("\t" + str(a))
sys.stdout.write("\n"),

for a in outputW:
    sys.stdout.write("outputW")
    for b in a:
        sys.stdout.write("\t" + str(b))
    sys.stdout.write("\n"),

sys.stdout.write("outputb")
for a in outputb:
    sys.stdout.write("\t" + str(a))
sys.stdout.write("\n"),
