#include "iostream"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){
	string fich="fichRandNormal.pr";
	ofstream f;
	int tipo = 1;
	int tamFichero = 10000;
	if(argc > 1){
		if(argv[1][0] == '1'){
			tamFichero *= 10;
		}else if(argv[1][0] == '2'){
			tamFichero *= 1000;
		}
	}
	if(argc > 2){
		tipo = argv[2][0] - '0';
	}
	f.open(fich);
	int repet[255];
	for(int i = 0; i< 255; i++){
		repet[i] = 0;
	}
	if(f.is_open()){
		int moduloRepeticiones = 1000;
		if(tipo > 2){
			moduloRepeticiones /= tipo;
		}
			srand (time(NULL));
			for(int i=0;i<=tamFichero;i++){

				unsigned char c = 0;
				float ran = 0;
				int numRep = rand()%moduloRepeticiones;
				for(int j = 0; j< numRep; j++){
					ran = ran + (float)rand()/RAND_MAX;
				}
				c = (char)ran*100%255;
				repet[c]++;

				f << c;
			}
		  f.close();
	}

	else{
		cout<<"No se ha podido abrir"<<endl;
	}
	int mas10 = 0;
	for(int i = 0; i< 255; i++){
		if(repet[i] > 0){
		printf("%d %d\n", i, repet[i]);
		mas10++;
		}
	}
	cout << endl<< mas10<< endl;
	return 0;
}