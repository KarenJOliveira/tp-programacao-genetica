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



void recombina_arvore(Arv *arv1, Arv *arv2, Arv *rec1, Arv *rec2){
    int rand1 = rand()%(arv1->cont-1);
    //int rand2 = rand()%(arv2->cont-1);
    
    //aux_recombina(rec1,rec1->raiz,arv1->raiz,rand1);
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
/*
    cout << "x\t" << "y\t" << "z\t" << "Valor esperado" << endl;
    cout << x[0]<< "\t" << y[0] << "\t" << z[0] << "\t" << valor_esperado[0] << endl;

    resultado[0] = p.resolve_operacoes(x[0],y[0],z[0]);
    cout << "Resultado da operacao obtida pela arvore original: "<< resultado[0] << endl;

    Arv sub_arv1(3);
    sub_arv1.implementa(sub_arv1.raiz,0,operadores,variaveis,size_op,size_var);
    arvores[1] = &sub_arv1;
    cout << "Sub-arvore nova: " << endl;
    sub_arv1.imprime();
    cout << endl;
*/

    cout << "Arvore original: " << endl;
    arv.imprime();
    cout << endl;
/*
    arv.muta_arvore(&sub_arv1);
    cout << "Arvore mutada: " << endl;
    arv.imprime();
    cout << endl;

    Arv arv2(20);
    arv2.implementa(arv2.raiz,0,operadores,variaveis,size_op,size_var);
    arvores[2] = &arv2;
    cout << "Arvore nova I: " << endl;
    arv2.imprime();
    cout << endl;

    Arv arv3(20);
    arv3.implementa(arv3.raiz,0,operadores,variaveis,size_op,size_var);
    arvores[3] = &arv3;
    cout << "Arvore nova II: " << endl;
    arv3.imprime();
    cout << endl;
*/
    Arv arv4(20);
    arv4.implementa(arv4.raiz,0,operadores,variaveis,size_op,size_var);
    arvores[4] = &arv4;
    cout << "Arvore nova III: " << endl;
    arv4.imprime();
    cout << endl;

    Arv aux1(20);
    arvores[5] = &aux1;
    Arv aux2(20);
    arvores[6] = &aux2;

    int rand1 = rand()%(arv.cont-1);
    int rand2 = rand()%(arv4.cont-1);
    aux1.implementa_copia(aux1.raiz,arv.raiz,rand1);
    aux2.implementa_copia(aux2.raiz,arv4.raiz,rand2);

    aux1.complementa_copia(&aux1.nos[rand1],&arv4.nos[rand2]);
    aux2.complementa_copia(&aux2.nos[rand2],&arv.nos[rand1]);
    
    cout << "Arvore recombinada I: " << endl;	
    aux1.imprime();
    cout << endl;
    cout << "Arvore recombinada II: " << endl;
    aux2.imprime();
    cout << endl;
/*
    Arv aux3(20);
    arvores[7] = &aux3;
    Arv aux4(20);
    arvores[8] = &aux4;

    int rand3 = rand()%(arv.cont-1);
    int rand4 = rand()%(arv3.cont-1);
    aux3.implementa_copia(aux3.raiz,arv.raiz,rand3);
    aux4.implementa_copia(aux4.raiz,arv3.raiz,rand4);

    aux3.complementa_copia(&aux3.nos[rand3],&arv3.nos[rand4]);
    aux4.complementa_copia(&aux4.nos[rand4],&arv.nos[rand3]);

    cout << "Arvore recombinada III: " << endl;	
    aux3.imprime();
    cout << endl;
    cout << "Arvore recombinada IV: " << endl;
    aux4.imprime();
    cout << endl;
*/
    return 0;
}