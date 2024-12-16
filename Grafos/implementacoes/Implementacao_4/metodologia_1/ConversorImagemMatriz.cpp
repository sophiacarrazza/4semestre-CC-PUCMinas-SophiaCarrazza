#define IMAGEM_PARA_MATRIZ

#include <sstream>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <tuple>
#include <vector>

using namespace std;


// função que converte a imagem PNG para PPM usando um script Python
void converterPNGparaPPM(const string& caminhoEntrada, const string& caminhoSaida) {

    string comando = "python3 png_to_ppm.py \"" + caminhoEntrada + ".png\" \"" + caminhoSaida + ".ppm\"";

    int resultadoComando = system(comando.c_str());

    if (resultadoComando != 0) {
        cerr << "Falha na conversão de PNG para PPM." << endl;
    }
}

int main() {

    string arquivoOrigem = "./img/igFiltro";
    string arquivoDestino = "./ppms/output";

    try {
        converterPNGparaPPM(arquivoOrigem, arquivoDestino); // converte o arquivo PNG para PPM
    } catch (const exception& erro) {
        cerr << "Erro: " << erro.what() << endl; // exibe a mensagem de erro
        return 1;
    }

    return 0;
}
