
/*===========================================================*/
/*

 devoir : affichage.cpp

 Par    : Eya Cherni

/*=========================================================*/

#define _CRT_SECURE_NO_WARNINGS   

//librairies usuelles à inclure

#include <stdio.h>

#include<ctype.h> 

#include<assert.h>

//libraire non-usuelle

#include "WinConsole.h"

#include "affichage.h"

/*constantes pour les couleurs */
const int COULEURS[NB_COUL] = { RED, LIGHTRED, MAGENTA, LIGHTMAGENTA,
BLUE, LIGHTBLUE,CYAN, LIGHTCYAN, GREEN, LIGHTGREEN, DARKGRAY,
BROWN, YELLOW, LIGHTGRAY, WHITE };

/*=========================================================*/


static void colorer_pos(t_matrice plaque, int lig, int col,
	double mint, double maxt)
{
	double ecart = (maxt - mint) / NB_COUL; // Calcul de l’écart entre 
	//les niveaux de couleur  

	double temp = plaque[lig][col];      // Température au point (lig, col) 

	int coul = (temp - mint) / ecart;    // Calcul de l’index de couleur 

	//si l'index ne respecte pas les limites
	if (coul >= NB_COUL)
	{
		coul = NB_COUL - 1; // Assure que l’index est dans les limites  
	}

	textcolor(COULEURS[coul]); // Applique la couleur correspondante 

	gotoxy(col, lig);          // Positionne le curseur à (col, lig) 

	printf("%c", AFFICHE);      // Affiche un caractère plein pour la couleur 

}

/**********************************************/


static void colorer_curseur(t_matrice plaque, int lig, int col,
	double mint, double maxt)
{
	double ecart = (maxt - mint) / NB_COUL; // Calcul de l’écart de température 

	double temp = plaque[lig][col];    // Température à la position (lig, col) 

	int coul = (temp - mint) / ecart;   // Calcul de l’index de couleur 


	// Ajuste l'index de couleur pour qu'il soit dans les limites 

	if (coul < 0)
	{
		coul = 0;
	}

	else if (coul >= NB_COUL)
	{
		coul = NB_COUL - 1;
	}

	// Applique la couleur de fond pour le curseur 
	textbackground(COULEURS[coul]);

	gotoxy(col, lig);               // Positionne le curseur 

	printf("+");                    // Affiche le symbole du curseur 

}

/*************************************************************/

/*fonction qui vient demander le nom d'un fichier et vérifie
la validité ce de fichier afin de pouvoir l'ouvrir*/

FILE* lire_nom_fiche()

{
	FILE* fentree;


	// la variable nomfichier peut contenir un nom de fichier 
	// de 39 caractères maximum 

	char nomfichier[MAXLIG];

	//boucle do-while qui permet de vérifier la séléction du fichier
	do
	{
		gotoxy(POSYAFF, 14);
		printf("Tapez le nom du fichier : \n"); //utilisateur entre le nom
		//d'un fichier

		gotoxy(POSYAFF, 15);

		clreol();

		scanf("%s", nomfichier);  //on lit fichier donné 

		FFLUSH();

		fentree = fopen(nomfichier, "r"); //ouverture et lecture du fichier  

		if (fentree == NULL) //si le fichier est introuvable ou son nom
			//est mal écrit
		{
			gotoxy(POSYAFF, 16);

			printf("Votre fichier est introuvable\n");
		}

		//recommencer la saisie tant que le ptr peux pas ouvrir le fichier 
	} while (fentree == NULL);

	return fentree;
}

/***************************************************/

/*cette fonction sert à afficher un menu comportant
les différentes options que l'utilisateur peut choisir
(8 options)*/

