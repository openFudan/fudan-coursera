import numpy as np
GAMMA = 0.8
Q = np.zeros((17,17))
states={
    1:'AAA',
    2:'BAA',
    3:'CAA',
    4:'BCA',
    5:'CBA',
    6:'CCA',
    7:'BBA',
    8:'CCB',
    9:'BBC',
    10:'ACB',
    11:'BCB',
    12:'CBC',
    13:'CAC',
    14:'ABC',
    15:'CBC',
    16:'ACC',
    17:'CCC'
}
R=[[-1 for i in range(17)] for j in range(17)]      #decide the switch between any two states
for i in range(17):
    i += 1
    for j in range(17):
        j += 1
        if i!=j:
            a=''
            b=''
            for a in ['A', 'B', 'C']:
                for k in ['A', 'B', 'C']:
                    if states[i][0]==a and k!=a and (k+states[i][1]+states[i][2])==states[j]:
                        R[i - 1][j - 1] = 0
            if states[i][1]!=states[i][0]:
                for a in ['A','B','C']:
                    for k in ['A','B','C']:
                        if states[i][0]==a and k!=a and k!=states[i][1] and (states[i][0]+k+states[i][2])==states[j]:
                            R[i - 1][j - 1] = 0
            if states[i][1]==states[i][0] and states[i][2]!=states[i][0]:
                for a in ['A', 'B', 'C']:
                    if a!=states[i][0] and a!=states[i][2] and (states[i][0]+states[i][1]+a)==states[j]:
                        R[i - 1][j - 1] = 0
R[15][16]=100
R[16][16]=100
print('R matrix:')
for i in range(17):
    print(R[i])

def getMaxQ(state):
    return max(Q[state, :])
def QLearning(state):
    curAction = None
    for action in range(17):
        if(R[state][action] == -1):
                Q[state, action]=0
        else:
                curAction = action
                Q[state,action]=R[state][action]+GAMMA * getMaxQ(curAction)

count=0
while count<1000:
    for i in range(17):
        QLearning(i)
    count+=1

Q=Q/5
for i in range(17):
    for j in range(17):
        Q[i][j]=int(Q[i][j])
print('Q matrix:')
for i in range(17):
    print(Q[i])

i=1                                 # get the road to the target
print('states:%d '%i+states[i])
while i!=17:
    for j in range(17):
        if Q[i-1][j]==max(Q[i-1]):
            i=j+1
            print('states:%d '%i+states[i])