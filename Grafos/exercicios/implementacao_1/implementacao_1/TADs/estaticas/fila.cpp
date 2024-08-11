#include <iostream>
#include <string>

using namespace std;

template <typename T>

class Fila {

private:
    static const int capacidade = 10;
    T fila[capacidade];
    int quantidade_atual;

public:
    Fila() { quantidade_atual = 0; }

    void inserir(T elemento) {

        if (quantidade_atual < capacidade) {
        fila[quantidade_atual] = elemento;
        quantidade_atual++;
        cout << elemento << " inserido" << endl;
        } else
        cout << "Fila cheia" << endl;
    }

    void shift_left() {

        for (int i = 0; i < quantidade_atual - 1; i++) {
        fila[i] = fila[i + 1];
        }
    }

    T remover() {

        if (quantidade_atual > 0) {
        T aux = fila[0];
        shift_left();
        quantidade_atual--;
        return aux;

        } else
        throw runtime_error("Fila vazia");
    }

    void busca_elemento(T elemento) {
        if (busca(elemento)) {
        cout << elemento << " foi encontrado" << endl;
        } else
        cout << elemento << " não foi encontrado" << endl;
    }

    bool busca(T elemento) {
        bool sucesso = false;

        for (int i = 0; i < quantidade_atual; i++) {
            if (fila[i] == elemento) {
                sucesso = true;
                i = quantidade_atual;
            }
        }
        return sucesso;
    }

    void mostra() {
        cout << "inicio ";
        for (int i = 0; i < quantidade_atual ; i++) {
        cout << fila[i] << " ";
        }
        std::cout << "fim" << endl;
    }
};

int main() {

    Fila<int>fila1;

    for (int i = 0; i < 10; i++) {
        fila1.inserir(i);
    }

    fila1.remover();
    fila1.remover();
    fila1.mostra();
    fila1.busca_elemento(1);
    fila1.busca_elemento(5);
}