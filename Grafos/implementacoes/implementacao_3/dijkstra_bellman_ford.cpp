#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int u, v, weight; // u: vértice de origem, v: vértice de destino, weight: peso da aresta
};

// algoritmo Bellman-Ford
void bellmanFord(int V, int E, int source, vector<Edge>& edges) {
    vector<int> dist(V, INT_MAX); // inicializando distâncias com infinito
    dist[source] = 0; // a distância do vértice de origem para ele mesmo é 0

    // relaxando as arestas V-1 vezes
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].weight;

            // atualizando a distância se uma rota mais curta for encontrada
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // verificando se existe um ciclo de peso negativo
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "O grafo contem um ciclo de peso negativo!" << endl; // não deve ocorrer em grafos com pesos positivos
            return;
        }
    }

    // imprimindo as distâncias calculadas
    cout << "Distancias do vertice de origem " << source + 1 << ":" << endl; // somando 1 para refletir a entrada original
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            cout << "Infinito ";
        } else {
            cout << dist[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    int V, E; // V: número de vértices, E: número de arestas
    cout << "Digite o numero de vertices e arestas: ";
    cin >> V >> E;

    vector<Edge> edges(E);

    // lendo as arestas
    cout << "Digite as arestas no formato u (vertice de origem) v (vertice de destino) peso:" << endl;
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].u--; // ajustando para indexação começando em 0
        edges[i].v--; // ajustando para indexação começando em 0
    }

    int source;
    cout << "Digite o vertice de origem: ";
    cin >> source;
    source--; // ajustando o vértice de origem para indexação 0

    // executando o Bellman-Ford
    bellmanFord(V, E, source, edges);

    return 0;
}
