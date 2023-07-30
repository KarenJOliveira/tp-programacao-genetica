#include <iostream>
#define MAX_FILA 1500
using namespace std;

typedef struct Fila
{
    public:
        int inicio;
        int fim;
        int indices_nos[MAX_FILA];
        Fila(){
            inicio = 0;
            fim = 0;
        }
        bool vazia();
        void enfileira(int idx);
        int desenfileira();
};


bool Fila::vazia(){
    if(inicio == fim)
        return true;

    return false;
}


void Fila::enfileira(int idx)
{
    if(fim == MAX_FILA){
        cout << "ERRO: Fila cheia" << endl;
        exit(2);
    }
    indices_nos[fim] = idx;
    fim++;
}

int Fila::desenfileira()
{
    if(!vazia()){
        inicio++;
        return indices_nos[inicio-1];
    }
    cout << "ERRO: Fila vazia" << endl;
    exit(1);
}