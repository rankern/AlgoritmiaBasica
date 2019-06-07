/**
 * @autor: Victor M. Lafuente NIA:747325
 * @autor: Jose M. Romero NIA:740914
 * @fecha: 06-03-2019
 * @ultima Modificacion: 13-03-2019
 */ 

#pragma once
#include <iostream>
using namespace std;

const int MAX = 100000;//capacidad máxima del montículo

template <typename T>
//Clase montículo
class Heap{
	int tam = 0; //tamaño del montículo
	T * elementos[MAX]; //Vector de elementos

	public:
		//Crea un montículo vacío
		Heap() : tam (0){}


		/*Pre:
		*Post:Devuelve true si el montículo está vacío
		*/
		bool isEmpty(){ return this->tam == 0; }

		/*Pre:
		*Post:Devuelve el número de elemento en el montículo
		*/
		int tamanyo() {return this->tam;}

		/*Pre:
		*Post:Añade al montículo el elemento e
		*/
		void add(T * e){
			this->elementos[this->tam] = e;
			for (int i = this->tam++; i > 0 && *this->elementos[i] < *this->elementos[(i-1)/2]; i = (i-1)/2){
				T * aux = this->elementos[i];
				this->elementos[i] = this->elementos[(i-1)/2];
				this->elementos[(i-1)/2] = aux;
			}
		}
		/*Pre:
		 *Post:Ha quitado el último elemento del montículo
		 */

		T * pop(){
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
