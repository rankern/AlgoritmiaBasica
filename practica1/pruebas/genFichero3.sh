#!/bin/bash

aImprimir=' ';
aImprimiAux=$aImprimir;
for i in $(seq 1 256)
do 
	for j in $(seq 1 5000)
	do
		printf "\\$(printf %o $i)" >>$1
	done
done