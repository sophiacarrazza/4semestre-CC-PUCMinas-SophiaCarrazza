from PIL import Image
import sys

def convert_png_to_ppm(input_file, output_file):
    try:
        imagem = Image.open(input_file) # abre a imagem PNG
        
        if imagem.mode != 'RGB': # se a imagem já não for RGB, converte
            imagem = imagem.convert('RGB')
        
        imagem.save(output_file, format='PPM') # salva como PPM
        print(f"Imagem convertida: {output_file}")
    except Exception as e:
        print(f"Erro ao converter PNG para PPM: {e}")

if __name__ == "__main__": # se o script for executado diretamente
    if len(sys.argv) != 3:
        print("Uso: python3 pngToPpm.py <arquivo_entrada.png> <arquivo_saida.ppm>") # mensagem de erro
    else:
        input_file = sys.argv[1] # pega o nome do arquivo de entrada
        output_file = sys.argv[2]  # pega o nome do arquivo de saída
        convert_png_to_ppm(input_file, output_file) # chama a função de conversão
