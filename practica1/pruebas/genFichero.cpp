#include "iostream"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
using namespace std;

int main(){
    string fich="fichRandNormal.txt";
    //char c=' ';
    //int i=0;
    fstream f;
    //string write="";
    f.open(fich);
    if(f.is_open()){
            srand (time(NULL));
            for(int i=0;i<=10000;i++){
                f<<rand()%10;
            }
        /*    for(i=0; i<=10;i++){
                write="";
                for(int j=0;j<=50;j++){
                    write=write+c;
                }
                f<<write;
                c=c+1;
            }*/
          f.close();
}
    else{
        cout<<"No se ha podido abrir"<<endl;
    }
  
  
}