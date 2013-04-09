#! /bin/bash
CSV="lab05_g14_data.csv"
for i in `seq 1 100`
	do
	for j in `seq 1 100`
	do
		"../bin/RubeGoldbergMachinePlots" $j | sed -e '/^ *$/d' | sed -e 's/[A-Za-z :]*\([0-9.]*\)[a-z ]*/\1,/' | sed -e ':a;N;$!ba;s/\n/ /g' | sed -e 's/,$//' | sed -e "s/\([0-9, .]*\)/$i, \1/" >> ../data/$CSV
	done
done
