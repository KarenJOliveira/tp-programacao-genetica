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
#define MAX_GER 50


using namespace std;

float** leArquivo(int *dados_l,int *dados_c){
    
    fstream file;
    file.open("function_9_data.csv", ios::in);

    if(file.is_open()){
        cout << "Arquivo aberto com sucesso" << endl;
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }
    string line;
    for(int i = 0;i<2;i++){
        getline(file,line,',');
        if(line == "rows"){
            getline(file,line);
            stringstream ss(line);
            ss >> *dados_l;
        }else{
            getline(file,line);
            stringstream ss(line);
            ss >> *dados_c;
        }
    }
    getline(file,line);
    line.clear();

    float **dados = new float*[*dados_l];
    for(int l=0;l<*dados_l+1;l++){
        dados[l] = new float[*dados_c];
        for(int c=0;c<*dados_c-1;c++){
            string line;
            getline(file,line,',');
            stringstream ss(line);
            ss >> dados[l][c];  
        }
        getline(file,line);
        stringstream ss(line);
        ss >> dados[l][*dados_c-1];
    }
    
    return dados;
}
/*
Arv* leArv(){
    Arv **pop_melhores = new Arv*[MAX_POP];
    
    fstream file;
    file.open("pop_melhores/funcao9.csv", ios::in);
    if(file.is_open()){
        cout << "Arquivo aberto com sucesso" << endl;
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }
    string line;
    getline(file,line);
    line.clear();
    while(getline(file,line)){
        stringstream ss(line);
        string aptidao;
        string arv_expression;
        Arv *arv = new Arv;
        getline(ss,aptidao,',');
        arv->aptidao = stof(aptidao);
        
    }
}
*/

