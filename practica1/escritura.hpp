
/* 
 * ALgoritmia Básica: 2018/2019
 * Practica1: Codigo Huffman
 * Autores: Victor M. Lafuente, José Manuel Romero
 * Nias: 		747325, 			740914
 * 
 * Contenido: Funciones necesarias para escritura de un fichero con codigo Huffman
 */

#pragma once
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class Escritura{
    char salida[1]; //Byte a escribir
    int enSalida = 0; //numero de bits validos en salida
    ofstream s;

    public:
        //Constructores
        Escritura(){}
        Escritura(string nombreFichero) : s(nombreFichero, ios::binary){}

        //escr es un string cuyo contenido es únicamente lista de caracteres '0' o '1'
        // 
        // Inserta la conversión de escr a bits en this->salida, concatenandolo detrás del contenido válido que ya existiera y escribirá multiplos de 8 bits.
        // En caso de que len(escr)+this->enSalida no sea múltipo de 8, se almacenará su contenido en this->salida, y el nuero de bits escritos en this->enSalida.
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

        //Habra escrito en this->s el vector de ocurrencias
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

        //Termina de escribir lo último que queda por escribir y cierra el fichero
        int escribirYcerrar(){
            if(!s.is_open()){ return 2;}
            if(enSalida > 0){
                this->salida[0] = (this->salida[0] << (8 -enSalida));
            }
            s.write(this->salida, 1);
            s.close();
        }
        
        //Destructor. Si queda algo por escribir y this-> aun esta abierto, se escribe, se cierra el fichero y se destruye la clase
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