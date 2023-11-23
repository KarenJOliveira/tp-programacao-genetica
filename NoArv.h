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

vector<char> variaveis = {'x','y','z'};
vector<char> operadores = {'+','-','*','/'};

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

    NoArv* alocaNo();
    NoArv* libera(NoArv *no);
    void liberar();
    void imprime();
    void auxImprime(NoArv *no);
    int countNodes(NoArv* root);
    void implementa(NoArv *no,int altura, vector<char> operadores, vector<char> variaveis, int size_op, int size_var);
    void empilhaArv(NoArv *no,Pilha *p);
    void calculaAptidao(float **dados, int dados_l);
    NoArv* auxMuta(NoArv *no_atual, NoArv *novo, int idx);
    NoArv* retornaPonteiro(NoArv *no, int idx);
    void alteraIndices(NoArv* root, int index);
    void copiaArv(NoArv *source);
    NoArv* auxCopia(NoArv* source);
    void recombinaArv(Arv *arv2);
    NoArv* auxRecombina(NoArv* pai,NoArv *no_atual,NoArv *novo, int idx);
    void mutaArv();
}Arv;


NoArv* Arv::alocaNo()
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

int Arv::countNodes(NoArv* root) {
    // Base case: if the tree is empty, return 0
    if (root == nullptr) {
        return 0;
    }

    // Recursive case: count nodes in the left and right subtrees and add 1 for the current node
    return 1 + countNodes(root->filho_esquerda) + countNodes(root->filho_direita);
}

