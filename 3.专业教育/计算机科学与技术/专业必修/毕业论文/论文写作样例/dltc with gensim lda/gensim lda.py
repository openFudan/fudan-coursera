'''
#lda eta
import gensim
import numpy as np
import nltk
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer
import matplotlib.pyplot as plt

txt = [
    'I like to eat broccoli and bananas.',
    'I munched a banana and spinach smoothie for breakfast.',
    'Chinchillas and kittens are cute.',
    'My sister adopted a kitten yesterday.',
    'Look at this cute hamster munching on a piece of broccoli.'
]
len(txt)


# simplify Penn tags to n (NOUN), v (VERB), a (ADJECTIVE) or r (ADVERB)
def simplify(penn_tag):
    pre = penn_tag[0]
    if (pre == 'J'):
        return 'a'
    elif (pre == 'R'):
        return 'r'
    elif (pre == 'V'):
        return 'v'
    else:
        return 'n'


def preprocess(text):
    stop_words = stopwords.words('english')
    toks = gensim.utils.simple_preprocess(str(text), deacc=True)
    #toks = gensim.utils.simple_preprocess(str(txt[0]), deacc=True)
    wn = WordNetLemmatizer()
    return [wn.lemmatize(tok, simplify(pos)) for tok, pos in nltk.pos_tag(toks) if tok not in stop_words]


corp = [preprocess(line) for line in txt]
corp


dictionary = gensim.corpora.Dictionary(corp)
len(dictionary)


bow = [dictionary.doc2bow(line) for line in corp]
bow


def viz_model(model, modeldict):
    ntopics = model.num_topics
    # top words associated with the resulting topics
    topics = ['Topic {}: {}'.format(t,modeldict[w]) for t in range(ntopics) for w,p in model.get_topic_terms(t, topn=1)]
    terms = [modeldict[w] for w in modeldict.keys()]
    fig,ax=plt.subplots()
    ax.imshow(model.get_topics())  # plot the numpy matrix
    ax.set_xticks(modeldict.keys())  # set up the x-axis
    ax.set_xticklabels(terms, rotation=90)
    ax.set_yticks(np.arange(ntopics))  # set up the y-axis
    ax.set_yticklabels(topics)
    plt.show()


def test_eta(eta, dictionary, ntopics, print_topics=True, print_dist=True):
    np.random.seed(42) # set the random seed for repeatability
    bow = [dictionary.doc2bow(line) for line in corp] # get the bow-format lines with the set dictionary
    with (np.errstate(divide='ignore')):  # ignore divide-by-zero warnings
        model = gensim.models.ldamodel.LdaModel(
            corpus=bow, id2word=dictionary, num_topics=ntopics,
            random_state=42, chunksize=100, eta=eta,
            eval_every=-1, update_every=1,
            passes=150, alpha='auto', per_word_topics=True)
    # visuzlize the model term topics
    viz_model(model, dictionary)
    print('Perplexity: {:.2f}'.format(model.log_perplexity(bow)))
    if print_topics:
        # display the top terms for each topic
        for topic in range(ntopics):
            print('Topic {}: {}'.format(topic, [dictionary[w] for w,p in model.get_topic_terms(topic, topn=3)]))
    if print_dist:
        # display the topic probabilities for each document
        for line,bag in zip(txt,bow):
            doc_topics = ['({}, {:.1%})'.format(topic, prob) for topic,prob in model.get_document_topics(bag)]
            print('{} {}'.format(line, doc_topics))
    return model


test_eta('auto',dictionary,ntopics=2)


def create_eta(priors, etadict, ntopics):
    eta = np.full(shape=(ntopics, len(etadict)), fill_value=1) # create a (ntopics, nterms) matrix and fill with 1
    for word, topic in priors.items(): # for each word in the list of priors
        keyindex = [index for index,term in etadict.items() if term==word] # look up the word in the dictionary
        if (len(keyindex)>0): # if it's in the dictionary
            eta[topic,keyindex[0]] = 1e7  # put a large number in there
    eta = np.divide(eta, eta.sum(axis=0)) # normalize so that the probabilities sum to 1 over all topics
    return eta


apriori_original = {
    'banana':0, 'broccoli':0, 'munch':0,
    'cute':1, 'kitten':1  # we'll leave out broccoli from this one!
}
eta = create_eta(apriori_original, dictionary, 2)
test_eta(eta, dictionary, 2)


apriori_opposite = {
    'cute':0, 'kitten':0,
    'banana':1, 'broccoli':1, 'munch':1
}
eta = create_eta(apriori_opposite, dictionary, 2)
test_eta(eta, dictionary, 2)


apriori_harder = {
    'cute':0, 'kitten':0, 'hamster':0, 'chinchilla':0, 'look':0,
    'banana':1, 'broccoli':1, 'piece':1, 'breakfast':1, 'munch':1
}
eta = create_eta(apriori_harder, dictionary, 2)
test_eta(eta, dictionary, 2)


print([dictionary[w] for w in dictionary.keys()])


dictionary2 = gensim.corpora.Dictionary(
    [['banana', 'broccoli', 'eat', 'like', 'breakfast', 'munch', 'smoothie', 'spinach', 'chinchilla',
    'cute', 'kitten', 'adopt', 'sister', 'yesterday', 'hamster', 'look', 'piece']]
)
print([dictionary2[w] for w in dictionary2.keys()])


eta = create_eta(apriori_harder, dictionary, 2)
test_eta(eta, dictionary, 2)

eta = create_eta(apriori_harder, dictionary2, 2)
test_eta(eta, dictionary2, 2)
'''

