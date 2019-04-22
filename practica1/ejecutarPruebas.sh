#!/bin/bash

make -s
if [ ! -d ficherosPrueba ]; then
    mkdir ficherosPrueba
fi
cd ficherosPrueba

echo "Comprimir/Descomprimir 100 ficheros de 10KB, Distribucion normal"
time for i in  $(seq 1 100)
do
    ../genFichero
    cp fichRandNormal.pr fichRandNormalCP.pr
    ../huf -c fichRandNormal.pr
    ../huf -d fichRandNormal.pr
    diff fichRandNormal.pr fichRandNormalCP.pr

    if [ $? -ne 0 ]; then
        echo "Error en el fichero"
        exit 1
    fi
done

for i in  $(seq 1 10)
do
    ../genFichero 2
    echo "Comprimiendo fichero generado de tam" 
    ls -lh fichRandNormal.pr
    cp fichRandNormal.pr fichRandNormalCP.pr
    time ../huf -c fichRandNormal.pr
    echo "Tamaño de comprensión"
    ls -lh fichRandNormal.pr.huf
    echo "descomprimiendo"
    ../huf -d fichRandNormal.pr
    diff fichRandNormal.pr fichRandNormalCP.pr

    if [ $? -ne 0 ]; then
        echo "Error en el fichero"
        exit 1
    fi
done

for i in  $(seq 1 20)
do
    dd if=/dev/urandom of=fichRand.pr bs=8388608 count=1
    echo "Comprimiendo fichero generado de tam" 
    ls -lh fichRand.pr
    cp fichRand.pr fichRandCP.pr
    time ../huf -c fichRand.pr
    echo "Tamaño de comprensión"
    ls -lh fichRand.pr.huf
    echo "descomprimiendo"
    ../huf -d fichRand.pr
    diff fichRand.pr fichRandCP.pr

    if [ $? -ne 0 ]; then
        echo "Error en el fichero"
        exit 1
    fi
done


cd ..
rm -r ficherosPrueba
make -s clear