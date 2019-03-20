#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

#include "heap.hpp"
#include "trie.hpp"
#include "escritura.hpp"


using namespace std;

enum{NUM_SIMBOLOS = 256};

int decod(Trie<char> *& t , char u, int desde){
	unsigned char mask = 0x80;
	mask = (mask >> desde);
	for(int i = desde; i< 8; i++){
		if(t->getIzq() == nullptr){ 
			return i;
		}
		if(u & mask){
			t = t->getDch();
		}else{
			t = t->getIzq();
		}
		mask = (mask >> 1);
	}
	return 8;
}


int comprimir(string nombreFichero){
	ifstream f;
	Heap<Trie<char>> mont;
	char byteLeido[1];
	int posicion;
	int frecuencias[NUM_SIMBOLOS];
	for (int i = 0; i< NUM_SIMBOLOS; i++){
		frecuencias[i] = 0;
	}

	//lectura fichero

	f.open(nombreFichero,ios::binary);
	if(f.is_open()){
		f.read(byteLeido,1);
		
		while(!f.eof()){
			unsigned int leido = byteLeido[0];
			frecuencias[leido%256]++;
			f.read(byteLeido,1); 
			
		}
	}
	f.close();
	for(int it = 0; it < NUM_SIMBOLOS; it++){
		if(frecuencias[it]>0){
			Trie<char> * tr = new Trie<char>((char) it, frecuencias[it]);
			mont.add(tr);
		}
	}


	//generar trie
	while (mont.tamanyo() > 1){
		Trie<char> * h = mont.pop();
		Trie<char> * x = mont.pop();
		Trie<char> * tr = new Trie<char>(h, x);
		mont.add(tr);
	}

	//generar vector equivalencias
	Trie<char> * trieCompleto = mont.pop();
	string equivalencias[NUM_SIMBOLOS];
	for(Trie<char> * t : *trieCompleto){
		unsigned int elem = t->getElement();
		equivalencias[elem%NUM_SIMBOLOS] = t->getCode();
	}
	//Volver a leer fichero y codificar
	f.open(nombreFichero,ios::binary);
	Escritura e(nombreFichero + ".comp");
	e.escribirFrecuencias(frecuencias);
	if(!f.is_open()){ return 1;}
	f.read(byteLeido,1);
	while(!f.eof()){
		unsigned int leido = byteLeido[0];
		string code = equivalencias[leido%256];
		e.escribir(code);
		f.read(byteLeido,1);
		
	}
	e.escribirYcerrar();
	f.close();
	
	return 0;
}

int descomprimir(string nombreFichero){
	//lectura de equivalencias (arbol, vector, ....)
	ifstream f;
	ofstream o;
	char byteLeido[1];
	int tam, simbolos, frecuencia, simbolo;
	char kk;
	Heap<Trie<char>> mont;
	f.open(nombreFichero,ios::binary);
	if(!f.is_open()){ return 1;}   
	f >> tam >> simbolos;

	while(!f.eof() && simbolos > 0){
		f >> kk >> simbolo >> kk >> frecuencia >> kk;
		Trie<char> * tr = new Trie<char>((char) simbolo, frecuencia);
		mont.add(tr);
		simbolos--;
	}

	//generar trie
	while (mont.tamanyo() > 1){
		Trie<char> * h = mont.pop();
		Trie<char> * x = mont.pop();
		Trie<char> * tr = new Trie<char>(h, x);
		mont.add(tr);
	}
	Trie<char> * trieCompleto = mont.pop();

	Trie <char> * pos = trieCompleto;
	f.read(byteLeido,1);
	f.read(byteLeido,1);
	o.open(nombreFichero + ".desc", ios::binary);
	if(!o.is_open()){ return 1;}
	int reconocidoEn = 0;
	char printy[1];
	while(!f.eof() && tam > 0){
		if((reconocidoEn = decod(pos, byteLeido[0], reconocidoEn)) < 8){
			printy[0] = pos->getElement();
			o.write(printy, 1);
			pos = trieCompleto;
			tam--;
		}else{
			f.read(byteLeido,1);
			reconocidoEn = 0;
		}
	}
	//lectura y regeneración fichero original
	f.close();
}


int main(int argc, char ** argv){
	bool paramComprimir = false;
	if (argc < 3){
		printf("USO: huffer [-c | -d] <fichero>\n");
		return 1;
	}
	string param1(argv[1]);
	string param2(argv[2]);
	if (param1 == "-c"){
		//aragv == -c
		paramComprimir = true;
	}else if(param1 != "-d"){
		//error en paraemtro
		printf("USO: huffer [-c | -d] <fichero>\n");
		return 1;
	}
	
	//inicializar vector frecuencias
	//Abrir fichero
	//verificar fichero correctamente abierto
	if(paramComprimir){
		return comprimir(param2);
	}else{
		return descomprimir(param2);
	}
	return 0 ;
}

