#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_ETUDIANTS 2

#define NB_MATIERES 5
#define NB_NOTES 2
// Pour tester le programme vous pouvez diminuer  NB_ETUDIANTS  qui est 100
struct Etudiant {
    char prenom[20];
    char nom[20];;
    float notes[NB_MATIERES][NB_NOTES];
    float moyenne[NB_MATIERES];
    float moyenneGenerale;
    char mention[10];
};


int main() {
     printf("__          ___      .___  ___.       .______          ___       ______  __    __       ___      .______       _______      __  \n");
    printf("|  |        /   \\     |   \\/   |       |   _  \\        /   \\     /      ||  |  |  |     /   \\     |   _  \\     |       \\    |  | \n");
    printf("|  |       /  ^  \\    |  \\  /  |       |  |_)  |      /  ^  \\   |  ,----'|  |__|  |    /  ^  \\    |  |_)  |    |  .--.  |   |  | \n");
    printf("|  |      /  /_\\  \\   |  |\\/|  |       |      /      /  /_\\  \\  |  |     |   __   |   /  /_\\  \\   |      /     |  |  |  |   |  | \n");
    printf("|  |     /  _____  \\  |  |  |  |       |  |\\  \\----./  _____  \\ |  `----.|  |  |  |  /  _____  \\  |  |\\  \\----.|  '--'  |   |__| \n");
    printf("|__|    /__/     \\__\\ |__|  |__|       | _| `._____/__/     \\__\\ \\______||__|  |__| /__/     \\__\\ | _| `._____||_______/    (__) \n");
    printf("----------------------------------------------------------------------------------\n");
    printf("                              BIENVENUE DANS MON PROGAMME                              \n");
    printf("----------------------------------------------------------------------------------\n");

    struct Etudiant etudiants[NB_ETUDIANTS];
    int i, j, k;

    // R�cup�ration des notes de chaque �tudiant
    for (i = 0; i < NB_ETUDIANTS; i++) {
        printf("Etudiant %d\n", i + 1);
        printf("Pr�nom : ");
        scanf("%s", etudiants[i].prenom);
        printf("Nom : ");
        scanf("%s", etudiants[i].nom);
        for (j = 0; j < NB_MATIERES; j++) {
            printf("Notes pour la mati�re %d (2 notes) : ", j + 1);
            for (k = 0; k < NB_NOTES; k++) {
                scanf("%f", &etudiants[i].notes[j][k]);

            }
        }
    }

    // Calcul de la moyenne de chaque �tudiant par mati�re
    for (i = 0; i < NB_ETUDIANTS; i++) {
        for (j = 0; j < NB_MATIERES; j++) {
            float som = 0;
            for (k = 0; k < NB_NOTES; k++) {
                som += etudiants[i].notes[j][k];
            }
            etudiants[i].moyenne[j] = som / NB_NOTES;
        }
    }

    // Calcul de la moyenne g�n�rale de chaque �tudiant et de sa mention
    for (i = 0; i < NB_ETUDIANTS; i++) {
        float som = 0;
        for (j = 0; j < NB_MATIERES; j++) {
            som += etudiants[i].moyenne[j];
        }
        etudiants[i].moyenneGenerale = som / NB_MATIERES;
        if (etudiants[i].moyenneGenerale >= 16) {
            strcpy(etudiants[i].mention, "Tr�s bien");
        } else if (etudiants[i].moyenneGenerale >= 14) {
            strcpy(etudiants[i].mention, "Bien");
        } else if (etudiants[i].moyenneGenerale >= 12) {
            strcpy(etudiants[i].mention, "Assez bien");
        } else if (etudiants[i].moyenneGenerale >= 10){
                    strcpy(etudiants[i].mention, "Passable");
        } else {
           strcpy(etudiants[i].mention, "Inssuffisant");
        }
    }

    // Stockage des informations dans un fichier
    FILE *file = fopen("notes.txt", "w");
    if (file != NULL) {
        for (i = 0; i < NB_ETUDIANTS; i++) {
            fprintf(file, "%s %s", etudiants[i].prenom, etudiants[i].nom);
            for (j = 0; j < NB_MATIERES; j++) {
                fprintf(file, " %.2f", etudiants[i].moyenne[j]);
            }
            fprintf(file, " %.2f %s\n", etudiants[i].moyenneGenerale, etudiants[i].mention);
        }
        fclose(file);
    }

    // Affichage de la moyenne de la classe, la plus forte et la plus faible
    float moyenne_De_Classe =0.0;
        float plus_forte_moyenne = etudiants[0].moyenneGenerale;
    float plus_faible_moyenne = etudiants[0].moyenneGenerale;

    for (i = 0; i < NB_ETUDIANTS; i++) {
        moyenne_De_Classe += etudiants[i].moyenneGenerale;
        if (etudiants[i].moyenneGenerale > plus_forte_moyenne) {
            plus_forte_moyenne = etudiants[i].moyenneGenerale;
        }
        if (etudiants[i].moyenneGenerale < plus_faible_moyenne) {
            plus_faible_moyenne = etudiants[i].moyenneGenerale;
        }
    }

    moyenne_De_Classe /= NB_ETUDIANTS;

    printf("Moyenne de base de la classe : %.2f\n", moyenne_De_Classe);
    printf("Plus forte moyenne de la classe : %.2f\n", plus_forte_moyenne);
    printf("Moyenne la plus faible:  : %.2f\n", plus_faible_moyenne);

    // Affichage des informations sur un �tudiant sp�cifique
    char prenom[20], nom[20];
    printf("Entrez le pr�nom et le nom de l'�tudiant dont vous voulez afficher les informations : ");
    scanf("%s %s", prenom, nom);
    for (i = 0; i < NB_ETUDIANTS; i++) {
        if (strcmp(prenom, etudiants[i].prenom) == 0 && strcmp(nom, etudiants[i].nom) == 0) {
            printf("Informations pour %s %s :\n", prenom, nom);
            for (j = 0; j < NB_MATIERES; j++) {
                printf("Mati�re %d : %.2f\n", j + 1, etudiants[i].moyenne[j]);
            }
            printf("Moyenne g�n�rale : %.2f\n", etudiants[i].moyenneGenerale);
            printf("Rang : %d/%d\n", i + 1, NB_ETUDIANTS);
             printf("Mention : %s\n", etudiants[i].mention);
 printf("-------------------------------------------------------------\n");
    printf("                  Bulletin de notes                  \n");
    printf("------------------------------------------------------------\n");
    printf("Nom : %s\n", nom);
    printf("Prenom : %s\n", prenom);
    printf("------------------------------------------------------------\n");
    printf("Matiere\t\tNote 1\t\tNote 2\t\t\tMoyenne\n");
     for (j = 0; j < NB_MATIERES; j++) {
                printf("Mati�re %d : \t %.2f \t\t %.2f \t \t \t%.2f\n",j + 1,  etudiants[i].notes[j][0], etudiants[i].notes[j][1], etudiants[i].moyenne[j]);
            }
    printf("-------------------------------------------------------------\n");

   printf("--------------------------------------------------------------\n");
   printf("Moyenne g�n�rale : %.2f\n", etudiants[i].moyenneGenerale);
   printf("Rang : %d/%d\n", i + 1, NB_ETUDIANTS);
   printf("Mention : %s\n", etudiants[i].mention);
   printf("------------------------------------------------------------------\n");
      break;
        return 0;
    }

}

        }


