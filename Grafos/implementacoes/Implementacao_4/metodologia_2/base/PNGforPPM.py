from PIL import Image

input_file = './impl2/img/peras2.png'

output_file = './impl2/base/input.ppm'

# Abrir a imagem
imagem = Image.open(input_file)

# Salvar a imagem no formato PNG
imagem.save(output_file, 'PPM')

print(f'Imagem convertida e salva como {output_file}')
