#include "iostream"
#include <stdio.h>  /* printf, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <fstream>
#include "clases/heap.hpp"
#include "clases/pedido.hpp"
#include "clases/problema.hpp"
using namespace std;

void resolverProblema(Pedido pedidos[], Heap<Problema> &nodos, int numPedidos){
	double U_min = 0;
	int mejorBenefico = 0;
	while (!nodos.isEmpty()){
		Problema *noCogido = nodos.pop();
		Problema cogido = noCogido->clone(); //clone incrementa en 1 el numPedido de noCogido
		if(cogido.anyadir(pedidos[noCogido->siguientePedido()])){
			double coste = cogido.costeEstimado(pedidos, numPedidos);
			if(U_min >= coste){
				int cota = cogido.cota_mejor(pedidos, numPedidos);
				if((cota == coste || cogido.siguientePedido() == numPedidos) && (0-cota) > mejorBenefico){
					/** HOJA*/
					mejorBenefico = 0-cota;
				}else{
					nodos.add(&cogido);
				}
				if(cota < U_min){
					U_min = cota;
				}
			}
			 coste = noCogido->costeEstimado(pedidos, numPedidos);
			if(U_min >= coste){
				int cota = noCogido->cota_mejor(pedidos, numPedidos);
				if((cota == coste || noCogido->siguientePedido() == numPedidos) && (0-cota) > mejorBenefico){
					/** HOJA*/
					mejorBenefico = 0-cota;
				}else{
					nodos.add(noCogido);
				}
				if(cota < U_min){
					U_min = cota;
				}
			}
		}
	}
}

int main(int argc, char *argv[]){
	string fichEnt = "pruebas.txt";
	string fichSal = "resultado.txt";
	if(argc == 3){
		fichEnt = string(argv[1]);
		fichSal = string(argv[2]);
	}
	ifstream fEnt;
	ofstream fSal;
	int beneficioMax = 0; //U
	int capMax;
	int numPedidos;
	int numEstacionFinal;
	int pedidosLeidos;
	clock_t start, end;

	fEnt.open(fichEnt);

	if (fEnt.is_open()){
		fSal.open(fichSal);
		if (fSal.is_open()){

			int estSalida;
			int estLlegada;
			int numPasajeros;
			fEnt >> capMax >> numEstacionFinal >> numPedidos;
			cout << capMax << numEstacionFinal << numPedidos << endl;
			Problema tren(capMax, numEstacionFinal, numPedidos);
			Pedido pedidos[numPedidos];
			Heap<Problema> frontera;
			frontera.add(&tren);
			while (!fEnt.eof()){
				if (capMax != 0 && numEstacionFinal != 0 && numPedidos != 0){
					start = clock();
					pedidosLeidos = 0;
					while (pedidosLeidos < numPedidos){

						fEnt >> estSalida >> estLlegada >> numPasajeros;
						cout << estSalida << estLlegada << numPasajeros << endl;
						pedidos[pedidosLeidos] = Pedido(numPasajeros, estSalida, estLlegada);
						pedidosLeidos++;
					}
					resolverProblema(pedidos, frontera, numPedidos);
					end = clock();
					int tiempo = (end - start);
					fSal << beneficioMax << " " << tiempo << "\n";
				}
				//Leer otro bloque
				fEnt >> capMax >> numEstacionFinal >> numPedidos;
			}
			fSal.close();
		}else{
			cout << "No se ha podido abrir el fichero de salida" << endl;
		}
		fEnt.close();
	}else{
		cout << "No se ha podido abrir el fichero de entrada" << endl;
	}

	return 0;
}