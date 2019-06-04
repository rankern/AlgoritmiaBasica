#pragma once
#include <iostream>
#include "pedido.hpp"


using namespace std;
class Problema{
	private:
	double costeEst = 0;
	int maxCapacidad = 0;
	int numEstaciones = 0;
	int numPedidos = 0;
	int beneficioAcum = 0;
	int pedidoActual = -1;
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
		
		Problema *clone(Pedido pedidos[], int numPedido){
			pedidoActual++;
			Problema *p =  new Problema(maxCapacidad, numEstaciones, numPedidos, pedidoActual-1, beneficioAcum, tramos);
			this->costeEst = this->costeEstimado(pedidos, numPedido);
			return p;
		}
		
		int beneficioActual(){return beneficioAcum;}

		bool anyadir(Pedido &p, Pedido pedidos[], int numPedido){
			this->pedidoActual++;
			bool ok = true;
			for(int i = p.estacionIni();i < p.estacionFin() && ok; i++){
				tramos[i] += p.billetes();
				ok = tramos[i] <= maxCapacidad;
			}
			if(ok){
				beneficioAcum += p.beneficioPedido();
				this->costeEst = this->costeEstimado(pedidos, numPedido);
			}
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
		double cEstim(){return this->costeEst;}
	
		double costeEstimado(Pedido pedidos[], int numPedidos){
			double coste = this->beneficioAcum;
			int replica[7] = {this->tramos[0],this->tramos[1],this->tramos[2],this->tramos[3],this->tramos[4],this->tramos[5],this->tramos[6] };
			for(int i = this->pedidoActual  + 1; i < numPedidos; i++){
				int maxPasajeros = replica[this->max(replica, pedidos[i].estacionIni(), pedidos[i].estacionFin())];
				int nuevosPasajeros = pedidos[i].billetes();
				int beneficio = pedidos[i].beneficioPedido();
				if((this->maxCapacidad - maxPasajeros) < nuevosPasajeros){
					nuevosPasajeros =  this->maxCapacidad - maxPasajeros;
					beneficio = nuevosPasajeros * (pedidos[i].estacionFin() - pedidos[i].estacionIni());
					coste += beneficio;
					return 0 - coste;
				}
				coste = coste + beneficio;
				for(int j = pedidos[i].estacionIni(); j < pedidos[i].estacionFin(); j++){
					replica[j] += nuevosPasajeros;
				}
				//--
				//for(int j = pedidos[i].estacionIni(); j < pedidos[i].estacionFin(); j++){
				//	if(pedidos[i].billetes() > this->maxCapacidad - replica[j]){
				//		nuevosPasajeros = this->maxCapacidad - replica[j];
				//		replica[j] += nuevosPasajeros;
				//		coste += nuevosPasajeros;
				//	}else{
				//		replica[j] += pedidos[i].billetes();
				//		coste += pedidos[i].billetes();
				//	}
				//	
				//	
				//}	
			}
			return 0 - coste;
		}

		int cota_mejor(Pedido pedidos[], int numPedidos){
			int cota = this->beneficioAcum;
			int replica[7] = {this->tramos[0],this->tramos[1],this->tramos[2],this->tramos[3],this->tramos[4],this->tramos[5],this->tramos[6] };
			for(int i = this->pedidoActual + 1; i < numPedidos; i++){
				int capac = this->maxCapacidad - replica[max(replica, pedidos[i].estacionIni(), pedidos[i].estacionFin())];
				if(capac < pedidos[i].billetes()){
					break;
				}
				for(int j = pedidos[i].estacionIni(); j < pedidos[i].estacionFin(); j++){
					replica[j] += pedidos[i].billetes();
					cota += pedidos[i].beneficioPedido();
				}
			}
			return 0 - cota;
		}

		void incrementarPedido(){pedidoActual++;}

		int siguientePedido(){return this->pedidoActual;}

		bool operator >= (Problema& p) {
			return this->cEstim() >= p.cEstim();
		}

		bool operator <=(Problema& p) {
			return this->cEstim() <= p.cEstim();
		}
		bool operator >(Problema& p) {
			return this->cEstim() > p.cEstim();
		}

		bool operator <(Problema& p) {
			return this->cEstim() < p.cEstim();
		}		
};