/**
 * @autor: Victor M. Lafuente
 * @autor: Jose M. Romero
 * @fecha: 06-03-2019
 * @ultima Modificacion: 13-03-2019
 */ 

#pragma once
#include <iostream>
using namespace std;

const int MAX = 100000;

template <typename T>
class Heap{
	int tam = 0;
	T * elementos[MAX];

	public:
		Heap() : tam (0){}

		bool isEmpty(){ return this->tam == 0; }
		int tamanyo() {return this->tam;}
		void add(T * e){
			this->elementos[this->tam] = e;
			for (int i = this->tam++; i > 0 && *this->elementos[i] < *this->elementos[(i-1)/2]; i = (i-1)/2){
				T * aux = this->elementos[i];
				this->elementos[i] = this->elementos[(i-1)/2];
				this->elementos[(i-1)/2] = aux;
			}
		}


		T * pop(){
			/*for (int i = 0; i< this->tam; i++){
				if(this->elementos[i]->getIzq() == nullptr){
					printf("(%c, %d)", this->elementos[i]->getElement(), this->elementos[i]->getFrecuencia());
				}else{
					printf("(N, %d)", this->elementos[i]->getFrecuencia());
				}
			}
			cout << endl;*/
			T * ret = this->elementos[0];
			this->tam--;
			this->elementos[0] = this->elementos[this->tam];
			int hijo = 1;
			for (int i = 0; (i*2)+1 <= this->tam; i = hijo){
				hijo = (i*2)+1;
				if((hijo+1) <= this->tam && *this->elementos[hijo] > *this->elementos[hijo+1]){
					hijo++;
				}
				if( *this->elementos[hijo] >= *this->elementos[i]){
					break;
				}
				T * aux = this->elementos[hijo];
				this->elementos[hijo] = this->elementos[i];
				this->elementos[i] = aux;
			}
			return ret;
		}
	
};