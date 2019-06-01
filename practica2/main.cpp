#include "iostream"
#include <stdio.h>  /* printf, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <fstream>
#include "clases/heap.hpp"
#include "clases/pedido.hpp"
#include "clases/problema.hpp"
using namespace std;

/**
 * Devuelve true si y solo si no es hoja y hay que insertarlo en monticulo
 */ 
bool calculosCotaYCoste(int &mBeneficio, double &U_min, Problema *p, int numPedidos, Pedido pedidos[]){
	bool insertar = false;
	double coste = p->costeEstimado(pedidos, numPedidos);
	if(U_min >= coste){
		int cota = p->cota_mejor(pedidos, numPedidos);
		if(cota == coste || p->siguientePedido() == numPedidos - 1){
			/** HOJA*/
			if((0-coste) > mBeneficio){
				mBeneficio = p->beneficioActual();
			}
		}else{
			insertar = true;
		}
		if(cota < U_min){
			U_min = cota;
		}
	}
	return insertar;
}


int resolverProblema(Pedido pedidos[], Heap<Problema> &nodos, int numPedidos){
	double U_min = 0;
	int mejorBenefico = 0;
	while (!nodos.isEmpty()){
		Problema *noCogido = nodos.pop();
		Problema *cogido = noCogido->clone(); //clone incrementa en 1 el numPedido de noCogido
		
		if(cogido->anyadir(pedidos[noCogido->siguientePedido()])){
			if(calculosCotaYCoste(mejorBenefico, U_min, cogido,numPedidos, pedidos)){
				nodos.add(cogido);
			}
		}
		if(calculosCotaYCoste(mejorBenefico, U_min, noCogido,numPedidos, pedidos)){
				nodos.add(noCogido);
		}
	}
	return mejorBenefico;
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

			fEnt >> capMax >> numEstacionFinal >> numPedidos;
			cout << capMax << " " << numEstacionFinal << " " << numPedidos << endl;
			while (!fEnt.eof()){
				if (capMax == 0 && numEstacionFinal == 0 && numPedidos == 0){
					break;
				}
				//definir variables variables problema
				Problema tren(capMax, numEstacionFinal, numPedidos);
				Heap<Problema> frontera;
				Pedido pedidos[numPedidos];
				Heap<Pedido> ordenacionInicial;
				if(numPedidos > 0){
					frontera.add(&tren);
				}
				//Leer pedidos del probelma
				pedidosLeidos = 0;
				while (!fEnt.eof() && pedidosLeidos < numPedidos){
					int estSalida, estLlegada, numPasajeros;
					fEnt >> estSalida >> estLlegada >> numPasajeros;
					cout << " " << estSalida << " "  << estLlegada << " " << numPasajeros << endl;
					Pedido * p = new Pedido(numPasajeros, estSalida, estLlegada);
					ordenacionInicial.add(p);
					pedidosLeidos++;
				}

				int i = 0;
				while(!ordenacionInicial.isEmpty()){
					pedidos[i] = *ordenacionInicial.pop();
					i++;
				}
				start = clock();
				beneficioMax = resolverProblema(pedidos, frontera, numPedidos);
				end = clock();
				int tiempo = (end - start);
				fSal << beneficioMax << " " << tiempo << "\n";
				cout << "----------------------------------------\n" << beneficioMax << " "
					 << tiempo << "\n" << "----------------------------------------\n";
				//Leer otro bloque
				fEnt >> capMax >> numEstacionFinal >> numPedidos;
				cout << capMax << " " << numEstacionFinal << " " << numPedidos << endl;
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