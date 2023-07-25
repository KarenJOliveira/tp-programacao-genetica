#include <iostream>
#define MAX_PILHA 1500
using namespace std;

typedef struct Item{
    float n;
    bool ehOperador;
    Item(){
        n = 0;
        ehOperador = false;
    };
}Item;

typedef struct No{
    Item info;

    No(){};
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
        void empilha(Item data);
        Item desempilha();
        bool ehOperador(char c);
        void copia_pilha(Pilha *p2);
        float resolve_operacoes(int x,int y,int z);
        void imprime_pilha();
        No* aloca_pilha();
        
}Pilha;

void Pilha::imprime_pilha(){
    int i = 0;
    while(i < cont){
        Item aux = pilha[i].info;
        cout << (char)aux.n << " ";
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
void Pilha::empilha(Item data){

    No *aux = aloca_pilha();
    aux->info = data;
    topo = aux;
}

Item Pilha::desempilha(){
    if(!vazia()){
        Item item;
        item = topo->info;
        cont--;
        topo = &pilha[cont];
        return item;
    }
    else{
        cout << "Pilha vazia" << endl;
        exit(1);
    }
}



void Pilha::copia_pilha(Pilha *p2){
    int i = cont-1;
    while(i >= 0){
        p2->empilha(pilha[i].info);
        i--;
    }
}

float Pilha::resolve_operacoes(int x,int y,int z){
    Pilha p2;
    copia_pilha(&p2);
    Pilha aux;

    while(!p2.vazia()){
        Item temp = p2.desempilha();
        if(temp.ehOperador){
            char op = static_cast<char>(temp.n);
            float a = aux.desempilha().n;
            float b = aux.desempilha().n;
            float result;
            switch (op)
            {
            case '+':
                result = a + b;
                break;
            
            case '-':
                result = a - b;
                break;
            
            case '*':
                result = a * b;
                break;
            
            case '/':
            {
                if(b == 0){
                    cout << "ERRO: Divisão por valor nulo" << endl;
                }else{
                    result = a / b;
                }
                break;
            }
            default:
                break;
            }
            Item rst;
            rst.n = (char)result;
            rst.ehOperador = false;
            aux.empilha(rst);
        }else{
            Item aux_;
            switch ((char)temp.n)
            {
            case 'x':
            {
                aux_.n = x;
                aux_.ehOperador = false;
                aux.empilha(aux_);
                break;
            }
            case 'y':
            {
                aux_.n = y;
                aux_.ehOperador = false;
                aux.empilha(aux_);
                break;
            }
            case 'z':
            {
                aux_.n = z;
                aux_.ehOperador = false;
                aux.empilha(aux_);
                break;
            }
            default:
                break;
            }
        }
    }
    float resultado = aux.desempilha().n;
    return resultado;
}
