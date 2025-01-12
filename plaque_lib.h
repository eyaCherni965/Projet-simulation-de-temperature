
/*===========================================================*/
/*

 module :plaque_lib.h

 Par    :  Eya Cherni
/*=========================================================*/


#if !defined(PLAQUE)
#define PLAQUE 0

//librairies à inclure

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS 

//constantes

#define MAXLIG  40 //dimension maximale des lignes de la plaque 

#define MAXCOL  75  //dimension maximale des colonnes de la plaque 

#define MAXTEMP 500	 //la température absolue maximale permise 

#define MODE_4 4 //mode de calcul 4

#define MODE_8 8 //mode de calcul 8


typedef double t_matrice[MAXLIG][MAXCOL]; //type-tableau pour les 2 plaques

typedef int t_matbool[MAXLIG][MAXCOL]; //type-tableau pour les positions fixes

/***************************************************/
/*
Nom:moyenne_voisins

Paramètres:
- t_matrice: matrice des températures
-int y: type entier, coordonées de la position y dans
la matrice
- int x: type entier, coordonée de la position x dans
la matrice
- int mode: type entier, le mode de calcul choisi, soit
4, soit 8

Valeur de retour: la moyenne calculée
Méthode:
cette fonction fait le calcul de la nouvelle température
à la position y,x de la plaque qu'elle reçoit. Ce
calcul se fait sous forme de moyenne et ce, en fonction
du mode que l'utilisateur choisi. Le mode 4 signifie
que la moyenne se fait en additionnant les 4 voisins
(haut, bas, gauche, droite) et en divisant par 4,
alors que le mode 8 signifie que la moyenne se fait
en additionnant les 8 voisins(haut, bas, gauche, droite,
et les 4 valeurs en diagonales) puis en divisant par 8
*/
double moyenne_voisins(const t_matrice plaque, int y, int x, int mode);

/*
Nom: calculer_nouv_plaque

Paramètres:
- t_matrice plaque: matrice des températures actuelles
- t_matrice nouv_plaque: matrice des nouvelles températures
- t_matbool p_fixes: matrice des positions fixes
- int maxl: le nombre de lignes maximum
- int maxc: le nombre de colonnes maximum
- int mode: le mode de calcul voisin reçu
- double epsilon: la valeur choisie d'epsilon
- double coeff: la valeur choisie du coefficient

Valeur de retour:
equilibre, l'état d'équilibre, soit 1 ou  0

Méthode:
cette fonction permet de calculer chaque les nouvelles
températures pour chaque case de la plaque reçue pour ensuite
les inscrire dans la nouvelle plaque.Si la case correspond à
une position fixe, la valeur est copiée de la plaque. Si elle
n'est pas fixe, la nouvelle température est calculée grâce à
l'opération présente dans la fonction. Un calcul de différence
entre la nouvelle température est l'ancienne est ensuite faite
et si la valeur de la différence est plsu grande qu'epsilon, la
fonction retourne 0. Une fois qu'aucune différence n'indique 0,
la fonction renvoit 1, l'état d'équilibre est atteint*/

int calculer_nouv_plaque(const t_matrice plaque, t_matrice nouv_plaque,
	t_matbool p_fixes, int maxl, int maxc, int mode, double epsilon,
	double coeff);

/*
Nom:copier_nouv_plaque

Paramètres:
- t_matrice plaque: matrice des températures
- const t_matrice nouv_plaque: matrice des nouvelles
températures
- int dimy: dimensions y de la matrice
- int dimx: dimensions x de la matrice
- double*mint: pointeur vers la température minimale
- double*maxt: pointeur vers la température maximale

Valeur de retour:
la moyenne de la plaque

Méthode:
cette fonction transfert toutes les températures présentes
dans la nouvelle plaque vers la plaque officielle. Durant le
transfert, on mets encore à jour la température max et min et
on  accumule la sommes des températures pour pouvoir en faire
une moyenne
*/

double copier_nouv_plaque(t_matrice plaque, const t_matrice nouv_plaque,
	int maxl, int maxc, double* mint, double* maxt);

/*
Nom: lire_fichier

Paramètres:
 - FILE *fichier : pointeur vers le fichier à lire
 - t_matrice plaque : matrice des températures à remplir
 - t_matbool pos_fixes : matrice pour identifier les positions
 fixes (1 pour fixe, 0 sinon)
 - *dimy: dimensions de la matrice retournées
 par référence
 - *dimx : dimensions de la matrice retournées
 par référence
 - double *mint: températures minimale
 retournées par référence
 - double *maxt : températures minimale et maximale
 retournées par référence

Valeur de retour:
aucune

Méthode:
cette fonction reçoit le pointeur-fichier
de la fonction précedente et elle lit le fichier.
Elle vient ensuite remplir la matrice "plaque" avec
les températures reçues. Les dimensions de la matrice
sont ensuite mises à jour, et les températures min et
max également.Les températures en bordures de la
matrice sont considérées comme des position fixe, donc
de valeur 1, alors que les autres sont non-fixes, donc
de valeur 0.
*/

void  lire_fichier(FILE* fichier, t_matrice plaque, t_matbool pos_fixes,
	int* dimy, int* dimx, double* mint, double* maxt);

#endif 


