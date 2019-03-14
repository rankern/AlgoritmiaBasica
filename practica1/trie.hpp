/**
 * @autor: Victor M. Lafuente
 * @autor: Jose M. Romero
 * @fecha: 06-03-2019
 * @ultima Modificacion: 6-03-2019
 */ 


#pragma once

#include "pila.hpp"
#include <stack>
using namespace std;
template <typename T>
class Trie{
	private:
		Trie * izq = nullptr;
		Trie * dch = nullptr;
		T elemento;
		int frecuencia = 0;
	
	public:
		Trie<T>(){}
		Trie<T>(T t) : elemento (t) { }
		Trie<T>(T t, int _frec) : elemento (t), frecuencia(_frec) { }
		Trie<T>(Trie * _izq, Trie * _dch) : izq(_izq), dch (_dch){
			this->frecuencia = _izq->getFrecuencia() + _dch->getFrecuencia();
		 }
		Trie<T>(Trie * _izq) : izq(_izq){ }
		
		Trie<T> * getIzq(){
			return this->izq;
		}
		Trie<T> * getDch(){
			return this->dch;
		}

		T getElement(){
			return this->elemento;
		}

		int getFrecuencia() {
			return this->frecuencia;
		}

		bool operator >=(Trie& t) {
			return this->frecuencia >= t.getFrecuencia();
		}

		bool operator <=(Trie& t) {
			return this->frecuencia <= t.getFrecuencia();
		}
		bool operator >(Trie& t) {
			return this->frecuencia > t.getFrecuencia();
		}

		bool operator <(Trie& t) {
			return this->frecuencia < t.getFrecuencia();
		}

		bool operator ==(Trie& t) {
			return this->frecuencia == t.getFrecuencia();
		}

		string operator<<(Trie t) {
			return t->getElement;
		}


		friend class const_iterator;
	   
		
		class const_iterator {
		private:
			stack<Trie *> p;
			Trie<T>* trie;
		public:
			const_iterator(Trie* t_) : trie(t_) {
				
				Trie * t = t_->getIzq();
				while(t != nullptr){
					p.push(this->trie);
					this->trie = t;
					t = t->getIzq();
				}
			}

			const_iterator(Trie* t_, int i) : trie(t_) {
				this->trie = nullptr;
			}
			
			
		
			//Este método redefine el operador de pre-incremento (++x).
			//Representa el avance del iterador.
			const_iterator& operator++(){ 
				if(p.empty()){
					this->trie = nullptr;
					return (*this);
				}
				//Trie * t = 
				this->trie = p.top();
				p.pop();
				while(this->trie->getDch() == nullptr && !p.empty()){
					this->trie = p.top();
				}
				if(this->trie->getDch() == nullptr){
					return *this;
				}
				this->trie =  this->trie->getDch();
				//this->trie = this->trie;
				//this->trie = this->trie.getDch();
				Trie * t = this->trie->getIzq();
				while(t != nullptr){
					p.push(this->trie);
					this->trie = t;
					t = this->trie->getIzq();
				}
				return (*this);
				
			}
			//Este método redefine el operador de "apuntado" (*x)
			//Representa la obtención de lo apuntado por el iterador.
			Trie * operator*()   const 
			{
				return this->trie;
				//TODO: Rellena este método para que devuelva el elemento T al que está apuntando el iterador.	
			} 


		//	En la definición por defecto de los iteradores, no existe la comprobación de si existe
		//	siguiente elemento. Por defecto las estructuras de datos devuelven iteradores al principio y al final,
		//	y para recorrer la estructura se compara el iterador que avanza con el iterador que apunta al final
		//	de la estructura.
		//
			bool operator!=(const const_iterator& that) const 
			{ 
				return this->trie != that.trie;
			}		

		};

		//Observa como nuestra agrupacion permite generar dos iteradores: uno al principio y otro al final.
		//El iterador que apunta al final de la agrupación se mantiene en este caso únicamente para hacer
		//la comprobación de que "existe siguiente".
		//Date cuenta que los valores que le pasamos como índice del iterador son para que se recorra la
		//estructura desde el último elemento (this->total - 1) hasta el primero (0).
		const_iterator begin() { return const_iterator(this); }
		const_iterator end()   { return const_iterator(this, 1); }
};