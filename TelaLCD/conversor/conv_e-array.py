from PIL import Image

def png_to_st7789_array(input_path, output_c_path, rotation=0):
    """
    Converte PNG/JPG para array C compatível com ST7789.
    rotation: 0, 90, 180, 270
    """
    img = Image.open(input_path).convert("RGB")
    # Rotaciona a imagem se necessário
    if rotation in [90, 180, 270]:
        img = img.rotate(rotation, expand=True)
    
    width, height = img.size
    pixels = list(img.getdata())

    with open(output_c_path, "w") as f:
        f.write(f"// Image {width}x{height} converted for ST7789 RGB565\n")
        f.write(f"const uint16_t image_data[{width*height}] = {{\n")
        for i, (r, g, b) in enumerate(pixels):
            # converte para RGB565
            rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
            f.write(f"0x{rgb565:04X}, ")
            if (i+1) % 12 == 0:  # quebra de linha a cada 12 pixels pra ficar legível
                f.write("\n")
        f.write("\n};\n")

    print(f"Array C gerado com sucesso: {output_c_path}")
    print(f"Tamanho estimado: {width*height*2/1024:.2f} KB")

# Exemplo de uso:
png_to_st7789_array("conversor/saida.jpeg", "imagem_st7789.h", rotation=0)
