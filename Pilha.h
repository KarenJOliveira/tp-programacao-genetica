#include <iostream>
#include <cmath>
#define MAX_PILHA 150000
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
    No *prox; // ponteiro para o proximo

    No()                  { };
    ~No()                 { };
    Item getInfo()         { return info; };
    No* getProx()         { return prox; };
    void setInfo(Item val) { info = val; };
    void setProx(No *p)   { prox = p; };

}No;

typedef struct Pilha{
    public:
        No *topo; 
        int cont; //quantidade de nós na pilha

        Pilha(){
            topo = NULL;
            cont = 0;
        }
        ~Pilha(){
            while(topo != NULL)
            {
                No *p = topo;
                topo = topo->getProx();
                delete p;
            }
        }
        Item getTopo();
        void imprime();     
        bool vazia();
        void empilha(Item data);
        Item desempilha();
        void copia_pilha(Pilha *p2);
        float resolve_operacoes(float **dados, int l);

        //No* aloca_pilha();

        
}Pilha;


Item Pilha::getTopo()
{
    if(topo != NULL)
        return topo->getInfo();
    cout << "ERRO: Pilha vazia" << endl;
    exit(1);
}

void Pilha::empilha(Item val)
{
    No *p = new No;
    p->setInfo(val);
    p->setProx(topo);
    this->cont++;
    topo = p;
}

Item Pilha::desempilha()
{
    if(topo == NULL){
        cout << "ERRO: Pilha vazia" << endl;
        exit(0);
    }
    else
    {
        No *p = topo;
        topo = topo->getProx();
        Item val = p->getInfo();
        delete p;
        this->cont--;
        return val;
    }
}

bool Pilha::vazia()
{
    return topo == NULL;
}

void Pilha::imprime()
{
    cout << "Pilha: ";
    for(No *p = topo; p != NULL; p = p->getProx())
        cout << p->getInfo().n << " ";
    cout << endl;
}


// No* Pilha::aloca_pilha(){
//     if(cont < MAX_PILHA){
//         cont++;
//         return new No;
//     }
//     return NULL;
// }

void Pilha::copia_pilha(Pilha *p2){
    No *p = this->topo;
    int cont_aux = this->cont;
    while(cont_aux > 0){
        p2->empilha(p->getInfo());
        p = p->getProx();
        cont_aux --;
    }
}

float Pilha::resolve_operacoes(float **dados, int l){
    Pilha *p2 = new Pilha;
    copia_pilha(p2);
    Pilha aux;
    
    while(!p2->vazia()){
        Item temp = p2->desempilha();
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
                    result = 0;
                    //cout << "ERRO: Divisão por valor nulo" << endl;
                }else{
                    result = a / b;
                }
                break;
            }
            case '^':
                result = pow(a,b);
                break;
            case 'S':
            {   result = sin(a);
                Item b_;
                b_.n = (char)b;
                aux.empilha(b_);
                break;
            }
            case 'C':
            {
                result = cos(a);
                Item b_;
                b_.n = (char)b;
                aux.empilha(b_);
                break;
            }
            case 'T':
            {
                result = tan(a);
                Item b_;
                b_.n = (char)b;
                aux.empilha(b_);
                break;
            }
            case 'e':
            {
                result = exp(a);
                Item b_;
                b_.n = (char)b;
                aux.empilha(b_);
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
                aux_.n = dados[l][0];
                aux_.ehOperador = false;
                aux.empilha(aux_);
                break;
            }
            case 'y':
            {
                aux_.n = dados[l][1];
                aux_.ehOperador = false;
                aux.empilha(aux_);
                break;
            }
            case 'z':
            {
                aux_.n = dados[l][2];
                aux_.ehOperador = false;
                aux.empilha(aux_);
                break;
            }
            case 'w':
            {
                aux_.n = dados[l][3];
                aux_.ehOperador = false;
                aux.empilha(aux_);
                break;
            }
            case 'p':
            {
                aux_.n = dados[l][4];
                aux_.ehOperador = false;
                aux.empilha(aux_);
                break;
            }
            case 'q':
            {
                aux_.n = dados[l][5];
                aux_.ehOperador = false;
                aux.empilha(aux_);
                break;
            }
            case 'm':
            {
                aux_.n = dados[l][6];
                aux_.ehOperador = false;
                aux.empilha(aux_);
                break;
            }
            case 'n':
            {
                aux_.n = dados[l][7];
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
