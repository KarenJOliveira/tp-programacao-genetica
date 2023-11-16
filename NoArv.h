//
// Created by karen on 17/08/2023.
//

#ifndef UNTITLED_NOARV_H
#define UNTITLED_NOARV_H

#include "Pilha.h"
#include <iostream>
#include <random>
#include <vector>
#define MAX 1000
#define ALTURA_MAX 10
using namespace std;

typedef struct NoArv
{
public:
    char info;
    int idx;
    NoArv *filho_esquerda;
    NoArv *filho_direita;
    bool ehOperador;

    NoArv(){
        info = '\0';
        idx = 0;
        ehOperador = false;
        filho_esquerda = NULL;
        filho_direita = NULL;
    };

    NoArv* getLeftChild() { return filho_esquerda; }
    NoArv* getRightChild() { return filho_direita; }
    void setLeftChild(NoArv* left) { filho_esquerda = left; }
    void setRightChild(NoArv* right) { filho_direita = right; }
    void setInfo(char info) { this->info = info; }
    char getInfo() { return info; }
    void setId(int id) { idx = id; }
    int getId() { return idx; }

}NoArv;

typedef struct Arv
{
    
    NoArv *raiz ;
    int cont; // quantidade de nós no vetor N-1
    int altura_max;

    float aptidao;
public:
    Arv(){
        raiz = new NoArv;
        cont = 0;
        altura_max = ALTURA_MAX;
        aptidao = 0;
    }

    ~Arv(){
        liberar();
    }

    void setAlturaMax(int altura){
        altura_max = altura;
    }

    NoArv* getRoot() { return raiz; }
    NoArv* aloca_no();
    NoArv* libera(NoArv *no);
    void liberar();
    void imprime();
    void auxImprime(NoArv *no);
    void implementa(NoArv *no,int altura, vector<char> operadores, vector<char> variaveis, int size_op, int size_var);
    void empilha_arv(NoArv *no,Pilha *p);
    void calcula_aptidao(float **dados, int dados_l);
    int contaNos(NoArv *no);
    void remove(NoArv *sub_raiz, int val);
    NoArv* auxRemove(NoArv *no_atual, NoArv *novo, int idx);
    NoArv* retorna_ponteiro(NoArv *no, int idx);
    void changeNodeIndices(NoArv* root, int& index);
    void copia_arv(NoArv *source);
    NoArv* copyTree(NoArv* source);
}Arv;


NoArv* Arv::aloca_no()
{
    if(cont < MAX){
        cont++;
       
        NoArv *no = new NoArv;
        no->idx = cont;
        return no;
    }
    return NULL;
}

void Arv::imprime(){
    auxImprime(raiz);
}

void Arv::auxImprime(NoArv *no){
    if(no != NULL){
        auxImprime(no->filho_esquerda);
        auxImprime(no->filho_direita);
        
        cout << no->info << " ";
    }
}

NoArv* Arv::libera(NoArv *no)
{
    if(no != NULL)
    {
        no->filho_esquerda = libera(no->filho_esquerda);
        no->filho_direita = libera(no->filho_direita);
        delete no;
        cont--;
    }
    return no;
}
void Arv::liberar()
{
    raiz = libera(raiz);
    aptidao = -1;
}

void Arv::implementa(NoArv *no,int altura, vector<char> operadores, vector<char> variaveis, int size_op, int size_var)
{
    if(altura == altura_max){

        no->info = operadores[rand()%size_op];
        no->ehOperador = true;

        no->filho_esquerda = aloca_no();
        no->filho_direita = aloca_no();
        no->filho_esquerda->info = variaveis[rand()%size_var];
        no->filho_direita->info = variaveis[rand()%size_var];
        return;
    }

    if(rand()%100 > 45){
        no->info = operadores[rand()%size_op];
        no->ehOperador = true;
    }else{
        no->info = variaveis[rand()%size_var];
        return;
    }
    no->filho_esquerda = aloca_no();
    no->filho_direita = aloca_no();

    implementa(no->filho_esquerda,altura+1,operadores,variaveis,size_op,size_var);
    implementa(no->filho_direita,altura+1,operadores,variaveis,size_op,size_var);
}

