#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100
#define MAX_PREFIXES 10

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Veuillez fournir le nom du fichier à modifier en argument.\n");
        return 1;
    }

    char *nomFichier = argv[1];
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier %s.\n", nomFichier);
        return 1;
    }

    char ligne[MAX_CHAR];
    char prefixes[MAX_PREFIXES][MAX_CHAR];
    double valeurs[MAX_PREFIXES];
    int nombrePrefixes = 0;
    int saisieTerminee = 0;

    printf("Entrez les paramètres et les valeurs correspondantes (terminez par 'end') :\n");

    while (!saisieTerminee && nombrePrefixes < MAX_PREFIXES) {
        scanf("%s", prefixes[nombrePrefixes]);
        if (strcmp(prefixes[nombrePrefixes], "end") == 0) {
            saisieTerminee = 1;
        } else {
            char valeur[MAX_CHAR];
            scanf("%s", valeur);
            valeurs[nombrePrefixes] = strtod(valeur, NULL);
            nombrePrefixes++;
        }
    }

    // Créer un fichier temporaire pour stocker les modifications
    FILE *fichierTemp = tmpfile();
    if (fichierTemp == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return 1;
    }

    int prefixeTrouve = 0; // Indicateur si un préfixe a été trouvé et modifié
    char prefixesModifies[MAX_PREFIXES][MAX_CHAR];
    int nombrePrefixesModifies = 0;

    while (fgets(ligne, MAX_CHAR, fichier) != NULL) {
        int prefixeCorrespondant = 0;
        char ligneModifiee[MAX_CHAR]; // Variable pour stocker la ligne modifiée

        for (int i = 0; i < nombrePrefixes; i++) {
            char prefixeAChercher[MAX_CHAR];
            sprintf(prefixeAChercher, "%s =", prefixes[i]);
            char prefixeAChercher2[MAX_CHAR];
            sprintf(prefixeAChercher2, "%s=", prefixes[i]);

            // Supprimer les espaces supplémentaires avant et après le préfixe dans la ligne
            char* debutLigne = ligne;
            while (*debutLigne == ' ') {
                debutLigne++;
            }

            if (strstr(debutLigne, prefixeAChercher) == debutLigne || strstr(debutLigne, prefixeAChercher2) == debutLigne) {
                // La ligne commence par l'un des préfixes, la modifier avec le nouveau contenu
                sprintf(ligneModifiee, "%s = %.8e\n", prefixes[i], valeurs[i]);
                prefixeCorrespondant = 1;
                prefixeTrouve = 1;
                strcpy(prefixesModifies[nombrePrefixesModifies], prefixes[i]);
                nombrePrefixesModifies++;
                break;
            }
        }

        if (prefixeCorrespondant) {
            // Préfixe correspondant trouvé, copier la ligne modifiée dans le fichier temporaire
            fprintf(fichierTemp, "%s", ligneModifiee);
        } else {
            // Aucun préfixe correspondant, copier la ligne telle quelle dans le fichier temporaire
            fprintf(fichierTemp, "%s", ligne);
        }
    }

    fclose(fichier);
    rewind(fichierTemp); // Remettre le curseur au début du fichier temporaire

    // Ouvrir le fichier original en mode d'écriture
    fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier %s.\n", nomFichier);
        fclose(fichierTemp);
        return 1;
    }

    // Copier le contenu du fichier temporaire dans le fichier original
    while (fgets(ligne, MAX_CHAR, fichierTemp) != NULL) {
        fprintf(fichier, "%s", ligne);
    }

    fclose(fichier);
    fclose(fichierTemp);

    if (prefixeTrouve) {
        printf("Lignes modifiées avec succès.\n");
        printf("Paramètres modifiés :\n");
        for (int i = 0; i < nombrePrefixesModifies; i++) {
            printf("- %s\n", prefixesModifies[i]);
        }
    } else {
        printf("Le paramètre n'a pas été trouvé dans le fichier.\n");
    }

    return 0;
}
