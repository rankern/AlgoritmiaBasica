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
        int Pedido::billetes(){return numBilletes;}
        int Pedido::estacionIni(){return estacionInicial;}
        int Pedido::estacionFin(){return estacionFinal;}
        int Pedido::beneficioPedido(){return beneficio;}
        
};

