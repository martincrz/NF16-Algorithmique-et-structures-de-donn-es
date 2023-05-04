#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <ctype.h>
#include "header.h"



t_ListePositions* creer_liste_positions()
{
    /*********************************************************
    Cette fonction crée une liste de positions, par une alloca
    -tion dynamique, et la retourne.
    *********************************************************/
    t_ListePositions* liste = malloc(sizeof(t_ListePositions));
    if (liste == NULL) return NULL; //si l'allocation n'a pas marché
    liste->debut = NULL;
    liste->nb_elements = 0;
    return liste;
}

void afficheliste(t_ListePositions *p)
{
    /*********************************************************
    Cette fonction affiche toutes les positions de la liste
    précédemment créée.
    *********************************************************/
    t_Position* position = p->debut;
    int i;
    if (position == NULL)//si la liste est vide
    {
        printf("Aucune position a afficher\n");
        return;
    }
    while (i<p->nb_elements)//parcourt tous les éléments de la liste
    {
        //afficheposition(position);
        printf("|----(l:%d, o:%d, p:%d)\n",position->numero_ligne,position->ordre,position->numero_phrase);
        position = position->suivant; //passe à l'element suivant
        i++; //incremente i
    }

    return;
}

void ajoutertete(t_ListePositions *listeP, int ligne, int ordre, int num_phrase)
{
    /*********************************************************
    Cette fonction ajoute une position en tête de liste.
    Dans le cadre du TP, elle n'est jamais appelée puisqu'au
    ajoute toujours en fin de liste.
    *********************************************************/
    t_Position* newposition = malloc(sizeof(t_Position*));
    newposition->numero_ligne = ligne;
    newposition->numero_phrase = num_phrase;
    newposition->ordre = ordre;
    newposition->suivant=listeP->debut;
    listeP->debut = newposition;
}

int ajouter_position(t_ListePositions *listeP, int ligne, int ordre, int num_phrase)
{
    /*********************************************************
    Cette fonction ajoute une position selon sa ligne et
    son ordre (placement du mot sur la ligne)
    Dans le cadre du TP, elle est simplificable en
    ajouter_fin_liste()
    Renvoie si l'ajout n'a pas abouti, 1 sinon.
    *********************************************************/
    t_Position* newposition = malloc(sizeof(t_Position));//on crée une position
    if (newposition==NULL) return 0; //si allocation ratée, on retourne 0

    //on attribue ses caractéristiques à la nouvelle position
    newposition->numero_ligne = ligne;
    newposition->numero_phrase = num_phrase;
    newposition->ordre = ordre;
    newposition->suivant = NULL;

    t_Position* position = listeP->debut;
    t_Position* prec = position;

    if (listeP->debut == NULL) //si la liste est vide
    {
        listeP->debut = newposition;
        listeP->nb_elements ++;
        return 1;
    }

    //CAS 1 : implémentation en tête de liste
    if (newposition->numero_ligne < listeP->debut->numero_ligne)
    {
        ajoutertete(listeP, ligne, ordre, num_phrase);
        //printf("test");
        listeP->nb_elements ++;
        return 1;
    }

    //CAS 2 : implémentation au sein de la liste
    //Dans ce cas, on parcourt tant que le numéro de ligne à ajouter est plus grand que celui de la position actuelle
    while (position!= NULL && newposition->numero_ligne > position->numero_ligne )
    {
        prec = position;
        position = position->suivant;
    }
    //position pointe donc sur la premiere position de la ligne suivante, et precedent sur le dernier element de la ligne où l'on veut insérer

    if (position == NULL)//AJouter en toute fin et première occurrence de la ligne
    {
        prec->suivant = newposition;
        //newposition->suivant = NULL; //deja dis
        listeP->nb_elements ++;
        return 1;
    }

    if (newposition->numero_ligne < position->numero_ligne) //cas où il n'y a aucune occurence sur cette ligne
    {
        prec->suivant = newposition;
        newposition->suivant = position;

        //printf("\nligne différente");
        listeP->nb_elements ++;
        return 1;
    }

//cas où il y a déjà des occurrences sur cette ligne :

    else if (newposition->numero_ligne == position->numero_ligne)
    {

        while (position->suivant != NULL  && position->numero_ligne == position->suivant->numero_ligne && newposition->ordre > position->ordre ) //on cherche l'ordre prec et suiv pour ajouter la nouvelle position
        {

            //printf("test");
            prec = position;
            position = position->suivant;
            //printf("%d",position->suivant->numero_ligne);


        }

        if (newposition->ordre < listeP->debut->ordre && newposition->numero_ligne == listeP->debut->numero_ligne)//implémentation en tête de liste
        {
            ajoutertete(listeP, ligne, ordre, num_phrase);
            //printf("test");
            listeP->nb_elements ++;
            return 1;
        }

        if (newposition->ordre < position->ordre && position->suivant == NULL)//cas implémentation au début d'un ordre
        {
            prec->suivant = newposition;
            newposition->suivant = position;
            listeP->nb_elements ++;
            return 1;
        }

        if (newposition->ordre > position->ordre && position->suivant != NULL) //cas d'implémentation à la fin d'un ordre
        {
            newposition->suivant = position->suivant;
            position->suivant = newposition;

            //printf("test");
            listeP->nb_elements ++;
            return 1;
        }


        if (newposition->ordre > position->ordre && position->suivant == NULL) //cas d'implémentation à la fin d'un ordre en fin de liste
        {
            position->suivant = newposition;
            newposition->suivant = NULL;
            //printf("test");
            listeP->nb_elements ++;
            return 1;
        }



        if (newposition->ordre == prec->ordre) return 0;


        prec->suivant = newposition;
        newposition->suivant = position;
        //printf("même ligne");
        listeP->nb_elements ++;
        return 1;

    }
    else return 0;

}


