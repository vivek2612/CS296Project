#! /usr/bin/python3
import numpy as np
import matplotlib.pyplot as plt
from math import fabs

f=open("../data/dataFile.csv")
content=f.readlines()
f.close()
# rerun number, iteration value step time, collision time, velocity time, position time, loop time.
rerun,iteration,step,collision,velocity,position,loop=[],[],[],[],[],[],[]
cols=[rerun,iteration,step,collision,velocity,position,loop]
for line in content:
	ele=line.split(',')
	for index,value in enumerate(ele[:(len(ele)-1)]):
		if index==0 or index==1:
			cols[index].append(int(value))
		else:
			cols[index].append(float(value))

X=[x+1 for x in range(100)]
sums1=[float(0) for x in range(100)] #step
sums2=[float(0) for x in range(100)] #loop
sums3=[float(0) for x in range(100)] # collision
sums4=[float(0) for x in range(100)] #velocity
sums5=[float(0) for x in range(100)] #position

for index,value in enumerate(iteration):
	sums1[value-1]+=step[index]
	sums2[value-1]+=loop[index]
	sums3[value-1]+=collision[index]
	sums4[value-1]+=velocity[index]
	sums5[value-1]+=position[index]

avgs=[x/100.0 for x in sums1]
avgl=[x/100.0 for x in sums2]
avgc=[x/100.0 for x in sums3]
avgv=[x/100.0 for x in sums4]
avgp=[x/100.0 for x in sums5]

plt.xlabel("Iteration Value")
plt.ylabel("Average Time(ms)")
plt.title("Step time&LoopTime averaged over ReRuns v/s Iteration Value")
plt.plot(X,avgs,'mo',label="StepTime")
plt.plot(X,avgl,'go',label="LoopTime")
plt.legend(loc='upper right')
plt.savefig("../plots/g14_plot01.png")
plt.clf();

plt.xlabel("Iteration Value")
plt.ylabel("Average Time(ms)")
plt.title("Step,collision,velocity,position Time averaged over ReRuns v/s Iteration Value ")
plt.plot(X,avgs,'mo',label="StepTime")
plt.plot(X,avgc,'go',label="collisionTime")
plt.plot(X,avgv,'bo',label="velocityTime")
plt.plot(X,avgp,'yo',label="positionTime")
plt.legend(loc='upper right')
plt.savefig("../plots/g14_plot02.png")
plt.clf()

sums1=[float(0) for x in range(100)] #step
sums2=[float(0) for x in range(100)] #loop
sums3=[float(0) for x in range(100)] # collision
sums4=[float(0) for x in range(100)] #velocity
sums5=[float(0) for x in range(100)] #position

for index,value in enumerate(rerun):
	sums1[value-1]+=step[index]
	sums2[value-1]+=loop[index]
	sums3[value-1]+=collision[index]
	sums4[value-1]+=velocity[index]
	sums5[value-1]+=position[index]
avgs=[x/100.0 for x in sums1]
avgl=[x/100.0 for x in sums2]
avgc=[x/100.0 for x in sums3]
avgv=[x/100.0 for x in sums4]
avgp=[x/100.0 for x in sums5]


plt.xlabel("RerunValue")
plt.ylabel("Average Time(ms)")
plt.title("Step time&LoopTime averaged over Iterations v/s RerunValue ")
plt.plot(X,avgs,'mo',label="StepTime")
plt.plot(X,avgl,'go',label="LoopTime")
plt.legend(loc='upper right')
plt.savefig("../plots/g14_plot03.png")
plt.clf();

plt.xlabel("RerunValue")
plt.ylabel("Average Time(ms)")
plt.title("Step,collision,velocity,position Time averaged over Iterations v/s RerunValue ")
plt.plot(X,avgs,'mo',label="StepTime")
plt.plot(X,avgc,'go',label="collisionTime")
plt.plot(X,avgv,'bo',label="velocityTime")
plt.plot(X,avgp,'yo',label="positionTime")
plt.legend(loc='upper right')
plt.savefig("../plots/g14_plot04.png")
plt.clf()

data=[]
def cumSum(data):
	cumdata=[]
	for i,val in enumerate(data):
		if i==0:
			cumdata.append(data[0])
		else :
			cumdata.append(cumdata[-1]+val)
	return cumdata
for i in range(100):
	data.append(step[i*100 + 41])
plt.xlabel("Step Time")
plt.ylabel("Frequency",color='m')
plt.title("Frequency Plot of stepTime variation with Reruns")
p=plt.hist(data,bins=60,color='m')
y=cumSum(p[0])
plt.twinx() #this is done to change the y-axis 
plt.ylabel("CumFrequency",color='r')
plt.plot(p[1][:-1],y,'g-',linewidth=1.5)
plt.legend(loc='upper right')
plt.show()
plt.savefig("../plots/g14_plot06.png")
plt.clf()



X=[x+1 for x in range(100)]
sums=[float(0) for x in range(100)]
sumsq=[float(0) for x in range(100)]

for index,value in enumerate(iteration):
	sums[value-1]+=step[index]
	sumsq[value-1]+=step[index]**2
avgs=[x/100.0 for x in sums]
avgsq=[(x/100.0)**0.5 for x in sumsq]
deviation=[fabs(x-y) for x,y in zip(avgs,avgsq)]
plt.xlabel("Iteration Value")
plt.ylabel("Time(ms)")
plt.title("step time over ReRuns v/s Iteration values with error bars")
plt.errorbar(X, avgs, yerr=deviation, fmt='ro',label="stepTime with errorbars",color='purple')
plt.legend(loc='upper right')
plt.savefig("../plots/g14_plot05.png")
plt.clf()
