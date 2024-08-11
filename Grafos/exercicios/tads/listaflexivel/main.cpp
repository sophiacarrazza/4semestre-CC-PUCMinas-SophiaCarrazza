#include <iostream>
template <typename T>

class ListaFlexivel {
    private:
    struct No {
        T elemento;
        No* prox;
    };
    No* cabeca;

    public:
    ListaFlexivel() : cabeca(nullptr) {} //construtor

    ~ListaFlexivel() { //destrutor (pra liberar memoria alocada)
        No* atual = cabeca;
        while (atual !=  nullptr) {
            atual = cabeca->prox; //guarda o proximo
            delete cabeca;
            cabeca = atual;
        }
    }

    void mostrar(){
        No* atual = cabeca;
        std::cout << "Lista: ";
        while(atual != nullptr){
            std::cout << atual->elemento << " - ";
            atual = atual->prox;
        }
        std::cout << std::endl; //quebra de linha
    }

    void addInicio(T elemento){
        No* novo = new No;
        novo->elemento = elemento;
        novo->prox = cabeca;
        cabeca = novo;
    }

    void addFinal(T elemento){
        No* novo = new No;
        novo->elemento = elemento;
        novo->prox = nullptr;

        if (cabeca == nullptr) {
            cabeca = novo;
        } else {
            No* atual = cabeca;
            while(atual->prox != nullptr){
                atual = atual->prox;
            }
            atual->prox = novo;
        }
    }

    T add(T elemento, int posicao) {
        if(posicao == 0){
            addInicio(elemento);
            return cabeca->elemento;
        } else if(cabeca == nullptr){
            std::cout << "Lista vazia" << std::endl;
            return -1;
        } else if(posicao-1 < 0){
            std::cout << "Posicao invalida" << std::endl;
            return -1;
        }
        No* novo = new No;
        No* atual = cabeca;
        int pos = 0;
        while(pos != posicao-2 && atual->prox != nullptr){
            atual = atual->prox;
            pos++;
        }
        novo->elemento = elemento;
        novo->prox = atual->prox;
        atual->prox = novo;
        return novo->elemento;
    }

    T removeInicio(){
        if(cabeca == nullptr){
            std::cout << "Lista vazia" << std::endl;
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

    T removeFinal(){
        if(cabeca == nullptr){
            std::cout << "Lista vazia" << std::endl;
            return -1;
        }
        if(cabeca->prox == nullptr){ //so tem um elemento
            T elemento = cabeca->elemento;
            delete cabeca;
            cabeca = nullptr;
            return elemento;
        }

        No* atual = cabeca;
        No* anterior = nullptr;
        while(atual->prox != nullptr){
            anterior = atual;
            atual = atual->prox;
        }
        anterior->prox = nullptr; //exclusao logica
        T elemento = atual->elemento;
        delete atual; //libera a memoria (exclusao fisica)
        return elemento;
    }

    T remover(int elemento){
        if(cabeca == nullptr){
            std::cout << "Lista vazia" << std::endl;
            return -1;
        }
        if(cabeca->elemento == elemento){
            return removeInicio();
        }
        No* atual = cabeca;
        No* anterior = nullptr;
        while(atual != nullptr && elemento != atual->elemento){ //procura o elemento
            anterior = atual;
            atual = atual->prox;
        }
        if(atual == nullptr) {
            std::cout << "Elemento nao encontrado" << std::endl;
            return -1;
        }
        anterior->prox = atual->prox;
        delete atual;
        return anterior->elemento;
    }
};

int main(){
    ListaFlexivel<int> lista;
    lista.addInicio(1);
    lista.addInicio(2);
    lista.addInicio(3);
    lista.addFinal(4);
    lista.addFinal(5);
    lista.addFinal(6);
    lista.add(7, 2);

    lista.mostrar();

    lista.removeInicio();
    lista.removeFinal();
    lista.remover(4);

    lista.mostrar();

    return 0;
}
