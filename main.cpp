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



//procurar qual o melhor elemento e colocar no vetor filho

void substituiPop(Arv **pop_inicial,Arv** pop_geracional, int size_pop){
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

Arv* torneioArv(Arv** pop_inicial, int size_pop){
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
        pop_inicial[i]->calculaAptidao(dados,dados_l);
    }

    
    for(int j=0;j<num_geracoes;j++){

        Arv *rand_arv;
        Arv *rand_arv2;
        Arv **pop_geracional = new Arv*[MAX_POP]; //Cria vetor de ponteiros para população geracional

        for(int i=0;i<size_pop;i+=2){
            pop_geracional[i] = new Arv;
            pop_geracional[i+1] = new Arv;
            

            rand_arv = torneioArv(pop_inicial, size_pop);
            rand_arv2 = torneioArv(pop_inicial, size_pop);
            
            cout << "Geração j = " << j << " e indivíduo i = " << i << endl;
            cout << "População parental: " << endl;
            rand_arv->imprime();
            cout << endl;
            rand_arv2->imprime();
            cout << endl;
            

            pop_geracional[i]->copiaArv(rand_arv->raiz);
            pop_geracional[i]->cont = rand_arv->cont;
            pop_geracional[i+1]->copiaArv(rand_arv2->raiz);
            pop_geracional[i+1]->cont = rand_arv2->cont;

            cout << "População geracional: " << endl;
            pop_geracional[i]->imprime();
            cout << endl;
            pop_geracional[i+1]->imprime();
            cout << endl;

            pop_geracional[i]->recombinaArv(pop_geracional[i+1]);
            
            cout << "População geracional após recombinação: " << endl;
            pop_geracional[i]->imprime();
            cout << endl;
            pop_geracional[i+1]->imprime();
            cout << endl;
            
            pop_geracional[i]->mutaArv();
            pop_geracional[i+1]->mutaArv();
            cout << "População geracional após mutação: " << endl;
            pop_geracional[i]->imprime();
            cout << endl;
            pop_geracional[i+1]->imprime();
            cout << endl;
            pop_geracional[i]->cont = pop_geracional[i]->countNodes(pop_geracional[i]->raiz);
            pop_geracional[i+1]->cont = pop_geracional[i+1]->countNodes(pop_geracional[i+1]->raiz);
            pop_geracional[i]->calculaAptidao(dados,dados_l);
            pop_geracional[i+1]->calculaAptidao(dados,dados_l);
        }
        
        substituiPop(pop_inicial,pop_geracional,size_pop);
        
        
        for (int k = 0; k < size_pop; k++) {
            delete pop_inicial[k];  // Deleta dados antigos de pop_inicial
            pop_inicial[k] = pop_geracional[k];  // Transfere o ponteiro
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

    return 0;
}
/*
Tendência crescente: uma tendência crescente indica que a métrica está se deteriorando.
Os dados de feedback estão se tornando significativamente diferentes dos dados de treinamento.

Tendência de queda: uma tendência de queda indica que a métrica está melhorando.
Isso significa que o novo treinamento do modelo é efetivo.
*/