t_Index* creer_index()
{
    /*********************************************************
    Cette fonction crée un index , par une allocation dynamique,
    et le retourne.
    *********************************************************/
    t_Index* index = malloc(sizeof(t_Index));
    if (index == NULL) return NULL; //si allocation pas fonctionnée

    index->racine = NULL;
    index->liste_phrases=creer_phrase();
    index->nb_mots_differents = 0;
    index->nb_mots_total = 0;
    return index;
}

char* min(char* chaine)//met tout en minuscules
{
    /*********************************************************
    Cette fonction permet de renvoyer la chaine mis en
    parametre en minsucule.
    *********************************************************/
    char *str_l = calloc(strlen(chaine)+1, sizeof(char));

    for (size_t i = 0; i < strlen(chaine); ++i) { //on parcourt la chaine
        str_l[i] = tolower((unsigned char)chaine[i]); //met le caractere en min
    }
    return str_l;
}

t_Noeud* rechercher_mot(t_Index *index, char *mot)
{
    /*********************************************************
    Cette fonction fait une recherche d'un mot dans l'index.
    On part de la racine puis on se déplace à droite ou à
    gauche selon le mot en parametre jusqu'à tomber sur lui.
    Si on arrive sur une feuille sans être tombé sur le mot,
    c'est ce que le mot n'existe pas.
    On compare les mots sans prendre en compte leur majuscule :
    en mettant tout en minsucule.
    *********************************************************/
    t_Noeud* noeud = index->racine;
    if (noeud == NULL) return NULL;

    while (noeud->filsDroit != NULL || noeud->filsGauche != NULL) //tant que le noeud n est pas une feuille
    {
        if (strcmp(min(mot),min(noeud->mot))==0) //si c'est le mot recherché,
        {
            return noeud; //on le renvoie
        }

        if (strcmp(min(mot),min(noeud->mot))<0) //s'il est plus "grand"
        {
            if (noeud->filsGauche) noeud = noeud->filsGauche; //on pointe sur son fils gauche
            else {
                printf("Aucun noeud ne possede ce mot\n");
                return NULL;
                }
        }

        else if (strcmp(min(mot),min(noeud->mot))>0) //si le noeud est plus "petit" que le mot recherché
        {
            if (noeud->filsDroit) noeud = noeud->filsDroit; //on pointe sur son fils droit
            else {
                printf("Aucun noeud ne possede ce mot\n");
                return NULL;
                }
        }
    }
    if (strcmp(min(mot),min(noeud->mot))==0) {
            return noeud;
        } //cas mot = feuille
    return NULL;
}

