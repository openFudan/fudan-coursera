#lda version:   import lda
'''
import numpy as np
import lda.datasets
X = lda.datasets.load_reuters()

# X.shape：(395, 4258)   X.sum()：84010
vocab = lda.datasets.load_reuters_vocab()
# shape：(1, 4258)   ('church', 'pope', 'years'...)
titles = lda.datasets.load_reuters_titles()
# shape：(1, 395)   ('title1', 'title2', 'title3'...)

model = lda.LDA(n_topics=20, n_iter=1500, random_state=1)

model.fit(X)  # model.fit_transform(X) is also available

topic_word = model.topic_word_  # model.components_ also works
# shape: (20, 4258)
n_top_words = 8
for i, topic_dist in enumerate(topic_word):
   topic_words = np.array(vocab)[np.argsort(topic_dist)][:-(n_top_words+1):-1]
   print('Topic {}: {}'.format(i, ' '.join(topic_words)))

doc_topic = model.doc_topic_
# shape: (395, 20)
for i in range(300):
    print("{} (top topic: {})".format(titles[i], doc_topic[i].argmax()))




Topic 0: british churchill sale million major letters west britain
Topic 1: church government political country state people party against
Topic 2: elvis king fans presley life concert young death
Topic 3: yeltsin russian russia president kremlin moscow michael operation
Topic 4: pope vatican paul john surgery hospital pontiff rome
Topic 5: family funeral police miami versace cunanan city service
Topic 6: simpson former years court president wife south church
Topic 7: order mother successor election nuns church nirmala head
Topic 8: charles prince diana royal king queen parker bowles
Topic 9: film french france against bardot paris poster animal
Topic 10: germany german war nazi letter christian book jews
Topic 11: east peace prize award timor quebec belo leader
Topic 12: n't life show told very love television father
Topic 13: years year time last church world people say
Topic 14: mother teresa heart calcutta charity nun hospital missionaries
Topic 15: city salonika capital buddhist cultural vietnam byzantine show
Topic 16: music tour opera singer israel people film israeli
Topic 17: church catholic bernardin cardinal bishop wright death cancer
Topic 18: harriman clinton u.s ambassador paris president churchill france
Topic 19: city museum art exhibition century million churches set

'''


'''
#dataset reuters and imdb from keras
from keras.datasets import reuters
from keras.datasets import imdb
(x_train, y_train), (x_test, y_test) = imdb.load_data(path="imdb.npz",
                                                      num_words=None,
                                                      skip_top=0,
                                                      maxlen=None,
                                                      seed=113,
                                                      start_char=1,
                                                      oov_char=2,
                                                      index_from=3)
                            
(x_train, y_train), (x_test, y_test) = reuters.load_data(path="reuters.npz",
                                                         num_words=None,
                                                         skip_top=0,
                                                         maxlen=None,
                                                         test_split=0.2,
                                                         seed=113,
                                                         start_char=1,
                                                         oov_char=2,
                                                         index_from=3)
                                                         
word_index = reuters.get_word_index(path="reuters_word_index.json")
word_index = imdb.get_word_index(path="imdb_word_index.json")
word_index1 = sorted(word_index.items(), key=lambda x: x[1])

x_train_new=[]
for i in range(len(x_train)):
    sent=x_train[i]
    x_train_new += [word_index1[num-1][0] for num in sent if num<88584]
'''

import urllib.request
import os
import tarfile

#download dataset
url="http://ai.stanford.edu/~amaas/data/sentiment/aclImdb_v1.tar.gz"
filepath="data/aclImdb_v1.tar.gz"
if not os.path.isfile(filepath):
    result=urllib.request.urlretrieve(url,filepath)
    print('downloaded:',result)
#extract files
if not os.path.exists("data/aclImdb"):
    tfile = tarfile.open("data/aclImdb_v1.tar.gz", 'r:gz')
    result=tfile.extractall('data/')

from keras.datasets import imdb
from keras.preprocessing import sequence
from keras.preprocessing.text import Tokenizer


import re
def rm_tags(text):
    re_tag = re.compile(r'<[^>]+>')
    return re_tag.sub('', text)


import os
def read_files(filetype):
    path = "/Users/tanglimpse/lab/data/aclImdb/"
    file_list = []

    positive_path = path + filetype + "/pos/"
    for f in os.listdir(positive_path):
        file_list += [positive_path + f]

    negative_path = path + filetype + "/neg/"
    for f in os.listdir(negative_path):
        file_list += [negative_path + f]

    print('read', filetype, 'files:', len(file_list))

    all_labels = ([1] * 12500 + [0] * 12500)

    all_texts = []

    for fi in file_list:
        with open(fi, encoding='utf8') as file_input:
            all_texts += [rm_tags(" ".join(file_input.readlines()))]

    return all_labels, all_texts

y_train,train_text=read_files("train")
y_test,test_text=read_files("test")

import re
import numpy
import pandas as pd
from pprint import pprint

# Gensim
import gensim
import gensim.corpora as corpora
import gensim.models
from gensim.utils import simple_preprocess
from gensim.models import CoherenceModel

# spacy for lemmatization
import spacy

# Plotting tools
import pyLDAvis
import pyLDAvis.gensim  # don't skip this
import matplotlib.pyplot as plt

# Enable logging for gensim - optional
import logging

logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.ERROR)

import warnings

