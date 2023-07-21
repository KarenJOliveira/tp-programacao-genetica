#include <iostream>
#define MAX_PILHA 1500
using namespace std;

typedef struct No{
    char info;
    No *prox;

    No(){
        prox = NULL;
    }
}No;

typedef struct Pilha{
    public:
        No *topo; 
        No pilha[MAX_PILHA]; // armazena os nós da pilha
        int cont; //quantidade de nós na pilha
        Pilha(){
            topo = pilha;
            cont = 0;
        }
        bool vazia();
        void empilha(char data);
        void desempilha();

        bool ehOperador(char op);
        void copia_pilha(Pilha *p2);
        void imprime_pilha();
        No* aloca_pilha();
        //void substitui_var(int *x,int *y, int *z, int cont);
}Pilha;

void Pilha::imprime_pilha(){
    int i = 0;
    while(i < cont){
        cout << pilha[i].info << " ";
        i++;
    }
    cout << endl;
}

bool Pilha::vazia(){
    if(topo == NULL)
        return true;

    return false;
}

No* Pilha::aloca_pilha(){
    if(cont < MAX_PILHA){
        if(cont == 0){
            cont++;
            return &pilha[0];
        }
        return &pilha[cont++];
    }
    return NULL;
}
void Pilha::empilha(char data){

    No *aux = aloca_pilha();
    aux->info = data;
    //aux->prox = aloca_pilha();
    topo->prox = aux;
    topo = aux;
}

void Pilha::desempilha(){
    if(!vazia()){
        topo = topo->prox;
        cont--;
    }
    else{
        cout << "Pilha vazia" << endl;
        exit(1);
    }
}


void Pilha::copia_pilha(Pilha *p2){
    int i = 0;
    while(i < cont){
        p2->empilha(pilha[i].info);
        i++;
    }
}
/*
void Pilha::substitui_var(int *x,int *y, int *z, int lin){
    if(ehOperador(pilha[i].info)){
            p2->empilha(pilha[i].info);
        }else{
            
            switch (pilha[i].info)
            {
            case 'x':
            {
                char p = static_cast<char>(x[lin]);
                p2->empilha(p);
                break;
            }
            
            case 'y':
            {
                char p = static_cast<char>(y[lin]);
                p2->empilha(p);
                break;
            }
            
            case 'z':
            {
                char p = static_cast<char>(z[lin]);
                p2->empilha(p);
                break;
            }
            
            default:
                break;
            }
        }
        i++;
    }
}

    while(!aux.vazia()){
        char c = aux.topo->info;
        empilha(c);
        aux.desempilha();
    }
}
*/

bool Pilha::ehOperador(char op){
    if(op == '+' || op == '-' || op == '*' || op == '/'){
        return true;
    }
    return false;
}