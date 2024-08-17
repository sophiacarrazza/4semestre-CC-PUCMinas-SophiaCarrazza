#include <iostream>

const int nlin = 5;
const int ncol = 4;
const int produto = nlin * ncol;
using namespace std;

struct Elemento{
    int elemento;
    bool lapide;

    Elemento(){
        lapide=false;
    }
    
};

void inserir(Elemento elementos[produto],Elemento matriz[nlin][ncol]){
    int c=0;
    for(int i=0;i<nlin;i++){
        for(int j=0;j<ncol;j++){
            matriz[i][j]=elementos[c];
            c++;
        }
    }
}

void mostra_matriz(Elemento matriz[nlin][ncol]){
    cout<<"matriz: "<<endl;
    for(int i=0;i<nlin;i++){
        for(int j=0;j<ncol;j++){
            if(!(matriz[i][j].lapide)){
                cout<<matriz[i][j].elemento<<" ";
            }
            else cout<<"elemento removido";
        }
        cout<<endl;
    }
}

void mostra_elementos(Elemento elementos[produto]){
    cout<<"elementos a serem incluidos: "<<endl;
    for(int i=0;i<produto;i++){
        cout<<elementos[i].elemento<<" ";
    }
    cout<<endl;
}

void preenche_elementos(Elemento elementos[produto]){
    srand(0);
    for(int i=0;i<produto;i++){
        elementos[i].elemento=rand()%100;
    }
}

void remover(int linha, int col, Elemento matriz[nlin][ncol]){
    if (linha >= 0 && linha < nlin && col >= 0 && col < ncol) {
        matriz[linha][col].lapide = true;
    } else {
        cout << "Erro: Indice fora dos limites da matriz!" << endl;
    }
}

bool busca(Elemento matriz[nlin][ncol], int chave){
    bool sucesso=false;
    for(int i=0;i<nlin;i++){
        for(int j=0;j<ncol;j++){
            if(matriz[i][j].elemento==chave){
                sucesso=true;
                j=ncol;
                i=nlin;
            }
        }
    }
    return sucesso;
}


void busca_elemento(Elemento matriz[nlin][ncol],int chave){
    if(busca(matriz,chave))
    cout << "Elemento encontrado"<< endl;
    else cout << "Elemento nao encontrado"<< endl;
    
}

int main(){
    Elemento matriz1[nlin][ncol];
    Elemento elementos[produto];
    preenche_elementos(elementos);
    mostra_elementos(elementos);
    inserir(elementos,matriz1);
    mostra_matriz(matriz1);
    remover(3,3,matriz1);
    mostra_matriz(matriz1);
    busca_elemento(matriz1,90);
    
}