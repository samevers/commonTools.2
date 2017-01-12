import numpy as np
import re
import itertools
from collections import Counter


def clean_str(string):
    """
    Tokenization/string cleaning for all datasets except for SST.
    Original taken from https://github.com/yoonkim/CNN_sentence/blob/master/process_data.py
    """
    string = re.sub(r"[^A-Za-z0-9(),!?\'\`]", " ", string)
    string = re.sub(r"\'s", " \'s", string)
    string = re.sub(r"\'ve", " \'ve", string)
    string = re.sub(r"n\'t", " n\'t", string)
    string = re.sub(r"\'re", " \'re", string)
    string = re.sub(r"\'d", " \'d", string)
    string = re.sub(r"\'ll", " \'ll", string)
    string = re.sub(r",", " , ", string)
    string = re.sub(r"!", " ! ", string)
    string = re.sub(r"\(", " \( ", string)
    string = re.sub(r"\)", " \) ", string)
    string = re.sub(r"\?", " \? ", string)
    string = re.sub(r"\s{2,}", " ", string)
    return string.strip().lower()


def load_data_and_labels():
    """
    Loads MR polarity data from files, splits the data into words and generates labels.
    Returns split sentences and labels.
    """
    # Load data from files
    positive_examples = list(open("./tmp/video.query.delFilm.seg.train", "r").readlines())
    positive_examples = [s.strip() for s in positive_examples]
    negative_examples = list(open("./tmp/web.novideo.query.seg.train", "r").readlines())
    negative_examples = [s.strip() for s in negative_examples]
    # Split by words
    x_text = positive_examples + negative_examples
    x_text = [clean_str(sent) for sent in x_text]
    x_text = [s.split(" ") for s in x_text]
    # Generate labels
    positive_labels = [[0, 1] for _ in positive_examples]
    negative_labels = [[1, 0] for _ in negative_examples]
    y = np.concatenate([positive_labels, negative_labels], 0)
    return [x_text, y]


def pad_sentences(sentences, padding_word="<PAD/>"):
    """
    Pads all sentences to the same length. The length is defined by the longest sentence.
    Returns padded sentences.
    """
    sequence_length = max(len(x) for x in sentences)
    padded_sentences = []
    for i in range(len(sentences)):
        sentence = sentences[i]
        num_padding = sequence_length - len(sentence)
        new_sentence = sentence + [padding_word] * num_padding
        padded_sentences.append(new_sentence)
    return padded_sentences


def build_vocab(sentences):
    """
    Builds a vocabulary mapping from word to index based on the sentences.
    Returns vocabulary mapping and inverse vocabulary mapping.
    """
    # Build vocabulary
    word_counts = Counter(itertools.chain(*sentences))
    # Mapping from index to word
    vocabulary_inv = [x[0] for x in word_counts.most_common()]
    vocabulary_inv = list(sorted(vocabulary_inv))
    # Mapping from word to index
    vocabulary = {x: i for i, x in enumerate(vocabulary_inv)}
    return [vocabulary, vocabulary_inv]


def build_input_data(sentences, labels, vocabulary):
    """
    Maps sentencs and labels to vectors based on a vocabulary.
    """
    x = np.array([[vocabulary[word] for word in sentence] for sentence in sentences])
    y = np.array(labels)
    return [x, y]


def load_data():
    """
    Loads and preprocessed data for the MR dataset.
    Returns input vectors, labels, vocabulary, and inverse vocabulary.
    """
    # Load and preprocess data
    sentences, labels = load_data_and_labels()
    sentences_padded = pad_sentences(sentences)
    vocabulary, vocabulary_inv = build_vocab(sentences_padded)
    x, y = build_input_data(sentences_padded, labels, vocabulary)
    return [x, y, vocabulary, vocabulary_inv]


def batch_iter(data, batch_size, num_epochs, shuffle=True):
    """
    Generates a batch iterator for a dataset.
    """
    data = np.array(data)
    data_size = len(data)
    num_batches_per_epoch = int(len(data)/batch_size) + 1
    for epoch in range(num_epochs):
        # Shuffle the data at each epoch
        if shuffle:
            shuffle_indices = np.random.permutation(np.arange(data_size))
            shuffled_data = data[shuffle_indices]
        else:
            shuffled_data = data
        for batch_num in range(num_batches_per_epoch):
            start_index = batch_num * batch_size
            end_index = min((batch_num + 1) * batch_size, data_size)
            yield shuffled_data[start_index:end_index]

def get_voc(filename="./data/video.vectors.bin", dim=100):
    #w2v = list(open("../data/vectors.skip.1124.4m.10w.txt", "r").readlines())
    w2v = list(open(filename, "r").readlines())
    #w2v = list(open("../tmp/w2v.head.1", "r").readlines())
    w2v = [s.strip().split("\t") for s in w2v]
    w2v = {s[0]:[float(x) for x in s[1:]] for s in w2v if len(s)==101}
    idmap = dict()
    idmap["<FIL/>"]=0
    w2vlst = []
    #w2vlst.append(np.zeros(dim))
    w2vlst.append([0.0]*100)
    idmap["<PAD/>"]=1
    #w2vlst.append(np.zeros(dim))
    w2vlst.append([0.0]*100)
    ind=2
    for k in w2v:
        idmap[k]=ind
        ind = ind + 1
        w2vlst.append(w2v[k])
    return [w2vlst,idmap]

def data_iter(idmap, batchsize=64, num_epochs=1, filename="./tmp/all.video"):
    batch = []
    for i in range(0,num_epochs):
        f=open(filename)
        for line in f:
            vec = line.strip().split("\t")
            if len(vec)==2:
                hit=0
                cnt=0
                token = []
                for i in vec[1].split(" "):
                    if i in idmap:
                        token.append(idmap[i])
                        hit = hit + 1
                    else:
                        token.append(idmap["<FIL/>"])
                    cnt = cnt+1
                    if cnt >= 24:
                        break
                if hit/(cnt+0.001) >= 0.7:
                    token = token + [idmap["<PAD/>"]] * (24 - len(token))
                    token1 = np.array([np.array(token), np.array([0,1] if int(vec[0])==1 else [1,0])])
                    batch.append(token1)
                    if len(batch) >= batchsize:
                        res = np.array(batch)
                        yield res
                        batch = []
        f.close()
#w2v,idmap = get_voc()
#train_batches = data_iter(idmap)
#for batch in train_batches:
#    x_batch, y_batch = zip(*batch)
#    print x_batch
#    print y_batch
#    #for tp in batch:
#    #    print tp
