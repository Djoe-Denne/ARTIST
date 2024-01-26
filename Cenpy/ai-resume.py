import os

# Function to list .rpy files and display their content
def lister_fichiers_rpy(repertoire):
    # Traverse the directory and its subdirectories
    for dossier_racine, dossiers, fichiers in os.walk(repertoire):
        for fichier in fichiers:
            # Check if the file has the .hpp or .cpp extension
            if fichier.endswith(".hpp") or fichier.endswith(".cpp"):
                chemin_fichier = os.path.join(dossier_racine, fichier)
                # Check if 'graphic' is part of the file path
                if 'graphic' in chemin_fichier.split(os.sep):
                    print(f"Contenu du fichier '{chemin_fichier}':")
                    try:
                        # Read and display the file content
                        with open(chemin_fichier, 'r', encoding='utf-8') as file:
                            contenu = file.read()
                            print(contenu)
                        print("=" * 80)  # Separation line
                    except Exception as e:
                        print(f"Erreur lors de la lecture du fichier '{chemin_fichier}': {e}")

# Replace the path below with the path to your Ren'Py directory
repertoire_renpy = "."

lister_fichiers_rpy(repertoire_renpy)
