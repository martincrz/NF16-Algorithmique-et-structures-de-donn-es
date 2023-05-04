#include <stdio.h>
#include <stdlib.h>

#include "header.h"
#include "fonctions.c"

int main()
{
    char n[taille_nom_max];
    long id;
    int c;

    T_Electeur list_elec=NULL, list_droit=NULL, list_gauche=NULL, list_blanc=NULL, list_fusion=NULL;
    T_Electeur nv_elect=creationelecteur();

    /*
    list_elec=ajoutentete(list_elec, "Zlatan", 320, 5);
    list_elec=ajoutentete(list_elec, "Zoe", 240, 3);
    list_elec=ajoutentete(list_elec, "Xavier", 369, 5);
    list_elec=ajoutentete(list_elec, "Tom", 548, 5);
    list_elec=ajoutentete(list_elec, "Stephanie", 250, 1);
    list_elec=ajoutentete(list_elec, "Rayenne", 540, 5);
    list_elec=ajoutentete(list_elec, "Nadine", 220, 2);
    list_elec=ajoutentete(list_elec, "Matuidi", 110, 5);
    list_elec=ajoutentete(list_elec, "Jacques", 140, 5);
    list_elec=ajoutentete(list_elec, "Camille", 170, 1);
    list_elec=ajoutentete(list_elec, "Bernard", 100, 3);
    list_elec=ajoutentete(list_elec, "Albert", 160, 4);
    */

    int num=0;
    int c_quest=0;
    while (num!=9)
    {
        printf("\n* * * * * * * * * * * * * * * * * * * * * MENU * * * * * * * * * * * * * * * * * * * * * \n");
        printf("\n1. Entrer un electeur et l ajouter dans la liste ,\n2. Supprimer un electeur,\n3. Rechercher un electeur,\n4. Afficher la liste des electeurs,\n5. Calculer le nombre des electeurs,\n6. Decouper la liste en trois sous-listes selon les choix: droite, gauche et blanc,\n7. Calculer les pourcentages de gauche et de droite pour le 2eme tour,");
        printf("\n8. Liberer les listes,\n9. Quitter\n");

        printf("\nVeuillez choisir la fonctionnalite desiree : ");
        scanf("%d",&num);

        switch (num)
        {
            case 1:

                printf("\nVous avez choisi d entrer et ajouter un nouvel electeur");
                printf("\nSaisir Nom : ");
                scanf("%s", &n);
                while (getchar()!='\n');
                while (strlen(n)>taille_nom_max)
                {
                    printf("La taille du nom doit etre inferieur a %d", taille_nom_max);
                    scanf("%s", &n);
                }

                printf("Saisir Num de la carte : ");
                scanf("%ld", &id);
                if (trouvelecteur(list_elec, id)==1)
                {
                    printf("Un electeur avec ce numero existe deja\n");
                    break;
                }

                printf("Saisir Choix : ");
                scanf("%d", &c);
                while (c<1 || c>5)
                {
                    printf("Le choix doit etre compris entre 1 et 5 \n");
                    printf("Saisir un choix correct : ");
                    scanf("%d", &c);
                }
                printf("\n");


                strcpy(nv_elect->nom, n);
                nv_elect->cin_num=id;
                nv_elect->choix=c;
                nv_elect->suivant=NULL;

                ajoutelecteur(&list_elec,nv_elect->nom,nv_elect->cin_num, nv_elect->choix);
                printf("L electeur %s, au numero d identite %ld a bien ete ajoute a la liste electorale\n\n\n", nv_elect->nom,nv_elect->cin_num);


                break;

            case 2:
                printf("\nVous avez choisi de supprimer un electeur");
                if (list_elec==NULL)
                {
                    printf("\nLa liste electorale est vide");
                    printf("\n\n");
                    break;
                }
                printf("\nSaisir l id de l electeur a supprimer : ");
                scanf("%ld", &id);

                Supprimelecteur(&list_elec, id);
                printf("\n\n");
                break;

            case 3:
                printf("\nVous avez choisi de rechercher un electeur");
                if (list_elec==NULL)
                {
                    printf("\nLa liste electorale est vide");
                    printf("\n\n");
                    break;
                }
                printf("\nSaisir l id de l electeur a rechercher : ");
                scanf("%ld", &id);
                affiche_donnees(list_elec, id);
                printf("\n\n");
                break;

            case 4:
                printf("\nVous avez choisi d afficher la liste d electeurs\n");
                afficheliste(list_elec);
                break;

            case 5:
                printf("\nVous avez choisi d afficher le nombre des electeurs dans la liste");
                printf("\nLe nombre d electeur est de %d \n", comptelecteur(list_elec));
                break;

            case 6:
                printf("\nVous avez choisi de decouper la liste en 3 sous listes: droite, gauche et blanc : ");
                if (list_elec==NULL)
                {
                    printf("\nLa liste electorale est vide");
                    printf("\n\n");
                    break;
                }
                //on remet les listes à zero, au cas ou il y a un ajout ou une suppression dans la liste
                list_blanc=NULL;
                list_droit=NULL;
                list_gauche=NULL;
                decoupeliste(list_elec, &list_gauche, &list_droit,  &list_blanc);
                printf("Liste decoupee\n");


                printf("\n----------------------------------------------------------------------------------------------------------------------\n");
                printf("6. Decouper la liste en trois sous-listes:");
                printf("\n      1. Trier les sous-listes\n      2. Afficher les sous-listes,\n      3. Fusionner les deux sous-listes : gauche et droite \n      4. Quitter" );
                printf("\nVeuillez choisir la fonctionnalite : ");

                scanf("%d", &c_quest);

                while (c_quest!=4)
                {
                    switch (c_quest)
                    {
                        case 1 :
                            printf("\nVous avez choisi de trier les sous listes par ordre croissant du num id : tri effectue\n");
                            triliste(&list_blanc);
                            triliste(&list_droit);
                            triliste(&list_gauche);
                            if (list_fusion!=NULL)triliste(&list_fusion);


                            printf("\n----------------------------------------------------------------------------------------------------------------------\n");
                            printf(" Vous avez trie les listes, que voulez vous faire ensuite?");
                            printf("\n      1. Trier les listes \n      2. afficher les listes\n      4. Quitter" );
                            printf("\nVeuillez choisir la fonctionnalite : ");
                            scanf("%d", &c_quest);
                            if (c_quest!=2 && c_quest!=1) {c_quest=4;}
                            break;

                        case 2:
                            printf("\nVous avez choisi d afficher les sous listes\n");
                            printf("\nListe des electeurs ayant vote le NOM1 ou le NOM3 (candidats de gauche)\n");
                            afficheliste(list_gauche);
                            printf("\nListe des electeurs ayant vote le NOM2 ou le NOM4 (candidats de droite)\n");
                            afficheliste(list_droit);
                            printf("\nListe des electeurs ayant vote blanc\n");
                            afficheliste(list_blanc);
                            if (list_fusion!=NULL)
                            {
                                printf("\nListe des electeurs ayant vote autre que blanc (liste fusionnee)\n");
                                afficheliste(list_fusion);
                            }

                            printf("\n----------------------------------------------------------------------------------------------------------------------\n");
                            printf("Vous avez affiche les listes, que voulez vous faire ensuite?");
                            printf("\n      1. Trier les sous-listes affichees ci dessus selon le numero \n      3. Fusionner les deux sous-listes : gauche et droite \n      4. Quitter" );
                            printf("\nVeuillez choisir la fonctionnalite : ");
                            scanf("%d", &c_quest);
                            if (c_quest!=1 && c_quest!=3) {c_quest=4;}
                            break;

                        case 3:
                            printf("\nVous avez choisi de fusionner les sous listes droite et gauche : fusion effectuee\n");
                            list_fusion=fusionlistes(list_droit, list_gauche);
                            triliste(&list_fusion);

                            printf("\n----------------------------------------------------------------------------------------------------------------------\n");

                            printf("Vous avez fusionne les listes, que voulez vous faire ensuite?");
                            printf("\n      2. Afficher les sous-listes dont la liste fusionnee, \n      4. Quitter" );
                            printf("\nVeuillez choisir la fonctionnalite : ");
                            scanf("%d", &c_quest);
                            if (c_quest!=2) {c_quest=4;}
                            break;

                        case 4:
                            printf("Vous avez choisi de quitter");
                            break;

                        default :
                            printf("\nAucune fonctionnalite selectionnee\n");
                            printf("Saisir nb correct : ");
                            scanf("%d", &c_quest);
                            break;
                    }
                }
                break;

            case 7:
                printf("\nVous avez choisi de calculer les pourcentages de gauche et de droite pour le 2eme tour\n");
                //on remet les listes à zero, au cas ou il y a un ajout ou une suppression dans la liste
                if (list_elec==NULL)
                {
                    printf("\nLa liste electorale est vide");
                    printf("\n\n");
                    break;
                }
                list_blanc=NULL;
                list_droit=NULL;
                list_gauche=NULL;
                decoupeliste(list_elec, &list_gauche, &list_droit, &list_blanc);
                list_fusion=fusionlistes(list_droit, list_gauche);
                printf("Nombre electeurs ayant vote autre que blanc %d\n", comptelecteur(list_fusion));
                printf("Nombre electeurs ayant vote a gauche %d\n", compteGD(list_fusion));
                float pourcentage_g = 100*compteGD(list_fusion)/comptelecteur(list_fusion);
                printf("Pourcentage vote a droite : %f \%\n", 100- pourcentage_g);
                printf("Pourcentage vote a gauche : %f \%\n", pourcentage_g);
                printf("\n");
                break;

            case 8:
                printf("\nVous avez choisi de liberer les listes\n");
                printf("On vide liste electeur\n");
                libereliste(&list_elec);
                if (list_blanc!=NULL)
                {
                    printf("On vide liste blanc\n");
                    libereliste(&list_blanc);
                }
                if (list_droit!=NULL)
                {
                    printf("On vide liste droite\n");
                    libereliste(&list_droit);
                }
                if (list_gauche!=NULL)
                {
                    printf("On vide liste gauche\n");
                    libereliste(&list_gauche);
                }
                if (list_fusion!=NULL)
                {
                    printf("On vide liste fusionnee\n");
                    libereliste(&list_fusion);
                }
                printf("\n");
                break;

            case 9:
                printf("\nVous avez choisi de quitter \n");
                break;
            default :
                printf("Choisir un chiffre correct \n");

        }


    }
    return 0;
}
