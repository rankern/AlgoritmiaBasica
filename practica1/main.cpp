#include "heap.hpp"
#include <stdlib.h>
#include <string.h>

enum{NUM_SIMBOLOS = 256};


int comprimir(){
    int frecuencias[NUM_SIMBOLOS];
    for (int i = 0; i< NUM_SIMBOLOS; i++){
        frecuencias[i] = 0;
    }

    //lectura fichero
    
    //generar monticulo
    
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
    bool comprimir = false;
    if (argc < 4){
        printf("USO: huffer [-c | -d] <fichero>\n");
        return 1;
    }

    if (argv[1]){
        //aragv == -c
        comprimir = true;
    }else if(argv[1]){
        //aragv == -d
    }else{
        //error en paraemtro
        printf("USO: huffer [-c | -d] <fichero>\n");
        return 1;
    }
    //inicializar vector frecuencias
    //Abrir fichero
    //verificar fichero correctamente abierto
    if(comprimir){
        return comprimir();
    }else{
        return descomprimir();
    }
}

