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

void muta_arvore(Arv *arv_inicial, Arv* sub_arv, int rand_no)
{
    //cout << "Arvore escolhida para mutação: " << endl;
    //arv_inicial->imprime();
    //cout << endl;
    //cout << "Sub arvore escolhida para mutação: " << endl;
    //sub_arv->imprime();
    //cout << endl;
    arv_inicial->remove(sub_arv->raiz,rand_no);
    //cout << "Arvore mutada: " << endl;
    //arv_inicial->imprime();
    //cout << endl;
}

void recombina_arvores(Arv *arv1, Arv *arv2,int size_pop, int seed){
    srand(seed);
    int rand_no2;
    int rand_no;
/*
    cout << "Arvores escolhidas para recombinação: " << endl;
    arv1->imprime();
    cout << endl;
    arv2->imprime();
    cout << endl;
*/
    //cout << "Nós selecionados para recombinação: " << endl;
    rand_no = rand()%(arv1->cont+1);
    //arv1->auxImprime(&arv1->nos[rand_no]);
    //cout << endl;
    rand_no2 = rand()%(arv2->cont+1);
    //arv2->auxImprime(&arv2->nos[rand_no2]);
    //cout << endl;

    arv1->setAlturaMax(15);
    arv2->setAlturaMax(15);
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

void evolucao(Arv **pop_inicial,Arv** primeira_geracao, int size_pop, int size_geracao){
    int mais_eficiente = 0;
    int menos_eficiente = 0;

    for(int i = 0; i < size_pop; i++){
        if(pop_inicial[i]->aptidao > pop_inicial[mais_eficiente]->aptidao){
            mais_eficiente = i;
        }
    }

    for(int i = 0; i < size_geracao; i++){
        if(primeira_geracao[i]->aptidao < primeira_geracao[menos_eficiente]->aptidao){
            menos_eficiente = i;
        }
    }

    primeira_geracao[menos_eficiente] = pop_inicial[mais_eficiente]; 
}

int main(){


    Arv **pop_inicial = new Arv*[100];
    char operadores[4] = {'+', '-', '*', '/'};
    char variaveis[3] = {'x', 'y', 'z'};
    int size_op = sizeof(operadores)/sizeof(operadores[0]);
    int size_var = sizeof(variaveis)/sizeof(variaveis[0]);
    int size_pop = 50;

    int seed = 98;
    int x[10];
    int y[10];
    int z[10];
    float valor_esperado[10];
    leArquivo(x,y,z,valor_esperado);


    for (int i = 0; i < size_pop; i++)
    {
        pop_inicial[i] = new Arv;
        pop_inicial[i]->altura_max = 15;
        pop_inicial[i]->raiz->info = operadores[rand()%size_op];
        pop_inicial[i]->implementa(pop_inicial[i]->raiz,0,operadores,variaveis,size_op,size_var);
        //pop_inicial[i]->imprime();
        //cout << endl;
    }

    Arv **primeira_geracao = new Arv*[100];
    //cout << "Arvores da primeira geração: " << endl;
    for (int i = 0; i < size_pop; i++)
    {
        primeira_geracao[i] = new Arv;
        pop_inicial[i]->copia_arvore(primeira_geracao[i]);
        //primeira_geracao[i]->imprime();
        //cout << endl;
    }
    

    for(int i=0;i<1;i++){
        int rand_arv; 
        int rand_arv2; 
        rand_arv = rand()%size_pop;
        rand_arv2 = rand()%size_pop;

        recombina_arvores(primeira_geracao[rand_arv], primeira_geracao[rand_arv2], size_pop,seed);


        rand_arv = rand()%size_pop;
        rand_arv2 = rand()%size_pop;
        int rand_no = rand()%(primeira_geracao[rand_arv]->cont+1);
        muta_arvore(primeira_geracao[rand_arv],primeira_geracao[rand_arv2],rand_no);
        
        for (int i = 0; i < size_pop; i++)
        {
            pop_inicial[i]->calcula_aptidao(x,y,z,valor_esperado,10);
            //cout << "Aptidão obtida pela arvore " << i << ": "<< pop_inicial[i]->aptidao << endl;
        }


        for (int i = 0; i < size_pop; i++)
        {
            primeira_geracao[i]->calcula_aptidao(x,y,z,valor_esperado,10);
            //cout << "Aptidão obtida pela arvore recombinada " << i << ": "<< primeira_geracao[i]->aptidao << endl;
        }

        evolucao(pop_inicial,primeira_geracao,size_pop,size_pop);
        
    }


    //conferir se cálculo esta sendo feito corretamente
    //conferir se a aptidao esta sendo calculada corretamente


    return 0;
}