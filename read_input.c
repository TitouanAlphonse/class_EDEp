#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Veuillez fournir le nom du fichier en argument.\n");
        return 1;
    }

    char *nomFichier = argv[1];
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier %s.\n", nomFichier);
        return 1;
    }

    char ligne[MAX_CHAR];
    char parametreRecherche[MAX_CHAR];

    printf("Entrez les paramètres à rechercher (ou 'end' pour quitter) :\n");
    while (1) {
        scanf("%s", parametreRecherche);

        if (strcmp(parametreRecherche, "end") == 0) {
            break;
        }

        int parametreTrouve = 0;

        rewind(fichier); // Réinitialiser la position du curseur de fichier au début

        while (fgets(ligne, MAX_CHAR, fichier) != NULL) {
            // Supprimer les espaces avant et après la ligne
            char *debutLigne = ligne;
            char *finLigne = ligne + strlen(ligne) - 1;
            while (*debutLigne == ' ') {
                debutLigne++;
            }
            while (finLigne > debutLigne && (*finLigne == ' ' || *finLigne == '\n' || *finLigne == '\r')) {
                *finLigne = '\0';
                finLigne--;
            }

            // Recherche du paramètre
            char *valeur = strstr(debutLigne, parametreRecherche);
            if (valeur != NULL) {
                valeur += strlen(parametreRecherche);
                while (*valeur == ' ') {
                    valeur++;
                }
                if (*valeur == '=') {
                    valeur++;
                    while (*valeur == ' ') {
                        valeur++;
                    }

                    // Affichage de la valeur
                    printf("Valeur de %s : %s\n", parametreRecherche, valeur);
                    parametreTrouve = 1;
                    break;
                }
            }
        }

        if (!parametreTrouve) {
            printf("Paramètre introuvable.\n");
        }
    }

    fclose(fichier);

    return 0;
}