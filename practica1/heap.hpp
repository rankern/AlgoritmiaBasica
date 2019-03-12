/**
 * @autor: Victor M. Lafuente
 * @autor: Jose M. Romero
 * @fecha: 06-03-2019
 * @ultima Modificacion: 6-03-2019
 */ 

#pragma once

const int MAX = 100000;
template <typename T>
class Heap{
	int tam = 0;
	T elementos[MAX];

	public:
		Heap() : tam (0){}

		bool isEmpty(){ return this.tam == 0; }
		int tamanyo() {return this.tam;}
		void add(T e){
			this.elementos[this.tam] = e;
			for (int i = this.tam++; i > 0 && this.elementos[i] >= this.elementos[(i-1)/2]; i = (i-1)/2){
				T aux = this.elementos[i];
				this.elementos[i] = this.elementos[(i-1)];
				this.elementos[(i-1)] = aux;
			}
		}
		T pop(){
			T ret = this.elementos[0];
			this.tam--;
			this.elementos[0] = this.elementos[this.tam];
			int hijo = 1;
			for (int i = 0; (i*2)+1 <= this.tam; i = hijo){
				hijo = (i*2)+1;
				T * aux = &this.elementos[hijo];
				if ((hijo+1) <= this.tam && this.elementos[hijo+1] < this.elementos[hijo+2]){
					aux++;
				}
				if( *aux >= this.elementos[i]){
					break;
				}
				T aux2 = *aux;
				*aux = this.elementos[i];
				this.elementos[i] = aux;
			}
		}
	
};