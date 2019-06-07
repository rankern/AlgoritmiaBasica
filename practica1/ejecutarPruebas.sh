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
    echo "Comparando"
    diff copia.pr "$f"
    if [ $? -eq 0 ]
    then
        echo "Descompresion correcta"
    fi
    echo "--------------------------------"
    
done
rm copia.pr
rm *.huf


cd ..
#rm -r ficherosPrueba
#make -s clear