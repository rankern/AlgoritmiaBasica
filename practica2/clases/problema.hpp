#pragma once
#include <iostream>
#include "pedido.hpp";
using namespace std;

class Problema{
	int maxCapacidad = 0;
	int numEstaciones = 0;
	int numPedidos = 0;
	int beneficioAcum = 0;
	int pedidoActual = 0;
	int tramos[7] = {0,0,0,0,0,0,0};	
	bool pedidos[22];
	public:
		Problema(){}
		Problema(int _cap, int _estaciones, int _pedidos)
			: maxCapacidad(_cap), numEstaciones(_estaciones), numPedidos(_pedidos){}
		
		Problema clone(){
			return Problema(maxCapacidad, numEstaciones, numPedidos);
		}
		
		int beneficioActual(){return beneficioAcum;}

		bool anyadir(Pedido &p){
			pedidos[pedidoActual] = true;
			bool ok = true;
			for(int i = p.estacionIni();i < p.estacionFin() && ok; i++){
				tramos[i] += p.billetes();
				ok = tramos[i] <= maxCapacidad;
			}
			beneficioAcum += p.beneficioPedido();
			return ok;
		}

		double costeEstimado(){
			return beneficioActual();
		}

		int cota_mejor(){
			return 0;
		}


};