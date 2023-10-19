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
#define ALTURA_MAX 10
#define MAX_POP 10
#define MAX_GER 10

vector<char> variaveis = {'x','y','z'};
vector<char> operadores = {'+','-','*','/'};

using namespace std;

float** leArquivo(int *dados_l,int *dados_c){
    
    fstream file;
    file.open("data.csv", ios::in);

    if(file.is_open()){
        cout << "Arquivo aberto com sucesso" << endl;
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }
    
    string linha,tam;

    getline(file,linha);
    getline(file,linha,',');
    stringstream ss(linha);
    ss >> (*dados_l);
    getline(file,linha,',');
    stringstream ss2(linha);
    ss2 >> (*dados_c);

    float **dados;
    getline(file,linha);
    linha.clear();

    string line;
    dados = new float*[(*dados_l)];
    for(int i=0;i<(*dados_l);i++){
        dados[i] = new float[(*dados_c)];
        for(int j=0;j<(*dados_c);j++){
            getline(file,line,',');
            stringstream s(line);
            s >> dados[i][j]; 
        }
    }

    return dados;
}

void muta_arvore(Arv *arv_inicial) // TODO: resolver problema de malloc(): unaligned fastbin chunk detected 3
{
    //cout << "Arvore escolhida para mutação: " << endl;
    //arv_inicial->imprime();
    //cout << endl;
    int rand_no;
    if(arv_inicial->cont == 0){
        rand_no = 0;
    }else{
        rand_no = rand()%(arv_inicial->cont);

    }
    //cout << "Sub arvore escolhida para mutação: " << endl;
    //sub_arv->imprime();
    //cout << endl;
    Arv *sub_arv = new Arv;
    sub_arv->altura_max = ALTURA_MAX;
    sub_arv->raiz->info = operadores[rand()%operadores.size()];
    sub_arv->implementa(sub_arv->raiz,0,operadores,variaveis,operadores.size(),variaveis.size());

    arv_inicial->remove(sub_arv->raiz,rand_no);
    sub_arv = NULL;
    delete sub_arv;
    //arv_inicial->imprime();
    //cout << endl;
}

void recombina_arvores(Arv *arv1, Arv *arv2){
    
    int rand_no2;
    int rand_no;
    rand_no = rand()%(arv1->cont+1);
    rand_no2 = rand()%(arv2->cont+1);
    if(arv1->cont == 0){
        rand_no = 0;
    }
    if(arv2->cont == 0){
        rand_no2 = 0;
    }


    arv1->setAlturaMax(ALTURA_MAX);
    arv2->setAlturaMax(ALTURA_MAX);
    NoArv *sub1 = arv1->retorna_ponteiro(arv1->raiz,rand_no);
    NoArv *sub2 = arv2->retorna_ponteiro(arv2->raiz,rand_no2);

    arv1->remove(sub2,rand_no);
    arv2->remove(sub1,rand_no2);

    sub1 = NULL;
    sub2 = NULL;
}

//procurar qual o melhor elemento e colocar no vetor filho

void substitui_pop(Arv **pop_inicial,Arv** pop_geracional){
    int mais_eficiente = 0;
    int menos_eficiente = 0;

    for(int i = 0; i < MAX_POP; i++){
        if(pop_inicial[i]->aptidao > pop_inicial[mais_eficiente]->aptidao){
            mais_eficiente = i;
        }
    }

    for(int i = 0; i < MAX_POP; i++){
        if(pop_geracional[i]->aptidao < pop_geracional[menos_eficiente]->aptidao){
            menos_eficiente = i;
        }
    }

    Arv *aux = pop_geracional[menos_eficiente];
    pop_geracional[menos_eficiente] = pop_inicial[mais_eficiente];
    pop_inicial[mais_eficiente] = aux;
    aux = NULL;
}

Arv* torneio_arv(Arv** pop_inicial){
    int rand1; 
    int rand2; 
    rand1 = rand()%MAX_POP;
    rand2 = rand()%MAX_POP;

    if(pop_inicial[rand1]->aptidao > pop_inicial[rand2]->aptidao){
        return pop_inicial[rand1];
    }
    else{
        return pop_inicial[rand2];
    }
}


int main(){

    int size_pop = 10;
    int num_geracoes = 10;

    int seed = 98;
    srand(seed);
    int dados_l;
    int dados_c;
    
    float **dados;
    dados = leArquivo(&dados_l,&dados_c);

    Arv **pop_inicial = new Arv*[MAX_POP]; //Cria vetor de ponteiros para população inicial

    for (int i = 0; i < size_pop; i++)
    {
        pop_inicial[i] = new Arv;
        pop_inicial[i]->altura_max = ALTURA_MAX;
        pop_inicial[i]->raiz->info = operadores[rand()%operadores.size()]; //Inicializa a raiz da arvore com um operador aleatório
        pop_inicial[i]->implementa(pop_inicial[i]->raiz,0,operadores,variaveis,operadores.size(),variaveis.size());
        pop_inicial[i]->calcula_aptidao(dados,dados_l,dados_c);
    }

    
    for(int j=0;j<num_geracoes;j++){

        Arv *rand_arv;
        Arv *rand_arv2;
        Arv **pop_geracional = new Arv*[MAX_POP]; //Cria vetor de ponteiros para população geracional
        for(int i=0;i<size_pop;i+=2){
            pop_geracional[i] = new Arv;
            pop_geracional[i+1] = new Arv;

            rand_arv = torneio_arv(pop_inicial);
            rand_arv2 = torneio_arv(pop_inicial);

            pop_geracional[i]->copia_arvore(rand_arv);
  
            pop_geracional[i+1]->copia_arvore(rand_arv2);

            recombina_arvores(pop_geracional[i], pop_geracional[i+1]);
            muta_arvore(pop_geracional[i]);
            muta_arvore(pop_geracional[i+1]);

            pop_geracional[i]->calcula_aptidao(dados,dados_l,dados_c);
        }
        
        substitui_pop(pop_inicial,pop_geracional);

        for(int k=0;k<size_pop;k++){
            delete pop_inicial[k];
        }
        
        pop_inicial = pop_geracional;

        pop_geracional = NULL;

        rand_arv2 = NULL;
        rand_arv = NULL;
    }

/*
Tendência crescente: uma tendência crescente indica que a métrica está se deteriorando.
Os dados de feedback estão se tornando significativamente diferentes dos dados de treinamento.

Tendência de queda: uma tendência de queda indica que a métrica está melhorando.
Isso significa que o novo treinamento do modelo é efetivo.
*/


    return 0;
}