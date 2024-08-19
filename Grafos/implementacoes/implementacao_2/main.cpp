#include <iostream>
#include <vector>
#include <cmath>

//Gerador de todos os subgrafos de um grafo completo com n vértices, 
//em que n é informado pelo usuário. Além disto, informe o número de 
//subgrafos gerados.

void geradorDeSubgrafos(int n) {
    int nArestas = n * (n - 1) / 2; //numero total de arestas no grafo completo
    int nSubgrafos = 0; //contador de subgrafos gerados
    
    std::cout << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Subgrafos gerados:" << std::endl;
    
    std::vector<std::pair<int, int>> arestas; //vetor para armazenar as arestas do grafo completo
    for (int i = 0; i < n; ++i) { //gera todas as arestas do grafo completo
        for (int j = i + 1; j < n; ++j) {
            arestas.push_back({i + 1, j + 1});
        }
    }

    //geração dos subgrafos
    for (int combinacaoVertices = 1; combinacaoVertices < (1 << n); ++combinacaoVertices) {
        for (int combinacaoArestas = 0; combinacaoArestas < (1 << nArestas); ++combinacaoArestas) {
            std::vector<int> verticesAtivos;
            for (int i = 0; i < n; ++i) {
                if (combinacaoVertices & (1 << i)) {
                    verticesAtivos.push_back(i + 1);
                }
            }

            bool subgrafoValido = true;
            std::vector<std::pair<int, int>> arestasDoSubgrafo;

            for (int i = 0; i < nArestas; ++i) {
                if (combinacaoArestas & (1 << i)) {
                    int v1 = arestas[i].first;
                    int v2 = arestas[i].second;
                    // Verifica se ambos os vértices da aresta estão no subgrafo atual
                    if ((combinacaoVertices & (1 << (v1 - 1))) && (combinacaoVertices & (1 << (v2 - 1)))) {
                        arestasDoSubgrafo.push_back({v1, v2});
                    } else {
                        subgrafoValido = false;
                        break;
                    }
                }
            }

            if (subgrafoValido) {
                ++nSubgrafos;
                std::cout << "Vertices: { ";
                for (int v : verticesAtivos) {
                    std::cout << v << " ";
                }
                std::cout << "} | Arestas: { ";
                for (auto& aresta : arestasDoSubgrafo) {
                    std::cout << "(" << aresta.first << ", " << aresta.second << ") ";
                }
                std::cout << "}" << std::endl;
            }
        }
    }
    std::cout << std::endl;
    std::cout << "Numero de subgrafos gerados: " << nSubgrafos << std::endl;
}

int main() {
    int n;
    std::cout << std::endl;
    std::cout << "Digite o numero de vertices do grafo: ";
    std::cin >> n;

    geradorDeSubgrafos(n);
    std::cout << std::endl;

    return 0;
}
