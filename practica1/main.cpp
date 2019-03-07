#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "heap.hpp"

using namespace std;

enum{NUM_SIMBOLOS = 256};


int comprimir(const char nombreFichero[]){
    ifstream f;
    Heap mont();
    char byteLeido;
    int posicion;
    int frecuencias[NUM_SIMBOLOS];
    for (int i = 0; i< NUM_SIMBOLOS; i++){
        frecuencias[i] = 0;
    }

    //lectura fichero

    f.open(nombreFichero,ios::binary);
    if(f.is_open()){
        while(!f.eof()){
            fread(byteLeido,1);
            posicion=byteLeido+'0';
            frecuencias[posicion]++;
        }
    f.close()
    }
    //generar monticulo

    int it=0;
    while(it<NUM_SIMBOLOS){
        if(frecuencias[it]>0){
            mont.add(frecuencias[it]);
        }
        cout>>frecuencias[it];
        it++;
    }


  //generar trie

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
    }else if(param2 == "-d"){
        //aragv == -d
    }else{
        //error en paraemtro
        printf("USO: huffer [-c | -d] <fichero>\n");
        return 1;
    }
    //inicializar vector frecuencias
    //Abrir fichero
    //verificar fichero correctamente abierto
    if(paramComprimir){
        return comprimir();
    }else{
        return descomprimir();
    }
}

