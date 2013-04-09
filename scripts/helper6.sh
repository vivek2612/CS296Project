#! /bin/bash
rm -rf ../data/Temp6.csv
declare -a squares
declare -a sums
A=INIT
B=INIT
C=INIT
j=0;
for i in `seq 1 100`
do
	squares[$i]=0;
	sums[$i]=0;
done
while IFS=, read col1 col2 col3 col4 col5
do
    squares[`expr $col2`]=$(echo "${squares[`expr $col2`]}+$col3*$col3" | bc);
    sums[`expr $col2`]=$(echo "${sums[`expr $col2`]}+$col3" | bc);
    j=$(echo "$j+1" | bc)
    #echo $j
done < "../data/lab05_g14_data.csv"

for i in `seq 1 100`
do
	A=$i
	B=$(echo "scale=10;${sums[$i]}/100.0" | bc)
	C=$(echo "scale=10;sqrt(${squares[$i]}/100.0-(${sums[$i]}/100.0)*(${sums[$i]}/100.0))" | bc)
	echo "$A,$B,$C" >> ../data/Temp6.csv
	#echo "$A,$B,$C"
done
