import numpy as np
from sklearn.cross_validation import train_test_split
data=np.loadtxt("D:\\1010.txt")  # use np to get data, having changed rsv file to txt file
train,test=train_test_split(data,test_size=0.1,random_state=42)
print('length of train data:%d'%len(train))
print('length of test  data:%d'%len(test))
lentrain=len(train)
lentest=len(test)
N0=0  # negative data of train data
N1=0  # positive  data of train data
for i in range(lentrain):
	if train[i][8]==0:
		N0=N0+1
	else:
		N1=N1+1
print('negtive data of train data:%d'%(N0))
print('posive  data of train data:%d'%(N1))
k=100
length=[[0 for x in range(2)] for y in range(lentrain)]
testresult=[0 for y in range(lentest)]
TP=0
FP=0
TN=0
FN=0
for j in range(lentest):  # test all test data
	if j*1.25>lentest:  # print the schedule
		print('going on:80%')
	elif j*2>lentest:
		print('going on:50%')
	elif j*3.33>lentest:
		print('going on:30%')
	elif j*10>lentest:
		print('going on:10%')
	for i in range(lentrain):  # compute all lengths between train data and current test data
		length[i][0]=(train[i][0]-test[j][0])**2+\
					 (train[i][1]-test[j][1])**2+\
					 (train[i][2]-test[j][2])**2+ \
					 (train[i][3] - test[j][3]) ** 2 + \
					 (train[i][4] - test[j][4]) ** 2 + \
					 (train[i][5] - test[j][5]) ** 2 + \
					 (train[i][6] - test[j][6]) ** 2 + \
					 (train[i][7] - test[j][7]) ** 2
		length[i][1]=train[i][8]
	length=sorted(length)
	n0=0
	n1=0
	for i in range(lentrain):  # find the k nearest neighbor
		if length[i][1]==0:
			n0=n0+1
		if length[i][1]==1:
			n1=n1+1
		if int((n0*(N0+N1))/N0)>=k:  # adjust n0 according to N0 and N1
			testresult[j]=0
			if test[j][8]==1:
				TN=TN+1
			else:
				FN=FN+1
			break
		if int((n1*(N0+N1))/N1)>=k:  # adjust n1 according to N0 and N1
			testresult[j]=1
			if test[j][8]==0:
				FP=FP+1
			else:
				TP=TP+1
			break
print('FN:%d'%FN)  # print the result
print('TP:%d'%TP)
print('TN:%d'%TN)
print('FP:%d'%FP)
P=TP/(TP+FP)
R=TP/(TP+TN)
F=(P*R*2)/(P+R)
print('F:%f'%F)