unsigned char afficher_menu(void)
{
	unsigned char choix; //choix de l'utilisateur

	gotoxy(POSYAFF, 1); // Position du menu en haut à droite 

	// Affichage du menu 
	printf("======= Menu Principal =======\n");

	gotoxy(POSYAFF, 2);

	printf("1. (L)ire donnees initiales d'un fichier\n");

	gotoxy(POSYAFF, 3);

	printf("2. (M)ethode : 4 voisins ou 8 voisins\n");

	gotoxy(POSYAFF, 4);

	printf("3. Changer (E)psilon\n");

	gotoxy(POSYAFF, 5);

	printf("4. Changer (C)oefficient\n");

	gotoxy(POSYAFF, 6);

	printf("5. (V)ariation de temperature\n");

	gotoxy(POSYAFF, 7);

	printf("6. (F)ixer temperature\n");

	gotoxy(POSYAFF, 8);

	printf("7. (S)imulation\n");

	gotoxy(POSYAFF, 9);

	printf("8. (Q)uitter le programme\n");

	gotoxy(POSYAFF, 11);

	printf("Choisissez une option : \n");

	gotoxy(POSYAFF, 12);


	do {
		// Lit la touche de commande sans besoin d'appuyer sur Entrée 
		choix = _getch();

		// Convertit le choix en majuscule
		choix = toupper(choix);

		//tant que les choix correspondent aux suivants:
	} while (!(choix == 'L' || choix == 'M' || choix == 'E' ||
		choix == 'C' || choix == 'V' || choix == 'F' ||
		choix == 'S' || choix == 'Q' || (choix >= '1' && choix <= '8')));

	printf("choix-->: %c\n", choix); // Affiche le choix pour confirmation  

	//on retourne le choix de l'utilisateur
	return choix;
}

/*=========================================================*/

/*cette fonction s'occupe d'afficher tout les points de
la plaque reçue*/

void afficher_plaque(t_matrice plaque, int dimy, int dimx,
	double mint, double maxt)
{
	double ecart;  // ecart de température  

	double temp;  // température de cahque point de la plaque  

	int coul;    // index de couleur pour température  

	int y; //position lignes 

	int x; //position colonnes  

	ecart = (maxt - mint) / NB_COUL; //pour déterminer la valeur de l'écart

	//2 boucles for pour aller jusqu'aux dimensions max
	//de la matrice
	for (y = 0; y < dimy; y++)
	{
		for (x = 0; x < dimx; x++)
		{
			// Appel de la nouvelle fonction pour chaque position
			colorer_pos(plaque, y, x, mint, maxt);
		}
	}
	// Réinitialise la couleur par défaut après l'affichage 
	textcolor(WHITE);
}

/*=========================================================*/

/*cette fonction permet d'effacer la plaque qui pourrait
être affichée dans le cas où l'utilisateur décide de
rentrer le nom d'un nouveau fichier*/

void effacer_plaque(int nblig)
{
	int ligne; //le nombre de ligne de la matrice
	int colonne; //le nombre de colonne de la matrice

	textcolor(BLACK); //la couleur devient noire

	//2 boucles for pour inclure l'entièreté
	//des dimensions de la matrice
	for (ligne = 0; ligne < MAXLIG; ligne++)
	{
		for (colonne = 0; colonne < MAXCOL; colonne++)
		{

			gotoxy(colonne, ligne);
			printf("%c", AFFICHE); //on imprime une case noire
		}
	}

	//on remet la couleur en blanc
	textcolor(WHITE);
}

/*=========================================================*/

/*cette fonction sert à afficher l'échelle des 15 couleurs
qu'il est possible de retrouver et ce, à la droite de la
plaque. L'échelle est divisée en 15 parties et chacune
comprend un intervalle [min.max]*/

void dessiner_echelle(double mint, double maxt)
{
	double ecart;  // ecart de température  

	int coul;    // index de couleur pour température   

	double tempmin; //valeur température min affiché  

	double tempmax;  //valeur température max affiché  

	ecart = (maxt - mint) / NB_COUL; //pour déterminer la valeur de l'écart

	//on va à cette position
	gotoxy(POSYAFF, 23);

	//ce message s'affiche
	printf("Echelle des temperatures :\n");

	//boucle for pour inclure toutes les dimensions de
	//la matrice
	for (coul = 0; coul < NB_COUL; coul++)
	{
		gotoxy(POSYAFF, 24 + coul);

		//pour trouver intervalle min de temp.
		tempmin = mint + coul * ecart;

		//pour trouver intervalle max de temp.
		tempmax = mint + (coul + 1) * ecart;

		//si la couleur correspond au nombre de couleur max
		if (coul == NB_COUL) {

			//couleur est réinitialisé à:
			coul = NB_COUL - 1;
		}

		//le texte s'affiche à la couleur attitrée
		textcolor(COULEURS[coul]);

		printf("%c%c%c ", AFFICHE, AFFICHE, AFFICHE);

		//on remet la couleur à blanc
		textcolor(WHITE);

		printf("%.2lf - %.2lf\n", tempmin, tempmax);
	}
}


