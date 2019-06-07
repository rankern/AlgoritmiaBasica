#!/bin/bash

make -s
if [ ! -d ficherosPrueba ]; then
    mkdir ficherosPrueba
fi
cd ficherosPrueba
#echo "$(ls ./ficherosPrueba)"
for f in $(ls ./)
do
    echo "Comprimiendo fichero $(ls -lh $f)"
    cp "$f" "copia.pr"
    time ../huf -c copia.pr v
    echo "Descomprimiendo"
    time ../huf -d copia.pr
    echo "comparando"
    diff copia.pr "$f"
    echo "--------------------------------"
    
done
rm copia.pr
rm *.huf


cd ..
#rm -r ficherosPrueba
#make -s clear