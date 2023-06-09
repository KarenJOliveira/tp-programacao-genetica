#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <iostream>
#define MAX 15000


typedef struct No
{
    char content;
    No *left_child;
    No *right_child;

    No(){
        content = ' ';
        left_child = NULL;
        right_child = NULL;
    };

}No;

No arvore[MAX]; 

int n = -1;

int aloca_filho(){
    n++;
    if(n >= MAX){
        return -1;
    }
    return n;
}

No* aloca_no(){
    if(n == -1){
        n++;
        return &arvore[0];
    }else{
        return &arvore[aloca_filho()];
    }
}


#endif