t_Noeud* creer_noeud()
{
    /*********************************************************
    Cette fonction crée un noeud, par une allocation dynamique,
    et le retourne.
    *********************************************************/
    t_Noeud* noeud = malloc(sizeof(t_Noeud));
    if (noeud== NULL){return NULL;} //si allocation pas abouti

    noeud->mot=malloc(30*sizeof(char));
    //bzero(noeud->mot, 30*sizeof(char)); //cette fonction ne marche pas sur les ordinateurs de l'utc (pb resolu)
    noeud->positions=*creer_liste_positions();
    noeud->nb_occurences=1;
    noeud->filsDroit=NULL;
    noeud->filsGauche=NULL;

    return noeud;
}


int ajouter_noeud(t_Index *index, t_Noeud *noeud)
{
    /*********************************************************
    Cette fonction ajoute un noeud dans l'arbre de l'index.
    Elle l'ajoute selon sa clé : son mot.
    *********************************************************/

    //les commentaires en printf() ont été mis pour pouvoir plus facilement trouvé où ...
    //... étaient les sources d'erreurs, on les a gardé au cas où le programme revenait à planter

    t_Noeud* n = index->racine;

    //printf("On veut ajouter le mot %s \n\n", noeud->mot);


    if (n == NULL)
    {
        //printf("L'arbre est vide\n"); //a enlever
        index->racine = noeud;
        index->nb_mots_total+= noeud->nb_occurences;
        index->nb_mots_differents ++;
        //printf("La racine est maintenant %s\n", index->racine->mot);
        //printf("L arbre a %d noeuds\n\n", index->nb_mots_differents);
        return 1;
    }
    //printf("On repart de la racine %s  \n", index->racine->mot);
    while (n!=NULL)
    {
        //printf("On est a la position %s\n", n->mot);
        //printf("on compare %s et %s\n", noeud->mot,n->mot);
        if (strcmp(min(noeud->mot),min(n->mot))==0) //cas noeud déja présent => on ajoute simplement l'occurrence du nouveau noeud à l'ancien.
        {
            //printf("Un noeud au nom %s existe deja\n", n->mot);
            index->nb_mots_total++;
            n->nb_occurences++;
            //printf("On ajoute les positions du noeud a ajouter dans celui dans dans l'arbre\n\n");
            ajouter_position( &n->positions , noeud->positions.debut->numero_ligne, noeud->positions.debut->ordre, noeud->positions.debut->numero_phrase);
            return 1;
        }
        if (strcmp(min(noeud->mot),min(n->mot))<0) //si le mot du noeud à ajouté est plus petit
        {
            if (n->filsGauche)
            {
                //printf("On se deplace de %s vers %s (a gauche)\n", n->mot, n->filsGauche->mot);
                n = n->filsGauche; //si le noeud a un fils gauche, on descend à gauche dans l'arbre
            }
            else
            {
                //printf("On ajoute %s en tant que fils gauche de %s\n", noeud->mot, n->mot);
                n->filsGauche = noeud;  //sinon on ajoute le noeud en tant que fils gauche
                index->nb_mots_total+= noeud->nb_occurences;
                index->nb_mots_differents++;
                //printf("L'arbre a maintenant %d noeuds\n\n", index->nb_mots_differents);
                return 1;
            }
        }
        else if (strcmp(min(noeud->mot),min(n->mot))>0) //si le mot du noeud à ajouté est plus grand
        {
            if (n->filsDroit)
            {
                //printf("On se deplace de %s vers %s (a droite)\n", n->mot, n->filsDroit->mot);
                n = n->filsDroit; //si le noeud a un fils droit, on descend à droite dans l'arbre
            }
            else
            {
                //printf("On ajoute %s en tant que fils droit de %s\n", noeud->mot, n->mot);
                n->filsDroit = noeud;  //sinon on ajoute le noeud en tant que fils droit
                index->nb_mots_total+= noeud->nb_occurences;
                index->nb_mots_differents ++;
                //printf("L'arbre a maintenant %d noeuds\n\n", index->nb_mots_differents);
                return 1;
            }
        }
    }
    return 0;
}

