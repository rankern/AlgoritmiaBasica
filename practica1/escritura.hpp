#pragma once
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class Escritura{
    char salida[1];
    int enSalida = 0;
    unsigned char resto;
    ofstream s;

    public:
        Escritura(){}
        Escritura(string nombreFichero) : s(nombreFichero, ios::binary){}
        int escribir(string escr){
            if(!s.is_open()){return 2;}
            for (int i = 0; i< escr.length(); i++){
                enSalida++;
                unsigned char c = escr[i] - '0';
                this->salida[0] = (this->salida[0] << 1) | c;
                if(enSalida > 7){
                    s.write(this->salida, 1);
                    enSalida = 0;
                    this->salida[0] = 0;
                }
            }
        }
        int escribirFrecuencias(int freq[]){
            if(!this->s.is_open()){ return 2;}
            int tam = 0;
            int simbolos = 0;
            string equivalencias = "";
            for(int i = 0; i< 256; i++){
                if(freq[i] != 0){
                    tam += freq[i];
                    simbolos++;
                    equivalencias += "(" + to_string(i) + "," + to_string(freq[i]) + ")";
                }
            } 
            equivalencias =  to_string(tam) + " " + to_string(simbolos) + "\n" + equivalencias +"\n";
            this->s.write(equivalencias.c_str(), equivalencias.length());

        }

        int escribirYcerrar(){
            if(!s.is_open()){ return 2;}
            if(enSalida > 0){
                this->salida[0] = (this->salida[0] << (8 -enSalida));
            }
            s.write(this->salida, 1);
            s.close();
        }
        
        ~Escritura(){
            if(s.is_open()){
                if(enSalida > 0){
                    this->salida[0] = (this->salida[0] << (8 -enSalida));
                }
                s.write(this->salida, 1);
            }
            s.close();
        }
};