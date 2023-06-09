#ifndef STACK_H
#define STACK_H

#include "definicao.h"

#define MAX_ITEMS 5000
//pilha
typedef struct stack {
    int topo;

    char items[MAX_ITEMS];
    stack(): topo(-1){};
    bool empilha(char x);
    char desempilha();
    bool vazia();
    void nodesToStack(No* no);
    
}stack;

bool stack::empilha(char x){
    if(topo >= MAX_ITEMS){
        return false;
    } 
    topo++;
    items[topo] = x;

    return true;
}

char stack::desempilha(){
    if(stack::vazia()){
        return 0;
    }
    char x = items[topo];
    topo--;
    return x;
}

bool stack::vazia(){
    return (topo < 0);
}

void stack::nodesToStack(No* no){
    if(no == NULL){
        return;
    }
    this->nodesToStack(no->left_child);
    this->nodesToStack(no->right_child);
    this->empilha(no->content);
    return;
}

#endif