void createFile(Arv *melhor_arv){
    //cout << "Criando arquivo" << endl;
    string arv_expression = "";
    string nome_arquivo = "pop_melhores/funcao9.csv";
    fstream file;
    file.open(nome_arquivo, ios::out);
    if(file.is_open()){
        cout << "Arquivo aberto com sucesso" << endl;
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    arv_expression = melhor_arv->retornaArvExp();
    file << "aptidao,arvore" << "\n";
    file << melhor_arv->aptidao << "," << arv_expression << "\n";
    file.close();
}



//procurar qual o melhor elemento e colocar no vetor filho

void substituiPop(Arv **pop_inicial,Arv** pop_geracional, int size_pop){
    int mais_eficiente = 0;
    int menos_eficiente = 0;

    for(int i = 0; i < size_pop; i++){
        if(pop_inicial[i]->aptidao < pop_inicial[mais_eficiente]->aptidao){
            mais_eficiente = i;
        }
    }

    for(int i = 0; i < size_pop; i++){
        if(pop_geracional[i]->aptidao > pop_geracional[menos_eficiente]->aptidao){
            menos_eficiente = i;
        }
    }

    pop_geracional[menos_eficiente]->liberar();
    pop_geracional[menos_eficiente]->copiaArv(pop_inicial[mais_eficiente]->raiz);
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

    int size_pop = 500;
    int num_geracoes = 50;
    float taxa_cruzamento = 90;
    float taxa_mutacao = 90;
    
    int seed = 98;
    srand(seed);
    int dados_l;
    int dados_c;
    
    float **dados;
    dados = leArquivo(&dados_l,&dados_c);
    Arv **pop_melhores = new Arv*[MAX_POP];

    Arv **pop_inicial = new Arv*[MAX_POP]; //Cria vetor de ponteiros para população inicial
    for (int i = 0; i < size_pop; i++)
    {
        pop_inicial[i] = new Arv;
        pop_inicial[i]->altura_max = ALTURA_MAX;
        pop_inicial[i]->raiz->info = operadores[rand()%operadores.size()]; //Inicializa a raiz da arvore com um operador aleatório
        pop_inicial[i]->implementa(pop_inicial[i]->raiz,0,operadores,variaveis,operadores.size(),variaveis.size());
        int idx = 0;
        pop_inicial[i]->alteraIndices(pop_inicial[i]->raiz,&idx);
        pop_inicial[i]->cont = pop_inicial[i]->countNodes(pop_inicial[i]->raiz);
        pop_inicial[i]->calculaAptidao(dados,dados_l,dados_c);
    }

    int j;
    for(j=0;j<num_geracoes;j++){

        Arv *rand_arv;
        Arv *rand_arv2;
        Arv **pop_geracional = new Arv*[MAX_POP]; //Cria vetor de ponteiros para população geracional
        //cout << "Geração j = " << j << endl;
        for(int i=0;i<size_pop;i+=2){
            pop_geracional[i] = new Arv;
            pop_geracional[i+1] = new Arv;
            

            rand_arv = torneioArv(pop_inicial, size_pop);
            rand_arv2 = torneioArv(pop_inicial, size_pop);
            
            pop_geracional[i]->copiaArv(rand_arv->raiz);
            pop_geracional[i]->cont = rand_arv->cont;
            pop_geracional[i+1]->copiaArv(rand_arv2->raiz);
            pop_geracional[i+1]->cont = rand_arv2->cont;


            if(rand()%100 < taxa_cruzamento){
                pop_geracional[i]->recombinaArv(pop_geracional[i+1]);
            }
            
            if(rand()%100 < taxa_mutacao){
                pop_geracional[i]->mutaArv();
                pop_geracional[i+1]->mutaArv();
            }
            
            pop_geracional[i]->calculaAptidao(dados,dados_l,dados_c);
            //cout << "Aptidão do primeiro filho: " << pop_geracional[i]->aptidao << endl;
            pop_geracional[i+1]->calculaAptidao(dados,dados_l,dados_c);
            //cout << "Aptidão do segundo filho: " << pop_geracional[i+1]->aptidao << endl;
        }
        
        substituiPop(pop_inicial,pop_geracional,size_pop);
        
        
        for (int k = 0; k < size_pop; k++) {
            pop_inicial[k]->liberar();  // Deleta dados antigos de pop_inicial
            pop_inicial[k]->copiaArv(pop_geracional[k]->raiz);
            pop_inicial[k]->cont = pop_geracional[k]->cont;
            pop_inicial[k]->calculaAptidao(dados,dados_l,dados_c);
            // cout << "População geracional: " << endl;
            // pop_geracional[k]->imprime();
            // cout << endl;
            pop_geracional[k]->liberar();  // Deleta dados de pop_geracional
        }

        int mais_eficiente = 0;
        int apt1, apt2;
        for (int i = 1; i < size_pop; i++)
        {
            apt1 = pop_inicial[i]->aptidao;
            apt2 = pop_inicial[mais_eficiente]->aptidao;
            
            if(pop_inicial[i]->aptidao < pop_inicial[mais_eficiente]->aptidao){
                mais_eficiente = i;
            }
        }
        
        //cout << pop_inicial[mais_eficiente]->aptidao << endl;
        
        pop_melhores[j] = new Arv;
        pop_melhores[j]->copiaArv(pop_inicial[mais_eficiente]->raiz);
        pop_melhores[j]->cont = pop_inicial[mais_eficiente]->cont;
        pop_melhores[j]->aptidao = pop_inicial[mais_eficiente]->aptidao;

        delete[] pop_geracional;
    }

    //avaliar a população final
    //int melhor = 0;
    for (int i = 0; i < j; i++)
    {
        // if(pop_melhores[i]->aptidao < pop_melhores[melhor]->aptidao){
        //     melhor = i;
        // }
        createFile(pop_melhores[i]);
        delete pop_melhores[i];
    }

    for (int i = 0; i < size_pop; i++) {
        delete pop_inicial[i];  // Delete old data in pop_inicial
    }   

    delete [] pop_melhores;
    delete [] pop_inicial;

    return 0;
}
/*
Tendência crescente: uma tendência crescente indica que a métrica está se deteriorando.
Os dados de feedback estão se tornando significativamente diferentes dos dados de treinamento.

Tendência de queda: uma tendência de queda indica que a métrica está melhorando.
Isso significa que o novo treinamento do modelo é efetivo.
*/