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
#define ALTURA_MAX 30
#define MAX_POP 1000
#define MAX_GER 100

vector<char> variaveis = {'x','y','z'};
vector<char> operadores = {'+','-','*','/'};

using namespace std;

void leArquivo(float **dados, int dados_l, int dados_c){
    fstream file;
    file.open("data.csv", ios::in);

    if(file.is_open()){
        cout << "Arquivo aberto com sucesso" << endl;
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    string line, word;

    int i,j = 0;
    string linha;

    getline(file,linha,',');
    getline(file,linha,'\n');
    getline(file,linha,',');
    getline(file,linha,',');
    getline(file,linha,',');
    getline(file,linha,'\n');
    linha.clear();

    stringstream ss(line);
    
    //trocar codigo

    
    
    dados_c = stof(word);

    for(int i=0;getline(file,line);i++){
        stringstream s(line);
        
        for(int j=0;getline(s,word,',');j++){
            getline(s,word,',');
            s >> dados[i][j]; 
        }
    }

    return;
}

void muta_arvore(Arv *arv_inicial)
{
    //cout << "Arvore escolhida para mutação: " << endl;
    //arv_inicial->imprime();
    //cout << endl;
    int rand_no = rand()%(arv_inicial->cont+1);
    //cout << "Sub arvore escolhida para mutação: " << endl;
    //sub_arv->imprime();
    //cout << endl;
    Arv *sub_arv = new Arv;
    sub_arv->implementa(sub_arv->raiz,0,operadores,variaveis,operadores.size(),operadores.size());

    arv_inicial->remove(sub_arv->raiz,rand_no);
    //cout << "Arvore mutada: " << endl;
    //arv_inicial->imprime();
    //cout << endl;
}

void recombina_arvores(Arv *arv1, Arv *arv2,int size_pop){
    
    int rand_no2;
    int rand_no;
    rand_no = rand()%(arv1->cont+1);
    rand_no2 = rand()%(arv2->cont+1);
/*
    cout << "Arvores escolhidas para recombinação: " << endl;
    arv1->imprime();
    cout << endl;
    arv2->imprime();
    cout << endl;
*/
    //cout << "Nós selecionados para recombinação: " << endl;
    //arv1->auxImprime(&arv1->nos[rand_no]);
    //cout << endl;
    //arv2->auxImprime(&arv2->nos[rand_no2]);
    //cout << endl;

    arv1->setAlturaMax(ALTURA_MAX);
    arv2->setAlturaMax(ALTURA_MAX);
    NoArv *sub1 = arv1->retorna_ponteiro(arv1->raiz,rand_no);
    NoArv *sub2 = arv2->retorna_ponteiro(arv2->raiz,rand_no2);

    arv1->remove(sub2,rand_no);
    arv2->remove(sub1,rand_no2);

/*
    cout << "\nArvores recombinadas: " << endl;
    arv1->imprime();
    cout << endl;
    arv2->imprime();
    cout << endl;
*/
}

//procurar qual o melhor elemento e colocar no vetor filho

void evolucao(Arv **pop_inicial,Arv** pop_geracional){
    int mais_eficiente = 0;
    int menos_eficiente = 0;

    for(int i = 0; i < MAX_POP; i++){
        if(pop_inicial[i]->aptidao > pop_inicial[mais_eficiente]->aptidao){
            mais_eficiente = i;
        }
    }

    for(int i = 0; i < MAX_GER; i++){
        if(pop_geracional[i]->aptidao < pop_geracional[menos_eficiente]->aptidao){
            menos_eficiente = i;
        }
    }

    pop_geracional[menos_eficiente] = pop_inicial[mais_eficiente]; 
}

int main(){


    Arv **pop_inicial = new Arv*[MAX_POP];
    //char operadores[4] = {'+', '-', '*', '/'};
    //char variaveis[3] = {'x', 'y', 'z'};
    //int size_op = sizeof(operadores)/sizeof(operadores[0]);
    //int size_var = sizeof(variaveis)/sizeof(variaveis[0]);
    int size_pop = MAX_POP;
    int num_geracoes = MAX_GER;

    int seed = 98;
    float **dados;
    int dados_l;
    int dados_c;
    /*
    int x[10];
    int y[10];
    int z[10];
    float valor_esperado[10];
    */
    leArquivo(dados,dados_l,dados_c);

    for (int i = 0; i < size_pop; i++)
    {
        pop_inicial[i] = new Arv;
        pop_inicial[i]->altura_max = ALTURA_MAX;
        pop_inicial[i]->raiz->info = operadores[rand()%operadores.size()];
        pop_inicial[i]->implementa(pop_inicial[i]->raiz,0,operadores,variaveis,operadores.size(),operadores.size());
        //pop_inicial[i]->imprime();
        //cout << endl;
    }

    Arv **pop_geracional = new Arv*[MAX_POP];
    //cout << "Arvores da primeira geração: " << endl;
    

    for(int i=0;i<num_geracoes;i++){

        pop_geracional[i] = new Arv;
        pop_geracional[i+1] = new Arv;

        for(int i=0;i<size_pop;i++){
            int rand_arv; 
            int rand_arv2; 
            rand_arv = rand()%size_pop;
            rand_arv2 = rand()%size_pop;
            pop_inicial[rand_arv]->copia_arvore(pop_geracional[i]);
            pop_inicial[rand_arv2]->copia_arvore(pop_geracional[i+1]);

            recombina_arvores(pop_geracional[i], pop_geracional[i+2], size_pop);

            muta_arvore(pop_geracional[i]);
            muta_arvore(pop_geracional[i+1]);

            for (int i = 0; i < size_pop; i++)
            {
                pop_inicial[i]->calcula_aptidao(dados);
            }


            for (int i = 0; i < size_pop; i++)
            {
                pop_geracional[i]->calcula_aptidao(dados);

            }

            evolucao(pop_inicial,pop_geracional);

        }

    }

    //conferir se cálculo esta sendo feito corretamente
    //conferir se a aptidao esta sendo calculada corretamente


    return 0;
}