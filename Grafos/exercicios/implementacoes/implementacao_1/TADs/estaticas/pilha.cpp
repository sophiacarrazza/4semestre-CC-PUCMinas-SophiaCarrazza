#include <iostream>
#include <string>

using namespace std;

//mecanismo para aceitar diferentes tipos 
template <typename T>

class Pilha {

private:

    static const int capacidade = 10;
    T pilha[capacidade];
    int quantidade_atual;

public:

    Pilha() { 
        quantidade_atual = 0; 
    }

    void inserir(T elemento) {

        if (quantidade_atual < capacidade) {
        pilha[quantidade_atual] = elemento;
        quantidade_atual++;
        cout <<elemento<<" inserido"<<endl;
        } else
        cout << "Pilha cheia"<<endl;
    }

    T remover() {
        if (quantidade_atual > 0) {       
        quantidade_atual--;
        return pilha[quantidade_atual];
        
        } else throw runtime_error("Pilha vazia");
        
    }

    void busca_elemento(T elemento){
        if(busca( elemento)){
        cout << elemento<< " foi encontrado"<<endl;
        }
        else cout << elemento<< " não foi encontrado"<<endl;
    }

    bool busca(T elemento) {
        bool sucesso = false;

        for (int i = 0; i < quantidade_atual; i++) {
            if (pilha[i] == elemento) {
                sucesso = true;
                i = quantidade_atual;
            }
        }
        return sucesso;
    }

    void mostra() {
        cout << "topo" << endl;
        for (int i = quantidade_atual - 1; i >= 0; i--){
        cout << pilha[i] << endl;
        }
        std::cout << "base" << endl;
    }
};

int main() {

    Pilha<int> pilha1;
    for (int i = 0; i < 10; i++) {
        pilha1.inserir(i);
        
    }
    pilha1.busca_elemento(5);
    pilha1.busca_elemento(15);
    pilha1.remover();
    pilha1.mostra();
}