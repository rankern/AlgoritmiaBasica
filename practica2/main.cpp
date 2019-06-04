#include "iostream"
#include <stdio.h>  /* printf, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <fstream>
#include "clases/heap.hpp"
#include "clases/pedido.hpp"
#include "clases/problema.1.hpp"
using namespace std;
#define debug
/**
 * Devuelve true si y solo si no es hoja y hay que insertarlo en monticulo
 */ 
bool calculosCotaYCoste(int &mBeneficio, double &U_min, Problema *p, int numPedidos, Pedido pedidos[]){
	bool insertar = false;
	//double coste = p->costeEstimado(pedidos, numPedidos);
	double coste = p->cEstim();
	#ifdef debug
		cout << " Coste: " << coste << ";  Cota: " << p->cota_mejor(pedidos, numPedidos);
	#endif

	if(U_min >= coste){
		int cota = p->cota_mejor(pedidos, numPedidos);
		if( cota == coste ||  p->siguientePedido() == numPedidos - 1){
			/** HOJA*/
			if((0-coste) > mBeneficio){
				mBeneficio = (0 -coste);
			}
			if(cota < U_min){
				U_min = cota;
			}
		}else{
			insertar = true;
		}
	}
	return insertar;
}


int resolverProblema(Pedido pedidos[], Heap<Problema> &nodos, int numPedidos){
	double U_min = 0;
	int mejorBenefico = 0;
	while (!nodos.isEmpty()){
		Problema *noCogido = nodos.pop();
		Problema *cogido = noCogido->clone(pedidos, numPedidos); //clone incrementa en 1 el numPedido de noCogido
		#ifdef debug
			cout << "Cogiendo pedido " << cogido->siguientePedido()+1 << " ";

		#endif
		
		if(cogido->anyadir(pedidos[noCogido->siguientePedido()], pedidos, numPedidos)){
			#ifdef debug
				cout << " Pedido VIABLE";
			#endif
			if(calculosCotaYCoste(mejorBenefico, U_min, cogido,numPedidos, pedidos)){
				nodos.add(cogido);
				#ifdef debug
					cout << " Pedido se anyade" << endl;
				#endif
			}else{
			#ifdef debug
				cout << " Pedido NO se anyade\n";
			#endif
				delete cogido;
			}
			
		}else{
			#ifdef debug
				cout << " Pedido NO viable" << endl;
			#endif
			delete cogido;
		}
		#ifdef debug
		cout << "NO Cogiendo pedido " << noCogido->siguientePedido() << " ";
		#endif
		if(calculosCotaYCoste(mejorBenefico, U_min, noCogido,numPedidos, pedidos)){
				nodos.add(noCogido);
				#ifdef debug
					cout << " Pedido se anyade" << endl;
				#endif
		}else{
			delete noCogido;
			#ifdef debug
				cout << " Pedido NO viable" << endl;
			#endif
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
					//std::cout << " " << estSalida << " "  << estLlegada << " " << numPasajeros << endl;
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
				#ifdef debug
				if(numProblemas == 3786){
					volatile int a = 2;
					beneficioMax = resolverProblema(pedidos, frontera, numPedidos);
					fSal << beneficioMax << " " << numPedidos << " " << numEstacionFinal << "\n";
					std::cout << "----------------------------------------\n" << beneficioMax << " "
						 "\n" << "----------------------------------------\n";
				}
				#else
					beneficioMax = resolverProblema(pedidos, frontera, numPedidos);
				#endif
				
				end = clock();
				int tiempo = (end - start);
				#ifndef debug
				fSal << beneficioMax << " " << tiempo << " " << numPedidos << " " << numEstacionFinal << "\n";
				std::cout << "----------------------------------------\n" << beneficioMax << " "
					 << tiempo <<  "\n" << "----------------------------------------\n";
				//Leer otro bloque
				#endif
				numProblemas++;
				
				fEnt >> capMax >> numEstacionFinal >> numPedidos;
				#ifndef debug
				std::cout << capMax << " " << numEstacionFinal << " " << numPedidos << endl;
				#endif
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