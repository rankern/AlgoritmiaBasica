#!/bin/bash

aImprimir=0;
if [ $# -eq 0 ]
then
	echo "Uso: genFichero2.sh fichero"
	exit 
fi

cat /dev/null > $1	
for i in $(seq 0 255)
do 
	for j in $(seq 1 1000)
	do
		echo "$i" >> $1
	done

done

exit 1