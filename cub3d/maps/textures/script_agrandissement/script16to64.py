import sys
import os

def upscale_xpm(input_file):
    # Lire le fichier XPM
    with open(input_file, 'r') as file:
        lines = file.readlines()

    # Extraire les métadonnées
    header = lines[0:3]  # Les trois premières lignes sont souvent des métadonnées
    size_line = lines[0]
    size_parts = size_line.split()
    
    # Assurez-vous que l'image est 16x16
    width, height = int(size_parts[0]), int(size_parts[1])
    if width != 16 or height != 16:
        print("Ce script fonctionne uniquement avec des images 16x16.")
        return

    num_colors = int(size_parts[2])
    chars_per_pixel = int(size_parts[3])
    colors = lines[1:1 + num_colors]
    pixel_lines = lines[1 + num_colors:1 + num_colors + height]

    # Agrandir l'image
    new_width, new_height = 64, 64
    upscale_factor = new_width // width
    new_pixel_lines = []

    for line in pixel_lines:
        expanded_line = ''.join(char * upscale_factor for char in line.strip())
        for _ in range(upscale_factor):
            new_pixel_lines.append(expanded_line)

    # Mise à jour de l'en-tête
    new_size_line = f"{new_width} {new_height} {num_colors} {chars_per_pixel}\n"

    # Création du fichier de sortie
    output_file = input_file.replace(".xpm", "_64.xpm")
    with open(output_file, 'w') as file:
        file.write(new_size_line)
        file.writelines(colors)
        file.writelines(line + '\n' for line in new_pixel_lines)

    print(f"Image agrandie enregistrée dans {output_file}")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python upscale_xpm.py <file.xpm>")
        sys.exit(1)

    input_filename = sys.argv[1]
    if not os.path.isfile(input_filename) or not input_filename.endswith('.xpm'):
        print("Veuillez fournir un fichier .xpm valide.")
        sys.exit(1)

    upscale_xpm(input_filename)
