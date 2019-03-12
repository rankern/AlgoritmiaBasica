/**
 * @autor: Victor M. Lafuente
 * @autor: Jose M. Romero
 * @fecha: 06-03-2019
 * @ultima Modificacion: 6-03-2019
 */ 


#pragma once

#include "pila.hpp"

template <typename T>
class Trie{
	private:
		Trie * izq = nullptr;
		Trie * dch = nullptr;
		T elemento;
	
	public:
		Trie<T>(){}
		Trie<T>(T t) : elemento (t) { }
		Trie<T>(Trie * _izq, Trie * _dch) : izq(_izq), dch (_dch){ }
		Trie<T>(Trie * _izq) : izq(_izq){ }
		Trie getIzq(){
			return this.izq;
		}
		Trie getDch(){
			return this.dch;
		}

		T getElement(){
			return this.elemento;
		}

		friend class const_iterator;
	   
		class const_iterator {
		private:
			class Nodo{
				Trie<T>& item;
				Nodo & next;
				public:
					Nodo(Trie<T>& t, Nodo& _next) : item(t), next(_next){}

					Nodo * getNext(){
						return &next;
					}
					~Nodo(){
						
					}
					Trie<T>& getItem(){
						return item;
					}

					Nodo apilar(Trie<T>& t){
						Nodo(t, this);
					}

					Nodo Desapilar(){
						Nodo * n = getNext();
						return *n;
					}
			};
			Trie<T>& trie;
		public:
			const_iterator(const Trie& t_) : trie(t_) {
				CrearPila(p);
				Trie<T>& t = this->trie.getIzq();
				while(t != nullptr){
					Apilar(p, this->trie);
					this->trie = t;
					t = this->trie.getIzq();
				}
			}
			
		
			//Este método redefine el operador de pre-incremento (++x).
			//Representa el avance del iterador.
			const_iterator& operator++(){ 	
				if(Desapilar(this->p, this->trie)){
					return (*this);
				}
				this->trie = this->trie.getDch();
			/*	if (this->&trie == nullptr){
					return (*this);
				}*/
				Trie& t = this->trie.getIzq();
				while(t != nullptr){
					Apilar(p, this->trie);
					this->trie = t;
					Trie& t = this->trie.getIzq();
				}
				return (*this);
				
			}
			//Este método redefine el operador de "apuntado" (*x)
			//Representa la obtención de lo apuntado por el iterador.
			const T& operator*()   const 
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
			//	return &this->trie == &that;
				//TODO: Rellenar este método para devuelva true si este iterador y el iterador "that" apuntan
				//a sitios diferentes, y false en caso contrario. 
			}		

		};

		//Observa como nuestra agrupacion permite generar dos iteradores: uno al principio y otro al final.
		//El iterador que apunta al final de la agrupación se mantiene en este caso únicamente para hacer
		//la comprobación de que "existe siguiente".
		//Date cuenta que los valores que le pasamos como índice del iterador son para que se recorra la
		//estructura desde el último elemento (this->total - 1) hasta el primero (0).
		const_iterator begin() const { return const_iterator(*this); }
		const_iterator end()   const { return const_iterator(*this); }
};