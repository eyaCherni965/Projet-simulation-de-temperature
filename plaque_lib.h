
/*===========================================================*/
/*

 module :plaque_lib.h

 Par    :  Eya Cherni
/*=========================================================*/


#if !defined(PLAQUE)
#define PLAQUE 0

//librairies � inclure

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS 

//constantes

#define MAXLIG  40 //dimension maximale des lignes de la plaque 

#define MAXCOL  75  //dimension maximale des colonnes de la plaque 

#define MAXTEMP 500	 //la temp�rature absolue maximale permise 

#define MODE_4 4 //mode de calcul 4

#define MODE_8 8 //mode de calcul 8


typedef double t_matrice[MAXLIG][MAXCOL]; //type-tableau pour les 2 plaques

typedef int t_matbool[MAXLIG][MAXCOL]; //type-tableau pour les positions fixes

/***************************************************/
/*
Nom:moyenne_voisins

Param�tres:
- t_matrice: matrice des temp�ratures
-int y: type entier, coordon�es de la position y dans
la matrice
- int x: type entier, coordon�e de la position x dans
la matrice
- int mode: type entier, le mode de calcul choisi, soit
4, soit 8

Valeur de retour: la moyenne calcul�e
M�thode:
cette fonction fait le calcul de la nouvelle temp�rature
� la position y,x de la plaque qu'elle re�oit. Ce
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

Param�tres:
- t_matrice plaque: matrice des temp�ratures actuelles
- t_matrice nouv_plaque: matrice des nouvelles temp�ratures
- t_matbool p_fixes: matrice des positions fixes
- int maxl: le nombre de lignes maximum
- int maxc: le nombre de colonnes maximum
- int mode: le mode de calcul voisin re�u
- double epsilon: la valeur choisie d'epsilon
- double coeff: la valeur choisie du coefficient

Valeur de retour:
equilibre, l'�tat d'�quilibre, soit 1 ou  0

M�thode:
cette fonction permet de calculer chaque les nouvelles
temp�ratures pour chaque case de la plaque re�ue pour ensuite
les inscrire dans la nouvelle plaque.Si la case correspond �
une position fixe, la valeur est copi�e de la plaque. Si elle
n'est pas fixe, la nouvelle temp�rature est calcul�e gr�ce �
l'op�ration pr�sente dans la fonction. Un calcul de diff�rence
entre la nouvelle temp�rature est l'ancienne est ensuite faite
et si la valeur de la diff�rence est plsu grande qu'epsilon, la
fonction retourne 0. Une fois qu'aucune diff�rence n'indique 0,
la fonction renvoit 1, l'�tat d'�quilibre est atteint*/

int calculer_nouv_plaque(const t_matrice plaque, t_matrice nouv_plaque,
	t_matbool p_fixes, int maxl, int maxc, int mode, double epsilon,
	double coeff);

/*
Nom:copier_nouv_plaque

Param�tres:
- t_matrice plaque: matrice des temp�ratures
- const t_matrice nouv_plaque: matrice des nouvelles
temp�ratures
- int dimy: dimensions y de la matrice
- int dimx: dimensions x de la matrice
- double*mint: pointeur vers la temp�rature minimale
- double*maxt: pointeur vers la temp�rature maximale

Valeur de retour:
la moyenne de la plaque

M�thode:
cette fonction transfert toutes les temp�ratures pr�sentes
dans la nouvelle plaque vers la plaque officielle. Durant le
transfert, on mets encore � jour la temp�rature max et min et
on  accumule la sommes des temp�ratures pour pouvoir en faire
une moyenne
*/

double copier_nouv_plaque(t_matrice plaque, const t_matrice nouv_plaque,
	int maxl, int maxc, double* mint, double* maxt);

/*
Nom: lire_fichier

Param�tres:
 - FILE *fichier : pointeur vers le fichier � lire
 - t_matrice plaque : matrice des temp�ratures � remplir
 - t_matbool pos_fixes : matrice pour identifier les positions
 fixes (1 pour fixe, 0 sinon)
 - *dimy: dimensions de la matrice retourn�es
 par r�f�rence
 - *dimx : dimensions de la matrice retourn�es
 par r�f�rence
 - double *mint: temp�ratures minimale
 retourn�es par r�f�rence
 - double *maxt : temp�ratures minimale et maximale
 retourn�es par r�f�rence

Valeur de retour:
aucune

M�thode:
cette fonction re�oit le pointeur-fichier
de la fonction pr�cedente et elle lit le fichier.
Elle vient ensuite remplir la matrice "plaque" avec
les temp�ratures re�ues. Les dimensions de la matrice
sont ensuite mises � jour, et les temp�ratures min et
max �galement.Les temp�ratures en bordures de la
matrice sont consid�r�es comme des position fixe, donc
de valeur 1, alors que les autres sont non-fixes, donc
de valeur 0.
*/

void  lire_fichier(FILE* fichier, t_matrice plaque, t_matbool pos_fixes,
	int* dimy, int* dimx, double* mint, double* maxt);

#endif 


