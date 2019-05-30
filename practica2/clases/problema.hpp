#pragma once
#include <iostream>
#include "pedido.hpp"


using namespace std;
class Problema{
	private:
	int maxCapacidad = 0;
	int numEstaciones = 0;
	int numPedidos = 0;
	int beneficioAcum = 0;
	int pedidoActual = 0;
	int tramos[7] = {0,0,0,0,0,0,0};
	public:
		Problema(){}
		Problema(int _cap, int _estaciones, int _pedidos)
			: maxCapacidad(_cap), numEstaciones(_estaciones), numPedidos(_pedidos){}

		Problema(int _cap, int _estaciones, int _pedidos, int _pedidoActual, int _beneficioAcum, int _tramos[])
			: maxCapacidad(_cap), numEstaciones(_estaciones), numPedidos(_pedidos), 
				pedidoActual(_pedidoActual), beneficioAcum(_beneficioAcum){
					for(int i = 0; i < 7; i++){
						tramos[i] = _tramos[i];
					}
				}	
		
		Problema clone(){
			pedidoActual++;
			return Problema(maxCapacidad, numEstaciones, numPedidos, pedidoActual-1, beneficioAcum, tramos);
		}
		
		int beneficioActual(){return beneficioAcum;}

		bool anyadir(Pedido &p){
			this->pedidoActual++;
			bool ok = true;
			for(int i = p.estacionIni();i < p.estacionFin() && ok; i++){
				tramos[i] += p.billetes();
				ok = tramos[i] <= maxCapacidad;
			}
			beneficioAcum += p.beneficioPedido();
			return ok;
		}
		/** indice del vector tramos con mayor cardinal de gente*/
		int max(int replica[],int desde, int hasta){
			int mGente = replica[desde];
			int indice = desde;
			for(int i = desde; i < hasta; i++){
				if(replica[i] > mGente){
					mGente = replica[i];
					indice = i;
				}
			}
			return indice;
		}

		/* void costeYcota(Pedido pedidos[], int numPedidos, double &cota, double &coste) {
			cota = this->beneficioAcum;
			coste = this->beneficioAcum;
			int replicaCota[7] = {this->tramos[0],this->tramos[1],this->tramos[2],this->tramos[3],this->tramos[4],this->tramos[5],this->tramos[6] };
			int replicaCoste[7] = {this->tramos[0],this->tramos[1],this->tramos[2],this->tramos[3],this->tramos[4],this->tramos[5],this->tramos[6] };
			for(int i = this->pedidoActual; i < numPedidos; i++){
				int maxCoste = replicaCoste[pedidos[i].estacionIni()];
				int maxCota = replicaCota[pedidos[i].estacionIni()];
				bool viableCota = true;
				//Calcular tramo ocurrente con mayor num pasajeros
				for(int j = pedidos[i].estacionIni()+1; j < pedidos[i].estacionFin(); j++){
					if(replicaCoste[j] > maxCoste)
						maxCoste = replicaCoste[j];
					viableCota &= (this->maxCapacidad - replicaCota[j] <= pedidos[i].billetes());
				}
				int nuevosPasajeros = pedidos[i].billetes();
				if(maxCoste < nuevosPasajeros){
					int nuevosPasajeros =  this->maxCapacidad - maxCoste;
					
				}
				coste = coste + (nuevosPasajeros * (pedidos[i].estacionFin() - pedidos[i].estacionIni()));
				for(int j = pedidos[i].estacionIni(); j < pedidos[i].estacionFin(); j++){
					replicaCoste[j] += nuevosPasajeros;
				}
				if(viableCota){
					cota += pedidos[i].beneficioPedido();
					for(int j = pedidos[i].estacionIni(); j < pedidos[i].estacionFin(); j++){
						replicaCota[j] += pedidos[i].billetes();
					}
				}

			}
			cota = 0 - cota;
			coste = 0 - coste;
		} */


		double costeEstimado(Pedido pedidos[], int numPedidos){
			double coste = this->beneficioAcum;
			int replica[7] = {this->tramos[0],this->tramos[1],this->tramos[2],this->tramos[3],this->tramos[4],this->tramos[5],this->tramos[6] };
			for(int i = this->pedidoActual; i < numPedidos; i++){
				int maxPasajeros = replica[this->max(replica, pedidos[i].estacionIni(), pedidos[i].estacionFin())];

				int nuevosPasajeros = pedidos[i].billetes();
				int beneficio = pedidos[i].beneficioPedido();
				if(maxPasajeros < nuevosPasajeros){
					int nuevosPasajeros =  this->maxCapacidad - maxPasajeros;
					beneficio = nuevosPasajeros * (pedidos[i].estacionFin() - pedidos[i].estacionIni());
				}
				coste = coste + beneficio;
				for(int j = pedidos[i].estacionIni(); j < pedidos[i].estacionFin(); j++){
					replica[j] += nuevosPasajeros;
				}
			}
			return 0 - coste;
		}

		int cota_mejor(Pedido pedidos[], int numPedidos){
			int cota = this->beneficioAcum;
			int replica[7] = {this->tramos[0],this->tramos[1],this->tramos[2],this->tramos[3],this->tramos[4],this->tramos[5],this->tramos[6] };
			for(int i = this->pedidoActual; i < numPedidos; i++){
				if(replica[this->max(replica,pedidos[i].estacionIni(), pedidos[i].estacionFin())] < pedidos[i].billetes()){
					continue;
				}
				for(int j = pedidos[i].estacionIni(); j < pedidos[i].estacionFin(); j++){
					replica[j] += pedidos[i].billetes();
				}
				cota += pedidos[i].billetes();
			}
			return 0 - cota;
		}

		void incrementarPedido(){pedidoActual++;}

		int siguientePedido(){return this->pedidoActual;}

		bool operator >=(Problema& p) {
			return this->beneficioActual() >= p.beneficioActual();
		}

		bool operator <=(Problema& p) {
			return this->beneficioActual() <= p.beneficioActual();
		}
		bool operator >(Problema& p) {
			return this->beneficioActual() > p.beneficioActual();
		}

		bool operator <(Problema& p) {
			return this->beneficioActual() < p.beneficioActual();
		}		
};