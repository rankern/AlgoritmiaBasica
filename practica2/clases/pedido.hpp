#pragma once
#include <iostream>
using namespace std;

class Pedido{
    int numBilletes = 0;
    int estacionInicial = 0;
    int estacionFinal = 0;
    int beneficio = 0;
    public:
        Pedido(){}
        Pedido(int _billetes, int iniEstacion, int finEstacion): numBilletes(_billetes), estacionInicial(iniEstacion), estacionFinal(finEstacion){
            beneficio = (estacionFinal - estacionInicial) * numBilletes;
        }
        int billetes(){return numBilletes;}
        int estacionIni(){return estacionInicial;}
        int estacionFin(){return estacionFinal;}
        int beneficioPedido(){return beneficio;}
        double beneficioIndividual(){return (double)this->beneficio/this->numBilletes;}
        bool operator >=(Pedido& p) {
            if((double)this->beneficio/this->numBilletes == p.beneficioIndividual()){
                return numBilletes >= p.billetes();
            }
			return (double)this->beneficio/this->numBilletes >= p.beneficioIndividual();
		}

		bool operator <=(Pedido& p) {
            if((double)this->beneficio/this->numBilletes == p.beneficioIndividual()){
                return numBilletes <= p.billetes();
            }
			return (double)this->beneficio/this->numBilletes <= p.beneficioIndividual();		
            }


		bool operator >(Pedido& p) {
            if((double)this->beneficio/this->numBilletes == p.beneficioIndividual()){
                return numBilletes > p.billetes();
            }
			return (double)this->beneficio/this->numBilletes > p.beneficioIndividual();		
            }



		bool operator <(Pedido& p) {
            if((double)this->beneficio/this->numBilletes == p.beneficioIndividual()){
                return numBilletes < p.billetes();
            }
			return (double)this->beneficio/this->numBilletes < p.beneficioIndividual();		
            }


        
};

