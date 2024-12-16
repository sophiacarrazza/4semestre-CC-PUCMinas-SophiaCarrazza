from PIL import Image
import numpy as np
import json

def carregar_mascaras(json_file, arquivo_entrada):
    # Carregar o arquivo JSON e extrair as seeds para as máscaras de objeto e fundo
    try:
        imagem = Image.open(arquivo_entrada)
        if imagem.format != "PPM":
            raise ValueError("O arquivo de entrada não é uma imagem PPM.")
        

        with open(json_file, 'r') as f:
            data = json.load(f)
        
        object_seeds = data["objectSeeds"]
        background_seeds = data["backgroundSeeds"]

        # Inicializar as máscaras com zeros (fundo)
        mascara_obj = np.zeros((imagem.height, imagem.width), dtype=int)
        mascara_fundo = np.zeros((imagem.height, imagem.width), dtype=int)

        # Definir as posições dos pixels de objeto e fundo
        for seed in object_seeds:
            mascara_obj[seed['y'], seed['x']] = 1
        
        for seed in background_seeds:
            mascara_fundo[seed['y'], seed['x']] = 1
        
        return mascara_obj, mascara_fundo

    except Exception as e:
        print(f"Erro ao carregar o arquivo JSON: {e}")
        return None, None


def calcular_histogramas(arquivo_entrada, mascara_obj, mascara_fundo):
    # Calcula histogramas para objeto e fundo com base nas máscaras fornecidas.
    
    # arquivo_entrada: Caminho da imagem PPM.
    # mascara_obj: Máscara binária indicando pixels do objeto (1).
    # mascara_fundo: Máscara binária indicando pixels do fundo (1).

    try:
        imagem = Image.open(arquivo_entrada)
        if imagem.format != "PPM":
            raise ValueError("O arquivo de entrada não é uma imagem PPM.")
        
        matriz_imagem = np.array(imagem)

        # Pixels do objeto e do fundo
        objeto_pixels = matriz_imagem[mascara_obj == 1]
        fundo_pixels = matriz_imagem[mascara_fundo == 1]

        histogramas = {}
        for i, canal in enumerate(['R', 'G', 'B']):
            hist_obj, _ = np.histogram(objeto_pixels[:, i], bins=256, range=(0, 255), density=True)
            hist_fundo, _ = np.histogram(fundo_pixels[:, i], bins=256, range=(0, 255), density=True)
            histogramas[canal] = {'obj': hist_obj.tolist(), 'bkg': hist_fundo.tolist()}  # Convertendo para lista para salvar em JSON

        return histogramas

    except Exception as erro:
        print(f"Erro ao calcular histogramas: {erro}")
        return None


def calcular_Rp(pixel, histogramas, tipo):
    # Calcula Rp para um pixel com base nos histogramas.
 
    R = 0
    for i, canal in enumerate(['R', 'G', 'B']):
        prob = histogramas[canal][tipo][pixel[i]]
        if prob > 0:
            R -= np.log(prob)
        else:
            R += np.inf  # Penalidade máxima para probabilidade zero
    return R


def salvar_histogramas_json(histogramas, nome_arquivo="histogramas.json"):
    # Salva o dicionário de histogramas em um arquivo JSON.
    try:
        with open(nome_arquivo, 'w') as f:
            json.dump(histogramas, f, indent=4)
        print(f"Histogramas salvos em {nome_arquivo}")
    except Exception as erro:
        print(f"Erro ao salvar histogramas em JSON: {erro}")


# Exemplo de uso:
arquivo_entrada = "./base/input.ppm"  # Caminho para a imagem PPM
arquivo_json = "./json/pontos.json"  # Caminho para o arquivo JSON com seeds

# Carregar as máscaras do arquivo JSON
mascara_obj, mascara_fundo = carregar_mascaras(arquivo_json, arquivo_entrada)

if mascara_obj is not None and mascara_fundo is not None:
    # Calcular histogramas
    histogramas = calcular_histogramas(arquivo_entrada, mascara_obj, mascara_fundo)

    if histogramas:
        # Salvar histogramas em JSON
        salvar_histogramas_json(histogramas, "./json/histogramas.json")
