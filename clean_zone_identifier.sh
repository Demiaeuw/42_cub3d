#!/bin/bash

# Fonction pour parcourir et supprimer les fichiers Zone.Identifier
delete_zone_identifier() {
    for item in "$1"/*; do
        if [ -f "$item" ] && [[ "$item" == *Zone.Identifier ]]; then
            # Si l'élément est un fichier et qu'il s'appelle Zone.Identifier, le supprimer
            rm -v "$item"
        elif [ -d "$item" ]; then
            # Si l'élément est un dossier, appeler récursivement la fonction
            delete_zone_identifier "$item"
        fi
    done
}

# Appel de la fonction avec le répertoire actuel comme point de départ
delete_zone_identifier "."

echo "Suppression des fichiers Zone.Identifier terminée."
