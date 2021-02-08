/*
INFO 1102 - Hiver 2020
Devoir2 - Question 1
Nom : Andie Erwan Kiswendsida SAMADOULOUGOU
NI : A00200508
courriel : eas5957@umoncton.ca
*/
#include <iostream>
#include <string>

using namespace std; 

// fonctions 
double generateur(short N);
bool verifier_taille_bit(short N);// pas sur de l'utiliser..hum ... etre sur que l'on ne depase pas les bits que l'on peut occuper
void recueillir_infos(short &Nb_de_bits, short &Nb_intervalles, long long  &Nb_tests);// interagir avec l'usager 
double calcul_taille_intervalles(long long  Nb_divisions);// diviser [0.0; 1.0) en N(intervalles) de taille egales 
void afficher_intervalles(long long  Nb_intervalles);// affichage des intervalles
void calculer_erreurs(long long  Nb_intervalles , double &Erreur_moyenne, double &Erreur_relative_moyenne , long Frequence_attendue,  long Frequences[], long Erreurs[], double Erreurs_relatives[]);
void calculer_erreur(long frequence_attendue, long Erreurs[], long Frequences[], long long  Nb_intervalles); // calculer les erreurs par intervalle 
void calculer_erreurs_relatives(long frequence_attendue, double Erreurs_relatives[], long Erreurs[], long long  Nb_intervalles); // calculer les erreurs relatives par intervalle
void rendre_positif(long &erreur_negative); // rendre les erreurs negatives positives pour le calcul de l'erreur moyenne 
double  cacluer_erreur_moyenne(long Erreurs[] , long long nb_intervalles ); // calculer l'erreur moyennne 
double  calculer_erreur_moyenne_relative(long frequence_attendue, double Erreur_moyenne); // calculer l'erreur moyenne relative
void afficher(long long   Nb_intervalles, double Erreur_moyenne, double Erreur_relative_moyenne, long Frequence_attendue, long Frequences[], long Erreurs[], double Erreurs_relatives[]);





int main()
{
	short Nb_bits, Nb_intervalles; long  long Nb_tests;
	long  Frequence[100] = {0};
	// recueillir les infos 
	recueillir_infos(Nb_bits, Nb_intervalles, Nb_tests);
	long frequence_attendue = Nb_tests / Nb_intervalles;
	// afficher les intervalles 
	cout << endl << endl << endl << "Les intervalles : " << endl << endl;
	afficher_intervalles(Nb_intervalles);

	for (short i =0 ; i< Nb_tests ; i++)
	{
		short indice = generateur(Nb_bits) * Nb_intervalles;
		Frequence[indice]++;
	}

	//long frequence_attendue = Nb_tests / Nb_intervalles;
	long Erreurs[100];
	double Erreur_moyenne, Erreur_relative_moyenne, Erreurs_relatives[100];
	calculer_erreurs(Nb_intervalles, Erreur_moyenne, Erreur_relative_moyenne, frequence_attendue, Frequence, Erreurs, Erreurs_relatives);
	afficher(Nb_intervalles, Erreur_moyenne, Erreur_relative_moyenne, frequence_attendue, Frequence, Erreurs, Erreurs_relatives);
	

}


























void afficher(long long   Nb_intervalles, double Erreur_moyenne, double Erreur_relative_moyenne, long Frequence_attendue, long Frequences[], long Erreurs[], double Erreurs_relatives[])
{
	cout << endl << endl << " Les tests sont finis. Voici les resultats : " << endl;
	cout << endl << "Frequence attendue =  " << Frequence_attendue << endl;
	cout << "Intervalle" << "                                             "/*45*/ << "Frequence" << "                                             " << "Erreur relative" << endl;
	for (long long i =0 ; i< Nb_intervalles; i++)
	{
		cout << i << "                                                          " << Frequences[i] << "                                                  " << Erreurs_relatives[i] << endl;
	}
	cout << endl << endl << "Erreur moyenne :  " << Erreur_moyenne << endl;
	cout << endl << endl << "Erreur relative moyenne  :  " << Erreur_relative_moyenne << "%"<<  endl;
}

