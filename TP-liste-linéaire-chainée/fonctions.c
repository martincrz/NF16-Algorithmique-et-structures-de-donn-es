#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

T_Electeur creationelecteur(void)
{
    /*********************************
    * Fonction :
    *       fonction qui permet de créer un électeur
    * Objectifs :
    *       allocation dans la mémoire de l'espace pour un electeur
    ***********************************/

    T_Electeur nv_elec = malloc(sizeof(electeur)); //allocation dans la memoire
    if (nv_elec!=NULL) //si allocation  reussie
    {
        return nv_elec; //on le retourne
    }
    else //sinon
    {
        printf("Erreur dans l'allocation"); //on affiche une erreur
        return NULL; //on retourne NULL
    }
}

int nombreChiffres (int nombre )
{
    /*********************************
    * Fonction :
    *       fonction qui renvoie le nombre de chiffre dans nombre
    *
    ***********************************/

	int i = 1;
	if (nombre < 0) //si il est negatif
	{
		nombre = -nombre; //on le met positif
	}
	while (nombre >= 10) //on regarde cb de fois on peut le diviser par 10
	{
		nombre /= 10;
		i++;
	}
	return i;
}

void afficheliste(T_Electeur E)
{
    /*********************************
    * Fonction :
    *       fonction qui affiche la liste des électeurs
    * Objectifs :
    *       affiche tous les noms, num et choix en colonne des electeurs de la liste electorale
    *       colonnes bien alignés
    ***********************************/
    T_Electeur elect=E;
    int i=0;
    if (elect==NULL)
    {
        printf("\nListe vide\n\n");
        return;
    }
    //Tant que l'on n'est pas au bout de la liste
    printf("- - - - - - - - - - - - - - ");
    while (elect != NULL)
    {
        printf("\n%s", elect->nom); //affiche nom de l electeur
        for (i=0; i<taille_nom_max-strlen(elect->nom);i++) //affiche x espaces
        {
            printf(" ");
        }
        printf("%ld",elect->cin_num); //affiche numero de l electeur
        for (i=0; i<10-nombreChiffres(elect->cin_num);i++) //affiche y espaces
        {
            printf(" ");
        }
        printf("%d", elect->choix); //affiche le choix de l electeur
        elect=elect->suivant;
    }
    printf("\n- - - - - - - - - - - - - - \n");
    printf("\n");
}

T_Electeur ajoutentete(T_Electeur E, char nom[taille_nom_max], long id, int choix ) //a supprimer
{
    //ajoute un électeur en tete de liste
    T_Electeur nv_elec=creationelecteur();//allocation dans la mémoire
    //on lui donne ses attributs (ceux données en parametres)
    strcpy(nv_elec->nom, nom);
    nv_elec->cin_num=id;
    nv_elec->choix=choix;
    nv_elec->suivant=E;
    return nv_elec; //on retourne la tete de la liste (=ce nouvel t_electeur)
}

T_Electeur precedent(T_Electeur elect, long id)
{
    //renvoie l'électeur précédent à celui saisi au paramètre
    while (elect!=NULL)//on parcourt la suite
        {
            if (elect->suivant->cin_num==id)//si le suivant a meme num id
            {
                return elect; //on s arrete et on retourne l electeur pointé
            }
            elect=elect->suivant; //sinon on passe au suivant
        }
    return NULL;
}

