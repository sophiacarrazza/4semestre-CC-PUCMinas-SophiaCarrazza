from PIL import Image

# Caminho do arquivo de entrada (PPM)
input_file = './segmentadas/segment_image.ppm'

# Caminho do arquivo de saída (PNG)
output_file = 'output.png'

# Abrir a imagem PPM
imagem = Image.open(input_file)

# Salvar a imagem no formato PNG
imagem.save(output_file, 'PNG')

print(f'Imagem convertida e salva como {output_file}')