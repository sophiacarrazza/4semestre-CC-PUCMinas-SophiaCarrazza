# Segmentação de imagens baseada em grafos
Implementação 4 da disciplina de Teoria dos Grafos e Computabilidade - Segmentação de imagens baseada em grafos

# Fluxo de Execução da segmentação baseada na técnica de Pedro F. Felzenszwalb e Daniel P. Huttenlocher

1. **Input:** `input.png`
   - **Ação:** Executar o código `gaussian.py`
   - **Output:** `output_filtro.png`

2. **Input:** `output_filtro.png`
   - **Ação:** Executar o código `ConversorImagemMatriz.cpp`
   - **Output:** `output.ppm`

3. **Input:** `output.ppm`
   - **Ação:** Executar o código `Main.cpp`
   - **Output:** `segmentImage.ppm`

4. **Input:** `segmentImage.ppm`
   - **Ação:** Executar o código `ppmTopng`
   - **Output:** `output.png`

