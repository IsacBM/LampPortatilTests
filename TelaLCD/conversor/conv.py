from PIL import Image

def convert_png_to_rgb565(input_path, output_path):
    # Abre a imagem
    img = Image.open(input_path).convert("RGB")
    
    # Converte para 240x320 (ou o tamanho do teu display)
    img = img.resize((240, 320))

    # Buffer para os pixels
    pixel_data = []

    for y in range(img.height):
        for x in range(img.width):
            r, g, b = img.getpixel((x, y))

            # Converte para 16 bits RGB565
            rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

            # Adiciona como 2 bytes (MSB, LSB)
            pixel_data.append(rgb565 >> 8)
            pixel_data.append(rgb565 & 0xFF)

    # Salva em arquivo binário
    with open(output_path, "wb") as f:
        f.write(bytearray(pixel_data))

    print(f"Imagem convertida e salva em {output_path} ({img.width}x{img.height})")

# Exemplo de uso:
convert_png_to_rgb565("conversor/saida2.jpeg", "saida.bin")
