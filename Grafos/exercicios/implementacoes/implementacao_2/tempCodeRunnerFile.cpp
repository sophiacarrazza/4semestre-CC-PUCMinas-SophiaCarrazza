    for(int combinacao = 0; combinacao < nSubgrafos; combinacao++) {
        std::vector<int> subgrafo; //criando um vetor que armazena as arestas do subgrafo
        
        //loop para passar por todas as arestas do grafo
        for (int i=0; i<nArestas; i++){ 
            if (combinacao & (1 << i)) { //verifica se a aresta está presente no subgrafo (pelo operador AND bit a bit)
                int vertice1 = i / (n-1) + 1; //calcula o primeiro vértice da aresta
                int vertice2 = i % (n-1) + 2; //calcula o segundo vértice da aresta
                subgrafo.push_back(vertice1); //adiciona o primeiro vértice ao subgrafo
                subgrafo.push_back(vertice2); //adiciona o segundo vértice ao subgrafo
            }
        }

        std::cout << "{ ";
        for (int j = 0; j < subgrafo.size(); j += 2) {
            std::cout << "(" << subgrafo[j] << ", " << subgrafo[j+1] << ") ";
        }
        std::cout << "}" << std::endl;
    }