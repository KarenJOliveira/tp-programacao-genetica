//
// Created by karen on 20/08/2023.
//
#include "NoArv.h"
#include <iostream>
#include <math.h>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void leArquivo(int *x,int *y,int *z,float *esperado){
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

    Arv arv(6);

    Arv* arvores[MAX];
    char operadores[4] = {'+', '-', '*', '/'};
    char variaveis[3] = {'x', 'y', 'z'};
    int size_op = sizeof(operadores)/sizeof(operadores[0]);
    int size_var = sizeof(variaveis)/sizeof(variaveis[0]);

    srand(98);
    arv.implementa(arv.raiz,0,operadores,variaveis,size_op,size_var);
    arvores[0] = &arv;
    Pilha p;
    arv.empilha_arv(arv.raiz,&p);

    int x[10];
    int y[10];
    int z[10];
    float valor_esperado[10];
    float resultado[10];

    arv.imprime();
    cout << endl;
    leArquivo(x,y,z,valor_esperado);

    cout << "x\t" << "y\t" << "z\t" << "Valor esperado" << endl;
    cout << x[0]<< "\t" << y[0] << "\t" << z[0] << "\t" << valor_esperado[0] << endl;

    resultado[0] = p.resolve_operacoes(x[0],y[0],z[0]);
    cout << "Resultado da operacao obtida pela arvore original: "<< resultado[0] << endl;

    cout << "x\t" << "y\t" << "z\t" << "Valor esperado" << endl;
    cout << x[1]<< "\t" << y[1] << "\t" << z[1] << "\t" << valor_esperado[1] << endl;

    resultado[1] = p.resolve_operacoes(x[1],y[1],z[1]);
    cout << "Resultado da operacao obtida pela arvore original: "<< resultado[1] << endl;

    Arv sub_arv1(3);
    sub_arv1.implementa(sub_arv1.raiz,0,operadores,variaveis,size_op,size_var);
    arvores[1] = &sub_arv1;
    cout << "Arvore nova: " << endl;
    sub_arv1.imprime();
    cout << endl;

    cout << "Arvore original: " << endl;
    arv.imprime();
    cout << endl;

    arv.muta_arvore(&sub_arv1);
    cout << "Arvore mutada: " << endl;
    arv.imprime();
    cout << endl;

    return 0;
}