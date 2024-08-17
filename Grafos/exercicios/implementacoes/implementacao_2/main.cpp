//Gerador de todos os subgrafos de um grafo completo com n vértices, 
//em que n é informado pelo usuário. Além disto, informe o número de 
//subgrafos gerados.

#include <iostream>
#include <vector>
#include <cmath>

void geradorDeSubgrafos (int n) {
    int nArestas = n*(n-1)/2;
    int nSubgrafos = pow(2, nArestas);

    std::cout << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Numero de subgrafos gerados: " << nSubgrafos << std::endl;
    std::cout << "Subgrafos gerados:" << std::endl;

    for(int combinacao = 0; combinacao < nSubgrafos; combinacao++) {
        std::vector<int> subgrafo; //criando um vetor que armazena as arestas do subgrafo
        
        //loop para passar por todas as arestas do grafo
        for (int i=0; i<n; i++){ 
            if (combinacao & (1 << i)) { //verifica se a aresta está presente no subgrafo (pelo operador AND bit a bit)
                subgrafo.push_back(i+1); //adiciona o vertice i ao subgrafo (vertices 1 a n)
            }
        }

        std::cout << "{ ";
        for (int valor : subgrafo) { 
            std::cout << valor << " ";
        }
        std::cout << "}" << std::endl;
    }
}

int main(){
    int n;
    std::cout << std::endl;
    std::cout << "Digite o numero de vertices do grafo: ";
    std::cin >> n;

    geradorDeSubgrafos(n);
    std::cout << std::endl;


    return 0;

}