void Arv::implementa(NoArv *no,int altura, vector<char> operadores, vector<char> variaveis, int size_op, int size_var)
{
    if(altura == altura_max){

        no->info = operadores[rand()%size_op];
        no->ehOperador = true;

        no->filho_esquerda = alocaNo();
        no->filho_direita = alocaNo();
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
    no->filho_esquerda = alocaNo();
    no->filho_direita = alocaNo();

    implementa(no->filho_esquerda,altura+1,operadores,variaveis,size_op,size_var);
    implementa(no->filho_direita,altura+1,operadores,variaveis,size_op,size_var);
}

void Arv::empilhaArv(NoArv *no,Pilha *p){
    if(no == NULL){
        return;
    }

    empilhaArv(no->filho_esquerda,p);
    empilhaArv(no->filho_direita,p);

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
void Arv::copiaArv(NoArv *source){
    raiz = auxCopia(source);
}

NoArv* Arv::auxCopia(NoArv* source) {
    if (source == nullptr) {
        return nullptr;
    }

    // cria um novo nó na árvore destino com o mesmo valor
    NoArv* destination = new NoArv;
    destination->info = source->info;
    destination->idx = source->idx;
    if(source->ehOperador){
        destination->ehOperador = source->ehOperador;
    }else{
        destination->ehOperador = source->ehOperador;
        return destination;
    }

    // recursivamente copia a subarvore esquerda e direita
    destination->filho_esquerda = auxCopia(source->filho_esquerda);
    destination->filho_direita = auxCopia(source->filho_direita);

    return destination;
}

void Arv::calculaAptidao(float **dados, int dados_l){
    Pilha *p = new Pilha;
    this->imprime();
    cout << endl;
    this->empilhaArv(this->raiz,p);
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

NoArv* Arv::retornaPonteiro(NoArv *no, int idx){
    if(no == NULL){
        return NULL;
    }else if(no->idx == idx){ //procura nó com o índice passado e o retorna seu ponteiro
        NoArv *aux = no;
        return aux;
    }else{
        NoArv *aux = retornaPonteiro(no->filho_esquerda,idx);
        if(aux == NULL){
            aux = retornaPonteiro(no->filho_direita,idx);
        }
        return aux;
    }
}




void Arv::alteraIndices(NoArv* root, int index) {
    if (root == nullptr) {
        return;
    }

    // muda o índice do nó atual
    root->idx = index;

    // recursivamente muda os indices da subárvore esquerda
    alteraIndices(root->filho_esquerda, 2*index+1);

    // recursivamente muda os indices da subárvore direita
    alteraIndices(root->filho_direita, 2*index+2);
}


void Arv::recombinaArv(Arv *arv2){
    //seleciona um nó aleatório da árvore 1 e um nó aleatório da árvore 2
    int rand_no = rand()%(this->cont+1);
    int rand_no2 = rand()%(arv2->cont+1);
    
    this->setAlturaMax(ALTURA_MAX);
    arv2->setAlturaMax(ALTURA_MAX);
    
    NoArv *sub1;
    sub1 = this->retornaPonteiro(this->raiz,rand_no);
    NoArv *sub2;
    sub2 = arv2->retornaPonteiro(arv2->raiz,rand_no2);
    

    this->raiz = auxRecombina(this->raiz,this->raiz,sub2,rand_no);
    arv2->raiz = arv2->auxRecombina(arv2->raiz,arv2->raiz,sub1,rand_no2);

    alteraIndices(sub1,rand_no2);
    alteraIndices(sub2,rand_no);

}

// NoArv* Arv::auxRecombina(NoArv *no_atual,NoArv *novo, int idx){
//     if(no_atual == NULL)
//     {
//         return NULL;
//     }
//     else if(no_atual->idx == idx){
        
//         alteraIndices(novo, idx);      //atualiza indices dos nós da subárvore que será inserida no lugar da subárvore removida
//         return novo;      //retorna para o pai o ponteiro para a subárvore que será inserida no lugar da subárvore removida

//     }else{

//         no_atual->filho_esquerda = auxRecombina(no_atual->filho_esquerda,novo,idx);
//         no_atual->filho_direita = auxRecombina(no_atual->filho_direita,novo,idx);

//     }

//     return no_atual;
// }

NoArv* Arv::auxRecombina(NoArv* pai, NoArv* no_atual, NoArv* novo, int idx) {
    if (no_atual == NULL) {
        return NULL;
    } else if (no_atual->idx == idx) {
        
        if (pai != NULL) {
            if (pai->filho_esquerda == no_atual) {
                pai->filho_esquerda = NULL;
            } else if(pai->filho_direita == no_atual) {
                pai->filho_direita = NULL;
            }else{
                pai = NULL;
            }
        }
        return novo;

    } else {
        no_atual->filho_esquerda = auxRecombina(no_atual, no_atual->filho_esquerda, novo, idx);
        no_atual->filho_direita = auxRecombina(no_atual, no_atual->filho_direita, novo, idx);
    }
    //alteraIndices(novo, idx);      //atualiza indices dos nós da subárvore que será inserida no lugar da subárvore removida
    return no_atual;
}


void Arv::mutaArv() 
{
    int rand_no;

    if(this->cont == 0){
        rand_no = 0;
    }else{
        rand_no = rand()%(this->cont);
    }
   
    Arv *sub_arv = new Arv;
    sub_arv->altura_max = ALTURA_MAX;
    sub_arv->raiz->info = operadores[rand()%operadores.size()];
    sub_arv->implementa(sub_arv->raiz,0,operadores,variaveis,operadores.size(),variaveis.size());

    this->raiz = auxMuta(this->raiz, sub_arv->raiz, rand_no);
    sub_arv = NULL;

    delete sub_arv;
}

NoArv* Arv::auxMuta(NoArv *no_atual, NoArv *novo, int idx)
{
    if(no_atual == NULL)
    {
        return NULL;
    }
    else if(no_atual->idx == idx){
        
        alteraIndices(novo, idx);        //atualiza indices dos nós da subárvore que será inserida no lugar da subárvore removida
        libera(no_atual);       //retira o ponteiro para a subarvore que será removida
        
        return novo;        //retorna para o pai o ponteiro para a subárvore que será inserida no lugar da subárvore removida
    }

    no_atual->filho_esquerda = auxMuta(no_atual->filho_esquerda,novo,idx);
    no_atual->filho_direita = auxMuta(no_atual->filho_direita,novo,idx);

    return no_atual;
}

#endif //UNTITLED_NOARV_H