void calculer_erreurs(long long   Nb_intervalles, double &Erreur_moyenne, double &Erreur_relative_moyenne, long Frequence_attendue, long Frequences[], long Erreurs[], double Erreurs_relatives[]) 
{
	// calculer les Erreurs et les mettre dans un tableau 
	calculer_erreur(Frequence_attendue, Erreurs, Frequences, Nb_intervalles);
	// calculer les erreurs relatives 
	calculer_erreurs_relatives(Frequence_attendue, Erreurs_relatives, Erreurs, Nb_intervalles);
	// calculer l'erreur moyenne
	Erreur_moyenne = cacluer_erreur_moyenne(Erreurs, Nb_intervalles);
	//calculer l'erreur moyenne relative
	Erreur_relative_moyenne = calculer_erreur_moyenne_relative(Frequence_attendue, Erreur_moyenne);

};

void calculer_erreur(long frequence_attendue, long Erreurs[], long Frequences[], long long  Nb_intervalles)
{
	for (long long i =0 ; i< Nb_intervalles; i++)
	{
		Erreurs[i] = Frequences[i] - frequence_attendue; 
	}
}

void calculer_erreurs_relatives(long frequence_attendue, double Erreurs_relatives[], long Erreurs[], long long  Nb_intervalles)
{
	for (short i =0 ; i< Nb_intervalles; i++)
	{
		Erreurs_relatives[i] = ((100 * (Erreurs[i])) / frequence_attendue );
	}
}
void rendre_positif(long &erreur_negative) 
{
	if (erreur_negative < 0) { erreur_negative *= (-1); }
};

double  cacluer_erreur_moyenne(long Erreurs[], long long nb_intervalles) 
{
	long somme_des_Erreurs = 0;
	for (long long i =0 ; i< nb_intervalles; i++)
	{
		if (Erreurs[i] < 0) { rendre_positif(Erreurs[i]); } // si la valeur est negative la rendre positive pour avoir valeur absolue
		somme_des_Erreurs += Erreurs[i]; // additionner les erreurs 
	}
	double erreur_moyenne = (somme_des_Erreurs / nb_intervalles);
	return erreur_moyenne;
};

double  calculer_erreur_moyenne_relative(long frequence_attendue, double Erreur_moyenne)
{
	double erreur_m_r = ((100 * Erreur_moyenne) / frequence_attendue); return erreur_m_r;
};
void afficher_intervalles(long long  Nb_intervalles)
{
	/*string nombre_de_0 = "0."; for (short i = 0; i < nb_bits; i++) { nombre_de_0 += '0'; }
	nombre_de_0 += '1';*/
	double debut = 0.0 , fin = debut ;
	double taille = calcul_taille_intervalles(Nb_intervalles);
	for (short i = 0; i < Nb_intervalles; i++)
	{
		fin = debut + taille;
		cout << "Intervalle " << i << " : [ " << debut << "   ;   " << fin << "  [" << endl;
		debut = fin;
	}
}

double calcul_taille_intervalles( long long  Nb_divisions ) 
{
	return 1.0 / Nb_divisions;
};
void recueillir_infos(short &Nb_de_bits, short &Nb_intervalles, long long  &Nb_tests) 
{
	cout << endl <<  "Veuillez entrer le nombre de bits a utiliser par le generateur  : "; cin >> Nb_de_bits; cout << endl;
	cout << "Combien de tests voulez vous effectuer ?  : "; cin >> Nb_tests; cout << endl; 
	cout << "Combien  d'intervalles voulez vous ? : "; cin >> Nb_intervalles;
};


bool verifier_taille_bit(short N)
{
	return N > 0 && N < 11;
}

double generateur(short N) 
{
	double  terme = 0;
	for (short K = 0; K < N; K++)
	{
		double  chiffre = rand() % 2;
		terme = terme / 2 + chiffre /2 ;
	}
	return terme;
};

unsigned long long aleatoireEntier_a_N_chiffres_binaires(short N)
{
	unsigned long long terme = 0;
	for (short K = 0; K < N; K++)
	{
		unsigned short chiffre = rand() % 2;
		terme = terme * 2 + chiffre;
	}
	return terme;
}
