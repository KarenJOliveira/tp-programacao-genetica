#include <iostream>
#include "NoArv.h"
#include <fstream>
#include <sstream>
#include <stack>
#define MAX_POP 5000

using namespace std;

Arv** leArvore(string filename){
    
    fstream file;
    file.open(filename, ios::in);
    if(file.is_open()){
        cout << "Arquivo aberto com sucesso" << endl;
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }
    
    Arv **melhores_arv = new Arv*[MAX_POP];
    int i = 0;
    string line;
    
    while(getline(file,line,',') && i < 4){
        stack<char> p;
        bool dentro_das_aspas = false;
        string palavra;
        
        for (char c : line) {
            if (c == '"') {
                // Inverte o estado (aberto/fechado) das aspas
                dentro_das_aspas = !dentro_das_aspas;
                continue;
            } else if (c == ' ' && dentro_das_aspas) {
                // Ignora espaços apenas quando não estamos dentro das aspas
                continue;
            }else if(c == '\n'){
                continue;
            }

            p.push(c);
            palavra += c;
            // Verifica se atingimos o final das aspas duplas
            if (c == '"' && dentro_das_aspas) {
                break;
            }
        }   
        cout << "Palavra: " << palavra << endl;
        Pilha *p2 = new Pilha;
        while(!p.empty()){
            Item aux;
            char c;
            c = p.top();
            aux.n = c;
            if(c == 'x' || c == 'y'){
                aux.ehOperador = false;
            }else{
                aux.ehOperador = true;
            }
            p2->empilha(aux);
            p.pop();
        }
        melhores_arv[i] = new Arv;
        melhores_arv[i]->desempilhaArv(melhores_arv[i]->raiz,p2);
        i++;
        //cout << i;
    }
    return melhores_arv;
}

float** leArquivo(int *dados_l,int *dados_c, string filename){
    
    fstream file;
    file.open(filename, ios::in);

    if(file.is_open()){
        cout << "Arquivo aberto com sucesso" << endl;
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }
    string line;
    for(int i = 0;i<2;i++){
        getline(file,line,',');
        if(line == "rows"){
            getline(file,line);
            stringstream ss(line);
            ss >> *dados_l;
        }else{
            getline(file,line);
            stringstream ss(line);
            ss >> *dados_c;
        }
    }
    getline(file,line);
    line.clear();

    float **dados = new float*[*dados_l];
    for(int l=0;l<*dados_l+1;l++){
        dados[l] = new float[*dados_c];
        for(int c=0;c<*dados_c-1;c++){
            string line;
            getline(file,line,',');
            stringstream ss(line);
            ss >> dados[l][c];  
        }
        getline(file,line);
        stringstream ss(line);
        ss >> dados[l][*dados_c-1];
    }
    
    return dados;
}

void createFile(Arv *melhor_arv){
    //cout << "Criando arquivo" << endl;
    string arv_expression = "";
    string nome_arquivo = "pop_melhores/funcao7.csv";
    ofstream file;
    file.open(nome_arquivo, ios::app);
    if(file.is_open()){
        cout << "Arquivo aberto com sucesso" << endl;
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    arv_expression = melhor_arv->retornaArvExp();
    //file << "\n";
    file << "Teste 50k: " << melhor_arv->aptidao << endl;
    file.close();
}

int main(int argc, char *argv[])
{   
    
    float **dados_50k;
    int dados_l_50k;
    int dados_c_50k;
    int numFuncao = stoi(argv[1]);
    
    string filename = "function_n_data/funcao" + to_string(numFuncao) + "/function_" + to_string(numFuncao) + "_50k_data.csv";
    dados_50k = leArquivo(&dados_l_50k,&dados_c_50k, filename);
    Arv **melhores_arv = new Arv*[MAX_POP];
    string filename2 = "pop_melhores/funcao" + to_string(numFuncao) + ".csv";
    melhores_arv = leArvore(filename2);
    cout << "Dados de teste 50k" << endl;
    for(int i = 0;i<4;i++){
        melhores_arv[i]->calculaAptidao(dados_50k,dados_l_50k,dados_c_50k);
        cout << "Aptidão da melhor árvore: " << melhores_arv[i]->aptidao << endl;
    }
    //melhores_arv->calculaAptidao(dados_50k,dados_l_50k,dados_c_50k);
    for(int i = 0;i<4;i++){
        melhores_arv[i]->liberar();
        delete [] melhores_arv[i];   
    }
    delete [] melhores_arv;   
    return 0;
} 