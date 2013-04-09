#! /bin/bash
rm -rf Temp5.csv
while IFS=, read col1 col2 col3 col4 col5
do
    if [ "$col2" = " 42" ];
    then
    	echo $col3 >> ../data/Temp5.csv
    fi	
done < "../data/lab05_g14_data.csv"
