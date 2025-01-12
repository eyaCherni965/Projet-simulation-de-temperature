
/*===========================================================*/
/*

fichier : plaque_lib.cpp

 Par    : Eya Cherni

/*=========================================================*/

#define _CRT_SECURE_NO_WARNINGS

//librairie usuelle à inclure


#include "affichage.h" 
#include <stdio.h>

/*fonction qui reçoit le pointeur fichier de la fonction
précedente et qui vient remplir la plaque reçue avec les
données de ce fichier*/

void  lire_fichier(FILE* fichier, t_matrice plaque, t_matbool pos_fixes,
	int* dimy, int* dimx, double* mint, double* maxt)

{
	int colonnes; //le nombre de colonne de la matrice

	int lignes; //le nombre de ligne de la matrice

	*maxt = -MAXTEMP; //pointeur vers la température minimale

	*mint = MAXTEMP; //pointeur vers la température maximale

	//on commence par effacer la plaque au cas où une
	//serait déjà affichée
	effacer_plaque(*dimx);

	//on fait la lecture des dimensions de la plaque
	fscanf(fichier, " %d %d", dimy, dimx);

	//boucle for pour pouvoir redéfinir les températures
	//min et max et pour pouvoir établir les positions fixes et
	//non-fixes
	for (lignes = 0; lignes < *dimy; ++lignes)
		for (colonnes = 0; colonnes < *dimx; ++colonnes)
		{
			fscanf(fichier, "%lf", &plaque[lignes][colonnes]);

			//si on trouve une température plus basse
			if (plaque[lignes][colonnes] < *mint)
			{
				*mint = plaque[lignes][colonnes];
			}

			//si on trouve une température plus haute
			if (plaque[lignes][colonnes] > *maxt)
			{
				*maxt = plaque[lignes][colonnes];
			}

			// Déterminer les positions fixes 
			if ((lignes == 0) || (lignes == *dimy - 1) ||
				(colonnes == 0) || (colonnes == *dimx - 1))
			{

				pos_fixes[lignes][colonnes] = 1; // Positions fixes 
			}

			else
				pos_fixes[lignes][colonnes] = 0; // Positions non fixes 
		}

	fclose(fichier); // Fermer le fichier à la fin de la lecture 

}

/************************************************/

/*Cette fonction fait le calcul de la nouvelle température à
la position [y, x] reçue de la plaque reçue. Le mode 4 ou 8
indique comment le calcul doit être effectué*/

double moyenne_voisins(const t_matrice plaque, int y, int x, int mode)

{

	int moyenne; //stock moyenne des 4 ou 8 voisins 

	switch (mode)

	{

	case MODE_4:

		moyenne = plaque[y + 1][x] + plaque[y - 1]
			[x] + plaque[y][x + 1] + plaque[y][x - 1];

		moyenne /= MODE_4;

		break;

	case MODE_8:

		moyenne = (plaque[y + 1][x] + plaque[y - 1][x] + plaque[y]
			[x + 1] + plaque[y][x - 1] + plaque[y + 1][x + 1]
			+ plaque[y + 1][x - 1] + plaque[y - 1][x + 1]
			+ plaque[y - 1][x - 1]);

		moyenne /= MODE_8;
	}

	return moyenne;
}

/**********************************************************************/

/*Cette fonction a la tâche de calculer toutes les températures
de l’étât suivant de la plaque dans la nouvelle plaque. Le calcul
dépendra de si la position de la case est une position fixe ou pas.*/

int calculer_nouv_plaque(const t_matrice plaque, t_matrice nouv_plaque,
	t_matbool p_fixes, int maxl, int maxc, int mode, double epsilon,
	double coeff)

{
	//ligne des plaques 

	int lignes;

	//colonnes des plaques 
	int colonnes;

	//état de l`équilibre initialisé a 1 (équilibre atteint)  
	int equilibre = 1;

	for (lignes = 0; lignes < maxl; lignes++)
	{
		for (colonnes = 0; colonnes < maxc; colonnes++)
		{
			if (p_fixes[lignes][colonnes] == 0) // position non fixes 

			{
				//calule nouvelle tempé.
				nouv_plaque[lignes][colonnes] = (plaque[lignes][colonnes] *
					coeff) + ((moyenne_voisins(plaque, lignes, colonnes, mode)
						* (1.0 - coeff)));
			}

			else
			{
				// si position fixe 
				nouv_plaque[lignes][colonnes] = plaque[lignes][colonnes];
			}

			// vérifie si équilibre est atteint  
			//utilisation de fabs pour valeur absolu 
			if (fabs(plaque[lignes][colonnes] -
				nouv_plaque[lignes][colonnes]) > epsilon)

				equilibre = 0;  // équilibre non-atteint  
		}
	}
	return equilibre;
}


/*=========================================================*/

/*cette fonction fait le transfert de toutes les nouvelles
températures inscrites dans la nouvelle plaque vers la plaque
officielle*/

double copier_nouv_plaque(t_matrice plaque, const t_matrice nouv_plaque,
	int dimy, int dimx, double* mint, double* maxt)
{
	int lignes; //ligne des plaques

	int colonnes; //colonnes des plaques

	double moyenne = 0.0; //moyenne de la plaque 

	*maxt = -MAXTEMP; //pointeur vers la température minimale

	*mint = MAXTEMP; //pointeur vers la température maximale

	// transfert  nouvelles températures nouv_plaque --> plaque .   

	for (lignes = 0; lignes < dimy; lignes++)
	{
		for (colonnes = 0; colonnes < dimx; colonnes++)
		{
			//la plaque devient égale à la nouvelle plaque
			plaque[lignes][colonnes] = nouv_plaque[lignes][colonnes];

			//on fait la moyenne de la plaaue
			moyenne += plaque[lignes][colonnes];

			//trouve la plus petite & grande température 

			//si on trouve une température plus basse
			if (plaque[lignes][colonnes] < *mint)

				//c'est elle qui devient mint
				*mint = plaque[lignes][colonnes];

			//si on trouve une température plus haute
			if (plaque[lignes][colonnes] > *maxt)

				//c'est elle qui devient maxt
				*maxt = plaque[lignes][colonnes];
		}
	}
	//on retourne la valeur de la moyenne
	return moyenne / (dimy * dimx);
}