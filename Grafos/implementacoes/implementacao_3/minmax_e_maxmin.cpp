#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int infinito = 2147483647;

// Representa uma aresta
struct Aresta {
    int destino;
    int peso;
    Aresta* prox;
};

// Representa cada um dos vértices
struct Vertice {
    int numero;
    Aresta* prox_V;
};

class Grafo {
public:
    int V;
    Vertice* vertices; 

    Grafo(int V) {
        this->V = V;
        vertices = new Vertice[V];

        for (int i = 0; i < V; i++) {
            vertices[i].numero = i;
            vertices[i].prox_V = nullptr;
        }
    }

    void addAresta(int origem, int destino, int w) {
        Aresta* newEdge = new Aresta{destino, w, vertices[origem].prox_V};
        vertices[origem].prox_V = newEdge;
    }

    // MinMax: minimiza o maior peso de aresta no caminho
    void dijkstraMinMax(int alvo, int maxEdge[], int predecessor[]) {
        bool visitados[V];

        for (int i = 0; i < V; i++) {
            maxEdge[i] = infinito;  // Inicializa como infinito
            visitados[i] = false;
            predecessor[i] = -1;  // Inicializa predecessores como -1
        }

        maxEdge[alvo] = 0;  // O ponto de partida tem "maior peso" 0

        for (int i = 0; i < V - 1; i++) {
            int minDist = infinito;
            int u = -1;

            for (int j = 0; j < V; j++) {
                if (!visitados[j] && maxEdge[j] < minDist) {
                    minDist = maxEdge[j];
                    u = j;
                }
            }

            if (u == -1) break;
            visitados[u] = true;

            for (Aresta* a = vertices[u].prox_V; a != nullptr; a = a->prox) {
                int v = a->destino;
                int peso = a->peso;

                // MinMax: o novo caminho até v passa pelo maior peso entre maxEdge[u] e a aresta atual
                int newMaxEdge = max(maxEdge[u], peso);

                if (!visitados[v] && newMaxEdge < maxEdge[v]) {
                    maxEdge[v] = newMaxEdge;
                    predecessor[v] = u;  // Atualiza o predecessor
                }
            }
        }
    }

    // MaxMin: maximiza o menor peso de aresta no caminho
    void dijkstraMaxMin(int alvo, int minEdge[], int predecessor[]) {
        bool visitados[V];

        for (int i = 0; i < V; i++) {
            minEdge[i] = 0;  // Inicializa como 0
            visitados[i] = false;
            predecessor[i] = -1;  // Inicializa predecessores como -1
        }

        minEdge[alvo] = infinito;  // O ponto de partida tem "menor peso" infinito

        for (int i = 0; i < V - 1; i++) {
            int maxDist = 0;
            int u = -1;

            for (int j = 0; j < V; j++) {
                if (!visitados[j] && minEdge[j] > maxDist) {
                    maxDist = minEdge[j];
                    u = j;
                }
            }

            if (u == -1) break;
            visitados[u] = true;

            for (Aresta* a = vertices[u].prox_V; a != nullptr; a = a->prox) {
                int v = a->destino;
                int peso = a->peso;

                // MaxMin: o novo caminho até v passa pelo menor peso entre minEdge[u] e a aresta atual
                int newMinEdge = min(minEdge[u], peso);

                if (!visitados[v] && newMinEdge > minEdge[v]) {
                    minEdge[v] = newMinEdge;
                    predecessor[v] = u;  // Atualiza o predecessor
                }
            }
        }
    }

    // Método para imprimir o caminho a partir do vértice origem até o vértice destino
    void printCaminho(int predecessor[], int destino) {
        vector<int> caminho;
        for (int v = destino; v != -1; v = predecessor[v]) {
            caminho.push_back(v);
        }

        cout << "Caminho: ";
        for (int i = caminho.size() - 1; i >= 0; i--) {
            cout << caminho[i];
            if (i != 0) cout << " -> ";
        }
        cout << endl;
    }

    ~Grafo() {
        for (int i = 0; i < V; i++) {
            while (vertices[i].prox_V) {
                Aresta* temp = vertices[i].prox_V;
                vertices[i].prox_V = vertices[i].prox_V->prox;
                delete temp;
            }
        }
        delete[] vertices;
    }
};

int main() {
    Grafo g(5); // cria um grafo com 5 vértices
    g.addAresta(0, 1, 10);
    g.addAresta(0, 4, 5);
    g.addAresta(1, 2, 1);
    g.addAresta(1, 4, 2);
    g.addAresta(2, 3, 4);
    g.addAresta(3, 0, 7);
    g.addAresta(4, 1, 3);
    g.addAresta(4, 2, 9);
    g.addAresta(4, 3, 2);

    int maxEdge[5];  // Para MinMax
    int minEdge[5];  // Para MaxMin
    int predecessorMinMax[5];  // Para armazenar os predecessores do MinMax
    int predecessorMaxMin[5];  // Para armazenar os predecessores do MaxMin

    g.dijkstraMinMax(0, maxEdge, predecessorMinMax);  // Calcula MinMax a partir do vértice 0
    g.dijkstraMaxMin(0, minEdge, predecessorMaxMin);  // Calcula MaxMin a partir do vértice 0

    cout << "Maiores pesos (MinMax) a partir do vertice 0:\n";
    for (int i = 0; i < g.V; i++) {
        cout << "Vertice " << i << ": Maior Aresta no Caminho = " << maxEdge[i] << " | ";
        g.printCaminho(predecessorMinMax, i);  // Imprime o caminho
    }

    cout << "\nMenores pesos (MaxMin) a partir do vertice 0:\n";
    for (int i = 0; i < g.V; i++) {
        if(i == 0) minEdge[i] = 0;
        cout << "Vertice " << i << ": Menor Aresta no Caminho = " << minEdge[i] << " | ";
        g.printCaminho(predecessorMaxMin, i);  // Imprime o caminho
    }

    return 0;
}
