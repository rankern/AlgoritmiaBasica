#include "iostream"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include "clases/heap.hpp"
#include "clases/pedido.hpp"
#include "clases/problema.hpp"
using namespace std;

void resolverProblema(Problema &tren, Pedido pedidos[] ){

}


int main(int argc, char *argv[]){
	string fichEnt="pruebas.txt";
	string fichSal="fiche.txt";
	ifstream fEnt;
	ofstream fSal;
	int beneficioMax=0;//U 
	int capMax;
	int numPedidos;
	int numEstacionFinal;
	int pedidosLeidos;
	clock_t start, end;

	fEnt.open(fichEnt);
	
	if(fEnt.is_open()){
		fSal.open(fichSal);
			if(fSal.is_open()){
		
		int estSalida;
		int estLlegada;
		int numPasajeros;
		fEnt>>capMax>>numEstacionFinal>>numPedidos;
		cout<<capMax<<numEstacionFinal<<numPedidos<<endl;
		Problema tren(capMax, numEstacionFinal, numPedidos);
		Pedido pedidos[numPedidos];
		while(!fEnt.eof()){
			if(capMax!=0 && numEstacionFinal!=0 && numPedidos!=0){
				start = clock();
				pedidosLeidos=0;
				while(pedidosLeidos<numPedidos){
					
					fEnt>>estSalida>>estLlegada>>numPasajeros;
					cout<<estSalida<<estLlegada<<numPasajeros<<endl;
					pedidos[pedidosLeidos] = Pedido(numPasajeros, estSalida, estLlegada);
					pedidosLeidos++;
					//Añadir a montículo
					//crear Nodo()

				}
				end= clock(); 
				int tiempo=(end - start);
				fSal<<beneficioMax<<" "<<tiempo<<"\n";
			}
				//Leer otro bloque
			fEnt>>capMax>>numEstacionFinal>>numPedidos;

		}

		  fSal.close();
			}
			else{
				cout<<"No se ha podido abrir el fichero de salida"<<endl;
			}
		  fEnt.close();
		}
	

	else{
		cout<<"No se ha podido abrir el fichero de entrada"<<endl;
	}

	return 0;
}