'''
#lda example
texts = [['bank','river','shore','water'],
        ['river','water','flow','fast','tree'],
        ['bank','water','fall','flow'],
        ['bank','bank','water','rain','river'],
        ['river','water','mud','tree'],
        ['money','transaction','bank','finance'],
        ['bank','borrow','money'],
        ['bank','finance'],
        ['finance','money','sell','bank'],
        ['borrow','sell'],
        ['bank','loan','sell']]

dictionary = corpora.Dictionary(texts)
corpus = [dictionary.doc2bow(text) for text in texts]
model = gensim.models.ldamodel.LdaModel(corpus,
                                        id2word=dictionary,
                                        num_topics=2,
                                        random_state=99)
model.show_topics()
topics = model.get_document_topics(corpus, per_word_topics=True)
'''

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
    #data = dataset
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
categories:
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

"""
#append keywords of class into words of each document
import copy
data_words_test_append=copy.deepcopy(data_words_test)


keywords=['christian', 'god', 'christ', 'church', 'bible', 'jesus', 'believe', 'morality', 'religion', 'horus',
        'israel', 'arab', 'jew', 'jewish', 'muslim', 'israeli', 'war', 'attack', 'palestinian', 'gun', 'fbi', 'weapon', 'compound', 'gay', 'homosexual', 'sexual', 'sex', 'drug' 
        ]
'''
computers:
bus pc motherboard bios board computer dos 
mac apple powerbook
graphics image gif animation tiff 
window motif xterm sun windows 
windows dos microsoft ms driver drivers card printer 
 
recreation:
car ford auto toyota honda nissan bmw 
bike motorcycle yamaha 
baseball ball hitter 
hockey wings espn 

religion:
christian god christ church bible jesus believe
christian morality jesus god religion horus believe

christian god christ church bible jesus believe morality religion horus
 
science:
circuit electronics radio signal battery 
encryption key crypto algorithm security 
doctor medical disease medicine patient 
space orbit moon earth sky solar 
 
forsale:
sale offer shipping forsale sell price brand obo
 
politics:
gun fbi weapon compound 
israel arab jew jewish muslim israeli war attack palestinian  
gay homosexual sexual sex drug

israel arab jew jewish muslim israeli war attack palestinian gun fbi weapon compound gay homosexual sexual sex drug 


'alt.atheism',
atheist christian atheism god islamic 
 
'''

times=100
for i in range(len(data_words_test_append)):
    keywords_exist=list(set(data_words_test_append[i]) & set(keywords))
    for j in range(times):
        data_words_test_append[i]+=keywords_exist

corpus_test1 = [id2word.doc2bow(text) for text in data_words_test_append]
topics1 = lda_model.get_document_topics(corpus_test1, per_word_topics=True)
print(topics1)
"""


# test result
target=[]
for i in dataset_test.target:
    target.append(1 if i==0 or i==4 else 2)

result=[]
for topic in topics:
    topic_len=len(topic[0])
    x=0
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
        if topic[0][i][0]==3:
            p1=topic[0][i][1]
        else:
            p2+=topic[0][i][1]
    if p2>=p1:
        result.append(2)
    else:
        result.append(1)

from sklearn.metrics import f1_score
f1_score(target, result, average='macro')


'''
#accuracy

right=0
for i in range(len(target)):
    if target[i]==result[i]:
        right+=1

print(right/len(target))
'''

'''
#find difference between two classes

n12=0
n21=0
for i in range(len(target)):
    if(target[i]==1 and result[i]==2):
        n12+=1
    if (target[i] == 2 and result[i] == 1):
        n21 += 1
'''

