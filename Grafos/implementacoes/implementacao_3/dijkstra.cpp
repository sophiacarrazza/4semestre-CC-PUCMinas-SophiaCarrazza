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
    Vertice* verticies; 

    Grafo(int V) {
        this->V = V;
        verticies = new Vertice[V];

        for (int i = 0; i < V; i++) {
            verticies[i].numero = i;
            verticies[i].prox_V = nullptr;
        }
    }


    void addAresta(int origem, int destino, int w) {
        Aresta* newEdge = new Aresta{destino, w, verticies[origem].prox_V};
        verticies[origem].prox_V = newEdge;
        
    }

    void dijkstra(int alvo,int dist []) {

        bool visitados [V];

        //inicicializando todos com infinito e marcando todos os visitados como falso
        for (int i = 0; i < V; i++) {
            dist[i] = infinito;
            visitados[i] = false;
        }
        //a distancia do verticie referencia para ele mesmo é 0
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

            for (Aresta* a = verticies[u].prox_V; a != nullptr; a = a->prox) {
                int v = a->destino;
                int peso = a->peso;

                if (!visitados[v] && dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                }
            }
        }
    }

    ~Grafo() {
        for (int i = 0; i < V; i++) {
            while (verticies[i].prox_V) {
                Aresta* temp = verticies[i].prox_V;
                verticies[i].prox_V = verticies[i].prox_V->prox;
                delete temp;
            }
        }
        delete[] verticies;
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

    int distances[5];
    g.dijkstra(0,distances); // calcula distâncias a partir do vértice 0

    cout << "Distancias a partir do vertice 0:\n";
    for (int i = 0; i < g.V; i++) {
        cout << "Vertice " << i << ": " << distances[i] << endl;
    }
    return 0;
}