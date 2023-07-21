#include "NoArv.h"
#include <iostream>
#include <math.h>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void leArquivo(float *x,float *y,float *z,float *esperado){
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
    int size_op = sizeof(operadores)/sizeof(operadores[0]);
    int size_var = sizeof(variaveis)/sizeof(variaveis[0]);

    srand(98);
    arv.implementa(arv.raiz,0,operadores,variaveis,size_op,size_var);
    
    Pilha p;
    arv.empilha_arv(arv.raiz,&p);
    
    float x[10];
    float y[10];
    float z[10];
    float valor_esperado[10];
    
    arv.imprime();
    cout << endl;
    leArquivo(x,y,z,valor_esperado);
    
    Pilha p2;
    p.copia_pilha(&p2,x,y,z,0);
    cout << "x\t" << "y\t" << "z\t" << "Valor esperado" << endl;
    //for(int i=0;i<10;i++){
    //    cout << x[i]<< "\t" << y[i] << "\t" << z[i] << "\t" << valor_esperado[i] << endl;
    //}
    
    cout << x[0]<< "\t" << y[0] << "\t" << z[0] << "\t" << valor_esperado[0] << endl;
    p.imprime_pilha();
    p2.imprime_pilha();

    return 0;
}