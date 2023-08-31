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

}NoArv;

typedef struct Arv
{
    NoArv *raiz;

    NoArv nos[MAX]; // vetor que armazena os nós
    int cont; // quantidade de nós no vetor N-1
    int altura_max;


    Arv(int max_alt){
        raiz = nos;
        cont = 0;
        altura_max = max_alt;
    }

    NoArv* aloca_no();
    void libera(NoArv *no);
    void imprime();
    void auxImprime(NoArv *no);

    void implementa(NoArv *no,int altura, char *operadores, char *variaveis, int size_op, int size_var);
    void empilha_arv(NoArv *no,Pilha *p);
    void implementa_copia(NoArv *no_copia,NoArv *original,int idx);
    void complementa_copia(NoArv *no_copia,NoArv *original);
    int contaNos(NoArv *no);

    void remove(NoArv *sub_raiz, int val);
    NoArv* auxRemove(NoArv *no_atual, NoArv *novo, int idx);
    void muta_arvore(Arv *sub_arv);
    void troca_indices(NoArv *no, int novo_idx);
    
    NoArv* aux_procura(NoArv *atual, int idx, char *c);
}Arv;


NoArv* Arv::aloca_no()
{
    if(cont < MAX){
        cont++;
        nos[cont].idx = cont;
        return &nos[cont];
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

void Arv::libera(NoArv *no)
{
    if(no != NULL)
    {
        libera(no->filho_esquerda);
        libera(no->filho_direita);
        delete no;
        cont--;
    }
}

void Arv::implementa(NoArv *no,int altura, char *operadores, char *variaveis, int size_op, int size_var)
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

    if(rand()%100 > 40){
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


void Arv::implementa_copia(NoArv *no_copia,NoArv *original,int idx)
{
    if(original->filho_esquerda == NULL && original->filho_direita == NULL){
        no_copia->info = original->info;
        return;
    }else if(original->idx == idx || original->idx == (2*idx+1) || original->idx == (2*idx+2)){
        return;
    }else{
        no_copia->info = original->info;

        no_copia->filho_esquerda = this->aloca_no();
        no_copia->filho_direita = this->aloca_no();
   
        implementa_copia(no_copia->filho_esquerda,original->filho_esquerda, idx);
        implementa_copia(no_copia->filho_direita,original->filho_direita, idx);
    }
    return;
}

void Arv::complementa_copia(NoArv *no_copia,NoArv *original)
{
    if(original == NULL){
        return;
    }else{
        if(original->filho_esquerda == NULL && original->filho_direita == NULL){
            no_copia->info = original->info;
        }else{
            no_copia->info = original->info;
            no_copia->filho_esquerda = this->aloca_no();
            no_copia->filho_direita = this->aloca_no();
        }
            
        complementa_copia(no_copia->filho_esquerda, original->filho_esquerda);
        complementa_copia(no_copia->filho_direita, original->filho_direita);
    }

   
    return;
}


int Arv::contaNos(NoArv *no)
{
    if(no != NULL)
        return 1 + contaNos(no->filho_esquerda) + contaNos(no->filho_direita);
    else
        return 0;
}


void Arv::remove(NoArv *sub_raiz, int idx)
{
    raiz = auxRemove(raiz, sub_raiz, idx);
}

NoArv* Arv::auxRemove(NoArv *no_atual, NoArv *novo, int idx)
{
    if(no_atual->filho_esquerda == NULL || no_atual->filho_esquerda == NULL)
    {
        return NULL;
    }
    else if(no_atual->filho_esquerda->idx == idx){
        NoArv *aux = no_atual->filho_esquerda;
        cout << "Sub-arvore removida: " << endl;
        auxImprime(aux);
        cout << endl;
        //libera(aux);
        no_atual->filho_esquerda = novo;
        return no_atual;
    }else if(no_atual->filho_direita->idx == idx) {
        NoArv *aux = no_atual->filho_direita;
        cout << "Sub-arvore removida: " << endl;
        auxImprime(aux);
        cout << endl;

        //libera(aux);

        no_atual->filho_direita = novo;
        
        return no_atual;
    }

    no_atual->filho_esquerda = auxRemove(no_atual->filho_esquerda,novo,idx);
    no_atual->filho_direita = auxRemove(no_atual->filho_direita,novo,idx);
    return no_atual;
}
void Arv::troca_indices(NoArv *no, int novo_idx){
    if(no != NULL){
        troca_indices(no->filho_esquerda, novo_idx++);
        troca_indices(no->filho_direita, novo_idx++);
        no->idx = novo_idx;
    }
}

void Arv::muta_arvore(Arv *sub_arv)
{
    int rand_ = rand()%(cont-1);
    troca_indices(sub_arv->raiz, rand_);
    remove(sub_arv->raiz, rand_);
    cont = contaNos(raiz);
}



NoArv* Arv::aux_procura(NoArv *atual, int idx, char *c){
    if(atual->filho_esquerda == NULL || atual->filho_direita == NULL){
        return NULL;
    }else if(atual->filho_esquerda->idx == idx){
        *c = 'e';
        return atual->filho_esquerda;
    }else if(atual->filho_direita->idx == idx){
        *c = 'd';
        return atual->filho_direita;
    }

    atual = aux_procura(atual->filho_esquerda,idx, c);
    atual = aux_procura(atual->filho_direita,idx, c);
    return atual;
}





#endif //UNTITLED_NOARV_H