void ajoutelecteur(T_Electeur *E, char nom[taille_nom_max], long id , int choix)
{
    /*********************************
    * Fonction :
    *       fonction qui ajoute un électeur dans la liste
    * Objectifs :
    *       garder les electeurs dans un ordre alphabétique
    *       cas si liste vide
    *       cas ajout en tete
    *       cas ajout en fin
    ***********************************/
    T_Electeur elect=*E;

    T_Electeur nv_elect = creationelecteur();
    strcpy(nv_elect->nom, nom);
    nv_elect->cin_num=id;
    nv_elect->choix=choix;

    //cas si la liste est vide
    if (elect==NULL)
    {
        //on le met en tete de liste
        elect=nv_elect;
        nv_elect->suivant=NULL;
        *E=elect;
        return;
    }
    else
    {
        //cas ou le nv electeur doit etre place en tete de liste
        if (strcmp(nv_elect->nom, elect->nom)<0)
        {
            //on le met en tete de liste
            nv_elect->suivant=elect;
            elect=nv_elect;
            *E=elect;
            return;
        }
        //sinon, on défile electeur par electeur
        else
        {
            while (elect!=NULL)
            {
                //quand on arrive à la fin de la liste : on le place à la fin
                if (elect->suivant==NULL)
                {
                    elect->suivant=nv_elect;
                    nv_elect->suivant=NULL;
                    return;
                //sinon on regarde si le suivant est plus grand ou plus petit que l electeur à inserer
                }
                else
                {
                    if (strcmp(nv_elect->nom, elect->nom)<0)
                    {
                        nv_elect->suivant=elect->suivant;
                        elect->suivant=nv_elect;
                        return;
                    }
                    else
                    {
                        elect=elect->suivant;
                    }
                }
            }
        }
    }


}

int comptelecteur(T_Electeur E)
{
    /*********************************
    *  renvoie le nbre electeur de la liste
    *  renvoie 0 si liste vide
    ***********************************/

    int nbre_elec=0;
    if (E==NULL)return 0;
    while (E!=NULL) //on parcourt la liste
    {
        nbre_elec+=1; //on incremente le nbre d electeur
        E=E->suivant;
    }
    return nbre_elec; //on retourne le nombre d'electeur
}

int trouvelecteur(T_Electeur E, long id)
{
    /********************************
    * cherche si l'electeur au numero indique est dans la liste
    * renvoie 1 s'il existe
    * renvoie 0 si liste vide
    * renvoie -1 si id n existe pas dans la liste
    ***********************************/
    if (E==NULL) return 0;

    while (E!=NULL) //on parcourt la liste
    {
        if (E->cin_num==id) //des qu on a id= num_cin, on quitte (dans la liste il y a seule occurrence de num_cin=id)
        {
            return 1;
        }
        else {E=E->suivant;} //sinon on passe au suivant
    }
    return -1;
}

void affiche_donnees(T_Electeur E, long id)
{
    //affiche les donnees de l electeur au numero de ci indique
    //on vérifie sil est bien dans la liste
    if (trouvelecteur(E, id)==-1)
    {
        printf("Cet electeur n existe pas dans la liste\n");
        return;
    }
    //si oui, on parcourt jusqu'à trouver l'electeur ayant ce numéro id
    while (E!=NULL && E->cin_num!=id)
    {
        E=E->suivant;
    }
    //on affiche ses données
    printf("\nVoici les donnees de l'id %ld : \n", E->cin_num);
    printf("Nom : %s, Choix: %d \n", E->nom, E->choix);
    return ;
}

void Supprimelecteur(T_Electeur *E,long id)
{
    /*********************************
    * Fonction qui supprime un electeur de la liste selon le num indique
    * Liberation de la mémoire lors de la suppression
    ***********************************/

    T_Electeur elect=*E;
    T_Electeur elect_a_supp=NULL;

    //cas : liste vide : dans le main.c, pas d'appel de la fonction si la liste est vide

    //cas : pas dans la liste
    if (trouvelecteur(elect, id)==-1)
    {
        printf("\nCet electeur n existe pas\n");
        free(elect_a_supp);
        return;
    }

    //cas elect a supp est en debut de liste
    if (elect->cin_num==id)
    {
        elect_a_supp=elect;
        elect=elect->suivant;
        free(elect_a_supp);
        *E=elect; //la nouvelle tete est le suivant de l electeur qu on a supprimé
        return;
    }
    else //sinon
    {
        elect=precedent(elect, id); //on cherche le precedent de l electeur a supprimer
        elect_a_supp=elect->suivant; //on appelle elect_a_supp l electeur a supp : qui correspond au suivant de son précédent
        elect->suivant=elect->suivant->suivant; //on lie son précédent avec son suivant
        free(elect_a_supp); //on libère l electeur à supprimer
        return;
    }
}

