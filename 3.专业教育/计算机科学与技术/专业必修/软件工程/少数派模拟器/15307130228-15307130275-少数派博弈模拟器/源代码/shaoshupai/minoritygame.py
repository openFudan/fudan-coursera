#  !/usr/bin/env python
#  -*- coding:utf-8 -*-

from numpy import *

class Strgy:
    def __init__(self, m=4):
        self.score = 0  # Strategy's initial score
        self.rules = ''.join(str(random.randint(2)) for _ in range(2**m))
        self.count = 0  # how many times this strategy has been used?

    def act(self, state):   # act according to the current state (the global info)
        self.count += 1
        return sign(int(self.rules[state], 2)-0.5)  # +1 bar; -1 home; state [0:2**m-1] describes all histories

    def update(self, v):
        self.score += v     # update the score by adding v to it


class Agent:
    def __init__(self, s=2, m=4):
        self.Strgies = array([Strgy(m) for _ in range(s)])  # the Agent's strategies
        self.action = None  # for recording the Agent's latest action   +1 bar; -1 home

    def act(self, state):
        self.state = state  # recording the current global information
        # respond using the best strategy
        scr = array([x.score for x in self.Strgies])
        strgy = random.choice(self.Strgies[scr >= max(scr)])
        self.action = strgy.act(state)  # from the current state get the action

    def update(self, w):
        # update the score of the strategies
        for strgy in self.Strgies:
            ds = sign(int(strgy.act(self.state) == w)-0.5)  # w=1 ds=1; w=-1 ds=-1 w:the winning action
            strgy.update(ds)


class World:
    def __init__(self, T = 20, N = 101, m=3, s=2):
        self.T = T # number of steps to run each time
        self.N = N # number of Agents
        self.m = m # memory length
        self.s = s # number of strategies for each Agent
        self.Agents = [Agent(s, m) for _ in range(self.N)] # initialize the Agents
        self.W = [random.choice([-1,1]) for _ in range(self.m)] # initialize global info (i.e. the winning actions)
        self.A = [] # actions sum list

    def act(self):
        for t in range(self.T):
            state = int(''.join([str(sign(x+1)) for x in self.W[-self.m:]]),2)
            for u in self.Agents: u.act(state)
            self.update()
            for u in self.Agents: u.update(self.W[-1])

    def actastep(self):
        state = int(''.join([str(sign(x+1)) for x in self.W[-self.m:]]),2)
        for u in self.Agents: u.act(state)
        self.update()
        for u in self.Agents: u.update(self.W[-1])

    def update(self):
        a = sum(array([u.action for u in self.Agents]))
        self.A.append(a)
        self.W.append(random.choice([-1,1]) if a==0 else -int(sign(a)))




'''
class Strgy:
    def __init__(self, m=4):
        self.score = 0 # Strategy's initial score
        self.rules = ''.join(str(random.randint(2)) for _ in range(2**m))
        self.count = 0 # how many times this strategy has been used?

    def act(self, state): # act according to the current state (the global info)
        self.count += 1
        return sign(int(self.rules[state], 2)-0.5)

    def update(self, v):
        self.score += v # update the score by adding v to it


class Agent:
    def __init__(self, s=2, m=4):
        self.Strgies = array([Strgy(m) for _ in range(s)]) # the Agent's strategies (long time memory)
        self.action = None # for recording the Agent's latest action
                           #  (short time memory)
    def act(self, state):
        self.state = state # recording the current global information
        # respond using the best strategy
        scr = array([x.score for x in self.Strgies])
        strgy = random.choice(self.Strgies[scr >= max(scr)])
        self.action = strgy.act(state) # from the current state get the action

    def update(self, w):
        # update the score of the strategies
        for strgy in self.Strgies:
            ds = sign(int(strgy.act(self.state) == w)-0.5)
            strgy.update(ds)


class World:
    def __init__(self, T = 1, N = 101, m=3, s=2):
        self.T = T # number of steps to run each time
        self.N = N # number of Agents
        self.m = m # memory length
        self.s = s # number of strategies for each Agent
        self.Agents = [Agent(s, m) for _ in range(self.N)] # initialize the Agents
        self.Prices = [0] # for storing the prices, initialize it with zero
        self.SuccessRates = [] # for storing the global success rates
        self.W = [random.choice([-1,1]) for _ in range(self.m)] # initialize global info (i.e. the winning actions)
        self.D = [] # net actions. sum_i a_i, where a_i is the i-th Agent's action +1 or -1

    def act(self):
        for t in range(self.T):
            state = int(''.join([str(sign(x+1)) for x in self.W[-self.m:]]),2)
            for u in self.Agents: u.act(state)
            self.update()
            for u in self.Agents: u.update(self.W[-1])

    def update(self):
        d = sum(array([u.action for u in self.Agents]))
        self.D.append(d)
        self.W.append(random.choice([-1,1]) if d==0 else -int(sign(d)))
        rate = (self.N-abs(d))/(2.0*self.N) # the success rate
        self.SuccessRates.append(rate)
        dd = d/float(self.N) # normalize by N to get the price
        self.Prices.append(self.Prices[-1] + dd) # update the price
'''
