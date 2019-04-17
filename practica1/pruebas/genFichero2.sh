#!/bin/bash

aImprimir=0;
if [ -f $1 ]
	then
cat /dev/null > $1	
for i in $(seq 1 256)
do 
	for j in $(seq 1 1000)
	do
		echo "$i" >> $1
	done

done
fi

exit 1