/*=========================================================*/

/*cette fonciton permet d'afficher un bloc de message qui
permet à l'utilisateur de visualiser lses différents choix
de valeur concernant le mode, epsilon et le coefficient
de résistance*/

void aff_options(int mode, double epsi, double coeff_res)
{

	gotoxy(POSYAFF, 19);  //a droite , en dessous du menu  

	// Affichage du mode choisi

	printf("Methode de calcul : %d voisins\n", mode);

	gotoxy(POSYAFF, 20);

	// Affichage de la tolérance epsilon choisi

	printf("Tolerance epsilon : %.2f\n", epsi);

	gotoxy(POSYAFF, 21);

	// Affichage du coefficient de résistance choisi

	printf("Coefficient de resistance : %.2f\n", coeff_res);

}

/*=========================================================*/

/*cette fonction permet d'afficher un bloc de message qui
indique la temérature minimale, maximale ainsi que la
température moyenne*/

void aff_minmax_moy(double mint, double maxt, double moyenne)
{

	gotoxy(POSYAFF, 40);  // a droite, en dessous echelle couleur  

	// Affichage des valeurs de mint, maxt et moyenne

	printf("Min: %.2f\n", mint);

	gotoxy(POSYAFF, 41);

	printf("Max: %.2f\n", maxt);

	gotoxy(POSYAFF, 42);

	printf("Moyenne: %.2f\n", moyenne);

}

/*=========================================================*/

/*cette fonction permet d'afficher le nombre d'itérations
néecessaires pour compléter la simulation*/

void aff_nb_iter(int nb_iter)

{
	gotoxy(POSYAFF, 22);  // meme endroit que mode epsilon coeff_res 

	//on imprime le nombre d'itérations effectuées
	printf("Nb d'iterations : %d\n", nb_iter);

}

/*=========================================================*/

/*cette fonction permet de limiter et de valider
les choix possibles de  l'utilisateur en ce qui concerne
le mode à choisir (soit 4, soit 8)*/

int  valider_mode_voisins()
{
	int mode;     //mode 4 ou 8 voisins  


	gotoxy(POSYAFF, 16); //au meme endroit que mode,epsilon,coeff_res 

	printf("Choisissez un mode voisin (4 ou 8) : ");

	gotoxy(POSYAFF, 17);

	scanf("%d", &mode);

	//pour pouvoir effacer le message précedemment affiché 
	gotoxy(POSYAFF, 16);

	printf("                                                            ");

	//pour pouvoir effacer la valeur précedemment rentrée
	gotoxy(POSYAFF, 17);
	printf("             ");

	FFLUSH();


	//tant que mode n`est pas 4 et 8 
	while (mode != MODE_4 && mode != MODE_8)
	{
		gotoxy(POSYAFF, 16); //au meme endroit que mode,epsilon,coeff_res 

		printf("Erreur : veuillez entrer 4 ou 8.");

		scanf("%d", &mode);

		//pour pouvoir effacer le message précedemment affiché 
		gotoxy(POSYAFF, 16);

		printf("                                                        ");

		//pour pouvoir effacer la valeur précedemment rentrée
		gotoxy(POSYAFF, 17);
		printf("             ");

		FFLUSH();

	}

	//on retourne le mode choisi
	return mode;
}

/*=========================================================*/

/*cette fonction permet de limiter et de valider le choix
de valeur de l'utilisateur en ce qui concerne epsilon et
le coefficient de résistance*/

