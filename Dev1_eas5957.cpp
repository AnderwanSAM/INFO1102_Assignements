// Dev1_eas5957.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
/*
Nom : Andie Erwan SAMADOULOUGOU
NI : A00 200 508
Compte : eas5957@umoncton.ca
*/


#include "pch.h"
#include <iostream>
#include <string>
#include <fstream> 
using namespace std;

const short uneGrilleDimension = 9;
typedef short uneGrille[uneGrilleDimension][uneGrilleDimension];
const short bloc_A_Debut = 0;
const short bloc_A_Fin = 2;
const short bloc_B_Debut = 3;
const short bloc_B_Fin = 5;
const short bloc_C_Debut = 6;
const short bloc_C_Fin = 8;


bool sont_rangees_OK(short  grille[][uneGrilleDimension])
{
	bool VERIFICATION = true;

	// Tâche : Vérifications des rangées
	for (int rangee = 0; rangee < uneGrilleDimension; rangee++)
	{
		// Mettre les compteurs à zéro avant de vérifier UNE rangée.
		int frequence[uneGrilleDimension] = { 0 };

		// Pour la rangée, nous allons compter la fréquence des chiffres 1 à 9. 
			// Le chiffre #K est associé au compteur #(K-1) d'où (grille[rangee][colonne]) - 1.
		for (int colonne = 0; colonne < uneGrilleDimension; colonne++)
			++frequence[(grille[rangee][colonne]) - 1];

		// vérifier que chaque chiffre n'apparaît qu'exactement une seule fois (ni plus, ni moins)
		// dans une rangée.
		for (int K = 0; K < uneGrilleDimension; K++)
			if (frequence[K] != 1)
			{
				VERIFICATION = false;
				cout << "La rangee " << rangee << " est fautive." << endl;
				break; // Une erreur dans la rangée suffit pour dire que la rangée est fautive.
			}
	}//fin de Vérifications des rangées.
	return VERIFICATION;

}
bool sont_colonnes_OK(short grille[][uneGrilleDimension])
{
	bool VERIFICATION = true;

	// Tâche : Vérifications des colonnes
	for (int colonne = 0; colonne < uneGrilleDimension; colonne++)
	{
		// Mettre les compteurs à zéro avant de vérifier UNE colonne.
		int frequence[uneGrilleDimension] = { 0 };

		// Pour la colonne, nous allons compter la fréquence des chiffres 1 à 9. 
			// Le chiffre #K est associé au compteur #(K-1) d'où (grille[rangee][colonne]) - 1.
		for (int rangee = 0; rangee < uneGrilleDimension; rangee++)
			++frequence[(grille[rangee][colonne]) - 1];

		// vérifier que chaque chiffre n'apparaît qu'exactement une seule fois (ni plus, ni moins)
		// dans une colonne.
		for (int K = 0; K < uneGrilleDimension; K++)
			if (frequence[K] != 1)
			{
				VERIFICATION = false;
				cout << "La colonne " << colonne << " est fautive." << endl;
				break; // Une erreur dans la colonne suffit pour dire que la colonne est fautive.
			}
	}//fin de Vérifications des colonnes.
	return VERIFICATION;
}
bool sont_blocs_OK(short  grille[][uneGrilleDimension])
{

	// Mettre les compteurs à zéro avant de vérifier les blocs.
	int frequence[uneGrilleDimension][uneGrilleDimension] = { 0 };
	// La rangée #K de frequence[][] contient les compteurs pour le bloc #K.

	// Le chiffre #K est associé au compteur (colonne) #(K-1) d'où (grille[rangee][colonne]) - 1.

	// On fait l'acquisition des fréquences pour tous les blocs avant de vérifier.
	for (int rangee = 0; rangee < uneGrilleDimension; rangee++)
		for (int colonne = 0; colonne < uneGrilleDimension; colonne++)
		{
			short numero_de_bloc = ((rangee / 3) * 3) + colonne / 3; // Voir la formule de l'énoncé du labo #1.
			++frequence[numero_de_bloc][(grille[rangee][colonne]) - 1];
		}

	bool VERIFICATION = true;

	for (short bloc = 0; bloc < uneGrilleDimension; bloc++)
	{
		// vérifier que chaque chiffre n'apparaît qu'exactement une seule fois (ni plus, ni moins)
		// dans un bloc.
		for (int K = 0; K < uneGrilleDimension; K++)
			if (frequence[bloc][K] != 1)
			{
				VERIFICATION = false;
				cout << "Le bloc " << bloc << " est fautif." << endl;
				break; // Une erreur dans le bloc suffit pour dire que le bloc est fautif.
			}

	}//fin de Vérifications des blocs.
	return VERIFICATION;
}
bool EstSudoku(short  grille[][uneGrilleDimension])
{
	bool rangees_OK = sont_rangees_OK(grille);
	bool colonnes_OK = sont_colonnes_OK(grille);
	bool blocs_OK = sont_blocs_OK(grille);

	return rangees_OK && colonnes_OK && blocs_OK;

} // fin -  EstSudoku( )
void echanger(short &A, short &B)
{
	short C = A;
	A = B;
	B = C;
}
bool nombre_correct(short n)
{
	if ((n >= 1) && (n <= 9)) { return true; }
	else { return false; }
}
void lire_la_grille(string fichier, uneGrille G)
{
	ifstream lire(fichier, ios::in); short jeton;
	for (short rangee = 0; rangee < 9; rangee++)
	{
		for (short position = 0; position < 9; position++)
		{
			lire >> jeton; if (nombre_correct(jeton) == true) { G[rangee][position] = jeton; }
			else { cout << endl << " //Erreur ****// Un des nombres presents dans le fichier n'est pas compris dans l'intervalle [1,9]  "<< endl << " Il est probable qu'un des nombres soit  incorrect ou qu'il n'y ait pas assez de nombres   " << endl << endl; }
		}
	}
}
void remplir_grille(short A[][9], char bloc[][21])
{ /* remplir la grille en utilisant une formule basée sur le fait que les chiffres de la grille sont dans les colonnes impaires et sur les rangees impaires de la grande grille visuelle  */
	for (short rangee = 0; rangee < 9; rangee++)
	{
		for (short position = 0; position < 9; position++)
		{
			if (A[rangee][position] == 0) { bloc[rangee * 2 + 1][position * 2 + 1] = ' '; }
			else {
				bloc[rangee * 2 + 1][position * 2 + 1] = char(48 + A[rangee][position]);
			}
		}
	}
}
void afficher(uneGrille G)
{	// grille visuelle
	char grille[19][21] = {	// 0            1         2             3       4         5            6        7           8        9        10         11         12          13     14           15           16       17        18        19
	   {char(201), char(205), char(203), char(205), char(203), char(205), char(203), char(205),char(203), char(205),char(203), char(205),char(203), char(205),char(203), char(205), char(203), char(205), char(187), '\0' },	   {char(186), '0',       char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186),  '0',  char(186) , '0',   char(186),'\0' },	   {char(204), char(205), char(206), char(205), char(206),char(205), char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205), char(185), '\0' },	   {char(186), '0',       char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186),  '0',  char(186) , '0',   char(186),'\0' },	   {char(204), char(205), char(206), char(205), char(206),char(205), char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205), char(185), '\0' },	   {char(186), '0',       char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186),  '0',  char(186) , '0',   char(186),'\0' },	   {char(204), char(205), char(206), char(205), char(206),char(205), char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205), char(185), '\0' },	   {char(186), '0',       char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186),  '0',  char(186) , '0',   char(186),'\0' },	   {char(204), char(205), char(206), char(205), char(206),char(205), char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205), char(185), '\0' },	   {char(186), '0',       char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186),  '0',  char(186) , '0',   char(186),'\0' },	   {char(204), char(205), char(206), char(205), char(206),char(205), char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205), char(185), '\0' },	   {char(186), '0',       char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186),  '0',  char(186) , '0',   char(186),'\0' },	   {char(204), char(205), char(206), char(205), char(206),char(205), char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205), char(185), '\0' },	   {char(186), '0',       char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186),  '0',  char(186) , '0',   char(186),'\0' },	   {char(204), char(205), char(206), char(205), char(206),char(205), char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205), char(185), '\0' },	   {char(186), '0',       char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186),  '0',  char(186) , '0',   char(186),'\0' },	   {char(204), char(205), char(206), char(205), char(206),char(205), char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205),char(206),char(205), char(185), '\0' },	   {char(186), '0',       char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186), '0',  char(186) , '0',   char(186),  '0',  char(186) , '0',   char(186),'\0' },	   {char(200), char(205), char(202), char(205),char(202), char(205),char(202), char(205),char(202), char(205),char(202), char(205),char(202), char(205),char(202), char(205),char(202), char(205), char(188), '\0' } };
	// remplissage de la grille visuelle avec les chiffres de la grille de sudoku
	remplir_grille(G, grille);
	// affcihage visuel 
	for (int i = 0; i < 19; i++)
	{
		cout << grille[i] << endl;
	}
}
void conserver_experimentale(uneGrille G, unsigned short a_garder)
{
	unsigned short a_supprimer = 81 - a_garder; unsigned short rangee = 0; unsigned colonne = 0 ;	int nb_deja_supprime = 0;
	while (nb_deja_supprime <= a_supprimer)
	{
		rangee = rand() % 10; colonne = rand() % 10;
		if (G[rangee][colonne] != 0) { G[rangee][colonne] = 0;  nb_deja_supprime += 1; }
	}
}
void conserver(uneGrille G, unsigned short a_garder)
{
	unsigned short a_supprimer = 81 - a_garder;// determination du nombre de chiffres a effacer 
	for (short compteur = 0; compteur < a_supprimer; compteur++)
	{
		G[rand() % 10][rand() % 10] = 0; // de facon aleatoire, des valeurs de la grille sont remplacees par 0 / une disposition a ete prise dans la fonction de remplissage pour qu'elle ache quoi faire 
	}
}
bool valider_intervalle(unsigned short a, unsigned short b)
{
	switch (a)
	{ // validation des intervalles -- en eliminant les cas ou c'est vrai on tire directement les cas faux 
	case 0: if (b != 1 && b != 2) { return false; }; break; 
	case 1: if (b != 0 && b != 2) { return false; }; break;
	case 2: if (b != 1 && b != 0) { return false; }; break;
	case 3: if (b != 4 && b != 5) { return false; }; break;
	case 4:if (b != 3 && b != 5) { return false; }; break;
	case 5:if (b != 3 && b != 4) { return false; }; break;
	case 6: if (b != 7 && b != 8) { return false; }; break;
	case 7: if (b != 8 && b != 6) { return false; }; break;
	case 8: if (b != 7 && b != 6) { return false; }; break;
	}
	return true;
}
void echangerRangees(uneGrille G, unsigned short rangee1, unsigned short rangee2)
{
	// pour tous les elements de la rangees , effectuer l'echangee;
	if (valider_intervalle(rangee1, rangee2) == true)
	{ // on fixe la rangee et on fait varier la position de colonnes 
		for (short i = 0; i < 9; i++)
		{
			echanger(G[rangee1][i], G[rangee2][i]);
		}
	}
	else { cout << endl << endl << " rangees imcompatibles pour l'echange :( " << endl << endl << endl; }
}
void echangerColonnes(uneGrille G, unsigned short colonne1, unsigned  colonne2)
{
	if (valider_intervalle(colonne1, colonne2) == true)
	{ // on fixe la colonne et on fait varier la position dans la rangee 
		for (short i = 0; i < 9; i++)
		{
			echanger(G[i][colonne1], G[i][colonne2]);
		}
	}
	else { cout << endl << endl << " colonnes  imcompatibles pour l'echange :( " << endl << endl << endl; }
};
void echangerRangees_special(uneGrille G, unsigned short rangee1, unsigned short rangee2)
{// disposition speciale pour l'echange des blocs *----sans processus de verification de l'intervalle
	for (short i = 0; i < 9; i++)
	{
		echanger(G[rangee1][i], G[rangee2][i]);
	}
}
void echangerGroupesHorizontaux(uneGrille G, char G1, char G2)
{ /*Tous les cas sont pris en compte --- un echange de groupe de blocs correspond a un echange colonnes entieres ou de rangees entieres --- elles sont customisées en fonction du cas ----Par exemple , echanger H A B correspond a l'echange des lignes 0,1,2 et 3,4,5 */
	switch (G1)
	{
	case 'A':
		if (G2 == 'B')
		{
			//echangerRangees_special(G, 0, 3);
			for (short indice = 0; indice < 3; indice++)
			{
				echangerRangees_special(G, indice, (indice + 3));
			}
		}
		else // G2 = 'C'
		{
			for (short indice = 0; indice < 3; indice++)
			{
				echangerRangees_special(G, indice, (indice + 6));
			}
		}
		break;
	case 'B ':
		if (G2 == 'A')
		{
			for (short indice = 3; indice < 6; indice++)
			{
				echangerRangees_special(G, indice, (indice - 3));
			}
		}
		else // G2 = 'C'
		{
			for (short indice = 3; indice < 6; indice++)
			{
				echangerRangees_special(G, indice, (indice + 3));
			}
		}
		break;
	case 'C':
		if (G2 == 'A')
		{
			for (short indice = 6; indice < 9; indice++)
			{
				echangerRangees_special(G, indice, (indice - 6));
			}
		}
		else // G2 = 'B'
		{
			for (short indice = 6; indice < 9; indice++)
			{
				echangerRangees_special(G, indice, (indice - 3));
			}
		}
		break;
	default:
		break;
	}
}
void echangerColonnes_special(uneGrille G, unsigned short colonne1, unsigned  colonne2)
{// disposition speciale pour l'echange des blocs *----sans processus de verification de l'intervalle
	for (short i = 0; i < 9; i++)
	{
		echanger(G[i][colonne1], G[i][colonne2]);
	}
};
void echangerGroupesVerticaux(uneGrille G, char G1, char G2)
{
	switch (G1)
	{
	case 'A':
		if (G2 == 'B')
		{
			for (short indice = 0; indice < 3; indice++)
			{
				echangerColonnes_special(G, indice, (indice + 3));
			}
		}
		else // G2 = 'C'
		{
			for (short indice = 0; indice < 3; indice++)
			{
				echangerColonnes_special(G, indice, (indice + 6));
			}
		}
		break;
	case 'B ':
		if (G2 == 'A')
		{
			for (short indice = 3; indice < 6; indice++)
			{
				echangerColonnes_special(G, indice, (indice - 3));
			}
		}
		else // G2 = 'C'
		{
			for (short indice = 3; indice < 6; indice++)
			{
				echangerColonnes_special(G, indice, (indice + 3));
			}
		}
		break;
	case 'C':
		if (G2 == 'A')
		{
			for (short indice = 6; indice < 9; indice++)
			{
				echangerColonnes_special(G, indice, (indice - 6));
			}
		}
		else // G2 = 'B'
		{
			for (short indice = 6; indice < 9; indice++)
			{
				echangerColonnes_special(G, indice, (indice - 3));
			}
		}
		break;
	default:
		break;
	}
}
void permuter(uneGrille G, string commandes)
{
	ifstream lire(commandes, ios::in);
	char jeton = '0';
	while (jeton != 'F')
	{
		lire >> jeton; char operande1 = jeton;
		lire >> jeton; char operande2 = jeton;
		lire >> jeton; char operande3 = jeton;
		switch (operande1)
		{
		case 'R':
			echangerRangees(G, short(operande2 - '0'), short(operande3 - '0'));
			cout << "  Resultat : est sudoku - echange de rangees === > " << EstSudoku(G) << endl;
			afficher(G);
			break;
		case 'C':
			echangerColonnes(G, short(operande2 - '0'), short(operande3 - '0'));
			cout << " est sudoku - echange de colonne === > " << EstSudoku(G) << endl;
			afficher(G);
			break;
		case 'H':
			echangerGroupesHorizontaux(G, operande2, operande3);
			cout << " est sudoku - echange de bloc horizontaux  === > " << EstSudoku(G) << endl;
			afficher(G);
			break;
		case 'V':
			echangerGroupesVerticaux(G, operande2, operande3);
			cout << " est sudoku - echange de blocs verticaux  === > " << EstSudoku(G) << endl;
			afficher(G);
			break;
		case 'F':
			break;
		default:
			break;
		}

	}
	lire.close();
}

int main()
{
	cout << " Veuillez entrer le nom du fichier contenant la definition ddu sudoku :   ";  
	string fichier_sudoku , fichier_commandes;
	cin >> fichier_sudoku; uneGrille sudoku;
	lire_la_grille(fichier_sudoku, sudoku);
	cout << endl << endl; afficher(sudoku); cout << endl;	cout << "Test EstSudoku ===> " << EstSudoku(sudoku) << endl << endl; 
	cout << " Veuillez entrer le nom du fichier de commandes :  "; cin >> fichier_commandes;
	cout << endl; permuter(sudoku, fichier_commandes); cout << endl << endl << endl;
	afficher(sudoku);  cout << "Test EstSudoku ===> " << EstSudoku(sudoku) << endl << endl;
	int nb_a_conserver; cout << " Veuillez entrer le nombre de chiffres a conserver  :  "; cin >> nb_a_conserver; conserver_experimentale(sudoku, nb_a_conserver);
	cout << endl << endl << endl;
	afficher(sudoku);
	cout << endl << endl << endl;

}

