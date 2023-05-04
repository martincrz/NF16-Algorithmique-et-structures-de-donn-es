#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#define taille_nom_max 15


typedef struct electeur
{
    char nom[taille_nom_max];
    long cin_num;
    int choix;
    struct electeur *suivant;
}electeur;

typedef electeur* T_Electeur;

T_Electeur creationelecteur(void);
int nombreChiffres ( int  );
void afficheliste(T_Electeur);
T_Electeur ajoutentete(T_Electeur, char[taille_nom_max], long , int );
T_Electeur precedent(T_Electeur , long );
void ajoutelecteur(T_Electeur*,char[taille_nom_max],long,int);
int comptelecteur(T_Electeur);
int trouvelecteur(T_Electeur, long);
void affiche_donnees(T_Electeur, long );
void Supprimelecteur(T_Electeur*,long );
void decoupeliste(T_Electeur,T_Electeur *,T_Electeur *,T_Electeur*);
T_Electeur minimum(T_Electeur );
void triliste(T_Electeur*);
T_Electeur fusionlistes(T_Electeur, T_Electeur);
int compteGD(T_Electeur);
void libereliste(T_Electeur*);



#endif // HEADER_H_INCLUDED