void Arv::empilha_arv(NoArv *no,Pilha *p){
    if(no == NULL){
        return;
    }

    empilha_arv(no->filho_esquerda,p);
    empilha_arv(no->filho_direita,p);

    if(no->ehOperador){
        Item aux;
        aux.n = static_cast<float>(no->info);
        aux.ehOperador = true;
        p->empilha(aux);
    }else{
        Item aux;
        aux.n = static_cast<float>(no->info);
        aux.ehOperador = false;
        p->empilha(aux);
    }
}
void Arv::copia_arv(NoArv *source){
    raiz = copyTree(source);
}

NoArv* Arv::copyTree(NoArv* source) {
    if (source == nullptr) {
        return nullptr;
    }

    // Create a new node in the destination tree with the same value
    NoArv* destination = new NoArv;
    destination->info = source->info;
    destination->idx = source->idx;
    if(source->ehOperador){
        destination->ehOperador = source->ehOperador;
    }else{
        destination->ehOperador = source->ehOperador;
        return destination;
    }

    // Recursively copy the left and right subtrees
    destination->filho_esquerda = copyTree(source->filho_esquerda);
    destination->filho_direita = copyTree(source->filho_direita);

    return destination;
}

void Arv::calcula_aptidao(float **dados, int dados_l){
    Pilha *p = new Pilha;
    this->empilha_arv(this->raiz,p);
    float resultado = 0;
    float somatorio = 0;
    float diferenca = 0;
    

    for(int i=0;i<dados_l;i++){
        resultado = p->resolve_operacoes(dados[i][0], dados[i][1], dados[i][2]); //Substitui as variaveis pelos valores nos dados e resolve a expressão gerada pelos nós
        diferenca = dados[i][3] - resultado;
        somatorio += pow(diferenca,2); // Calcula o somatório do erro quadrático(Média da diferença quadrática entre a predição do modelo e o valor de destino)
    }

    this->aptidao = somatorio;
    
    delete p;
}

int Arv::contaNos(NoArv *no)
{
    if(no != NULL)
        return 1 + contaNos(no->filho_esquerda) + contaNos(no->filho_direita);
    else
        return 0;
}

NoArv* Arv::retorna_ponteiro(NoArv *no, int idx){
    if(no == NULL){
        return NULL;
    }else if(no->idx == idx){ //procura nó com o índice passado e o retorna seu ponteiro
        NoArv *aux = no;
        return aux;
    }else{
        NoArv *aux = retorna_ponteiro(no->filho_esquerda,idx);
        if(aux == NULL){
            aux = retorna_ponteiro(no->filho_direita,idx);
        }
        return aux;
    }
}

void Arv::remove(NoArv *sub_raiz, int idx)
{
    this->raiz = auxRemove(this->raiz, sub_raiz, idx);
}

NoArv* Arv::auxRemove(NoArv *no_atual, NoArv *novo, int idx)
{
    if(no_atual == NULL)
    {
        return NULL;
    }
    else if(no_atual->idx == idx){
        
        changeNodeIndices(novo, idx);
        libera(no_atual);
        
        return novo;
    }

    no_atual->filho_esquerda = auxRemove(no_atual->filho_esquerda,novo,idx);
    no_atual->filho_direita = auxRemove(no_atual->filho_direita,novo,idx);
    return no_atual;
}


void Arv::changeNodeIndices(NoArv* root, int& index) {
    if (root == nullptr) {
        return;
    }

    // Change the index of the current node
    root->idx = index;
    index++;

    // Recursively change indices of left subtree
    changeNodeIndices(root->filho_esquerda, index);

    // Recursively change indices of right subtree
    changeNodeIndices(root->filho_direita, index);
}


#endif //UNTITLED_NOARV_H
