#! /usr/bin/python3
import os
import subprocess
import re

filecsv = open("../data/dataFile.csv",'a+')
executable = "../bin/RubeGoldbergMachinePlots"
for i in range(1,101):
	for j in range(1,101):
		args = []
		args = [executable,str(j)]
		process = subprocess.Popen(args,stdout=subprocess.PIPE)
		process.wait()
		output = process.stdout.read()
		temp = re.findall(r"[0-9.]+",str(output),re.S)
		filecsv.write(str(i)+",")
		for num in temp:
			filecsv.write(num+",")
		filecsv.write("\n")
