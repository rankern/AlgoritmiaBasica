#!/bin/bash

aImprimir=' ';
aImprimiAux=$aImprimir;
if [ -f $1 ]
then
for i in $(seq 32 256)
do 
	for j in $(seq 1 5000)
	do
		printf "\\$(printf %o $i)" >>$1
	done
done
fi

exit 1