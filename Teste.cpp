#include "NoArv.h"

#include <iostream>
#include <math.h>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void leArquivo(int *x,int *y,int *z,int *esperado){
    fstream file;
    file.open("data.csv", ios::in);

    if(file.is_open()){
        cout << "Arquivo aberto com sucesso" << endl;
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    string line, word;

    int i = 0;
    string linha;
    getline(file,linha,',');
    getline(file,linha,',');
    getline(file,linha,',');
    getline(file,linha,'\n');
    linha.clear();
    
    while(getline(file,line)){
   
        stringstream s(line);

        getline(s,word,',');
        x[i] = stoi(word);
        getline(s,word,',');
        y[i] = stoi(word);
        getline(s,word,',');
        z[i] = stoi(word);

        getline(s,word,',');
        esperado[i] = stoi(word);
        
        i++;
    }
    return;
}

int main(){

    Arv arv;

    char operadores[4] = {'+', '-', '*', '/'};
    char variaveis[3] = {'x', 'y', 'z'};
    arv.implementa(operadores,variaveis);

    int x[10];
    int y[10];
    int z[10];
    int valor_esperado[10];
    
    arv.imprime();
    leArquivo(x,y,z,valor_esperado);

    cout << "x\t" << "y\t" << "z\t" << "Valor esperado" << endl;
    for(int i=0;i<10;i++){
        cout << x[i]<< "\t" << y[i] << "\t" << z[i] << "\t" << valor_esperado[i] << endl;
    }
    return 0;
}