int indexer_fichier(t_Index* index, char *filename)
{
    /*********************************************************
    Cette fonction indexe un fichier. Elle lit caractère par caractère jusqu'à tomber sur autre chose qu'une lettre.
    On considere que l'ensemble des caractères précédents forment un mot.
    Un noeud ayant pour clé ce mot est alors créé.
    On lui ajoute également sa position avec la fonction ajouter_position().
    A chaque fois qu'on lie apres un mot un caractere autre qu'une lettre, on passe à l'ordre suivant (placement sur la ligne),
    si '.' à la phrase suivant et si '\n' à la ligne suivante en remettant ordre à 0.
    On ajoute ensuite ce noeud dans l'arbre de l'index.

    Pour Q9 et Q10, nous ajoutons également ce mot dans la liste de mot de la liste de phrase.
    De meme, si on tombe sur le caractère '.', on passe à la phrase suivante.
    *********************************************************/



    FILE* fichier = fopen(filename, "r");
    if (fichier==NULL)
    {
        printf("Ce fichier n'existe pas\n");
        fclose(fichier);
        return 0;
    }

    int num_ligne= 1;
    int num_phrase=1;
    int num_ordre=1;
    int nbre_mots=0;

    t_Phrase phrase=index->liste_phrases;

    char c;
    int i=0;



    while((c=fgetc(fichier))!=EOF) //fgets
    {

        char *mot=malloc(30*sizeof(char));
        if (mot==NULL)
        {
            printf("Erreur");
            return 0;
        }


        //printf("Mot = %s\n", mot);

        while ((c>='A' && c<='Z') || (c>='a' && c<='z'))
        {
            if (c!=' ')
            {
                //printf("Caractere : %c \n", c);
                mot[i]=c;
                i++;
                c=fgetc(fichier);

            }
        }
        mot[i]='\0';


        //printf("\nOn ajoute le mot '%s' de position (%d,%d,%d) \n", mot, num_ligne, num_ordre, num_phrase);

        t_Noeud* nv_noeud=creer_noeud();
        strcpy(nv_noeud->mot,mot);
        //printf("On ajoute le mot a la liste de mot\n");
        ajouter_Pmot(phrase, mot); //pour q9_q10
        //printf("\n");

        ajouter_position(&nv_noeud->positions, num_ligne, num_ordre, num_phrase);
        ajouter_noeud(index,nv_noeud);




        nbre_mots++;
        num_ordre++;

        if (c==' ') //si espace ou virgule on passe au caractere suivant
        {
            //printf("espace \n");
            i=0;
        }

        if (c=='.') //si un point on passe au caractere suivant
        {
            //printf("point \n");
            c=fgetc(fichier);
            num_phrase++;

            ajouter_phrase(index->liste_phrases);
            phrase->phrase_suivante->numero_phrase=phrase->numero_phrase+1;

            phrase=phrase->phrase_suivante;
            i=0;
        }
        if (c==',')
        {
            //printf("virgule \n");
            c=fgetc(fichier);
            i=0;
        }

        if (c=='\n')
        {
            //printf("buffer \n");
            num_ligne++;
            num_ordre=1;
            i=0;
        }

    }

    printf("\nNombre de mots lus dans le fichier = %d\n", nbre_mots);
    fclose(fichier);
    return 0;
}

int maximum(int x, int y)
{
    /*********************************************************
    Fonction max() de base ; renvoie maximum entre 2 entiers
    *********************************************************/

    if (x>y) return x;
    if (y>x) return y;
    else return x;
}

