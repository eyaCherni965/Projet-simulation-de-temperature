/*===========================================================*/
/*

 module : affichage.h

 Par   Eya Cherni

/*=========================================================*/

#if !defined(AFFICHE)
#define AFFICHE 0 

#endif 


#define _CRT_SECURE_NO_WARNINGS   

//librairie usuelle à inclure
#include<stdio.h> 

#include<stdlib.h> 

#include<math.h> 

#include<assert.h> 

#include<conio.h>  

#include<ctype.h>

// Librairies usuelles à inclure  



/*=========================================================*/
//Librairie non usuelle 
 
#include "plaque_lib.h"

//constantes:

#define MAXLIG  40 //dimension maximale des lignes de la plaque 

#define MAXCOL  75  //dimension maximale des colonnes de la plaque 

#define MAXTEMP 500	 //la température absolue maximale permise 

#define NB_COUL 15   // nb de couleur de l`échelle  

#define POSYAFF 80  // position x pour début d`affichage  

#define MODE_4 4 //mode de calcul 4

#define MODE_8 8 //mode de calcul 8

#define AFFICHE 219 //code ASCII pour affichage de caractère plein

#define HAUT 72 //code ASCII pour flèche du haut

#define BAS 80 //code ASCII pour flèche du bas

#define GAUCHE 75 //code ASCII pour flèche gauche

#define DROIT 77 //code ASCII pour flèche droite

#define ENTREE 13 //code ASCII pour la touche entrée


//type-tableau pour les 2 plaques
typedef double t_matrice[MAXLIG][MAXCOL];

//type-tableau pour les positions fixes
typedef int t_matbool[MAXLIG][MAXCOL];

/*FFLUSH() : Cette constante empêche le programme de
planter si l'utilisateur rentre du texte.*/

#define FFLUSH()   while (getchar() != '\n') {} 

/************************************/

//fonctions:



FILE* lire_nom_fiche();


unsigned char afficher_menu(void);



void afficher_plaque(t_matrice plaque, int dimy, int dimx,
	double mint, double maxt);


void effacer_plaque(int nblig);



void dessiner_echelle(double mint, double maxt);



void aff_options(int mode, double epsi, double coeff_res);




void aff_minmax_moy(double mint, double maxt, double moyenne);



void aff_nb_iter(int nb_iter);


int  valider_mode_voisins();



double valider_reel(const char* message, double b_min, double b_max);


void initialiser_ecran();



void pt_variation(t_matrice plaque, t_matbool pos_fixes, int dimy, int dimx,
	double* mint, double* maxt, int fixe);






