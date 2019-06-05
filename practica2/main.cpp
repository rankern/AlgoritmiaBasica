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
bool calculosCotaYCoste(int &mBeneficio, double &U_max, Problema *p, int numPedidos, Pedido pedidos[]){
	bool insertar = false;
	//double coste = p->costeEstimado(pedidos, numPedidos);
	double coste = p->cEstim();
	if(U_max <= coste){
		int cota =mBeneficio;
		if( cota == coste ||  p->siguientePedido() == numPedidos - 1){
			/** HOJA*/
			if(coste > mBeneficio){
				mBeneficio = coste;
			}
		}else{
			insertar = true;
		}
		if(cota > U_max){
			U_max = cota;
		}
	}else{
		volatile int a = 1;
	}
	return insertar;
}


int resolverProblema(Pedido pedidos[], Heap<Problema> &nodos, int numPedidos){
	double U_max = 0;
	int beneficio = 0;
	while (!nodos.isEmpty()){
		Problema *noCogido = nodos.pop();
		Problema *cogido = noCogido->clone(pedidos, numPedidos); //clone incrementa en 1 el numPedido de noCogido
		
		if(cogido->anyadir(pedidos[noCogido->siguientePedido()], pedidos, numPedidos)){
			if(calculosCotaYCoste(beneficio, U_max, cogido,numPedidos, pedidos)){
				nodos.add(cogido);
			}
		}else{
			delete cogido;
		}
		if(calculosCotaYCoste(beneficio, U_max, noCogido,numPedidos, pedidos)){
				nodos.add(noCogido);
		}else{
			delete noCogido;
		}
	}
	return beneficio;
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
	int numProblemas =1;
	fEnt.open(fichEnt);

	if (fEnt.is_open()){
		fSal.open(fichSal);
		if (fSal.is_open()){

			fEnt >> capMax >> numEstacionFinal >> numPedidos;
			std::cout << capMax << " " << numEstacionFinal << " " << numPedidos << endl;
			while (!fEnt.eof()){
				if (capMax == 0 && numEstacionFinal == 0 && numPedidos == 0){
					break;
				}
				//definir variables variables problema
				Problema * tren = new Problema(capMax, numEstacionFinal, numPedidos);
				Heap<Problema> frontera;
				Pedido pedidos[numPedidos];
				Heap<Pedido> ordenacionInicial;
				if(numPedidos > 0){
					frontera.add(tren);
				}
				//Leer pedidos del probelma
				pedidosLeidos = 0;
				while (!fEnt.eof() && pedidosLeidos < numPedidos){
					int estSalida, estLlegada, numPasajeros;
					fEnt >> estSalida >> estLlegada >> numPasajeros;
					std::cout << " " << estSalida << " "  << estLlegada << " " << numPasajeros << endl;
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
				std::cout << "----------------------------------------\n" << beneficioMax << " "
					 << tiempo << "\n" << "----------------------------------------\n";
				//Leer otro bloque
				numProblemas++;
				if(numProblemas == 167){
					volatile int a = 2;
				}
				fEnt >> capMax >> numEstacionFinal >> numPedidos;
				std::cout << capMax << " " << numEstacionFinal << " " << numPedidos << endl;
			}
			fSal.close();
		}else{
			std::cout << "No se ha podido abrir el fichero de salida" << endl;
		}
		fEnt.close();
	}else{
		std::cout << "No se ha podido abrir el fichero de entrada" << endl;
	}

	return 0;
}