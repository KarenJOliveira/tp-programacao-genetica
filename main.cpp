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

void recombina_arvores(Arv** arvores, Arv **recombinadas,int size_pop, int seed){
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
        cout << "Arvores escolhidas para recombinação: " << endl;
        arvores[rand_arv]->imprime();
        cout << endl;
        arvores[rand_arv2]->imprime();
        cout << endl;

        rand_no = rand()%(arvores[rand_arv]->cont+1);
        rand_no2 = rand()%(arvores[rand_arv2]->cont+1);

        rand_altura = rand()%10;

        recombinadas[i] = new Arv;
        recombinadas[i+1] = new Arv;
        recombinadas[i]->setAlturaMax(rand_altura);
        recombinadas[i+1]->setAlturaMax(rand_altura);
        recombinadas[i]->implementa_copia(recombinadas[i]->raiz,arvores[rand_arv]->raiz,rand_no);
        recombinadas[i+1]->implementa_copia(recombinadas[i+1]->raiz,arvores[rand_arv2]->raiz,rand_no2);

        recombinadas[i]->complementa_copia(&recombinadas[i]->nos[rand_no],&arvores[rand_arv2]->nos[rand_no2]);
        recombinadas[i+1]->complementa_copia(&recombinadas[i+1]->nos[rand_no2],&arvores[rand_arv]->nos[rand_no]);

        cout << "\nArvores recombinadas: " << endl;
        recombinadas[i]->imprime();
        cout << endl;
        recombinadas[i+1]->imprime();
        cout << endl;

        i+=2;
    }
}

int main(){


    Arv **pop_inicial = new Arv*[100];
    char operadores[4] = {'+', '-', '*', '/'};
    char variaveis[3] = {'x', 'y', 'z'};
    int size_op = sizeof(operadores)/sizeof(operadores[0]);
    int size_var = sizeof(variaveis)/sizeof(variaveis[0]);
    int size_pop = 10;


    for (int i = 0; i < size_pop; i++)
    {
        int rand_alt = rand()%15;
        pop_inicial[i] = new Arv;
        pop_inicial[i]->setAlturaMax(rand_alt);
        pop_inicial[i]->implementa(pop_inicial[i]->raiz,0,operadores,variaveis,size_op,size_var);
    }

    int x[10];
    int y[10];
    int z[10];
    float valor_esperado[10];

    Arv **recombinadas = new Arv*[100];
    recombina_arvores(pop_inicial, recombinadas, size_pop,98);
/*
    for(int i=0;i<size_pop;i++){
        cout << "Arvore " << i << endl;
        pop_inicial[i]->imprime();
        cout << endl;
    }

    for(int i=0;i<size_pop;i++){
        cout << "Arvore recombinada: " << i << endl;
        recombinadas[i]->imprime();
        cout << endl;
    }
*/
    leArquivo(x,y,z,valor_esperado);

    for (int i = 0; i < size_pop; i++)
    {
        pop_inicial[i]->calcula_aptidao(x,y,z,valor_esperado,10);
        cout << "Aptidão obtida pela arvore " << i << ": "<< pop_inicial[i]->aptidao << endl;
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

    Arv sub_arv1;
    sub_arv1.setAlturaMax(3);
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
*/

    return 0;
}