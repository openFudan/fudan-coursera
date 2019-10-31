#  !/usr/bin/env python
#  -*- coding:utf-8 -*-

from pylab import *
from shaoshupai.minoritygame import *



T = int(sys.argv[1])
N = int(sys.argv[2])
m = int(sys.argv[3])
s = int(sys.argv[4])
fig = figure(1, figsize=(6,4))
# no player   figure1: A(t)-by-Iteration
sim = World(T, N, m, s)
sim.act()
X=[i for i in range(T)]
Y=sim.A
plot(X, Y)
xlabel(r'$Iteration$')
ylabel(r'$A(t)$')
legend(loc='best')
fig.set_tight_layout(True)
savefig('A(t)-by-Iteration.png', format='png')
fig.clf()

# no player  figure2: variance-by-2^{m}
syms = ['ro-','gs-','bd-']
s = [2, 4, 6]
for i in range(len(s)):
    Y = []
    X = []
    for m in range(1, 13):
        x = []
        y = []
        sim = World(T, N, m=m, s=s[i])
        sim.act()
        x.append(float(2**m)/float(N))
        y.append(var(sim.A)/float(N))
        X.append(mean(x))
        Y.append(mean(y))
        print('m='+str(m))
    plot(X, Y, syms[i], label='s='+str(s[i]))
    print('s='+str(s[i]))

xscale('log')
yscale('log')
xlabel(r'$2^{m}/N$')
ylabel(r'$\sigma^2/N$')
legend(loc='best')
fig.set_tight_layout(True)
savefig('variance-by-2^{m}.png', format='png')
#, bbox_inches='tight'
fig.clf()
