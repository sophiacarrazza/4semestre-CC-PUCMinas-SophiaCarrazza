import cv2
import numpy as np
import matplotlib.pyplot as plt

# Função para aplicar o filtro gaussiano
def aplicar_filtro_gaussiano(imagem, kernel_size=(15, 15), sigma=0.8):
    # Aplica o filtro gaussiano em cada canal da imagem se for colorida
    if len(imagem.shape) == 3:  # Caso a imagem seja colorida
        imagem_filtrada = cv2.GaussianBlur(imagem, kernel_size, sigma)
    else:  # Caso a imagem seja em escala de cinza
        imagem_filtrada = cv2.GaussianBlur(imagem, kernel_size, sigma)
    return imagem_filtrada

# Função de pré-processamento
def preprocessamento_imagem(imagem_path, imagem_saida_path):
    # Carregar a imagem
    imagem = cv2.imread(imagem_path, cv2.IMREAD_COLOR)

    if imagem is None:
        print("Erro ao carregar a imagem!")
        return None

    # Converter a imagem para escala de cinza
    imagem_cinza = cv2.cvtColor(imagem, cv2.COLOR_BGR2GRAY)

    # Aplicar o filtro gaussiano na imagem original (colorida) e na imagem em escala de cinza
    imagem_filtrada_colorida = aplicar_filtro_gaussiano(imagem)
    imagem_filtrada_cinza = aplicar_filtro_gaussiano(imagem_cinza)

    # Exibir as imagens
    plt.figure(figsize=(12, 8))

    plt.subplot(1, 3, 1)
    plt.imshow(cv2.cvtColor(imagem, cv2.COLOR_BGR2RGB))
    plt.title("Imagem Original")
    plt.axis('off')

    plt.subplot(1, 3, 2)
    plt.imshow(imagem_cinza, cmap='gray')
    plt.title("Escala de Cinza")
    plt.axis('off')

    plt.subplot(1, 3, 3)
    plt.imshow(cv2.cvtColor(imagem_filtrada_colorida, cv2.COLOR_BGR2RGB))
    plt.title("Imagem Filtrada (Filtro Gaussiano)")
    plt.axis('off')

    plt.tight_layout()
    plt.show()

    # Salvar a imagem filtrada
    cv2.imwrite(imagem_saida_path, imagem_filtrada_colorida)
    print(f"Imagem filtrada salva em: {imagem_saida_path}")

# Caminho para a imagem de entrada e saída
imagem_path = 'peras.png'  # Substitua pelo nome da sua imagem de entrada
imagem_saida_path = 'peraFiltro.png'  # Nome do arquivo de saída

# Realizar o pré-processamento
imagem_preprocessada = preprocessamento_imagem(imagem_path, imagem_saida_path)
