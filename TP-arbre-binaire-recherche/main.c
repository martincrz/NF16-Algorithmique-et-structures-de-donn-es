#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "fonctions.c"

int main()
{

    char* nom_fichier;
    t_Index* index=creer_index();
    int a_indexer=0;

    int choix=0;
    while (choix!=8)
    {
        printf("\n      ----------------MENU----------------      \n\n");
        printf("1. Charger un fichier \n2. Caracteristiques de l'index\n3. Afficher index\n4. Rechercher un mot\n5. Afficher le mot avec le maximum d'apparitions\n6. Afficher les occurences d'un mot\n7. Construire le texte a partir de l'index\n8. Quitter\n\n");
        printf("Saisir une fonctionnalite : ");
        scanf("%d",&choix);
        printf("\n");
        printf("      ------------------------------------      \n\n");

        switch (choix)
        {
        case 1:

            printf("Objectif : lire un fichier et le charger dans un index puis afficher le nombre de mots lus dans le fichier. \n\n");
            printf("Nom du fichier : ");
            scanf("%s", &nom_fichier);
            indexer_fichier(index,&nom_fichier); //indexe et affiche nombre de mots
            a_indexer=1;

            break;

        case 2:
            if (a_indexer==0)
            {
                printf("Veuillez d'abord charger un fichier dans la fonction 1\n");
                break;
            }
            printf("Objectif : Afficher les caracteristiques de l’index et si oui ou non il est equilibre. \n\n");
            printf("Nombre de mots totales : %d\nNombre de mots differents : %d\n", index->nb_mots_total, index->nb_mots_differents);

            if (estequilibre(index->racine)==1) printf("L arbre est equilibre\n");
            else printf("L'arbre n est pas equilibre\n");

            break;

        case 3:
            if (a_indexer==0)
            {
                printf("Veuillez d'abord charger un fichier dans la fonction 1\n");
                break;
            }
            printf("Objectif : Afficher les mots contenus dans l’index en respectant le format demande. \n\n");
            afficher_index(index);
            printf("\n");
            break;

        case 4:
            if (a_indexer==0)
            {
                printf("Veuillez d'abord charger un fichier dans la fonction 1\n");
                break;
            }
            printf("Objectif : Afficher le num de ligne, l'ordre dans la ligne, le num de phrase pour chaque occurrence.  \n\n");
            char* m;
            printf("Saisir un mot : ");
            scanf("%s", &m);
            t_Noeud* noeud_recherche=rechercher_mot(index, &m);
            printf("Mot : %s\nNombre occurences : %d\n", noeud_recherche->mot, noeud_recherche->nb_occurences);
            afficheliste(&noeud_recherche->positions);

            /*while (noeud_recherche->positions->debut!=NULL)
            {
                printf("test\n");
                printf("Num ligne : %d\nOrdre dans ligne : %d\nNum phrase : %d\n",noeud_recherche->positions->debut->numero_ligne,noeud_recherche->positions->debut->ordre,noeud_recherche->positions->debut->numero_phrase);
                noeud_recherche->positions->debut=noeud_recherche->positions->debut->suivant;
            }*/
            break;

        case 5:
            if (a_indexer==0)
            {
                printf("Veuillez d'abord charger un fichier dans la fonction 1\n");
                break;
            }
            printf("Objectif : Afficher le mot et le nombre d’occurrences. \n\n");
            afficher_max_apparition(index);
            break;

        case 6:
            if (a_indexer==0)
            {
                printf("Veuillez d'abord charger un fichier dans la fonction 1\n");
                break;
            }
            printf("Objectif : Recherche un mot dans l index et affiche toutes les phrases dans lesquelles il apparait. \n\n");
            char* mot;
            printf("Saisir un mot : ");
            scanf("%s", &mot);
            afficher_occurences_mot(index, &mot);
            break;

        case 7:
            if (a_indexer==0)
            {
                printf("Veuillez d'abord charger un fichier dans la fonction 1\n");
                break;
            }

            printf("Objectif : Affiche le texte et l enregistre dans un fichier. \n\n");
            char* nom_f;

            printf("Saisir nom du nouveau fichier : ");
            scanf("%s", &nom_f);
            printf("\n");
            printf("Voici le texte ajoute au fichier :\n\n");
            construire_texte(index, &nom_f );
            break;

        case 8 :
            printf("Fin de l execution \n\n");
            free(index);
            break;

        default :
            printf("Saisir un chiffre correct \n");
            break;
        }

    }

}
/*ajouter des maj partout*/
