import os

# Fonction pour lister les fichiers .rpy et afficher leur contenu
def lister_fichiers_rpy(repertoire):
    # Parcourir le répertoire et ses sous-répertoires
    for dossier_racine, dossiers, fichiers in os.walk(repertoire):
        for fichier in fichiers:
            # Vérifier si le fichier a l'extension .rpy
            if fichier.endswith(".hpp") or fichier.endswith(".cpp"):
                chemin_fichier = os.path.join(dossier_racine, fichier)
                print(f"Contenu du fichier '{chemin_fichier}':")
                try:
                    # Lire et afficher le contenu du fichier
                    with open(chemin_fichier, 'r', encoding='utf-8') as file:
                        contenu = file.read()
                        print(contenu)
                    print("=" * 80)  # Ligne de séparation
                except Exception as e:
                    print(f"Erreur lors de la lecture du fichier '{chemin_fichier}': {e}")

# Remplacez le chemin ci-dessous par le chemin de votre répertoire Ren'Py
repertoire_renpy = "."

lister_fichiers_rpy(repertoire_renpy)
