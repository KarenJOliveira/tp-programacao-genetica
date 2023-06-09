#include <iostream>
#include <random>
#include <math.h>
#include "stack.h"

using namespace std;

#define SEED 32

void fill_random_expr_tree(No* node, int height, char *OPERATIONS, char *VARIABLES, int size_op, int size_var){
        if(height == 1){
            node->content = OPERATIONS[rand()% size_op];
            
            node->left_child = aloca_no();
            node->right_child = aloca_no();

            node->left_child->content = VARIABLES[rand()%size_var];
            node->right_child->content = VARIABLES[rand()%size_var];
            return;
        }

        if(rand()%100 > 50)
            node->content = OPERATIONS[rand()%size_op];
        else
            node->content = VARIABLES[rand()%size_var];

        node->left_child = aloca_no();
        node->right_child = aloca_no();

        
        fill_random_expr_tree(node->left_child, height-1, OPERATIONS, VARIABLES, size_op, size_var);
        fill_random_expr_tree(node->right_child, height-1, OPERATIONS, VARIABLES, size_op, size_var);

    return;
}

void traverse_postfix(No* node){
    if(node == NULL){ 
        return;
    }
  
    traverse_postfix(node->left_child);
    traverse_postfix(node->right_child);
    cout <<  " " << node->content << " ";
    return;
}

int main(){

    
    char CONTENTS[6] = {'+', '-', '*', '/','x','y'};

    char OPERATIONS[4] = {'+', '-', '*', '/'};

    char VARIABLES[2] = {'x', 'y'};
   
    int size_op = sizeof(OPERATIONS)/sizeof(OPERATIONS[0]);
    int size_var = sizeof(VARIABLES)/sizeof(VARIABLES[0]);

    stack s;

    int height = 4;

    No *root = aloca_no();

    srand(SEED);

    fill_random_expr_tree(root, height, OPERATIONS, VARIABLES, size_op, size_var);

    s.nodesToStack(root);

    traverse_postfix(root);
    cout << endl;

   return 0;
}