int hauteur(t_Noeud *noeud)
{
    /*********************************************************
    Fonction qui renvoie la hauteur d'un arbre
    *********************************************************/
    t_Noeud* n = noeud;

    if (n==NULL)
    {
        return -1;
    }
    if (n->filsGauche==NULL && n->filsDroit==NULL)
    {
        return 0;
    }
    else
    {
        if (n->filsGauche==NULL) return (hauteur(n->filsDroit)+1);
        if (n->filsDroit==NULL ) return (hauteur(n->filsGauche)+1);
        return (maximum(hauteur(n->filsGauche), hauteur(n->filsDroit))+1 );
    }
}


int estequilibre(t_Noeud *noeud)
{
    /*********************************************************
    Fonction qui vérifie si un arbre est equilibre ou non
    *********************************************************/
    t_Noeud* n = noeud;
    while (n!=NULL)
    {
        int h_gauche=hauteur(n->filsGauche);
        //printf("Hauteur fils gauche %s : %d\n",n->filsGauche->mot, h_gauche);
        int h_droit=hauteur(n->filsDroit);
        //printf("Hauteur fils droit %s : %d\n" ,n->filsDroit->mot, h_droit);
        int equilibre= h_droit-h_gauche;

        if ((equilibre<=1) && (equilibre>=-1)) //equivalent, valeur absolue
        {
            if (estequilibre(n->filsGauche)==1 && estequilibre(n->filsDroit)==1) return 1;
        }
        else return 0;
    }
    return 1;
}

void afficher_index(t_Index *index)
{
    /*********************************************************
    Fonction qui affiche l'index
    *********************************************************/
    t_Noeud* r;
    r=index->racine;
    static char* abecedaire [32];


    if (r!=NULL)
    {

        if (r->filsGauche!=NULL)
        {
            afficher_index(&r->filsGauche);
        }

        if (strchr(abecedaire,toupper(r->mot[0])) == NULL) // recherche de la première lettre dans l'abecedaire
        {
            char lettre[2] = {toupper(r->mot[0]),'\0'};
            printf("\n\n%c", toupper(r->mot[0])); //si absente => on affiche la première lettre
            strcat(abecedaire,lettre); // on l'ajoute dans l'abecedaire
        }

        printf("\n|--%s\n", r->mot);
        afficheliste(&r->positions);
        printf("|");

        if (r->filsDroit!=NULL)
        {

            afficher_index(&r->filsDroit);

        }

    }
    return;
}

int max_app=0;
char* mot_max;

t_Noeud* trouver_max_apparition(t_Index *index, t_Noeud* noeudmax)
{
    /*********************************************************
    Fonction qui trouve le mot avec le maximum d'occurences
    *********************************************************/
    static int maximum;

    t_Noeud* r = index->racine;
    t_Noeud* max = noeudmax;

    if (r!=NULL)
    {

        if (r->filsGauche!=NULL)
        {
            trouver_max_apparition(&r->filsGauche, max);

        }

        if (r->nb_occurences > maximum)
        {
            maximum = r->nb_occurences;
            max = r;

        }

        if (r->filsDroit!=NULL)
        {

            trouver_max_apparition(&r->filsDroit, max);


        }

    }

    return max;
}

void afficher_max_apparition (t_Index * index)
{
    /*********************************************************
    Fonction qui l'affiche
    *********************************************************/

    t_Noeud* r = trouver_max_apparition(index, index->racine);
    printf("Le mot present le plus de fois dans le texte est \"%s\" avec %d occurences.\n",r->mot, r->nb_occurences);
/*
    //printf("tezst");
    if (r->nb_occurences == maximum)
    {
        printf("Le mot present le plus de fois dans le texte est \"%s\" avec %d occurences.\n",r->mot, r->nb_occurences);
        return;
    }
    if (r!=NULL)
    {
        if (r->filsGauche!=NULL)
        {
            afficher_max_apparition (&r->filsGauche, maximum);
        }

        if (r->filsDroit!=NULL)
        {

            afficher_max_apparition (&r->filsDroit, maximum);

        }

    }*/
    return;
}


