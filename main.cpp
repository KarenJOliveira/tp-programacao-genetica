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

Arv* inicializa_pop(int size_pop, int seed, char *operadores, char *variaveis, int size_op, int size_var){
    Arv* pop = new Arv[size_pop];
    srand(seed);
    for (int i = 0; i < size_pop; i++)
    {
        int rand_ = rand()%10;
        pop[i].setAlturaMax(rand_);
        pop[i].implementa(pop[i].raiz,0,operadores,variaveis,size_op,size_var);
    }
    return pop;
}

void recombina_arvores(Arv* arvores, Arv *recombinadas,int size_pop, int seed){
    srand(seed);
    int i = 0;
    int rand_altura;
    int rand_no2;
    int rand_no;
    int rand_arv2;
    int rand_arv;

    while(i < size_pop){
        rand_arv = rand()%size_pop;
        rand_arv2 = rand()%size_pop;

        rand_no = rand()%(arvores[rand_arv].cont-1);
        rand_no2 = rand()%(arvores[rand_arv2].cont-1);

        rand_altura = rand()%10;

        recombinadas[i].setAlturaMax(rand_altura);
        recombinadas[i+1].setAlturaMax(rand_altura);
        recombinadas[i].implementa_copia(recombinadas[i].raiz,arvores[rand_arv].raiz,rand_no);
        recombinadas[i+1].implementa_copia(recombinadas[i+1].raiz,arvores[rand_arv2].raiz,rand_no2);

        recombinadas[i].complementa_copia(&recombinadas[i].nos[rand_no],&arvores[rand_arv2].nos[rand_no2]);
        recombinadas[i+1].complementa_copia(&recombinadas[i+1].nos[rand_no2],&arvores[rand_arv].nos[rand_no]);

        i+=2;
    }
}

int main(){


    Arv* arvores;
    char operadores[4] = {'+', '-', '*', '/'};
    char variaveis[3] = {'x', 'y', 'z'};
    int size_op = sizeof(operadores)/sizeof(operadores[0]);
    int size_var = sizeof(variaveis)/sizeof(variaveis[0]);
    
    arvores = inicializa_pop(100, 98, operadores, variaveis, size_op, size_var);
    int x[10];
    int y[10];
    int z[10];
    float valor_esperado[10];
    float resultado[10];

    Arv *recombinadas = new Arv[100];
    recombina_arvores(arvores,recombinadas,100,98);

    for(int i=0;i<4;i++){
        cout << "Arvore " << i << endl;
        arvores[i].imprime();
        cout << endl;
    }
    for(int i=0;i<4;i++){
        cout << "Arvore recombinada: " << i << endl;
        recombinadas[i].imprime();
        cout << endl;
    }

/*
    srand(98);
    Arv arv;
    arv.setAlturaMax(6);
    arv.implementa(arv.raiz,0,operadores,variaveis,size_op,size_var);
    arvores[0] = &arv;
    Pilha p;
    arv.empilha_arv(arv.raiz,&p);

    arv.imprime();
    cout << endl;
    leArquivo(x,y,z,valor_esperado);

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


    cout << "Arvore original: " << endl;
    arv.imprime();
    cout << endl;

    arv.muta_arvore(&sub_arv1);
    cout << "Arvore mutada: " << endl;
    arv.imprime();
    cout << endl;

    Arv arv2;
    arv2.setAlturaMax(6);
    arv2.implementa(arv2.raiz,0,operadores,variaveis,size_op,size_var);
    arvores[2] = &arv2;
    cout << "Arvore nova I: " << endl;
    arv2.imprime();
    cout << endl;

    Arv arv3;
    arv3.setAlturaMax(6);
    arv3.implementa(arv3.raiz,0,operadores,variaveis,size_op,size_var);
    arvores[3] = &arv3;
    cout << "Arvore nova II: " << endl;
    arv3.imprime();
    cout << endl;

    Arv arv4;
    arv4.setAlturaMax(6);
    arv4.implementa(arv4.raiz,0,operadores,variaveis,size_op,size_var);
    arvores[4] = &arv4;
    cout << "Arvore nova III: " << endl;
    arv4.imprime();
    cout << endl;

    Arv aux1;
    aux1.setAlturaMax(6);
    arvores[5] = &aux1;
    Arv aux2;
    aux2.setAlturaMax(6);
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

    Arv aux3;
    aux3.setAlturaMax(6);
    arvores[7] = &aux3;
    Arv aux4;
    aux4.setAlturaMax(6);
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