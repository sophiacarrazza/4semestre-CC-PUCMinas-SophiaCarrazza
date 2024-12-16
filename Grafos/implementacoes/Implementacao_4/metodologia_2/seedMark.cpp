#include <opencv2/opencv.hpp>
#include <iostream>
#include <deque>
#include "json.hpp"
#include <fstream>

using namespace cv;
using namespace std;
using json = nlohmann::json;

Mat imagemAtual;
deque<Point> pontosObjeto, pontosFundo;

// Função para lidar com cliques do mouse
void registrarClique(int acao, int posX, int posY, int, void*) {
    Point ponto(posX, posY);
    if (acao == EVENT_LBUTTONDOWN) { // Botão esquerdo -> Objeto
        pontosObjeto.push_back(ponto);
        putText(imagemAtual, "O", ponto, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
        cout << "Ponto Objeto: (" << posX << ", " << posY << ")\n";
    } else if (acao == EVENT_RBUTTONDOWN) { // Botão direito -> Fundo
        pontosFundo.push_back(ponto);
        putText(imagemAtual, "F", ponto, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);
        cout << "Ponto Fundo: (" << posX << ", " << posY << ")\n";
    }
    imshow("Marcar Ponto", imagemAtual);
}

// Função para salvar os pontos em um arquivo JSON
void salvarEmJSON(const deque<Point>& pontosObjeto, const deque<Point>& pontosFundo, const string& nomeArquivo) {
    json j;

    // Converter os pontos de objetos e fundo para formato adequado
    for (const auto& p : pontosObjeto) {
        j["objectSeeds"].push_back({{"x", p.x}, {"y", p.y}});
    }

    for (const auto& p : pontosFundo) {
        j["backgroundSeeds"].push_back({{"x", p.x}, {"y", p.y}});
    }

    // Salvar o JSON em um arquivo
    ofstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        arquivo << j.dump(4); // Indenta com 4 espaços
        cout << "Arquivo JSON salvo com sucesso!\n";
    } else {
        cerr << "Erro ao salvar o arquivo JSON.\n";
    }
}

// Função para iniciar o processo de seleção
void iniciarSelecao(const string& arquivo, deque<Point>& obj, deque<Point>& fundo) {
    Mat imagemOriginal = imread(arquivo);
    if (imagemOriginal.empty()) {
        cerr << "Erro ao carregar a imagem!\n";
        return;
    }

    imagemAtual = imagemOriginal.clone();

    namedWindow("Marcar Ponto", WINDOW_NORMAL);

    // Definir o tamanho fixo da janela
    int largura = 800;  // Largura desejada
    int altura = 600;   // Altura desejada
    resizeWindow("Marcar Ponto", largura, altura);
    setMouseCallback("Marcar Ponto", registrarClique);

    cout << "Clique esquerdo: Objeto (verde). Clique direito: Fundo (vermelho).\n";
    cout << "Pressione 'ESC' para finalizar.\n";

    while (true) {
        imshow("Marcar Ponto", imagemAtual);
        obj = pontosObjeto;
        fundo = pontosFundo;

        if (waitKey(30) == 27) break; // ESC para sair
    }

    cout << "\nPontos do Objeto:\n";
    for (const auto& p : obj)
        cout << "(" << p.x << ", " << p.y << ")\n";

    cout << "\nPontos do Fundo:\n";
    for (const auto& p : fundo)
        cout << "(" << p.x << ", " << p.y << ")\n";

    // Salvar os pontos em um arquivo JSON
    salvarEmJSON(obj, fundo, "./json/pontos.json");
}

int main() {
    string caminhoImagem = "./base/input.ppm";
    deque<Point> pontosObj, pontosFnd;

    iniciarSelecao(caminhoImagem, pontosObj, pontosFnd);

    return 0;
}
