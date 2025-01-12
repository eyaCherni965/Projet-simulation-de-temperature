
/*===========================================================*/
/*
Fichier principale: D�velopp� un programme en C pour simuler la 
distribution de temp�rature sur une plaque 
m�tallique � l�aide de m�thodes thermiques avanc�es.

 Par    :Eya Cherni

/*=========================================================*/

#define _CRT_SECURE_NO_WARNINGS  

// Librairies usuelles � inclure  

#include<stdio.h> 

#include<stdlib.h> 

#include<math.h> 

#include<assert.h> 

#include<conio.h>  

#include<ctype.h>  

/*=========================================================*/


#include "affichage.h"
/*=========================================================*/

/*                  LES CONSTANTES                         */

/*=========================================================*/
#define MAXLIG  40 //dimension maximale des lignes de la plaque 

#define MAXCOL  75  //dimension maximale des colonnes de la plaque 

#define MAXTEMP 500	 //la temp�rature absolue maximale permise 

#define MIN_EPS 0.01  //valeur minimale d'epsilon

#define MAX_ESP 10.0  //valeur maximale d'epsilon

#define MIN_COEF 0.20  //valeur minimale du coefficient

#define MAX_COEF 0.80  //valeur maximale du coefficient

#define POSYAFF 80  // position x pour d�but d`affichage  


/*=========================================================*/

int simulation(t_matrice plaque, t_matbool pos_fixes, int dimy, int dimx,
	double* mint, double* maxt, int mode, double epsilon, double coeff);

//Programme principal: 

void main(void)

{

	FILE* fichier;    // Pointeur pour le fichier de donn�es 

	double epsilon = 5.0;  // Tol�rance pour l'�quilibre thermique 

	int dimy;           // les dimensions y de la matrice

	int dimx;                    // les dimensions x de la plaque 

	double mint;                     // Temp�rature minimale 

	double maxt;                      // Temp�rature maximale  

	double coeff_res = 0.5;  // Coefficient de r�sistance � la transmission 

	int mode = 4;         //mode choisi, 4 par d�faut mais peut �tre modifi�

	int iteration;

	t_matrice plaque;            // Matrice pour les temp�ratures de la plaque 

	t_matrice nouv_plaque;         // Matrice pour les nouvelles 
	//temp�ratures calcul�es 

	t_matbool pos_fixes;        // Matrice pour indiquer les positions fixes 

	int init = 0;              // Indicateur si les donn�es ont �t� charg�es 

	unsigned char choix;               // Choix du menu par l'utilisateur 

	initialiser_ecran();


	/*boucle do-while pour permettre d'afficher et
	 d'executer les diff�rentes options du menu*/

	do {
		choix = afficher_menu();

		switch (choix)
		{

		case 'L': case '1':  //si l'option L ou 1 est choisi, on fait la
			//s�l�ction et la lecture du fichier

			fichier = lire_nom_fiche();

			lire_fichier(fichier, plaque, pos_fixes, &dimy,
				&dimx, &mint, &maxt);

			afficher_plaque(plaque, dimy, dimx, mint, maxt);


			dessiner_echelle(mint, maxt);

			aff_options(mode, epsilon, coeff_res);

			init = 1; //init devient �gal � 1 pour permettre l'execution des 
			//options 5,6,7
			break;


		case 'M':  case '2': //si l'option 2 ou M est choisie, on choisi
			//la valeur du mode voisin, 4 ou 8

			mode = valider_mode_voisins();

			aff_options(mode, epsilon, coeff_res);

			break;

		case 'E':  case '3': //si l'option 3 ou E est choisie, on choisi
			//la valeur d'epsilon selon les marges limites

			epsilon = valider_reel("Entrez un epsilon ", MIN_EPS, MAX_ESP);

			aff_options(mode, epsilon, coeff_res);

			break;

		case 'C':  case '4':  //si l'option 4 ou C est choisie, on choisi
			//la valeur du coefficient en fonciton des
		   //marges limites 

			coeff_res = valider_reel("Entrez un coefficent",
				MIN_COEF, MAX_COEF);

			aff_options(mode, epsilon, coeff_res);

			break;

		case 'S':  case '7'://si l'option 7 ou S est choisie et que la
			//lecture du fichier est faite correctement,
			 //on execute la simulation

			if (init)
			{
				// Si les donn�es ont d�j� �t� initialis�es, lance la simulation 
				iteration = simulation(plaque, pos_fixes, dimy, dimx, &mint, &maxt,
					mode, epsilon, coeff_res);

				aff_nb_iter(iteration);

			}
			break;

		case 'V':  case '5':  //si l'option 5 ou V est choisie, et que la
			//lecture du fichier s'est faite correctement
			//on peut effectuer les variations de temp�rature

			if (init)
			{
				pt_variation(plaque, pos_fixes, dimy, dimx, &mint, &maxt, 0);
			}
			break;

		case 'F':  case '6': //si l'option 6 ou F est choisie et que la
			//lecture du fichier s'est faite correctement,
			 //on peut executer l'option de fixer une temp�rature
			if (init)
			{
				pt_variation(plaque, pos_fixes, dimy, dimx, &mint, &maxt, 1);
			}
			break;

		case 'Q':  case '8': //si l'option 8 ou Q est choisie, 
			break;           //le programme s'arr�te

		}

		//les conditions pour la continuit� de la boucle
		//tant que Q ou 8 n'est pas choisi
	} while ((choix != 'Q') && (choix != '8'));

	system("pause");
}

/*=========================================================*/


/*algorithme principal de la simulation qui vient afficher
la plaque et l'�chelle actuelle, calcul les valeurs suivantes
de la temp�rature en fonction du mode re�u et vient copier
ces valeurs l� dans la plaque actuelle.La fonction incr�mente
le compteur d'it�rations et affiche le mint, maxt et la
temp�rature moyenne*/

int simulation(t_matrice plaque, t_matbool pos_fixes, int dimy, int dimx,
	double* mint, double* maxt, int mode, double epsilon, double coeff)
{

	double moyenne = 0.0; //moyenne de la plaque

	t_matrice nouv_plaque; // recoit nouvelles valeur de chaque it�rations

	int iteration = 0; //le nombre d`iteration effectu�

	int equilibre = 0; //�tat de l`�quilibre

	//boucle do-while pour effectuer la simulation
	do
	{
		//calcule nouvelle plaque 

		equilibre = calculer_nouv_plaque(plaque, nouv_plaque, pos_fixes,
			dimy, dimx, mode, epsilon, coeff);

		//copie nouvelle plaque dans ancienne  

		moyenne = copier_nouv_plaque(plaque, nouv_plaque, dimy, dimx,
			mint, maxt);

		// Dessine l'�chelle des temp�ratures 

		dessiner_echelle(*mint, *maxt);

		// Affiche la plaque actuelle 

		afficher_plaque(plaque, dimy, dimx, *mint, *maxt);

		//on incr�mente le compteur d'it�rations
		iteration++;

		//boucle continue tant que �quilibre n`est pas atteint 
	} while (equilibre == 0);


	//pour afficher valeur actuel de mint maxt 
	aff_minmax_moy(*mint, *maxt, copier_nouv_plaque(plaque, nouv_plaque,
		dimy, dimx, mint, maxt));

	
	 //On retourne le nombre d'it�rations
	return iteration;

}