double valider_reel(const char* message, double b_min, double b_max)
{
	double valeur; //valeur choisie par l'utilisateur

	gotoxy(POSYAFF, 16);

	printf("%s (entre %.2lf et %.2lf):", message, b_min, b_max);

	gotoxy(POSYAFF, 17); //meme endroit que mode,epsilon,coeff_ress 

	scanf("%lf", &valeur);

	//pour pouvoir effacer le message précedemment affiché 
	gotoxy(POSYAFF, 16);

	printf("                                                            ");

	//pour pouvoir effacer la valeur précedemment rentrée
	gotoxy(POSYAFF, 17);

	printf("             ");

	FFLUSH();

	//boucle do-while pour choisir des valeurs qui respectent les marges
	while ((valeur < b_min) || (valeur > b_max))
	{
		gotoxy(POSYAFF, 16);  //meme endroit que mode,epsilon,coeff_ress 

		printf("Erreur, tappez de nouveau.\n",
			b_min, b_max);

		gotoxy(POSYAFF, 17); //meme endroit que mode,epsilon,coeff_ress 

		scanf("%lf", &valeur);

		//pour pouvoir effacer le message précedemment affiché 
		gotoxy(POSYAFF, 16);

		printf("                                                              ");

		//pour pouvoir effacer la valeur précedemment rentrée
		gotoxy(POSYAFF, 17);
		printf("             ");

		FFLUSH();
	}

	//on retourne la valeur choisie
	return valeur;
}

/***************************************************************/

/*Cette fonction permet de déplacer un curseur représenté
par un + sur la plaque de températures et de modifier la
température à une position sélectionnée par l'utilisateur*/

void pt_variation(t_matrice plaque, t_matbool pos_fixes, int dimy, int dimx,
	double* mint, double* maxt, int fixe)
{
	int posx = dimx / 2; // Position initiale (centrale) 

	int posy = dimy / 2; // Position initiale (centrale) 

	double temp;         // Température pour cette position 

	int ecart;          // Écart de température 

	int coul;           // Index de couleur 

	int touche;         // Touche sélectionnée  

	//on colore le curseur grâce à la fonction colorer_curseur
	colorer_curseur(plaque, posy, posx, *mint, *maxt);

	// Boucle pour déplacer le curseur 
	do {
		touche = _getch();

		/// Effacer le curseur à la position actuelle 

		colorer_curseur(plaque, posy, posx, *mint, *maxt);

		gotoxy(posx, posy);

		printf(" "); // Effacer le curseur 

		if (touche == 0 || touche == 224)

			touche = _getch();

		// Déplacer le curseur en fonction de la touche pressée 

		switch (touche) {

		case HAUT:  // Flèche haut 

			// on s`assure de pas descendre en dehors de la matrice (ligne 0)
			if (posy > 0)

				posy--; //sinon on décrémente posy

			break;

		case BAS:  // Flèche bas 

			//on s`assure qu`on dépasse pas la matrice.
			if (posy < dimy - 1)

				posy++; //sinon on incrémente posy

			break;

		case GAUCHE:  // Flèche gauche 

			//on s`assure qu`on dépasse pas la matrice.
			if (posx > 0)

				posx--; //sinon on décrémente posx

			break;

		case DROIT:  // Flèche droite 

			//on s`assure qu`on dépasse pas la matrice.
			if (posx < dimx - 1)

				posx++; //sinon on incrémente posx

			break;

		}

		colorer_curseur(plaque, posy, posx, *mint, *maxt);

		//tant que l'utilisateur ne choisi pas la touche ENTRÉE
	} while (!(touche == ENTREE));

	//la couleur devient noire
	textbackground(BLACK);

	//choix de la température
	temp = valider_reel("Entrez une temperature ", -MAXTEMP, MAXTEMP);

	// Mettre à jour la plaque avec la nouvelle température 
	plaque[posy][posx] = temp;

	// Mettre à jour mint et maxt  
	if (temp < *mint) 		*mint = temp;

	if (temp > *maxt)		*maxt = temp;

	// Mettre à jour le tableau des positions fixes 
	if (fixe == 1)
	{
		pos_fixes[posy][posx] = 1; // Marquer comme position fixe 
	}

	else
	{
		pos_fixes[posy][posx] = 0; // Marquer comme position variable 
	}

	// Afficher la nouvelle plaque avec la température mise à jour 

	afficher_plaque(plaque, dimy, dimx, *mint, *maxt);

}

/*****************************************/

/*Cette fonction permet d'initialiser l'écran
au mode text 55*/

void initialiser_ecran()
{

	textmode(55);
}
