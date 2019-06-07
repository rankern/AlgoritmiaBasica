
/* 
 * ALgoritmia Básica: 2018/2019
 * Practica1: Codigo Huffman
 * Autores: Victor M. Lafuente, José Manuel Romero
 * Nias: 		747325, 			740914
 * 
 * Contenido: Main del algoritmo necesario para Codificar/Decodificar
 */


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
bool verbose = false;

/*
 * PRE: 
 *	t = un árbol lexicográfico binario.
 * 	u = byte para decodificar
 * 	desde = posición de siguiente bit 'u' para descodificar
 * POST:
 * 	Devuelve el último bit (entre 0 a 7) empleado para descodificar u 8 si no se aún no se ha encontrado símbolo equivalente
 * 	t apuntará al último nodo del árbol visitado.
 */
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

/* 
 * PRE:
 * nombreFichero es el path completo o relativo de fichero existente 
 * 
 * POST:
 *  habra genererado un fichero con nombre "<nombreFichero>.huf" 
 * 	cuyo contenido sera el equivalente al original tras la compresión 
 * 	mediante el código Huffman
*/
int comprimir(string nombreFichero){
	//Inicializacion variables
	ifstream f;
	Heap<Trie<char>> mont;
	char byteLeido[1];
	int posicion;
	int frecuencias[NUM_SIMBOLOS];
	for (int i = 0; i< NUM_SIMBOLOS; i++){
		frecuencias[i] = 0;
	}

	//lectura fichero y contabilizacion de ocurrencias
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

	//Inicialización de monticulo
	int leidos = 0;
	for(int it = 0; it < NUM_SIMBOLOS; it++){
		if(frecuencias[it]>0){
			leidos++;
			Trie<char> * tr = new Trie<char>((char) it, frecuencias[it]);
			mont.add(tr);
		}
	}
	if(verbose)
		cout << "Cantidad de bytes distintos leidos = " << leidos << endl;

	//generar trie de código Huffman
	while (mont.tamanyo() > 1){
		Trie<char> * h = mont.pop();
		Trie<char> * x = mont.pop();
		Trie<char> * tr = new Trie<char>(h, x);
		mont.add(tr);
	}

	//generar vector equivalencias (LUT)
	Trie<char> * trieCompleto = mont.pop();
	string equivalencias[NUM_SIMBOLOS];
	for(Trie<char> * t : *trieCompleto){
		unsigned int elem = t->getElement();
		equivalencias[elem%NUM_SIMBOLOS] = t->getCode();
	}

	//Volver a leer fichero y escribir codificado
	f.open(nombreFichero,ios::binary);
	Escritura e(nombreFichero + ".huf");
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

/* 
 * PRE:
 * 	<nombreFichero>.huf es el path completo o relativo de un fichero existente
 * 		y comprimido mediante este algoritmo
 * 
 * POST:
 *  habra genererado un fichero con nombre "<nombreFichero>" 
 * 	cuyo contenido sera el equivalente al original antes de la compresión
*/
int descomprimir(string nombreFichero){

	//inicializacion variables
	ifstream f;
	ofstream o;
	char byteLeido[1];
	int tam, simbolos, frecuencia, simbolo;
	char kk;
	Heap<Trie<char>> mont;

	//lectura de equivalencias (vector)
	f.open(nombreFichero + ".huf",ios::binary);
	if(!f.is_open()){ return 1;}   
	f >> tam >> simbolos;
	while(!f.eof() && simbolos > 0){
		f >> kk >> simbolo >> kk >> frecuencia >> kk;
		Trie<char> * tr = new Trie<char>((char) simbolo, frecuencia);
		mont.add(tr);
		simbolos--;
	}

	//generar trie codigo Huffman
	while (mont.tamanyo() > 1){
		Trie<char> * h = mont.pop();
		Trie<char> * x = mont.pop();
		Trie<char> * tr = new Trie<char>(h, x);
		mont.add(tr);
	}
	Trie<char> * trieCompleto = mont.pop();

	Trie <char> * pos = trieCompleto; //Puntero a nodo actual
	f.read(byteLeido,1); // \n
	f.read(byteLeido,1); // primer byte a decodificar
	o.open(nombreFichero, ios::binary);
	if(!o.is_open()){ return 1;}

	int reconocidoEn = 0;	//Si 0 <= reconocidoEn < 8 -> pos = simbolo de últimos bits leídos, caso contrario es un nodo intermedio
	char printy[1];
	//Decodificación
	while(!f.eof() && tam > 0){
		if((reconocidoEn = decod(pos, byteLeido[0], reconocidoEn)) < 8){
			//Se ha reconocido simbolo válido
			printy[0] = pos->getElement();
			o.write(printy, 1);
			pos = trieCompleto;
			tam--;
		}else{
			//No se ha encontrado aún simbolo equivalente. leer siguiente byte
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
	verbose = (argc == 4);
	if (param1 == "-c"){
		paramComprimir = true;
	}else if(param1 != "-d"){
		//error en paraemtro
		printf("USO: huffer [-c | -d] <fichero>\n");
		return 1;
	}
	
	if(paramComprimir){
		return comprimir(param2);
	}else{
		return descomprimir(param2);
	}
	return 0 ;
}
