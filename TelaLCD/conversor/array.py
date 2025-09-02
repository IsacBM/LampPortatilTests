def bin_to_c_array(bin_path, array_name="image_data", output_path="image.h"):
    with open(bin_path, "rb") as f:
        data = f.read()

    # Cada pixel = 2 bytes (RGB565)
    num_pixels = len(data) // 2

    # Monta array C
    lines = []
    lines.append(f"const uint16_t {array_name}[{num_pixels}] = {{")
    for i in range(0, len(data), 2):
        pixel = data[i] | (data[i+1] << 8)  # little endian
        lines.append(f"0x{pixel:04X},")
    lines.append("};")

    # Salva em arquivo .h
    with open(output_path, "w") as f:
        f.write("\n".join(lines))

    print(f"Array gerado em {output_path} com {num_pixels} pixels.")


# Exemplo de uso
bin_to_c_array("conversor/saida.bin", "minha_imagem", "imagem.h")
