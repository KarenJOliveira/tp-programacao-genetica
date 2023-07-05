#include "NoArv.h"

#include <iostream>
using namespace std;


int main(){

    Arv arv;

    char operadores[4] = {'+', '-', '*', '/'};
    char variaveis[3] = {'x', 'y', 'z'};
    arv.implementa(operadores,variaveis);
    
    arv.imprime();
    return 0;
}