t_Phrase creer_phrase() //cree une liste de phrase
{
    t_Phrase phrase=malloc(sizeof(Phrase));
    if (phrase==NULL) return NULL;

    phrase->numero_phrase = 1;
    phrase->premier_mot = NULL;
    phrase->phrase_suivante = NULL;
    return phrase;
}

Pmot* creer_pmot() //cree une liste de mot
{
    Pmot* pmot=malloc(sizeof(Pmot));
    if (pmot==NULL) return NULL;
    pmot->mot =malloc(30*sizeof(char));
    pmot->suivant = NULL;
    return pmot;
}

void afficher_liste_phrase(t_Phrase phrase) //affiche la liste de liste (mot par mot)
{
    t_Phrase p=phrase;
    if (p==NULL)
    {
        printf("Liste vide");
        return;
    }
    while (p!=NULL)
    {
        Pmot * mot=p->premier_mot;
        while (mot!=NULL)
        {
            printf("%s ", mot->mot);
            mot=mot->suivant;
        }
        printf(".\n"); //enelver le \n si on veut pas lire chaque phrase sur chaque ligne
        p=p->phrase_suivante;
    }
}

void ajouter_Pmot (t_Phrase phrase, char* str) //ajoute un mot
{
    //printf("On veut ajouter %s\n", str);
    Pmot* nv_mot=creer_pmot();
    nv_mot->mot=str;
    if (phrase->premier_mot == NULL)
    {
        //printf("La liste etait vide\n");
        phrase->premier_mot=nv_mot;
        return;
    }
    Pmot* m = phrase->premier_mot;
    while (m->suivant) m= m->suivant;
    m->suivant = nv_mot;
    return;

}


void ajouter_phrase(t_Phrase phrase) //ajoute un phrase
{
    Phrase* p = phrase;
    Phrase* new_phrase=creer_phrase();
    while (p->phrase_suivante) p = p->phrase_suivante;
    p->phrase_suivante=new_phrase;
    return;
}

void afficher_i_ligne(t_Phrase liste, int i) //affiche la i eme phrase
{
    while (liste->numero_phrase!=i)
    {
        liste=liste->phrase_suivante;
    }
    //une fois a la bonne ligne
    Pmot* pmot=liste->premier_mot;
    while (pmot!=NULL)
    {
        printf("%s ", pmot->mot);
        pmot=pmot->suivant;
    }
    printf("\n");
}

void afficher_occurences_mot(t_Index* index, char* mot) //affiche les positions et les phrases pour chaque occurence du mot souhaité
{

    t_Phrase liste_phrase=index->liste_phrases;

    int num_phrase=0;
    //pour trouver le nombre de phrases a afficher on cherche ses positions dans le texte
    t_Noeud* nd_recherche=rechercher_mot(index, mot);
    if (nd_recherche==NULL) return;


    t_Position* p=nd_recherche->positions.debut;


    printf("Mot = \"%s\" \nOccurences = %d\n", nd_recherche->mot, nd_recherche->nb_occurences);
    while (p!=NULL)
    {
        num_phrase=p->numero_phrase;
        printf("| Ligne %d, ordre %d : ", p->numero_ligne, p->ordre);
        afficher_i_ligne(index->liste_phrases, num_phrase);
        p=p->suivant;
    }

}

void construire_texte(t_Index* index, char *filename) //construit le texte dans un nouveau fichier et l'affiche
{
    t_Phrase liste_p=index->liste_phrases;
    printf("\n");
    //afficher_liste_phrase(index->liste_phrases);
    //printf("test, on veut creer %s\n", filename);
    FILE * fichier=fopen(filename, "w+");


    if (liste_p==NULL) return 0;
    else
    {
        while (liste_p!=NULL)
        {
            Pmot* mot=liste_p->premier_mot;
            while (mot!=NULL)
            {
                printf(" %s",mot->mot);
                fprintf(fichier," %s", mot->mot);
                mot=mot->suivant;
            }
        fprintf(fichier, ".\n");
        printf(".\n");
        liste_p=liste_p->phrase_suivante;
        }
        fclose(fichier);
        return 1;
    }
}