warnings.filterwarnings("ignore", category=DeprecationWarning)

# NLTK Stop words
from nltk.corpus import stopwords

stop_words = stopwords.words('english')
stop_words.extend(['from', 'subject', 're', 'edu', 'use', 'article', 'write', 'university'])


def sent_to_words(sentences):
    for sentence in sentences:
        yield (gensim.utils.simple_preprocess(str(sentence), deacc=True))  # deacc=True removes punctuations


# Define functions for stopwords, bigrams, trigrams and lemmatization
def remove_stopwords(texts):
    return [[word for word in simple_preprocess(str(doc)) if word not in stop_words] for doc in texts]


'''
def make_bigrams(texts):
    return [bigram_mod[doc] for doc in texts]

def make_trigrams(texts):
    return [trigram_mod[bigram_mod[doc]] for doc in texts]
'''


def lemmatization(texts, allowed_postags=['NOUN', 'ADJ', 'VERB', 'ADV']):
    """https://spacy.io/api/annotation"""
    # Initialize spacy 'en' model, keeping only tagger component (for efficiency)
    # python3 -m spacy download en
    nlp = spacy.load('en', disable=['parser', 'ner'])
    texts_out = []
    for sent in texts:
        doc = nlp(" ".join(sent))
        texts_out.append([token.lemma_ for token in doc if token.pos_ in allowed_postags])
    return texts_out


def preprocess(dataset):
    #data = dataset.data
    data = dataset
    #
    # Remove Emails
    data = [re.sub('\S*@\S*\s?', '', sent) for sent in data]

    data = [
        re.sub('From|Subject|Organization|Lines|In-reply-to|NNTP-Posting-Host|Nntp-Posting-Host|Article-I.D.|Keywords',
               ' ', sent) for sent in data]

    data = [re.sub('[a-zA-Z1-9]+\.[a-zA-Z1-9]+[a-zA-Z1-9\.]+', ' ', sent) for sent in data]

    # Remove new line characters
    data = [re.sub('\s+', ' ', sent) for sent in data]

    # Remove distracting single quotes
    data = [re.sub("\'", "", sent) for sent in data]

    data_words = list(sent_to_words(data))

    '''
    # Build the bigram and trigram models
    bigram = gensim.models.Phrases(data_words, min_count=5, threshold=100) # higher threshold fewer phrases.
    trigram = gensim.models.Phrases(bigram[data_words], threshold=100)

    # Faster way to get a sentence clubbed as a trigram/bigram
    bigram_mod = gensim.models.phrases.Phraser(bigram)
    trigram_mod = gensim.models.phrases.Phraser(trigram)

    # See trigram example
    #print(trigram_mod[bigram_mod[data_words[0]]])

    # Form Bigrams
    #data_words_bigrams = make_bigrams(data_words_nostops)
    '''

    # Do lemmatization keeping only noun, adj, vb, adv
    data_lemmatized = lemmatization(data_words, allowed_postags=['NOUN', 'ADJ', 'VERB', 'ADV'])

    # Remove Stop Words
    data_words_nostops = remove_stopwords(data_lemmatized)
    return data_words_nostops


data_words_train = preprocess(train_text[:1500]+train_text[15000:16500])
data_words_test = preprocess(test_text[:1000]+test_text[15000:16000])
data_words_all = data_words_train + data_words_test

# Create Dictionary
id2word = corpora.Dictionary(data_words_all)

# Term Document Frequency
corpus_train = [id2word.doc2bow(text) for text in data_words_train]
corpus_test = [id2word.doc2bow(text) for text in data_words_test]
corpus_all = corpus_train + corpus_test

# Build LDA model
lda_model = gensim.models.ldamodel.LdaModel(corpus=corpus_train,
                                            id2word=id2word,
                                            num_topics=3,
                                            random_state=99,
                                            update_every=1,
                                            chunksize=100,
                                            passes=10,
                                            alpha='auto',
                                            per_word_topics=True)
lda_model.show_topics()


'''
#find a word in the list and print
for i in range(len(data_words_train)):
    list=data_words_train[i]
    if 'armenian' in list:
        print(i)
'''

topics = lda_model.get_document_topics(corpus_test, per_word_topics=True)

'''
# append keywords of class into words of each document
import copy

data_words_test_append = copy.deepcopy(data_words_test)

keywords = ['religion', 'church']


times = 100
for i in range(times):
    text += keywords
corpus_test1 = id2word.doc2bow(text)
topics1 = lda_model.get_document_topics(corpus_test1, per_word_topics=True)
print(topics1)

corpus_test = [id2word.doc2bow(text) for text in data_words_test_append]
topics = lda_model.get_document_topics(corpus_test, per_word_topics=True)
'''


# test result
target = y_test[:1000]+y_test[15000:16000]

result = []
for topic in topics:
    topic_len = len(topic[0])
    x = 0
    '''
    for i in range(topic_len):
        if topic[0][i][1]>0.5:
            result.append(topic[0][i][0])
            x=1
    if x==0:
        result.append(topic[0][0][0])
    '''
    p1 = 0
    p2 = 0
    for i in range(topic_len):

        if topic[0][i][0] == 3:
            p1 = topic[0][i][1]
        else:
            p2 += topic[0][i][1]
    if p2 >= p1:
        result.append(2)
    else:
        result.append(1)

from sklearn.metrics import f1_score

f1_score(target, result, average='macro')