void decoupeliste(T_Electeur elect,T_Electeur *e_gauche,T_Electeur *e_droite,T_Electeur *e_blanc)
{
    /*********************************
    * Cette fonction décompose la liste des électeurs en trois sous-listes gauche, droite et blanc selon le choix de candidats.
    * (1 ou 3 pour gauche et 2 ou 4 pour droite sinon blanc).
    *
    * On appelle la fonction ajoutelecteur pour garder ces listes dans l'ordres alphabétiques
    ***********************************/

    //cas liste vide : vérifié dans le main

    while (elect!=NULL) //on parcourt la liste, et on ajoute l electeur dans une liste selon son choix
    {
        if (elect->choix==1 || elect->choix==3)ajoutelecteur(e_gauche, elect->nom, elect->cin_num, elect->choix);
        else if (elect->choix==2 || elect->choix==4)ajoutelecteur(e_droite, elect->nom, elect->cin_num, elect->choix);
        else ajoutelecteur(e_blanc, elect->nom, elect->cin_num, elect->choix);
        elect=elect->suivant;
    }

}

T_Electeur minimum(T_Electeur elect)
{
    //renvoie le t_electeur qui a le plus petit num id dans la liste
    long min=999999999; //on initialise min à un nbre tres grand
    T_Electeur elect_min;
    while (elect!=NULL)//on parcourt la liste
    {
        if(elect->cin_num<min) //des que le num id de l'electeur est plus petit que le min
        {
            min=elect->cin_num; //on attribue cette valeur au min
            elect_min=elect; //on appelle elect_min cet electeur
        }
        else elect=elect->suivant; //sinon on passe au suivant
    }
    return elect_min; //on retourne l electeur minimum
}

void triliste(T_Electeur *E)
{
    /****************
    * Fonction qui trie par ordre croissant de cin_num
    * Les listes sont initialement tries par ordre alphabetique
    *
    ****************/

    T_Electeur elect=*E;
    T_Electeur elect_min, elect_tete=elect, elect_svg;
    int i=0,nbre_elec=comptelecteur(elect);

    *E=minimum(*E);
    while (i<nbre_elec-1) //-1 pour s arrter a l avant dernier (ca sert a rien de chercher le min dune liste de 1)
    {
        //On deroule a partir de elect_tete);

        //trouver minimum de la liste
        elect_min=minimum(elect_tete);


        //recrée les liens
        elect=elect_tete;
        if (elect_min!=elect_tete) //si il est mal place
        {
            //recherche du precedent de l electeur a deplace
            elect=precedent(elect, elect_min->cin_num);
            elect_svg=elect_min->suivant;
            //On lie preced avec suivant
            elect->suivant=elect_svg;

            //On met le minimum en tete de liste
            elect_min->suivant=elect_tete;
            elect_tete=elect_min;
        }
        //on refait la meme chose avec la liste sans le/les minimums ajoutes
        elect_tete=elect_tete->suivant;
        i++;
    }
}

T_Electeur fusionlistes(T_Electeur L1, T_Electeur L2)
{
    //fusionne la liste 1 et la liste 2
    //la tete de L2 sera le suivant de la queue de l1
    T_Electeur tete_l1=L1;
    if (L1==NULL && L2==NULL) return NULL;
    if (L1==NULL) return L2;
    if (L2==NULL) return L1;
    while (L1->suivant!=NULL)
    {
        L1=L1->suivant;
    }
    L1->suivant=L2;

    return tete_l1;
}

int compteGD(T_Electeur E)
{
    /*********************************
    * renvoie 0 si liste vide
    * renvoie nb electeur de la liste a avoir voté NOM1 ou NOM3
    ***********************************/
    int nbre_elec=0;
    if (E==NULL)return 0;
    while (E!=NULL)
    {
        if (E->choix==1 || E->choix==3)
        {
            nbre_elec+=1;
        }
        E=E->suivant;
    }
    return nbre_elec;
}

void libereliste(T_Electeur *E)
{
    //supprime tous les elements de la liste
    //libere l espace memoire
    T_Electeur elect=*E, elect_svg;

    if (elect==NULL)
    {
        printf("La liste est deja vide");
        return;
    }
    while (elect!=NULL)
    {
        elect_svg=elect->suivant;
        Supprimelecteur(E, elect->cin_num);
        //la fonction permet de libérer aussi l espace dans la memoire
        elect=elect_svg;
    }
    //free(E);
    return;
}





