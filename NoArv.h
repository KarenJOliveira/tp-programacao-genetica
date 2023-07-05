
#include <iostream>
#include <random>
#define MAX_ALT 4
#define MAX 100
using namespace std;

typedef struct NoArv
{
    public:
    char info;
    NoArv *filho_esquerda;
    NoArv *filho_direita;

    NoArv(){
        info = '\0';
        filho_esquerda = NULL;
        filho_direita = NULL;
    };
}NoArv;

typedef struct Arv
{
    NoArv *raiz;

    NoArv nos[MAX]; //
    int cont; // quantidade de nós no vetor N-1

    Arv(){
        raiz = nos;
        cont = 0;
    }
    NoArv* aloca_no();
    void imprime();
    void auxImprime(NoArv *no);
    void implementa(char *operadores, char *variaveis);
    void auxImplementa(NoArv *no,int altura, char *operadores, char *variaveis);

}Arv;

NoArv* Arv::aloca_no()
{
    if(cont < MAX){
        cont++;
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
    cout << endl;
}
void Arv::implementa(char *operadores, char *variaveis){
    raiz->info = operadores[rand()%4];
    auxImplementa(raiz,0,operadores,variaveis);
}
void Arv::auxImplementa(NoArv *no,int altura, char *operadores, char *variaveis)
{
    if(altura == MAX_ALT){
        
        no->info = operadores[rand()%4];
        no->filho_esquerda = aloca_no();
        no->filho_direita = aloca_no();
        no->filho_esquerda->info = variaveis[rand()%3];
        no->filho_direita->info = variaveis[rand()%3];
        return;
    }

    no->filho_esquerda = aloca_no();
    no->filho_direita = aloca_no();
    if(rand()%100 < 40){
        no->filho_esquerda->info = variaveis[rand()%3];
        no->filho_direita->info = variaveis[rand()%3];
        return;
    }

    no->filho_esquerda->info = operadores[rand()%3];
    no->filho_direita->info = operadores[rand()%3];

    auxImplementa(no->filho_esquerda,altura+1,operadores,variaveis);
    auxImplementa(no->filho_direita,altura+1,operadores,variaveis);
}