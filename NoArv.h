#include "Pilha.h"
#include "Fila.h"
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
        idx = -1;
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
    void enfileira_arv(NoArv *no, Fila *fila);
    int contaNos(NoArv *no);
    NoArv* procura_no(int pos);
    void insereK(int k,NoArv* novo);
    void removeK(int k);
    void mutacao(Arv *sub_arv);
    void muta_arvore(NoArv *no, Arv *sub_arv, int idx);
}Arv;


NoArv* Arv::aloca_no()
{
    if(this->cont < MAX){
        this->cont++;
        nos[this->cont].idx = this->cont;
        return &nos[this->cont];
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
    }
}

void Arv::implementa(NoArv *no,int altura, char *operadores, char *variaveis, int size_op, int size_var)
{
    if(altura == this->altura_max){
        
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

void Arv::enfileira_arv(NoArv *no, Fila *fila){
    if(no == NULL){
        return;
    }   

    enfileira_arv(no->filho_esquerda,fila);
    enfileira_arv(no->filho_direita,fila);
    
    fila->enfileira(no->idx);
}

NoArv* Arv::procura_no(int pos){
    if(raiz != NULL)
    {
        Fila f;
        enfileira_arv(raiz, &f);
        while(!f.vazia())
        {
            int aux = f.desenfileira();
            if(aux == pos){
                return &nos[aux];
            }
        }
    }
    return NULL;
}

int Arv::contaNos(NoArv *no)
{
    if(no != NULL)
        return 1 + contaNos(no->filho_esquerda) + contaNos(no->filho_direita);
    else
        return 0;
}
void Arv::insereK(int k,NoArv* novo){
    if(cont < MAX){
        for(int i = cont; i > k; i--){
            nos[i] = nos[i-1];
        }
        novo = &nos[k];
    }
    else{
        cout << "Erro: vetor cheio" << endl;
    }

}
void Arv::removeK(int k){
    for(int i = k; i < cont-1; i++){
        nos[i] = nos[i+1];
    }
    cont--;
}

void Arv::mutacao(Arv *sub_arv){
    int rand_idx = rand()%cont;
    NoArv *no = procura_no(rand_idx);
    muta_arvore(no,sub_arv,rand_idx);
}

void Arv::muta_arvore(NoArv *no, Arv *sub_arv, int idx)
{
    int aux = contaNos(no);
    int aux2 = contaNos(sub_arv->raiz);
    if(aux < aux2){
        int qnt = aux2 - aux;
        for(int i = 0; i < qnt; i++){
            insereK(idx,&sub_arv->nos[i]);
        }
    }else if(aux > aux2){
        int qnt = aux - aux2;
        for(int i = 0; i < qnt; i++){
            insereK(idx+i,&sub_arv->nos[i]);
        }
        int pos = idx+aux2;
        for(int i = 0; i < qnt; i++){
            removeK(pos+i);
        }
    }
    else{
        for(int i = 0; i < aux; i++){
            insereK(idx+i,&sub_arv->nos[i]);
        }
    }
    libera(no);
}