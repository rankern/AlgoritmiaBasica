
/* 
 * ALgoritmia Básica: 2018/2019
 * Practica1: Codigo Huffman
 * Autores: Victor M. Lafuente, José Manuel Romero
 * Nias: 		747325, 			740914
 * 
 * Contenido: Clase Trie, árbol de tipo Lexicográfico para codigo Huffman
 */

#pragma once

#include "pila.hpp"
#include <stack>
#include <string>
using namespace std;
template <typename T>
class Trie{
	private:
		Trie * izq = nullptr; //Hijo izquierdo del árbol
		Trie * dch = nullptr; //Hijo derecho del árbol
		T elemento;	//Simbolo a codificar (sólo si this es hoja)
		int frecuencia = 0;	//Numero de frecuencias
		string codificacion = ""; //equivalencia de codificacion
	
	public:
		//Constructores
		Trie<T>(){}
		Trie<T>(T t) : elemento (t) { }
		Trie<T>(T t, int _frec) : elemento (t), frecuencia(_frec) { }
		Trie<T>(Trie * _izq, Trie * _dch) : izq(_izq), dch (_dch){
			this->frecuencia = _izq->getFrecuencia() + _dch->getFrecuencia();
		 }
		Trie<T>(Trie * _izq) : izq(_izq){ }
		//Geters
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
		//añade la condificación equivalente al nodo
		void setCode(string c){
			this->codificacion = c;
		}
		string getCode(){
			return this->codificacion;
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
	   
		//Iterador de la clase. Se emplea para codificar los nodos
		class const_iterator {
		private:
			stack<Trie *> p;
			Trie<T>* trie;
		public:
			//Inicializa iterador en hoja más a la izquierda. Habra ido generando codigos Huffman e insertandolos en cada nodo recorrido
			const_iterator(Trie* t_) : trie(t_) {
				string c = "";
				c += "0";
				Trie * t = t_->getIzq();
				while(t != nullptr){
					t->setCode(c);
					p.push(this->trie);
					this->trie = t;
					t = t->getIzq();
					c += "0";
				}
			}

			const_iterator(Trie* t_, int i) : trie(t_) {
				this->trie = nullptr;
			}
			
			
		
			//redefine el operador de pre-incremento (++x) necesario para el avance del iterador.
			//Recorre el árbol en in-Orden, generando e insertando codigos Huffman, hasta siguiente hoja
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
				string c = this->trie->getCode();
				this->trie =  this->trie->getDch();
				c += "1";
				this->trie->setCode(c);
				//this->trie = this->trie;
				//this->trie = this->trie.getDch();
				Trie * t = this->trie->getIzq();
				while(t != nullptr){
					c += "0";
					t->setCode(c);
					p.push(this->trie);
					this->trie = t;
					t = this->trie->getIzq();
				}
				return (*this);
				
			}

			Trie * operator*()   const 
			{
				return this->trie;
			} 



			bool operator!=(const const_iterator& that) const 
			{ 
				return this->trie != that.trie;
			}		

		};


		const_iterator begin() { return const_iterator(this); }
		const_iterator end()   { return const_iterator(this, 1); }
};