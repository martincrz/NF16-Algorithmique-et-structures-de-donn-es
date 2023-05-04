#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include "header.h"

typedef struct t_Position
{
    int numero_ligne;
    int ordre;
    int numero_phrase;
    struct t_Position* suivant;
}t_Position;

typedef struct t_ListePositions
{
    t_Position* debut;
    int nb_elements;

}t_ListePositions; //représente la liste des positions d’un mot dans le texte

typedef struct t_noeud
{
    char* mot;
    int nb_occurences;
    t_ListePositions positions;
    struct t_noeud* filsGauche;
    struct t_noeud* filsDroit;

}t_Noeud;//représente un nœud de l’ABR

typedef struct Pmot //liste de mots (phrase)
{
    char* mot;
    struct Pmot* suivant;
}Pmot;

typedef struct Phrase
{
    int numero_phrase;
    Pmot* premier_mot;
    struct Phrase* phrase_suivante;
}Phrase;

typedef Phrase* t_Phrase;

typedef struct t_index
{
    t_Noeud* racine;
    t_Phrase liste_phrases;
    int nb_mots_differents;
    int nb_mots_total;
}t_Index; //représente l’ABR dans lequel sont stockés les mots


t_ListePositions* creer_liste_positions();
void afficheliste(t_ListePositions *p);
void ajoutertete(t_ListePositions *listeP, int ligne, int ordre, int num_phrase);
int ajouter_position(t_ListePositions *listeP, int ligne, int ordre, int num_phrase);

char* min(char* );
t_Index* creer_index();
t_Noeud* creer_noeud();
t_Noeud* rechercher_mot(t_Index *, char *);

int ajouter_noeud(t_Index*, t_Noeud*);
int indexer_fichier(t_Index *, char *);
void afficher_index(t_Index *);
int maximum(int, int );
int hauteur(t_Noeud *);
int estequilibre(t_Noeud *);

t_Noeud* trouver_max_apparition(t_Index *, t_Noeud* noeudmax);
void afficher_max_apparition (t_Index * index);


t_Phrase creer_phrase();
Pmot* creer_pmot();
void afficher_liste_phrase(t_Phrase phrase);
void ajouter_Pmot (t_Phrase phrase, char* str);
void ajouter_phrase(t_Phrase phrase);
void afficher_i_ligne(t_Phrase , int );

void afficher_occurences_mot(t_Index *, char *);
void construire_texte(t_Index *, char *);


#endif // HEADER_H_INCLUDED
