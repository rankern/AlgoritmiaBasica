CC = g++
CFLAGS = -O3

all: huf genFichero

genFichero: ./pruebas/genFichero.cpp
	$(CC) ./pruebas/genFichero.cpp -o genFichero ${CFLAGS}

huf: main.cpp trie.hpp heap.hpp escritura.hpp 
	$(CC) main.cpp -o huf ${CFLAGS}

clear:
	rm -f -r huf *.huf genFichero ficherosPrueba
