#include <iostream>
template <typename T>

class FilaFlexivel {
    private:
    struct No {
        T elemento;
        No* prox;
    };
    No* cabeca;

    public:
    FilaFlexivel() : cabeca(nullptr) {} //construtor

    ~FilaFlexivel() { //destrutor (pra liberar memoria alocada)
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
        std::cout << "Fila: ";
        while(atual != nullptr){
            std::cout << atual->elemento << " - ";
            atual = atual->prox; 
        }
        std::cout << std::endl; //quebra de linha
    }

    //o mais eficiente para fila: inserir no final e remover no inicio

    void add(T elemento){
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

    T remove(){
        if(cabeca == nullptr){
            std::cout << "Fila vazia" << std::endl;
            return -1;
        }
        No* atual = cabeca;
        cabeca = cabeca->prox;
        delete atual;
        if (cabeca != nullptr) {
            return cabeca->elemento;
        }
        return -1; //fila vazia depois de remover
    }
};

int main(){
    FilaFlexivel<int> fila;
    fila.add(1);
    fila.add(2);
    fila.add(3);
    fila.add(4);
    fila.add(5);
    fila.add(6);

    fila.mostrar();

    bool busca = fila.buscar(1);

    fila.remove();
    fila.remove();

    fila.mostrar();

    busca = fila.buscar(1);

    return 0;
}
