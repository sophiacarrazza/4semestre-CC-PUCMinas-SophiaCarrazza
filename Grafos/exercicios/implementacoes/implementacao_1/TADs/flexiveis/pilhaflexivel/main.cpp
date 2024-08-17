#include <iostream>
template <typename T>

class PilhaFlexivel {
    private:
    struct No {
        T elemento;
        No* prox;
    };
    No* cabeca;

    public:
    PilhaFlexivel() : cabeca(nullptr) {} //construtor

    ~PilhaFlexivel() { //destrutor (pra liberar memoria alocada)
        No* atual = cabeca;
        while (atual !=  nullptr) {
            atual = cabeca->prox; //guarda o proximo
            delete cabeca;
            cabeca = atual;
        }
    }

    bool buscar(T elemento){
        No* atual = cabeca;
        while(atual != nullptr){
            if(atual->elemento == elemento){
                std::cout << "Elemento " << atual->elemento << " encontrado" << std::endl;
                return true;
            }
            atual = atual->prox;
        }
        std::cout << "Elemento " << elemento << " nao encontrado" << std::endl;
        return false;
    }

    void mostrar(){
        No* atual = cabeca;
        std::cout << "Pilha: ";
        while(atual != nullptr){
            std::cout << atual->elemento << " - ";
            atual = atual->prox;
        }
        std::cout << std::endl; //quebra de linha
    }

    //o mais eficiente para pilha: inserir no inicio e remover no inicio

    void add(T elemento){
        No* novo = new No;
        novo->elemento = elemento;
        novo->prox = cabeca;
        cabeca = novo;
    }

    T remove(){
        if(cabeca == nullptr){
            std::cout << "Pilha vazia" << std::endl;
            return -1;
        }
        No* atual = cabeca;
        cabeca = cabeca->prox;
        delete atual;
        if (cabeca != nullptr) {
            return cabeca->elemento;
        }
        return -1; //lista vazia depois de remover
    }
};

int main(){
    PilhaFlexivel<int> pilha;
    pilha.add(1);
    pilha.add(2);
    pilha.add(3);
    pilha.add(4);
    pilha.add(5);
    pilha.add(6);

    pilha.mostrar();

    bool busca = pilha.buscar(5);

    pilha.remove();
    pilha.remove();

    pilha.mostrar();

    busca = pilha.buscar(5);

    return 0;
}
