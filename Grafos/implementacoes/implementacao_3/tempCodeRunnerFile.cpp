#include <iostream>
#include <limits>

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

    void dijkstraMinMax(int alvo, int dist[], int maxEdge[]) {
        bool visitados[V];

        for (int i = 0; i < V; i++) {
            dist[i] = infinito;
            maxEdge[i] = 0;  // Inicializa como 0, pois estamos tentando minimizar o maior peso
            visitados[i] = false;
        }

        dist[alvo] = 0;

        for (int i = 0; i < V - 1; i++) {
            int minDist = infinito;
            int u = -1;

            for (int j = 0; j < V; j++) {
                if (!visitados[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }

            if (u == -1) break;
            visitados[u] = true;

            for (Aresta* a = vertices[u].prox_V; a != nullptr; a = a->prox) {
                int v = a->destino;
                int peso = a->peso;

                int newMaxEdge = max(maxEdge[u], peso);  // Atualiza o maior peso no caminho
                if (!visitados[v] && newMaxEdge < maxEdge[v]) {
                    dist[v] = dist[u] + peso;
                    maxEdge[v] = newMaxEdge;  // Atualiza o maior peso no caminho para v
                }
            }
        }
    }

    void dijkstraMaxMin(int alvo, int dist[], int minEdge[]) {
        bool visitados[V];

        for (int i = 0; i < V; i++) {
            dist[i] = infinito;
            minEdge[i] = infinito;  // Inicializa com infinito para tentar maximizar o menor peso
            visitados[i] = false;
        }

        dist[alvo] = 0;
        minEdge[alvo] = infinito;  // Não há aresta até o vértice inicial

        for (int i = 0; i < V - 1; i++) {
            int minDist = infinito;
            int u = -1;

            for (int j = 0; j < V; j++) {
                if (!visitados[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }

            if (u == -1) break;
            visitados[u] = true;

            for (Aresta* a = vertices[u].prox_V; a != nullptr; a = a->prox) {
                int v = a->destino;
                int peso = a->peso;

                int newMinEdge = min(minEdge[u], peso);  // Atualiza o menor peso no caminho
                if (!visitados[v] && newMinEdge > minEdge[v]) {
                    dist[v] = dist[u] + peso;
                    minEdge[v] = newMinEdge;  // Atualiza o menor peso no caminho para v
                }
            }
        }
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

    int distancesMinMax[5], maxEdge[5];
    int distancesMaxMin[5], minEdge[5];

    g.dijkstraMinMax(0, distancesMinMax, maxEdge);
    g.dijkstraMaxMin(0, distancesMaxMin, minEdge);

    cout << "Distâncias e maiores pesos (MinMax) a partir do vértice 0:\n";
    for (int i = 0; i < g.V; i++) {
        cout << "Vértice " << i << ": Distância = " << distancesMinMax[i] << ", Maior Aresta no Caminho = " << maxEdge[i] << endl;
    }

    cout << "\nDistâncias e menores pesos (MaxMin) a partir do vértice 0:\n";
    for (int i = 0; i < g.V; i++) {
        cout << "Vértice " << i << ": Distância = " << distancesMaxMin[i] << ", Menor Aresta no Caminho = " << minEdge[i] << endl;
    }

    return 0;
}
