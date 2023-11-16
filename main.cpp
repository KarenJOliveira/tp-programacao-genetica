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
#define MAX_POP 5000
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
        for(int j=0;j<(*dados_c)-1;j++){
            getline(file,line,',');
            //cout << line << endl;
            stringstream s(line);
            s >> dados[i][j]; 
        }
        getline(file,line);
        //cout << line << endl;
        stringstream s(line);
        s >> dados[i][(*dados_c)-1];
    }

    return dados;
}

void muta_arvore(Arv *arv_inicial) // TODO: resolver problema de malloc(): unaligned fastbin chunk detected 3
{
    int rand_no;

    if(arv_inicial->cont == 0){
        rand_no = 0;
    }else{
        rand_no = rand()%(arv_inicial->cont);
    }
   
    Arv *sub_arv = new Arv;
    sub_arv->altura_max = ALTURA_MAX;
    sub_arv->raiz->info = operadores[rand()%operadores.size()];
    sub_arv->implementa(sub_arv->raiz,0,operadores,variaveis,operadores.size(),variaveis.size());

    Arv *aux = new Arv;
    aux->raiz = arv_inicial->retorna_ponteiro(arv_inicial->raiz,rand_no);
    arv_inicial->remove(sub_arv->raiz,rand_no);
    sub_arv = NULL;
    delete sub_arv;

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
    Arv *aux = new Arv;
    Arv *aux2 = new Arv;
    NoArv *sub1;
    sub1 = arv1->retorna_ponteiro(arv1->raiz,rand_no);
    aux->copia_arv(sub1);
    NoArv *sub2;
    sub2 = arv2->retorna_ponteiro(arv2->raiz,rand_no2);
    aux2->copia_arv(sub2);

    arv1->remove(aux2->raiz,rand_no);
    arv2->remove(aux->raiz,rand_no2);

    aux = NULL;
    delete aux;
    aux2 = NULL;
    delete aux2;
}

//procurar qual o melhor elemento e colocar no vetor filho

void substitui_pop(Arv **pop_inicial,Arv** pop_geracional, int size_pop){
    int mais_eficiente = 0;
    int menos_eficiente = 0;

    for(int i = 0; i < size_pop; i++){
        if(pop_inicial[i]->aptidao > pop_inicial[mais_eficiente]->aptidao){
            mais_eficiente = i;
        }
    }

    for(int i = 0; i < size_pop; i++){
        if(pop_geracional[i]->aptidao < pop_geracional[menos_eficiente]->aptidao){
            menos_eficiente = i;
        }
    }

    Arv *aux = pop_geracional[menos_eficiente];
    pop_geracional[menos_eficiente] = pop_inicial[mais_eficiente];
    pop_inicial[mais_eficiente] = aux;
    aux = NULL;
}

Arv* torneio_arv(Arv** pop_inicial, int size_pop){
    int rand1; 
    int rand2; 
    rand1 = rand()%size_pop;
    rand2 = rand()%size_pop;

    if(pop_inicial[rand1]->aptidao > pop_inicial[rand2]->aptidao){
        return pop_inicial[rand1];
    }
    else{
        return pop_inicial[rand2];
    }
}


int main(){

    int size_pop = 100;
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
        pop_inicial[i]->calcula_aptidao(dados,dados_l);
    }

    
    for(int j=0;j<num_geracoes;j++){

        Arv *rand_arv;
        Arv *rand_arv2;
        Arv **pop_geracional = new Arv*[MAX_POP]; //Cria vetor de ponteiros para população geracional

        for(int i=0;i<size_pop;i+=2){
            pop_geracional[i] = new Arv;
            pop_geracional[i+1] = new Arv;
            

            rand_arv = torneio_arv(pop_inicial, size_pop);
            rand_arv2 = torneio_arv(pop_inicial, size_pop);
            cout << "População parental: " << endl;
            rand_arv->imprime();
            cout << endl;
            rand_arv2->imprime();
            cout << endl;
            

            pop_geracional[i]->copia_arv(rand_arv->raiz);
            pop_geracional[i]->cont = rand_arv->cont;
            pop_geracional[i+1]->copia_arv(rand_arv2->raiz);
            pop_geracional[i+1]->cont = rand_arv2->cont;

            recombina_arvores(pop_geracional[i], pop_geracional[i+1]);
            cout << "População geracional após recombinação: " << endl;
            pop_geracional[i]->imprime();
            cout << endl;
            pop_geracional[i+1]->imprime();
            cout << endl;
            
            muta_arvore(pop_geracional[i]);
            muta_arvore(pop_geracional[i+1]);
            cout << "População geracional após mutação: " << endl;
            pop_geracional[i]->imprime();
            cout << endl;
            pop_geracional[i+1]->imprime();
            cout << endl;

            pop_geracional[i]->calcula_aptidao(dados,dados_l);
        }
        
        substitui_pop(pop_inicial,pop_geracional,size_pop);
        
        
        // for (int k = 0; k < size_pop; k++) { 
            
        //     cout << "População geracional: " << endl;
        //     pop_geracional[k]->imprime();
        //     cout << endl;
        // }
        
        for (int k = 0; k < size_pop; k++) {
            delete pop_inicial[k];  // Delete old data in pop_inicial
            pop_inicial[k] = pop_geracional[k];  // Transfer the pointer
            // cout << "População geracional: " << endl;
            // pop_geracional[k]->imprime();
            // cout << endl;
            pop_geracional[k] = nullptr;  // Set pop_geracional[k] to nullptr to avoid deleting it later
        }

        delete[] pop_geracional;
    }

for (int k = 0; k < size_pop; k++) {
    delete pop_inicial[k];  // Delete old data in pop_inicial
}
delete [] pop_inicial;
/*
Tendência crescente: uma tendência crescente indica que a métrica está se deteriorando.
Os dados de feedback estão se tornando significativamente diferentes dos dados de treinamento.

Tendência de queda: uma tendência de queda indica que a métrica está melhorando.
Isso significa que o novo treinamento do modelo é efetivo.
*/


    return 0;
}