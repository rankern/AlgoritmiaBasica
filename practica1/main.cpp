#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

#include "heap.hpp"
#include "trie.hpp"


using namespace std;

enum{NUM_SIMBOLOS = 256};


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
            frecuencias[byteLeido[0]]++;
            cout << byteLeido << " ";
            f.read(byteLeido,1);
        }
        cout << endl;
    f.close();
    }
    //generar monticulo

    for(int it = 0; it < NUM_SIMBOLOS; it++){
        if(frecuencias[it]>0){
            Trie<char> * tr = new Trie<char>((char) it, frecuencias[it]);
            mont.add(tr);
            cout << frecuencias[it];
        }
    }
    cout << endl;

    /*while(!mont.isEmpty()){
        //cout << mont.pop().getElement() << " ";
        mont.pop();
    }
    cout << endl;*/
    
    //generar trie
    while (mont.tamanyo() > 1){
        Trie<char> * h = mont.pop();
        Trie<char> * x = mont.pop();
        //printf("f = %d + %d\n", h->getFrecuencia(), x->getFrecuencia());
        Trie<char> * tr = new Trie<char>(x, h);
        mont.add(tr);
    }

    Trie<char> trieCompleto = *mont.pop();

    int i = 1;
    for(Trie<char> * t : trieCompleto){
    
        cout << i++ <<" (" <<t->getElement() << ", " << t->getFrecuencia() << ")" << endl;
    }

    //generar vector equivalencias

    //generar salidas
    return 0;
}

int descomprimir(){
    //lectura de equivalencias (arbol, vector, ....)

    //lectura y regeneración fichero original

    //generar salida
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
        return descomprimir();
    }
    return 0 ;
}

