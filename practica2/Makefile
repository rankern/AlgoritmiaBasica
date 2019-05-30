CC = g++
CFLAGS = -O3

all: transporte 

transporte: main.cpp ./clases/heap.hpp ./clases/pedido.hpp ./clases/problema.hpp
	$(CC) main.cpp -o transporte ${CFLAGS}

clear:
	rm -f -r transporte
