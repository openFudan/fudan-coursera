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
warnings.filterwarnings("ignore",category=DeprecationWarning)



# NLTK Stop words
from nltk.corpus import stopwords
stop_words = stopwords.words('english')
stop_words.extend(['from', 'subject', 're', 'edu', 'use', 'article', 'write', 'university'])
from sklearn.datasets import fetch_20newsgroups


def sent_to_words(sentences):
    for sentence in sentences:
        yield(gensim.utils.simple_preprocess(str(sentence), deacc=True))  # deacc=True removes punctuations

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
    data=dataset.data
    #
    # Remove Emails
    data = [re.sub('\S*@\S*\s?', '', sent) for sent in data]

    data=  [re.sub('From|Subject|Organization|Lines|In-reply-to|NNTP-Posting-Host|Nntp-Posting-Host|Article-I.D.|Keywords', ' ', sent) for sent in data]

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


categories = [  'comp.graphics',
                'comp.os.ms-windows.misc',
                'comp.sys.ibm.pc.hardware',
                'comp.sys.mac.hardware',
                'comp.windows.x',
                'talk.politics.guns',
                'talk.politics.mideast',
                'talk.politics.misc'
            ]
categories1 = [ 'soc.religion.christian',
                'talk.religion.misc',
                'talk.politics.guns',
                'talk.politics.mideast',
                'talk.politics.misc'
            ]

'''
computers, recreation, religion, science, forsale and politics.
computers:
 'comp.graphics',
 'comp.os.ms-windows.misc',
 'comp.sys.ibm.pc.hardware',
 'comp.sys.mac.hardware',
 'comp.windows.x',
 
recreation:
 'rec.autos',
 'rec.motorcycles',
 'rec.sport.baseball',
 'rec.sport.hockey',

religion:
 'talk.religion.misc',
 'soc.religion.christian'
 
science:
 'sci.crypt',
 'sci.electronics',
 'sci.med',
 'sci.space',
 
forsale:
 'misc.forsale',
 
politics:
 'talk.politics.guns',
 'talk.politics.mideast',
 'talk.politics.misc',


 'alt.atheism',
'''

dataset_all = fetch_20newsgroups(subset='all', categories=categories1, shuffle=True, random_state=1)
dataset_train = fetch_20newsgroups(subset='train', categories=categories1, shuffle=True, random_state=1)
dataset_test = fetch_20newsgroups(subset='test', categories=categories1, shuffle=True, random_state=1)
# all=18846     train=11314     test=7532


data_words_train=preprocess(dataset_train)
data_words_test=preprocess(dataset_test)
data_words_all=data_words_train+data_words_test

# Create Dictionary
id2word = corpora.Dictionary(data_words_all)

# Term Document Frequency
corpus_train = [id2word.doc2bow(text) for text in data_words_train]
corpus_test = [id2word.doc2bow(text) for text in data_words_test]
corpus_all =  corpus_train+corpus_test

# Build LDA model
lda_model = gensim.models.ldamodel.LdaModel(corpus=corpus_train,
                                           id2word=id2word,
                                           num_topics=5,
                                           random_state=99,
                                           update_every=1,
                                           chunksize=100,
                                           passes=10,
                                           alpha='auto',
                                           per_word_topics=True)
lda_model.show_topics()



'''
for i in range(len(data_words_train)):
    list=data_words_train[i]
    if 'armenian' in list:
        print(i)
'''

topics = lda_model.get_document_topics(corpus_test, per_word_topics=True)

print(topics[0])
